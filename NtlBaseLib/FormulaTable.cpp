#include "StdAfx.h"
#include "FormulaTable.h"

float FormulaTable::m_afRate[DBO_MAX_FORMULA_IDX + 1][DBO_MAX_FORMULA_RATE_COUNT + 1];

WCHAR* FormulaTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

FormulaTable::FormulaTable(void)
{
	Init();
}

FormulaTable::~FormulaTable(void)
{
	Destroy();
}

bool FormulaTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void FormulaTable::Destroy()
{
	::ZeroMemory(m_afRate, sizeof(m_afRate));

	Table::Destroy();
}

void FormulaTable::Init()
{
	::ZeroMemory(m_afRate, sizeof(m_afRate));
}

void* FormulaTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sFORMULA_TBLDAT* pNewFormula = new sFORMULA_TBLDAT;
		if (NULL == pNewFormula)
		{
			return NULL;
		}

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewFormula;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewFormula;
	}

	return NULL;
}

bool FormulaTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sFORMULA_TBLDAT* pFormula = (sFORMULA_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pFormula, sizeof(*pFormula)))
		{
			return false;
		}

		delete pFormula;

		return true;
	}

	return false;
}

bool FormulaTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sFORMULA_TBLDAT* pTbldat = (sFORMULA_TBLDAT*)pvTable;

	if (false == pTbldat->bValidity_Able)
	{
		return false;
	}

	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated.", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}

	if (DBO_MAX_FORMULA_IDX < pTbldat->tblidx)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is too big. The maximum is %u.", m_wszXmlFileName, pTbldat->tblidx, DBO_MAX_FORMULA_IDX);
		_ASSERTE(0);
		return false;
	}

	::CopyMemory(&(m_afRate[pTbldat->tblidx][1]), pTbldat->afRate, sizeof(m_afRate[pTbldat->tblidx]));

	return true;
}

bool FormulaTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sFORMULA_TBLDAT* pFormula = (sFORMULA_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Idx"))
		{
			pFormula->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcsncmp(pstrDataName->c_str(), L"Rate", wcslen(L"Rate")))
		{
			bool bFound = false;

			WCHAR szBuffer[1024] = { 0x00, };
			for (int i = 0; i < DBO_MAX_FORMULA_RATE_COUNT; i++)
			{
				swprintf(szBuffer, 1024, L"Rate%d", i + 1);

				if (0 == wcscmp(pstrDataName->c_str(), szBuffer))
				{
					pFormula->afRate[i] = READ_FLOAT(bstrData, pstrDataName->c_str());

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
		_ASSERT(0);
		return false;
	}

	return true;
}


sTBLDAT* FormulaTable::FindData(TBLIDX tblidx)
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

bool FormulaTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sFORMULA_TBLDAT* pTableData = new sFORMULA_TBLDAT;
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

bool FormulaTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sFORMULA_TBLDAT* pTableData = (sFORMULA_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}