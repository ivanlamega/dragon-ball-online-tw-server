#include "StdAfx.h"
#include "SuperiorDropTable.h"
#include "Serializer.h"

WCHAR* SuperiorDropTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

SuperiorDropTable::SuperiorDropTable(void)
{
	Init();
}

SuperiorDropTable::~SuperiorDropTable(void)
{
	Destroy();
}

bool SuperiorDropTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void SuperiorDropTable::Destroy()
{
	Table::Destroy();
}

void SuperiorDropTable::Init()
{
}

void* SuperiorDropTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSUPERIOR_DROP_TBLDAT* pDrop = new sSUPERIOR_DROP_TBLDAT;
		if (NULL == pDrop)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pDrop;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pDrop;
	}

	return NULL;
}

bool SuperiorDropTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSUPERIOR_DROP_TBLDAT* pDrop = (sSUPERIOR_DROP_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pDrop, sizeof(*pDrop)))
			return false;

		delete pDrop;

		return true;
	}

	return false;
}

bool SuperiorDropTable::AddTable(void * pvTable, bool bReload)
{
	sSUPERIOR_DROP_TBLDAT * pTbldat = (sSUPERIOR_DROP_TBLDAT*)pvTable;
	sSUPERIOR_DROP_TBLDAT * pExistTbldat = NULL;

	if (bReload)
	{
		pExistTbldat = (sSUPERIOR_DROP_TBLDAT*)FindData(pTbldat->tblidx);
		if (pExistTbldat)
		{
			CopyMemory(pTbldat, pExistTbldat, pTbldat->GetDataSize());
			// return false for release reloaded table data
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

bool SuperiorDropTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSUPERIOR_DROP_TBLDAT* pDrop = (sSUPERIOR_DROP_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			pDrop->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Max_Quality"))
		{
			pDrop->byMax_Quality = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Option_Rate"))
		{
			pDrop->fOption_Rate = READ_FLOAT(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcsncmp(pstrDataName->c_str(), L"Item_Tblidx_", wcslen(L"Item_Tblidx_")))
		{
			bool bFound = false;

			WCHAR szBuffer[1024] = { 0x00, };
			for (int i = 0; i < MAX_SUPERIOR_DROP; i++)
			{
				swprintf(szBuffer, 1024, L"Item_Tblidx_%d", i + 1);

				if (0 == wcscmp(pstrDataName->c_str(), szBuffer))
				{
					pDrop->aItem_Tblidx[i] = READ_DWORD(bstrData);

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
		else if (0 == wcsncmp(pstrDataName->c_str(), L"Drop_Rate_", wcslen(L"Drop_Rate_")))
		{
			bool bFound = false;

			WCHAR szBuffer[1024] = { 0x00, };
			for (int i = 0; i < MAX_SUPERIOR_DROP; i++)
			{
				swprintf(szBuffer, 1024, L"Drop_Rate_%d", i + 1);

				if (0 == wcscmp(pstrDataName->c_str(), szBuffer))
				{
					pDrop->afDrop_Rate[i] = READ_FLOAT(bstrData, pstrDataName->c_str(), 0.0f);

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


sTBLDAT* SuperiorDropTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

TBLIDX SuperiorDropTable::FindDropIndex(sSUPERIOR_DROP_TBLDAT* psTblData, BYTE byIndex)
{
	if (MAX_SUPERIOR_DROP <= byIndex || 0 > byIndex)
		return INVALID_TBLIDX;

	return psTblData->aItem_Tblidx[byIndex];
}

float SuperiorDropTable::FindDropRate(sSUPERIOR_DROP_TBLDAT* psTblData, BYTE byIndex)
{
	if (MAX_SUPERIOR_DROP <= byIndex || 0 > byIndex)
		return 0.0f;

	return psTblData->afDrop_Rate[byIndex];
}

bool SuperiorDropTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sSUPERIOR_DROP_TBLDAT* pTableData = new sSUPERIOR_DROP_TBLDAT;
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

bool SuperiorDropTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sSUPERIOR_DROP_TBLDAT* pTableData = (sSUPERIOR_DROP_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}