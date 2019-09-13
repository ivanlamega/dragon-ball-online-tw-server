#include "StdAfx.h"
#include "NtlCharacter.h"
#include "NtlSkill.h"
#include "SkillTable.h"
#include "Serializer.h"

WCHAR* SkillTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

SkillTable::SkillTable(void)
{
	Init();
}

SkillTable::~SkillTable(void)
{
	Destroy();
}

bool SkillTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void SkillTable::Destroy()
{
	m_mapPreTableList.clear();

	Table::Destroy();
}

void SkillTable::Init()
{
	m_mapPreTableList.clear();
}

void* SkillTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSKILL_TBLDAT* pNewSkill = new sSKILL_TBLDAT;
		if (NULL == pNewSkill)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewSkill;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewSkill;
	}

	return NULL;
}

bool SkillTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSKILL_TBLDAT* pSkill = (sSKILL_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pSkill, sizeof(*pSkill)))
			return false;

		delete pSkill;

		return true;
	}

	return false;
}

bool SkillTable::AddTable(void * pvTable, bool bReload)
{
	sSKILL_TBLDAT * pTbldat = (sSKILL_TBLDAT*)pvTable;
	sSKILL_TBLDAT * pExistTbldat = NULL;

	if (false == pTbldat->bValidity_Able)
	{
		return false;
	}

	if (bReload)
	{
		pExistTbldat = (sSKILL_TBLDAT*)FindData(pTbldat->tblidx);
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


	if (INVALID_TBLIDX != pTbldat->dwNextSkillTblidx)
	{
		if (false == m_mapPreTableList.insert(std::map<TBLIDX, TBLIDX>::value_type(pTbldat->dwNextSkillTblidx, pTbldat->tblidx)).second)
		{
			Table::CallErrorCallbackFunction(L"Tblidx[%u]::dwNextSkillTblidx[%u] is Duplicated ", pTbldat->tblidx, pTbldat->dwNextSkillTblidx);
			_ASSERTE(0);
			return false;
		}
	}

	return true;
}

bool SkillTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sSKILL_TBLDAT* pSkill = (sSKILL_TBLDAT*)pvTable;
		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pSkill->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Skill_Name"))
		{
			pSkill->Skill_Name = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Name_Text"))
		{
			READ_STRINGW(bstrData, pSkill->wszNameText, _countof(pSkill->wszNameText));
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Validity_Able"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pSkill->bValidity_Able = READ_BOOL(bstrData, pstrDataName->c_str());
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


sTBLDAT* SkillTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool SkillTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sSKILL_TBLDAT* pTableData = new sSKILL_TBLDAT;
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

bool SkillTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sSKILL_TBLDAT* pTableData = (sSKILL_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}

TBLIDX SkillTable::FindPreSkillTblidx(TBLIDX tblidx)
{
	if (0 == tblidx || INVALID_TBLIDX == tblidx)
		return INVALID_TBLIDX;

	PRE_TABLE_IT iter;
	iter = m_mapPreTableList.find(tblidx);
	if (m_mapPreTableList.end() == iter)
		return INVALID_TBLIDX;

	return iter->second;
}

TBLIDX SkillTable::FindBasicSkillTblidx(TBLIDX tblidx)
{
	if (0 == tblidx || INVALID_TBLIDX == tblidx)
		return INVALID_TBLIDX;

	TBLIDX basicTblidx = tblidx;
	while (INVALID_TBLIDX != basicTblidx)
	{
		PRE_TABLE_IT iter;
		iter = m_mapPreTableList.find(basicTblidx);
		if (m_mapPreTableList.end() == iter)
		{
			return basicTblidx;
		}
		else
		{
			if (INVALID_TBLIDX != iter->second)
			{
				basicTblidx = iter->second;
			}
			else
			{
				return basicTblidx;
			}
		}
	}
	return INVALID_TBLIDX;
}