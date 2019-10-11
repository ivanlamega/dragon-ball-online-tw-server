#ifndef _EVENT
#define _EVENT

#pragma once

#include <process.h>

#include "Base.h"
#include "ThreadException.h"

class Event
{
public:
	Event();
	virtual ~Event(void);
	Event(const Event & ev);
	Event & operator=(const Event &ev);

	void Reset();
	void Notify();
	void Wait();
	int Wait(unsigned int millisecs);

private:
	HANDLE _Event;
};

#endif