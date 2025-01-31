#ifndef TIMER_H__
#define TIMER_H__

#include <Windows.h>
#define FIXED_DT 0.01667f

class Timer
{
	float mDeltaTime;
	float mAccumulatedDt = 0.f;
	bool mRunning = false;
	DWORD mSysTime = 0;
	float mElapsedTime = 0.0f;

private:
	bool UpdateTime();
	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }

protected:

public:
	Timer();
	~Timer();

	void StartTimer();
	void StopTimer();
	void ResetTimer();

	float GetDeltaTime() const;
	float GetAccumulatedTime() const;
};

#endif