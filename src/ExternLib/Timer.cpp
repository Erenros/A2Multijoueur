#include "pch.h"
#include "Timer.h"
#pragma comment(lib, "Winmm.lib")

bool Timer::UpdateTime()
{
    if (!mRunning) return false;

    DWORD newSysTime = timeGetTime();
    DWORD elapsedSysTime = newSysTime - mSysTime;

    if (elapsedSysTime < 5) return false;

    mSysTime = newSysTime;
    if (elapsedSysTime > 40) elapsedSysTime = 40;

    mElapsedTime = elapsedSysTime / 1000.0f;
    mDeltaTime = mElapsedTime;
    return true;
}

Timer::Timer() : mDeltaTime(0.0f)
{
}

Timer::~Timer()
{
}

void Timer::StartTimer() {
    if (!mRunning) {
        mRunning = true;
        mSysTime = timeGetTime();
    }
}

void Timer::StopTimer() {
    if (mRunning) {
        UpdateTime();
        mAccumulatedDt += mDeltaTime;
        mRunning = false;
    }
}

void Timer::ResetTimer() {
    mDeltaTime = 0.0f;
    mAccumulatedDt = 0.0f;
    mRunning = false;
    mSysTime = 0;
    mElapsedTime = 0.0f;
}

float Timer::GetDeltaTime() const
{
    return mDeltaTime;
}

float Timer::GetAccumulatedTime() const
{
    return mAccumulatedDt;
}
