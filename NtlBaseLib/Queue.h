#ifndef _QUEUE
#define _QUEUE

#pragma once

#include "Base.h"
#include "Mutex.h"
#include <deque>

template <class TYPE>
class Queue
{
public:
	Queue();
	virtual ~Queue() { Clear();	}

	TYPE Pop();
	bool Push(TYPE typeObject, bool Front = false);
	TYPE Peek();
	void Clear();
	DWORD GetMaxUsedSize() { return _MaxUseSize; }
	DWORD GetSize() { return (DWORD)_queue.size(); }
	bool IsEmpty() { return _queue.empty(); }

private:
	std::deque<TYPE> _queue;
	Mutex _mutex;
	DWORD _MaxUseSize;
};

template <class TYPE>
inline Queue<TYPE>::Queue()
{
	_MaxUseSize = 0;
}

template <class TYPE>
inline TYPE Queue<TYPE>::Pop()
{
	TYPE typeObject;

	_mutex.Lock();
	if (false == _queue.empty())
	{
		typeObject = _queue.front();
		_queue.pop_front();
	}
	else
	{
		ZeroMemory(&typeObject, sizeof(typeObject));
	}
	_mutex.Unlock();

	return typeObject;
}

template <class TYPE>
inline bool Queue<TYPE>::Push(TYPE typeObject, bool Front)
{
	_mutex.Lock();

	(Front) ? (_queue.push_front(typeObject)) : (_queue.push_back(typeObject));

	if (GetSize() > _MaxUseSize)
	{
		_MaxUseSize = GetSize();
	}

	_mutex.Unlock();

	return true;
}

template <class TYPE>
inline TYPE Queue<TYPE>::Peek()
{
	TYPE typeObject;

	_mutex.Lock();
	if (false == _queue.empty())
	{
		typeObject = _queue.front();
	}
	else
	{
		ZeroMemory(&typeObject, sizeof(typeObject));
	}
	_mutex.Unlock();

	return typeObject;
}

template <class TYPE>
inline void Queue<TYPE>::Clear()
{
	_mutex.Lock();
	if (false == _queue.empty())
	{
		_queue.clear();
	}
	_mutex.Unlock();
}


#endif
