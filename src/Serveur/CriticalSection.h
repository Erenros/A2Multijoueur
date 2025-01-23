#ifndef CRITICALSECTION_H__
#define CRITICALSECTION_H__

class CriticalSection
{
private:

	CRITICAL_SECTION mCriticalSection;

public:
	CriticalSection();
	~CriticalSection();

	void Init();
	void Uninit();

	void Enter();
	void Wait();
	void Leave();
	void Delete();
};

#endif