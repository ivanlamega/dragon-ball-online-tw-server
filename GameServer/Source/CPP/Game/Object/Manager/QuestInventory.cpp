#include "Manager/QuestInventory.h"

void QuestInventoryManager::AddItemQuest(QuestItem newItemQuest)
{
	QuestItems.push_back(newItemQuest);
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