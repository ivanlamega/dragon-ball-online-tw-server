#include "StdAfx.h"
#include "QuestDropTable.h"
#include "Serializer.h"

WCHAR* QuestDropTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

QuestDropTable::QuestDropTable(void)
{
	Init();
}

QuestDropTable::~QuestDropTable(void)
{
	Destroy();
}

bool QuestDropTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void QuestDropTable::Destroy()
{
	Table::Destroy();
}

void QuestDropTable::Init()
{
}

void* QuestDropTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUEST_DROP_TBLDAT* pQuestDrop = new sQUEST_DROP_TBLDAT;
		if (NULL == pQuestDrop)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pQuestDrop;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pQuestDrop;
	}

	return NULL;
}

bool QuestDropTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUEST_DROP_TBLDAT* pQuestDrop = (sQUEST_DROP_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pQuestDrop, sizeof(*pQuestDrop)))
			return false;

		delete pQuestDrop;

		return true;
	}

	return false;
}

bool QuestDropTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sQUEST_DROP_TBLDAT* pTbldat = (sQUEST_DROP_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}

	return true;
}

bool QuestDropTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUEST_DROP_TBLDAT* pQuestDrop = (sQUEST_DROP_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Quest_Drop_Tblidx"))
		{
			pQuestDrop->tblidx = READ_TBLIDX(bstrData);
		}

		// 1
		else if (0 == wcscmp(pstrDataName->c_str(), L"Quest_Item_Index1"))
		{
			pQuestDrop->aQuestItemTblidx[0] = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Drop_Rate_1"))
		{
			pQuestDrop->aDropRate[0] = READ_FLOAT(bstrData, pstrDataName->c_str());
		}

		// 2
		else if (0 == wcscmp(pstrDataName->c_str(), L"Quest_Item_Index2"))
		{
			pQuestDrop->aQuestItemTblidx[1] = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Drop_Rate_2"))
		{
			pQuestDrop->aDropRate[1] = READ_FLOAT(bstrData, pstrDataName->c_str());
		}

		// 3
		else if (0 == wcscmp(pstrDataName->c_str(), L"Quest_Item_Index3"))
		{
			pQuestDrop->aQuestItemTblidx[2] = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Drop_Rate_3"))
		{
			pQuestDrop->aDropRate[2] = READ_FLOAT(bstrData, pstrDataName->c_str());
		}

		// 4
		else if (0 == wcscmp(pstrDataName->c_str(), L"Quest_Item_Index4"))
		{
			pQuestDrop->aQuestItemTblidx[3] = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Drop_Rate_4"))
		{
			pQuestDrop->aDropRate[3] = READ_FLOAT(bstrData, pstrDataName->c_str());
		}

		// 5
		else if (0 == wcscmp(pstrDataName->c_str(), L"Quest_Item_Index5"))
		{
			pQuestDrop->aQuestItemTblidx[4] = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Drop_Rate_5"))
		{
			pQuestDrop->aDropRate[4] = READ_FLOAT(bstrData, pstrDataName->c_str());
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


sTBLDAT* QuestDropTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool QuestDropTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sQUEST_DROP_TBLDAT* pTableData = new sQUEST_DROP_TBLDAT;
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

bool QuestDropTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sQUEST_DROP_TBLDAT* pTableData = (sQUEST_DROP_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}