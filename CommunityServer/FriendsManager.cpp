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
	res.wResultCode = CHAT_SUCCESS;
	res.targetID = (int)req->wchName[0] + (int)req->wchName[1];

	SendPacket((char*)&res, sizeof sTU_FRIEND_ADD_RES);
}

void CommunitySession::SendFriendDelete(Packet packet)
{
	sUT_FRIEND_DEL_REQ * req = (sUT_FRIEND_DEL_REQ*)packet.GetPacketBuffer();

	sTU_FRIEND_DEL_RES res;

	res.wPacketSize = (sizeof sTU_FRIEND_DEL_RES) - 2;
	res.wOpCode = TU_FRIEND_ADD_RES;
	wcscpy_s(res.wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, req->wchName);
	res.wResultCode = CHAT_SUCCESS;
	res.targetID = (int)req->wchName[0] + (int)req->wchName[1];

	SendPacket((char*)&res, sizeof sTU_FRIEND_DEL_RES);
}

void CommunitySession::SendFriendMove(Packet packet)
{
	sUT_FRIEND_MOVE_REQ * req = (sUT_FRIEND_MOVE_REQ*)packet.GetPacketBuffer();

	sTU_FRIEND_MOVE_RES res;
	
	res.wPacketSize = (sizeof sTU_FRIEND_MOVE_RES) - 2;
	res.wOpCode = TU_FRIEND_MOVE_RES;
	res.wResultCode = CHAT_SUCCESS;
	wcscpy_s(res.wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, req->wchName);
	res.targetID = (int)req->wchName[0] + (int)req->wchName[1];

	SendPacket((char*)&res, sizeof sTU_FRIEND_MOVE_RES);
}

void CommunitySession::SendFriendBlackAdd(Packet packet)
{
	sUT_FRIEND_BLACK_ADD_REQ * req = (sUT_FRIEND_BLACK_ADD_REQ*)packet.GetPacketBuffer();

	sTU_FRIEND_BLACK_ADD_RES res;

	res.wPacketSize = (sizeof sTU_FRIEND_BLACK_ADD_RES) - 2;
	res.wOpCode = TU_FRIEND_BLACK_ADD_RES;
	res.wResultCode = CHAT_SUCCESS;
	wcscpy_s(res.wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, req->awchName);
	res.targetID = (int)req->awchName[0] + (int)req->awchName[1];

	SendPacket((char*)&res, sizeof sTU_FRIEND_BLACK_ADD_RES);
}

void CommunitySession::SendFriendBlackDelete(Packet packet)
{
	sUT_FRIEND_BLACK_DEL_REQ * req = (sUT_FRIEND_BLACK_DEL_REQ*)packet.GetPacketBuffer();

	sTU_FRIEND_BLACK_DEL_RES res;

	res.wPacketSize = (sizeof sTU_FRIEND_BLACK_DEL_RES) - 2;
	res.wOpCode = TU_FRIEND_BLACK_DEL_RES;
	res.wResultCode = CHAT_SUCCESS;
	wcscpy_s(res.wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, req->awchName);
	res.targetID = (int)req->awchName[0] + (int)req->awchName[1];

	SendPacket((char*)&res, sizeof sTU_FRIEND_BLACK_DEL_RES);
}