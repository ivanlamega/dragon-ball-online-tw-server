#include "stdafx.h"
#include "VehicleTable.h"
#include "NtlBattle.h"
#include "Serializer.h"

WCHAR* VehicleTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

VehicleTable::VehicleTable(void)
{
	Init();
}

VehicleTable::~VehicleTable(void)
{
	Destroy();
}

bool VehicleTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void VehicleTable::Destroy()
{
	Table::Destroy();
}

void VehicleTable::Init()
{
}

void* VehicleTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sVEHICLE_TBLDAT* pNewItem = new sVEHICLE_TBLDAT;
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

bool VehicleTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sVEHICLE_TBLDAT* pItem = (sVEHICLE_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pItem, sizeof(*pItem)))
			return false;

		delete pItem;
		return true;
	}

	return false;
}

bool VehicleTable::AddTable(void * pvTable, bool bReload)
{
	sVEHICLE_TBLDAT * pTbldat = (sVEHICLE_TBLDAT*)pvTable;
	sVEHICLE_TBLDAT * pExistTbldat = NULL;

	if (true == bReload)
	{
		pExistTbldat = (sVEHICLE_TBLDAT*)FindData(pTbldat->tblidx);
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

bool VehicleTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{

	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sVEHICLE_TBLDAT* pItem = (sVEHICLE_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pItem->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Model_Name"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			READ_STRING(bstrData, pItem->szModelName, _countof(pItem->szModelName));
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"SRP_Type"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pItem->bySRPType = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Speed"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pItem->bySpeed = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Vehicle_Type"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pItem->byVehicleType = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Run_Height"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pItem->wRunHeight = READ_WORD(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Personnel"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pItem->byPersonnel = READ_BYTE(bstrData, pstrDataName->c_str());
		}
	}
	else
	{
		return false;
	}

	return true;
}


sTBLDAT* VehicleTable::FindData(TBLIDX tblidx)
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

bool VehicleTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sVEHICLE_TBLDAT* pTableData = new sVEHICLE_TBLDAT;
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

bool VehicleTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sVEHICLE_TBLDAT* pTableData = (sVEHICLE_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}