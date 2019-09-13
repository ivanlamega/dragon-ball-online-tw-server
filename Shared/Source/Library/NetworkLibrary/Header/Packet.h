#ifndef __PACKET__H
#define __PACKET__H

#include <Define.h>
#include <stdlib.h>
#include <Opcodes.h>

typedef struct PACKETHEADER
{
	WORD		wPacketLen : 15;
	WORD		bEncrypt : 1;
	BYTE		bySequence;
	BYTE		byChecksum;
} PACKETHEADER, *LPPACKETHEADER;

typedef struct PACKETDATA
{
	PACKETDATA() {}
	PACKETDATA(WORD opcode) :wOpCode(opcode) {}
	BYTE		wSize;
	WORD		wOpCode;
} PACKETDATA, *LPPACKETDATA;

const int HEADER_SIZE = sizeof(PACKETHEADER);
const int PACKET_LIMIT_SIZE = 0x7FFF;
const BYTE PACKET_MAX_SEQUENCE = 0xFF;
const int PACKET_MAX_SIZE = 4096;

class Packet
{
public:
	Packet();
	Packet(Packet& rhs);
	Packet(BYTE * pAttachBuffer);
	Packet(BYTE * pPacketData, WORD wPacketBodySize);
	Packet(WORD wPacketBodySize);
	~Packet();
	void Init();
	void Destroy();
	void Attach(BYTE * pPacketBuffer);
	void AttachData(BYTE * pPacketBuffer, WORD wBufferUsedSize);
	void InitUseInternalBuffer(BYTE * pPacketBuffer, WORD wBufferUsedSize);
	void InitUseExternalBuffer(BYTE * pPacketBuffer, WORD wBufferUsedSize);
	void CopyToBuffer(BYTE * pDestBuffer, int nSize);
	void CopyFromBuffer(BYTE * pSrcBuffer, int nSize);
	void Realloc(int nSize);
	bool IsValidHeader();
	bool IsValidPacket();
	void ReadData(void * pDest, int nSize);
	void WriteData(void * pSrc, int nSize);
	void SetPacket(BYTE * pPacketData, WORD wPacketBodySize);
	void SetPacketLen(WORD wPacketLen);

	void SetUsedSize(WORD wSize) { mDataSize = wSize; }
	void SetPacketLenToUsedSize() { mDataSize = GetPacketLen(); }
	void AdjustPacketLen(WORD wPacketLen) { SetPacketLen(wPacketLen); SetPacketLenToUsedSize(); }
	virtual int	GetHeaderSize() { return HEADER_SIZE; }
	BYTE* GetPacketBuffer() { return mBufferPtr; }
	LPPACKETHEADER GetPacketHeader() { return	pHeader; }
	BYTE* GetPacketData() { return pData; }
	WORD GetPacketLen() { return (WORD)GetHeaderSize() + GetPacketDataSize(); }
	virtual WORD GetPacketDataSize() { return pHeader->wPacketLen; }
	WORD GetUsedSize() { return mDataSize; }

	Packet& operator =(Packet & rhs);
	Packet& operator <<(Packet& rhs);
	Packet& operator >> (Packet& rhs);
	Packet& operator <<(LPTSTR arg);
	Packet& operator >> (LPTSTR arg);
	Packet& operator <<(bool arg);
	Packet& operator >> (bool& arg);
	Packet& operator <<(int arg);
	Packet& operator >> (int& arg);
	Packet& operator <<(long arg);
	Packet& operator >> (long& arg);
	Packet& operator <<(DWORD arg);
	Packet& operator >> (DWORD& arg);

private:
	LPPACKETHEADER pHeader;
	BYTE* mAllocBuffer;
	BYTE* mBufferPtr;
	WORD mDataSize;
	BYTE* pData;
	BYTE* pDataWritePos;
	BYTE* pDataReadPos;
	BYTE* pEndPos;
};

#endif // !__PACKET__H
