#include "stdafx.h"
#include "ItemUpgradeTable.h"
#include "NtlBattle.h"
#include "Serializer.h"

WCHAR* ItemUpgradeTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

ItemUpgradeTable::ItemUpgradeTable(void)
{
	Init();
}

ItemUpgradeTable::~ItemUpgradeTable(void)
{
	Destroy();
}

bool ItemUpgradeTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void ItemUpgradeTable::Destroy()
{
	Table::Destroy();
}

void ItemUpgradeTable::Init()
{
}

void* ItemUpgradeTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sITEM_UPGRADE_TBLDAT* pNewItem = new sITEM_UPGRADE_TBLDAT;
		if (NULL == pNewItem)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewItem;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewItem;
	}

	return NULL;
}

bool ItemUpgradeTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sITEM_UPGRADE_TBLDAT* pItem = (sITEM_UPGRADE_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pItem, sizeof(*pItem)))
			return false;

		delete pItem;
		return true;
	}

	return false;
}

bool ItemUpgradeTable::AddTable(void * pvTable, bool bReload)
{
	sITEM_UPGRADE_TBLDAT * pTbldat = (sITEM_UPGRADE_TBLDAT*)pvTable;
	sITEM_UPGRADE_TBLDAT * pExistTbldat = NULL;

	if (true == bReload)
	{
		pExistTbldat = (sITEM_UPGRADE_TBLDAT*)FindData(pTbldat->tblidx);
		if (pExistTbldat)
		{
			CopyMemory(pTbldat, pExistTbldat, pTbldat->GetDataSize());
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

bool ItemUpgradeTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{

	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sITEM_UPGRADE_TBLDAT* pItem = (sITEM_UPGRADE_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pItem->tblidx = READ_DWORD(bstrData);
		}
	}
	else
	{
		return false;
	}

	return true;
}


sTBLDAT* ItemUpgradeTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
	{
		return NULL;
	}

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
	{
		return NULL;
	}

	return (sTBLDAT*)(iter->second);
}

bool ItemUpgradeTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sITEM_UPGRADE_TBLDAT* pTableData = new sITEM_UPGRADE_TBLDAT;
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

bool ItemUpgradeTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sITEM_UPGRADE_TBLDAT* pTableData = (sITEM_UPGRADE_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}