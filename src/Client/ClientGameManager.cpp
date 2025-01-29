#include "pch.h"
#include "ClientGameManager.h"

GameManager::GameManager()
{
    InitializeCriticalSection(&criticalSection);
}

void GameManager::ParsePlayerData(const std::string& message, Player& player)
{
    std::string prefix = "Initialisation Player: ";
    if (message.find(prefix) == 0) {
        auto openPos = message.find('(');
        auto closePos = message.find(')');
        if (openPos == std::string::npos || closePos == std::string::npos || closePos < openPos) {
            std::cerr << "Format de message invalide (parenthèses manquantes)\n";
            return;
        }

        std::string data = message.substr(openPos + 1, closePos - openPos - 1);
        std::replace(data.begin(), data.end(), ',', ' ');

        std::stringstream ss(data);
        int mPosX, mPosY, mHp;
        float mSpeed, mSizeX, mSizeY;

        Vector2 mSize, mPos;
        if (ss >> mPosX >> mPosY >> mSpeed >> mSizeX >> mSizeY >> mHp) {
            mSize.Init(mSizeX, mSizeY);
            mPos.Init(mPosX, mPosY);
            player.Init(&mPlayerSprite, &mInputManager, mSize, mPos, mSpeed, mHp);

            Vector2 mSizeMap;
            mSizeMap.Init(3000, 3000);
            mMap.Init(3000, 3000, "Window Client");
            std::cout << "---Map créée---" << std::endl;
        }
        else {
            std::cerr << "Erreur lors du parsing des données\n";
        }
    }
    else {
        std::cerr << "Message invalide: " << message << "\n";
    }
}

DWORD WINAPI GameManager::StaticClientThreadNetwork(void* pParam)
{
    GameManager* gameManager = static_cast<GameManager*>(pParam);
    return gameManager->ClientThreadNetwork(pParam);
}

DWORD WINAPI GameManager::StaticClientThreadCommand(void* pParam)
{
    GameManager* gameManager = static_cast<GameManager*>(pParam);
    return gameManager->ClientThreadCommand(pParam);
}


DWORD WINAPI GameManager::ClientThreadNetwork(void* pParam)
{
    ClientThreadParams* params = static_cast<ClientThreadParams*>(pParam);
    bool* isRunning = params->isRunning;
    Player* player = params->player;
    CRITICAL_SECTION* criticalSection = params->criticalSection;

    sockaddr_in from;
    socklen_t fromlen = sizeof(from);
    char buffer[4096];
    int ret;

    while (*(bool*)pParam) {
        ret = recvfrom(socket_client, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&from, &fromlen);
        if (ret > 0) {
            buffer[ret] = '\0';
            std::string message(buffer);

            std::cout << "Vous avez reçu : " << message << std::endl;

            if (message.find("Initialisation Player:") == 0) {
                EnterCriticalSection(criticalSection);
                ParsePlayerData(message, *player); // Initialiser le joueur
                LeaveCriticalSection(criticalSection);
            }
            else if (message.find("Position: ") == 0) {
                size_t posStart = message.find("Position: ");
                if (posStart != std::string::npos) {
                    std::string positionData = message.substr(posStart + 10); // Extraire après "Position: "

                    std::istringstream ss(positionData);
                    std::string posX_str, posY_str;

                    // Séparer les coordonnées posX et posY
                    if (std::getline(ss, posX_str, ',') && std::getline(ss, posY_str)) {
                        try {
                            // Convertir les chaînes en entiers pour les positions
                            float mPosX = std::stoi(posX_str);
                            float mPosY = std::stoi(posY_str);

                            Vector2 mPlayerPos;
                            mPlayerPos.Init(mPosX, mPosY);

                            // Mettre à jour la position du joueur
                            EnterCriticalSection(criticalSection); // Protection multi-thread
                            player->SetPosition(mPlayerPos); // Mettre à jour la position
                            LeaveCriticalSection(criticalSection);

                            std::cout << "Nouvelle position mise à jour : X=" << mPosX << ", Y=" << mPosY << std::endl;
                        }
                        catch (const std::exception& e) {
                            std::cerr << "Erreur lors de l'analyse des coordonnées : " << e.what() << std::endl;
                        }
                    }
                }
            }
        }
        else if (ret == SOCKET_ERROR) {
            std::cerr << "Erreur lors de la réception des données\n";
        }
    }

    return 0;
}

DWORD __stdcall GameManager::ClientThreadCommand(void* pParam)
{
    ClientThreadParams* params = static_cast<ClientThreadParams*>(pParam);
    bool running = (params->isRunning);

    while (running) {
        for (const auto& key : { 'Z', 'Q', 'S', 'D', 'I', 'J', 'K', 'L' }) {
            KeyState state = mInputManager.getKeyState(key);  // Utilisation du pointeur inputManager

            // Envoi au serveur en fonction de l'état
            if (state == Push || state == Down) {
                std::string command;
                command = "InGame, Pseudo: ";
                command += mPseudo;
                command += " \n Input: ";

                switch (key) {
                    case 'Z':
                        command += "z";
                        break;
                    case 'Q':
                        command += "q";
                        break;
                    case 'S':
                        command += "s";
                        break;
                    case 'D':
                        command += "d";
                        break;
                    case 'J':
                        command += "j";
                        break;
                    case 'K':
                        command += "k";
                        break;
                    case 'L':
                        command += "l";
                        break;
                    case 'I':
                        command += "i";
                        break;
                    default:
                        break;
                }

                sendto(socket_client, command.c_str(), command.size(), 0, (sockaddr*)&addrServer, sizeof(addrServer));
                std::cout << "Client envoie : " << command << std::endl;
            }
        }

        Sleep(16);  // Pour éviter une surcharge du processeur
    }

    return 0;
}

int GameManager::Init()
{
        std::cout << "Initialisation du client..." << std::endl;

    Sleep(1000);
    std::cout << "Client demarre..." << std::endl;

    // Créer une fenêtre SFML
    window.create(sf::VideoMode(1200, 800), "Client: Connexion");

    // Initialisation de Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur WSAStartup : " << WSAGetLastError() << std::endl;
        return -1;
    }

    // Création du socket UDP
    socket_client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_client == INVALID_SOCKET) {
        std::cerr << "Erreur creation socket : " << WSAGetLastError() << std::endl;
        return -2;
    }

    std::cout << "Socket créé avec succès" << std::endl;

    // Initialisation de la police de caractères
    font;
    if (!font.loadFromFile("../../font/Poppins-Regular.ttf")) {
        std::cerr << "Impossible de charger la police" << std::endl;
        return -3;
    }

    std::cout << "Police chargée avec succès" << std::endl;

    // Initialisation de la CriticalSection
    InitializeCriticalSection(&criticalSection);
    std::cout << "CriticalSection initialisée" << std::endl;

    // Création des threads
    threadNetwork = CreateThread(nullptr, 0, GameManager::StaticClientThreadNetwork, this, 0, nullptr);
    threadCommand = CreateThread(nullptr, 0, GameManager::StaticClientThreadCommand, this, 0, nullptr);

    if (threadNetwork == NULL || threadCommand == NULL) {
        std::cerr << "Erreur lors de la création des threads" << std::endl;
        return -4;
    }

    std::cout << "Threads créés avec succès" << std::endl;

    // Créer les labels avec un style moderne
    labelTop.setString("Pseudo:");
    labelTop.setFont(font);
    labelTop.setCharacterSize(35);
    labelTop.setPosition(100, 60);
    labelTop.setFillColor(sf::Color(255, 255, 255));  // Blanc

    // Application d'une ombre portée pour un effet de profondeur
    labelTop.setOutlineColor(sf::Color(0, 0, 0));     // Ombre noire
    labelTop.setOutlineThickness(2);

    // Label pour l'adresse IP
    labelMid.setString("Adresse IP:");
    labelMid.setFont(font);
    labelMid.setCharacterSize(35);
    labelMid.setPosition(100, 220);
    labelMid.setFillColor(sf::Color(255, 255, 255));  // Blanc
    labelMid.setOutlineColor(sf::Color(0, 0, 0));     // Ombre noire
    labelMid.setOutlineThickness(2);

    // Label pour le port
    labelBottom.setString("Port:");
    labelBottom.setFont(font);
    labelBottom.setCharacterSize(35);
    labelBottom.setPosition(100, 380);
    labelBottom.setFillColor(sf::Color(255, 255, 255));  // Blanc
    labelBottom.setOutlineColor(sf::Color(0, 0, 0));     // Ombre noire
    labelBottom.setOutlineThickness(2);

    inputAreaTop.setSize(sf::Vector2f(600, 50));
    inputAreaTop.setPosition(250, 60);
    inputAreaTop.setFillColor(sf::Color(50, 50, 50));    // Fond gris foncé
    inputAreaTop.setOutlineColor(sf::Color(255, 255, 255)); // Bordure blanche
    inputAreaTop.setOutlineThickness(2);

    inputAreaMid.setSize(sf::Vector2f(600, 50));
    inputAreaMid.setPosition(250, 220);
    inputAreaMid.setFillColor(sf::Color(50, 50, 50));    // Fond gris foncé
    inputAreaMid.setOutlineColor(sf::Color(255, 255, 255)); // Bordure blanche
    inputAreaMid.setOutlineThickness(2);

    inputAreaBottom.setSize(sf::Vector2f(600, 50));
    inputAreaBottom.setPosition(250, 380);
    inputAreaBottom.setFillColor(sf::Color(50, 50, 50));    // Fond gris foncé
    inputAreaBottom.setOutlineColor(sf::Color(255, 255, 255)); // Bordure blanche
    inputAreaBottom.setOutlineThickness(2);

    textTop.setString("");
    textTop.setFont(font);
    textTop.setCharacterSize(30);
    textTop.setPosition(270, 70);
    textTop.setFillColor(sf::Color(255, 255, 255));  // Texte en blanc

    textMid.setString("");
    textMid.setFont(font);
    textMid.setCharacterSize(30);
    textMid.setPosition(270, 230);
    textMid.setFillColor(sf::Color(255, 255, 255));  // Texte en blanc

    textBottom.setString("");
    textBottom.setFont(font);
    textBottom.setCharacterSize(30);
    textBottom.setPosition(270, 390);
    textBottom.setFillColor(sf::Color(255, 255, 255));  // Texte en blanc

    // Créer un bouton "Se Connecter" avec des coins arrondis et un fond dégradé
    connectButton.Init(sf::Vector2f(220, 60), sf::Vector2f(290, 500), "Connexion", font);

    // Initialisation de la fenêtre
    window.setFramerateLimit(60);
}

int GameManager::GameLoop()
{
    while (window.isOpen())
    {
        bool isWindowActive = window.hasFocus();

        // Gérer les événements SFML
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();

            }
            if (isWindowActive)
            {
                if (isConnected)
                {
                    mInputManager.update();

                    continue;
                }


                else if (event.type == sf::Event::MouseButtonPressed) {
                    // Vérifier où l'utilisateur clique
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (inputAreaTop.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isInTopArea = true;
                        isInMidArea = false;
                        isInBottomArea = false;

                        inputAreaTop.setFillColor(sf::Color(100, 100, 50));  // Vert militaire actif
                        inputAreaMid.setFillColor(sf::Color(80, 80, 80));    // Gris militaire inactif
                        inputAreaBottom.setFillColor(sf::Color(80, 80, 80)); // Gris militaire inactif
                    }
                    else if (inputAreaMid.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isInTopArea = false;
                        isInMidArea = true;
                        isInBottomArea = false;

                        inputAreaTop.setFillColor(sf::Color(80, 80, 80));    // Gris militaire inactif
                        inputAreaMid.setFillColor(sf::Color(100, 100, 50));  // Vert militaire actif
                        inputAreaBottom.setFillColor(sf::Color(80, 80, 80)); // Gris militaire inactif
                    }
                    else if (inputAreaBottom.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isInTopArea = false;
                        isInMidArea = false;
                        isInBottomArea = true;

                        inputAreaTop.setFillColor(sf::Color(80, 80, 80));    // Gris militaire inactif
                        inputAreaMid.setFillColor(sf::Color(80, 80, 80));    // Gris militaire inactif
                        inputAreaBottom.setFillColor(sf::Color(100, 100, 50)); // Vert militaire actif
                    }
                    else if (connectButton.isPressed()) {
                        //Initialise les variables Pseudo, Ip, Port
                        // Afficher les données des zones de texte dans la console
                        std::cout << "Texte dans la zone du haut: " << inputTextTop << std::endl;
                        std::cout << "Texte dans la zone du milieu: " << inputTextMid << std::endl;
                        std::cout << "Texte dans la zone du bas: " << inputTextBottom << std::endl;

                        mPseudo = inputTextTop;
                        ip_Server = inputTextMid.c_str();
                        port = std::stoi(inputTextBottom);

                        addrServer.sin_family = AF_INET;
                        addrServer.sin_port = htons(port);
                        inet_pton(AF_INET, ip_Server, &addrServer.sin_addr);

                        std::string command = "Connexion, Pseudo: " + mPseudo;

                        sendto(socket_client, command.c_str(), command.size(), 0, (sockaddr*)&addrServer, sizeof(addrServer));
                        std::cout << "Client envoie :\n " << command << std::endl;

                    }
                }
            }

            // Gestion des saisies clavier
            if (event.type == sf::Event::TextEntered) {
                if (isInTopArea && event.text.unicode < 128) {
                    if (event.text.unicode == '\b' && !inputTextTop.empty()) {
                        inputTextTop.pop_back();
                    }
                    else {
                        inputTextTop += static_cast<char>(event.text.unicode);
                    }
                }
                else if (isInMidArea && event.text.unicode < 128) {
                    if (event.text.unicode == '\b' && !inputTextMid.empty()) {
                        inputTextMid.pop_back();
                    }
                    else {
                        inputTextMid += static_cast<char>(event.text.unicode);
                    }
                }
                else if (isInBottomArea && event.text.unicode < 128) {
                    if (event.text.unicode == '\b' && !inputTextBottom.empty()) {
                        inputTextBottom.pop_back();
                    }
                    else {
                        inputTextBottom += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }

        if (isConnected)
        {
            window.clear(sf::Color::Black);

            mMap.Render(window);
           // mPseudo.Render(window);
        }

        else
        {
            // Mettre à jour le texte affiché dans les zones
            textTop.setString(inputTextTop);
            textMid.setString(inputTextMid);
            textBottom.setString(inputTextBottom);

            // Effacer la fenêtre
            window.clear(sf::Color::White);

            // Dessiner les éléments
            window.draw(labelTop);
            window.draw(labelMid);
            window.draw(labelBottom);
            window.draw(inputAreaTop);
            window.draw(inputAreaMid);
            window.draw(inputAreaBottom);
            window.draw(textTop);
            window.draw(textMid);
            window.draw(textBottom);

            // Dessiner le bouton "Se Connecter"
            connectButton.Update(sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            connectButton.Draw(window);
        }

        // Afficher la fenêtre
        window.display();
    }
    return 0;
}

void GameManager::Uninit()
{
    DeleteCriticalSection(&criticalSection);
}
