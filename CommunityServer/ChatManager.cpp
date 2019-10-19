#include <CommunitySocket.h>
#include <Logger.h>
#include <stdio.h>
#include <cstdio>
#include <Opcodes.h>
#include <Encryptation.h>
#include <mysqlconn_wrapper.h>
#include <XmlParser2/XmlParser2.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Packet.h>
#include "CommunitySession.h"
#include "Community.h"
#include "NtlStringHandler.h"
#include "source\Header\Game\Object\Player.h"

void CommunitySession::SendLocalChat(Packet packet)
{
	/*
	app->db->prepare("SELECT OnlineID FROM accounts WHERE AccountID = ?");
	app->db->setInt(1, this->accountID);
	app->db->execute();
	app->db->fetch();

	int onlineid = app->db->getInt("OnlineID");
	this->characterID = onlineid;
	sUT_CHAT_MESSAGE_SAY * req = (sUT_CHAT_MESSAGE_SAY *)pPacket->GetPacketData();

	CLkPacket packet(sizeof(sTU_CHAT_MESSAGE_SAY));
	sTU_CHAT_MESSAGE_SAY * res = (sTU_CHAT_MESSAGE_SAY *)packet.GetPacketData();
	req->awchMessage[LK_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE] = 0;
	res->wOpCode = TU_CHAT_MESSAGE_SAY;
	wcscpy_s(res->awchMessage, LK_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1, req->awchMessage);
	res->wMessageLengthInUnicode = req->wMessageLengthInUnicode;
	res->hSubject = this->characterID;

	wcscpy_s(res->awchSenderCharName, LK_MAX_SIZE_CHAR_NAME_UNICODE + 1, s2ws(this->charName).c_str());

	packet.SetPacketLen(sizeof(sTU_CHAT_MESSAGE_SAY));
	//	int rc = g_pApp->Send( this->GetHandle(), &packet );
	//	app->UserBroadcastothers(&packet, this);
	app->UserBroadcast(&packet);
*/
	sUT_CHAT_MESSAGE_SAY * req = (sUT_CHAT_MESSAGE_SAY *)packet.GetPacketBuffer();
	
	sTU_CHAT_MESSAGE_SAY res;
	memset(&res, 0, sizeof(sTU_CHAT_MESSAGE_SAY));
	req->awchMessage[req->wMessageLengthInUnicode] = 0;
	//sLog.outPacketFile(&packet);
	res.wPacketSize = sizeof(sTU_CHAT_MESSAGE_SAY) - 2;
	res.wOpCode = TU_CHAT_MESSAGE_SAY;
	res.hSubject = _player->handle;
	//wcscpy_s(res.awchMessage, MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1, req->awchMessage);

	memcpy(res.awchMessage, req->awchMessage, sizeof(wchar_t)* MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1);
	printf("sTU_CHAT_MESSAGE_SAY");
	res.wMessageLengthInUnicode = req->wMessageLengthInUnicode;
	_charName = s2ws(_player->GetName());
	wcscpy_s(res.awchSenderCharName, MAX_SIZE_CHAR_NAME_UNICODE + 1, (_charName).c_str());


	sCommunity.SendToAll((char*)&res, sizeof(sTU_CHAT_MESSAGE_SAY));
}

void CommunitySession::SendShoutChat(Packet packet)
{
	sUT_CHAT_MESSAGE_SHOUT * req = (sUT_CHAT_MESSAGE_SHOUT*)packet.GetPacketBuffer();

	sTU_CHAT_MESSAGE_SHOUT res;
	memset(&res, 0, sizeof(sTU_CHAT_MESSAGE_SHOUT));
	req->awchMessage[req->wMessageLengthInUnicode] = 0;
	res.wPacketSize = sizeof(sTU_CHAT_MESSAGE_SHOUT) - 2;
	res.wOpCode = TU_CHAT_MESSAGE_SHOUT;
	res.hSubject = _player->handle;

	wcscpy_s(res.awchMessage, MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1, req->awchMessage);

	res.wMessageLengthInUnicode = req->wMessageLengthInUnicode;

	_charName = s2ws(_player->GetName());
	wcscpy_s(res.awchSenderCharName, MAX_SIZE_CHAR_NAME_UNICODE + 1, (_charName).c_str());

	sCommunity.SendToAll((char*)&res, sizeof(sTU_CHAT_MESSAGE_SHOUT));
}

void CommunitySession::SendTradeChat(Packet packet)
{
	sUT_CHAT_MESSAGE_TRADE * req = (sUT_CHAT_MESSAGE_TRADE*)packet.GetPacketBuffer();

	sTU_CHAT_MESSAGE_TRADE res;
	memset(&res, 0, sizeof(sTU_CHAT_MESSAGE_TRADE));
	res.wPacketSize = sizeof(sTU_CHAT_MESSAGE_TRADE) - 2;
	res.wOpCode = TU_CHAT_MESSAGE_TRADE;
	res.hSubject = _player->handle;
	req->awchMessage[req->wMessageLengthInUnicode] = 0;


	wcscpy_s(res.awchMessage, MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1, req->awchMessage);

	res.wMessageLengthInUnicode = req->wMessageLengthInUnicode;

	_charName = s2ws(_player->GetName());
	wcscpy_s(res.awchSenderCharName, MAX_SIZE_CHAR_NAME_UNICODE + 1, (_charName).c_str());

	res.byChannelID = 0;
	sCommunity.SendToAll((char*)&res, sizeof(sTU_CHAT_MESSAGE_TRADE));
}

void CommunitySession::SendLFGChat(Packet packet)
{
	sUT_CHAT_MESSAGE_FIND_PARTY * req = (sUT_CHAT_MESSAGE_FIND_PARTY*)packet.GetPacketBuffer();

	sTU_CHAT_MESSAGE_FIND_PARTY res;
	memset(&res, 0, sizeof(sTU_CHAT_MESSAGE_FIND_PARTY));
	req->awchMessage[req->wMessageLengthInUnicode] = 0;
	res.wPacketSize = sizeof(sTU_CHAT_MESSAGE_FIND_PARTY) - 2;
	res.wOpCode = TU_CHAT_MESSAGE_FIND_PARTY;
	res.hSubject = _player->handle;

	wcscpy_s(res.awchMessage, MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1, req->awchMessage);
	res.wMessageLengthInUnicode = req->wMessageLengthInUnicode;

	_charName = s2ws(_player->GetName());
	wcscpy_s(res.awchSenderCharName, MAX_SIZE_CHAR_NAME_UNICODE + 1, (_charName).c_str());

	res.byChannelID = 0;

	sCommunity.SendToAll((char*)&res, sizeof(sTU_CHAT_MESSAGE_FIND_PARTY));
}