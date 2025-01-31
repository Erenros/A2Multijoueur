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
#include "UIManager.h"
#include "Vector2.h"

#include <iostream>
#include <filesystem>

class GameManager {
public:
    GameManager();
    ~GameManager();

    void ParsePlayerData(const std::string& message, Player& player);

    static DWORD WINAPI StaticClientThreadNetwork(void* pParam);
    static DWORD WINAPI StaticClientThreadCommand(void* pParam);

    DWORD WINAPI ClientThreadNetwork();
    DWORD WINAPI ClientThreadCommand();

    int Init();
    int GameLoop();
    void Uninit();

protected:
    InputManager mInputManager;

    SpriteClass mPlayerSprite;
    SpriteClass mObstacleSprite;
    SpriteClass mMapSprite;

    sf::Texture mObstacleTexture;
    sf::Texture mMapTexture;
    std::string mObstacleTexturePath;

    Obstacle mObstacle;
    Vector2 mPositionObstacle;

    std::map<std::string, Player*> pPlayers;
    std::map<std::string, Obstacle> pObstacles;

    std::string basePath = std::filesystem::current_path().parent_path().parent_path().string();

    std::string mPseudo;

    std::string inputTextTop = "";
    std::string inputTextMid = "";
    std::string inputTextBottom = "";

    sf::Text labelTop;
    sf::Text labelMid;
    sf::Text labelBottom;

    sf::RectangleShape inputAreaTop;
    sf::RectangleShape inputAreaMid;
    sf::RectangleShape inputAreaBottom;

    sf::Text textTop;
    sf::Text textMid;
    sf::Text textBottom;

    sf::Font font;

    sf::RenderWindow window;
    sf::RenderWindow gameWindow;

    bool isInTopArea = false;
    bool isInMidArea = false;
    bool isInBottomArea = false;

    const float windowWidth = 1260.0f;
    const float windowHeight = 800.0f;

    UIManager connectButton;

    bool bRunning = true;
    bool isConnected = false;

    Map mMap;

    int port;
    WSAData wsaData;
    SOCKET socket_client;
    sockaddr_in addrServer;
    const char* ip_Server;

    CRITICAL_SECTION criticalSection;

    HANDLE threadNetwork = nullptr;
    HANDLE threadCommand = nullptr;
};

#endif