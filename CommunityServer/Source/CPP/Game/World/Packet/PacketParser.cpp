#include <CommunitySocket.h>
#include <Define.h>
#include <Logger.h>
#include <Opcodes.h>
#include <Packet.h>
#include "CommunitySession.h"
#include <Game\Object\Player.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Npc.h>
#include <Community.h>
#include <Packet\Community\PacketTU.h>
#include <Packet\Community\PacketUT.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <XmlParser2/XmlParser2.h>

//----------------------------------------
//	Parcket parser
//----------------------------------------
void			CommunitySession::PacketParser(Packet& packet)
{
	//std::lock_guard<std::mutex> guard(m_recvQueueLock);

	PACKETDATA *header = (PACKETDATA*)packet.GetPacketHeader();

	switch (header->wOpCode)
	{
	case UT_CHAT_MESSAGE_SAY:
	{
		SendLocalChat(packet);
		break;
	}
	case UT_CHAT_MESSAGE_SHOUT:
	{
		SendShoutChat(packet);
		break;
	}
	case UT_CHAT_MESSAGE_TRADE:
	{
		SendTradeChat(packet);
		break;
	}
	case UT_CHAT_MESSAGE_FIND_PARTY:
	{
		SendLFGChat(packet);
		break;
	}
	case UT_FRIEND_ADD_REQ:
	{
		break;
	}
	case UT_HLS_SLOT_MACHINE_INFO_REQ:
	{
		SendHlsSlotMachineInfo(packet);
		break;
	}
	case UT_HLS_SLOT_MACHINE_EXTRACT_REQ:
	{
		SendHlsSlotMachineExtract(packet);
		break;
	}
	case UT_HLS_SLOT_MACHINE_WINNER_INFO_REQ:
	{
		SendHlsSlotMachineWinnerInfo(packet);
		break;
	}
		default:
		{
			try
			{
				sLog.outPacketFile(&packet);
//				sLog.outDebug("Unhandle packet received: %s", header->wOpCode);
			}
			catch (exception* e)
			{
				printf(e->what());
			}
			break;
		}
	}
}
