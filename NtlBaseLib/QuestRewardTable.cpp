#include "StdAfx.h"
#include "QuestRewardTable.h"
#include "Serializer.h"

WCHAR* QuestRewardTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};


QuestRewardTable::QuestRewardTable(void)
{
	Init();
}

QuestRewardTable::~QuestRewardTable(void)
{
	Destroy();
}

bool QuestRewardTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void QuestRewardTable::Destroy()
{
	Table::Destroy();
}

void QuestRewardTable::Init()
{
}

void* QuestRewardTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUEST_REWARD_TBLDAT* pQuestReward = new sQUEST_REWARD_TBLDAT;
		if (NULL == pQuestReward)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pQuestReward;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pQuestReward;
	}

	return NULL;
}

bool QuestRewardTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUEST_REWARD_TBLDAT* pQuestReward = (sQUEST_REWARD_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pQuestReward, sizeof(*pQuestReward)))
			return false;

		delete pQuestReward;

		return true;
	}

	return false;
}

bool QuestRewardTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sQUEST_REWARD_TBLDAT* pQuestReward = (sQUEST_REWARD_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pQuestReward->tblidx, pQuestReward)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pQuestReward->tblidx);
		_ASSERTE(0);
		return false;
	}

	return true;
}

bool QuestRewardTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUEST_REWARD_TBLDAT* pQuestReward = (sQUEST_REWARD_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			pQuestReward->tblidx = READ_TBLIDX(bstrData);
		}

		else
		{
			Table::CallErrorCallbackFunction(L"[File] : %s\n[Error] : Unknown field name found!(Field Name = %s)", m_wszXmlFileName, pstrDataName->c_str());
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}


sTBLDAT* QuestRewardTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool QuestRewardTable::LoadFromBinary(Serializer& serializer, bool bReload)
{
	if (false == bReload)
	{
		Reset();
	}

	BYTE byMargin = 1;
	serializer >> byMargin;

	bool bLoop = true;
	do
	{
		sQUEST_REWARD_TBLDAT* pTableData = new sQUEST_REWARD_TBLDAT;
		if (NULL == pTableData)
		{
			//- yoshiki : To log system!
			Destroy();
			return false;
		}

		if (false == pTableData->LoadFromBinary(serializer))
		{
			delete pTableData;
			bLoop = false;
			break;
		}

		//  [4/26/2008 zeroera] : 설명 : 실패하더라도 Load의 종료여부는 File Loading에서 결정한다
		if (false == AddTable(pTableData, bReload))
		{
			delete pTableData;
		}

	} while (false != bLoop);

	return true;
}

bool QuestRewardTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sQUEST_REWARD_TBLDAT* pTableData = (sQUEST_REWARD_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}