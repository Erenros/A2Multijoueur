#ifndef CLIENTGAMAMANAGER_H__
#define CLIENTGAMAMANAGER_H__

#include <SFML/Graphics.hpp>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "ExternLib.lib")
#include "windows.h"
#include <SFML/Network.hpp>

#include "Player.h"
#include "Obstacle.h"
#include "Sprite.h"
#include "Map.h"
#include "InputManager.h"
#include "Vector2.h"

#include <iostream>
#include <filesystem> // Pour gérer les chemins dynamiquement

class GameManager {
public:

    GameManager();

    void ParsePlayerData(const std::string& message, Player& player);

    DWORD WINAPI ClientThreadNetwork(void* pParam);
    DWORD WINAPI ClientThreadCommand(void* pParam);

    int Init();
    int GameLoop();
    void Uninit();

protected:

    InputManager mInputManager;

    SpriteClass mPlayerSprite;
    SpriteClass mObstacleSprite;

    sf::Texture obstacleTexture;
    std::string obstacleTexturePath;

    Obstacle obstacle;
    Vector2 positionObstacle;

    std::map<std::string, Player*> pPlayers;
    std::map<std::string, Obstacle> pObstacles;

    std::string basePath = std::filesystem::current_path().parent_path().parent_path().string();

    std::string mPseudo;
    const float windowWidth = 1260.0f;
    const float windowHeight = 800.0f;

    sf::RenderWindow window;
    Map mMap;

    int port = 8080;
    WSAData wsaData;
    SOCKET socket_client;
    sockaddr_in addrServer;

    CRITICAL_SECTION criticalSection;

    //sf::Font mFont;
    //sf::Text mScoreText;      // Texte pour afficher le score

private:
    struct ClientThreadParams {
        bool* isRunning;
        Player* player;
        InputManager* inputManager;
        std::string* pseudo;
        CRITICAL_SECTION* criticalSection;
    };
};

#endif