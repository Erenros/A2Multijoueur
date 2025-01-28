#include "pch.h"
//#include "Thread.h"
//#include <windows.h>
//#include <cassert>
//
//Thread::Thread()
//{
//	mThread = NULL;
//}
//
//Thread::~Thread()
//{
//	assert(mThread == NULL);
//}
//
//void Thread::Init()
//{
//	mThread = NULL;
//}
//
//void Thread::Uninit()
//{
//	CloseThrd();
//	mThread = NULL;
//}
//
//void Thread::CreateThread(LPTHREAD_START_ROUTINE func, LPVOID param)
//{
//	mThread = CreateThread(NULL, 0, func, param, 0, NULL);
//}
//void Thread::CloseThread()
//{
//	CloseHandle(mThread);
//}