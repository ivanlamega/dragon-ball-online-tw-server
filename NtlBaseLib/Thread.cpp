#include "stdafx.h"
#include "Thread.h"

class ThreadKey
{
public:
	ThreadKey()
	{
		_Key = ::TlsAlloc();
		if (TLS_OUT_OF_INDEXES == _Key) THROW_THREAD_EXCEPTION(THREAD_ERR_TLS_KEY_CREATE, GetLastError());
	}
	~ThreadKey()
	{
		if (TLS_OUT_OF_INDEXES != _Key)
		{
			::TlsFree(_Key);
			_Key = TLS_OUT_OF_INDEXES;
		}
	}
	DWORD GetKey() { return _Key; }

private:
	DWORD _Key;
};

class MainRun : public RunObject
{
public:
	void Run() {};
};

class MainThread : public Thread
{
public:
	MainThread() : Thread(new MainRun, "MainThread", true)
	{
		_threadID = ::GetCurrentThreadId();
		Init();
	}
};

class ThreadHelper
{
public:
	ThreadHelper()
	{
		Thread::_ThreadKey = new ThreadKey;
		ThreadFactory::_Mutex = new Mutex;
		ThreadFactory::_ThreadList = new LinkList;
		Thread::_MainThread = new MainThread;
	}

	virtual ~ThreadHelper()
	{
		ThreadFactory::Shutdown();
		SAFE_DELETE(Thread::_MainThread);
		SAFE_DELETE(ThreadFactory::_Mutex);
		SAFE_DELETE(ThreadFactory::_ThreadList);
		SAFE_DELETE(Thread::_ThreadKey);
	}
};

char* thread_status_string[THREAD_MAX_STATUS] =
{
	"THREAD_NOT_RUNNING",
	"THREAD_PREPARING_TO_RUN",
	"THREAD_RUNNING",
	"THREAD_PAUSED",
	"THREAD_DEAD",
};

const char* Thread::GetStatusString()
{
	if (_status >= THREAD_MAX_STATUS)
		return "Unknown Status";
	return thread_status_string[_status];
}

// START STATIC FUNCTIONS/DECLARATIOBS
static unsigned __stdcall ThreadMain(void * arg)
{
	Thread* pThread = (Thread*)arg;
	pThread->Execute();
	return 0;
}
ThreadHelper threadHelper;
ThreadKey* Thread::_ThreadKey = 0;
Thread* Thread::_MainThread = 0;
LinkList* ThreadFactory::_ThreadList = 0;
Mutex* ThreadFactory::_Mutex = 0;
bool ThreadFactory::_IsClosed = false;
// END STATIC FUNCTIONS/DECLARATIOBS

void Thread::Init()
{
	ThreadFactory::Lock();

	_status = THREAD_RUNNING;

	ThreadFactory::Unlock();

	if (!TlsSetValue(_ThreadKey->GetKey(), (LPVOID) this))
	{
		THROW_THREAD_EXCEPTION(THREAD_ERR_TLS_SET_VALUE, GetLastError());
	}
}

void Thread::Close()
{
	if (_RunObject)
	{
		_RunObject->Close();
	}
}

void Thread::CleanUp()
{
	ThreadFactory::Lock();

	_status = THREAD_DEAD;

	ThreadFactory::Unlock();
}

void Thread::Execute()
{
	Init();

	try
	{
		_RunObject->Run();
	}
	catch (ThreadException e)
	{
		e.Dump();
	}
	catch (...)
	{
	}

	CleanUp();
}

void Thread::Start()
{
	_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadMain, this, 0, &_threadID);

	if (!_hThread)
	{
		THROW_THREAD_EXCEPTION(THREAD_ERR_THREAD_CREATE, GetLastError());
	}
}

void Thread::Exit()
{
	CleanUp();
	_endthreadex(0);
}

void Thread::Wait()
{
	_event.Wait();
}

int Thread::Wait(unsigned int millisecs)
{
	int rc = _event.Wait(millisecs);
	return rc;
}

void Thread::Notify(Thread * pThread)
{
	pThread->_event.Notify();
}

void Thread::Join()
{
	int rc = ::WaitForSingleObject(_hThread, INFINITE);
	if (WAIT_FAILED == rc)
	{
		THROW_THREAD_EXCEPTION(THREAD_ERR_THREAD_JOIN, GetLastError());
	}
	else
	{
		::CloseHandle(_hThread);
	}

	ThreadFactory::Lock();

	_status = THREAD_NOT_RUNNING;

	ThreadFactory::Unlock();
}

Thread::Thread(RunObject * pRunObject, const char * name, bool AutoDelete)
{
	_status = THREAD_NOT_RUNNING;

	_IsAutoDelete = AutoDelete;
	_IsSignaled = false;
	_strName = name;

	_RunObject = pRunObject;

	_RunObject->SetThread(this);

	_status = THREAD_PREPARING_TO_RUN;
}

Thread::~Thread()
{
	if (THREAD_NOT_RUNNING != _status && this != Thread::_MainThread) {}

	if (_IsAutoDelete)
	{
		SAFE_DELETE(_RunObject);
	}
}

Thread * Thread::GetCurrentThread()
{
	return (Thread*)TlsGetValue(_ThreadKey->GetKey());
}

ThreadFactory::ThreadFactory()
{
}

ThreadFactory::~ThreadFactory()
{
}

void ThreadFactory::GarbageCollect(bool ShutDown)
{
	Thread * pThread = (Thread*)_ThreadList->GetFirst();
	while (pThread)
	{
		if (pThread->IsAutoDelete() &&
			(ShutDown && !pThread->IsStatus(THREAD_NOT_RUNNING) ||
			!ShutDown && pThread->IsStatus(THREAD_DEAD)))
		{
			Unlock();

			pThread->Join();

			Lock();

			pThread = (Thread*)_ThreadList->GetFirst();
			continue;
		}
		else
		{
			pThread = (Thread*)pThread->GetNext();
		}
	}

	pThread = (Thread*)_ThreadList->GetFirst();
	while (pThread)
	{
		Thread* pNext = (Thread*)pThread->GetNext();
		if (pThread->IsStatus(THREAD_NOT_RUNNING))
		{
			_ThreadList->Remove(pThread);
			SAFE_DELETE(pThread);
		}

		pThread = pNext;
	}
}

void ThreadFactory::SingleGarbageCollect(Thread* GarbageThread)
{
	Thread* pThread = (Thread*)(_ThreadList->GetFirst());
	while (NULL != pThread)
	{
		if (GarbageThread == pThread)
		{
			if (false != pThread->IsStatus(THREAD_NOT_RUNNING) ||
				false != pThread->IsStatus(THREAD_PREPARING_TO_RUN))
			{
				_ThreadList->Remove(pThread);
				SAFE_DELETE(pThread);
			}

			return;
		}

		pThread = (Thread*)pThread->GetNext();
	}
}

Thread* ThreadFactory::CreateThread(RunObject* pRunObject, const char * name, bool AutoDelete)
{
	Lock();

	GarbageCollect();

	Thread * pThread = new Thread(pRunObject, name, AutoDelete);
	if (NULL == pThread)
	{
		printf("\"new Thread( pRunObject, name, AutoDelete )\" failed.");
		return NULL;
	}

	_ThreadList->Append(pThread);

	Unlock();

	return pThread;
}

void ThreadFactory::Shutdown()
{
	Lock();

	if (false == _IsClosed)
	{
		_IsClosed = true;

		Thread * pThread = (Thread*)_ThreadList->GetFirst();
		while (pThread)
		{
			Unlock();

			pThread->Close();

			Lock();

			pThread = (Thread*)pThread->GetNext();
		}
	}

	GarbageCollect(true);

	Unlock();
}

void ThreadFactory::CloseAll()
{
	Lock();

	if (false == _IsClosed)
	{
		_IsClosed = true;

		Thread * pThread = (Thread*)_ThreadList->GetFirst();
		while (pThread)
		{
			Unlock();

			pThread->Close();

			Lock();

			pThread = (Thread*)pThread->GetNext();
		}
	}

	Unlock();
}

void ThreadFactory::JoinAll()
{
	Lock();

	Thread * pThread = (Thread*)_ThreadList->GetFirst();
	while (pThread)
	{
		Unlock();

		pThread->Join();

		Lock();

		pThread = (Thread*)pThread->GetNext();
	}

	Unlock();
}