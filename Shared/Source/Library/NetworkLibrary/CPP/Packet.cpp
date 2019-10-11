#include <Packet.h>
#include <Logger.h>

Packet::Packet()
{
	Init();
}

Packet::Packet(Packet& rhs)
{
	Init();
	(*this) = rhs;
}

Packet::Packet(BYTE * pAttachBuffer)
{
	Init();
	Attach(pAttachBuffer);
}

Packet::Packet(BYTE * pPacketData, WORD wPacketBodySize)
{
	Init();
	InitUseInternalBuffer(NULL, (WORD)GetHeaderSize() + wPacketBodySize);
	SetPacketLen(wPacketBodySize);
}

Packet::Packet(WORD wPacketBodySize)
{
	Init();
	InitUseInternalBuffer(NULL, (WORD)GetHeaderSize() + wPacketBodySize);
	SetPacketLen(wPacketBodySize);
}

Packet::~Packet()
{
	Destroy();
}

void Packet::Init()
{
	mAllocBuffer = NULL;
	pDataReadPos = NULL;
	pDataWritePos = NULL;
	pEndPos = NULL;
	pData = NULL;
	pHeader = NULL;
	mBufferPtr = NULL;
	mDataSize = 0;
}

void Packet::Destroy()
{
	pDataReadPos = NULL;
	pDataWritePos = NULL;
	pEndPos = NULL;
	pData = NULL;
	pHeader = NULL;
	mBufferPtr = NULL;
	mDataSize = 0;

	if (mAllocBuffer != nullptr)
		free(mAllocBuffer);
	mAllocBuffer = NULL;
}

void Packet::Attach(BYTE * pPacketBuffer)
{
	LPPACKETHEADER pPacketHeader = (LPPACKETHEADER)&pPacketBuffer[0];
	WORD wPacketTotalSize = pPacketHeader->wPacketLen + (WORD)GetHeaderSize();
	InitUseExternalBuffer(pPacketBuffer, wPacketTotalSize);
}

void Packet::AttachData(BYTE * pPacketBuffer, WORD wBufferUsedSize)
{
	InitUseExternalBuffer(pPacketBuffer, wBufferUsedSize);
}

void Packet::InitUseInternalBuffer(BYTE * pPacketBuffer, WORD wBufferUsedSize)
{
	Realloc(wBufferUsedSize);
	mBufferPtr = mAllocBuffer;
	if (mBufferPtr)
	{
		if (pPacketBuffer) 
			memcpy(mBufferPtr, pPacketBuffer, wBufferUsedSize);
		pHeader = (LPPACKETHEADER)&mBufferPtr[0];
		pData = (BYTE*)&mBufferPtr[GetHeaderSize()];
		pEndPos = (wBufferUsedSize >= 1) ? &mBufferPtr[wBufferUsedSize - 1] : mBufferPtr;
		pDataReadPos = pDataWritePos = pData;
		mDataSize = wBufferUsedSize;
	}
}

void Packet::InitUseExternalBuffer(BYTE * pPacketBuffer, WORD wBufferUsedSize)
{
	mBufferPtr = pPacketBuffer;
	pHeader = (LPPACKETHEADER)&mBufferPtr[0];
	pData = (BYTE*)&mBufferPtr[GetHeaderSize()];
	pEndPos = (wBufferUsedSize >= 1) ? &mBufferPtr[wBufferUsedSize - 1] : mBufferPtr;
	pDataReadPos = pDataWritePos = pData;
	mDataSize = wBufferUsedSize;
}

void Packet::Realloc(int nSize)
{
	if (mAllocBuffer != nullptr)
		free(mAllocBuffer);
	mAllocBuffer = (BYTE*)calloc(nSize, sizeof(BYTE));
	memset(mAllocBuffer, 0, nSize);
}

void Packet::CopyToBuffer(BYTE * pDestBuffer, int nSize)
{
	if (NULL == mBufferPtr)	return;
	memcpy(pDestBuffer, mBufferPtr, nSize);
}

void Packet::CopyFromBuffer(BYTE * pSrcBuffer, int nSize)
{
	InitUseInternalBuffer(pSrcBuffer, (BYTE)nSize);
}

bool Packet::IsValidHeader()
{
	if (NULL == mBufferPtr)
	{
		sLog.outError("Packet::IsValidHeader(): NULL == mBufferPtr");
		return false;
	}
	if (GetUsedSize() < GetHeaderSize())
	{
		sLog.outError("Packet::IsValidHeader(): GetUsedSize([%d]) <  GetHeaderSize([%d])", GetUsedSize(), GetHeaderSize());
		return false;
	}
	return true;
}

bool Packet::IsValidPacket()
{
	if (NULL == mBufferPtr)
	{
		sLog.outError("Packet::IsValidPacket(): NULL == mBufferPtr");
		return false;
	}
	if (false == IsValidHeader())
	{
		sLog.outError("Packet::IsValidPacket(): false == IsValidHeader()");
		return false;
	}
	if (GetUsedSize() < GetPacketLen())
	{
		sLog.outError("Packet::IsValidPacket(): GetUsedSize([%d]) < GetPacketLen([%d])", GetUsedSize(), GetPacketLen());
		return false;
	}
	return true;
}

void Packet::ReadData(void * pDest, int nSize)
{
	if (NULL == mBufferPtr) return;
	if (pDataReadPos + nSize > pEndPos ||
		pDataReadPos + nSize > pData + GetPacketDataSize())
	{
		return;
	}
	memcpy(pDest, pDataReadPos, nSize);
	pDataReadPos += nSize;
}

void Packet::WriteData(void * pSrc, int nSize)
{
	if (NULL == mBufferPtr) return;
	if (pDataWritePos + nSize > pEndPos)
	{
		return;
	}
	memcpy(pDataWritePos, pSrc, nSize);
	pDataWritePos += nSize;
	mDataSize = mDataSize + (WORD)nSize;
	SetPacketLen(GetPacketLen() + (WORD)nSize);
}
void Packet::SetPacket(BYTE * pPacketData, WORD wPacketBodySize)
{
	if (NULL == mBufferPtr) return;
	if (wPacketBodySize > GetUsedSize() - GetHeaderSize())
	{
		return;
	}

	SetPacketLen(wPacketBodySize);
	memcpy(pData, pPacketData, wPacketBodySize);

	pDataWritePos = pData + wPacketBodySize;
	mDataSize = wPacketBodySize + (WORD)GetHeaderSize();
}

void Packet::SetPacketLen(WORD wPacketLen)
{
	if (wPacketLen > PACKET_LIMIT_SIZE)
	{
		pHeader->wPacketLen = PACKET_LIMIT_SIZE;
		return;
	}
	pHeader->wPacketLen = wPacketLen;
}

Packet& Packet::operator =(Packet & rhs)
{
	InitUseInternalBuffer(rhs.mBufferPtr, rhs.GetUsedSize());

	size_t wReadPos = rhs.pDataReadPos - rhs.pData;
	size_t wWritePos = rhs.pDataWritePos - rhs.pData;

	pDataReadPos = pData + wReadPos;
	pDataWritePos = pData + wWritePos;

	return *this;
}

Packet& Packet::operator <<(Packet& rhs)
{
	*this = rhs;
	return *this;
}

Packet& Packet::operator >> (Packet& rhs)
{
	rhs = *this;
	return *this;
}

Packet& Packet::operator <<(LPTSTR arg)
{
	WriteData((void *)arg, (int)strlen((char*)arg));
	return *this;
}

Packet& Packet::operator >> (LPTSTR arg)
{
	ReadData((void*)arg, (int)strlen((char*)(LPTSTR)pDataReadPos));
	return *this;
}

Packet& Packet::operator <<(bool arg)
{
	WriteData(&arg, sizeof(bool));
	return *this;
}

Packet& Packet::operator >> (bool& arg)
{
	ReadData(&arg, sizeof(bool));
	return *this;
}

Packet& Packet::operator <<(int arg)
{
	WriteData(&arg, sizeof(int));
	return *this;
}

Packet& Packet::operator >> (int& arg)
{
	ReadData(&arg, sizeof(int));
	return *this;
}

Packet& Packet::operator <<(long arg)
{
	WriteData(&arg, sizeof(long));
	return *this;
}

Packet& Packet::operator >> (long& arg)
{
	ReadData(&arg, sizeof(long));
	return *this;
}

Packet& Packet::operator <<(DWORD arg)
{
	WriteData(&arg, sizeof(DWORD));
	return *this;
}

Packet& Packet::operator >> (DWORD& arg)
{
	ReadData(&arg, sizeof(DWORD));
	return *this;
}