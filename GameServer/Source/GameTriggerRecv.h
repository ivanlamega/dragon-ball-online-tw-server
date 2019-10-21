#pragma once
#include "DboTSCore.h"

class CGameTriggerCtrl;
class CGameTriggerAgency;

//Server Trigger Receiver

struct sSTRUN_PARAM : public sTRUN_PARAM
{
public:
	sSTRUN_PARAM(void) { return; }

public:
	virtual void						Init(void) { sTRUN_PARAM::Init(); }

	CGameTriggerCtrl*						GetCtrl(void) { return (CGameTriggerCtrl*)pCtrl; }
	CGameTriggerAgency*						GetAgency(void) { return (CGameTriggerAgency*)pAgency; }
};

class CGameTriggerRecv : public CDboTSTRecv
{
	NTL_TS_DECLARE_RTTI
public:
	CGameTriggerRecv();
	~CGameTriggerRecv();
};

