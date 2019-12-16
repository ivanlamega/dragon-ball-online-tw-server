#ifndef __QUEST_H
#define __QUEST_H

#include <vector>

class Player;
class Npc;

struct QuestData;

class QuestManager
{
public:
	QuestManager() {};
	~QuestManager() {};

	void		AddQuest(QuestData newQuest);
	void		DeleteQuest(int questId);
	QuestData*	FindQuestById(int questId);

private:

	std::vector<QuestData> QuestDat;
};

#endif