#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser.h>

void WorldSession::SendHLSShopStart(Packet & packet)
{
	//sLog.outError("UG_CASHITEM_HLSHOP_START_REQ");
	sGU_CASHITEM_HLSHOP_START_RES res;

	res.dwRemainAmount = _player->GetAttributesManager()->cashpoit;
	res.wOpCode = GU_CASHITEM_HLSHOP_START_RES;
	res.wPacketSize = sizeof(sGU_CASHITEM_HLSHOP_START_RES) - 2;
	res.wResultCode = GAME_SUCCESS;
	_player->GetAttributesManager()->cashpoit = res.dwRemainAmount;
	SendPacket((char*)&res, sizeof(sGU_CASHITEM_HLSHOP_START_RES));
}

void WorldSession::SendHLSShopEnd(Packet & packet)
{
	//sLog.outError("UG_CASHITEM_HLSHOP_END_REQ");
	sGU_CASHITEM_HLSHOP_END_RES res;

	res.wOpCode = GU_CASHITEM_HLSHOP_END_RES;
	res.wPacketSize = sizeof(sGU_CASHITEM_HLSHOP_END_RES) - 2;
	res.wResultCode = GAME_SUCCESS;

	SendPacket((char*)&res, sizeof(sGU_CASHITEM_HLSHOP_END_RES));
}

void WorldSession::SendCashItemStart(Packet & packet)
{
	//sLog.outError("UG_CASHITEM_START_REQ");
	sGU_CASHITEM_START_RES res;

	res.wOpCode = GU_CASHITEM_START_RES;
	res.wPacketSize = sizeof(sGU_CASHITEM_START_RES) - 2;
	res.wResultCode = GAME_SUCCESS;

	SendPacket((char*)&res, sizeof(sGU_CASHITEM_START_RES));
}

void WorldSession::SendCashItemBuy(Packet & packet)
{
	//sLog.outError("UG_CASHITEM_BUY_REQ");
	sUG_CASHITEM_BUY_REQ* req = (sUG_CASHITEM_BUY_REQ *)packet.GetPacketBuffer();
	//TAble here
	if (sTBM.GetHLSItemTable() != NULL && sTBM.GetHLSItemTable()->FindData(req->HLSItemTblidx) != NULL)
	{
		sHLS_ITEM_TBLDAT* HLSData = (sHLS_ITEM_TBLDAT*)sTBM.GetHLSItemTable()->FindData(req->HLSItemTblidx);
		if (HLSData != NULL)
		{
			sGU_CASHITEM_BUY_RES res;
			sGU_CASHITEM_ADD_NFY item;

			res.wOpCode = GU_CASHITEM_BUY_RES;
			res.wPacketSize = sizeof(sGU_CASHITEM_BUY_RES) - 2;
			res.wResultCode = GAME_SUCCESS;
			DWORD price = HLSData->dwCost;
			res.curCash = _player->GetAttributesManager()->cashpoit;
			// check if got cash 
			if (res.curCash <= price || _player->GetAttributesManager()->cashpoit <= price)
			{
				res.curCash = _player->GetAttributesManager()->cashpoit;
				res.wResultCode = GAME_CASHITEM_CANT_MOVE;
			}
			if (_player->GetAttributesManager()->cashpoit >= price)
			{
				memset(&item, 0, sizeof(sGU_CASHITEM_ADD_NFY));
				item.handle = sWorld.AcquireItemSerialId();//PlayerHandle
				item.sInfo.dwProductId = 0;//Item Handle
				item.sInfo.ItemHLSTableID = req->HLSItemTblidx;//ItemHLSTableID "Not is Tblidx of item in Bag" Maybe they convert ID on Item Move;
				item.sInfo.byStackCount = HLSData->ItemAmount;//Item count
															  //for (int i = 0; i <= 17; i++) { item.awchName[i] = 0; }
				wcscpy_s(item.awchName, 16 + 1, (L" Marco "));
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

				res.curCash = _player->GetAttributesManager()->cashpoit - price;//Update cash in Cart
				_player->GetAttributesManager()->cashpoit = res.curCash;
			}
			SendPacket((char*)&res, sizeof(sGU_CASHITEM_BUY_RES));
			sDB.AddCashItem(item.sInfo.ItemHLSTableID, _player->charid, item.sInfo.byStackCount, item.handle);
			sDB.SavePlayerCashPoit(_player->GetAttributesManager()->cashpoit, _player->GetCharacterID());
		}
	}
	else
	{
		//printf("HLSItemTblidx %d", req->HLSItemTblidx);
		sGU_CASHITEM_BUY_RES res;
		res.wOpCode = GU_CASHITEM_BUY_RES;
		res.wPacketSize = sizeof(sGU_CASHITEM_BUY_RES) - 2;
		res.wResultCode = GAME_CASHITEM_NOT_FOUND;
		res.curCash = _player->GetAttributesManager()->cashpoit;
		SendPacket((char*)&res, sizeof(sGU_CASHITEM_BUY_RES));
	}
}

void WorldSession::SendCashItemMove(Packet & packet)
{
	//sLog.outDebug("UG_CASHITEM_MOVE_REQ");
	sUG_CASHITEM_MOVE_REQ* req = (sUG_CASHITEM_MOVE_REQ *)packet.GetPacketBuffer();
	//Get ItemID by ItemHandle
	sql::ResultSet* result = sDB.executes("SELECT * FROM cashitem WHERE owner_id = '%d' AND Handle = '%d';", _player->charid, req->Handle);
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return;
	}
	int ItemID = result->getInt("tblidx");
	//Check if ItemID is Valid
	if (sTBM.GetHLSItemTable() != NULL && sTBM.GetHLSItemTable()->FindData(ItemID) != NULL)
	{
		sHLS_ITEM_TBLDAT* HLSData = (sHLS_ITEM_TBLDAT*)sTBM.GetHLSItemTable()->FindData(ItemID);
		if (HLSData != NULL)
		{
			//Create Item in Normal Bag
			sITEM_PROFILE createdItem;
			WORD result = _player->GetInventoryManager()->PerformShopBuy(HLSData->itemTblidx3, HLSData->ItemAmount, createdItem);
			if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
			{
				sGU_CASHITEM_MOVE_RES res;
				res.wOpCode = GU_CASHITEM_MOVE_RES;
				res.wPacketSize = sizeof(sGU_CASHITEM_MOVE_RES) - 2;
				res.wResultCode = GAME_SUCCESS;
				res.Handle = req->Handle;
				res.dwProductId = req->dwProductId;
				SendPacket((char*)&res, sizeof(sGU_CASHITEM_MOVE_RES));
				//sLog.outDetail("Item Created \n");
				SendItemCreate(&createdItem);
				//Delet The Item in Cash Bag after Recive	
				sGU_CASHITEM_DEL_NFY Del;
				Del.wOpCode = GU_CASHITEM_DEL_NFY;
				Del.wPacketSize = sizeof(sGU_CASHITEM_DEL_NFY) - 2;
				Del.handle = req->Handle;
				Del.dwProductId = req->dwProductId;
				SendPacket((char*)&Del, sizeof(sGU_CASHITEM_DEL_NFY));
				//Delete in Db here
				sql::ResultSet* result1 = sDB.executes("DELETE FROM `cashitem` WHERE `owner_id` = '%d' AND Handle = '%d';", _player->charid, req->Handle);
				if (result1 != NULL)
					delete result1;
			}
			else
			{
				sGU_CASHITEM_MOVE_RES res;
				res.wOpCode = GU_CASHITEM_MOVE_RES;
				res.wPacketSize = sizeof(sGU_CASHITEM_MOVE_RES) - 2;
				res.wResultCode = GAME_CASHITEM_CANT_MOVE;
				res.Handle = req->Handle;
				res.dwProductId = req->dwProductId;
				SendPacket((char*)&res, sizeof(sGU_CASHITEM_MOVE_RES));
			}
		}
	}
	else//case table is NULL send that error
	{
		sGU_CASHITEM_MOVE_RES res;
		res.wOpCode = GU_CASHITEM_MOVE_RES;
		res.wPacketSize = sizeof(sGU_CASHITEM_MOVE_RES) - 2;
		res.wResultCode = GAME_CASHITEM_CANT_MOVE;
		res.Handle = req->Handle;
		res.dwProductId = req->dwProductId;
		SendPacket((char*)&res, sizeof(sGU_CASHITEM_MOVE_RES));
	}
}

void WorldSession::SendCashItemEnd(Packet & packet)
{
	//sLog.outError("UG_CASHITEM_END_REQ");
	sGU_CASHITEM_END_RES res;

	res.wOpCode = GU_CASHITEM_END_RES;
	res.wPacketSize = sizeof(sGU_CASHITEM_END_RES) - 2;
	res.wResultCode = GAME_SUCCESS;

	SendPacket((char*)&res, sizeof(sGU_CASHITEM_END_RES));
}

void WorldSession::SendNetPyStart(Packet & packet)
{
	sGU_SHOP_NETPYITEM_START_RES res1;

	res1.byType = 0;
	res1.wOpCode = GU_SHOP_NETPYITEM_START_RES;
	res1.wResultCode = GAME_SUCCESS;
	res1.wPacketSize = sizeof(sGU_SHOP_NETPYITEM_START_RES) - 2;

	SendPacket((char*)&res1, sizeof(sGU_SHOP_NETPYITEM_START_RES));
}

void WorldSession::SendNetPyBuy(Packet & packet)
{
	sUG_SHOP_NETPYITEM_BUY_REQ* req = (sUG_SHOP_NETPYITEM_BUY_REQ *)packet.GetPacketBuffer();
		
	sGU_SHOP_NETPYITEM_BUY_RES res;

	res.wOpCode = GU_SHOP_NETPYITEM_BUY_RES;
	res.wResultCode = GAME_FAIL;
	res.wPacketSize = sizeof(sGU_SHOP_NETPYITEM_BUY_RES) - 2;

	SendPacket((char*)&res, sizeof(sGU_SHOP_NETPYITEM_BUY_RES));
}

void WorldSession::SendNetPyEnd(Packet & packet)
{
	sGU_SHOP_NETPYITEM_END_RES res;

	res.wOpCode = GU_SHOP_NETPYITEM_END_RES;
	res.wResultCode = GAME_SUCCESS;
	res.wPacketSize = sizeof(sGU_SHOP_NETPYITEM_END_RES) - 2;

	SendPacket((char*)&res, sizeof(sGU_SHOP_NETPYITEM_END_RES));
}
