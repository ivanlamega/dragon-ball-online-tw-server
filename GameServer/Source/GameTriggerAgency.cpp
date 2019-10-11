#include "stdafx.h"
#include "GameTriggerAgency.h"
#include "GameTriggerCtrl.h"
#include "GameTriggerRecv.h"
#include "QuestWrapper.h"
#include "TableContainer.h"
#include "ObjectTable.h"
#include "NtlObject.h"
#include "MobTable.h"
#include "ObjectTable.h"
#include "QuestNarrationTable.h"


NTL_TS_IMPLEMENT_RTTI(CGameTriggerAgency, CDboTSTAgency)

CGameTriggerAgency::CGameTriggerAgency()
{
	m_TriggerInfo.QuestInfoList.reserve(10);
}


CGameTriggerAgency::~CGameTriggerAgency()
{
	mapdef_TRIGGER_LIST::iterator it = m_defCurTList.begin();
	for (; it != m_defCurTList.end(); ++it)
	{
		CNtlTSControlObject* pObj = it->second;
		m_pParent->GetControlFactory()->DeleteObj(pObj);
	}
	m_defCurTList.clear();
}

CDboTSTCtrl* CGameTriggerAgency::MakeTriggerController(CNtlTSTrigger* pTrig)
{
	// Trigger controller 를 생성한다
	CNtlTSControlObject* pCtrlObj = GetParent()->GetControlFactory()->CreateObj("CDboTSSTCtrl");
	if (!pCtrlObj->IsDerivedClass("CDboTSCTCtrl"))
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSSTCtrl. Info[%s]. [%s]", pCtrlObj->GetClassName(), TS_CODE_TRACE());
		m_pParent->GetControlFactory()->DeleteObj(pCtrlObj);
		return 0;
	}

	// TS trigger 와 Trigger를 연결 및 저장한다
	((CGameTriggerCtrl*)pCtrlObj)->SetTrigger(pTrig);
	((CGameTriggerCtrl*)pCtrlObj)->SetParent(this);

	return (CGameTriggerCtrl*)pCtrlObj;
}