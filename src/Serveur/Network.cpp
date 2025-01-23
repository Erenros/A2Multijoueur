#include "pch.h"
//#include "Network.h"
//
//Network::Network()
//{
//	mSocket = NULL;
//	mThread = Thread();
//	mCriticalSection = CriticalSection();
//}
//
//Network::~Network()
//{
//	assert(mSocket == NULL);
//}
//
//void Network::Init()
//{
//	WSADATA wsaData;
//	WSAStartup(MAKEWORD(2, 2), &wsaData);
//
//}
//
//void Network::Uninit()
//{
//	CloseSock();
//	WSACleanup();
//
//	mSocket = NULL;
//	mThread.Uninit();
//	mCriticalSection.Uninit();
//
//}
//
//void Network::CreateSock()
//{
//	mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//}
//
//void Network::CloseSock()
//{
//	closesocket(mSocket);
//}
//
//void Network::SendData(sockaddr_in& to, char* data, int length)
//{
//	sendto(mSocket, data, length, 0, (sockaddr*)&to, sizeof(to));
//}
//
//int Network::ReceiveData(sockaddr_in& from, char* data, int length)
//{
//	int size = sizeof(from);
//	return recvfrom(mSocket, data, length, 0, (sockaddr*)&from, &size);
//
//}