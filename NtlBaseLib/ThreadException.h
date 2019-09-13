#ifndef _THREADEXCEPTION
#define _THREADEXCEPTION

#pragma once

#include "Base.h"
#include "Exception.h"

enum THREAD_ERROR
{
	THREAD_ERR_UNEXPECTED = 1,
	THREAD_ERR_MUTEX_CREATE,
	THREAD_ERR_MUTEX_LOCK,
	THREAD_ERR_MUTEX_UNLOCK,
	THREAD_ERR_EVENT_CREATE,
	THREAD_ERR_EVENT_DESTROY,
	THREAD_ERR_EVENT_RESET,
	THREAD_ERR_EVENT_WAIT,
	THREAD_ERR_EVENT_NOTIFY,
	THREAD_ERR_MONITOR_STATE,
	THREAD_ERR_MONITOR_DESTROYED,
	THREAD_ERR_MONITOR_BUSY,
	THREAD_ERR_THREAD_CREATE,
	THREAD_ERR_THREAD_JOIN,
	THREAD_ERR_TLS_KEY_CREATE,
	THREAD_ERR_TLS_SET_VALUE,

	MAX_THREAD_ERROR
};

#define THROW_THREAD_EXCEPTION(c, rc) throw ThreadException(__FILE__, __LINE__, __FUNCTION__, c, rc)

class ThreadException : public Exception
{
public:
	ThreadException(const char *filename, int line, const char * func, int category, int errorCode)
		:Exception(filename, line, func, ""),_category(category), _errorCode(errorCode)
	{
	}
	virtual ~ThreadException(void) {}

protected:
	int _category;
	int _errorCode;
};

#endif