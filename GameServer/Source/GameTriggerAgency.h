#pragma once
#include "DboTSCore.h"

class CGameTriggerCtrl;

class CGameTriggerAgency : public CDboTSTAgency
{
	NTL_TS_DECLARE_RTTI(CGameTriggerAgency, CDboTSTAgency)
protected:
	SGET_QUEST_INFO						m_TriggerInfo;
public:
	CGameTriggerAgency();
	~CGameTriggerAgency();
	// Implementations
	virtual CDboTSTCtrl*				MakeTriggerController(CNtlTSTrigger* pTrig);
};

