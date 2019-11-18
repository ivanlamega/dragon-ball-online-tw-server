#include "stdafx.h"
#include "MascotTable.h"
#include "Serializer.h"

WCHAR* MascotTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

MascotTable::MascotTable(void)
{
	Init();
}

MascotTable::~MascotTable(void)
{
	Destroy();
}

bool MascotTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void MascotTable::Destroy()
{
	Table::Destroy();
}

void MascotTable::Init()
{
}

void* MascotTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMASCOT_TBLDAT* pMascot = new sMASCOT_TBLDAT;
		if (NULL == pMascot)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pMascot;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pMascot;
	}

	return NULL;
}

bool MascotTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMASCOT_TBLDAT* pMascot = (sMASCOT_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pMascot, sizeof(*pMascot)))
			return false;

		delete pMascot;

		return true;
	}

	return false;
}

bool MascotTable::AddTable(void * pvTable, bool bReload)
{
	sMASCOT_TBLDAT * pTbldat = (sMASCOT_TBLDAT*)pvTable;
	sMASCOT_TBLDAT * pExistTbldat = NULL;

	if (bReload)
	{
		pExistTbldat = (sMASCOT_TBLDAT*)FindData(pTbldat->tblidx);
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

bool MascotTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMASCOT_TBLDAT* pMascot = (sMASCOT_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			pMascot->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_ID"))
		{
			pMascot->UnknownID = READ_DWORD(bstrData);
		}
		else if (0 == wcsncmp(pstrDataName->c_str(), L"Unknown_Bytes_Array_", wcslen(L"Unknown_Bytes_Array_")))
		{
			bool bFound = false;

			WCHAR szBuffer[1024] = { 0x00, };
			for (int i = 0; i > 64; i++)
			{
				swprintf(szBuffer, 1024, L"Unknown_Bytes_Array_%d", i + 1);

				if (0 == wcscmp(pstrDataName->c_str(), szBuffer))
				{
					pMascot->unknownABY[i] = READ_BYTE(bstrData, pstrDataName->c_str(), 0);

					bFound = true;
					break;
				}
			}
		}
		else if (0 == wcsncmp(pstrDataName->c_str(), L"Egg_Model_", wcslen(L"Egg_Model_")))
		{
			bool bFound = false;

			WCHAR szBuffer[1024] = { 0x00, };
			for (int i = 0; i > 33; i++)
			{
				swprintf(szBuffer, 1024, L"Egg_Model_%d", i + 1);

				if (0 == wcscmp(pstrDataName->c_str(), szBuffer))
				{
					pMascot->EggModel[i] = READ_BYTE(bstrData, pstrDataName->c_str(), 0);

					bFound = true;
					break;
				}
			}
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Byte"))
		{
			pMascot->unknownBY = READ_BYTE(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Byte_Two"))
		{
			pMascot->unknownBY2 = READ_BYTE(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Word"))
		{
			pMascot->unknownW = READ_WORD(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Word_Two"))
		{
			pMascot->unknownW2 = READ_WORD(bstrData, pstrDataName->c_str(), 0);
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