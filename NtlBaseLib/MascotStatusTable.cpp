#include "stdafx.h"
#include "MascotStatusTable.h"
#include "Serializer.h"

WCHAR* MascotStatusTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

MascotStatusTable::MascotStatusTable(void)
{
	Init();
}

MascotStatusTable::~MascotStatusTable(void)
{
	Destroy();
}

bool MascotStatusTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void MascotStatusTable::Destroy()
{
	Table::Destroy();
}

void MascotStatusTable::Init()
{
}

void* MascotStatusTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMASCOT_STATUS_TBLDAT* pMascotStatus = new sMASCOT_STATUS_TBLDAT;
		if (NULL == pMascotStatus)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pMascotStatus;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pMascotStatus;
	}

	return NULL;
}

bool MascotStatusTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMASCOT_STATUS_TBLDAT* pMascotStatus = (sMASCOT_STATUS_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pMascotStatus, sizeof(*pMascotStatus)))
			return false;

		delete pMascotStatus;

		return true;
	}

	return false;
}

bool MascotStatusTable::AddTable(void * pvTable, bool bReload)
{
	sMASCOT_STATUS_TBLDAT * pTbldat = (sMASCOT_STATUS_TBLDAT*)pvTable;
	sMASCOT_STATUS_TBLDAT * pExistTbldat = NULL;

	if (bReload)
	{
		pExistTbldat = (sMASCOT_STATUS_TBLDAT*)FindData(pTbldat->tblidx);
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
bool MascotStatusTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMASCOT_STATUS_TBLDAT* pMascotStatus = (sMASCOT_STATUS_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			pMascotStatus->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_ID"))
		{
			pMascotStatus->Unknown_ID = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_DW1"))
		{
			pMascotStatus->unknownDW = READ_DWORD(bstrData);
		}
		else if (0 == wcsncmp(pstrDataName->c_str(), L"Unknown_Bytes_Array_", wcslen(L"Unknown_Bytes_Array_")))
		{
			bool bFound = false;

			WCHAR szBuffer[1024] = { 0x00, };
			for (int i = 0; i > 62; i++)
			{
				swprintf(szBuffer, 1024, L"Unknown_Bytes_Array_%d", i + 1);

				if (0 == wcscmp(pstrDataName->c_str(), szBuffer))
				{
					pMascotStatus->UnknownABY[i] = READ_BYTE(bstrData, pstrDataName->c_str(), 0);

					bFound = true;
					break;
				}
			}
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Byte1"))
		{
			pMascotStatus->unknownby1 = READ_BYTE(bstrData, pstrDataName->c_str(), 0);
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
					pMascotStatus->EggModel[i] = READ_BYTE(bstrData, pstrDataName->c_str(), 0);

					bFound = true;
					break;
				}
			}
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Byte2"))
		{
			pMascotStatus->unknownby2 = READ_BYTE(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Byte3"))
		{
			pMascotStatus->unknownby3 = READ_BYTE(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Word"))
		{
			pMascotStatus->unknownW1 = READ_WORD(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Word2"))
		{
			pMascotStatus->unknownW2 = READ_WORD(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Word3"))
		{
			pMascotStatus->unknownW3 = READ_WORD(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Word4"))
		{
			pMascotStatus->unknownW4 = READ_WORD(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Word5"))
		{
			pMascotStatus->unknownW5 = READ_WORD(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Word6"))
		{
			pMascotStatus->unknownW6 = READ_WORD(bstrData, pstrDataName->c_str(), 0);
		}
		
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_DW2"))
		{
			pMascotStatus->unknownDW2 = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_DW3"))
		{
			pMascotStatus->unknownDW3 = READ_DWORD(bstrData);
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