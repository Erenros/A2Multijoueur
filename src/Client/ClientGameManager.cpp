#include "pch.h"
#include "ClientGameManager.h"

GameManager::GameManager() : bRunning(true), isConnected(false) {
    InitializeCriticalSection(&criticalSection);

    std::string mMapTexturePath = basePath + "/sprite/Map.png";
    if (!mMapTexture.loadFromFile(mMapTexturePath)) {
        std::cerr << "Erreur : Impossible de charger la texture de la carte !" << std::endl;
    }
    else {
        std::cout << "Texture de la carte chargée avec succès." << std::endl;
    }

    // Initialiser le sprite de la carte
    mMapSprite.GetSprite().setTexture(mMapTexture);
    mMap.SetSprite(&mMapSprite);
}

GameManager::~GameManager() {
    if (threadNetwork) WaitForSingleObject(threadNetwork, INFINITE);
    if (threadCommand) WaitForSingleObject(threadCommand, INFINITE);
    DeleteCriticalSection(&criticalSection);
}

void GameManager::ParsePlayerData(const std::string& message, Player& player) {
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

            std::string playerTexturePath = basePath + "/sprite/Soldier.png";
            sf::Texture playerTexture;
            if (!playerTexture.loadFromFile(playerTexturePath)) {
                std::cerr << "Erreur : Impossible de charger la texture du joueur !" << std::endl;
                return;
            }

            mPlayerSprite.GetSprite().setTexture(playerTexture);

            player.Init(&mPlayerSprite, &mInputManager, mSize, mPos, mSpeed, mHp);

            std::cout << "Joueur initialisé à la position : X=" << mPosX << ", Y=" << mPosY << std::endl;
        }
        else {
            std::cerr << "Erreur lors du parsing des données\n";
        }
    }
    else {
        std::cerr << "Message invalide: " << message << "\n";
    }
}

DWORD WINAPI GameManager::StaticClientThreadNetwork(void* pParam) {
    GameManager* gameManager = static_cast<GameManager*>(pParam);
    return gameManager->ClientThreadNetwork();
}

DWORD WINAPI GameManager::StaticClientThreadCommand(void* pParam) {
    GameManager* gameManager = static_cast<GameManager*>(pParam);
    return gameManager->ClientThreadCommand();
}

DWORD WINAPI GameManager::ClientThreadNetwork() {
    std::cout << "[Client] Thread réseau démarré" << std::endl;

    sockaddr_in from;
    socklen_t fromlen = sizeof(from);
    char buffer[4096] = { 0 };
    int ret;

    while (bRunning) {
        ret = recvfrom(socket_client, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&from, &fromlen);
        if (ret > 0) {
            buffer[ret] = '\0';
            std::string message(buffer);

            if (message.find("Initialisation Player:") == 0) {
                EnterCriticalSection(&criticalSection);

                if (pPlayers.find(mPseudo) == pPlayers.end()) {
                    pPlayers[mPseudo] = new Player();
                }

                ParsePlayerData(message, *pPlayers[mPseudo]);
                isConnected = true;

                LeaveCriticalSection(&criticalSection);
            }
            else if (message.find("Position: ") == 0) {
                size_t posStart = message.find("Position: ");
                if (posStart != std::string::npos) {
                    std::string positionData = message.substr(posStart + 10);

                    std::istringstream ss(positionData);
                    std::string posX_str, posY_str;

                    if (std::getline(ss, posX_str, ',') && std::getline(ss, posY_str)) {
                        try {
                            float mPosX = std::stoi(posX_str);
                            float mPosY = std::stoi(posY_str);

                            Vector2 mPlayerPos;
                            mPlayerPos.Init(mPosX, mPosY);

                            EnterCriticalSection(&criticalSection);
                            pPlayers[mPseudo]->SetPosition(mPlayerPos);
                            LeaveCriticalSection(&criticalSection);

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

    std::cout << "[Client] Thread réseau terminé" << std::endl;
    return 0;
}

DWORD WINAPI GameManager::ClientThreadCommand() {
    std::cout << "[Client] Thread commande démarré" << std::endl;

    while (bRunning) {
        if (isConnected) {
            for (const auto& key : { 'Z', 'Q', 'S', 'D', 'I', 'J', 'K', 'L' }) {
                KeyState state = mInputManager.getKeyState(key);

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
        }

        Sleep(16);
    }

    std::cout << "[Client] Thread commande terminé" << std::endl;
    return 0;
}

int GameManager::Init() {
    std::cout << "Initialisation du client..." << std::endl;

    Sleep(1000);
    std::cout << "Client démarré..." << std::endl;

    window.create(sf::VideoMode(1200, 800), "Client: Connexion");

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur WSAStartup : " << WSAGetLastError() << std::endl;
        return -1;
    }

    socket_client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_client == INVALID_SOCKET) {
        std::cerr << "Erreur création socket : " << WSAGetLastError() << std::endl;
        return -2;
    }

    std::cout << "Socket créé avec succès" << std::endl;

    if (!font.loadFromFile("../../font/Poppins-Regular.ttf")) {
        std::cerr << "Impossible de charger la police" << std::endl;
        return -3;
    }

    std::cout << "Police chargée avec succès" << std::endl;

    InitializeCriticalSection(&criticalSection);
    std::cout << "CriticalSection initialisée" << std::endl;

    labelTop.setString("Pseudo:");
    labelTop.setFont(font);
    labelTop.setCharacterSize(35);
    labelTop.setPosition(100, 60);
    labelTop.setFillColor(sf::Color(255, 255, 255));
    labelTop.setOutlineColor(sf::Color(0, 0, 0));
    labelTop.setOutlineThickness(2);

    labelMid.setString("Adresse IP:");
    labelMid.setFont(font);
    labelMid.setCharacterSize(35);
    labelMid.setPosition(100, 220);
    labelMid.setFillColor(sf::Color(255, 255, 255));
    labelMid.setOutlineColor(sf::Color(0, 0, 0));
    labelMid.setOutlineThickness(2);

    labelBottom.setString("Port:");
    labelBottom.setFont(font);
    labelBottom.setCharacterSize(35);
    labelBottom.setPosition(100, 380);
    labelBottom.setFillColor(sf::Color(255, 255, 255));
    labelBottom.setOutlineColor(sf::Color(0, 0, 0));
    labelBottom.setOutlineThickness(2);

    inputAreaTop.setSize(sf::Vector2f(600, 50));
    inputAreaTop.setPosition(250, 60);
    inputAreaTop.setFillColor(sf::Color(50, 50, 50));
    inputAreaTop.setOutlineColor(sf::Color(255, 255, 255));
    inputAreaTop.setOutlineThickness(2);

    inputAreaMid.setSize(sf::Vector2f(600, 50));
    inputAreaMid.setPosition(250, 220);
    inputAreaMid.setFillColor(sf::Color(50, 50, 50));
    inputAreaMid.setOutlineColor(sf::Color(255, 255, 255));
    inputAreaMid.setOutlineThickness(2);

    inputAreaBottom.setSize(sf::Vector2f(600, 50));
    inputAreaBottom.setPosition(250, 380);
    inputAreaBottom.setFillColor(sf::Color(50, 50, 50));
    inputAreaBottom.setOutlineColor(sf::Color(255, 255, 255));
    inputAreaBottom.setOutlineThickness(2);

    textTop.setString("");
    textTop.setFont(font);
    textTop.setCharacterSize(30);
    textTop.setPosition(270, 70);
    textTop.setFillColor(sf::Color(255, 255, 255));

    textMid.setString("");
    textMid.setFont(font);
    textMid.setCharacterSize(30);
    textMid.setPosition(270, 230);
    textMid.setFillColor(sf::Color(255, 255, 255));

    textBottom.setString("");
    textBottom.setFont(font);
    textBottom.setCharacterSize(30);
    textBottom.setPosition(270, 390);
    textBottom.setFillColor(sf::Color(255, 255, 255));

    connectButton.Init(sf::Vector2f(220, 60), sf::Vector2f(290, 500), "Connexion", font);

    window.setFramerateLimit(60);

    threadNetwork = CreateThread(nullptr, 0, StaticClientThreadNetwork, this, 0, nullptr);
    threadCommand = CreateThread(nullptr, 0, StaticClientThreadCommand, this, 0, nullptr);

    if (threadNetwork == NULL || threadCommand == NULL) {
        std::cerr << "Erreur lors de la création des threads" << std::endl;
        return -4;
    }

    return 0;
}

int GameManager::GameLoop() {
    while (window.isOpen() || (isConnected && gameWindow.isOpen())) {
        if (isConnected && !gameWindow.isOpen()) {
            window.close();
            gameWindow.create(sf::VideoMode(1200, 800), "Game Window");
            gameWindow.setFramerateLimit(60);
        }

        if (isConnected) {
            sf::Event event;
            while (gameWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    gameWindow.close();
                }
            }

            gameWindow.clear(sf::Color::Black);

            // Récupérer la position du joueur
            Vector2 playerPos = pPlayers[mPseudo]->GetPosition();

            // Créer une transformation pour simuler la caméra
            sf::Transform transform;
            transform.translate(-playerPos.GetX() + 600, -playerPos.GetY() + 400);  // 600 et 400 sont les moitiés de la taille de la fenêtre

            // Dessiner la carte avec la transformation
            if (mMap.GetSprite()) {
                mMap.Render(gameWindow, transform);  // Passer la transformation à la méthode Render
            }
            else {
                std::cerr << "Erreur : La carte n'est pas initialisée !" << std::endl;
                return -1;
            }

            // Dessiner le joueur avec la transformation
            if (pPlayers.find(mPseudo) != pPlayers.end() && pPlayers[mPseudo]) {
                pPlayers[mPseudo]->Render(gameWindow, transform);  // Passer la transformation à la méthode Render
            }
            else {
                std::cerr << "Erreur : Le joueur n'est pas initialisé !" << std::endl;
                return -2;
            }

            gameWindow.display();
        }
        else {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (inputAreaTop.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isInTopArea = true;
                        isInMidArea = false;
                        isInBottomArea = false;

                        inputAreaTop.setFillColor(sf::Color(100, 100, 50));
                        inputAreaMid.setFillColor(sf::Color(80, 80, 80));
                        inputAreaBottom.setFillColor(sf::Color(80, 80, 80));
                    }
                    else if (inputAreaMid.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isInTopArea = false;
                        isInMidArea = true;
                        isInBottomArea = false;

                        inputAreaTop.setFillColor(sf::Color(80, 80, 80));
                        inputAreaMid.setFillColor(sf::Color(100, 100, 50));
                        inputAreaBottom.setFillColor(sf::Color(80, 80, 80));
                    }
                    else if (inputAreaBottom.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isInTopArea = false;
                        isInMidArea = false;
                        isInBottomArea = true;

                        inputAreaTop.setFillColor(sf::Color(80, 80, 80));
                        inputAreaMid.setFillColor(sf::Color(80, 80, 80));
                        inputAreaBottom.setFillColor(sf::Color(100, 100, 50));
                    }
                    else if (connectButton.isPressed()) {
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

            textTop.setString(inputTextTop);
            textMid.setString(inputTextMid);
            textBottom.setString(inputTextBottom);

            window.clear(sf::Color::White);

            window.draw(labelTop);
            window.draw(labelMid);
            window.draw(labelBottom);
            window.draw(inputAreaTop);
            window.draw(inputAreaMid);
            window.draw(inputAreaBottom);
            window.draw(textTop);
            window.draw(textMid);
            window.draw(textBottom);

            connectButton.Update(sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            connectButton.Draw(window);

            window.display();
        }
    }
    return 0;
}

void GameManager::Uninit() {
    DeleteCriticalSection(&criticalSection);
}