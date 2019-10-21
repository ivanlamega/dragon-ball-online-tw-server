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
#include <Game\Object\Player.h>

void CommunitySession::SendHlsSlotMachineInfo(Packet packet)
{
	sUT_HLS_SLOT_MACHINE_INFO_REQ* req = (sUT_HLS_SLOT_MACHINE_INFO_REQ *)packet.GetPacketBuffer();
	if (req->TabType == 0)//Waggu Waggu Tab
	{
		sTU_HLS_SLOT_MACHINE_INFO_RES res;
		memset(&res, 0, sizeof(sTU_HLS_SLOT_MACHINE_INFO_RES));
		res.wOpCode = TU_HLS_SLOT_MACHINE_INFO_RES;
		res.wPacketSize = sizeof(sTU_HLS_SLOT_MACHINE_INFO_RES) - 2;
		res.ResultCode = CHAT_SUCCESS;
		res.BiginCount = 0;
		res.TotalCount = 4;

		//MachineID
		res.MachineID[0] = 1;
		res.MachineID[1] = 2;
		res.MachineID[2] = 3;
		res.MachineID[3] = 4;

		//Cost to play
		res.Price[0] = 1;//price
		res.Price[1] = 1;
		res.Price[2] = 1;
		res.Price[3] = 1;

		// 1 to activate Machine
		res.unk[0] = 1;
		res.unk[1] = 1;
		res.unk[2] = 1;
		res.unk[3] = 1;

		//Set Items Avalible in Machine 1
		res.ItemRankMachine1[0] = 2400029;
		res.ItemRankMachine1[1] = 2400026;
		res.ItemRankMachine1[2] = 2400024;
		res.ItemRankMachine1[3] = 2500003;
		res.ItemRankMachine1[4] = 2900561;
		res.ItemRankMachine1[5] = 2400011;

		//Set Items Avalible in Machine 2
		res.ItemRankMachine2[0] = 2900590;
		res.ItemRankMachine2[1] = 2800003;
		res.ItemRankMachine2[2] = 2900766;
		res.ItemRankMachine2[3] = 2900590;
		res.ItemRankMachine2[4] = 2900645;

		//Set Items Avalible in Machine 3
		res.ItemRankMachine3[0] = 2900465;
		res.ItemRankMachine3[1] = 2800003;
		res.ItemRankMachine3[2] = 2900766;
		res.ItemRankMachine3[3] = 2900590;
		res.ItemRankMachine3[4] = 2900645;

		//Set Items Avalible in Machine 4
		res.ItemRankMachine4[0] = 2900628;
		res.ItemRankMachine4[1] = 2800003;
		res.ItemRankMachine4[2] = 2900766;
		res.ItemRankMachine4[3] = 2900590;
		res.ItemRankMachine4[4] = 2900645;

		//Define if is Waggu or Event "0 = Waggu 1 = Event"
		res.CoinType[0] = 0;
		res.CoinType[1] = 0;
		res.CoinType[2] = 0;
		res.CoinType[3] = 0;
		//Show how Much Balls Machine Got "low number balls more chance to get Rank1 Item"
		res.BallsMachine1 = 800;
		res.BallsMachine2 = 800;
		res.BallsMachine3 = 800;
		res.BallsMachine4 = 800;
		//Show max balls in Maxine
		res.MaxBallsMachine1 = 800;
		res.MaxBallsMachine2 = 800;
		res.MaxBallsMachine3 = 800;
		res.MaxBallsMachine4 = 800;
		SendPacket((char*)&res, sizeof(sTU_HLS_SLOT_MACHINE_INFO_RES));

	}
	else if (req->TabType == 1)//Event Tab not know how load Correct yet
	{
		sTU_HLS_SLOT_MACHINE_INFO_RES res;
		memset(&res, INVALID_TBLIDX, sizeof(sTU_HLS_SLOT_MACHINE_INFO_RES));
		res.wOpCode = TU_HLS_SLOT_MACHINE_INFO_RES;
		res.wPacketSize = sizeof(sTU_HLS_SLOT_MACHINE_INFO_RES) - 2;
		res.ResultCode = CHAT_SUCCESS;
		res.BiginCount = 0;
		res.TotalCount = 1;
		SendPacket((char*)&res, sizeof(sTU_HLS_SLOT_MACHINE_INFO_RES));
	}
}

void CommunitySession::SendHlsSlotMachineExtract(Packet packet)
{
	sUT_HLS_SLOT_MACHINE_EXTRACT_REQ* req = (sUT_HLS_SLOT_MACHINE_EXTRACT_REQ *)packet.GetPacketBuffer();
	//printf(" MachineID %d \n unk %d \n unk2 %d \n", req->MachineID, req->unk, req->PlayTimes);
	//Execute The Play Machine
	//Check if Player got Coin to play
	if (_player->GetAttributesManager()->WagguCoin >= req->PlayTimes)
	{
		sTU_HLS_SLOT_MACHINE_EXTRACT_RES res;
		memset(&res, 0, sizeof(sTU_HLS_SLOT_MACHINE_EXTRACT_RES));
		res.wOpCode = TU_HLS_SLOT_MACHINE_EXTRACT_RES;
		res.wPacketSize = sizeof(sTU_HLS_SLOT_MACHINE_EXTRACT_RES) - 2;
		res.ResultCode = CHAT_SUCCESS;
		res.MachineID = req->MachineID;
		res.unk[0] = req->unk;//Set 0 never Change
		res.unk[1] = 0;
		res.unk[2] = 0;
		res.RewardWPPoint = 10;//Waggu point	
		res.ByItemCount = 1;//count item reward Item
		res.WagguCost = 1;//Waggu consumable ???
		res.PlayNumber = req->PlayTimes;// PlayCount
		//4 machine with 5 ItemID
		const int myArray[4][6] = {
			{ 2400029,2400026,2400024,2500003,2900561,2400011},
			{ 2900590,2800003,2900766,2900590,2900645,2900645},
			{ 2900465,2400022,2900766,2900590,2900645,2900645},
			{ 2900628,2800003,2900766,2900590,2900645,2900645},
		};		

		//Create the Recived Item
		//use for bacause can play 1x 5x or 10x
		for (int j = 0; j < res.PlayNumber; j++)
		{
			int peekUp = rand() % 6;//if play mutlip times get Same Item in all
			res.ItemID[j] = myArray[req->MachineID - 1][peekUp];//need Correct ItemID for Machine
			sGU_CASHITEM_ADD_NFY item;
			memset(&item, 0, sizeof(sGU_CASHITEM_ADD_NFY));
			item.handle = sCommunity.AcquireItemSerialId();//ItemHandle
			item.sInfo.dwProductId = 0;

			item.sInfo.ItemHLSTableID = myArray[req->MachineID - 1][peekUp];//need Correct ItemID for Machine
			item.sInfo.byStackCount = res.ByItemCount;//Item count
			//for (int i = 0; i <= 9; i++) { item.unk1[i] = 0; }
			//for (int i = 0; i <= 17; i++) { item.awchName[i] = 0; }
			memset(item.unk1, 0, sizeof item.unk1);
			memset(item.awchName, 0, sizeof item.awchName);
			//Time of Item Creation
			item.Year = 2017;
			item.Moch = 12;
			item.Day = 25;
			item.Hour = 10;
			item.Minute = 30;
			item.Secound = 25;
			item.unk2 = 0;
			item.wOpCode = GU_CASHITEM_ADD_NFY;
			item.wPacketSize = sizeof(sGU_CASHITEM_ADD_NFY) - 2;
			SendPacket((char*)&item, sizeof(sGU_CASHITEM_ADD_NFY));
			sDB.AddCashItem(item.sInfo.ItemHLSTableID, _player->charid, item.sInfo.byStackCount, item.handle);
			
		}
		SendPacket((char*)&res, sizeof(sTU_HLS_SLOT_MACHINE_EXTRACT_RES));
		// Update the coin
		sTU_WAGUWAGUCOIN_UPDATE_INFO UpdateCoin;
		UpdateCoin.wOpCode = TU_WAGUWAGUCOIN_UPDATE_INFO;
		UpdateCoin.wPacketSize = sizeof(sTU_WAGUWAGUCOIN_UPDATE_INFO) - 2;
		UpdateCoin.WagguCoin = _player->GetAttributesManager()->WagguCoin - req->PlayTimes;
		_player->GetAttributesManager()->WagguCoin = UpdateCoin.WagguCoin;
		SendPacket((char*)&UpdateCoin, sizeof(sTU_WAGUWAGUCOIN_UPDATE_INFO));
		sDB.SavePlayerWagguCoin(_player->GetAttributesManager()->WagguCoin, _player->GetCharacterID());
	}
	else
	{
		sTU_HLS_SLOT_MACHINE_EXTRACT_RES res;
		memset(&res, 0, sizeof(sTU_HLS_SLOT_MACHINE_EXTRACT_RES));
		res.wOpCode = TU_HLS_SLOT_MACHINE_EXTRACT_RES;
		res.wPacketSize = sizeof(sTU_HLS_SLOT_MACHINE_EXTRACT_RES) - 2;
		res.ResultCode = 15004;
		SendPacket((char*)&res, sizeof(sTU_HLS_SLOT_MACHINE_EXTRACT_RES));
	}
}

void CommunitySession::SendHlsSlotMachineWinnerInfo(Packet packet)
{
	sUT_HLS_SLOT_MACHINE_WINNER_INFO_REQ* req = (sUT_HLS_SLOT_MACHINE_WINNER_INFO_REQ *)packet.GetPacketBuffer();
	sTU_HLS_SLOT_MACHINE_WINNER_INFO_RES res;
	memset(&res, 0, sizeof(sTU_HLS_SLOT_MACHINE_WINNER_INFO_RES));
	//	printf(" MachineID %d \n unk %d \n", req->MachineID, req->unk);
	res.wOpCode = TU_HLS_SLOT_MACHINE_WINNER_INFO_RES;
	res.wPacketSize = sizeof(sTU_HLS_SLOT_MACHINE_WINNER_INFO_RES) - 2;
	res.ResultCode = 300;
	res.MachineID = req->MachineID;
	res.BiginCount = 0;
	res.TotalCount = 3;
	wcscpy_s(res.WinnerCharName1, MAX_SIZE_CHAR_NAME_UNICODE + 1, (L"Marco Rafael"));
	wcscpy_s(res.WinnerCharName2, MAX_SIZE_CHAR_NAME_UNICODE + 1, (L"SanGawku"));
	wcscpy_s(res.WinnerCharName3, MAX_SIZE_CHAR_NAME_UNICODE + 1, (L"ANTIDOT3"));
	res.TryToGetRank1 = 1;//Try to get
	res.TryToGetRank2 = 2;//Try to get
	res.TryToGetRank3 = 3;//Try to get
	res.RewardTimeRank1 = 0;
	res.RewardTimeRank2 = 0;
	res.RewardTimeRank3 = 0;
	res.WinnerCount1 = 1;
	res.WinnerCount2 = 2;
	res.WinnerCount3 = 3;

	res.UNK11 = 0;

	res.UNK16 = 3;
	res.UNK17 = 1;
	res.UNK18 = 2;
	SendPacket((char*)&res, sizeof(sTU_HLS_SLOT_MACHINE_WINNER_INFO_RES));
}
