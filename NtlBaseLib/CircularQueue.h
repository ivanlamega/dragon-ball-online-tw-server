#ifndef _CIRCULARQUEUE
#define _CIRCULARQUEUE

#pragma once

#include "Base.h"

template <class TYPE>
class CircularQueue
{
public:
	CircularQueue() { Init();}
	virtual ~CircularQueue() { Destroy(); }

	bool Create(int QueueSize, int ExtraSize);
	void Destroy();
	bool Realloc(int QueueSize, int ExtraSize) { return Create(QueueSize, ExtraSize); }
	void Clear();
	int	GetQueueSize() { return QUEUE_SIZE; }
	int	GetQueueExtraSize() { return EXTRA_SIZE; }
	int	GetQueueTotalSize() { return GetQueueSize() + GetQueueExtraSize(); }
	int	GetFreeSize() { return GetQueueSize() - GetCurSize(); }
	int	GetLinearFreeSize() { return GetQueueTotalSize() - GetPushPos(); }
	int	GetCurSize();
	int	GetPushAvailableSize();
	int	GetWorkRemainSize();
	int	GetQueueLoopCount() { return _LoopCount; }
	int	GetPushPos() { return _PushPos; }
	int	GetPopPos() { return _PopPos; }
	int	GetWorkPos() { return _WorkPos; }
	TYPE* GetQueuePtr(int Pos);
	TYPE* GetQueuePushPtr() { return GetQueuePtr(GetPushPos()); }
	TYPE* GetQueuePopPtr() { return GetQueuePtr(GetPopPos()); }
	TYPE* GetQueueWorkPtr() { return GetQueuePtr(GetWorkPos()); }
	bool IsFull() { return GetCurSize() == GetQueueSize(); }
	bool IsEmpty() { return 0 == GetCurSize(); }
	bool IncreasePushPos(int Size);
	bool IncreasePopPos(int Size);
	bool IncreaseWorkPos(int Size);

protected:
	void Init();
	TYPE* GetQueueBufferPtr() { return _queueBuffer; }
	TYPE* GetQueueExtraPtr() { return &_queueBuffer[QUEUE_SIZE]; }

private:
	int QUEUE_SIZE;
	int	EXTRA_SIZE;
	int	_PushPos;
	int	_PopPos;
	int	_WorkPos;
	TYPE* _queueBuffer;
	int	_LoopCount;
};

template <class TYPE>
inline void CircularQueue<TYPE>::Init()
{
	_queueBuffer = NULL;
	_LoopCount = 0;
}

template <class TYPE>
inline bool CircularQueue<TYPE>::Create(int QueueSize, int ExtraSize)
{
	if (NULL != _queueBuffer)
	{
		return false;
	}

	QUEUE_SIZE = QueueSize;
	EXTRA_SIZE = ExtraSize;

	_queueBuffer = new TYPE[GetQueueTotalSize()];
	if (NULL == _queueBuffer)
	{
		return false;
	}

	Clear();

	return true;
}

template <class TYPE>
inline void CircularQueue<TYPE>::Destroy()
{
	SAFE_DELETE_ARRAY(_queueBuffer);
}

template <class TYPE>
inline void CircularQueue<TYPE>::Clear()
{
	_PushPos = _PopPos = _WorkPos = 0;

	if (_queueBuffer)
	{
		ZeroMemory(_queueBuffer, sizeof(TYPE) * GetQueueTotalSize());
	}
}

template <class TYPE>
TYPE* CircularQueue<TYPE>::GetQueuePtr(int Pos)
{
	if (Pos >= GetQueueTotalSize())
		return (TYPE*)0;

	return &_queueBuffer[Pos];
}

template <class TYPE>
bool CircularQueue<TYPE>::IncreasePushPos(int Size)
{
	if (GetFreeSize() <= Size)
		return false;

	_PushPos += Size;

	if (_PushPos >= GetQueueSize())
	{
		_PushPos -= GetQueueSize();
		memcpy(GetQueueBufferPtr(), GetQueueExtraPtr(), sizeof(TYPE) * _PushPos);

		_LoopCount++;
	}

	return true;
}

template <class TYPE>
bool CircularQueue<TYPE>::IncreasePopPos(int Size)
{
	_PopPos += Size;

	if (_PopPos >= GetQueueSize())
		_PopPos -= GetQueueSize();

	return true;
}

template <class TYPE>
bool CircularQueue<TYPE>::IncreaseWorkPos(int Size)
{
	_WorkPos += Size;

	if (_WorkPos >= GetQueueSize())
		_WorkPos -= GetQueueSize();

	return true;
}

template <class TYPE>
inline int CircularQueue<TYPE>::GetCurSize()
{
	int RetValue = GetPushPos() - GetPopPos();

	if (RetValue < 0)
		return RetValue + GetQueueSize();

	return RetValue;
}

template <class TYPE>
inline int CircularQueue<TYPE>::GetWorkRemainSize()
{
	int RetValue = GetPushPos() - GetWorkPos();

	if (RetValue < 0)
		return RetValue + GetQueueSize();

	return RetValue;
}

template <class TYPE>
int CircularQueue<TYPE>::GetPushAvailableSize()
{
	int nFreeSize = GetFreeSize();
	int nLinearFreeSize = GetLinearFreeSize();

	return (nLinearFreeSize < nFreeSize) ? nLinearFreeSize : (nFreeSize - 1);
}

#endif