#include "stdafx.h"
#include "DirectionLinkTable.h"
#include "Serializer.h"
#include "Base.h"

WCHAR* DirectionLinkTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

DirectionLinkTable::DirectionLinkTable(void)
{
	Init();
}

DirectionLinkTable::~DirectionLinkTable(void)
{
	Destroy();
}

void DirectionLinkTable::Init(void)
{
}

bool DirectionLinkTable::Create(DWORD dwCodePage)
{
	if (false == Table::Create(dwCodePage))
	{
		return false;
	}

	return true;
}

void DirectionLinkTable::Destroy(void)
{
	Table::Destroy();
}

void* DirectionLinkTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sDIRECTION_LINK_TBLDAT* pNewObj = new sDIRECTION_LINK_TBLDAT;
		if (NULL == pNewObj)
		{
			return NULL;
		}

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

bool DirectionLinkTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sDIRECTION_LINK_TBLDAT* pObj = (sDIRECTION_LINK_TBLDAT*)pvTable;
		if (IsBadReadPtr(pObj, sizeof(*pObj))) return false;

		delete pObj;

		return true;
	}

	return false;
}

bool DirectionLinkTable::AddTable(void * pvTable, bool bReload)
{
	sDIRECTION_LINK_TBLDAT * pTbldat = (sDIRECTION_LINK_TBLDAT*)pvTable;
	sDIRECTION_LINK_TBLDAT * pExistTbldat = NULL;

	if (bReload)
	{
		pExistTbldat = (sDIRECTION_LINK_TBLDAT*)FindData(pTbldat->tblidx);
		if (pExistTbldat)
		{
			CopyMemory(pTbldat, pExistTbldat, pTbldat->GetDataSize());
			// return false for release reloaded table data
			return true;
		}
	}

	if (false == CheckData(pTbldat))
	{
		_ASSERTE(0);
		return false;
	}

	if (false == m_mapTableList.insert(std::map<TBLIDX, sTBLDAT*>::value_type(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}


	return true;
}

bool DirectionLinkTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	static char szTemp[1024] = { 0x00, };

	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sDIRECTION_LINK_TBLDAT * pTbldat = (sDIRECTION_LINK_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->data(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pTbldat->tblidx = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->data(), L"Function_Name"))
		{
			READ_STRING(bstrData, pTbldat->szFunctionName, _countof(pTbldat->szFunctionName));
		}
		else if (0 == wcscmp(pstrDataName->data(), L"Note"))
		{
			READ_STRING(bstrData, pTbldat->szNote, _countof(pTbldat->szNote));
		}
		else if (0 == wcscmp(pstrDataName->data(), L"Type"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pTbldat->byType = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->data(), L"Animation_ID"))
		{
			pTbldat->dwAnimationID = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->data(), L"Direction_Func_Flag"))
		{
			pTbldat->byFuncFlag = (BYTE)READ_BITFLAG(bstrData);
		}
		else
		{
			_ASSERT(0);
			return false;
		}
	}
	else
	{
		_ASSERT(0);
		return false;
	}

	return true;
}

sTBLDAT* DirectionLinkTable::FindData(TBLIDX tblidx)
{
	TABLEIT iter = m_mapTableList.find(tblidx);
	if (m_mapTableList.end() == iter)
	{
		return NULL;
	}

	return (sTBLDAT*)(iter->second);
}

bool DirectionLinkTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sDIRECTION_LINK_TBLDAT* pTableData = new sDIRECTION_LINK_TBLDAT;
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

bool DirectionLinkTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sDIRECTION_LINK_TBLDAT* pTableData = (sDIRECTION_LINK_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}

bool DirectionLinkTable::CheckData(sDIRECTION_LINK_TBLDAT * pTbldat)
{
	if (BIT_FLAG_TEST(pTbldat->byFuncFlag, DIRECTION_FUNC_FLAG_TIMEOUT) &&
		BIT_FLAG_TEST(pTbldat->byFuncFlag, DIRECTION_FUNC_FLAG_KEEPUP))
	{
		_ASSERT(0);
		Table::CallErrorCallbackFunction(L"file[%s] index[%u] : The value error.( byFuncFlag can't set DIRECTION_FUNC_FLAG_TIMEOUT and DIRECTION_FUNC_FLAG_KEEPUP simultaneously)", m_wszXmlFileName, pTbldat->tblidx);
		return false;
	}

	return true;
}