#include "stdafx.h"
#include "ItemRecipeTable2.h"
#include "NtlBattle.h"
#include "Serializer.h"

WCHAR* ItemRecipeTable2::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

ItemRecipeTable2::ItemRecipeTable2(void)
{
	Init();
}

ItemRecipeTable2::~ItemRecipeTable2(void)
{
	Destroy();
}

bool ItemRecipeTable2::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void ItemRecipeTable2::Destroy()
{
	Table::Destroy();
}

void ItemRecipeTable2::Init()
{
}

void* ItemRecipeTable2::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sITEM_RECIPE_TBLDAT2* pNewItem = new sITEM_RECIPE_TBLDAT2;
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

bool ItemRecipeTable2::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sITEM_RECIPE_TBLDAT2* pItem = (sITEM_RECIPE_TBLDAT2*)pvTable;
		if (FALSE != IsBadReadPtr(pItem, sizeof(*pItem)))
			return false;

		delete pItem;

		return true;
	}

	return false;
}

bool ItemRecipeTable2::AddTable(void * pvTable, bool bReload)
{
	sITEM_RECIPE_TBLDAT2 * pTbldat = (sITEM_RECIPE_TBLDAT2*)pvTable;
	sITEM_RECIPE_TBLDAT2 * pExistTbldat = NULL;

	if (bReload)
	{
		pExistTbldat = (sITEM_RECIPE_TBLDAT2*)FindData(pTbldat->tblidx);
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

bool ItemRecipeTable2::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{

	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sITEM_RECIPE_TBLDAT2* pItem = (sITEM_RECIPE_TBLDAT2*)pvTable;

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


sTBLDAT* ItemRecipeTable2::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool ItemRecipeTable2::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sITEM_RECIPE_TBLDAT2* pTableData = new sITEM_RECIPE_TBLDAT2;
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

bool ItemRecipeTable2::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sITEM_RECIPE_TBLDAT2* pTableData = (sITEM_RECIPE_TBLDAT2*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}