#include "stdafx.h"
#include "MobTable.h"
#include "Serializer.h"

WCHAR* MobTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

MobTable::MobTable(void)
{
	Init();
}

MobTable::~MobTable(void)
{
	Destroy();
}

bool MobTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void MobTable::Destroy()
{
	m_mapMobTableList.clear();

	Table::Destroy();
}

void MobTable::Init()
{
	m_mapMobTableList.clear();
}

void* MobTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMOB_TBLDAT* pNewMob = new sMOB_TBLDAT;
		if (NULL == pNewMob)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewMob;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewMob;
	}

	return NULL;
}

bool MobTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMOB_TBLDAT* pMob = (sMOB_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pMob, sizeof(*pMob)))
			return false;

		delete pMob;

		return true;
	}

	return false;
}

bool MobTable::AddTable(void * pvTable, bool bReload)
{
	sMOB_TBLDAT * pTbldat = (sMOB_TBLDAT*)pvTable;
	sMOB_TBLDAT * pExistTbldat = NULL;

	if (false == pTbldat->bValidity_Able)
	{
		return false;
	}

	//  [9/27/2006 zeroera] : 임시 : 일단 X, Z의 평균값을 계산하여 결정한다. ( 원형 or 박스 확실히 결정하자 )
	//	pTbldat->fRadius = (float) ( ( pTbldat->fRadius_X + pTbldat->fRadius_Z  ) * 0.5 );


	if (bReload)
	{
		pExistTbldat = (sMOB_TBLDAT*)FindData(pTbldat->tblidx);
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

	MOB_TABLEIT iter = m_mapMobTableList.find(pTbldat->Mob_Group);
	if (MobEnd() == iter)
	{
		if (false == m_mapMobTableList.insert(MOB_TABLEVAL(pTbldat->Mob_Group, pTbldat->tblidx)).second)
		{
			_ASSERTE(0);
			return false;
		}
	}

	MOB_TABLESIT iter2;
	iter2 = m_mapMobTablesList.find(pTbldat->Mob_Group);
	if (MobsEnd() == iter2)
	{
		m_mapMobTablesList[pTbldat->Mob_Group] = std::vector<TBLIDX>();
		m_mapMobTablesList[pTbldat->Mob_Group].push_back(pTbldat->tblidx);
	}
	else
	{
		m_mapMobTablesList[pTbldat->Mob_Group].push_back(pTbldat->tblidx);
	}

	MOB_QITEMIT iterMobQItem;
	iterMobQItem = m_mapMobQItemList.find(pTbldat->dropQuestTblidx);
	if (MobsQItemEnd() == iterMobQItem)
	{
		m_mapMobQItemList[pTbldat->dropQuestTblidx] = std::vector<TBLIDX>();
		m_mapMobQItemList[pTbldat->dropQuestTblidx].push_back(pTbldat->tblidx);
	}
	else
	{
		m_mapMobQItemList[pTbldat->dropQuestTblidx].push_back(pTbldat->tblidx);
	}

	return true;
}

bool MobTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sMOB_TBLDAT* pMob = (sMOB_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pMob->tblidx = READ_DWORD(bstrData);
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


sTBLDAT* MobTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

TBLIDX MobTable::FindTblidxByGroup(DWORD dwMobGroup)
{
	if (INVALID_TBLIDX == dwMobGroup)
		return INVALID_TBLIDX;

	MOB_TABLEIT iter;
	iter = m_mapMobTableList.find(dwMobGroup);
	if (MobEnd() == iter)
		return NULL;

	return (TBLIDX)(iter->second);
}

std::vector<TBLIDX>	MobTable::FindTblidxsByGroup(DWORD dwMobGroup)
{
	if (INVALID_TBLIDX == dwMobGroup)
	{
		return {};
	}

	MOB_TABLESIT iter;
	iter = m_mapMobTablesList.find(dwMobGroup);
	if (MobsEnd() == iter)
	{
		return {};
	}

	return (std::vector<TBLIDX>)iter->second;
}

std::vector<TBLIDX>	MobTable::FindTblidxsByQuestDrop(TBLIDX questDropTblidx)
{
	if (INVALID_TBLIDX == questDropTblidx)
	{
		return {};
	}

	MOB_QITEMIT iter;
	iter = m_mapMobQItemList.find(questDropTblidx);
	if (MobsQItemEnd() == iter)
	{
		return {};
	}
	return iter->second;
}

bool MobTable::LoadFromBinary(Serializer& serializer, bool bReload)
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
		sMOB_TBLDAT* pTableData = new sMOB_TBLDAT;
		if (NULL == pTableData)
		{
			//- yoshiki : To log system!
			Destroy();
			return false;
		}

		// 새로 추가된 테이블에 의해 기존 테이블을 못읽는 일이 없도록 하기위해
		// 여기서 return false를 안한다
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

bool MobTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sMOB_TBLDAT* pTableData = (sMOB_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}
