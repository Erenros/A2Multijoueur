#ifndef NETWORK_H__
#define NETWORK_H__

#include "Thread.h"
#include "CriticalSection.h"

class Network
{
protected:
	SOCKET mSocket;
	Thread mThread;
	CriticalSection mCriticalSection;

public:
	Network();
	virtual ~Network();

	void Init();
	void Uninit();

	void CreateSock();
	void CloseSock();

	void SendData(sockaddr_in& to, char* data, int length);
	int ReceiveData(sockaddr_in& from, char* data, int length);

};

#endif