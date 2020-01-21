#ifndef __QUEST_INVENTORY_H
#define __QUEST_INVENTORY_H

#include <TableAll.h>

class Player;

struct QuestItem
{
	BYTE				byPos;
	TBLIDX				qItemTblidx;
	BYTE				byCurCount;
};

class QuestInventoryManager
{
public:
	QuestInventoryManager() {};
	~QuestInventoryManager() {};

	BYTE		AddItemQuest(QuestItem newItemQuest);
	void		DeleteItemQuest(BYTE pos);
	QuestItem*	FindItemQuestBySlot(BYTE pos);
	QuestItem*	FindItemQuestByTblidx(TBLIDX tblidx);
	BYTE		GetFreeSlot();

private:
	CHARACTERID			charid;
	Player* plr;
	std::vector<QuestItem> QuestItems;
};

#endif