#include "StdAfx.h"
#include "MobMovePatternTable.h"
#include "Serializer.h"

WCHAR* MobMovePatternTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

MobMovePatternTable::MobMovePatternTable(void)
{
	Init();
}

MobMovePatternTable::~MobMovePatternTable(void)
{
	Destroy();
}

bool MobMovePatternTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void MobMovePatternTable::Destroy()
{
	Table::Destroy();
}

void MobMovePatternTable::Init()
{
}

void* MobMovePatternTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMOVE_PATTERN_TBLDAT* pPattern = new sMOVE_PATTERN_TBLDAT;
		if (NULL == pPattern)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pPattern;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pPattern;
	}

	return NULL;
}

bool MobMovePatternTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMOVE_PATTERN_TBLDAT* pPattern = (sMOVE_PATTERN_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pPattern, sizeof(*pPattern)))
			return false;

		delete pPattern;

		return true;
	}

	return false;
}

bool MobMovePatternTable::AddTable(void * pvTable, bool bReload)
{
	sMOVE_PATTERN_TBLDAT * pTbldat = (sMOVE_PATTERN_TBLDAT*)pvTable;
	sMOVE_PATTERN_TBLDAT * pExistTbldat = NULL;

	// Reload인경우 Data를 찾아 Update해준다
	if (bReload)
	{
		pExistTbldat = (sMOVE_PATTERN_TBLDAT*)FindData(pTbldat->tblidx);
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

bool MobMovePatternTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMOVE_PATTERN_TBLDAT* pPattern = (sMOVE_PATTERN_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			pPattern->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcsncmp(pstrDataName->c_str(), L"Pattern_", wcslen(L"Pattern_")))
		{
			bool bFound = false;

			WCHAR szBuffer[1024] = { 0x00, };
			for (int i = 0; i < DBO_MAX_COUNT_MOVE_PATTERN; i++)
			{
				swprintf(szBuffer, 1024, L"Pattern_%d", i + 1);

				if (0 == wcscmp(pstrDataName->c_str(), szBuffer))
				{
					pPattern->abyPattern[i] = READ_BYTE(bstrData, pstrDataName->c_str());

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
		else if (0 == wcscmp(pstrDataName->c_str(), L"Note"))
		{
			//			READ_STR( pPattern->wstrNote, bstrData);	// 메모리에 로드하지 않는다.
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


sTBLDAT* MobMovePatternTable::FindData(TBLIDX tblidx)
{
	if (INVALID_TBLIDX == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool MobMovePatternTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sMOVE_PATTERN_TBLDAT* pTableData = new sMOVE_PATTERN_TBLDAT;
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

bool MobMovePatternTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sMOVE_PATTERN_TBLDAT* pTableData = (sMOVE_PATTERN_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}