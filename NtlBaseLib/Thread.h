#ifndef _THEREAD_H
#define _THEREAD_H

#pragma once

#include "Base.h"
#include "Event.h"
#include "GameString.h"
#include "Mutex.h"
#include "LinkList.h"

#if !defined(SAFE_DELETE)
#define SAFE_DELETE(p) if(p) { delete p; p = 0; }
#endif

#pragma once
#define WIN32_LEAN_AND_MEAN

class ThreadKey;
class ThreadHelper;

enum THREAD_STATUS
{
	THREAD_NOT_RUNNING = 0,
	THREAD_PREPARING_TO_RUN,
	THREAD_RUNNING,
	THREAD_PAUSED,
	THREAD_DEAD,

	THREAD_MAX_STATUS
};

class RunObject
{
	friend class Thread;
public:
	RunObject()
		:_arg(0), _Owner(0), _IsRunning(true) {}
	virtual ~RunObject() {}

	virtual void Run() {}
	virtual void Close() { _IsRunning = false; }

	void Terminate();
	void* GetArg() const { return _arg; }
	void SetArg(void * arg) { _arg = arg; }
	Thread* GetThread() const { return _Owner; }
	void Wait();
	int Wait(unsigned int millisecs);
	void Exit();
	const char* GetName() const;
	bool IsRunnable() { return _IsRunning; }
	void SetRunnable(bool Running) { _IsRunning = Running; }

private:
	void SetThread(Thread* Owner) { _Owner = Owner; }
	Thread* _Owner;
	bool _IsRunning;

protected:
	void* _arg;
};

class Thread : public LinkObject
{
	friend class ThreadKey;
	friend class ThreadHelper;
	friend class ThreadFactory;
public:
	Thread(RunObject * pRunObject, const char * name = "Unknown Thread", bool AutoDelete = false);
	virtual ~Thread(void);
	void Close();
	void CleanUp();
	void Execute();
	void Init();
	Thread* GetNextThread() const { return (Thread*) this->GetNext(); }
	void Wait();
	int Wait(unsigned int millisecs);
	void Exit();
	void Join();
	void Start();
	const char* GetName() { return _strName.c_str(); }
	RunObject* GetRunObject() { return _RunObject; }
	void SetArg(void *arg) { _RunObject->SetArg(arg); }
	void* GetArg() { return _RunObject->GetArg(); }
	bool IsAutoDelete() { return _IsAutoDelete; }
	bool IsStatus(THREAD_STATUS status) { return status == _status; }
	const char* GetStatusString();
	void SetSignaled(bool Signaled) { _IsSignaled = Signaled; }
	bool IsSignaled() { return _IsSignaled; }
	static void Notify(Thread * pThread);
	static Thread* GetCurrentThread();
	static Thread* GetMainThread() { return _MainThread; }

protected:
	GameString _strName;
	THREAD_STATUS _status;
	HANDLE _hThread;
	unsigned _threadID;
	Event _event;
	bool _IsSignaled;
	bool _IsAutoDelete;
	RunObject* _RunObject;
	static ThreadKey* _ThreadKey;
	static Thread* _MainThread;

private:
	Thread(const Thread &);
	void operator=(const Thread &);
};

class ThreadFactory
{
	friend class Thread;
	friend class ThreadHelper;
	friend class RunObject;
public:
	ThreadFactory();
	virtual ~ThreadFactory();

	static void	Shutdown();
	static void	CloseAll();
	static void	JoinAll();
	static Thread* CreateThread(RunObject * pRunObject, const char * name = "Unnamed Thread", bool AutoDelete = false);

protected:
	static void	Lock() { _Mutex->Lock(); }
	static void	Unlock() { _Mutex->Unlock(); }
	static void	GarbageCollect(bool ShutDown = false);
	static void	SingleGarbageCollect(Thread* GarbageThread);

	static LinkList* _ThreadList;
	static Mutex* _Mutex;
	static bool _IsClosed;
};

inline void RunObject::Wait()
{
	_Owner->Wait();
}

inline void RunObject::Terminate()
{
	Close();

	if (false != GetThread()->IsStatus(THREAD_RUNNING) ||
		false != GetThread()->IsStatus(THREAD_PAUSED) ||
		false != GetThread()->IsStatus(THREAD_DEAD))
	{
		GetThread()->Join();
	}

	ThreadFactory::Lock();
	ThreadFactory::SingleGarbageCollect(GetThread());
	ThreadFactory::Unlock();
}

inline int RunObject::Wait(unsigned int millisecs)
{
	return _Owner->Wait(millisecs);
}

inline void RunObject::Exit()
{
	_Owner->Exit();
}

inline const char * RunObject::GetName() const
{
	return _Owner->GetName();
}

#endif