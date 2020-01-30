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

	typedef std::unordered_map<TBLIDX, NTL_TS_T_ID> OBJECTQUEST;
	typedef OBJECTQUEST::iterator OBJECTQUESTIT;
	typedef OBJECTQUEST::value_type OBJECTQUESTVAL;

	OBJECTQUEST							m_pObjectQuestList;

	std::vector<QuestData> QuestDat;

public:
	void							AddMobQuest(TBLIDX mobTblidx, NTL_TS_T_ID questId);
	NTL_TS_T_ID						FindQuestByMob(TBLIDX mobTblidx);
	MOBQUESTIT						MobQuestBegin() { return m_pMobQuestList.begin(); };
	MOBQUESTIT						MobQuestEnd() { return m_pMobQuestList.end(); };

	void							AddObjectQuest(TBLIDX objTblidx, NTL_TS_T_ID questId);
	NTL_TS_T_ID						FindQuestByObject(TBLIDX objTblidx);
	OBJECTQUESTIT					ObjectQuestBegin() { return m_pObjectQuestList.begin(); };
	OBJECTQUESTIT					ObjectQuestEnd() { return m_pObjectQuestList.end(); };
};

#endif