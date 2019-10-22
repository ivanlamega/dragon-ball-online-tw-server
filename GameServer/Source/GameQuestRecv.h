#pragma once
#include "DboTSCore.h"

class CGameQuestCtrl;
class CGameQuestAgency;

//Server Quest Receiver

struct sSQRUN_PARAM : public sQRUN_PARAM
{
public:
	sSQRUN_PARAM(void) : bQuestShare(false), bQuestShareOutMsg(false), bCheckForQuestMark(false) { return; }

public:
	virtual void						Init(void) { bQuestShare = false; bQuestShareOutMsg = false; bCheckForQuestMark = false; sQRUN_PARAM::Init(); }

	virtual bool						IsQuestShare(void) { return bQuestShare; }
	virtual void						SetQuestShare(bool bQuestShare) { this->bQuestShare = bQuestShare; }

	virtual bool						IsQuestShareOutMsg(void) { return bQuestShareOutMsg; }
	virtual void						SetQuestShareOutMsg(bool bOutMsg) { bQuestShareOutMsg = bOutMsg; }

	virtual bool						IsForCheckQuestMark(void) { return bCheckForQuestMark; }
	virtual void						SetForCheckQuestMark(bool bCheckForQuestMark) { this->bCheckForQuestMark = bCheckForQuestMark; }

	CGameQuestCtrl*						GetCtrl(void) { return (CGameQuestCtrl*)pCtrl; }
	CGameQuestAgency*						GetAgency(void) { return (CGameQuestAgency*)pAgency; }

protected:
	bool								bQuestShare;
	bool								bQuestShareOutMsg;

	bool								bCheckForQuestMark;
};

class CGameQuestRecv : public CDboTSQRecv
{
	NTL_TS_DECLARE_RTTI(CGameQuestRecv, CDboTSQRecv)
public:
	CGameQuestRecv();
	~CGameQuestRecv();
};

