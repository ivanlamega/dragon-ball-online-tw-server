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

	typedef std::unordered_map<TBLIDX, NTL_TS_T_ID> OBJECTTRIGGER;
	typedef OBJECTTRIGGER::iterator OBJECTTRIGGERIT;
	typedef OBJECTTRIGGER::value_type OBJECTTRIGGERVAL;

	OBJECTTRIGGER							m_pObjectTriggerList;

	typedef std::unordered_map<TBLIDX, OBJECTTRIGGER> WORLDTRIGGER;
	typedef WORLDTRIGGER::iterator WORLDTRIGGERIT;
	typedef WORLDTRIGGER::value_type WORLDTRIGGERVAL;

	WORLDTRIGGER							m_pWorldTriggerList;

	typedef std::unordered_map<TBLIDX, NTL_TS_T_ID> ITEMGIVEQUEST;
	typedef ITEMGIVEQUEST::iterator ITEMGIVEQUESTIT;
	typedef ITEMGIVEQUEST::value_type ITEMGIVEQUESTVAL;

	ITEMGIVEQUEST							m_pItemGiveQuestList;

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

	void							AddObjectTrigger(TBLIDX objTblidx, NTL_TS_T_ID triggerId, TBLIDX worldTblidx);
	NTL_TS_T_ID						FindTriggerByObject(TBLIDX objTblidx, TBLIDX worldTblidx);

	WORLDTRIGGERIT					WorldTriggerBegin() { return m_pWorldTriggerList.begin(); };
	WORLDTRIGGERIT					WorldTriggerEnd() { return m_pWorldTriggerList.end(); };

	void							AddItemGiveQuest(TBLIDX itemTblidx, NTL_TS_T_ID questId);
	NTL_TS_T_ID						FindQuestByItemGive(TBLIDX itemTblidx);
	ITEMGIVEQUESTIT					ItemGiveQuestBegin() { return m_pItemGiveQuestList.begin(); };
	ITEMGIVEQUESTIT					ItemGiveQuestEnd() { return m_pItemGiveQuestList.end(); };
};

#endif