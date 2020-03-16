#include "StdAfx.h"
#include "ItemEnchantTable.h"

WCHAR* ItemEnchantTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

ItemEnchantTable::ItemEnchantTable(void)
{
	Init();
}

ItemEnchantTable::~ItemEnchantTable(void)
{
	Destroy();
}

bool ItemEnchantTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void ItemEnchantTable::Destroy()
{

	Table::Destroy();
}

void ItemEnchantTable::Init()
{
}

void* ItemEnchantTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sITEM_ENCHANT_TBLDAT* pNewItemEnchant = new sITEM_ENCHANT_TBLDAT;
		if (NULL == pNewItemEnchant)
		{
			return NULL;
		}

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewItemEnchant;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewItemEnchant;
	}

	return NULL;
}

bool ItemEnchantTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sITEM_ENCHANT_TBLDAT* pItemEnchant = (sITEM_ENCHANT_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pItemEnchant, sizeof(*pItemEnchant)))
		{
			return false;
		}

		delete pItemEnchant;

		return true;
	}

	return false;
}

bool ItemEnchantTable::AddTable(void* pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sITEM_ENCHANT_TBLDAT* pTbldat = (sITEM_ENCHANT_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated.", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}
	return true;
}

bool ItemEnchantTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sITEM_ENCHANT_TBLDAT* pItemEnchant = (sITEM_ENCHANT_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pItemEnchant->tblidx = READ_DWORD(bstrData);
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


sTBLDAT* ItemEnchantTable::FindData(TBLIDX tblidx)
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

bool ItemEnchantTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sITEM_ENCHANT_TBLDAT* pTableData = new sITEM_ENCHANT_TBLDAT;
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

bool ItemEnchantTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sITEM_ENCHANT_TBLDAT* pTableData = (sITEM_ENCHANT_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}