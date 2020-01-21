#include "Manager/QuestInventory.h"

BYTE QuestInventoryManager::AddItemQuest(QuestItem newItemQuest)
{
	BYTE slot = GetFreeSlot();
	if (slot != -1)
	{
		newItemQuest.byPos = slot;
		QuestItems.push_back(newItemQuest);
		return slot;
	}
	return -1;
}

void QuestInventoryManager::DeleteItemQuest(BYTE pos)
{
	for (std::vector<QuestItem>::iterator iter = QuestItems.begin(); iter != QuestItems.end(); ++iter)
	{
		if (iter->byPos == pos)
		{
			QuestItems.erase(iter);
			break;
		}
	}
}

QuestItem* QuestInventoryManager::FindItemQuestBySlot(BYTE pos)
{
	for (std::vector<QuestItem>::size_type i = 0; i != QuestItems.size(); i++)
	{
		if (QuestItems[i].byPos == pos)
		{
			return &QuestItems[i];
		}
	}
	return NULL;
}

QuestItem* QuestInventoryManager::FindItemQuestByTblidx(TBLIDX tblidx)
{
	for (std::vector<QuestItem>::size_type i = 0; i != QuestItems.size(); i++)
	{
		if (QuestItems[i].qItemTblidx == tblidx)
		{
			return &QuestItems[i];
		}
	}
	return NULL;
}

BYTE QuestInventoryManager::GetFreeSlot()
{
	for (int slot = 0; slot < NTL_QUEST_INVENTORY_SLOT_COUNT-2; slot++)
	{
		if (FindItemQuestBySlot(slot) == NULL)
		{
			return slot;
		}
	}
	return -1;
}