#include "precomp_trigger.h"
#include "CDboTSEMSideIcon.h"
#include "DboTSCoreDefine.h"
#include "NtlTSMemIO.h"


struct sSIDEICON_PARAM
{
	sSIDEICON_PARAM(void) : bFind(false), unknown1(0xffffffff) { return; }

	bool						bFind;
	unsigned int				unknown1;
};

class CDboTSEMSideIcon_Recv : public CNtlTSRecv
{
public:
	NTL_TSRESULT				Search(CNtlTSEntity* pEntity, void* pParam);
	NTL_TSRESULT				Run(CNtlTSEntity*, void*) { return 0; }
};

NTL_TSRESULT CDboTSEMSideIcon_Recv::Search(CNtlTSEntity* pEntity, void* pParam)
{
	if (pEntity->GetEntityType() == DBO_EVENT_TYPE_ID_BIND_STONE)
	{
		((sSIDEICON_PARAM*)pParam)->bFind = true;
	}

	return 0;
}


/**
	Event mapper bind stone
*/


NTL_TS_IMPLEMENT_RTTI(CDboTSEMSideIcon, CNtlTSEvtMapper)


CDboTSEMSideIcon::CDboTSEMSideIcon(void)
{
}

CDboTSEMSideIcon::~CDboTSEMSideIcon(void)
{
}

const CNtlTSEvtMapper::vecdef_TID_LIST* CDboTSEMSideIcon::FindTSList(unsigned int uiId, const std::string& strKey) const
{
	UNREFERENCED_PARAMETER(uiId);

	mapdef_SIDEICON_MAPPER::const_iterator it = m_defSideIconMapper.find(strKey);
	if (it == m_defSideIconMapper.end()) return NULL;

	return &(it->second);
}

void CDboTSEMSideIcon::Clear(void)
{
	m_defSideIconMapper.clear();
}

bool CDboTSEMSideIcon::Load(const std::string& strFileName)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, strFileName.c_str(), "rb");

	if (NULL == pFile)
	{
		return false;
	}

	m_defSideIconMapper.clear();

	//////////////////////////////////////////////////////////////////////////
	//
	//	Mapper counter
	//
	//////////////////////////////////////////////////////////////////////////
	int nMapperCnt;
	fread(&nMapperCnt, sizeof(nMapperCnt), 1, pFile);

	for (int nCurMapperCnt = 0; nCurMapperCnt < nMapperCnt; ++nCurMapperCnt)
	{
		//////////////////////////////////////////////////////////////////////////
		//
		//	String
		//
		//////////////////////////////////////////////////////////////////////////
		int nStrLen;
		fread(&nStrLen, sizeof(nStrLen), 1, pFile);

		char* pStr = new char[nStrLen + 1];
		fread(pStr, nStrLen, 1, pFile);
		pStr[nStrLen] = '\0';

		vecdef_TID_LIST* pTrigList = &m_defSideIconMapper.insert(mapdef_SIDEICON_MAPPER::value_type(pStr, vecdef_TID_LIST())).first->second;

		delete[] pStr;
		pStr = NULL;

		//////////////////////////////////////////////////////////////////////////
		//	Trigger counter
		//////////////////////////////////////////////////////////////////////////
		int nTrigCnt;
		fread(&nTrigCnt, sizeof(nTrigCnt), 1, pFile);

		for (int nCurTrigCnt = 0; nCurTrigCnt < nTrigCnt; ++nCurTrigCnt)
		{
			//////////////////////////////////////////////////////////////////////////
			//	Trigger
			//////////////////////////////////////////////////////////////////////////
			NTL_TS_T_ID tID;
			fread(&tID, sizeof(tID), 1, pFile);

			pTrigList->push_back(tID);
		}
	}

	fclose(pFile);

	return true;
}

bool CDboTSEMSideIcon::Load(const char* pData, int nDataSize)
{
	CNtlTSMemInput clMemInput(pData, nDataSize);

	m_defSideIconMapper.clear();

	//////////////////////////////////////////////////////////////////////////
	//
	//	Mapper counter
	//
	//////////////////////////////////////////////////////////////////////////
	int nMapperCnt;
	if (!clMemInput.Read(&nMapperCnt, sizeof(nMapperCnt)))
	{
		m_defSideIconMapper.clear();
		return false;
	}

	for (int nCurMapperCnt = 0; nCurMapperCnt < nMapperCnt; ++nCurMapperCnt)
	{
		//////////////////////////////////////////////////////////////////////////
		//
		//	String
		//
		//////////////////////////////////////////////////////////////////////////
		int nStrLen;
		if (!clMemInput.Read(&nStrLen, sizeof(nStrLen)))
		{
			m_defSideIconMapper.clear();
			return false;
		}

		char* pStr = new char[nStrLen + 1];

		if (!clMemInput.Read(pStr, nStrLen))
		{
			m_defSideIconMapper.clear();
			return false;
		}

		pStr[nStrLen] = '\0';

		vecdef_TID_LIST* pTrigList = &m_defSideIconMapper.insert(mapdef_SIDEICON_MAPPER::value_type(pStr, vecdef_TID_LIST())).first->second;

		delete[] pStr;
		pStr = NULL;

		//////////////////////////////////////////////////////////////////////////
		//	Trigger counter
		//////////////////////////////////////////////////////////////////////////
		int nTrigCnt;
		if (!clMemInput.Read(&nTrigCnt, sizeof(nTrigCnt)))
		{
			m_defSideIconMapper.clear();
			return false;
		}

		for (int nCurTrigCnt = 0; nCurTrigCnt < nTrigCnt; ++nCurTrigCnt)
		{
			//////////////////////////////////////////////////////////////////////////
			//	Trigger
			//////////////////////////////////////////////////////////////////////////
			NTL_TS_T_ID tID;
			if (!clMemInput.Read(&tID, sizeof(tID)))
			{
				m_defSideIconMapper.clear();
				return false;
			}

			pTrigList->push_back(tID);
		}
	}

	return true;
}

bool CDboTSEMSideIcon::Save(const std::string& strFileName)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, strFileName.c_str(), "wb");

	if (NULL == pFile)
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//	Mapper counter
	//
	//////////////////////////////////////////////////////////////////////////
	int nMapperCnt = (int)m_defSideIconMapper.size();
	fwrite(&nMapperCnt, sizeof(nMapperCnt), 1, pFile);

	mapdef_SIDEICON_MAPPER::iterator itMapper = m_defSideIconMapper.begin();
	for (; itMapper != m_defSideIconMapper.end(); ++itMapper)
	{
		//////////////////////////////////////////////////////////////////////////
		//
		//	String
		//
		//////////////////////////////////////////////////////////////////////////
		int nStrLen = (int)itMapper->first.size();
		const char* pStr = itMapper->first.c_str();
		fwrite(&nStrLen, sizeof(nStrLen), 1, pFile);
		fwrite(pStr, nStrLen, 1, pFile);

		//////////////////////////////////////////////////////////////////////////
		//
		//	Trigger list size
		//
		//////////////////////////////////////////////////////////////////////////
		int nTrigListSize = (int)itMapper->second.size();
		fwrite(&nTrigListSize, sizeof(nTrigListSize), 1, pFile);

		vecdef_TID_LIST::iterator itTList = itMapper->second.begin();
		for (; itTList != itMapper->second.end(); ++itTList)
		{
			//////////////////////////////////////////////////////////////////////////
			//	Trigger
			//////////////////////////////////////////////////////////////////////////
			NTL_TS_T_ID tID = *itTList;
			fwrite(&tID, sizeof(tID), 1, pFile);
		}
	}

	fclose(pFile);

	return true;
}

bool CDboTSEMSideIcon::AddBuildData(const std::string& strKey, const CNtlTSMain::mapdef_TLIST& TList, void* pTblList, void* pParameter)
{
	UNREFERENCED_PARAMETER(pTblList);
	UNREFERENCED_PARAMETER(pParameter);

	if (m_defSideIconMapper.find(strKey) == m_defSideIconMapper.end())
	{
		m_defSideIconMapper[strKey] = vecdef_TID_LIST();
	}

	vecdef_TID_LIST& defTIDList = m_defSideIconMapper[strKey];

	// Trigger system script들을 순회하면서 해당 collision region으로 시작할 수 있는
	// trigger를 찾는다

	sSIDEICON_PARAM sParam;
	CDboTSEMSideIcon_Recv clRecv;

	CNtlTSTrigger* pTrig;
	CNtlTSMain::mapdef_TLIST::const_iterator citTSBegin = TList.begin();
	CNtlTSMain::mapdef_TLIST::const_iterator citTSEnd = TList.end();

	for (; citTSBegin != citTSEnd; ++citTSBegin)
	{
		pTrig = citTSBegin->second;

		sParam.bFind = false;

		pTrig->SearchTarget(NTL_TS_MAIN_GROUP_ID, START_CONTAINER_ID, &clRecv, &sParam);

		if (sParam.bFind)
		{
			defTIDList.push_back(citTSBegin->first);
		}
	}

	return true;
}

bool CDboTSEMSideIcon::DelBuildData(const std::string& strKey)
{
	mapdef_SIDEICON_MAPPER::iterator it = m_defSideIconMapper.find(strKey);
	if (it != m_defSideIconMapper.end())
	{
		m_defSideIconMapper.erase(it);
	}

	return true;
}

