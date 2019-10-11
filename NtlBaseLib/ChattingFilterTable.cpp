#include "StdAfx.h"
#include "ChattingFilterTable.h"
#include "Serializer.h"

WCHAR* ChattingFilterTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

ChattingFilterTable::ChattingFilterTable(void)
{
	Init();
}

ChattingFilterTable::~ChattingFilterTable(void)
{
	Destroy();
}

bool ChattingFilterTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void ChattingFilterTable::Destroy()
{
	Table::Destroy();
}

void ChattingFilterTable::Init()
{
}

void* ChattingFilterTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHAT_FILTER_TBLDAT* pFilter = new sCHAT_FILTER_TBLDAT;
		if (NULL == pFilter)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pFilter;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pFilter;
	}

	return NULL;
}

bool ChattingFilterTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHAT_FILTER_TBLDAT* pFilter = (sCHAT_FILTER_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pFilter, sizeof(*pFilter)))
			return false;

		delete pFilter;

		return true;
	}

	return false;
}

bool ChattingFilterTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sCHAT_FILTER_TBLDAT* pTbldat = (sCHAT_FILTER_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}


	return true;
}

bool ChattingFilterTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHAT_FILTER_TBLDAT* pFilter = (sCHAT_FILTER_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Chatting_Filter_Tblidx"))
		{
			pFilter->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Slang_Text"))
		{
			READ_STRINGW(bstrData, pFilter->wszSlangText, _countof(pFilter->wszSlangText));
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Filtering_Text_Index"))
		{
			pFilter->filteringTextIndex = READ_DWORD(bstrData);
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


sTBLDAT* ChattingFilterTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool ChattingFilterTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sCHAT_FILTER_TBLDAT* pTableData = new sCHAT_FILTER_TBLDAT;
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

bool ChattingFilterTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sCHAT_FILTER_TBLDAT* pTableData = (sCHAT_FILTER_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}