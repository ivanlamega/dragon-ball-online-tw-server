#pragma once
#include "DboTSCore.h"
class CGameQuestCtrl;
class CGameQuestAgency : public CDboTSQAgency
{
	NTL_TS_DECLARE_RTTI(CGameQuestAgency, CDboTSQAgency)
protected:
	SGET_QUEST_INFO						m_QuestInfo;
public:
	CGameQuestAgency();
	~CGameQuestAgency();
	virtual CDboTSTCtrl*				MakeTriggerController(CNtlTSTrigger* pTrig);
};

