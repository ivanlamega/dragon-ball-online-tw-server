#include "StdAfx.h"
#include "ExpTable.h"
#include "Serializer.h"

WCHAR* ExpTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

ExpTable::ExpTable(void)
{
	Init();
}

ExpTable::~ExpTable(void)
{
	Destroy();
}

bool ExpTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void ExpTable::Destroy()
{
	Table::Destroy();
}

void ExpTable::Init()
{
}

void* ExpTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sEXP_TBLDAT* pNewExp = new sEXP_TBLDAT;
		if (NULL == pNewExp)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewExp;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewExp;
	}

	return NULL;
}

bool ExpTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sEXP_TBLDAT* pExp = (sEXP_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pExp, sizeof(*pExp)))
			return false;

		delete pExp;

		return true;
	}

	return false;
}

bool ExpTable::AddTable(void * pvTable, bool bReload)
{
	sEXP_TBLDAT * pTbldat = (sEXP_TBLDAT*)pvTable;
	sEXP_TBLDAT * pExistTbldat = NULL;

	// Reload인경우 Data를 찾아 Update해준다
	if (bReload)
	{
		pExistTbldat = (sEXP_TBLDAT*)FindData(pTbldat->tblidx);
		if (pExistTbldat)
		{
			CopyMemory(pTbldat, pExistTbldat, pTbldat->GetDataSize());
			// 데이타의 해제를 위한 false 반환
			return true;
		}
	}

	if (false == m_mapTableList.insert(std::map<TBLIDX, sTBLDAT*>::value_type(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}

	return true;
}

bool ExpTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sEXP_TBLDAT* pExp = (sEXP_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Level"))
		{
			pExp->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"EXP"))
		{
			pExp->dwExp = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Need_EXP"))
		{
			pExp->dwNeed_Exp = READ_DWORD(bstrData);
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


sTBLDAT* ExpTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool ExpTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sEXP_TBLDAT* pTableData = new sEXP_TBLDAT;
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

bool ExpTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sEXP_TBLDAT* pTableData = (sEXP_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}