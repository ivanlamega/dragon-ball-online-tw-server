#include "stdafx.h"
#include "Event.h"

Event::Event()
	: _Event(INVALID_HANDLE_VALUE)
{
	_Event = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == _Event)
	{
		DWORD rc = GetLastError();
		THROW_THREAD_EXCEPTION(THREAD_ERR_EVENT_CREATE, rc);
	}
}

Event::~Event(void)
{
	if (false == CloseHandle(_Event))
	{
		DWORD rc = GetLastError();
		THROW_THREAD_EXCEPTION(THREAD_ERR_EVENT_DESTROY, rc);
	}

	_Event = INVALID_HANDLE_VALUE;
}

void Event::Reset()
{
	if (false == ResetEvent(_Event))
	{
		DWORD rc = GetLastError();
		THROW_THREAD_EXCEPTION(THREAD_ERR_EVENT_RESET, rc);
	}
}

void Event::Wait()
{
	if (WAIT_FAILED == WaitForSingleObject(_Event, INFINITE))
	{
		DWORD rc = GetLastError();
		THROW_THREAD_EXCEPTION(THREAD_ERR_EVENT_WAIT, rc);
	}
}

int Event::Wait(unsigned int millisecs)
{
	DWORD rc = NO_ERROR;
	DWORD status = WaitForSingleObject(_Event, millisecs);

	if (WAIT_TIMEOUT == status)
	{
		rc = ERROR_TIMEOUT;
	}
	else if (WAIT_FAILED == status)
	{
		rc = GetLastError();
		THROW_THREAD_EXCEPTION(THREAD_ERR_EVENT_WAIT, rc);
	}

	return rc;
}

void Event::Notify()
{
	if (!SetEvent(_Event))
	{
		DWORD rc = GetLastError();
		THROW_THREAD_EXCEPTION(THREAD_ERR_EVENT_NOTIFY, rc);
	}
}