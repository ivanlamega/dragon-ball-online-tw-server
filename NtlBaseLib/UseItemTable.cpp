#include "stdafx.h"
#include "NtlSkill.h"
#include "UseItemTable.h"
#include "SystemEffectTable.h"
#include "Serializer.h"

WCHAR* UseItemTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

UseItemTable::UseItemTable(void)
{
	Init();
}

UseItemTable::~UseItemTable(void)
{
	Destroy();
}

bool UseItemTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void UseItemTable::Destroy()
{
	Table::Destroy();
}

void UseItemTable::Init()
{
}

void* UseItemTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sUSE_ITEM_TBLDAT* pNewItem = new sUSE_ITEM_TBLDAT;
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

bool UseItemTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sUSE_ITEM_TBLDAT* pItem = (sUSE_ITEM_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pItem, sizeof(*pItem)))
			return false;

		delete pItem;

		return true;
	}

	return false;
}

bool UseItemTable::AddTable(void * pvTable, bool bReload)
{
	sUSE_ITEM_TBLDAT* pTbldat = (sUSE_ITEM_TBLDAT*)pvTable;
	sUSE_ITEM_TBLDAT * pExistTbldat = NULL;

	if (bReload)
	{
		pExistTbldat = (sUSE_ITEM_TBLDAT*)FindData(pTbldat->tblidx);
		if (pExistTbldat)
		{
			CopyMemory(pTbldat, pExistTbldat, pTbldat->GetDataSize());
			// 데이타의 해제를 위한 false 반환
			return true;
		}
	}

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}


	return true;
}

bool UseItemTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sUSE_ITEM_TBLDAT* pItem = (sUSE_ITEM_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pItem->tblidx = READ_DWORD(bstrData);
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


sTBLDAT* UseItemTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool UseItemTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sUSE_ITEM_TBLDAT* pTableData = new sUSE_ITEM_TBLDAT;
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

bool UseItemTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sUSE_ITEM_TBLDAT* pTableData = (sUSE_ITEM_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}