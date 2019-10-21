#pragma once
#include "DboTSCore.h"
class CGameObjectAgency : public CDboTSTAgency
{
	NTL_TS_DECLARE_RTTI
protected:
	SGET_QUEST_INFO						m_QuestInfo;

public:
	SGET_QUEST_INFO*					GetQuestInfoList(eEVENT_GEN_TYPE eEvtGenType, HOBJECT uiOwnerId);

public:
	CGameObjectAgency();
	~CGameObjectAgency();
};

