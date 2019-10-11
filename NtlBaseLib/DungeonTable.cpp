
#include "stdafx.h"
#include "DungeonTable.h"
#include "Serializer.h"

WCHAR* DungeonTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

DungeonTable::DungeonTable(void)
{
	Init();
}

DungeonTable::~DungeonTable(void)
{
	Destroy();
}

void DungeonTable::Init(void)
{
}

bool DungeonTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void DungeonTable::Destroy(void)
{
	Table::Destroy();
}

void* DungeonTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sDUNGEON_TBLDAT* pNewObj = new sDUNGEON_TBLDAT;
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

bool DungeonTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sDUNGEON_TBLDAT* pObj = (sDUNGEON_TBLDAT*)pvTable;
		if (IsBadReadPtr(pObj, sizeof(*pObj))) return false;

		delete pObj;

		return true;
	}

	return false;
}

bool DungeonTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sDUNGEON_TBLDAT * pTbldat = (sDUNGEON_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}


	return true;
}

bool DungeonTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	static char szTemp[1024] = { 0x00, };

	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sDUNGEON_TBLDAT * pTbldat = (sDUNGEON_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			pTbldat->tblidx = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Dungeon_Type"))
		{
			pTbldat->byDungeonType = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Max_Member"))
		{
			pTbldat->byMaxMember = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Link_World"))
		{
			pTbldat->linkWorld = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Min_Level"))
		{
			pTbldat->byMinLevel = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Max_Level"))
		{
			pTbldat->byMaxLevel = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Need_Item"))
		{
			pTbldat->needItemTblidx = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Honor_Point"))
		{
			pTbldat->dwHonorPoint = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Wps_Tblidx"))
		{
			pTbldat->wpsTblidx = READ_TBLIDX(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Open_Cine"))
		{
			pTbldat->openCine = READ_TBLIDX(bstrData);
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

sTBLDAT* DungeonTable::FindData(TBLIDX tblidx)
{
	TABLEIT iter = m_mapTableList.find(tblidx);
	if (m_mapTableList.end() == iter)
	{
		return NULL;
	}

	return (sTBLDAT*)(iter->second);
}

bool DungeonTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sDUNGEON_TBLDAT* pTableData = new sDUNGEON_TBLDAT;
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

bool DungeonTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sDUNGEON_TBLDAT* pTableData = (sDUNGEON_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}
