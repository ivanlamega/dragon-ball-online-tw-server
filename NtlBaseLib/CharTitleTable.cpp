#include "stdafx.h"
#include "CharTitleTable.h"
#include "Serializer.h"


WCHAR* CharTitleTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

CharTitleTable::CharTitleTable(void)
{
	Init();
}

CharTitleTable::~CharTitleTable(void)
{
	Destroy();
}

bool CharTitleTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void CharTitleTable::Destroy()
{
	Table::Destroy();
}

void CharTitleTable::Init()
{
}

void* CharTitleTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHAR_TITLE_TBLDAT* pNewItem = new sCHAR_TITLE_TBLDAT;
		if (NULL == pNewItem)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewItem;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewItem;
	}

	return NULL;
}

bool CharTitleTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHAR_TITLE_TBLDAT* pItem = (sCHAR_TITLE_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pItem, sizeof(*pItem)))
			return false;

		delete pItem;

		return true;
	}

	return false;
}

bool CharTitleTable::AddTable(void * pvTable, bool bReload)
{
	sCHAR_TITLE_TBLDAT * pTbldat = (sCHAR_TITLE_TBLDAT*)pvTable;
	sCHAR_TITLE_TBLDAT * pExistTbldat = NULL;

	if (bReload)
	{
		pExistTbldat = (sCHAR_TITLE_TBLDAT*)FindData(pTbldat->tblidx);
		if (pExistTbldat)
		{
			CopyMemory(pTbldat, pExistTbldat, pTbldat->GetDataSize());
			// 데이타의 리로드 성공을 위한 true 반환
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

bool CharTitleTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{

	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHAR_TITLE_TBLDAT* pTitle = (sCHAR_TITLE_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pTitle->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Title_tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pTitle->tTitleTblidx= READ_WORD(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"ClassBitflags"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pTitle->classBitFlags = (WORD)READ_BITFLAG(bstrData);
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


sTBLDAT* CharTitleTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool CharTitleTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sCHAR_TITLE_TBLDAT* pTableData = new sCHAR_TITLE_TBLDAT;
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

bool CharTitleTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sCHAR_TITLE_TBLDAT* pTableData = (sCHAR_TITLE_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}
