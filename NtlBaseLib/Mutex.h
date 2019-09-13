#ifndef _MUTEX
#define _MUTEX

#pragma once

#include "Base.h"

class Mutex
{
public:
	Mutex(DWORD SpinCount = 4000) { ::InitializeCriticalSectionAndSpinCount(&_mutex, SpinCount); }
	virtual ~Mutex() { ::DeleteCriticalSection(&_mutex); }

	void Lock() { ::EnterCriticalSection(&_mutex); }
	void Unlock() { ::LeaveCriticalSection(&_mutex); }
	CRITICAL_SECTION* GetRealMutex() { return &_mutex; }

private:
	CRITICAL_SECTION _mutex;
};

class AutoMutex
{
public:
	AutoMutex(Mutex * pMutex) :_Mutex(pMutex), _IsLocked(false) {}
	virtual ~AutoMutex(void) { Unlock(); }

	void Lock();
	void Unlock();

private:
	Mutex * _Mutex;
	bool _IsLocked;
};

inline void AutoMutex::Lock()
{
	if (!_IsLocked)
	{
		_Mutex->Lock();
		_IsLocked = true;
	}
}

inline void AutoMutex::Unlock()
{
	if (_IsLocked)
	{
		_IsLocked = false;
		_Mutex->Unlock();
	}
}

#endif