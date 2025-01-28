//#include "pch.h"
//#include <SFML/Graphics.hpp>
//#include "Player.h"
//#include "Obstacle.h"
//#include "Sprite.h"
//#include "Map.h"
//#include "InputManager.h"
//#include "Vector2.h"
//#include <iostream>
//#include <filesystem> // Pour gérer les chemins dynamiquement
//
//int main() {
//
//    //  -------------------------------------   INIT   -------------------------------------
//    // Dimensions de la fenêtre
//    const float windowWidth = 1260.0f;
//    const float windowHeight = 800.0f;
//
//    // Création de la fenêtre principale
//    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Test Player");
//    window.setFramerateLimit(60);
//
//    // Vérification si la fenêtre est bien ouverte
//    if (!window.isOpen()) {
//        std::cout << "Échec de l'ouverture de la fenêtre !" << std::endl;
//        return -1;
//    }
//
//    // Gestionnaire d'entrées
//    InputManager inputManager;
//
//    // ------------- Création et initialisation des sprites -------------
//    SpriteClass playerSprite;
//    SpriteClass obstacleSprite;
//
//    // Définir le chemin relatif dynamiquement
//    std::string basePath = std::filesystem::current_path().parent_path().parent_path().string();
//
//    // ------------- Création du joueur -------------
//    std::string texturePath = basePath + "/sprite/Soldier.png";
//
//    // Charger la texture pour le sprite
//    sf::Texture texture;
//    if (!texture.loadFromFile(texturePath)) {
//        std::cout << "Erreur : Impossible de charger l'image '" << texturePath << "' !" << std::endl;
//        return -1; // Arrêter l'exécution en cas d'erreur
//    }
//
//    std::cout << "Texture chargée depuis : " << texturePath << std::endl;
//
//    // Appliquer la texture au sprite
//    playerSprite.GetSprite().setTexture(texture);
//
//    Player player;
//
//    // Récupérer la taille du sprite du joueur et prendre en compte la mise à l'échelle
//    sf::Vector2u textureSize = texture.getSize();  // Taille de la texture du joueur
//
//    // Appliquer la mise à l'échelle si nécessaire
//    sf::Vector2f scale = playerSprite.GetSprite().getScale();
//    Vector2 size;
//    size.Init(static_cast<float>(textureSize.x) * scale.x, static_cast<float>(textureSize.y) * scale.y);
//
//    Vector2 position;
//    position.Init(375.0f, 550.0f);
//
//    player.Init(&playerSprite, &inputManager, size, position, 10.10f, 100);
//
//    // ------------- Création d'un obstacle -------------
//    Obstacle obstacle;
//
//    // Charger une texture pour l'obstacle
//    std::string obstacleTexturePath = basePath + "/sprite/Obstacle.png";
//    sf::Texture obstacleTexture;
//    if (!obstacleTexture.loadFromFile(obstacleTexturePath)) {
//        std::cout << "Erreur : Impossible de charger l'image de l'obstacle '" << obstacleTexturePath << "' !" << std::endl;
//        return -1; // Arrêter l'exécution en cas d'erreur
//    }
//    obstacleSprite.GetSprite().setTexture(obstacleTexture);
//
//    // Prendre la taille du sprite pour l'obstacle
//    sf::Vector2u obstacleTextureSize = obstacleTexture.getSize();
//
//    // Appliquer la mise à l'échelle si nécessaire
//    sf::Vector2f obstacleScale = obstacleSprite.GetSprite().getScale();
//    Vector2 sizeObstacle;
//    sizeObstacle.Init(static_cast<float>(obstacleTextureSize.x) * obstacleScale.x, static_cast<float>(obstacleTextureSize.y) * obstacleScale.y);
//
//    Vector2 positionObstacle;
//    positionObstacle.Init(500.0f, 400.0f); // Position initiale de l'obstacle
//    obstacle.Init(&obstacleSprite, sizeObstacle, positionObstacle, 0.0f, 0.0f, 100);
//
//    //  -------------------------------------   GAME LOOP   -------------------------------------
//
//    // Boucle principale
//    // Boucle principale
//    Map map;
//    map.Init(1260, 800, "Game Map");
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//        // Enregistrer la position actuelle du joueur
//        Vector2 previousPosition = player.GetPosition();
//
//        // Mettre à jour la position du joueur
//        player.Move(windowWidth, windowHeight);
//
//        // Vérifier les collisions
//        if (player.CollisionAABB(&obstacle)) {
//            std::cout << "Collision détectée entre le joueur et l'obstacle !" << std::endl;
//            // Revenir à la position précédente
//            player.SetPosition(previousPosition);
//        }
//
//        // Mettre à jour la caméra pour suivre le joueur
//        map.UpdateCamera(sf::Vector2f(player.GetPosition().GetX(), player.GetPosition().GetY()), windowWidth, windowHeight);
//
//        // Effacer l'écran
//        window.clear();
//
//        // Appliquer la transformation pour simuler la caméra
//        sf::Transform transform;
//        transform.translate(-player.GetPosition().GetX() + windowWidth / 2.f, -player.GetPosition().GetY() + windowHeight / 2.f);
//
//        // Dessiner les objets principaux dans la fenêtre principale
//        sf::Sprite& sprite = player.GetSprite()->GetSprite();
//        sprite.setPosition(player.GetPosition().GetX(), player.GetPosition().GetY());
//        window.draw(sprite, transform);  // Appliquer la transformation au joueur
//
//        // Dessiner l'obstacle avec transformation
//        sf::Sprite obstacleSfSprite = obstacle.GetSfSprite();
//        obstacleSfSprite.setPosition(positionObstacle.GetX(), positionObstacle.GetY());
//        window.draw(obstacleSfSprite, transform);  // Appliquer la transformation à l'obstacle
//
//        window.display();  // Afficher la scène principale
//
//        // Dessiner la carte dans la fenêtre dédiée à la carte
//        map.Draw(window);
//    }
//
//
//    //  -------------------------------------   UNINIT   -------------------------------------
//    player.Uninit();
//    playerSprite.Uninit();
//
//    return 0;
//}













//#include "pch.h"
//#include <SFML/Graphics.hpp>
//#include <WinSock2.h>
//#include <ws2tcpip.h>
//#pragma comment(lib, "Ws2_32.lib")
//#include "windows.h"
//#include <SFML/Network.hpp>
//
//#include "Player.h"
//#include "Obstacle.h"
//#include "Sprite.h"
//#include "Map.h"
//#include "InputManager.h"
//#include "Vector2.h"
//
//#include <iostream>
//#include <filesystem> // Pour gérer les chemins dynamiquement
//
//
//
//
//
//// ------------- Création des variables -------------
//
//InputManager inputManager;
//
//SpriteClass playerSprite;
//SpriteClass obstacleSprite;
//
//std::map<std::string, Player*> players;
//std::map<std::string, Obstacle> obstacles;
//
//std::string basePath = std::filesystem::current_path().parent_path().parent_path().string();
//
//const float windowWidth = 1260.0f;
//const float windowHeight = 800.0f;
//
//int port = 8080;
//WSAData wsaData;
//SOCKET server_UDP;
//sockaddr_in addr;
//
//CRITICAL_SECTION criticalSection;
//
//DWORD WINAPI ServerThreadNetwork(void* pParam) {
//    sockaddr_in from;
//    socklen_t fromlen = sizeof(from);
//    char buffer[4096];
//    int ret;
//
//    while (*(bool*)pParam) {
//        ret = recvfrom(server_UDP, buffer, sizeof(buffer), 0, (sockaddr*)&from, &fromlen);
//        if (ret > 0) {
//            buffer[ret] = '\0'; // Null terminate the message
//            std::cout << "Serveur a recu : " << buffer << std::endl;
//
//            if (std::string(buffer).find("Connexion, Pseudo: ") == 0) {
//                size_t pos = std::string(buffer).find("Pseudo: ");
//                if (pos != std::string::npos) {
//                    std::string pseudo = std::string(buffer).substr(pos + 8);
//
//                    EnterCriticalSection(&criticalSection); // Protéger l'accès partagé
//                    if (players.find(pseudo) != players.end()) {
//                        std::cout << "Le pseudo: '" << pseudo << "' est deja pris!" << std::endl;
//                        const char* responseCstr = "Refuse: Pseudo existe deja";
//                        sendto(server_UDP, responseCstr, strlen(responseCstr), 0, (sockaddr*)&from, fromlen);
//                    }
//                    else {
//                        std::cout << "Le pseudo: '" << pseudo << "' est disponible!" << std::endl;
//                        std::string texturePath = basePath + "/sprite/Soldier.png";
//
//                        // Charger la texture pour le sprite
//                        sf::Texture texture;
//                        if (!texture.loadFromFile(texturePath)) {
//                            std::cout << "Erreur : Impossible de charger l'image '" << texturePath << "' !" << std::endl;
//                            return -1;
//                        }
//
//                        std::cout << "Texture chargée depuis : " << texturePath << std::endl;
//
//                        playerSprite.GetSprite().setTexture(texture);
//
//                        sf::Vector2u textureSize = texture.getSize();
//
//                        sf::Vector2f scale = playerSprite.GetSprite().getScale();
//                        Vector2 size;
//                        size.Init(static_cast<float>(textureSize.x) * scale.x, static_cast<float>(textureSize.y) * scale.y);
//
//                        Vector2 position;
//                        position.Init(375.0f, 550.0f);
//
//                        Player* player = new Player;
//                        player->Init(&playerSprite, &inputManager, size, position, 10.10f, 100);
//                        players.insert(make_pair(pseudo, player));
//
//                        std::ostringstream response;
//                        response << "Initialisation Player: (" << player->GetPosition().GetX() << ", "
//                            << player->GetPosition().GetY() << ", " << player->GetSpeed() << ", "
//                            << player->GetSize().GetX() << ", " << player->GetSize().GetY() << ", "
//                            << player->GetHp();
//                        const std::string strResponse = response.str();
//                        const char* responseCstr = strResponse.c_str();
//                        sendto(server_UDP, responseCstr, strlen(responseCstr), 0, (sockaddr*)&from, fromlen);
//                    }
//                    LeaveCriticalSection(&criticalSection);
//                }
//            }
//            else if (std::string(buffer).find("InGame, Pseudo: ") == 0) {
//                size_t pseudoPos = std::string(buffer).find("InGame, Pseudo: ");
//                size_t inputPos = std::string(buffer).find("Input: ");
//
//                size_t pseudoStart = pseudoPos + 16;
//                size_t pseudoEnd = std::string(buffer).find(" \n", pseudoStart);
//                std::string pseudo = std::string(buffer).substr(pseudoStart, pseudoEnd - pseudoStart);
//
//                std::cout << "Pseudo extrait: " << pseudo << std::endl;
//
//                size_t inputStart = inputPos + 7;
//                std::string input = std::string(buffer).substr(inputStart);
//
//                std::cout << "Input extrait: " << input << std::endl;
//
//                if (inputPos != std::string::npos) {
//                    std::string inputMsg = input;
//
//                    EnterCriticalSection(&criticalSection);
//                    auto it = players.find(pseudo);
//                    if (it != players.end()) {
//                        Player* player = it->second;
//                        if (inputMsg == "z") {
//                            player->Move(2, 0.16); // Mouvement vers le haut
//                        }
//                        else if (inputMsg == "q") {
//                            player->Move(1, 0.16); // Mouvement gauche
//                        }
//                        else if (inputMsg == "s") {
//                            player->Move(3, 0.16); // Mouvement bas
//                        }
//                        else if (inputMsg == "d") {
//                            player->Move(0, 0.16); // Mouvement droite
//                        }
//
//                        std::ostringstream updatePos;
//                        updatePos << "Position: "
//                            << player->GetPosition().GetX()
//                            << ","
//                            << player->GetPosition().GetY();
//                        const std::string StrupdatePos = updatePos.str();
//                        const char* updatePos_cstr = StrupdatePos.c_str();
//
//                        sendto(server_UDP, updatePos_cstr, strlen(updatePos_cstr), 0, (sockaddr*)&from, fromlen);
//                    }
//                    LeaveCriticalSection(&criticalSection);
//                }
//            }
//        }
//    }
//    return 0;
//}
//
//// Thread pour gérer la logique du jeu
//DWORD WINAPI ServerThreadGame(void* pParam) {
//    while (*(bool*)pParam) {
//        EnterCriticalSection(&criticalSection);
//        for (auto& [playerId, player] : players) {
//            // Logique de gestion de jeu
//        }
//        LeaveCriticalSection(&criticalSection);
//        Sleep(100); // Limite de vitesse du thread
//    }
//    return 0;
//}
//
//int main() {
//    std::cout << "Serveur demarre..." << std::endl;
//    std::cout << "Serveur en ecoute sur le port " << port << std::endl;
//
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        std::cerr << "Erreur WSAStartup : " << WSAGetLastError() << std::endl;
//        return -1;
//    }
//
//    server_UDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//    if (server_UDP == INVALID_SOCKET) {
//        std::cerr << "Erreur creation socket : " << WSAGetLastError() << std::endl;
//        return -2;
//    }
//
//    addr.sin_family = AF_INET;
//    addr.sin_port = htons(port);
//    addr.sin_addr.s_addr = INADDR_ANY;
//
//    if (bind(server_UDP, (sockaddr*)&addr, sizeof(addr)) != 0) {
//        std::cerr << "Erreur bind : " << WSAGetLastError() << std::endl;
//        return -3;
//    }
//
//    bool running = true;
//    InitializeCriticalSection(&criticalSection);
//
//    HANDLE threadNetwork = CreateThread(nullptr, 0, ServerThreadNetwork, &running, 0, nullptr);
//    HANDLE threadGame = CreateThread(nullptr, 0, ServerThreadGame, &running, 0, nullptr);
//
//    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Test Player");
//    window.setFramerateLimit(60);
//
//    if (!window.isOpen()) {
//        std::cout << "Échec de l'ouverture de la fenêtre !" << std::endl;
//        return -1;
//    }
//
//    // Initialisation du joueur
//    std::string obstacleTexturePath = basePath + "/sprite/Obstacle.png";
//    sf::Texture obstacleTexture;
//    if (!obstacleTexture.loadFromFile(obstacleTexturePath)) {
//        std::cout << "Erreur : Impossible de charger l'image de l'obstacle '" << obstacleTexturePath << "' !" << std::endl;
//        return -1;
//    }
//    obstacleSprite.GetSprite().setTexture(obstacleTexture);
//
//    sf::Vector2u obstacleTextureSize = obstacleTexture.getSize();
//    sf::Vector2f obstacleScale = obstacleSprite.GetSprite().getScale();
//    Vector2 sizeObstacle;
//    sizeObstacle.Init(static_cast<float>(obstacleTextureSize.x) * obstacleScale.x, static_cast<float>(obstacleTextureSize.y) * obstacleScale.y);
//
//    Vector2 positionObstacle;
//    positionObstacle.Init(500.0f, 400.0f);
//    Obstacle obstacle;
//    obstacle.Init(&obstacleSprite, sizeObstacle, positionObstacle, 0.0f, 0.0f, 100);
//
//    // Initialisation de la map
//    Map map;
//    map.Init(1260, 800, "Game Map");
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//        window.clear();  // Effacer l'écran
//
//        // Mettre à jour les objets
//        for (auto& [id, player] : players) {
//            sf::Sprite& sprite = player->GetSprite()->GetSprite();
//            sprite.setPosition(player->GetPosition().GetX(), player->GetPosition().GetY());
//            window.draw(sprite);
//        }
//
//        sf::Sprite obstacleSfSprite = obstacle.GetSfSprite();
//        obstacleSfSprite.setPosition(positionObstacle.GetX(), positionObstacle.GetY());
//        window.draw(obstacleSfSprite);
//
//        window.display();  // Afficher la scène
//
//        map.Draw(window);  // Dessiner la map
//    }
//
//    return 0;
//}







#include "pch.h"
#include "HostGameManager.h"

int main() {
    GameManager gameManager;

    if (gameManager.Init() != 0) {
        std::cerr << "Erreur lors de l'initialisation du jeu." << std::endl;
        return -1;
    }

    gameManager.GameLoop();

    gameManager.Uninit();

    return 0;
}
