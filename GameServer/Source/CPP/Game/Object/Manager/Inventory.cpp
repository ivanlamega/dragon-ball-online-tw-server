#include <Game\Object\Manager\Inventory.h>
#include <Game\Object\Player.h>
#include <Game\Object\Npc.h>
#include <WorldSession.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>

//----------------------------------------
//	Constructor
//----------------------------------------
InventoryManager::InventoryManager()
{

}
//----------------------------------------
//	Destructor
//----------------------------------------
InventoryManager::~InventoryManager()
{

}
//----------------------------------------
//	Load our inventory
//----------------------------------------
bool InventoryManager::LoadInventory(CHARACTERID _id, Player *_plr)
{
	charid = _id;

	if (LoadCharInventoryFromDatabase() == false)
	{
		sLog.outError("InventoryManager::LoadInventory Error while loading character: %d", charid);
		return false;
	}
	plr = _plr;
	return true;
}
//----------------------------------------
//	Save our inventory
//----------------------------------------
void InventoryManager::SaveInventory()
{
	sql::ResultSet* result = sDB.executes("DELETE FROM `items` WHERE `owner_id` = '%d';", charid);
	if (result != NULL)
		delete result;
	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		sITEM_TBLDAT* item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(ItemProfile[i].tblidx);
		if (item == NULL)
		{
			item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(ItemProfile[i].tblidx);
		}
		if (ItemProfile[i].tblidx != INVALID_TBLIDX && ItemProfile[i].tblidx > 0 && item != NULL)
		{
			sDB.AddItem(ItemProfile[i].tblidx, charid, ItemProfile[i].byPlace, ItemProfile[i].byPos, ItemProfile[i].byStackcount, ItemProfile[i].byRank, ItemProfile[i].byCurDur, ItemProfile[i].byGrade, ItemProfile[i].aitemEffect[0].wType, ItemProfile[i].aitemEffect[0].dwValue,
				ItemProfile[i].aitemEffect[1].wType, ItemProfile[i].aitemEffect[1].dwValue, ItemProfile[i].aitemEffect[2].wType, ItemProfile[i].aitemEffect[2].dwValue,
				ItemProfile[i].aitemEffect[3].wType, ItemProfile[i].aitemEffect[3].dwValue, ItemProfile[i].aitemEffect[4].wType, ItemProfile[i].aitemEffect[4].dwValue,
				ItemProfile[i].aitemEffect[5].wType, ItemProfile[i].aitemEffect[5].dwValue);
		}
	}
}
//----------------------------------------
//	Load function
//----------------------------------------
bool InventoryManager::LoadCharInventoryFromDatabase()
{
	size_t i = 0;

	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++) memset(&ItemProfile[i], INVALID_TBLIDX, sizeof(sITEM_PROFILE));
	for (int i = 0; i < 17; i++) memset(&ItemBrief[i], INVALID_TBLIDX, sizeof(sITEM_BRIEF));

	sql::ResultSet* result = sDB.executes("SELECT * FROM items WHERE owner_id = '%d' ORDER BY place ASC, pos ASC;", charid);
	//sql::ResultSet* result2 = sDB.executes("SELECT * FROM itematributes WHERE owner_id = '%d';", charid);
	if (result == NULL)
		return false;
	if (result->rowsCount() <= 0)
	{
		delete result;		
		return false;
	}	
	while (true)
	{
		sITEM_TBLDAT* item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(result->getInt("tblidx"));
		if (item == NULL)
		{
			item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(result->getInt("tblidx"));
		}
		if (item != NULL && item->tblidx != 0)
		{
			ItemProfile[i].handle = sWorld.AcquireItemSerialId();//result->getInt("id");
			ItemProfile[i].tblidx = result->getInt("tblidx");
			ItemProfile[i].byPlace = static_cast<BYTE>(result->getInt("place"));
			ItemProfile[i].byPos = static_cast<BYTE>(result->getInt("pos"));
			ItemProfile[i].byStackcount = static_cast<BYTE>(result->getInt("count"));
			ItemProfile[i].byRank = static_cast<BYTE>(result->getInt("rank"));
			ItemProfile[i].byGrade = static_cast<BYTE>(result->getInt("grade"));
			ItemProfile[i].byCurDur = static_cast<BYTE>(result->getInt("durability"));
			ItemProfile[i].byDurationType = eDURATIONTYPE::eDURATIONTYPE_NORMAL;
			ItemProfile[i].byBattleAttribute = static_cast<BYTE>(result->getInt("battleAttribute"));
			ItemProfile[i].bNeedToIdentify = false;
			ItemProfile[i].nUseEndTime = 0;
			ItemProfile[i].nUseStartTime = 0;

			ItemProfile[i].byRestrictType = eITEM_RESTRICT_TYPE::ITEM_RESTRICT_TYPE_NONE;// item->unknownStruct.unknown14;
			
			ItemProfile[i].aOptionTblidx = item->tbxItemOption;//result->getInt("tblidx");// item->Item_Option_Tblidx;
			ItemProfile[i].aOptionTblidx1 = INVALID_TBLIDX;// item->Item_Option_Tblidx;
			
			if (result->getInt("AtributeType1") == 0 || result->getInt("AtributeValue1") == INVALID_TBLIDX)
			{
				ItemProfile[i].aitemEffect[0].dwValue = INVALID_TBLIDX;// 8;
				ItemProfile[i].aitemEffect[0].wType = INVALID_TBLIDX;
			}
			else
			{
				ItemProfile[i].aitemEffect[0].dwValue = result->getInt("AtributeValue1");// 8;
				ItemProfile[i].aitemEffect[0].wType = result->getInt("AtributeType1");
			}
			if (result->getInt("AtributeType2") == 0 || result->getInt("AtributeValue2") == INVALID_TBLIDX)
			{
				ItemProfile[i].aitemEffect[1].dwValue = INVALID_TBLIDX;// 8;
				ItemProfile[i].aitemEffect[1].wType = INVALID_TBLIDX;
			}
			else
			{
				ItemProfile[i].aitemEffect[1].dwValue = result->getInt("AtributeValue2");// 8;
				ItemProfile[i].aitemEffect[1].wType = result->getInt("AtributeType2");
			}
			if (result->getInt("AtributeType3") == 0 || result->getInt("AtributeValue3") == INVALID_TBLIDX)
			{
				ItemProfile[i].aitemEffect[2].dwValue = INVALID_TBLIDX;// 8;
				ItemProfile[i].aitemEffect[2].wType = INVALID_TBLIDX;
			}
			else
			{
				ItemProfile[i].aitemEffect[2].dwValue = result->getInt("AtributeValue3");// 8;
				ItemProfile[i].aitemEffect[2].wType = result->getInt("AtributeType3");
			}
			if (result->getInt("AtributeType4") == 0 || result->getInt("AtributeValue4") == INVALID_TBLIDX)
			{
				ItemProfile[i].aitemEffect[3].dwValue = INVALID_TBLIDX;// 8;
				ItemProfile[i].aitemEffect[3].wType = INVALID_TBLIDX;
			}
			else
			{
				ItemProfile[i].aitemEffect[3].dwValue = result->getInt("AtributeValue4");// 8;
				ItemProfile[i].aitemEffect[3].wType = result->getInt("AtributeType4");
			}
			if (result->getInt("AtributeType5") == 0 || result->getInt("AtributeValue5") == INVALID_TBLIDX)
			{
				ItemProfile[i].aitemEffect[4].dwValue = INVALID_TBLIDX;// 8;
				ItemProfile[i].aitemEffect[4].wType = INVALID_TBLIDX;
			}
			else
			{
				ItemProfile[i].aitemEffect[4].dwValue = result->getInt("AtributeValue5");// 8;
				ItemProfile[i].aitemEffect[4].wType = result->getInt("AtributeType5");
			}
			if (result->getInt("AtributeType6") == 0 || result->getInt("AtributeValue6") == INVALID_TBLIDX)
			{
				ItemProfile[i].aitemEffect[5].dwValue = INVALID_TBLIDX;// 8;
				ItemProfile[i].aitemEffect[5].wType = INVALID_TBLIDX;
			}
			else
			{
				ItemProfile[i].aitemEffect[5].dwValue = result->getInt("AtributeValue6");// 8;
				ItemProfile[i].aitemEffect[5].wType = result->getInt("AtributeType6");
			}
			for (int j = 0; j < 2; j++)
			{
				ItemProfile[i].aitemExtraEffect[j].dwValue = INVALID_TBLIDX;// 8;
				ItemProfile[i].aitemExtraEffect[j].wType = INVALID_WORD;// j + 1;
			}
			for (int j = 0; j < 17; j++)
			{
				ItemProfile[i].awchMaker[j] = 0;
			}
			if (ItemProfile[i].byPlace == CONTAINER_TYPE_EQUIP)
			{
				ItemBrief[ItemProfile[i].byPos].tblidx = result->getInt("tblidx");
				ItemBrief[ItemProfile[i].byPos].byGrade = ItemProfile[i].byGrade;
				ItemBrief[ItemProfile[i].byPos].byRank = ItemProfile[i].byRank;
				ItemBrief[ItemProfile[i].byPos].byBattleAttribute = ItemProfile[i].byBattleAttribute;				
			}
			i++;
			if (result->next())
				continue;
			else
				break;		
		}
	}
	ItemsCount = i;
	delete result;
	//delete result2;
	return true;
}
//----------------------------------------
//	Check eligibility of slot
//----------------------------------------
bool InventoryManager::MoveItem(sUG_ITEM_MOVE_REQ& request, sGU_UPDATE_ITEM_EQUIP& result, sGU_ITEM_MOVE_RES& itemMoveRes)
{
	sITEM_PROFILE *source = NULL;
	sITEM_PROFILE *dest = NULL;
	sITEM_PROFILE tmp = { 0 };

	sITEM_TBLDAT *itemSrc = NULL;
	sITEM_TBLDAT *itemDest = NULL;

	if ((source = GetItemAtPlaceAndPost(request.bySrcPlace, request.bySrcPos)) == NULL)
		return false;
	if ((dest = GetItemAtPlaceAndPost(request.byDestPlace, request.byDestPos)) != NULL)
	{
		if ((itemDest = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(dest->tblidx)) == NULL)
		{
			itemDest = (sCASHITEM_TBLDAT *)sTBM.GetCashItemTable()->FindData(dest->tblidx);
		}
		if (itemDest ==NULL)
			return false;
	}
	if ((itemSrc = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(source->tblidx)) == NULL)
	{
		itemSrc = (sCASHITEM_TBLDAT *)sTBM.GetCashItemTable()->FindData(source->tblidx);
		if (itemSrc == NULL)
			return false;
	}	

	if (request.byDestPlace == CONTAINER_TYPE_EQUIP)
	{
		sITEM_TBLDAT* item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(GetItemAtPlaceAndPost(request.bySrcPlace, request.bySrcPos)->tblidx);
		if (item == NULL)
		{
			item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(GetItemAtPlaceAndPost(request.bySrcPlace, request.bySrcPos)->tblidx);
		}
		if (item != NULL)
		{
			if (plr->GetPcProfile()->byLevel < item->byNeedLevel)
				return false;

		/*	DWORD myFlag;
			// if we have double spec
			// (0x01 << 0) | (0x01 << plr->GetMyClass());
			myFlag = plr->GetClassFlag(plr->GetMyClass(), item->eItemType);
			sLog.outDetail("My flag: %d on class: %d", myFlag, item->dwNeedClassBitFlag);
			if (myFlag & ~item->dwNeedClassBitFlag)
			{
				//sLog.outDebug("Special class: %u, need class: %d", item->byClass_Special, item->dwNeed_Class_Bit_Flag);
				return false;
			}*/
			//else
				//sLog.outString("Special class: %u, need class: %d is ok", item->byClass_Special, item->dwNeed_Class_Bit_Flag);
		}
	}
	result.handle = plr->GetHandle();
	result.sItemBrief.byGrade = source->byGrade;
	itemMoveRes.hSrcItem = source->handle;

	if (request.byDestPlace >= CONTAINER_TYPE_BAG1 && request.byDestPlace <= CONTAINER_TYPE_BAG5) // CHECK IN BAG
	{
		if (dest != NULL) // there is item on bag at pos
		{
			if (request.bySrcPlace == CONTAINER_TYPE_EQUIP) // move item from equipped to bag and swap them
			{
				itemMoveRes.hDestItem = dest->handle;
				plr->GetAttributesManager()->UpdateAttributesFromItem(*itemSrc,source->byGrade, true);
				plr->GetAttributesManager()->UpdateAttributesFromItem(*itemDest, dest->byGrade);
				plr->GetAttributesManager()->UpdateExtraAttributesFromItem(source->aitemEffect, true);
				plr->GetAttributesManager()->UpdateExtraAttributesFromItem(dest->aitemEffect);
				tmp.byPos = source->byPos;
				tmp.byPlace = source->byPlace;
				source->byPlace = dest->byPlace;
				source->byPos = dest->byPos;
				dest->byPos = tmp.byPos;
				dest->byPlace = tmp.byPlace;

				result.byPos = dest->byPos;
				result.sItemBrief.tblidx = itemDest->tblidx;
				ItemBrief[request.byDestPos].tblidx = itemSrc->tblidx;
			}
			else if (request.byDestPlace == source->byPlace) // swap bag item
			{
				itemMoveRes.hDestItem = dest->handle;
				
				tmp.byPos = source->byPos;
				tmp.byPlace = source->byPlace;
				source->byPlace = dest->byPlace;
				source->byPos = dest->byPos;
				dest->byPos = tmp.byPos;
				dest->byPlace = tmp.byPlace;

				result.byPos = dest->byPos;
				result.sItemBrief.tblidx = dest->tblidx;
			}
			else
			{
				//sLog.outDebug("understand the voodoo in action");
				return false;
			}
		}
		else // no item we can simply move it
		{
			if (request.bySrcPlace == CONTAINER_TYPE_EQUIP) // we move an equipped item to bag
			{
				source->byPlace = request.byDestPlace;
				source->byPos = request.byDestPos;
				result.sItemBrief.tblidx = INVALID_TBLIDX;
				result.byPos = request.bySrcPos;
				plr->GetAttributesManager()->UpdateAttributesFromItem(*itemSrc, source->byGrade, true);
				plr->GetAttributesManager()->UpdateExtraAttributesFromItem(source->aitemEffect, true);
				ItemBrief[request.bySrcPos].tblidx = INVALID_TBLIDX;
			}
			else
			{
				result.byPos = request.byDestPos;
				result.sItemBrief.tblidx = source->tblidx;
				source->byPlace = request.byDestPlace;
				source->byPos = request.byDestPos;
			}
		}
	}
	else if (request.byDestPlace == CONTAINER_TYPE_EQUIP) // check equiped
	{
		if (dest != NULL) // there is a item at equipped slot
		{			
			itemMoveRes.hDestItem = dest->handle;
			plr->GetAttributesManager()->UpdateAttributesFromItem(*itemDest, dest->byGrade, true);
			plr->GetAttributesManager()->UpdateAttributesFromItem(*itemSrc,source->byGrade);
			plr->GetAttributesManager()->UpdateExtraAttributesFromItem(dest->aitemEffect, true);
			plr->GetAttributesManager()->UpdateExtraAttributesFromItem(source->aitemEffect);

			tmp.byPos = source->byPos;
			tmp.byPlace = source->byPlace;
			source->byPlace = dest->byPlace;
			source->byPos = dest->byPos;
			dest->byPos = tmp.byPos;
			dest->byPlace = tmp.byPlace;

			result.byPos = request.byDestPos;
			result.sItemBrief.tblidx = itemSrc->tblidx;
			ItemBrief[request.byDestPos].tblidx = itemSrc->tblidx;
		}
		else if (dest == NULL) // no equipped item move item to slot
		{			
			if (request.bySrcPlace == CONTAINER_TYPE_EQUIP) // wtf ?
			{
				return false;
			}
			else // move bag to equipped free slot
			{
				result.byPos = request.byDestPos;
				result.sItemBrief.tblidx = source->tblidx;
				source->byPlace = request.byDestPlace;
				source->byPos = request.byDestPos;
				plr->GetAttributesManager()->UpdateAttributesFromItem(*itemSrc, source->byGrade);
				plr->GetAttributesManager()->UpdateExtraAttributesFromItem(source->aitemEffect);
				ItemBrief[request.byDestPos].tblidx = itemSrc->tblidx;
			}
		}
		else
			return false;
	}
	else if (request.byDestPlace == CONTAINER_TYPE_BAGSLOT) // add new bag
	{
		if (dest != NULL) // automatic return false, need a free slot
		{
			return false;
		}
		else
		{
			source->byPlace = request.byDestPlace;
			source->byPos = request.byDestPos;
		}
	}
	else
		return false;
	return true;
}
//----------------------------------------
//	Check eligibility of stack slot
//----------------------------------------
bool InventoryManager::MoveItemStack(sUG_ITEM_MOVE_STACK_REQ& request, sGU_ITEM_MOVE_STACK_RES& result, sGU_ITEM_DELETE& deletes, sGU_ITEM_CREATE& created)
{
	sITEM_PROFILE *source = NULL;
	sITEM_PROFILE *dest = NULL;

	sITEM_TBLDAT *itemSrc = NULL;
	BYTE overStack = 0;

	source = GetItemAtPlaceAndPost(request.bySrcPlace, request.bySrcPos);
	dest = GetItemAtPlaceAndPost(request.byDestPlace, request.byDestPos);
	if (source == NULL)
		return false;
	itemSrc = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(source->tblidx);
	
	if (itemSrc == NULL)
	{
		itemSrc = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(source->tblidx);
		if (itemSrc == NULL)
		{
			return false;
		}
	}
	if (dest == NULL)
	{
		dest = CreateItem(*itemSrc);
		if (dest == NULL)
			return false;
		dest->byPlace = request.byDestPlace;
		dest->byPos = request.byDestPos;
		dest->byStackcount = 0;
		created.handle = dest->handle;
		created.sItemData.charId = charid;
	}
	if (itemSrc->tblidx != dest->tblidx)
		return false;

	if ((dest->byStackcount + request.byStackCount) >= itemSrc->byMaxStack)		
		overStack = (dest->byStackcount + request.byStackCount) - itemSrc->byMaxStack;

	dest->byStackcount += request.byStackCount;
	if (dest->byStackcount >= itemSrc->byMaxStack)
		dest->byStackcount -= overStack;

	if (created.sItemData.charId == charid)
	{
		created.sItemData.byStackcount = dest->byStackcount;
		created.sItemData.itemNo = dest->tblidx;
		created.sItemData.itemId = dest->handle;
		created.sItemData.byPlace = request.byDestPlace;
		created.sItemData.byPosition = request.byDestPos;
		created.sItemData.byCurrentDurability = itemSrc->byDurability;
		created.sItemData.byRank = itemSrc->eRank;
		created.sItemData.bNeedToIdentify = false;
	}
	source->byStackcount -= request.byStackCount;	
	if (source->byStackcount < 0 || source->byStackcount == 255)
		source->byStackcount = 0;
	if (overStack > 0)
		source->byStackcount = overStack;
	result.byStackCount1 = source->byStackcount;
	result.byStackCount2 = dest->byStackcount;
	result.hSrcItem = source->handle;
	result.hDestItem = dest->handle;
	if (source->byStackcount <= 0)
	{
		deletes.hSrcItem = source->handle;
		memset(source, INVALID_TBLIDX, sizeof(sITEM_PROFILE));
	}
	return true;
}
//----------------------------------------
//	Perform a buy to a merchant
//	@param id - item ID - amount of this item - the created item reference
//----------------------------------------
ResultCodes InventoryManager::PerformShopBuy(TBLIDX item, int amount, sITEM_PROFILE& createdReference)
{
	sITEM_TBLDAT *newItem = (sITEM_TBLDAT *)sTBM.GetItemTable()->FindData(item);
	sCASHITEM_TBLDAT * cashItem = (sCASHITEM_TBLDAT *)sTBM.GetCashItemTable()->FindData(item);


	bool isBag = false;
	if (newItem == NULL)
	{
		if (cashItem == NULL)
		{
			//sLog.outDebug("CASH ITEM MAYBE");
			return GAME_SHOP_ITEM_INVALID;
		}
		else
		{
			if (cashItem->eItemType == ITEM_TYPE_BAG)
				isBag = true;
		}
	}
	else
	{
		if (newItem->eItemType == ITEM_TYPE_BAG)
			isBag = true;
	}
	if (isBag == true)
	{

		sITEM_PROFILE *data = CreateNewItem(item, amount);
		if (data != NULL)
		{
			createdReference = *data;
			return GAME_SUCCESS;
		}
		else
		{
			return GAME_ITEM_INVEN_FULL;
		}
	}
	else if (IsInventoryFull() == false)
	{
		sITEM_PROFILE *data = CreateNewItem(item, amount);
		if (data != NULL)
		{
			createdReference = *data;
			return GAME_SUCCESS;
		}
	}
	else
	{
		return GAME_ITEM_INVEN_FULL;
	}
	return GAME_FAIL;
}
//----------------------------------------
//	Get Item profile at place and pos in bag
//----------------------------------------
sITEM_PROFILE *InventoryManager::GetItemAtPlaceAndPost(BYTE place, BYTE pos)
{
	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		if (ItemProfile[i].byPlace == place && ItemProfile[i].byPos == pos)
		{
			return &ItemProfile[i];
		}
	}
	return NULL;
}
sITEM_PROFILE *InventoryManager::GetItemByHandle(HOBJECT Handle)
{
	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		if (ItemProfile[i].handle == Handle)
		{
			return &ItemProfile[i];
		}
	}
	return NULL;
}
sITEM_PROFILE *InventoryManager::GetItemByTblidx(TBLIDX Item)
{
	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		if (ItemProfile[i].tblidx == Item)
		{
			return &ItemProfile[i];
		}
	}
	return NULL;
}
//----------------------------------------
//	Check if inventory is full
//----------------------------------------
bool InventoryManager::IsInventoryFull()
{
	BYTE Place = INVALID_SLOTID;
	BYTE Pos = INVALID_SLOTID;

	if (GetFreeBagPlaceAndSlot(&Place, &Pos) == GAME_ITEM_INVEN_FULL)
		return true;
	return false;
}
//----------------------------------------
//	Create item function
//----------------------------------------
sITEM_PROFILE* InventoryManager::CreateNewItem(TBLIDX itemID, int stack)
{
	sITEM_TBLDAT* item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(itemID);

	if (item && item->eItemType == ITEM_TYPE_BAG)
	{
		sITEM_PROFILE* newItem = CreateBag(itemID, stack);
		if (newItem == NULL) // Full bag slot
		{
			if (IsInventoryFull() == false)
				return CreateItem(*item, stack); // Add item in inventory
			return NULL;
		}
		else
		{
			return newItem;
		}
	}
	else
	{
		if (item)
			return CreateItem(*item, stack);
	}
	if (sTBM.GetCashItemTable() != NULL && sTBM.GetCashItemTable()->FindData(itemID) != NULL)
	{
		
		sCASHITEM_TBLDAT* item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(itemID);
		if (item)
		{
			
			return CreateCashItem(*item, stack);
		}
	}
	else
		sLog.outDebug("Can't load cash item");
	return NULL;
}
//----------------------------------------
//	Create a bag an fill to to bag slots
//	@param id - item id - stack of the item
//----------------------------------------
sITEM_PROFILE *InventoryManager::CreateBag(TBLIDX itemID, int stack)
{
	sITEM_TBLDAT* item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(itemID);
	BYTE Place = INVALID_SLOTID;
	BYTE Pos = INVALID_SLOTID;
	if (item == NULL)
	{
		item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(itemID);
	}
	if (GetFreeBagSlot(&Place, &Pos) == GAME_ITEM_INVEN_FULL)
	{
		return NULL;
	}
	if (Place == INVALID_SLOTID || Pos == INVALID_SLOTID)
		return NULL;
	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		if (ItemProfile[i].tblidx == INVALID_TBLIDX || ItemProfile[i].tblidx == 0)
		{
			ItemProfile[i].handle = sWorld.AcquireItemSerialId();
			ItemProfile[i].tblidx = item->tblidx;
			ItemProfile[i].byPlace = Place;
			ItemProfile[i].byPos = Pos;
			ItemProfile[i].byStackcount = stack;
			ItemProfile[i].byRank = item->eRank;
			ItemProfile[i].byGrade = 0;
			ItemProfile[i].byBattleAttribute = item->eBattleAttribute;
			ItemProfile[i].byCurDur = item->byDurability;
			ItemProfile[i].byRestrictType = eITEM_RESTRICT_TYPE::ITEM_RESTRICT_TYPE_NONE;// item.unknownStruct.unknown14;

			return &ItemProfile[i];
		}
	}
	return NULL;
}
//----------------------------------------
//	Create a new item
//	@param id - item table ref - stack of the new item to create
//----------------------------------------
sITEM_PROFILE *InventoryManager::CreateItem(sITEM_TBLDAT& item, int stack)
{
	BYTE Place = INVALID_SLOTID;
	BYTE Pos = INVALID_SLOTID;

	if (GetFreeBagPlaceAndSlot(&Place, &Pos) == GAME_ITEM_INVEN_FULL)
	{
		return NULL;
	}
	if (Place == INVALID_SLOTID || Pos == INVALID_SLOTID)
		return NULL;
	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		if (ItemProfile[i].tblidx == INVALID_TBLIDX || ItemProfile[i].tblidx == 0)
		{
			memset(&ItemProfile[i], INVALID_TBLIDX, sizeof(sITEM_PROFILE));

			ItemProfile[i].handle = sWorld.AcquireItemSerialId();//sDB.getInt("id");
			ItemProfile[i].tblidx = item.tblidx;
			ItemProfile[i].byPlace = Place;
			ItemProfile[i].byPos = Pos;
			ItemProfile[i].byStackcount = stack;
			ItemProfile[i].byRank = item.eRank;
			ItemProfile[i].byGrade = 0;
			ItemProfile[i].byCurDur = item.byDurability;
			ItemProfile[i].byDurationType = eDURATIONTYPE::eDURATIONTYPE_NORMAL;
			ItemProfile[i].byBattleAttribute = item.eBattleAttribute;
			ItemProfile[i].bNeedToIdentify = item.bValidity_Able;
			ItemProfile[i].nUseEndTime = 0;
			ItemProfile[i].nUseStartTime = 0;

			ItemProfile[i].byRestrictType = eITEM_RESTRICT_TYPE::ITEM_RESTRICT_TYPE_NONE;// item->unknownStruct.unknown14;
			ItemProfile[i].aOptionTblidx = item.tbxItemOption;// item.Item_Option_Tblidx;
			ItemProfile[i].aOptionTblidx1 = INVALID_TBLIDX;// item->Item_Option_Tblidx;
			for (int j = 0; j < 6; j++)
			{
				ItemProfile[i].aitemEffect[j].dwValue = INVALID_TBLIDX;// 8;
				ItemProfile[i].aitemEffect[j].wType = INVALID_WORD;// j + 1;
			}
			for (int j = 0; j < 2; j++)
			{
				ItemProfile[i].aitemExtraEffect[j].dwValue = INVALID_TBLIDX;// 12;
				ItemProfile[i].aitemExtraEffect[j].wType = INVALID_WORD;// j + 1; // ?????
			}
			for (int j = 0; j < 17; j++)
			{
				ItemProfile[i].awchMaker[j] = 0;
			}
			//sLog.outDebug("New item created: %d\n\tDurability: %u, other durability: %u\n\tRank: %u, BattleAttribute: %u", item.tblidx, item.byDurability, item.byDurability_Count, item.byRank, item.byBattle_Attribute);

			return &ItemProfile[i];
		}
	}
	return NULL;
}
//----------------------------------------
//	Create a new item
//	@param id - item table ref - stack of the new item to create
//----------------------------------------
sITEM_PROFILE *InventoryManager::CreateCashItem(sCASHITEM_TBLDAT& item, int stack)
{
	BYTE Place = INVALID_SLOTID;
	BYTE Pos = INVALID_SLOTID;

	if (GetFreeBagPlaceAndSlot(&Place, &Pos) == GAME_ITEM_INVEN_FULL)
	{
		return NULL;
	}
	if (Place == INVALID_SLOTID || Pos == INVALID_SLOTID)
		return NULL;
	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		if (ItemProfile[i].tblidx == INVALID_TBLIDX || ItemProfile[i].tblidx == 0)
		{
			memset(&ItemProfile[i], INVALID_TBLIDX, sizeof(sITEM_PROFILE));

			ItemProfile[i].handle = sWorld.AcquireItemSerialId();//sDB.getInt("id");
			ItemProfile[i].tblidx = item.tblidx;
			ItemProfile[i].byPlace = Place;
			ItemProfile[i].byPos = Pos;
			ItemProfile[i].byStackcount = stack;
			ItemProfile[i].byRank = item.eRank;
			ItemProfile[i].byGrade = 0;
			ItemProfile[i].byCurDur = item.byDurability;
			ItemProfile[i].byDurationType = eDURATIONTYPE::eDURATIONTYPE_NORMAL;
			ItemProfile[i].byBattleAttribute = item.eBattleAttribute;
			ItemProfile[i].bNeedToIdentify = item.bValidity_Able;
			ItemProfile[i].nUseEndTime = 0;
			ItemProfile[i].nUseStartTime = 0;

			ItemProfile[i].byRestrictType = eITEM_RESTRICT_TYPE::ITEM_RESTRICT_TYPE_NONE;// item->unknownStruct.unknown14;
			ItemProfile[i].aOptionTblidx = item.tbxItemOption;// item.Item_Option_Tblidx;
			ItemProfile[i].aOptionTblidx1 = INVALID_TBLIDX;// item->Item_Option_Tblidx;
			for (int j = 0; j < 6; j++)
			{
				ItemProfile[i].aitemEffect[j].dwValue = INVALID_TBLIDX;// 8;
				ItemProfile[i].aitemEffect[j].wType = INVALID_WORD;// j + 1;
			}
			for (int j = 0; j < 2; j++)
			{
				ItemProfile[i].aitemExtraEffect[j].dwValue = INVALID_TBLIDX;// 12;
				ItemProfile[i].aitemExtraEffect[j].wType = INVALID_WORD;// j + 1; // ?????
			}
			for (int j = 0; j < 17; j++)
			{
				ItemProfile[i].awchMaker[j] = 0;
			}
			//sLog.outDebug("New item created: %d\n\tDurability: %u, other durability: %u\n\tRank: %u, BattleAttribute: %u", item.tblidx, item.byDurability, item.byDurability_Count, item.byRank, item.byBattle_Attribute);

			return &ItemProfile[i];
		}
	}
	return NULL;
}
//----------------------------------------
//	Delete function
//----------------------------------------
void InventoryManager::DeleteItem(BYTE byPlace, BYTE byPosition, HOBJECT& hItem)
{
	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		if (ItemProfile[i].tblidx != INVALID_TBLIDX && ItemProfile[i].tblidx > 0 && ItemProfile[i].byPlace == byPlace && ItemProfile[i].byPos == byPosition)
		{
			sITEM_TBLDAT* item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(ItemProfile[i].tblidx);
			if (item == NULL)
			{
				item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(ItemProfile[i].tblidx);
			}

			if (item != NULL)
			{
				hItem = ItemProfile[i].handle;
				if (ItemProfile[i].byPlace == CONTAINER_TYPE_EQUIP)
				{
					plr->GetAttributesManager()->UpdateAttributesFromItem(*item, true);
				}
				memset(&ItemProfile[i], INVALID_TBLIDX, sizeof(sITEM_PROFILE));
				break;
			}
		}
	}
}
//----------------------------------------
//	Find the free slot in bag
//----------------------------------------
ResultCodes InventoryManager::GetFreeBagPlaceAndSlot(BYTE* Place, BYTE* Pos)
{
	return GetFirstFreeBag(*Place, *Pos);
}
//----------------------------------------
//	Find the free bag slot
//----------------------------------------
ResultCodes InventoryManager::GetFreeBagSlot(BYTE* Place, BYTE* Pos)
{
	for (int j = 0; j < MAX_COUNT_USER_HAVE_INVEN_ITEM; j++)
	{
		if (ItemProfile[j].byPlace == CONTAINER_TYPE_BAGSLOT)
		{
			*Pos = ItemProfile[j].byPos + 1;
			*Place = 0;
		}
	}
	if (*Pos >= CONTAINER_TYPE_BAG5)
	{
		*Pos = 255;
		*Place = 255;
		return GAME_ITEM_INVEN_FULL;
	}
	return GAME_SUCCESS;
}
//----------------------------------------
//	Look bag position
//----------------------------------------
ResultCodes InventoryManager::GetFirstFreeBag(BYTE& Place, BYTE& Postition)
{
	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		if (ItemProfile[i].byPlace == CONTAINER_TYPE_BAGSLOT && ItemProfile[i].byPos < CONTAINER_TYPE_BAG5)
		{
			sITEM_TBLDAT* item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(ItemProfile[i].tblidx);
			if (item == NULL)
			{
				item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(ItemProfile[i].tblidx);
			}
			if (item != NULL)
			{
				for (int j = 0; j < item->byBagSize; j++)
				{
					if (GetFirstFreePosInBag(ItemProfile[i].byPos + 1, j) != INVALID_SLOTID)
					{
						Postition = j;
						Place = ItemProfile[i].byPos + 1;
						return GAME_SUCCESS;
					}
				}
			}
		}
	}
	return GAME_ITEM_INVEN_FULL;
}
//----------------------------------------
//	Look slot in bag position
//----------------------------------------
BYTE InventoryManager::GetFirstFreePosInBag(BYTE Bag, SLOTID slot)
{
	for (int j = 0; j < MAX_COUNT_USER_HAVE_INVEN_ITEM; j++)
	{
		if (ItemProfile[j].byPlace == Bag && ItemProfile[j].byPos == slot)
		{
			return INVALID_SLOTID;
		}
	}
	return slot;
}
//----------------------------------------
//	Get all free slot
//----------------------------------------
int InventoryManager::GetTotalFreeSpaceInBag()
{
	int totalFreeSlots = 0;

	for (int i = 0; i < MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		if (ItemProfile[i].byPlace == CONTAINER_TYPE_BAGSLOT && ItemProfile[i].byPos < CONTAINER_TYPE_BAG5)
		{
			sITEM_TBLDAT* item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(ItemProfile[i].tblidx);
			if (item == NULL)
			{
				item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(ItemProfile[i].tblidx);
			}
			if (item != NULL)
			{
				for (int j = 0; j < item->byBagSize; j++)
				{
					if (GetFirstFreePosInBag(ItemProfile[i].byPos + 1, j) != 255)
					{
						totalFreeSlots++;
					}
				}
			}
		}
	}
	return totalFreeSlots;
}