#include "pch.h"
#include "HostGameManager.h"

GameManager::GameManager()
{
}

DWORD WINAPI GameManager::StaticServerThreadNetwork(void* pParam)
{
    GameManager* gameManager = static_cast<GameManager*>(pParam);
    return gameManager->ServerThreadNetwork(pParam);
}

DWORD WINAPI GameManager::StaticServerThreadGame(void* pParam)
{
    GameManager* gameManager = static_cast<GameManager*>(pParam);
    return gameManager->ServerThreadGame(pParam);
}


DWORD __stdcall GameManager::ServerThreadNetwork(void* pParam)
{
    sockaddr_in from;
    socklen_t fromlen = sizeof(from);
    char buffer[4096];
    int ret;

    while (*(bool*)pParam) {
        ret = recvfrom(server_UDP, buffer, sizeof(buffer), 0, (sockaddr*)&from, &fromlen);
        if (ret > 0) {
            buffer[ret] = '\0'; // Null terminate the message
            std::cout << "Serveur a recu : " << buffer << std::endl;

            if (std::string(buffer).find("Connexion, Pseudo: ") == 0) {
                size_t pos = std::string(buffer).find("Pseudo: ");
                if (pos != std::string::npos) {
                    std::string pseudo = std::string(buffer).substr(pos + 8);

                    EnterCriticalSection(&criticalSection); // Protéger l'accès partagé
                    if (pPlayers.find(pseudo) != pPlayers.end()) {
                        std::cout << "Le pseudo: '" << pseudo << "' est deja pris!" << std::endl;
                        const char* responseCstr = "Refuse: Pseudo existe deja";
                        sendto(server_UDP, responseCstr, strlen(responseCstr), 0, (sockaddr*)&from, fromlen);
                    }
                    else {
                        std::cout << "Le pseudo: '" << pseudo << "' est disponible!" << std::endl;
                        std::string texturePath = basePath + "/sprite/Soldier.png";

                        // Charger la texture pour le sprite
                        sf::Texture texture;
                        if (!texture.loadFromFile(texturePath)) {
                            std::cout << "Erreur : Impossible de charger l'image '" << texturePath << "' !" << std::endl;
                            return -1;
                        }

                        std::cout << "Texture chargée depuis : " << texturePath << std::endl;

                        mPlayerSprite.GetSprite().setTexture(texture);

                        sf::Vector2u textureSize = texture.getSize();

                        sf::Vector2f scale = mPlayerSprite.GetSprite().getScale();
                        Vector2 size;
                        size.Init(static_cast<float>(textureSize.x) * scale.x, static_cast<float>(textureSize.y) * scale.y);

                        Vector2 position;
                        position.Init(375.0f, 550.0f);

                        Player* player = new Player;
                        player->Init(&mPlayerSprite, &mInputManager, size, position, 10.10f, 100);
                        pPlayers.insert(make_pair(pseudo, player));

                        std::ostringstream response;
                        response << "Initialisation Player: (" << player->GetPosition().GetX() << ", "
                            << player->GetPosition().GetY() << ", " << player->GetSpeed() << ", "
                            << player->GetSize().GetX() << ", " << player->GetSize().GetY() << ", "
                            << player->GetHp();
                        const std::string strResponse = response.str();
                        const char* responseCstr = strResponse.c_str();
                        sendto(server_UDP, responseCstr, strlen(responseCstr), 0, (sockaddr*)&from, fromlen);
                    }
                    LeaveCriticalSection(&criticalSection);
                }
            }
            else if (std::string(buffer).find("InGame, Pseudo: ") == 0) {
                size_t pseudoPos = std::string(buffer).find("InGame, Pseudo: ");
                size_t inputPos = std::string(buffer).find("Input: ");

                size_t pseudoStart = pseudoPos + 16;
                size_t pseudoEnd = std::string(buffer).find(" \n", pseudoStart);
                std::string pseudo = std::string(buffer).substr(pseudoStart, pseudoEnd - pseudoStart);

                std::cout << "Pseudo extrait: " << pseudo << std::endl;

                size_t inputStart = inputPos + 7;
                std::string input = std::string(buffer).substr(inputStart);

                std::cout << "Input extrait: " << input << std::endl;

                if (inputPos != std::string::npos) {
                    std::string inputMsg = input;

                    EnterCriticalSection(&criticalSection);
                    auto it = pPlayers.find(pseudo);
                    if (it != pPlayers.end()) {
                        Player* player = it->second;
                        if (inputMsg == "z") {
                            player->Move(2, 0.16); // Mouvement vers le haut
                        }
                        else if (inputMsg == "q") {
                            player->Move(1, 0.16); // Mouvement gauche
                        }
                        else if (inputMsg == "s") {
                            player->Move(3, 0.16); // Mouvement bas
                        }
                        else if (inputMsg == "d") {
                            player->Move(0, 0.16); // Mouvement droite
                        }

                        std::ostringstream updatePos;
                        updatePos << "Position: "
                            << player->GetPosition().GetX()
                            << ","
                            << player->GetPosition().GetY();
                        const std::string StrupdatePos = updatePos.str();
                        const char* updatePos_cstr = StrupdatePos.c_str();

                        sendto(server_UDP, updatePos_cstr, strlen(updatePos_cstr), 0, (sockaddr*)&from, fromlen);
                    }
                    LeaveCriticalSection(&criticalSection);
                }
            }
        }
    }
    return 0;
}

DWORD __stdcall GameManager::ServerThreadGame(void* pParam)
{
    while (*(bool*)pParam) {
        EnterCriticalSection(&criticalSection);
        for (auto& [playerId, player] : pPlayers) {
            // Logique de gestion de jeu
        }
        LeaveCriticalSection(&criticalSection);
        Sleep(100); // Limite de vitesse du thread
    }
    return 0;
}

int GameManager::Init()
{
    std::cout << "Serveur demarre..." << std::endl;
    std::cout << "Serveur en ecoute sur le port " << port << std::endl;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur WSAStartup : " << WSAGetLastError() << std::endl;
        return -1;
    }

    server_UDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server_UDP == INVALID_SOCKET) {
        std::cerr << "Erreur creation socket : " << WSAGetLastError() << std::endl;
        return -2;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_UDP, (sockaddr*)&addr, sizeof(addr)) != 0) {
        std::cerr << "Erreur bind : " << WSAGetLastError() << std::endl;
        return -3;
    }

    bool running = true;
    InitializeCriticalSection(&criticalSection);

    HANDLE threadNetwork = CreateThread(nullptr, 0, StaticServerThreadNetwork, this, 0, nullptr);
    HANDLE threadGame = CreateThread(nullptr, 0, StaticServerThreadGame, this, 0, nullptr);

    // Attend la fin des threads
    WaitForSingleObject(threadNetwork, INFINITE);
    WaitForSingleObject(threadGame, INFINITE);

    window.create(sf::VideoMode(windowWidth, windowHeight), "Test Player");
    window.setFramerateLimit(60);

    if (!window.isOpen()) {
        std::cout << "Échec de l'ouverture de la fenêtre !" << std::endl;
        return -1;
    }

    // Initialisation de l'obstacle
    obstacleTexturePath = basePath + "/sprite/Obstacle.png";
    
    if (!obstacleTexture.loadFromFile(obstacleTexturePath)) {
        std::cout << "Erreur : Impossible de charger l'image de l'obstacle '" << obstacleTexturePath << "' !" << std::endl;
        return -1;
    }
    mObstacleSprite.GetSprite().setTexture(obstacleTexture);
    std::cout << "Chemin de l'image de l'obstacle : " << obstacleTexturePath << std::endl;  // Affichage du chemin

    sf::Vector2u obstacleTextureSize = obstacleTexture.getSize();
    sf::Vector2f obstacleScale = mObstacleSprite.GetSprite().getScale();
    Vector2 sizeObstacle;
    sizeObstacle.Init(static_cast<float>(obstacleTextureSize.x) * obstacleScale.x, static_cast<float>(obstacleTextureSize.y) * obstacleScale.y);

    positionObstacle.Init(500.0f, 400.0f);
    obstacle.Init(&mObstacleSprite, sizeObstacle, positionObstacle, 0.0f, 0.0f, 100);

    // Initialisation de la map
    mMap.Init(1260, 800, "Game Map");

    return 0;
}


int GameManager::GameLoop()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();  // Effacer l'écran

        // Mettre à jour les objets
        for (auto& [id, player] : pPlayers) {
            sf::Sprite& sprite = player->GetSprite()->GetSprite();
            sprite.setPosition(player->GetPosition().GetX(), player->GetPosition().GetY());
            window.draw(sprite);
        }

        sf::Sprite obstacleSfSprite = obstacle.GetSfSprite();
        obstacleSfSprite.setPosition(positionObstacle.GetX(), positionObstacle.GetY());
        window.draw(obstacleSfSprite);

        window.display();  // Afficher la scène

        mMap.Draw(window);  // Dessiner la map
    }

    return 0;
}

void GameManager::Uninit()
{
    DeleteCriticalSection(&criticalSection);
}
