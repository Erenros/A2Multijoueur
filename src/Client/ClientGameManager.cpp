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

    while (*isRunning) {
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
    bool running = *(params->isRunning);
    InputManager* inputManager = params->inputManager;
    std::string pseudo = *(params->pseudo);

    while (running) {
        for (const auto& key : { 'Z', 'Q', 'S', 'D', 'I', 'J', 'K', 'L' }) {
            KeyState state = inputManager->getKeyState(key);  // Utilisation du pointeur inputManager

            // Envoi au serveur en fonction de l'état
            if (state == Push || state == Down) {
                std::string command;
                command = "InGame, Pseudo: ";
                command += pseudo;
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

}

int GameManager::GameLoop()
{

}

void GameManager::Uninit()
{

}
