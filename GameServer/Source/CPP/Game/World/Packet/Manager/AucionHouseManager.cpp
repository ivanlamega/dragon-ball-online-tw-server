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
#include <XmlParser2/XmlParser2.h>


void Player::AucionHouseList(Packet& packet)
{
	sUG_TENKAICHIDAISIJYOU_LIST_REQ* req = (sUG_TENKAICHIDAISIJYOU_LIST_REQ*)packet.GetPacketBuffer();

	sGU_TENKAICHIDAISIJYOU_LIST_RES res;
	res.wOpCode = GU_TENKAICHIDAISIJYOU_LIST_RES;
	res.wPacketSize = sizeof(sGU_TENKAICHIDAISIJYOU_LIST_RES) - 2;
	res.ResultCode = ResultCodes::GAME_SUCCESS;
	res.PageNumber = req->PageNumber;//StartPage	
	res.ItemCount = 0;//item count
	res.MaxPage = 1;//MaxPage

	sGU_TENKAICHIDAISIJYOU_LIST_DATA data;
	memset(&data, 0, sizeof(sGU_TENKAICHIDAISIJYOU_LIST_DATA));
	data.wOpCode = GU_TENKAICHIDAISIJYOU_LIST_DATA;
	data.wPacketSize = sizeof(sGU_TENKAICHIDAISIJYOU_LIST_DATA) - 2;

	sql::ResultSet* result = sDB.executes("SELECT * FROM aucionhouse;");
	if (result == NULL)	
		return;			
	if (result->rowsCount() <= 0)
	{
		res.ResultCode = ResultCodes::GAME_ITEM_NOT_FOUND;
		SendPacket((char*)&res, sizeof(sGU_TENKAICHIDAISIJYOU_LIST_RES));
		delete result;
		return;		
	}
	int i = 0;	
	int TotalCount = 0;
	int TotalSellItemCount = 0;
	while (true)
	{		
		DWORD ItemID = result->getInt("ItemTblidx");
		int CharIDs = result->getInt("CharID");

		sITEM_TBLDAT *ItemData = NULL;
		if ((ItemData = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(ItemID)) == NULL)
		{
			ItemData = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(ItemID);
		}
		if (ItemData != NULL)
		{						
			//Load Buy Tab
			if (req->charID == INVALID_TBLIDX && TotalCount >= (req->PageNumber * 10 - 10) && TotalCount <= (req->PageNumber * 10))
			{
				data.CharID = result->getInt("CharID");
				data.ItemHandle = result->getInt("ItemHandle");
				data.ItemTblidx = ItemID;
				data.TabType = req->ItemTypeTab;
				data.ItemType = result->getInt("ItemType");
				data.ByLevel = result->getInt("ItemLevel");
				wcscpy_s(data.SellerName, MAX_SIZE_CHAR_NAME_UNICODE + 1, charToWChar((result->getString("SellerName")).c_str()));
				wcscpy_s(data.wszItemName, 32 + 1, ItemData->awcNameText);
				data.SellAmount = result->getInt("SellAmount");
				data.ByStackCount = result->getInt("StackCount");
				data.Rank = ItemData->eRank;
				data.Grade = result->getInt("ItemGrade");
				data.Durablity = ItemData->byDurability;
				data.StartTime = 24;
				data.EndTime = 23;

				for (int k = 0; k < 2; k++)
				{
					data.aitemExtraEffect[k].wType = INVALID_WORD;
					data.aitemExtraEffect[k].dwValue = INVALID_TBLIDX;
				}
				for (int k = 0; k < 6; k++)
				{
					data.aitemEffect[k].wType = INVALID_WORD;
					data.aitemEffect[k].dwValue = INVALID_TBLIDX;
				}	
				i++;
				SendPacket((char*)&data, sizeof(sGU_TENKAICHIDAISIJYOU_LIST_DATA));
			}			
			//Load Sell Tab
			if (req->charID == CharIDs)
			{
				if (i >= (req->PageNumber * 10 - 10) && i <= (req->PageNumber * 10))
				{
					data.CharID = result->getInt("CharID");
					data.ItemHandle = result->getInt("ItemHandle");
					data.ItemTblidx = ItemID;
					data.TabType = req->ItemTypeTab;
					data.ItemType = result->getInt("ItemType");
					data.ByLevel = result->getInt("ItemLevel");
					wcscpy_s(data.SellerName, MAX_SIZE_CHAR_NAME_UNICODE + 1, charToWChar((result->getString("SellerName")).c_str()));
					wcscpy_s(data.wszItemName, 32 + 1, ItemData->awcNameText);
					data.SellAmount = result->getInt("SellAmount");
					data.ByStackCount = result->getInt("StackCount");
					data.Rank = ItemData->eRank;
					data.Grade = result->getInt("ItemGrade");
					data.Durablity = ItemData->byDurability;
					data.StartTime = 24;
					data.EndTime = 20;

					for (int k = 0; k < 2; k++)
					{
						data.aitemExtraEffect[k].wType = INVALID_WORD;
						data.aitemExtraEffect[k].dwValue = INVALID_TBLIDX;
					}
					for (int k = 0; k < 6; k++)
					{
						data.aitemEffect[k].wType = INVALID_WORD;
						data.aitemEffect[k].dwValue = INVALID_TBLIDX;
					}
					SendPacket((char*)&data, sizeof(sGU_TENKAICHIDAISIJYOU_LIST_DATA));
					TotalSellItemCount++;
				}				
				i++;
			}	
			TotalCount++;			
			res.ItemCount = i;//item count			

			//Item/Page Count to Buy
			if (req->charID == INVALID_TBLIDX && TotalCount > 0)
			{
				res.PageNumber = req->PageNumber;
				res.MaxPage = (TotalCount / 10) + 1;
			}
			else
			{
				res.MaxPage == 1;
			}
			//Item/Page Count to Sell
			if (req->charID == CharIDs && i > 0)
			{
				res.ItemCount = TotalSellItemCount;
				res.PageNumber = req->PageNumber;
				res.MaxPage = (i / 10) + 1;
			}
			else
			{
				//res.ItemCount = TotalSellItemCount;
				res.MaxPage == 1;
			}
			//printf(" Count %d \n", res.ItemCount);
			if (result->next())
				continue;
			else
				break;
		}
		delete result;
	}	
	SendPacket((char*)&res, sizeof(sGU_TENKAICHIDAISIJYOU_LIST_RES));
}
void Player::AucionHouseSell(Packet& packet)
{
	sUG_TENKAICHIDAISIJYOU_SELL_REQ* req = (sUG_TENKAICHIDAISIJYOU_SELL_REQ*)packet.GetPacketBuffer();
	sITEM_PROFILE *Item = NULL;
	sITEM_TBLDAT *ItemData = NULL;

	Item = this->inventoryManager.GetItemAtPlaceAndPost(req->byPlace, req->byPos);
	if (Item != NULL)
	{
		if ((ItemData = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Item->tblidx)) == NULL)
		{
			ItemData = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Item->tblidx);
		}
		if (ItemData != NULL)
		{
			sGU_TENKAICHIDAISIJYOU_SELL_RES res;
			res.wOpCode = GU_TENKAICHIDAISIJYOU_SELL_RES;
			res.wPacketSize = sizeof(sGU_TENKAICHIDAISIJYOU_SELL_RES) - 2;
			res.ResultCode = GAME_SUCCESS;
			res.ItemID = Item->tblidx;
			res.byPlace = Item->byPlace;
			res.byPos = Item->byPos;
			char PlayerName[16];
			wcstombs(PlayerName, GetPcProfile()->awchName, 16);
			sDB.AddAucionHouseSell(charid, Item->handle, PlayerName, Item->tblidx, req->Price, req->StackCount, ItemData->byNeedLevel, ItemData->eItemType, Item->byGrade ,Item->byRank, Item->aitemEffect[0].wType, Item->aitemEffect[0].dwValue, Item->aitemEffect[1].wType, Item->aitemEffect[1].dwValue, Item->aitemEffect[2].wType, Item->aitemEffect[2].dwValue, Item->aitemEffect[3].wType, Item->aitemEffect[3].dwValue, Item->aitemEffect[4].wType, Item->aitemEffect[4].dwValue, Item->aitemEffect[5].wType, Item->aitemEffect[5].dwValue);
			SendPacket((char*)&res, sizeof(sGU_TENKAICHIDAISIJYOU_SELL_RES));

			//Delet Item From Inventary

			//sLog.outError("Item Handle add %d", Item->handle);
		}
	}	
}
void Player::AucionHouseSellCancel(Packet& packet)
{
	sUG_TENKAICHIDAISIJYOU_SELL_CANCEL_REQ* req = (sUG_TENKAICHIDAISIJYOU_SELL_CANCEL_REQ*)packet.GetPacketBuffer();
	//sLog.outError("Item Handle Cancel %d",req->ItemHandle);

	sGU_TENKAICHIDAISIJYOU_SELL_CANCEL_RES res;
	memset(&res, 0, sizeof(sGU_TENKAICHIDAISIJYOU_SELL_CANCEL_RES));
	res.wOpCode = GU_TENKAICHIDAISIJYOU_SELL_CANCEL_RES;
	res.wPacketSize = sizeof(sGU_TENKAICHIDAISIJYOU_SELL_CANCEL_RES) - 2;

	sql::ResultSet* result = sDB.executes("SELECT * FROM aucionhouse WHERE ItemHandle = '%d';", req->ItemHandle);
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{
		res.ResultCode = ResultCodes::GAME_ITEM_NOT_FOUND;
		SendPacket((char*)&res, sizeof(sGU_TENKAICHIDAISIJYOU_SELL_CANCEL_RES));
		delete result;
		return;
	}	
	int i = 0;
	while (true)
	{
		DWORD ItemID = result->getInt("ItemTblidx");
		int StackCount = result->getInt("StackCount");
		int Grade = result->getInt("ItemGrade");
		//SendEmailAucionHouse(ItemID, StackCount, Grade, eMAIL_TYPE_ITEM, 0);
		res.ResultCode = ResultCodes::GAME_SUCCESS;				
		SendPacket((char*)&res, sizeof(sGU_TENKAICHIDAISIJYOU_SELL_CANCEL_RES));
		sql::ResultSet* result1 = sDB.executes("DELETE FROM `aucionhouse` WHERE `ItemHandle` = '%d';", req->ItemHandle);
		if (result1 != NULL)
			delete result1;
		i++;
		if (result->next())
			continue;
		else
			break;
	}
	delete result;	
}

void Player::SendEmailAucionHouse(int ItemID, int StackCount, int Grade, int EmailType, int Zenny)
{
	sGU_MAIL_SEND_RES sMailData;
	sMailData.wOpCode = GU_MAIL_SEND_RES;
	sMailData.wPacketSize = sizeof(sGU_MAIL_SEND_RES) - 2;

	char targetname[16];
	wcstombs(targetname, GetPcProfile()->awchName, 16);
	char PlayerName[16];
	wcstombs(PlayerName, L"System", 16);
	char *text = new char[128];
	wcstombs(text, L"This Mail From Aucion House", 128);
	text[128] = '\0';

	sql::ResultSet* result = sDB.executes("SELECT * FROM characters WHERE Name = '%s';", targetname);
	if (result == NULL)
		return;
	if (result->rowsCount() <= 0)
	{	
		sMailData.hObject = INVALID_TBLIDX;
		sMailData.wResultCode = GAME_MAIL_NOT_EXISTING_PLAYER;
		SendPacket((char*)&sMailData, sizeof(sGU_MAIL_SEND_RES));
		delete result;
		return;
	}	
	if (result != NULL)
	{
		int id = result->getInt("CharacterID");
		bool isAway = result->getBoolean("MailIsAway");
		wcscpy_s(sMailData.wszTargetName, 16, GetPcProfile()->awchName);
		sMailData.hObject = INVALID_TBLIDX;	

		sMailData.wResultCode = GAME_SUCCESS;
		sDB.AddMail(id, 1, EmailType, 128, text, targetname, PlayerName, 0, 0, 0, eMAIL_SENDER_TYPE::eMAIL_SENDER_TYPE_SYSTEM, ItemID, StackCount, Grade, Zenny);
		
		SendPacket((char*)&sMailData, sizeof(sGU_MAIL_SEND_RES));		
	}	
	delete result;
	return;
}