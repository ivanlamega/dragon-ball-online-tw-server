#ifndef __QUEST_H
#define __QUEST_H

#include <vector>
#include <unordered_map>
#include "DboTSCore.h"

#define MAX_QUEST_SLOT 30

class Player;
class Npc;

struct QuestData;

class QuestManager
{
public:
	QuestManager() {};
	~QuestManager() {};

	void		AddQuest(QuestData newQuest);
	bool		DeleteQuest(int questId);
	QuestData*	FindQuestById(int questId);

private:
	typedef std::unordered_map<TBLIDX, NTL_TS_T_ID> MOBQUEST;
	typedef MOBQUEST::iterator MOBQUESTIT;
	typedef MOBQUEST::value_type MOBQUESTVAL;

	MOBQUEST							m_pMobQuestList;

	std::vector<QuestData> QuestDat;

public:
	void							AddMobQuest(TBLIDX mobTblidx, NTL_TS_T_ID questId);
	NTL_TS_T_ID						FindQuestByMob(TBLIDX mobTblidx);
	MOBQUESTIT						MobQuestBegin() { return m_pMobQuestList.begin(); };
	MOBQUESTIT						MobQuestEnd() { return m_pMobQuestList.end(); };
};

#endif