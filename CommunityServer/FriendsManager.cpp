#include <CommunitySocket.h>
#include <Logger.h>
#include <stdio.h>
#include <cstdio>
#include <Opcodes.h>
#include <Encryptation.h>
#include <mysqlconn_wrapper.h>
#include <XmlParser.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Packet.h>
#include "CommunitySession.h"
#include "Community.h"
#include "NtlStringHandler.h"
#include "source\Header\Game\Object\Player.h"

void CommunitySession::SendFriendAdd(Packet packet)
{
	sUT_FRIEND_ADD_REQ * req = (sUT_FRIEND_ADD_REQ*)packet.GetPacketBuffer();

	sTU_FRIEND_ADD_RES res;

	res.wPacketSize = (sizeof sTU_FRIEND_ADD_RES) - 2;
	res.wOpCode = TU_FRIEND_ADD_RES;
	wcscpy_s(res.wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, req->wchName);
	res.wResultCode = GAME_SUCCESS;
	res.targetID = 10000;

	SendPacket((char*)&res, sizeof sTU_FRIEND_ADD_RES);
}