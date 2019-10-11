#include "StdAfx.h"
#include "NtlSkill.h"
#include "SystemEffectTable.h"
#include "Serializer.h"

WCHAR* SystemEffectTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

SystemEffectTable::SystemEffectTable(void)
{
	Init();
}

SystemEffectTable::~SystemEffectTable(void)
{
	Destroy();
}

bool SystemEffectTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void SystemEffectTable::Destroy()
{
	Table::Destroy();
}

void SystemEffectTable::Init()
{
}

void* SystemEffectTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSYSTEM_EFFECT_TBLDAT* pNewSystemEffect = new sSYSTEM_EFFECT_TBLDAT;
		if (NULL == pNewSystemEffect)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewSystemEffect;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewSystemEffect;
	}

	return NULL;
}

bool SystemEffectTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSYSTEM_EFFECT_TBLDAT* pSystemEffect = (sSYSTEM_EFFECT_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pSystemEffect, sizeof(*pSystemEffect)))
			return false;

		delete pSystemEffect;

		return true;
	}

	return false;
}

bool SystemEffectTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sSYSTEM_EFFECT_TBLDAT* pTbldat = (sSYSTEM_EFFECT_TBLDAT*)pvTable;

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}


	return true;
}

bool SystemEffectTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSYSTEM_EFFECT_TBLDAT* pSystemEffect = (sSYSTEM_EFFECT_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pSystemEffect->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Name"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);

			READ_STRINGW(bstrData, pSystemEffect->wszName, _countof(pSystemEffect->wszName));
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Effect_Type"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pSystemEffect->byEffect_Type = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Active_Effect_Type"))
		{
			pSystemEffect->byActive_Effect_Type = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Effect_Info_Text"))
		{
			pSystemEffect->Effect_Info_Text = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Keep_Effect_Name"))
		{
			pSystemEffect->Keep_Effect_Name = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Target_Effect_Position"))
		{
			pSystemEffect->byTarget_Effect_Position = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Success_Effect_Name"))
		{
			READ_STRING(bstrData, pSystemEffect->szSuccess_Effect_Name, _countof(pSystemEffect->szSuccess_Effect_Name));
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Success_Projectile_Type"))
		{
			pSystemEffect->bySuccess_Projectile_Type = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Success_Effect_Position"))
		{
			pSystemEffect->bySuccess_Effect_Position = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Success_End_Effect_Name"))
		{
			READ_STRING(bstrData, pSystemEffect->szSuccess_End_Effect_Name, _countof(pSystemEffect->szSuccess_End_Effect_Name));
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"End_Effect_Position"))
		{
			pSystemEffect->byEnd_Effect_Position = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Keep_Animation_Index"))
		{
			pSystemEffect->wKeep_Animation_Index = READ_WORD(bstrData, pstrDataName->c_str());
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


sTBLDAT* SystemEffectTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

sSYSTEM_EFFECT_TBLDAT * SystemEffectTable::FindDataWithEffectCode(DWORD dwEffectCode)
{
	TBLIDX tblidx = GetEffectTblidx(dwEffectCode);
	if (INVALID_TBLIDX != tblidx)
	{
		return (sSYSTEM_EFFECT_TBLDAT *)FindData(tblidx);
	}

	return NULL;
}

TBLIDX SystemEffectTable::GetEffectTblidx(DWORD dwEffectCode)
{
	if (dwEffectCode >= MAX_SYSTEM_EFFECT_CODE)
	{
		return INVALID_TBLIDX;
	}

	return m_aEffectCodeMatchTable[dwEffectCode];
}

bool SystemEffectTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sSYSTEM_EFFECT_TBLDAT* pTableData = new sSYSTEM_EFFECT_TBLDAT;
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

bool SystemEffectTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sSYSTEM_EFFECT_TBLDAT* pTableData = (sSYSTEM_EFFECT_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}