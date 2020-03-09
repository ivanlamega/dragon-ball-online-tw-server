#include <Game\Object\Manager\Skills.h>
#include <Game\Object\Player.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
//----------------------------------------
//	Constructor
//----------------------------------------
SkillsManager::SkillsManager()
{

}
//----------------------------------------
//	Destructor
//----------------------------------------
SkillsManager::~SkillsManager()
{

}
//----------------------------------------
//	Load skills
//----------------------------------------
bool SkillsManager::LoadSkill(CHARACTERID id)
{
	charid = id;
	if (LoadSkillsFromDatabase() == false)
	{
		return false;
	}
	if (LoadSkillBuffFromDatabase() == false)
	{
		return false;
	}
	if (LoadHTBFromDatabase() == false)
	{
		return false;
	}
	/*if (LoadQuickSlotFromDatabase() == false)
	{
		return false;
	}*/
	return true;
}
//----------------------------------------
//	Save quickSlot
//----------------------------------------
/*void SkillsManager::SaveSkill(Player& plr)
{
	for (int i = 0; i < 48; i++)
	{
		if (QuickSlotData[i].tblidx != INVALID_TBLIDX && QuickSlotData[i].tblidx != -1)
		{
			sDB.UpdateQuickSlots(QuickSlotData[i].tblidx, i, plr.GetCharacterID());
		}
		else
		{
			sDB.UpdateQuickSlots(0, i, plr.GetCharacterID());
		}
	}
}*/
//----------------------------------------
//	Load function
//----------------------------------------
bool SkillsManager::LoadSkillsFromDatabase()
{
	for (int i = 0; i < 120; i++) memset(&SkillInfo[i], 0, sizeof(sSKILL_INFO));
	size_t i = 0;

	sql::ResultSet* result = sDB.executes("SELECT * FROM skills WHERE owner_id = '%d' ORDER BY SlotID ASC;", charid);
	if (result == NULL)
		return false;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return false;
	}
	SkillCounter = result->rowsCount();
	SkillTable * pSkillTable = sTBM.GetSkillTable();
	while (true)
	{
		sSKILL_TBLDAT* pSkillData = reinterpret_cast<sSKILL_TBLDAT*>(pSkillTable->FindData(result->getInt("skill_id")));

		SkillInfo[i].bIsRpBonusAuto = result->getBoolean("RpBonusAuto");
		SkillInfo[i].byRpBonusType = result->getInt("RpBonusType");
		SkillInfo[i].bySlotId = result->getInt("SlotID");
		SkillInfo[i].dwTimeRemaining = result->getInt("TimeRemaining");
		SkillInfo[i].nExp = result->getInt("Exp");
		SkillInfo[i].tblidx = result->getInt("skill_id");
		i++;
		if (result->next())
			continue;
		else
			break;
	}
	delete result;
	return true;
}
//----------------------------------------
//	Load all buff apply to this character
//----------------------------------------
bool SkillsManager::LoadSkillBuffFromDatabase()
{
	for (int i = 0; i < 16; i++) memset(&BuffInfo[i], 0, sizeof(sBUFF_INFO));
	SkillTable * pSkillTable = sTBM.GetSkillTable();
	int iCountBuff = 0;

	sql::ResultSet* result = sDB.executes("SELECT * FROM skills WHERE owner_id = '%d';", charid);
	if (result == NULL)
		return false;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return false;
	}
	while (true)
	{
		int SkillId = result->getInt("skill_id");
		int iTimeRemaining = result->getInt("TimeRemaining");
		sSKILL_TBLDAT * pSkillBuffData = reinterpret_cast<sSKILL_TBLDAT*>(pSkillTable->FindData(SkillId));
			if (pSkillBuffData == nullptr)
			{
				sLog.outError("Couldn't find skill in table");
				return false;
			}
		
		if (iCountBuff == ((MAX_BLESS_BUFF_CHARACTER_HAS + MAX_CURSE_BUFF_CHARACTER_HAS) - 1))
			break;
		if ((pSkillBuffData->byBuff_Group != INVALID_BUFF_GROUP) && (iTimeRemaining != 0))
		{
			BuffInfo[iCountBuff].SourceTblidx = pSkillBuffData->tblidx;
			BuffInfo[iCountBuff].bySourceType = DBO_OBJECT_SOURCE_SKILL;//Need Check
			BuffInfo[iCountBuff].dwInitialDuration = pSkillBuffData->dwKeepTimeInMilliSecs;
			BuffInfo[iCountBuff].dwTimeRemaining = (iTimeRemaining * 1000);//to MilliSeconds

			BuffInfo[iCountBuff].InitialDuration = pSkillBuffData->dwKeepTimeInMilliSecs;
			BuffInfo[iCountBuff].EffectType = pSkillBuffData->bySkill_Effect_Type[0];
			BuffInfo[iCountBuff].afEffectValue[0] = pSkillBuffData->SkillValue[0];
			BuffInfo[iCountBuff].afEffectValue[1] = 0;

			BuffInfo[iCountBuff].InitialDuration2 = pSkillBuffData->dwKeepTimeInMilliSecs;
			BuffInfo[iCountBuff].EffectType2 = pSkillBuffData->skill_Effect[1];
			BuffInfo[iCountBuff].afEffectValue2[0] = pSkillBuffData->SkillValue[1];
			BuffInfo[iCountBuff].afEffectValue2[1] = 0;
			
			iCountBuff++;
		}
		if (result->next())
			continue;
		else
			break;
	}
	this->SkillBuffCounter = static_cast<BYTE>(iCountBuff);
	delete result;
	return true;
}
//----------------------------------------
//	Load all HTB for this char
//----------------------------------------
bool SkillsManager::LoadHTBFromDatabase()
{
	for (int i = 0; i < 30; i++) memset(&HTBSkillnfo[i], 0, sizeof(sHTB_SKILL_INFO));
	size_t i = 0;

	sql::ResultSet* result = sDB.executes("SELECT * FROM skills WHERE owner_id = '%d' ORDER BY SlotID ASC;", charid);
	if (result == NULL)
		return false;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return false;
	}
	SkillTable * pSkillTable = sTBM.GetSkillTable();
	while (true)
	{
		//Added because Shenron Buffs and for help to detect type of skills
		//Note Shenron Buffs does not take ANY SLOTID
		sSKILL_TBLDAT* pSkillData = reinterpret_cast<sSKILL_TBLDAT*>(pSkillTable->FindData(result->getInt("skill_id")));
		if (pSkillData->bySkill_Class == SKILL_CLASS_HTB)
		{
			HTBSkillnfo[i].bySlotId = static_cast<BYTE>(result->getInt("SlotID"));
			HTBSkillnfo[i].dwTimeRemaining = result->getInt("TimeRemaining");
			HTBSkillnfo[i].skillId = pSkillData->tblidx;
			i++;
		}
		if (result->next())
			continue;
		else
			break;
	}
	HTBSkillCounter = i;
	delete result;
	return true;
}
//----------------------------------------
//	Load all skill quick slot
//----------------------------------------
/*bool SkillsManager::LoadQuickSlotFromDatabase()
{
	for (int i = 0; i < 48; i++) memset(&QuickSlotData[i], 0, sizeof(sQUICK_SLOT_PROFILE));

	sql::ResultSet* result = sDB.executes("SELECT * FROM quickslot WHERE CharID = %d;", charid);
	if (result == NULL)
		return false;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return false;
	}
	SkillTable * pSkillTable = sTBM.GetSkillTable();
	ItemTable * pItemTable = sTBM.GetItemTable();
	UseItemTable * pItemUseTable = sTBM.GetUseItemTable();

	int i = 0;
	int SkillOrItem = 0;
	int slotID = 0;
	std::string query;

	while (i < 48)
	{
		query = "slotId_" + std::to_string(i);//To Who use VS2013

		SkillOrItem = result->getInt(query.c_str());
		QuickSlotData[slotID].bySlot = 255;
		QuickSlotData[slotID].tblidx = 0;
		sSKILL_TBLDAT* pSkillData = reinterpret_cast<sSKILL_TBLDAT*>(pSkillTable->FindData(SkillOrItem));
		sITEM_TBLDAT * pItemData = reinterpret_cast<sITEM_TBLDAT*>(pItemTable->FindData(SkillOrItem));
		
		if (pItemData == NULL)
		{
			pItemData = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(SkillOrItem);
		}

		if (pSkillData)
		{
			QuickSlotData[slotID].bySlot = static_cast<BYTE>(i);
			QuickSlotData[slotID].tblidx = pSkillData->tblidx;
			QuickSlotData[slotID].byType = (pSkillData->bySkill_Class == SKILL_CLASS_HTB ? QUICK_SLOT_TYPE_HTB_SKILL : QUICK_SLOT_TYPE_SKILL);
			slotID++;
		}
		else if (pItemData)
		{
			sUSE_ITEM_TBLDAT * pUseItemData = reinterpret_cast<sUSE_ITEM_TBLDAT*>(pItemUseTable->FindData(pItemData->tbxUseItem));
			if (pUseItemData)
			{
				sql::ResultSet* result = sDB.executes("SELECT id FROM items WHERE tblidx = '%d' AND owner_id = '%d';", SkillOrItem, charid);
				if (result == NULL)
					break;
				if (result->rowsCount() <= 0)
				{
					delete result;
					break;
				}
				QuickSlotData[slotID].bySlot = i;
				QuickSlotData[slotID].tblidx = pItemData->tblidx;
				QuickSlotData[slotID].hItem = result->getInt("id");
				QuickSlotData[slotID].byType = QUICK_SLOT_TYPE_ITEM;
				slotID++;
				delete result;
			}
			else
			{
				QuickSlotData[slotID].bySlot = static_cast<BYTE>(i);
				QuickSlotData[slotID].tblidx = pItemData->tblidx;
				QuickSlotData[slotID].byType = QUICK_SLOT_TYPE_SOCIALACTION;
				slotID++;
			}
		}
		i++;
	}
	QuickSlotCounter = static_cast<BYTE>(slotID);
	delete result;
	return true;
}*/
//----------------------------------------
//	Update our quickslot localy
//----------------------------------------
/*void SkillsManager::UpdateSlot(BYTE slot_id, TBLIDX id, BYTE byType)
{
	printf("UpdateSlot : slot id: %u -- at slotid: %d\n", slot_id, id);

	QuickSlotData[slot_id].bySlot = slot_id;
	QuickSlotData[slot_id].tblidx = id;
	QuickSlotData[slot_id].byType = byType;
	QuickSlotData[slot_id].hItem = INVALID_TBLIDX;
}*/
//----------------------------------------
//	Get id from slot_id
//----------------------------------------
TBLIDX SkillsManager::getIdAtPos(BYTE slot_id)
{
	for (int i = 0; i < 120; i++)
	{
		if (SkillInfo[i].bySlotId == slot_id)
			return SkillInfo[i].tblidx;
	}
	return INVALID_TBLIDX;
}

bool SkillsManager::isSkillLearned(DWORD SkillID)
{
	for (int i = 0; i < 120; i++)
	{
		if (SkillInfo[i].tblidx == SkillID)
			return true;		
	}
	return false;
}