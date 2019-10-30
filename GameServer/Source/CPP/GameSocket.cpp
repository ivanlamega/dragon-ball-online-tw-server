#include <GameSocket.h>

#include <World.h>
#include <WorldSession.h>
#include <Logger.h>
#include <stdio.h>
#include <cstdio>
#include <Opcodes.h>
#include <Encryptation.h>
#include <mysqlconn_wrapper.h>

#include <Packet\Game\PacketUG.h>
#include <Packet\Game\PacketGU.h>

#include <XmlParser2/XmlParser2.h>

GameSocket::GameSocket(boost::asio::io_service &service, std::function<void(Socket *)> closeHandler)
	: Socket(service, closeHandler), m_session(nullptr)
{
	m_sessionFinalized = false;
}
void GameSocket::OnConnectionDone()
{
	uint8 rawData[] = { 0x06, 0x00, 0x03, 0x00, 0x30, 0x2C, 0x67, 0x4C };

	Write((char*)rawData, sizeof(rawData));
	memset(&rawData, 0, sizeof(rawData));
	sLog.outDebug("Client connected: [%s]", m_address);
}
void GameSocket::OnClosed()
{
	sLog.outDebug("Client disconnected: [%s]", m_address);
}
bool GameSocket::HandleAuthSession(Packet& packet)
{
	sUG_GAME_ENTER_REQ *req = (sUG_GAME_ENTER_REQ*)packet.GetPacketData();
	sGU_GAME_ENTER_RES res;

	sql::ResultSet* result = sDB.executes("UPDATE characters SET isOnline = 1 AND IsTutorialDone = 1 WHERE CharacterID = '%d';" , req->charId);
	
	if (result != NULL)
		delete result;
	//res.bEncrypt = 0;
	res.wOpCode = GU_GAME_ENTER_RES;
	res.wPacketSize = sizeof(sGU_GAME_ENTER_RES) - 2;
	res.wResultCode = GAME_SUCCESS;
	strcpy_s(res.achCommunityServerIP, sizeof(res.achCommunityServerIP), sXmlParser.GetStr("CharServerList.CharServer1", "IP").c_str());
	res.wCommunityServerPort = sXmlParser.GetInt("CharServerList.CharServer1", "Port");
	res.timeDBOEnter = time(NULL);

	if (!(m_session = new WorldSession(req->accountId, this, (AccountTypes)sDB.GetIsGameMaster(req->accountId))))
	{
		res.wResultCode = GAME_FAIL;
		Write((char*)&res, sizeof(sGU_GAME_ENTER_RES));
		sLog.outError("WorldSession create failed !.");
		return false;
	}
	if (m_session == NULL)
	{
		res.wResultCode = GAME_FAIL;
		Write((char*)&res, sizeof(sGU_GAME_ENTER_RES));
		sLog.outError("WorldSession create failed !.");
		return false;
	}
	Write((char*)&res, sizeof(sGU_GAME_ENTER_RES));

	if (!m_session->CreatePlayer(req->charId))
	{
		res.wResultCode = GAME_FAIL;
		Write((char*)&res, sizeof(sGU_GAME_ENTER_RES));
		sLog.outError("Player create failed !.");
		return false;
	}
	sWorld.AddSession_(m_session);

	m_session->SendAvatarCharInfo();
	m_session->SendAvatarSkillInfo();	
	m_session->SendAvatarItemInfo();
	m_session->SendAvatarBuffInfo();
	m_session->SendAvatarHTBInfo();
	//m_session->SendAvatarQuestList(pPacket, app);
	m_session->SendSlotInfo();
	/*m_session->SendBusLocation();*/
	m_session->SendAvatarWarFogInfo();
	m_session->SendPortalInfo();	
	m_session->SendMascotInfo();
	m_session->SendHoiPoiMixInfo();
	m_session->SendAvatarWagguInfo();
	m_session->SendAvatarTitleInfo();
	m_session->SendAvatarInfoEnd();
	
	m_session->SendUpdateSkillPassiveAtribute();
	/* ADD OUR PLAYER TO THE ACCESSOR */
	//sObjectAccessor.AddObject(pCurrChar);
	return true;
}
bool GameSocket::ProcessIncomingData()
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
		case Opcodes::UG_GAME_ENTER_REQ:
		{
			if (m_session)
			{
				sLog.outError("GameSocket::ProcessIncomingData: Player send UG_GAME_ENTER_REQ again");
				return false;
			}
			if (HandleAuthSession(packet) == false)
			{
				packet.Destroy();
				return false;
			}
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
