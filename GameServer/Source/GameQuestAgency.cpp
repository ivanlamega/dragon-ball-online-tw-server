#include "stdafx.h"
#include "GameQuestAgency.h"
#include "GameQuestCtrl.h"
#include "GameQuestRecv.h"
#include "QuestWrapper.h"
//#include "NtlResultCode.h"
#include "TableContainer.h"
#include "QuestTextDataTable.h"
#include "MobTable.h"
#include "NPCTable.h"
#include "ObjectTable.h"
#include "QuestNarrationTable.h"
#include "QuestItemTable.h"
#include "GameServer.h"


NTL_TS_IMPLEMENT_RTTI(CGameQuestAgency, CDboTSQAgency)


CGameQuestAgency::CGameQuestAgency(void)
{
	m_QuestInfo.QuestInfoList.reserve(10);
}

CGameQuestAgency::~CGameQuestAgency(void)
{
	mapdef_TRIGGER_LIST::iterator it = m_defCurTList.begin();
	for (; it != m_defCurTList.end(); ++it)
	{
		CNtlTSControlObject* pObj = it->second;
		m_pParent->GetControlFactory()->DeleteObj(pObj);
	}
	m_defCurTList.clear();
}

CDboTSTCtrl* CGameQuestAgency::MakeTriggerController(CNtlTSTrigger* pTrig)
{
	// Quest controller 를 생성한다
	CNtlTSControlObject* pCtrlObj = GetParent()->GetControlFactory()->CreateObj("CDboTSSQCtrl");
	if (!pCtrlObj->IsDerivedClass("CDboTSCQCtrl"))
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSSQCtrl. Info[%s]. [%s]", pCtrlObj->GetClassName(), TS_CODE_TRACE());
		m_pParent->GetControlFactory()->DeleteObj(pCtrlObj);
		return 0;
	}

	// TS trigger 와 Quest trigger를 연결 및 저장한다
	((CGameQuestCtrl*)pCtrlObj)->SetTrigger(pTrig);
	((CGameQuestCtrl*)pCtrlObj)->SetParent(this);

	return (CGameQuestCtrl*)pCtrlObj;
}