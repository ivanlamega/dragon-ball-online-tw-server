#include "StdAfx.h"
#include "SetItemTable.h"
#include "Serializer.h"

WCHAR* SetItemTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

SetItemTable::SetItemTable(void)
{
	Init();
}

SetItemTable::~SetItemTable(void)
{
	Destroy();
}

bool SetItemTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void SetItemTable::Destroy()
{
	Table::Destroy();
}

void SetItemTable::Init()
{
}

void* SetItemTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSET_ITEM_TBLDAT* pSetItem = new sSET_ITEM_TBLDAT;
		if (NULL == pSetItem)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pSetItem;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pSetItem;
	}

	return NULL;
}

bool SetItemTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSET_ITEM_TBLDAT* pSetItem = (sSET_ITEM_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pSetItem, sizeof(*pSetItem)))
			return false;

		delete pSetItem;

		return true;
	}

	return false;
}

bool SetItemTable::AddTable(void * pvTable, bool bReload)
{
	sSET_ITEM_TBLDAT * pTbldat = (sSET_ITEM_TBLDAT*)pvTable;
	sSET_ITEM_TBLDAT * pExistTbldat = NULL;

	if (false == pTbldat->bValidity_Able)
	{
		return false;
	}

	if (bReload)
	{
		pExistTbldat = (sSET_ITEM_TBLDAT*)FindData(pTbldat->tblidx);
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

bool SetItemTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSET_ITEM_TBLDAT* pSetItem = (sSET_ITEM_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			pSetItem->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Validity_Able"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pSetItem->bValidity_Able = READ_BOOL(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Semi_Set_Option"))
		{
			pSetItem->semiSetOption = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Full_Set_Option"))
		{
			pSetItem->fullSetOption = READ_DWORD(bstrData);
		}
		else if (0 == wcsncmp(pstrDataName->c_str(), L"Item_Tblidx_", wcslen(L"Item_Tblidx_")))
		{
			bool bFound = false;

			WCHAR szBuffer[1024] = { 0x00, };
			for (int i = 0; i < MAX_SET_ITEM_COUNT; i++)
			{
				swprintf(szBuffer, 1024, L"Item_Tblidx_%d", i + 1);

				if (0 == wcscmp(pstrDataName->c_str(), szBuffer))
				{
					pSetItem->aItemTblidx[i] = READ_DWORD(bstrData);

					bFound = true;
					break;
				}
			}

			if (false == bFound)
			{
				Table::CallErrorCallbackFunction(L"[File] : %s\n[Error] : Unknown field name found!(Field Name = %s)", m_wszXmlFileName, pstrDataName->c_str());
				return false;
			}
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


sTBLDAT* SetItemTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool SetItemTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sSET_ITEM_TBLDAT* pTableData = new sSET_ITEM_TBLDAT;
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

bool SetItemTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sSET_ITEM_TBLDAT* pTableData = (sSET_ITEM_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}