#include "StdAfx.h"
#include "CharmTable.h"
#include "Serializer.h"

WCHAR* CharmTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

CharmTable::CharmTable(void)
{
	Init();
}

CharmTable::~CharmTable(void)
{
	Destroy();
}

bool CharmTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void CharmTable::Destroy()
{
	Table::Destroy();
}

void CharmTable::Init()
{
}

void* CharmTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHARM_TBLDAT* pNewCharm = new sCHARM_TBLDAT;
		if (NULL == pNewCharm)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewCharm;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewCharm;
	}

	return NULL;
}

bool CharmTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHARM_TBLDAT* pCharm = (sCHARM_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pCharm, sizeof(*pCharm)))
			return false;

		delete pCharm;

		return true;
	}

	return false;
}

bool CharmTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sCHARM_TBLDAT * pTbldat = (sCHARM_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}


	return true;
}

bool CharmTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	sCHARM_TBLDAT* pCharm = (sCHARM_TBLDAT*)pvTable;

	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pCharm->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Drop_Rate"))
		{
			pCharm->wDrop_Rate = READ_WORD(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"EXP"))
		{
			pCharm->wEXP = READ_WORD(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"RP_Sharing"))
		{
			pCharm->wRP_Sharing = READ_WORD(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Cool_Time"))
		{
			pCharm->wCool_Time = READ_WORD(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Keep_Time"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pCharm->wKeep_Time = READ_WORD(bstrData, pstrDataName->c_str());
			pCharm->dwKeep_Time_In_Millisecs = pCharm->wKeep_Time * 1000;
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Need_Zenny"))
		{
			pCharm->dwNeed_Zenny = READ_DWORD(bstrData, 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Dice_Min"))
		{
			pCharm->byDice_Min = READ_BYTE(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Dice_Max"))
		{
			pCharm->byDice_Max = READ_BYTE(bstrData, pstrDataName->c_str(), 0xFF);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Charm_Type_Bit_Flag"))
		{
			pCharm->byCharm_Type_Bit_Flag = READ_BYTE(bstrData, pstrDataName->c_str(), 0);
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


sTBLDAT* CharmTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool CharmTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sCHARM_TBLDAT* pTableData = new sCHARM_TBLDAT;
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

bool CharmTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sCHARM_TBLDAT* pTableData = (sCHARM_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}