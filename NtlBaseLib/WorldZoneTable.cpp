#include "StdAfx.h"
#include "WorldZoneTable.h"
#include "Serializer.h"

WCHAR* WorldZoneTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

WorldZoneTable::WorldZoneTable(void)
{
	Init();
}

WorldZoneTable::~WorldZoneTable(void)
{
	Destroy();
}

bool WorldZoneTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void WorldZoneTable::Destroy()
{
	Table::Destroy();
}

void WorldZoneTable::Init()
{
}

void* WorldZoneTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sWORLD_ZONE_TBLDAT* pNewWorldZone = new sWORLD_ZONE_TBLDAT;
		if (NULL == pNewWorldZone)
		{
			return NULL;
		}

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewWorldZone;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewWorldZone;
	}

	return NULL;
}

bool WorldZoneTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sWORLD_ZONE_TBLDAT* pWorldZone = (sWORLD_ZONE_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pWorldZone, sizeof(*pWorldZone)))
		{
			return false;
		}

		delete pWorldZone;

		return true;
	}

	return false;
}

bool WorldZoneTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sWORLD_ZONE_TBLDAT* pTbldat = (sWORLD_ZONE_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}

	return true;
}

bool WorldZoneTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sWORLD_ZONE_TBLDAT* pWorldZone = (sWORLD_ZONE_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pWorldZone->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Function_Bit_Flag"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pWorldZone->wFunctionBitFlag = (WORD)READ_BITFLAG(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"World"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pWorldZone->worldTblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Name"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pWorldZone->nameTblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Name_Text"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);

			READ_STRINGW(bstrData, pWorldZone->wszName_Text, _countof(pWorldZone->wszName_Text));
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Forbidden_Vehicle"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pWorldZone->bForbidden_Vehicle = READ_BOOL(bstrData, pstrDataName->c_str());
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


sTBLDAT* WorldZoneTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
	{
		return NULL;
	}

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool WorldZoneTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sWORLD_ZONE_TBLDAT* pTableData = new sWORLD_ZONE_TBLDAT;
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

bool WorldZoneTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sWORLD_ZONE_TBLDAT* pTableData = (sWORLD_ZONE_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}