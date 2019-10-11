#include "StdAfx.h"
#include "WorldPlayTable.h"
#include "Serializer.h"

WCHAR* WorldPlayTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};


WorldPlayTable::WorldPlayTable(void)
{
	Init();
}

WorldPlayTable::~WorldPlayTable(void)
{
	Destroy();
}

bool WorldPlayTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void WorldPlayTable::Destroy()
{
	Table::Destroy();
}

void WorldPlayTable::Init()
{
}

void* WorldPlayTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sWORLDPLAY_TBLDAT * pNewWorldPlay = new sWORLDPLAY_TBLDAT;
		if (NULL == pNewWorldPlay)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewWorldPlay;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewWorldPlay;
	}

	return NULL;
}

bool WorldPlayTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sWORLDPLAY_TBLDAT * pWorldPlay = (sWORLDPLAY_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pWorldPlay, sizeof(*pWorldPlay)))
			return false;

		delete pWorldPlay;

		return true;
	}

	return false;
}


bool WorldPlayTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sWORLDPLAY_TBLDAT* pTbldat = (sWORLDPLAY_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}

	return true;
}


bool WorldPlayTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sWORLDPLAY_TBLDAT* pTbldat = (sWORLDPLAY_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pTbldat->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Group"))
		{
			pTbldat->dwGroup = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"ExecuterType"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pTbldat->byExecuterType = READ_BYTE(bstrData, pstrDataName->c_str());

			if (WORLDPLAY_EXECUTER_TYPE_COUNT <= pTbldat->byExecuterType)
			{
				_ASSERTE(0);
				return false;
			}
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"ShareType"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pTbldat->byShareType = READ_BYTE(bstrData, pstrDataName->c_str());

			if (WORLDPLAY_SHARE_TYPE_COUNT <= pTbldat->byShareType)
			{
				_ASSERTE(0);
				return false;
			}
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"ShareLimitTime"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pTbldat->dwShareLimitTime = READ_DWORD(bstrData);
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


sTBLDAT* WorldPlayTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}


bool WorldPlayTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sWORLDPLAY_TBLDAT* pTableData = new sWORLDPLAY_TBLDAT;
		if (NULL == pTableData)
		{
			Destroy();
			return false;
		}

		if (false == pTableData->LoadFromBinary(serializer))
		{
			delete pTableData;
			bLoop = false;
			break;
		}
		if (false == AddTable(pTableData, bReload))
		{
			delete pTableData;
		}

	} while (false != bLoop);

	return true;
}

bool WorldPlayTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sWORLDPLAY_TBLDAT* pTableData = (sWORLDPLAY_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}