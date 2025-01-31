//#ifndef NETWORK_H__
//#define NETWORK_H__
//
//#include "pch.h"
//#include <SFML/Graphics.hpp>
//#include <SFML/Network.hpp>
//
//#include <WinSock2.h>
//#include <ws2tcpip.h>
//#pragma comment(lib, "Ws2_32.lib")
//
//#include <iostream>
//#include <unordered_map>
//#include <map>
//#include <string>
//#include <sstream>
//
//#include "Player.h"
//#include "Projectile.h"
//#include "Obstacle.h"
//
//class Network
//{
//protected:
//
//	int port = 9999;
//	WSAData wsaData;
//	SOCKET server_UDP;
//	sockaddr_in addr;
//
//	CRITICAL_SECTION criticalSection;
//	Player player;
//	Projectile projectile;
//	Obstacle obstacle;
//
//public:
//	Network();
//	~Network();
//
//	DWORD WINAPI ServerThreadNetwork(void* pParam);
//
//	void Init();
//	void Uninit();
//
//	void CreateSock();
//	void CloseSock();
//
//	void SendData(sockaddr_in& to, char* data, int length);
//	int ReceiveData(sockaddr_in& from, char* data, int length);
//
//};
//
//#endif