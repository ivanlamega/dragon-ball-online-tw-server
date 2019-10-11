#ifndef __INVENTORY_H
#define __INVENTORY_H

#pragma once

#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <TableAll.h>

class Player;
class Npc;

class InventoryManager
{
public:
	InventoryManager();
	~InventoryManager();

	bool				LoadInventory(CHARACTERID _id, Player *_plr);
	void				SaveInventory();
	BYTE				GetTotalItemsCount() { return ItemsCount; }
	sITEM_PROFILE*		GetInventory() { return ItemProfile; }
	sITEM_BRIEF*		GetEquippedItems() { return ItemBrief; }
	sITEM_DATA*			GettradedItems() { return TradeInventory; }

	bool				MoveItem(sUG_ITEM_MOVE_REQ& request, sGU_UPDATE_ITEM_EQUIP& result, sGU_ITEM_MOVE_RES& itemMoveRes);
	bool				MoveItemStack(sUG_ITEM_MOVE_STACK_REQ& request, sGU_ITEM_MOVE_STACK_RES& result, sGU_ITEM_DELETE& deletes, sGU_ITEM_CREATE& created);
	sITEM_PROFILE *     CreateCashItem(sCASHITEM_TBLDAT & item, int stack = 1);
	void				DeleteItem(BYTE byPlace, BYTE byPosition, HOBJECT& hItem);

	// CREATE NEW ITEM
	ResultCodes			PerformShopBuy(TBLIDX item, int amount, sITEM_PROFILE& createdReference);

	sITEM_PROFILE		*CreateNewItem(TBLIDX item, int stack = 1);
	sITEM_PROFILE		*CreateBag(TBLIDX item, int stack = 1);
	sITEM_PROFILE		*CreateItem(sITEM_TBLDAT& item, int stack = 1);
	sITEM_PROFILE		*GetItemAtPlaceAndPost(BYTE place, BYTE pos);
	sITEM_PROFILE		*GetItemByTblidx(TBLIDX Item);
	sITEM_PROFILE		*GetItemByHandle(HOBJECT Handle);
	sITEM_DATA			*AddTradeList(sITEM_DATA Trade);
	sITEM_DATA			*TradeList(sITEM_DATA Trade);
	ResultCodes			GetFreeBagPlaceAndSlot(BYTE* Place, BYTE* Pos);
	ResultCodes			GetFreeBagSlot(BYTE* Place, BYTE* Pos);

	// LOGIC
	bool				IsInventoryFull();
	int					GetTotalFreeSpaceInBag();
private:
	bool				LoadCharInventoryFromDatabase();
	ResultCodes			GetFirstFreeBag(BYTE& Place, BYTE& Postition);
	BYTE				GetFirstFreePosInBag(BYTE Bag, SLOTID slot);

	CHARACTERID			charid;
	Player*				plr;
	// INVENTORY
	BYTE				ItemsCount;
	sITEM_PROFILE		ItemProfile[MAX_COUNT_USER_HAVE_INVEN_ITEM];
	sITEM_BRIEF			ItemBrief[EQUIP_SLOT_TYPE_COUNT];
	BYTE				TradeItemCount = 0;
	sITEM_DATA          TradeInventory[12];
};

#endif