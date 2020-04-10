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
	//Cast Request Packet
	sUT_FRIEND_ADD_REQ * req = (sUT_FRIEND_ADD_REQ*)packet.GetPacketBuffer();

	//Convert WCHAR to CHAR then to string  
	char charName[17];
	sDB.wcharToChar(req->wchName, charName, 34);
	std::string charNameStr(charName);

	//Cant invite urself or existing friend in ur friend list
	unsigned int friendId = sDB.GetFriendIdByName(charNameStr);
	if (friendId == -1) return;

	bool ExistingFriend = sDB.CheckFriendonFriendList(_player->GetCharacterID(),friendId);
	if (ExistingFriend) return;

	//Success
	if (friendId != _player->GetCharacterID() && !ExistingFriend)
	{
		//Prepare Packet 
		sTU_FRIEND_ADD_RES res;
		res.wPacketSize = (sizeof sTU_FRIEND_ADD_RES) - 2;
		res.wOpCode = TU_FRIEND_ADD_RES;
		wcscpy_s(res.wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, req->wchName);
		res.wResultCode = CHAT_SUCCESS;
		res.targetID = friendId;

		sDB.AddFriendToList(_player->GetCharacterID(), friendId);
		SendPacket((char*)&res, sizeof sTU_FRIEND_ADD_RES);

		//Send Informations to friendList
		sql::ResultSet* result = sDB.executes("SELECT * from characters WHERE CharacterID = %d", friendId);
		if (!result || result->rowsCount() <= 0) return;
		if (result->getInt("isOnline") == 1) {
			int Hhandle = result->getInt("GSHandle");
			SendFriendInfomationSingular(_player, result->getInt("CharacterID"), result->getInt("ClassID"), result->getInt("CurrentLevel"), 0, Hhandle, result->getInt("MapInfoID"));
		}
		
	}
	else {
		//sLog.outDebug("Add Player to Friend list Failed !");
		return;
	}

}

void CommunitySession::SendFriendDelete(Packet packet)
{
	sUT_FRIEND_DEL_REQ * req = (sUT_FRIEND_DEL_REQ*)packet.GetPacketBuffer();

	sTU_FRIEND_DEL_RES res;
	res.wOpCode = TU_FRIEND_DEL_RES;
	res.wPacketSize = sizeof(sTU_FRIEND_DEL_RES) - 2;
	res.wResultCode = CHAT_SUCCESS;
	res.targetID = req->targetID;
	wcscpy_s(res.wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, req->wchName);
	SendPacket((char*)&res, sizeof(sTU_FRIEND_DEL_RES));

	sDB.executes("DELETE FROM friendlist WHERE OwnerID = %d AND CharID = %d;", _player->GetCharacterID(), req->targetID);
	
}

void CommunitySession::SendFriendMove(Packet packet)
{
	sUT_FRIEND_MOVE_REQ * req = (sUT_FRIEND_MOVE_REQ*)packet.GetPacketBuffer();

	sTU_FRIEND_MOVE_RES res;
	res.wOpCode = TU_FRIEND_MOVE_RES;
	res.wPacketSize = sizeof (sTU_FRIEND_MOVE_RES) - 2;
	res.wResultCode = CHAT_SUCCESS;
	wcscpy_s(res.wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, req->wchName);
	res.targetID = req->targetID;
	SendPacket((char*)&res, sizeof sTU_FRIEND_MOVE_RES);

	sDB.executes("UPDATE `friendlist` SET `IsBlack` = '%d' WHERE `OwnerID` = '%d' AND `CharID` = '%d';", 1, _player->GetCharacterID(), req->targetID);
}

void CommunitySession::SendFriendBlackAdd(Packet packet)
{

	//Cast Request Packet
	sUT_FRIEND_BLACK_ADD_REQ * req = (sUT_FRIEND_BLACK_ADD_REQ*)packet.GetPacketBuffer();

	//Convert WCHAR to CHAR then to string  
	char charName[17];
	sDB.wcharToChar(req->awchName, charName, 17);
	std::string charNameStr(charName);

	//Cant invite urself or existing friend in ur friend list
	unsigned int friendId = sDB.GetFriendIdByName(charNameStr);
	if (friendId == -1) return;

	bool ExistingFriend = sDB.CheckFriendonFriendList(_player->GetCharacterID(), friendId);
	if (ExistingFriend) return;

	//Success
	if (friendId != _player->GetCharacterID() && !ExistingFriend)
	{
		//Prepare Packet 
		sTU_FRIEND_BLACK_ADD_RES res;
		res.wPacketSize = sizeof(sTU_FRIEND_BLACK_ADD_RES) - 2;
		res.wOpCode = TU_FRIEND_BLACK_ADD_RES;
		res.wResultCode = CHAT_SUCCESS;
		wcscpy_s(res.wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, req->awchName);
		res.targetID = friendId;
		sDB.AddBlackToList(_player->GetCharacterID(), friendId);
		SendPacket((char*)&res, sizeof(sTU_FRIEND_BLACK_ADD_RES));
	}
	else {
		//sLog.outDebug("Add Player to Friend list Failed !");
		return;
	}



	
	
}

void CommunitySession::SendFriendBlackDelete(Packet packet)
{
	sUT_FRIEND_BLACK_DEL_REQ * req = (sUT_FRIEND_BLACK_DEL_REQ*)packet.GetPacketBuffer();

	sTU_FRIEND_BLACK_DEL_RES res;
	res.wPacketSize = sizeof (sTU_FRIEND_BLACK_DEL_RES) - 2;
	res.wOpCode = TU_FRIEND_BLACK_DEL_RES;
	res.wResultCode = CHAT_SUCCESS;
	wcscpy_s(res.wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, req->awchName);
	res.targetID = req->targetID;

	SendPacket((char*)&res, sizeof(sTU_FRIEND_BLACK_DEL_RES));

	sDB.executes("DELETE FROM friendlist WHERE OwnerID = %d AND CharID = %d;", _player->GetCharacterID(), req->targetID);
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
	List_info.wPacketSize = 3 + ((sizeof (sFRIEND_FULL_INFO)) * List_info.byCount);
	SendPacket((char*)&List_info, 5 + ((sizeof (sFRIEND_FULL_INFO)) * List_info.byCount));

	//retun pointer to 1st Row
	result->first();

	for (int i = 0; i < byCount; i++)
	{
		int playerfriendID = _player->friendlist.find(result->getInt("CharacterID"))->first;

		if (sCommunity.FindSession(playerfriendID)) {
			//if blacked dont send
			if (result->getInt("isBlack") == 0) {
				int Hhandle = _player->friendlist.find(result->getInt("CharacterID"))->second;
				SendFriendInfomationSingular(_player, result->getInt("CharacterID"), result->getInt("ClassID"), result->getInt("CurrentLevel"), 0, Hhandle, result->getInt("MapInfoID"));
			}
		}
		//Offline
		else {
		}
		result->next();
	}

}

void CommunitySession::SendFriendInfomationSingular(Player *plr,int CharID, int ClassID, int Level, int Channel, HOBJECT handle, TBLIDX MapNameTblidx) {

	sTU_FRIEND_INFO Friend;
	Friend.wOpCode = TU_FRIEND_INFO;
	Friend.bIsFirst = false;
	Friend.wPacketSize = sizeof(sTU_FRIEND_INFO) - 2;

	//set Info
	Friend.sInfo.charID = CharID;
	Friend.sInfo.byClass = ClassID;
	Friend.sInfo.byLevel = Level;
	Friend.sInfo.byChannel = Channel;
	Friend.sInfo.hHandle = handle;
	Friend.sInfo.mapNameTblidx = MapNameTblidx;
	//send the packet
	plr->SendPacket((char*)&Friend, sizeof(sTU_FRIEND_INFO));

}

void CommunitySession::NotifyOtherPlayersFriendList() {

	sql::ResultSet* result = sDB.executes("SELECT * from friendlist JOIN characters ON characters.CharacterID = friendlist.CharID WHERE CharID = %d", _player->GetCharacterID());
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;	
		return;
	}

	sTU_FRIEND_INFO Friend;
	Friend.wOpCode = TU_FRIEND_INFO;
	Friend.bIsFirst = false;
	Friend.wPacketSize = sizeof(sTU_FRIEND_INFO) - 2;

	BYTE count = result->rowsCount();
	   
	for (int i = 0; i < count; i++) {

		if (sCommunity.FindSession(result->getInt("OwnerID"))) 
		{
			//send the packet
			Player* plr = static_cast<Player*>(sCommunity.FindSession(result->getInt("OwnerID"))->_player);
			SendFriendInfomationSingular(plr, result->getInt("CharacterID"), result->getInt("ClassID"), result->getInt("CurrentLevel"), 0, _player->GetHandle(), result->getInt("MapInfoID"));
		}


		//Offline
		else {
			//sLog.outDebug("Session Not Found");
		}

		result->next();
	}

}

void CommunitySession::NotifyOtherPlayersFriendList_onLogoff() {



	sql::ResultSet* result = sDB.executes("SELECT * from friendlist JOIN characters ON characters.CharacterID = friendlist.OwnerID WHERE CharID = %d and IsBlack = 0 and isOnline = 1", _player->GetCharacterID());
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}

	int count = result->rowsCount();

	//Send Offline Packet
	sTU_FRIEND_INFO_CHANGE res;
	res.wOpCode = TU_FRIEND_INFO_CHANGE;
	res.byChangeType = eFRIEND_CHANGE_TYPE::eFRIEND_CHANGE_TYPE_OFFLINE;
	res.dwChangeValue = 2;
	res.wPacketSize = sizeof(sTU_FRIEND_INFO_CHANGE) - 2;


	for (int i = 0; i < count; i++) {

		if (sCommunity.FindSession(result->getInt("OwnerID"))) {

			//set Info
			res.targetID = _player->GetCharacterID();

			//send the packet
			Player* plr = static_cast<Player*>(sCommunity.FindSession(result->getInt("OwnerID"))->_player);
			plr->SendPacket((char*)&res, sizeof(sTU_FRIEND_INFO_CHANGE));

			
		}
		//Offline
		else {
		}

		result->next();
	}

}

