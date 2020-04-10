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
#include <..\Maps\MapManager.h>
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

	char charName[17];
	sDB.wcharToChar(req->wchName, charName, 34);

	std::string charNameStr(charName);

	unsigned int friendId = sDB.GetFriendIdByName(charNameStr);

	res.targetID = friendId;

	sDB.AddFriendToList(_player->GetCharacterID(), friendId);

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

void CommunitySession::SendFriendListInfomation()
{
	//Send FriendList to player
	sTU_FRIEND_LIST_INFO List_info;
	List_info.wOpCode = TU_FRIEND_LIST_INFO;
	sql::ResultSet* result = sDB.executes("SELECT * from friendlist JOIN characters on characters.CharacterID = friendlist.CharID WHERE friendlist.OwnerID = %d", _player->GetCharacterID());
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}

	BYTE byCount = result->rowsCount();

	for (int i = 0; i < byCount; i++)
	{
		wcscpy_s(List_info.asInfo[i].wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, charToWChar(result->getString("Name").c_str()));
		List_info.asInfo[i].charID = result->getInt("CharID");
		List_info.asInfo[i].bIsBlack = result->getBoolean("IsBlack");

		result->next();
	}

	List_info.byCount = byCount;
	List_info.wPacketSize = 3 + ((sizeof sFRIEND_FULL_INFO) * List_info.byCount);
	SendPacket((char*)&List_info, 5 + ((sizeof sFRIEND_FULL_INFO) * List_info.byCount));

	//retun pointer to 1st

	result->first();

	sTU_FRIEND_INFO Friend;
	Friend.wOpCode = TU_FRIEND_INFO;
	Friend.bIsFirst = false;
	Friend.wPacketSize = sizeof(sTU_FRIEND_INFO) - 2;

	/*
	Friend.sInfo.charID = result->getInt("CharacterID");
	Friend.sInfo.byClass = result->getInt("ClassID");
	Friend.sInfo.byLevel = result->getInt("CurrentLevel");
	Friend.sInfo.byChannel = 0;
	Friend.sInfo.hHandle = _player->friendlist.find(result->getInt("CharacterID"))->second;

	Friend.sInfo.mapNameTblidx = 1;

	//sCommunity.FindSession(playerfriend)->SendPacket((char*)&Friend, sizeof(sTU_FRIEND_INFO));
	SendPacket((char*)&Friend, sizeof(sTU_FRIEND_INFO));
	sLog.outDebug("TU_FRIEND_INFO Packet Sent");

	*/

	for (int i = 0; i < byCount; i++)
	{
		int playerfriendID = _player->friendlist.find(result->getInt("CharacterID"))->first;

		if (sCommunity.FindSession(playerfriendID)) {

			//set Info
			Friend.sInfo.charID = result->getInt("CharacterID");
			Friend.sInfo.byClass = result->getInt("ClassID");
			Friend.sInfo.byLevel = result->getInt("CurrentLevel");
			Friend.sInfo.byChannel = 0;
			Friend.sInfo.hHandle = _player->friendlist.find(result->getInt("CharacterID"))->second;
			Friend.sInfo.mapNameTblidx = result->getInt("MapInfoID");
			//send the packet
			SendPacket((char*)&Friend, sizeof(sTU_FRIEND_INFO));
			
		}
		//Offline
		else {
		}
		result->next();
	}


	/*
	//Send Online 
	sTU_FRIEND_INFO_CHANGE res2;
	res2.wOpCode = TU_FRIEND_INFO_CHANGE;
	res2.byChangeType = eFRIEND_CHANGE_TYPE::eFRIEND_CHANGE_TYPE_LEVEL;
	res2.dwChangeValue = 100;
	res2.wPacketSize = sizeof(sTU_FRIEND_INFO_CHANGE) - 2;

	for (auto itr = _player->friendlist.begin(); itr != _player->friendlist.end(); ++itr) 
	{
		if (itr->second > 0) {
			res2.targetID = itr->second;

			if (sCommunity.FindSession(itr->first)) {
				sLog.outDebug("Session Found");
				sCommunity.FindSession(itr->first)->SendPacket((char*)&res2, sizeof(sTU_FRIEND_INFO_CHANGE));
				sLog.outDebug("Session Found and Packet Sent");
			}
				
				
		}
		//sLog.outDebug("KEY : %d VALUE : %d", itr->first, itr->second);
	}
	

	*/

}

void CommunitySession::NotifyOtherPlayersFriendList() {


	sql::ResultSet* result = sDB.executes("SELECT * from characters WHERE CharacterID = %d", _player->GetCharacterID());


	sTU_FRIEND_INFO Friend;
	Friend.wOpCode = TU_FRIEND_INFO;
	Friend.bIsFirst = false;
	Friend.wPacketSize = sizeof(sTU_FRIEND_INFO) - 2;

	for (auto itr = _player->friendlist.begin(); itr != _player->friendlist.end(); ++itr)
	{

		if (sCommunity.FindSession(itr->first)) {

			//set Info
			Friend.sInfo.charID = result->getInt("CharacterID");
			Friend.sInfo.byClass = result->getInt("ClassID");
			Friend.sInfo.byLevel = result->getInt("CurrentLevel");
			Friend.sInfo.byChannel = result->getInt("WorldID");
			Friend.sInfo.hHandle = _player->GetHandle();
			Friend.sInfo.mapNameTblidx = result->getInt("MapInfoID");
			//send the packet
			Player* plr = static_cast<Player*>(sCommunity.FindSession(itr->first)->_player);
			plr->SendPacket((char*)&Friend, sizeof(sTU_FRIEND_INFO));

		}
		//Offline
		else {
		}
	}

}

void CommunitySession::NotifyOtherPlayersFriendList_onLogoff() {

	//Send Offline Packet
	sTU_FRIEND_INFO_CHANGE res;
	res.wOpCode = TU_FRIEND_INFO_CHANGE;
	res.byChangeType = eFRIEND_CHANGE_TYPE::eFRIEND_CHANGE_TYPE_OFFLINE;
	res.dwChangeValue = 2;
	res.wPacketSize = sizeof(sTU_FRIEND_INFO_CHANGE) - 2;

	for (auto itr = _player->friendlist.begin(); itr != _player->friendlist.end(); ++itr)
	{

		if (sCommunity.FindSession(itr->first)) {

			//set Info
			res.targetID = _player->GetCharacterID();

			//send the packet
			Player* plr = static_cast<Player*>(sCommunity.FindSession(itr->first)->_player);
			plr->SendPacket((char*)&res, sizeof(sTU_FRIEND_INFO_CHANGE));

		}
		//Offline
		else {
		}
	}


}