#include "stdafx.h"
#include "GameObjectAgency.h"
#include "ObjectTable.h"
#include "TableContainer.h"
#include "NtlObject.h"

NTL_TS_IMPLEMENT_RTTI(CGameObjectAgency, CDboTSTAgency)


CGameObjectAgency::CGameObjectAgency(void)
{
	m_QuestInfo.QuestInfoList.reserve(10);
}

CGameObjectAgency::~CGameObjectAgency(void)
{
}

SGET_QUEST_INFO* CGameObjectAgency::GetQuestInfoList(eEVENT_GEN_TYPE eEvtGenType, HOBJECT uiOwnerId)
{
	m_QuestInfo.dwType = 0;
	m_QuestInfo.QuestInfoList.clear();

	return &m_QuestInfo;
}