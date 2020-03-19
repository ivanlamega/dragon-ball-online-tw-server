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
	LoadClassInfo();
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

void FormulaTable::AddClassInfo(BYTE byClass)
{
	TBLIDX PO = 101;
	TBLIDX LP = 201;
	TBLIDX EO = 1101;
	TBLIDX EP = 1301;
	TBLIDX CPCR = 1901;
	TBLIDX PCR = 2001;
	TBLIDX CECR = 2101;
	TBLIDX ECR = 2201;
	TBLIDX MAP = 2301;

	CLASS_INFO classInfo;
	classInfo.byClass = byClass;
	classInfo.Physical_Offence = PO + byClass;
	classInfo.LP = LP + byClass;
	classInfo.Energy_Offence = EO + byClass;
	classInfo.EP = EP + byClass;
	classInfo.Physical_Critical_Rate = CPCR + byClass;
	classInfo.Physical_Critical_Range = PCR + byClass;
	classInfo.Energy_Critical_Rate = CECR + byClass;
	classInfo.Energy_Critical_Range = ECR + byClass;
	classInfo.Max_AP = MAP + byClass;

	m_mapClassInfoList.insert(std::pair<BYTE, CLASS_INFO>(byClass, classInfo));
}

CLASS_INFO*	FormulaTable::FindClassInfoByClass(BYTE byClass)
{
	if (PC_CLASS_UNKNOWN == byClass)
	{
		return NULL;
	}

	CLASS_INFODATAIT iter;
	iter = m_mapClassInfoList.find(byClass);
	if (ClassInfoEnd() == iter)
	{
		return NULL;
	}

	return &iter->second;
}

bool FormulaTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sFORMULA_TBLDAT* pTbldat = (sFORMULA_TBLDAT*)pvTable;
		
	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated.", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}
	return true;
}

bool FormulaTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sFORMULA_TBLDAT* pFormula = (sFORMULA_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pFormula->tblidx = READ_DWORD(bstrData);
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

void FormulaTable::LoadClassInfo()
{
	AddClassInfo(PC_CLASS_HUMAN_FIGHTER);
	AddClassInfo(PC_CLASS_HUMAN_MYSTIC);
	AddClassInfo(PC_CLASS_HUMAN_ENGINEER);
	AddClassInfo(PC_CLASS_NAMEK_FIGHTER);
	AddClassInfo(PC_CLASS_NAMEK_MYSTIC);
	AddClassInfo(PC_CLASS_MIGHTY_MAJIN);
	AddClassInfo(PC_CLASS_WONDER_MAJIN);
	AddClassInfo(PC_CLASS_STREET_FIGHTER);
	AddClassInfo(PC_CLASS_SWORD_MASTER);
	AddClassInfo(PC_CLASS_CRANE_ROSHI);
	AddClassInfo(PC_CLASS_TURTLE_ROSHI);
	AddClassInfo(PC_CLASS_GUN_MANIA);
	AddClassInfo(PC_CLASS_MECH_MANIA);
	AddClassInfo(PC_CLASS_DARK_WARRIOR);
	AddClassInfo(PC_CLASS_SHADOW_KNIGHT);
	AddClassInfo(PC_CLASS_DENDEN_HEALER);
	AddClassInfo(PC_CLASS_POCO_SUMMONER);
	AddClassInfo(PC_CLASS_ULTI_MA);
	AddClassInfo(PC_CLASS_GRAND_MA);
	AddClassInfo(PC_CLASS_PLAS_MA);
	AddClassInfo(PC_CLASS_KAR_MA);
}