#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <Game\Object\Npc.h>
#include <XmlParser2/XmlParser2.h>

//----------------------------------------
//	Send avatar item from database
//----------------------------------------
void WorldSession::SendAvatarItemInfo()
{
	sGU_AVATAR_ITEM_INFO	res;
	memset(&res, 0, sizeof(sGU_AVATAR_ITEM_INFO));

	res.wOpCode = GU_AVATAR_ITEM_INFO;

	int totalItem = _player->inventoryManager.GetTotalItemsCount();
	int divide = 1;
	int sendCount = 0;

	res.byBeginCount = 0;
	res.byItemCount = 0;

	if (totalItem >= 31)
	{
		divide = 6;
	}
	else
		divide = 1;
	for (int totalLoop = 0; totalLoop < divide; totalLoop++)
	{
		for (int i = 0; i <= std::round(totalItem / divide); i++, sendCount++)
		{
			res.aItemProfile[i].handle = _player->inventoryManager.GetInventory()[sendCount].handle;
			res.aItemProfile[i].tblidx = _player->inventoryManager.GetInventory()[sendCount].tblidx;
			res.aItemProfile[i].byPlace = _player->inventoryManager.GetInventory()[sendCount].byPlace;
			res.aItemProfile[i].byPos = _player->inventoryManager.GetInventory()[sendCount].byPos;
			res.aItemProfile[i].byStackcount = _player->inventoryManager.GetInventory()[sendCount].byStackcount;
			res.aItemProfile[i].byRank = _player->inventoryManager.GetInventory()[sendCount].byRank;
			res.aItemProfile[i].byGrade = _player->inventoryManager.GetInventory()[sendCount].byGrade;
			res.aItemProfile[i].byCurDur = _player->inventoryManager.GetInventory()[sendCount].byCurDur;
			res.aItemProfile[i].byBattleAttribute = 0;			
			res.aItemProfile[i].byRestrictType = _player->inventoryManager.GetInventory()[sendCount].byRestrictType;
			res.aItemProfile[i].aOptionTblidx = _player->inventoryManager.GetInventory()[sendCount].aOptionTblidx;	
			res.aItemProfile[i].aOptionTblidx1 = _player->inventoryManager.GetInventory()[sendCount].aOptionTblidx1;
			for (int k = 0; k < 2; k++)
			{
				res.aItemProfile[i].aitemExtraEffect[k] = _player->inventoryManager.GetInventory()[sendCount].aitemExtraEffect[k];
			}
			for (int k = 0; k < 6; k++)
			{
				res.aItemProfile[i].aitemEffect[k] = _player->inventoryManager.GetInventory()[sendCount].aitemEffect[k];
			}
			for (int k = 0; k <= 16; k++)
				res.aItemProfile[i].awchMaker[k] = _player->inventoryManager.GetInventory()[sendCount].awchMaker[k];

			if (res.aItemProfile[i].byPlace == 7)
				_player->GetAttributesManager()->UpdateExtraAttributesFromItem(res.aItemProfile[i].aitemEffect);
			res.byItemCount = i + 1;			
		}
		res.byBeginCount = (sendCount - res.byItemCount);
		res.wPacketSize = (6 + (res.byItemCount * sizeof(sITEM_PROFILE)));
		
		SendPacket((char*)&res, sizeof(sGU_AVATAR_ITEM_INFO));
		if (_player->inventoryManager.GetInventory()[sendCount].tblidx == INVALID_TBLIDX)
			break;
	//	cout << "Tamanho Packet" << endl;
	//	std::cout << sizeof(sGU_AVATAR_ITEM_INFO) << std::endl;
	}
}
//----------------------------------------
//	Do we open or close the NPC window ?
//----------------------------------------
void WorldSession::SendShopRequest(Packet& packet, bool enter)
{
	if (enter == true)
	{
		sUG_SHOP_START_REQ *req = (sUG_SHOP_START_REQ*)packet.GetPacketBuffer();
		sGU_SHOP_START_RES res;

		res.wOpCode = GU_SHOP_START_RES;
		res.wPacketSize = sizeof(sGU_SHOP_START_RES) - 2;
		res.handle = req->handle;
		res.byType = req->NpcType;
		res.wResultCode = GAME_SUCCESS;

		SendPacket((char*)&res, sizeof(sGU_SHOP_START_RES));
	}
	else
	{
		sGU_SHOP_END_RES res;

		res.wOpCode = GU_SHOP_END_RES;
		res.wPacketSize = sizeof(sGU_SHOP_END_RES) - 2;
		res.wResultCode = GAME_SUCCESS;
		SendPacket((char*)&res, sizeof(sGU_SHOP_END_RES));
	}
}
//----------------------------------------
//	Change item location
//----------------------------------------
void WorldSession::SendItemMove(Packet& packet)
{
	sUG_ITEM_MOVE_REQ * req = (sUG_ITEM_MOVE_REQ*)packet.GetPacketBuffer();
	sGU_ITEM_MOVE_RES res;
	sGU_UPDATE_ITEM_EQUIP eq;

	res.wPacketSize = sizeof(sGU_ITEM_MOVE_RES) - 2;
	res.wOpCode = GU_ITEM_MOVE_RES;
	eq.wOpCode = GU_UPDATE_ITEM_EQUIP;
	eq.wPacketSize = sizeof(sGU_UPDATE_ITEM_EQUIP) - 2;
	res.hDestItem = -1;


	if (_player->GetInventoryManager()->MoveItem(*req, eq, res) == false)
	{
		res.wResultCode = GAME_MOVE_CANT_GO_THERE;
		sLog.outError("An error is occured in SendItemMoveReq: GAME_MOVE_CANT_GO_THERE");
	}
	else
	{
		res.wResultCode = GAME_SUCCESS;
	}
	res.wOpCode = GU_ITEM_MOVE_RES;
	res.bySrcPlace = req->bySrcPlace;
	res.bySrcPos = req->bySrcPos;
	res.byDestPlace = req->byDestPlace;
	res.byDestPos = req->byDestPos;
	if (req->byDestPlace == CONTAINER_TYPE_EQUIP || req->bySrcPlace == CONTAINER_TYPE_EQUIP)
		_player->SendToPlayerList((char*)&eq, sizeof(sGU_UPDATE_ITEM_EQUIP));
	SendPacket((char*)&res, sizeof(sGU_ITEM_MOVE_RES));
}
//----------------------------------------
//	Move a stack of item (from to)
//----------------------------------------
void WorldSession::SendItemMoveStack(Packet& packet)
{
	sUG_ITEM_MOVE_STACK_REQ* req = (sUG_ITEM_MOVE_STACK_REQ*)packet.GetPacketBuffer();
	sGU_ITEM_MOVE_STACK_RES res;
	sGU_ITEM_DELETE deletes;
	sGU_ITEM_CREATE created;

	memset(&created, INVALID_TBLIDX, sizeof(sGU_ITEM_CREATE));
	memset(&deletes, INVALID_TBLIDX, sizeof(sGU_ITEM_DELETE));
	memset(&res, INVALID_TBLIDX, sizeof(sGU_ITEM_MOVE_STACK_RES));

	res.wPacketSize = sizeof(sGU_ITEM_MOVE_STACK_RES) - 2;
	res.wOpCode = GU_ITEM_MOVE_STACK_RES;
	res.hDestItem = -1;
	deletes.wOpCode = GU_ITEM_DELETE;
	deletes.wPacketSize = sizeof(sGU_ITEM_DELETE) - 2;
	deletes.bySrcPlace = req->bySrcPlace;
	deletes.bySrcPos = req->bySrcPos;
	deletes.hSrcItem = -1;
	created.wOpCode = GU_ITEM_CREATE;
	created.wPacketSize = sizeof(sGU_ITEM_CREATE) - 2;
	created.handle = -1;
	created.bIsNew = true;
	if (_player->GetInventoryManager()->MoveItemStack(*req, res, deletes, created) == false)
	{
		res.wResultCode = GAME_MOVE_CANT_GO_THERE;
		sLog.outError("An error is occured in SendItemMoveStack: GAME_MOVE_CANT_GO_THERE");
	}
	else
	{
		res.wResultCode = GAME_SUCCESS;
	}
	res.byDestPlace = req->byDestPlace;
	res.byDestPos = req->byDestPos;
	res.bySrcPlace = req->bySrcPlace;
	res.bySrcPos = req->bySrcPos;
	SendPacket((char*)&res, sizeof(sGU_ITEM_MOVE_STACK_RES));
	if (deletes.hSrcItem != -1)
		SendPacket((char*)&deletes, sizeof(sGU_ITEM_DELETE));
	if (created.handle != -1)
		SendPacket((char*)&created, sizeof(sGU_ITEM_CREATE));
}
//----------------------------------------
//	Remove an item
//----------------------------------------
void WorldSession::SendRemoveItem(Packet& packet)
{ 
	sUG_ITEM_DELETE_REQ * req = (sUG_ITEM_DELETE_REQ*)packet.GetPacketBuffer();
	sGU_ITEM_DELETE deletes;
	sGU_ITEM_DELETE_RES deleted_item;

	deleted_item.wOpCode = GU_ITEM_DELETE_RES;
	deleted_item.wResultCode = GAME_SUCCESS;
	deleted_item.wPacketSize = sizeof(sGU_ITEM_DELETE_RES) - 2;

	deletes.wOpCode = GU_ITEM_DELETE;
	deletes.wPacketSize = sizeof(sGU_ITEM_DELETE) - 2;
	
	deletes.bySrcPlace = req->bySrcPlace;
	deletes.bySrcPos = req->bySrcPos;
	deleted_item.byPlace = req->bySrcPlace;
	deleted_item.byPos = req->bySrcPos;	

	_player->GetInventoryManager()->DeleteItem(req->bySrcPlace, req->bySrcPos, deletes.hSrcItem);

	SendPacket((char*)&deleted_item, sizeof(sGU_ITEM_DELETE_RES));
	SendPacket((char*)&deletes, sizeof(sGU_ITEM_DELETE));
}
//----------------------------------------
//	Send packet for created item
//----------------------------------------
void WorldSession::SendItemCreate(sITEM_PROFILE *createdItem)
{
	sGU_ITEM_CREATE create;

	create.wOpCode = GU_ITEM_CREATE;
	create.wPacketSize = sizeof(sGU_ITEM_CREATE) - 2;

	create.bIsNew = true;
	create.sItemData.unknown1 = 0;
	create.sItemData.unknown2 = 0;
	create.sItemData.unk = 0;
	//create.sItemData.handle = create.handle = createdItem->handle;

	for (int i = 0; i < 6; i++)
	{
		create.sItemData.aitemEffect[i].dwValue = createdItem->aitemEffect[i].dwValue;
		create.sItemData.aitemEffect[i].wType = createdItem->aitemEffect[i].wType;

	}
	for (int i = 0; i < 2; i++)
	{
		create.sItemData.aitemExtraEffect[i].dwValue = createdItem->aitemExtraEffect[i].dwValue;
		create.sItemData.aitemExtraEffect[i].wType = createdItem->aitemExtraEffect[i].wType;
	}
	for (int i = 0; i < 17; i++)
		create.sItemData.awchMaker[i] = createdItem->awchMaker[i];

	create.sItemData.bNeedToIdentify = false;
	create.sItemData.byBattleAttribute = createdItem->byBattleAttribute;
	create.sItemData.byCurrentDurability = createdItem->byCurDur;
	create.sItemData.byDurationType = createdItem->byDurationType;
	create.sItemData.byGrade = createdItem->byGrade;
	create.sItemData.byPlace = createdItem->byPlace;
	create.sItemData.byPosition = createdItem->byPos;
	create.sItemData.byRank = createdItem->byRank;
	create.sItemData.byRestrictType = createdItem->byRestrictType;
	create.sItemData.byStackcount = createdItem->byStackcount;
	create.sItemData.charId = _player->GetCharacterID();
	create.sItemData.itemId = createdItem->handle;
	create.sItemData.itemNo = createdItem->tblidx;

	create.sItemData.aOptionTblidx = createdItem->aOptionTblidx;
	create.sItemData.aOptionTblidx1 = INVALID_TBLIDX;

	SendPacket((char*)&create, sizeof(sGU_ITEM_CREATE));
}
//----------------------------------------
//	Send result from the buy we made 
//----------------------------------------
void WorldSession::SendShopBuy(Packet& packet)
{
	sUG_SHOP_BUY_REQ * req = (sUG_SHOP_BUY_REQ*)packet.GetPacketBuffer();
	sGU_SHOP_BUY_RES res;
	sITEM_TBLDAT* item = NULL;
	res.handle = _player->GetHandle();
	res.wOpCode = GU_SHOP_BUY_RES;
	res.wPacketSize = sizeof(sGU_SHOP_BUY_RES) - 2;
	res.wResultCode = GAME_SHOP_ITEM_INVALID;

	Npc* vendor = static_cast<Npc*>(_player->GetFromList(req->handle));
	if (vendor == NULL)
	{
		sLog.outError("Error npc is nill");
		return;
	}
	int itemamount = 0;
	DWORD cost = 0;
	for (int k = 0; k < req->byBuyCount; k++)
	{
		printf("handle %d \n", req->handle);
		printf("byMerchantTab %d \n", req->sBuyData[k].byMerchantTab);
		printf("byItemPos %d \n", req->sBuyData[k].byItemPos);
		printf("byStack %d \n", req->sBuyData[k].byStack);
		sMERCHANT_TBLDAT* merchant = (sMERCHANT_TBLDAT*)sTBM.GetMerchantTable()->FindData(vendor->GetNpcData().amerchant_Tblidx[req->sBuyData[k].byMerchantTab]);
		if (merchant != NULL && merchant->bySell_Type == MERCHANT_SELL_TYPE_ITEM)
		{
			for (int j = 0; j < MAX_MERCHANT_COUNT; j++)
			{
				if ((item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(merchant->aitem_Tblidx[j])) == NULL)
				{
					item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(merchant->aitem_Tblidx[j]);
				}
				if (item != NULL && j == req->sBuyData[k].byItemPos)
				{
					
					itemamount++;
					cost += item->dwCost * req->sBuyData[k].byStack;
				}
			}
		}
		else
		{
			sLog.outError("Error merchant is null");
		}
	}
	if (itemamount > _player->GetInventoryManager()->GetTotalFreeSpaceInBag())
	{
		res.wResultCode = GAME_ITEM_INVEN_FULL;
	}
	else if (_player->GetPcProfile()->dwZenny < cost)
	{
		res.wResultCode = GAME_ITEM_RECIPE_CANNOT_SET_YOU_NEED_MORE_ZENNY;
	}
	else
	{
		_player->UpdateZennyAmount((cost * -1), eZENNY_CHANGE_TYPE::ZENNY_CHANGE_TYPE_ITEM_BUY);

		for (int k = 0; k < req->byBuyCount; k++)
		{
			sMERCHANT_TBLDAT* merchant = (sMERCHANT_TBLDAT*)sTBM.GetMerchantTable()->FindData(vendor->GetNpcData().amerchant_Tblidx[req->sBuyData[k].byMerchantTab]);
			if (merchant != NULL && merchant->bySell_Type == MERCHANT_SELL_TYPE_ITEM)
			{
				for (int j = 0; j < MAX_MERCHANT_COUNT; j++)
				{
					if (j == req->sBuyData[k].byItemPos)
					{
						sITEM_PROFILE createdItem;
						res.wResultCode = _player->GetInventoryManager()->PerformShopBuy(merchant->aitem_Tblidx[j], req->sBuyData[k].byStack, createdItem);
						if (res.wResultCode == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
						{
							SendItemCreate(&createdItem);
						}
						else
						{
							break; // force interupt Loop
						}
					}
				}
			}
			else if (merchant != NULL && merchant->bySell_Type == MERCHANT_SELL_TYPE_GAMBLE)
			{
				sLog.outDebug("GAMBLE merchant.");
			}
			else if (merchant != NULL && merchant->bySell_Type == MERCHANT_SELL_TYPE_BUDOKAI)
			{
				sLog.outDebug("BUDOKAI merchant.");
			}
			else
			{
				sLog.outDebug("merchant->bySell_Type not recognize: %u merchant.", merchant->bySell_Type);
			}
		}
	}
	SendPacket((char*)&res, sizeof(sGU_SHOP_BUY_RES));
}
void WorldSession::SendShopEventBuy(Packet& packet)
{
	sUG_SHOP_EVENTITEM_BUY_REQ * req = (sUG_SHOP_EVENTITEM_BUY_REQ*)packet.GetPacketBuffer();
	sGU_SHOP_EVENTITEM_BUY_RES res;

	res.handle = _player->GetHandle();
	res.wOpCode = GU_SHOP_EVENTITEM_BUY_RES;
	res.wPacketSize = sizeof(sGU_SHOP_EVENTITEM_BUY_RES) - 2;
	res.wResultCode = GAME_SHOP_ITEM_INVALID;

	Npc* vendor = static_cast<Npc*>(_player->GetFromList(req->handle));
	if (vendor == NULL)
	{
		sLog.outError("Error npc is nill");
		return;
	}
	int itemamount = 0;
	DWORD cost = 0;
	for (int k = 0; k < req->byBuyCount; k++)
	{
		sMERCHANT_TBLDAT* merchant = (sMERCHANT_TBLDAT*)sTBM.GetMerchantTable()->FindData(vendor->GetNpcData().amerchant_Tblidx[req->sBuyData[k].byMerchantTab]);
		if (merchant != NULL && merchant->bySell_Type == MERCHANT_SELL_TYPE_ITEM)
		{
			for (int j = 0; j < MAX_MERCHANT_COUNT; j++)
			{
				sITEM_TBLDAT* item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(merchant->aitem_Tblidx[j]);
				if (item != NULL && j == req->sBuyData[k].byItemPos)
				{

					itemamount++;
					cost += item->dwCost * req->sBuyData[k].byStack;
				}
			}
		}
	}
	if (itemamount > _player->GetInventoryManager()->GetTotalFreeSpaceInBag())
	{
		res.wResultCode = GAME_ITEM_INVEN_FULL;
	}
	else if (_player->GetPcProfile()->dwZenny < cost)
	{
		res.wResultCode = GAME_ITEM_RECIPE_CANNOT_SET_YOU_NEED_MORE_ZENNY;
	}
	else
	{
		_player->UpdateZennyAmount((cost * -1), eZENNY_CHANGE_TYPE::ZENNY_CHANGE_TYPE_ITEM_BUY);

		for (int k = 0; k < req->byBuyCount; k++)
		{
			sMERCHANT_TBLDAT* merchant = (sMERCHANT_TBLDAT*)sTBM.GetMerchantTable()->FindData(vendor->GetNpcData().amerchant_Tblidx[req->sBuyData[k].byMerchantTab]);
			if (merchant != NULL && merchant->bySell_Type == MERCHANT_SELL_TYPE_ITEM)
			{
				for (int j = 0; j < MAX_MERCHANT_COUNT; j++)
				{
					if (j == req->sBuyData[k].byItemPos)
					{
						sITEM_PROFILE createdItem;
						res.wResultCode = _player->GetInventoryManager()->PerformShopBuy(merchant->aitem_Tblidx[j], req->sBuyData[k].byStack, createdItem);
						if (res.wResultCode == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
						{
							SendItemCreate(&createdItem);
						}
						else
						{
							break; // force interupt Loop
						}
					}
				}
			}
			else if (merchant != NULL && merchant->bySell_Type == MERCHANT_SELL_TYPE_GAMBLE)
			{
				sLog.outDebug("GAMBLE merchant.");
			}
			else if (merchant != NULL && merchant->bySell_Type == MERCHANT_SELL_TYPE_BUDOKAI)
			{
				sLog.outDebug("BUDOKAI merchant.");
			}
			else
			{
				sLog.outDebug("merchant->bySell_Type not recognize: %u merchant.", merchant->bySell_Type);
			}
		}
	}
	SendPacket((char*)&res, sizeof(sGU_SHOP_EVENTITEM_BUY_RES));
}
void WorldSession::SendShopItemChange(Packet& packet)
{
	sUG_ITEM_EXCHANGE_REQ * req = (sUG_ITEM_EXCHANGE_REQ*)packet.GetPacketBuffer();
	sGU_SHOP_BUY_RES res;
	sITEM_TBLDAT* item = NULL;
	sMERCHANT_TBLDAT* merchant = NULL;
	res.handle = _player->GetHandle();
	res.wOpCode = GU_SHOP_BUY_RES;
	res.wPacketSize = sizeof(sGU_SHOP_BUY_RES) - 2;
	res.wResultCode = GAME_SUCCESS;
	Npc* vendor = static_cast<Npc*>(_player->GetFromList(req->handle));
	if (vendor == NULL)
	{
		sLog.outError("Error npc is nill");
		return;
	}	
	//sMERCHANT_TBLDAT* merchant = (sMERCHANT_TBLDAT*)sTBM.GetMerchantTable()->FindData(vendor->GetNpcData().amerchant_Tblidx[req->sBuyData.byMerchantTab]);
	int tab = req->sBuyData.byMerchantTab;
	if (vendor->GetNpcData().amerchant_Tblidx[req->sBuyData.byMerchantTab] == 11891)
	{
		tab = 1;
	}
	if (vendor->GetNpcData().amerchant_Tblidx[req->sBuyData.byMerchantTab] == 11892)
	{
		tab = 0;
	}

	if ((merchant = (sMERCHANT_TBLDAT2*)sTBM.GetMerchantTable2()->FindData(vendor->GetNpcData().amerchant_Tblidx[tab])) == NULL)
	{
		merchant = (sMERCHANT_TBLDAT*)sTBM.GetMerchantTable()->FindData(vendor->GetNpcData().amerchant_Tblidx[tab]);
	}
	if (merchant != NULL)
	{
		printf("amerchant_Tblidx %d \n", vendor->GetNpcData().amerchant_Tblidx[tab]);
		printf("tab %d \n", tab);
		if ((item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(merchant->aitem_Tblidx[req->sBuyData.byItemPos])) == NULL)
		{
			item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(merchant->aitem_Tblidx[req->sBuyData.byItemPos]);
		}
		if (item != NULL)
		{
			sITEM_PROFILE createdItem;
			res.wResultCode = _player->GetInventoryManager()->PerformShopBuy(merchant->aitem_Tblidx[req->sBuyData.byItemPos], req->sBuyData.byStack, createdItem);
			if (createdItem.tblidx != INVALID_TBLIDX)
			{
				SendItemCreate(&createdItem);
			}
		}			
	}
	SendPacket((char*)&res, sizeof(sGU_SHOP_BUY_RES));
}
//----------------------------------------
//	Send the result from our selling, add zenny etc
//----------------------------------------
void WorldSession::SendShopSell(Packet& packet)
{
	sUG_SHOP_SELL_REQ *req = (sUG_SHOP_SELL_REQ*)packet.GetPacketBuffer();
	sGU_SHOP_SELL_RES res;
	sGU_ITEM_DELETE itmDelete;
	sGU_ITEM_STACK_UPDATE stackUpd;

	res.handle = _player->GetHandle();
	res.wOpCode = GU_SHOP_SELL_RES;
	res.wPacketSize = sizeof(sGU_SHOP_SELL_RES) - 2;

	itmDelete.wOpCode = GU_ITEM_DELETE;
	itmDelete.wPacketSize = sizeof(sGU_ITEM_DELETE) - 2;

	stackUpd.wOpCode = GU_ITEM_STACK_UPDATE;
	stackUpd.wPacketSize = sizeof(sGU_ITEM_STACK_UPDATE) - 2;

	for (int i = 0; i < req->bySellCount; i++)
	{
		sITEM_PROFILE*itm = _player->GetInventoryManager()->GetItemAtPlaceAndPost(req->sSellData[i].byPlace, req->sSellData[i].byPos);
		if (itm != NULL)
		{
			sITEM_TBLDAT* pItemData = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(itm->tblidx);
			if (pItemData != NULL)
			{
				int zenit_amount = pItemData->tbxSellPrice * req->sSellData[i].byStack;
				_player->UpdateZennyAmount(zenit_amount, eZENNY_CHANGE_TYPE::ZENNY_CHANGE_TYPE_ITEM_SELL);

				if (itm->byStackcount == req->sSellData[i].byStack)
				{
					itmDelete.bySrcPlace = itm->byPlace;
					itmDelete.bySrcPos = itm->byPos;
					itmDelete.hSrcItem = itm->handle;
					SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
					itm->byPlace = INVALID_TBLIDX;
					itm->byPos = INVALID_TBLIDX;
					itm->tblidx = INVALID_TBLIDX;
				}
				else if (itm->byStackcount > req->sSellData[i].byStack)
				{
					stackUpd.bIsNew = false;
					stackUpd.byStack = itm->byStackcount - req->sSellData[i].byStack;
					itm->byStackcount = stackUpd.byStack;
					stackUpd.hItemHandle = itm->handle;
					SendPacket((char*)&stackUpd, sizeof(sGU_ITEM_STACK_UPDATE));
				}
			}
		}
	}
	res.wResultCode = GAME_SUCCESS;
	SendPacket((char*)&res, sizeof(sGU_SHOP_SELL_RES));
}
//----------------------------------------
//	Send the result of a pickup
//----------------------------------------
void WorldSession::SendPickUp(HOBJECT handle)
{
	DroppedObject* dropped = _player->GetPickupData(handle);
	if (dropped == NULL)
	{
		// try to duplicate object by clicking fast on item
		// or simply lag
		return;
	}
	switch (dropped->objType)
	{
		case eOBJTYPE::OBJTYPE_DROPITEM:
		{
			sGU_ITEM_PICK_RES res;
			res.wOpCode = GU_ITEM_PICK_RES;
			res.wPacketSize = sizeof(sGU_ITEM_PICK_RES) - 2;
			res.wResultCode = ResultCodes::GAME_SUCCESS;

			res.bByPartyHunting = false;
			res.itemTblidx = dropped->item.Handle;

			SendPacket((char*)&res, sizeof(sGU_ITEM_PICK_RES));
			if (_player->GetInventoryManager()->IsInventoryFull() == false)
			{
				sITEM_PROFILE *data = _player->inventoryManager.CreateNewItem(dropped->item.Tblidx, 1);
				if (data != NULL)
				{
					SendItemCreate(data);
					_player->RemoveDropFromList(handle);
				}
			}
			break;
		}
		case eOBJTYPE::OBJTYPE_DROPMONEY:
		{
			sGU_ZENNY_PICK_RES res;
			res.wOpCode = GU_ZENNY_PICK_RES;
			res.wPacketSize = sizeof(sGU_ZENNY_PICK_RES) - 2;
			res.wResultCode = ResultCodes::GAME_SUCCESS;

			res.bSharedInParty = false;
			res.dwBonusZenny = 0;
			res.dwAcquisitionZenny = dropped->zenny.dwZenny + res.dwBonusZenny;
			res.dwOriginalZenny = dropped->zenny.dwZenny;
			res.dwZenny = res.dwAcquisitionZenny;
			
			SendPacket((char*)&res, sizeof(sGU_ZENNY_PICK_RES));

			_player->UpdateZennyAmount(res.dwAcquisitionZenny, eZENNY_CHANGE_TYPE::ZENNY_CHANGE_TYPE_PICK);
			_player->RemoveDropFromList(handle);
			break;
		}
		default:
			break;
	}
}

void WorldSession::SendUpdateCharZenny(DWORD amount, eZENNY_CHANGE_TYPE zennyType, HOBJECT handle, bool bIsNew)
{
	sGU_UPDATE_CHAR_ZENNY zenny;
	zenny.wOpCode = GU_UPDATE_CHAR_ZENNY;
	zenny.wPacketSize = sizeof(sGU_UPDATE_CHAR_ZENNY) - 2;

	zenny.bIsNew = bIsNew;
	zenny.byChangeType = zennyType;
	zenny.handle = handle;
	zenny.dwZenny = amount;

	SendPacket((char*)&zenny, sizeof(sGU_UPDATE_CHAR_ZENNY));
}

void WorldSession::SendUpdateCharExp(DWORD expAmount, DWORD bonus, HOBJECT handle, DWORD curExp)
{
	sGU_UPDATE_CHAR_EXP expPacket;

	expPacket.dwIncreasedExp = expAmount + bonus;
	expPacket.dwAcquisitionExp = expAmount;
	expPacket.dwBonusExp = bonus;
	expPacket.wOpCode = GU_UPDATE_CHAR_EXP;
	expPacket.wPacketSize = sizeof(sGU_UPDATE_CHAR_EXP) - 2;
	expPacket.handle = handle;
	expPacket.dwCurExp = curExp;

	SendPacket((char*)&expPacket, sizeof(sGU_UPDATE_CHAR_EXP));
}