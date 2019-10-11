#include "stdafx.h"
#include "QuestItemTable.h"
#include "Serializer.h"

WCHAR* QuestItemTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

QuestItemTable::QuestItemTable(void)
{
	Init();
}

QuestItemTable::~QuestItemTable(void)
{
	Destroy();
}

bool QuestItemTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void QuestItemTable::Destroy(void)
{
	Table::Destroy();
}

void QuestItemTable::Init(void)
{
}

void* QuestItemTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUESTITEM_TBLDAT* pNewObj = new sQUESTITEM_TBLDAT;
		if (NULL == pNewObj) return NULL;

		CPINFO cpInfo;
		if (!GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewObj;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewObj;
	}

	return NULL;
}

bool QuestItemTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUESTITEM_TBLDAT* pObj = (sQUESTITEM_TBLDAT*)pvTable;
		if (IsBadReadPtr(pObj, sizeof(*pObj))) return false;

		delete pObj;

		return true;
	}

	return false;
}

bool QuestItemTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sQUESTITEM_TBLDAT* pTbldat = (sQUESTITEM_TBLDAT*)pvTable;
	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}


	return true;
}

bool QuestItemTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sQUESTITEM_TBLDAT* pObj = (sQUESTITEM_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Item_Tblidx"))
		{
			pObj->tblidx = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Item_Name"))
		{
			pObj->ItemName = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Icon_Name"))
		{
			READ_STRING(bstrData, pObj->szIconName, _countof(pObj->szIconName));
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Note"))
		{
			pObj->Note = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Function_Bit_Flag"))
		{
			pObj->byFunctionBitFlag = (BYTE)READ_BITFLAG(bstrData);
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


sTBLDAT* QuestItemTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx) return NULL;

	TABLEIT iter = m_mapTableList.find(tblidx);
	if (m_mapTableList.end() == iter) return NULL;

	return (sTBLDAT*)(iter->second);
}

bool QuestItemTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sQUESTITEM_TBLDAT* pTableData = new sQUESTITEM_TBLDAT;
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

bool QuestItemTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sQUESTITEM_TBLDAT* pTableData = (sQUESTITEM_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}