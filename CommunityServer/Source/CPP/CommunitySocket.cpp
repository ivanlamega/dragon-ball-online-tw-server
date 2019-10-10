#include <CommunitySocket.h>

#include <Community.h>
#include <CommunitySession.h>
#include <Logger.h>
#include <stdio.h>
#include <cstdio>
#include <Opcodes.h>
#include <Encryptation.h>
#include <mysqlconn_wrapper.h>

#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>

CommunitySocket::CommunitySocket(boost::asio::io_service &service, std::function<void(Socket *)> closeHandler)
	: Socket(service, closeHandler), m_session(nullptr)
{
	m_sessionFinalized = false;
}
void CommunitySocket::OnConnectionDone()
{
	uint8 rawData[] = { 0x06, 0x00, 0x03, 0x00, 0x30, 0x2C, 0x67, 0x4C };

	Write((char*)rawData, sizeof(rawData));
	memset(&rawData, 0, sizeof(rawData));
	sLog.outDebug("Client connected: [%s]", m_address);
}
void CommunitySocket::OnClosed()
{
	sLog.outDebug("Client disconnected: [%s]", m_address);
}
bool CommunitySocket::HandleAuthSession(Packet& packet)
{
	sUT_ENTER_CHAT *req = (sUT_ENTER_CHAT*)packet.GetPacketBuffer();

	sTU_ENTER_CHAT_RES res;
	
	res.wOpCode = TU_ENTER_CHAT_RES;
	res.wPacketSize = sizeof(sTU_ENTER_CHAT_RES) - 2;
	res.wResultCode = CHAT_SUCCESS;
	sLog.outDebug("UT_ENTER_CHAT By AccID: %d", req->accountId);
	CHARACTERID charId = INVALID_CHARACTERID;

	if (!(m_session = new CommunitySession(req->accountId, this, (AccountTypes)sDB.GetIsGameMaster(req->accountId))))
	{
		res.wResultCode = COMMUNITY_FAIL;
		Write((char*)&res, sizeof(sTU_ENTER_CHAT_RES));
		sLog.outError("CommunitySession create failed !.");
		return false;
	}
	if (m_session == NULL)
	{
		res.wResultCode = COMMUNITY_FAIL;
		Write((char*)&res, sizeof(sTU_ENTER_CHAT_RES));
		sLog.outError("Session Is NULL!.");
		return false;
	}
	sql::ResultSet* result = sDB.executes("SELECT CharacterId from characters where isOnline = 1 and AccountID = %d", req->accountId);
	if (result)
	{
		charId = result->getUInt("CharacterId");
	}
	if(charId != INVALID_CHARACTERID)
	{
		if (!m_session->CreatePlayer(charId))
		{
			res.wResultCode = COMMUNITY_FAIL;
			Write((char*)&res, sizeof(sTU_ENTER_CHAT_RES));
			sLog.outError("Player create failed !.");
			return false;
		}
	}
	Write((char*)&res, sizeof(sTU_ENTER_CHAT_RES));

	m_session->SendFriendListInfomation();
	sCommunity.AddSession_(m_session);
	return true;
}
bool CommunitySocket::ProcessIncomingData()
{
	PACKETHEADER packetHeader;
	memcpy(&packetHeader, InPeak(), sizeof(PACKETHEADER));

	/*std::unique_ptr<Packet> pct(new Packet(packetHeader.wPacketLen));
	pct->AttachData((BYTE*)InPeak(), packetHeader.wPacketLen + HEADER_SIZE);*/

	Packet packet(packetHeader.wPacketLen);
	packet.AttachData((BYTE*)InPeak(), packetHeader.wPacketLen + HEADER_SIZE);
	
	PACKETDATA *header = (PACKETDATA*)packet.GetPacketHeader();
	Opcodes opcode = *(Opcodes*)&header->wOpCode;
	opcode = (Opcodes)header->wOpCode;
	ReadSkip(packetHeader.wPacketLen + 2);

	if (packet.IsValidHeader() == false || packet.IsValidPacket() == false)
	{
		sLog.outError("Client: %s have send modifider packet data", m_address);
		packet.Destroy();
		return false;
	}
	if (((opcode <= 0 || opcode >= OPCODE_END) && (packetHeader.wPacketLen <= 0 || packetHeader.wPacketLen > PACKET_MAX_SIZE)))
	{
		sLog.outError("This shouldn't happend");
		/// how handle that ? may happen by flooding input or because real bad data
		packet.Destroy();
		return false;
	}
	switch (opcode)
	{
		case Opcodes::SYS_HANDSHAKE_RES:
		{
			uint8 rawData2[] = { 0x22, 0x00, 0x10, 0x00, 0x49, 0xD1, 0xF1, 0x1C, 0x6D, 0x58, 0xF9, 0xC5, 0x30, 0x26, 0xA4, 0x7B,
				0xB2, 0xD8, 0x2C, 0x86, 0x58, 0x60, 0x7B, 0xDD, 0xF0, 0x77, 0xCF, 0x25, 0x48, 0xB3, 0x65, 0x45,
				0x38, 0x80, 0x14, 0x72 };
			Write((char*)rawData2, sizeof(rawData2));
			memset(&rawData2, 0, sizeof(rawData2));
			break;
		}
		case Opcodes::SYS_ALIVE:
		{
			break;
		}
		case Opcodes::UT_ENTER_CHAT:
		{
			if (m_session)
			{
				sLog.outError("CommunitySocket::ProcessIncomingData: Player send UT_ENTER_CHAT again");
				return false;
			}
			if (HandleAuthSession(packet) == false)
			{
				packet.Destroy();
				return false;
			}
			break;
		}
		case Opcodes::UT_CHAT_USER_ON_CHANNEL_UPDATE_NFY:
		{
			sLog.outDebug("CHAT_USER_ON_CHANNEL_UPDATE_NFY");
			/*sTU_DOJO_SCRAMBLE_INFORM_NFY res;
			res.wOpCode = TU_DOJO_SCRAMBLE_INFORM_NFY;
			res.wPacketSize = sizeof(sTU_DOJO_SCRAMBLE_INFORM_NFY) - 2;
			res.dojoTblidx = 3;
			res.byState = 1;
			Write((char*)&res, sizeof(sTU_DOJO_SCRAMBLE_INFORM_NFY));*/
			break;
		}
		default:
		{
			if (!m_session)
			{
				sLog.outError("Unauthorized packet [%u] from: %s", opcode, m_address);
				packet.Destroy();
				return false;
			}
			//m_session->QueuePacket(std::move(pct));
			m_session->PacketParser(packet);
			packet.Destroy();
			break;
		}
	}
	return true;
}
