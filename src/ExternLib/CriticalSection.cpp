#include "pch.h"
//#include "CriticalSection.h"
//
//CriticalSection::CriticalSection()
//{
//	mCriticalSection = CRITICAL_SECTION();
//}
//
//CriticalSection::~CriticalSection()
//{
//
//}
//
//void CriticalSection::Init()
//{
//	InitializeCriticalSection(&mCriticalSection);
//}
//
//void CriticalSection::Uninit()
//{
//	Delete();
//}
//
//void CriticalSection::Enter()
//{
//	EnterCriticalSection(&mCriticalSection);
//}
//
//void CriticalSection::Wait()
//{
//	WaitForSingleObject(&mCriticalSection, INFINITE);
//}
//
//void CriticalSection::Leave()
//{
//	LeaveCriticalSection(&mCriticalSection);
//}
//
//void CriticalSection::Delete()
//{
//	DeleteCriticalSection(&mCriticalSection);
//}