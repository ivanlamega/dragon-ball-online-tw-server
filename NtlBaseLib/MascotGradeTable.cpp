#include "stdafx.h"
#include "MascotGradeTable.h"
#include "Serializer.h"

WCHAR* MascotGradeTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

MascotGradeTable::MascotGradeTable(void)
{
	Init();
}

MascotGradeTable::~MascotGradeTable(void)
{
	Destroy();
}

bool MascotGradeTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void MascotGradeTable::Destroy()
{
	Table::Destroy();
}

void MascotGradeTable::Init()
{
}

void* MascotGradeTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMASCOT_GRADE_TBLDAT* pMascotGrade = new sMASCOT_GRADE_TBLDAT;
		if (NULL == pMascotGrade)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pMascotGrade;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pMascotGrade;
	}

	return NULL;
}

bool MascotGradeTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMASCOT_GRADE_TBLDAT* pMascotGrade = (sMASCOT_GRADE_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pMascotGrade, sizeof(*pMascotGrade)))
			return false;

		delete pMascotGrade;

		return true;
	}

	return false;
}

bool MascotGradeTable::AddTable(void * pvTable, bool bReload)
{
	sMASCOT_GRADE_TBLDAT * pTbldat = (sMASCOT_GRADE_TBLDAT*)pvTable;
	sMASCOT_GRADE_TBLDAT * pExistTbldat = NULL;

	if (bReload)
	{
		pExistTbldat = (sMASCOT_GRADE_TBLDAT*)FindData(pTbldat->tblidx);
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

bool MascotGradeTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMASCOT_GRADE_TBLDAT* pMascotGrade = (sMASCOT_GRADE_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			pMascotGrade->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_DWORD"))
		{
			pMascotGrade->unknown1 = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_WORD"))
		{
			pMascotGrade->unknown2 = READ_WORD(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_WORD_Two"))
		{
			pMascotGrade->unknown3 = READ_WORD(bstrData, pstrDataName->c_str(), 0);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Unknown_Word_Three"))
		{
			pMascotGrade->unknown4 = READ_WORD(bstrData, pstrDataName->c_str(), 0);
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