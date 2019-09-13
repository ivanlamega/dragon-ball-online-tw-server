#include "stdafx.h"
#include "NPCTable.h"
#include "Serializer.h"

WCHAR* NPCTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

NPCTable::NPCTable(void)
{
	Init();
}

NPCTable::~NPCTable(void)
{
	Destroy();
}

bool NPCTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void NPCTable::Destroy()
{
	Table::Destroy();
}

void NPCTable::Init()
{
}

void* NPCTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sNPC_TBLDAT* pNewNPC = new sNPC_TBLDAT;
		if (NULL == pNewNPC)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewNPC;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewNPC;
	}

	return NULL;
}

bool NPCTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sNPC_TBLDAT* pNPC = (sNPC_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pNPC, sizeof(*pNPC)))
			return false;

		delete pNPC;

		return true;
	}

	return false;
}

bool NPCTable::AddTable(void * pvTable, bool bReload)
{
	sNPC_TBLDAT * pTbldat = (sNPC_TBLDAT*)pvTable;
	sNPC_TBLDAT * pExistTbldat = NULL;

	if (false == pTbldat->bValidity_Able)
	{
		return false;
	}

	//  [9/27/2006 zeroera] : 임시 : 일단 X, Z의 평균값을 계산하여 결정한다. ( 원형 or 박스 확실히 결정하자 )
	//pTbldat->fRadius = (float) ( ( pTbldat->fRadius_X + pTbldat->fRadius_Z  ) * 0.5 );

	if (bReload)
	{
		pExistTbldat = (sNPC_TBLDAT*)FindData(pTbldat->tblidx);
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


bool NPCTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{

	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sNPC_TBLDAT* pNPC = (sNPC_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pNPC->tblidx = READ_DWORD(bstrData);
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


sTBLDAT* NPCTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

TBLIDX NPCTable::FindMerchantItem(sNPC_TBLDAT* psTbldat, BYTE byIndex)
{
	if (MAX_MERCHANT_TAB_COUNT <= byIndex || 0 > byIndex)
		return INVALID_TBLIDX;

	return psTbldat->amerchant_Tblidx[byIndex];
}

bool NPCTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sNPC_TBLDAT* pTableData = new sNPC_TBLDAT;
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

bool NPCTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sNPC_TBLDAT* pTableData = (sNPC_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}