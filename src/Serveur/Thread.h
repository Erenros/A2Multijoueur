#ifndef TREAD_H__
#define TREAD_H__

class Thread
{
private:

	HANDLE mThread;

public:

	Thread();
	~Thread();

	void Init();
	void Uninit();

	void CreateThread(LPTHREAD_START_ROUTINE func, LPVOID param);
	void CloseThread();
};

#endif