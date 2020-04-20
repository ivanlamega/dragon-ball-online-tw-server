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
		SendFriendAdd(packet);
		break;
	}
	case UT_FRIEND_DEL_REQ:
	{
		SendFriendDelete(packet);
		break;
	}
	case UT_FRIEND_MOVE_REQ:
	{
		SendFriendMove(packet);
		break;
	}
	case UT_FRIEND_BLACK_ADD_REQ:
	{
		SendFriendBlackAdd(packet);
		break;
	}
	case UT_FRIEND_BLACK_DEL_REQ:
	{
		SendFriendBlackDelete(packet);
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
	/////////////////////////////////////////////
	// Guild Packets///////
	case UT_GUILD_LEAVE_REQ:
	{
		sLog.outError("UT_GUILD_LEAVE_REQ");
		LeaveGuild(packet);
		break;
	}
	case UT_GUILD_CHANGE_NOTICE_REQ:
	{
		sLog.outError("UT_GUILD_CHANGE_NOTICE_REQ");
		UpdateGuildNotice(packet);
		break;
	}
	case UT_GUILD_RESPONSE_INVITATION:
	{
		sLog.outError("UT_GUILD_RESPONSE_INVITATION");
		GuildInviteResponse(packet);
		break; 
	}
	//In dev
	case UT_GUILD_APPOINT_SECOND_MASTER_REQ:
	{
		sLog.outError("UT_GUILD_APPOINT_SECOND_MASTER_REQ");
		GUILD_APPOINT_SECOND_MASTER(packet);
		break;
	}
	case UT_GUILD_CHANGE_GUILD_MASTER_REQ:
	{
		sLog.outError("UT_GUILD_CHANGE_GUILD_MASTER_REQ");
		GUILD_CHANGE_GUILD_MASTER(packet);
		break;
	}
	case UT_GUILD_KICK_OUT_REQ:
	{
		sLog.outError("UT_GUILD_KICK_OUT_REQ");
		GUILD_KICK_OUT(packet);
		break;
	}
	////////////////////////////////////////////
		default:
		{

			//Log every OpCode
			sLog.outError("OpCode received :: %d", header->wOpCode);

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
