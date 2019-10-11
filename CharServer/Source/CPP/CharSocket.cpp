#include <CharSocket.h>
#include <Logger.h>
#include <stdio.h>
#include <cstdio>
#include <Opcodes.h>
#include <Encryptation.h>
#include <mysqlconn_wrapper.h>

CharSocket::CharSocket(boost::asio::io_service &service, std::function<void(Socket *)> closeHandler)
	: Socket(service, closeHandler)
{
	AccountID = -1;
}
void CharSocket::OnConnectionDone()
{
	uint8 rawData[] = { 0x06, 0x00, 0x03, 0x00, 0x30, 0x2C, 0x67, 0x4C };

	Write((char*)rawData, sizeof(rawData));
	memset(&rawData, 0, sizeof(rawData));
	sLog.outDebug("Client connected: [%s]", m_address);
}
void CharSocket::OnClosed()
{
	sLog.outDebug("Client disconnected: [%s]", m_address);
	if (AccountID != -1)
		sDB.UpdateAccountOnline(AccountID, 0); // SET OUR USER OFFLINE IN DB
}

bool CharSocket::ProcessIncomingData()
{
	while (ReadLengthRemaining() > 0)
	{
		size_t sizeInc = ReadLengthRemaining();
		Packet *pk = new Packet();
		pk->AttachData((BYTE*)InPeak(), sizeInc);
		PACKETDATA *header = (PACKETDATA*)InPeak();
		if ((pk->GetHeaderSize() < 4) || (pk->GetHeaderSize() > PACKET_MAX_SIZE))
		{
			sLog.outError("AuthSocket::ProcessIncomingData: client sent malformed packet size = %u", pk->GetHeaderSize());
			errno = EINVAL;
			return false;
		}
		sLog.outDebug("Received opcode: [%u] from: [%s]", header->wOpCode, m_address);
		/*
		///		 DECRYPT PACKET HERE ????		\\\
		*/
		//sLog.outPacketDebugger(&packet);
		bool process = false;
		if (header->wOpCode == 4)
		{
			uint8 rawData2[] = { 0x22, 0x00, 0x10, 0x00, 0x49, 0xD1, 0xF1, 0x1C, 0x6D, 0x58, 0xF9, 0xC5, 0x30, 0x26, 0xA4, 0x7B,
				0xB2, 0xD8, 0x2C, 0x86, 0x58, 0x60, 0x7B, 0xDD, 0xF0, 0x77, 0xCF, 0x25, 0x48, 0xB3, 0x65, 0x45,
				0x38, 0x80, 0x14, 0x72 };
			Write((char*)rawData2, sizeof(rawData2));
			memset(&rawData2, 0, sizeof(rawData2));
			process = true;
		}
		else if (header->wOpCode == Opcodes::SYS_ALIVE)
		{
			process = true;
		}
		else if (header->wOpCode >= Opcodes::UC_DUMMY && header->wOpCode <= Opcodes::UC_CHAR_SERVERLIST_REQ)
		{
			process = _ProcessCharPacket(*pk, header->wOpCode);
		}
		else
		{
			sLog.outError("Packet_[%u] Unknown /n Size: [%u] Data Dump: [%u]", header->wOpCode, header->wSize, pk->GetPacketData());
			ReadSkip(sizeInc);
			delete pk;
			return false;
		}
		/// if we reach here, it means that a valid opcode was found and the handler completed successfully
		ReadSkip(sizeInc);
		delete pk;
		return process;
	}
	return true;
}