#ifndef GAMAMANAGER_H__
#define GAMAMANAGER_H__

#include <SFML/Graphics.hpp>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
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

    static DWORD WINAPI StaticServerThreadNetwork(void* pParam);
    static DWORD WINAPI StaticServerThreadGame(void* pParam);

    DWORD WINAPI ServerThreadNetwork(void* pParam);
    DWORD WINAPI ServerThreadGame(void* pParam);

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

    const float windowWidth = 1260.0f;
    const float windowHeight = 800.0f;

    sf::RenderWindow window;
    Map mMap;

    int port = 8080;
    WSAData wsaData;
    SOCKET server_UDP;
    sockaddr_in addr;

    CRITICAL_SECTION criticalSection;

    //sf::Font mFont;
    //sf::Text mScoreText;      // Texte pour afficher le score

private:
    
};

#endif