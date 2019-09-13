#include "stdafx.h"
#include "DynamicObjectTable.h"
#include "Serializer.h"

WCHAR* DynamicObjectTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

DynamicObjectTable::DynamicObjectTable(void)
{
	Init();
}

DynamicObjectTable::~DynamicObjectTable(void)
{
	Destroy();
}

bool DynamicObjectTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void DynamicObjectTable::Destroy(void)
{
	Table::Destroy();
}

void DynamicObjectTable::Init(void)
{
	m_dwObjectSequence = 0;
}

void* DynamicObjectTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sDYNAMIC_OBJECT_TBLDAT* pNewObj = new sDYNAMIC_OBJECT_TBLDAT;
		if (NULL == pNewObj) return NULL;

		CPINFO cpInfo;
		if (!GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewObj;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewObj;
	}

	return NULL;
}

bool DynamicObjectTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sDYNAMIC_OBJECT_TBLDAT* pObj = (sDYNAMIC_OBJECT_TBLDAT*)pvTable;
		if (IsBadReadPtr(pObj, sizeof(*pObj))) return false;

		delete pObj;

		return true;
	}

	return false;
}

bool DynamicObjectTable::AddTable(void * pvTable, bool bReload)
{
	sDYNAMIC_OBJECT_TBLDAT * pTbldat = (sDYNAMIC_OBJECT_TBLDAT*)pvTable;
	sDYNAMIC_OBJECT_TBLDAT * pExistTbldat = NULL;


	if (bReload)
	{
		pExistTbldat = (sDYNAMIC_OBJECT_TBLDAT*)FindData(pTbldat->tblidx);
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

	return true;
}

bool DynamicObjectTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
#define READ_STATE( idx )															\
	if ( READ_STRING( bstrData, szTemp, 1024 ) )									\
	{																				\
		int nCnt = 0;																\
		char *pToken, *pNextToken;													\
																					\
		pToken = strtok_s( szTemp, ";", &pNextToken );								\
																					\
		while ( NULL != pToken )													\
		{																			\
			DWORD dwTemp = (DWORD)_atoi64( pToken );								\
																					\
			if ( dwTemp >= INVALID_BYTE )											\
			{																		\
				_ASSERTE( !"BYTE 타입의 데이타 값이 최대값 을 초과했습니다." );		\
			}																		\
			else																	\
			{																		\
				pObj->abyState[idx][nCnt] = (BYTE)dwTemp;							\
			}																		\
																					\
			nCnt++;																	\
																					\
			pToken = strtok_s( NULL, ";", &pNextToken );							\
		}																			\
	}

	static char szTemp[1024];

	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sDYNAMIC_OBJECT_TBLDAT* pObj = (sDYNAMIC_OBJECT_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			pObj->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Validity_Able"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pObj->bValidityAble = READ_BOOL(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Type"))
		{
			pObj->byType = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Model_Name"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);

			READ_STRING(bstrData, pObj->szModelName, _countof(pObj->szModelName));
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"State_Type"))
		{
			pObj->byStateType = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Spawn_Animation"))
		{
			pObj->spawnAnimation = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Idle_Animation"))
		{
			pObj->idleAnimation = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Despawn_Animation"))
		{
			pObj->despawnAnimation = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"State1_Animation"))
		{
			pObj->state1Animation = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"State2_Animation"))
		{
			pObj->state2Animation = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Boundary_Distance"))
		{
			pObj->byBoundaryDistance = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Despawn_Distance"))
		{
			pObj->byDespawnDistance = READ_BYTE(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Note"))
		{
			// 기획 전용 필드
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


sTBLDAT* DynamicObjectTable::FindData(TBLIDX tblidx)
{
	TABLEIT iter = m_mapTableList.find(tblidx);
	if (m_mapTableList.end() == iter) return NULL;

	return (sTBLDAT*)(iter->second);
}

bool DynamicObjectTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sDYNAMIC_OBJECT_TBLDAT* pTableData = new sDYNAMIC_OBJECT_TBLDAT;
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

bool DynamicObjectTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sDYNAMIC_OBJECT_TBLDAT* pTableData = (sDYNAMIC_OBJECT_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}