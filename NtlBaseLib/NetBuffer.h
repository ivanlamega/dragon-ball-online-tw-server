#ifndef _NETBUFFER
#define _NETBUFFER

#pragma once

#include "Base.h"
#include "Packet.h"
#include "Encoder.h"
#include "CircularQueue.h"
#include "Queue.h"

const unsigned int	DEF_PACKET_MAX_COUNT = 100;

class NetBuffer : public CircularQueue<BYTE>
{
public:
	NetBuffer()
		:_MaxPacketSize(PACKET_MAX_SIZE) {}

	bool Create(int PacketCapacity = DEF_PACKET_MAX_COUNT, int MaxPacketSize = PACKET_MAX_SIZE)
	{
		if (false == CircularQueue<BYTE>::Create(MaxPacketSize * PacketCapacity, MaxPacketSize))
		{
			return false;
		}
		_MaxPacketSize = MaxPacketSize;

		return true;
	}

	bool Resize(int PacketCapacity = DEF_PACKET_MAX_COUNT, int MaxPacketSize = PACKET_MAX_SIZE)
	{
		if (false == CircularQueue<BYTE>::Realloc(MaxPacketSize * PacketCapacity, MaxPacketSize))
		{
			return false;
		}
		_MaxPacketSize = MaxPacketSize;

		return true;
	}

	BYTE* InGetQueueBufferPtr() { return GetQueueBufferPtr(); }

	BYTE* InGetQueueExtraPtr() { return GetQueueExtraPtr(); }

	DWORD GetMaxPacketCount() { return GetQueueSize() / _MaxPacketSize; }

	int GetMaxPacketSize() { return _MaxPacketSize; }

private:
	int	_MaxPacketSize;
};

class NetQueue : public Queue<Packet*>
{
public:
	NetQueue() :_MaxCount(0) {}
	virtual ~NetQueue() { Destroy(); }

	void Destroy()
	{
		Packet* pPacket = PopPacket();
		while (pPacket)
		{
			SAFE_DELETE(pPacket);

			pPacket = PopPacket();
		}
	}

	bool PushPacket(Packet* pPacket)
	{
		if (false == Queue<Packet*>::Push(pPacket))
		{
			return false;
		}

		int Size = GetSize();
		if (Size > _MaxCount)
		{
			_MaxCount = Size;
		}

		return true;
	}


	Packet* PeekPacket()
	{
		return Queue<Packet*>::Peek();
	}

	Packet* PopPacket()
	{
		return Queue<Packet*>::Pop();
	}


private:
	int	_MaxCount;
};

#endif