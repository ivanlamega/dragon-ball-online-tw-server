#include "stdafx.h"
#include "NtlUnzip.h"
#include "NtlCipher.h"
#include "GameQuestAgency.h"
#include "GameQuestRecv.h"
#include "GameTriggerAgency.h"
#include "GameTriggerRecv.h"
#include "GameObjectAgency.h"
#include "NtlDebug.h"
#include "TableContainer.h"
#include "WorldTable.h"
#include "NPCTable.h"
#include "SpawnTable.h"
#include "NtlUnzip.h"
#include "NtlCipher.h"
#include "QuestWrapper.h"
#include "GameServer.h"

#include <XmlParser2/XmlParser2.h>

//#include "NtlTSCoreStatic.h" //quitar

CQuestWrapper* CQuestWrapper::s_pInstance = NULL;
//char g_NtlTSString[1024]; //quitar

NTL_TS_IMPLEMENT_RTTI(CQuestWrapper, CDboTSMain)

CQuestWrapper::CQuestWrapper(void)
{
	m_bCreated = false;

	m_bSchedulingLoad = false;

	s_pInstance = this;

	m_pQAgency = 0;
	m_pTAgency = 0;
	m_pObjAgency = 0;

	m_bSchedulingLoad = false;

	m_pclQuestZip = NULL;
	m_pclTriggerZip = NULL;
	m_pclObjectZip = NULL;

	m_pQRecv = 0;
	m_pTRecv = 0;
}

CQuestWrapper::~CQuestWrapper(void)
{
	Delete();

	printf("CDboTSMain::~CDboTSMain not destroyd");
}

bool CQuestWrapper::Create(void)
{
	m_strQuestPath = sXmlParser.GetStr("GameTS.Quest", "Path");//"..\\Quest\\ts\\quest.e";
	m_strTriggerPath = sXmlParser.GetStr("GameTS.PcTrigger", "Path");// "..\\Quest\\ts\\pctrigger.e";
	m_strObjectPath = sXmlParser.GetStr("GameTS.ObjTrigger", "Path");// "..\\Quest\\ts\\objtrigger.e";

	MakeListTriggerIdQuestId();

	m_bSchedulingLoad = true;

	m_pclQuestZip = new CNtlUnzip;
	m_pclTriggerZip = new CNtlUnzip;
	m_pclObjectZip = new CNtlUnzip;

	bool bRet = CDboTSMain::Create();

	if (bRet)
	{
		m_bCreated = true;
	}

	return bRet;
}

void CQuestWrapper::Delete(void)
{
	ClearAllNPCPosition();

	DeleteAgency_Quest();
	DeleteAgency_Trigger();
	DeleteAgency_Object();

	CDboTSMain::Delete();

	SAFE_DELETE(m_pclQuestZip);
	SAFE_DELETE(m_pclTriggerZip);
	SAFE_DELETE(m_pclObjectZip);

	m_bCreated = false;
}

void CQuestWrapper::DeleteTrigger(CNtlTSTrigger* pNTLTrigger)
{
	m_pEntityFactory->DeleteObj((CNtlTSScrObject*&)pNTLTrigger);
}

bool CQuestWrapper::LoadLog(void)
{
	UnloadLog();

	m_pLog = new CNtlTSLog;
	CNtlTSLog::Register(m_pLog);

	return true;
}

void CQuestWrapper::UnloadLog(void)
{
	if (m_pLog)
	{
		CNtlTSLog::Unregister();
		delete m_pLog;
		m_pLog = 0;
	}
}

void CQuestWrapper::MakeListTriggerIdQuestId()
{
	/* Arguments:
	 @Questid @Triggerid */
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 1));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 10));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1026, 1026));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1030, 1030));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1036, 1036));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1036, 1037));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 11));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1104, 1104));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1108, 1108));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1108, 1109));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1132, 1132));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1149, 1149));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1159, 1159));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1161, 1161));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1163, 1163));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(117, 117));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1171, 1171));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 12));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1208, 1208));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1211, 1211));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(122, 122));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1225, 1225));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1238, 1238));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1242, 1242));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1266, 1266));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1281, 1281));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 13));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1334, 1334));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1340, 1340));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1341, 1341));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1360, 1360));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1374, 1374));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 14));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(142, 142));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1425, 1425));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1466, 1466));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 15));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1502, 1502));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1520, 1520));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1522, 1522));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1537, 1537));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1555, 1555));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1555, 1556));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1593, 1593));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1594, 1594));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 16));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1600, 1600));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1612, 1612));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(162, 162));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1626, 1626));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1627, 1627));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1632, 1632));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1675, 1675));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1679, 1679));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1682, 1682));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1688, 1688));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1691, 1691));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1695, 1695));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 17));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1707, 1707));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1731, 1731));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1734, 1734));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 18));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 19));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1934, 1934));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1935, 1935));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1940, 1940));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1941, 1941));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1942, 1942));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1943, 1943));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1944, 1944));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1945, 1945));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1951, 1951));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1954, 1954));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1957, 1957));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1961, 1961));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1963, 1963));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(1976, 1976));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 2));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2004, 2004));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2005, 2005));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2006, 2006));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2007, 2007));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2008, 2008));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2009, 2009));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2010, 2010));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2011, 2011));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2012, 2012));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2013, 2013));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2014, 2014));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2015, 2015));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2016, 2016));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2017, 2017));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2018, 2018));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2019, 2019));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2020, 2020));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2021, 2021));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2022, 2022));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2023, 2023));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2025, 2025));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2026, 2026));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2027, 2027));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2028, 2028));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2029, 2029));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2030, 2030));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2031, 2031));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2032, 2032));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2033, 2033));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2034, 2034));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2035, 2035));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2036, 2036));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2037, 2037));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2038, 2038));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2039, 2039));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2040, 2040));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2041, 2041));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2107, 2107));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2115, 2115));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 220));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 221));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 222));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 223));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 224));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 225));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 226));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 227));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 228));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 229));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 230));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 231));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 232));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 233));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 234));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 235));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2351, 2351));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2358, 2358));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 236));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2366, 2366));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2369, 2369));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 237));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 238));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2383, 2383));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2388, 2388));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 239));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2395, 2395));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2396, 2396));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 240));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2404, 2404));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 241));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2415, 2415));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 242));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2963, 243));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2444, 2444));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2464, 2464));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2522, 2522));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2530, 2530));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2547, 2547));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2575, 2575));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2581, 2581));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2604, 2604));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2608, 2608));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2624, 2624));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2630, 2630));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2637, 2637));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(264, 264));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2658, 2658));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2663, 2663));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2676, 2676));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(27, 27));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(270, 270));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2705, 2705));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2904, 2904));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2907, 2907));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(291, 291));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2919, 2919));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2928, 2928));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2939, 2939));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2943, 2943));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2949, 2949));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(295, 295));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(296, 296));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2966, 2966));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2975, 2975));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2977, 2977));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2990, 2990));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2993, 2993));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 3));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3007, 3007));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3026, 3026));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3031, 3031));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3034, 3034));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(324, 324));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(329, 329));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(330, 330));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(352, 352));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(370, 370));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3701, 3701));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3714, 3714));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3754, 3754));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3766, 3766));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3774, 3774));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3775, 3775));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(3776, 3776));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 4));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(405, 405));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(405, 406));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(405, 407));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(441, 441));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(473, 473));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(489, 489));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 5));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(501, 501));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(528, 528));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(56, 56));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 6));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6007, 6013));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6021, 6017));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6041, 6041));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6047, 6047));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(605, 605));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(607, 607));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6212, 6202));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6213, 6203));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6214, 6204));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6216, 6206));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6212, 6212));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6213, 6213));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6214, 6214));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6216, 6216));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6251, 6251));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6251, 6261));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(630, 630));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(639, 639));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6892, 6892));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(6893, 6893));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 7));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(712, 712));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(717, 717));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(718, 718));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(72, 72));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(727, 727));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(75, 75));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(759, 759));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(765, 765));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(767, 767));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(769, 769));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(793, 793));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 8));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(800, 800));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(816, 816));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(869, 869));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(2925, 9));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(910, 910));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(922, 922));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(940, 940));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(942, 942));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(957, 957));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(975, 975));
	m_pTriggQuestList.insert(std::pair<NTL_TS_T_ID, NTL_TS_T_ID>(981, 981));
}

NTL_TS_T_ID CQuestWrapper::FindTriggerByQuest(NTL_TS_T_ID questId)
{
	if (NTL_TS_T_ID_INVALID == questId)
	{
		return NTL_TS_T_ID_INVALID;
	}

	QUESTTRIGGIT iter;
	iter = m_pTriggQuestList.find(questId);
	if (QuestTriggerEnd() == iter)
	{
		return NTL_TS_T_ID_INVALID;
	}

	return (NTL_TS_T_ID)iter->second;
}


bool CQuestWrapper::LoadScripts(void)
{
	UnloadAllScripts();

	if ('e' == m_strQuestPath[m_strQuestPath.size() - 1])
	{
		if (m_bSchedulingLoad)
		{
			if (!LoadTSCryptoData_UnZip(m_strQuestPath, m_pclQuestZip))
			{
				return false;
			}
		}
		else
		{
			if (!LoadTSCryptoData(m_strQuestPath, m_defQuest))
			{
				return false;
			}
		}
	}
	else
	{
		if (!LoadTSZip(m_strQuestPath, m_defQuest))
		{
			char szPath[1024], szName[128];
			_splitpath_s(m_strQuestPath.c_str(), 0, 0, szPath, 1024, szName, 128, 0, 0);
			std::string strPath = szPath;
			strPath += szName;

			if (!LoadTSPath(strPath.c_str(), m_defQuest))
			{
				return false;
			}
		}
	}

	if ('e' == m_strTriggerPath[m_strTriggerPath.size() - 1])
	{
		if (m_bSchedulingLoad)
		{
			if (!LoadTSCryptoData_UnZip(m_strTriggerPath, m_pclTriggerZip))
			{
				return false;
			}
		}
		else
		{
			if (!LoadTSCryptoData(m_strTriggerPath, m_defTrigger))
			{
				return false;
			}
		}
	}
	else
	{
		if (!LoadTSZip(m_strTriggerPath, m_defTrigger))
		{
			char szPath[1024], szName[128];
			_splitpath_s(m_strTriggerPath.c_str(), 0, 0, szPath, 1024, szName, 128, 0, 0);
			std::string strPath = szPath;
			strPath += szName;

			if (!LoadTSPath(strPath.c_str(), m_defTrigger))
			{
				return false;
			}
		}
	}

	if ('e' == m_strObjectPath[m_strObjectPath.size() - 1])
	{
		if (m_bSchedulingLoad)
		{
			if (!LoadTSCryptoData_UnZip(m_strObjectPath, m_pclObjectZip))
			{
				return false;
			}
		}
		else
		{
			if (!LoadTSCryptoData(m_strObjectPath, m_defObject))
			{
				return false;
			}
		}
	}
	else
	{
		if (!LoadTSZip(m_strObjectPath, m_defObject))
		{
			char szPath[1024], szName[128];
			_splitpath_s(m_strObjectPath.c_str(), 0, 0, szPath, 1024, szName, 128, 0, 0);
			std::string strPath = szPath;
			strPath += szName;

			if (!LoadTSPath(strPath.c_str(), m_defObject))
			{
				return false;
			}
		}
	}

	return true;
}
bool CQuestWrapper::LoadFactories(void)
{
	UnloadFactories();

	// Entity factory ����
	m_pEntityFactory = new CDboTSEntityFactory;
	m_pEntityFactory->RegisterEntityType();

	// Control factory ����
	m_pCtrlFactory = new CDboTSCtrlFactory;
	m_pCtrlFactory->RegisterCtrlType();

	// UI factory ����
	m_pUIFactory = new CDboTSUIFactory;
	m_pUIFactory->RegisterUIType();

	return true;
}

void CQuestWrapper::UnloadFactories(void)
{
	if (m_pUIFactory)
	{
		delete m_pUIFactory;
		m_pUIFactory = 0;
	}
	if (m_pCtrlFactory)
	{
		delete m_pCtrlFactory;
		m_pCtrlFactory = 0;
	}
	if (m_pEntityFactory)
	{
		delete m_pEntityFactory;
		m_pEntityFactory = 0;
	}
}

void CQuestWrapper::UnloadAllScripts(void)
{
	mapdef_TLIST::iterator it;

	it = m_defQuest.begin();
	for (; it != m_defQuest.end(); ++it)
	{
		CNtlTSTrigger* pTrig = it->second;
		m_pEntityFactory->DeleteObj((CNtlTSScrObject*&)pTrig);
	}
	m_defQuest.clear();

	it = m_defTrigger.begin();
	for (; it != m_defTrigger.end(); ++it)
	{
		CNtlTSTrigger* pTrig = it->second;
		m_pEntityFactory->DeleteObj((CNtlTSScrObject*&)pTrig);
	}
	m_defTrigger.clear();

	it = m_defObject.begin();
	for (; it != m_defObject.end(); ++it)
	{
		CNtlTSTrigger* pTrig = it->second;
		m_pEntityFactory->DeleteObj((CNtlTSScrObject*&)pTrig);
	}
	m_defObject.clear();
}

bool CQuestWrapper::LoadEventMappers(void)
{
	if (!LoadEventMapperFromFile())
	{
		if (!LoadEventMapperFromRunTime())
		{
			return false;
		}
	}

	return true;
}

void CQuestWrapper::UnloadEventMappers(void)
{
	hashdef_EVT_MAPPER_LIST::iterator it = m_defEvtMapper.begin();
	for (; it != m_defEvtMapper.end(); ++it)
	{
		m_pCtrlFactory->DeleteObj((CNtlTSControlObject *&)it->second);
	}
	m_defEvtMapper.clear();
}

bool CQuestWrapper::LoadRecv(void)
{
	UnloadRecv();

	CNtlTSUIObject* pObj;

	pObj = m_pUIFactory->CreateObj("CDboTSQRecv");
	if (0 == pObj || !pObj->IsDerivedClass("CDboTSQRecv"))
	{
		CNtlTSLog::Log("Can not type cast from CNtlTSUIObject to CDboTSQRecv. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}
	m_pQRecv = (CGameQuestRecv*)pObj;

	pObj = m_pUIFactory->CreateObj("CDboTSTRecv");
	if (0 == pObj || !pObj->IsDerivedClass("CDboTSTRecv"))
	{
		CNtlTSLog::Log("Can not type cast from CNtlTSUIObject to CDboTSTRecv. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}
	m_pTRecv = (CGameTriggerRecv*)pObj;

	return true;
}

void CQuestWrapper::UnloadRecv(void)
{
	if (m_pTRecv)
	{
		m_pUIFactory->DeleteObj((CNtlTSUIObject*&)m_pTRecv);
	}

	if (m_pQRecv)
	{
		m_pUIFactory->DeleteObj((CNtlTSUIObject*&)m_pQRecv);
	}
}

void CQuestWrapper::LoadEventMapper(sUZ_FILEINFO* pFileInfo, char* pBuf)
{
	std::string strName = pFileInfo->szFileName;

	std::string::size_type pos = strName.find(".evt");
	if (std::string::npos != pos)
	{
		strName = strName.substr(0, pos);
	}

	std::string strTypeName = strName;

	pos = strName.find("_");
	if (std::string::npos != pos)
	{
		strTypeName = strName.substr(0, pos);
	}

	CNtlTSEvtMapper* pEvtMapper = (CNtlTSEvtMapper*)m_pCtrlFactory->CreateObj(strTypeName);

	if (pEvtMapper->Load(pBuf, pFileInfo->dwUncompressedSize))
	{
		m_defEvtMapper[strName.c_str()] = pEvtMapper;
	}
	else
	{
		m_pCtrlFactory->DeleteObj((CNtlTSControlObject*&)pEvtMapper);

		CNtlTSLog::Log("Loading event mapper failed. Info[%s]. [%s]", strName.c_str(), TS_CODE_TRACE());
	}
}

bool CQuestWrapper::HasEventMapperFromFile(void)
{
	std::string strEvtPath = ".\\ts\\evt.e";

	FILE* pFile;
	fopen_s(&pFile, strEvtPath.c_str(), "rb");
	if (NULL == pFile)
	{
		return false;
	}

	fclose(pFile);

	return true;
}

bool CQuestWrapper::LoadEventMapperFromFile(void)
{
	std::string strEvtPath = sXmlParser.GetStr("GameTS.EventMapper", "Path");//"..\\Quest\\evt\\";

	char* pReadBuf = NULL;
	char* pDecryptBuf = NULL;
	char* pBuf = NULL;

	// ���� �ε�
	FILE* pFile;
	fopen_s(&pFile, strEvtPath.c_str(), "rb");
	if (NULL == pFile)
	{
		return false;
	}

	fseek(pFile, 0, SEEK_END);
	int nReadSize = ftell(pFile) - 4;
	fseek(pFile, 0, SEEK_SET);
	pReadBuf = new char[nReadSize];
	int nOriginSize;
	fread(&nOriginSize, sizeof(int), 1, pFile);
	fread(pReadBuf, 1, nReadSize, pFile);
	fclose(pFile);

	// ��ȣȭ�� Ǭ��
	std::string strKey = "dnfldbofmftkfkdgowntpdy";//"tddkaghghkqlalfqjsghdlqslek"; //
	CNtlCipher Cipher;
	Cipher.SetKey(DES_CIPHER, strKey.c_str(), (int)strKey.size());
	pDecryptBuf = new char[nReadSize + 256];
	ZeroMemory(pDecryptBuf, nReadSize + 256);
	Cipher.Decrypt(pReadBuf, nReadSize, pDecryptBuf, nReadSize + 256);

	CNtlUnzip clZip;
	if (!clZip.OpenZip(strEvtPath.c_str(), pDecryptBuf, nOriginSize))
	{
		CNtlTSLog::Log("Zip file open failed. Info[%s]. [%s]", strEvtPath.c_str(), TS_CODE_TRACE());

		delete[] pReadBuf;
		delete[] pDecryptBuf;

		return false;
	}

	if (!clZip.GotoFirstFile())
	{
		CNtlTSLog::Log("Zip GotoFirstFile failed. Info[%s]. [%s]", strEvtPath.c_str(), TS_CODE_TRACE());

		delete[] pReadBuf;
		delete[] pDecryptBuf;

		return false;
	}

	unsigned int MAX_BUFFER_SIZE = 102400;
	pBuf = new char[MAX_BUFFER_SIZE];

	sUZ_FILEINFO sInfo;

	do
	{
		clZip.GetFileInfo(sInfo);

		if (sInfo.bFolder)
		{
			continue;
		}

		int nNameLength = (int)strlen(sInfo.szFileName);

		if (nNameLength <= 2)
		{
			continue;
		}

		if ('.' != sInfo.szFileName[nNameLength - 4] ||
			'e' != sInfo.szFileName[nNameLength - 3] ||
			'v' != sInfo.szFileName[nNameLength - 2] ||
			't' != sInfo.szFileName[nNameLength - 1])
		{
			continue;
		}

		if (MAX_BUFFER_SIZE < sInfo.dwUncompressedSize)
		{
			MAX_BUFFER_SIZE = sInfo.dwUncompressedSize + 1;

			delete[] pBuf;

			pBuf = new char[MAX_BUFFER_SIZE];
		}

		if (!clZip.ReadFileData(pBuf, sInfo.dwUncompressedSize))
		{
			CNtlTSLog::Log("Load TS compressed file. Info[%s]. [%s]", sInfo.szFileName, TS_CODE_TRACE());
		}
		else
		{
			LoadEventMapper(&sInfo, pBuf);
		}
	} while (clZip.GotoNextFile());

	delete[] pBuf;
	delete[] pReadBuf;
	delete[] pDecryptBuf;

	return true;
}

bool CQuestWrapper::LoadEventMapperFromRunTime(void)
{
	CNtlTSControlObject* pObj;

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMNPC");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMNPC"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMNPC*)pObj)->AddBuildData("quest", m_defQuest, sTBM.GetNpcTable(), NULL))//((CGameServer*)NtlSfxGetApp())->GetTableContainer()->GetNpcTable()
		{
			CNtlTSLog::Log("Building the npc in the npc event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMNPC*)pObj)->AddBuildData("pctrigger", m_defTrigger, sTBM.GetNpcTable(), NULL))
		{
			CNtlTSLog::Log("Building the npc in the npc event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMNPC. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}
	TableContainer::OBJTABLEIT it = sTBM.BeginObjectTable();//((CGameServer*)NtlSfxGetApp())->GetTableContainer()->BeginObjectTable();
	TableContainer::OBJTABLEIT itEnd =sTBM.EndObjectTable();//((CGameServer*)NtlSfxGetApp())->GetTableContainer()->EndObjectTable();

	for (; it != itEnd; ++it)
	{
		pObj = m_pCtrlFactory->CreateObj("CDboTSEMObject");
		if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMObject"))
		{
			unsigned int uiWorldTblIdx = it->first;

			sprintf_s(g_NtlTSString, "CDboTSEMObject_%d", uiWorldTblIdx);

			m_defEvtMapper[g_NtlTSString] = (CNtlTSEvtMapper*)pObj;

			if (!((CDboTSEMObject*)pObj)->AddBuildData("quest", m_defQuest, it->second, &uiWorldTblIdx))
			{
				CNtlTSLog::Log("Building the npc in the object event mapper is failed. [%s].", TS_CODE_TRACE());
				return false;
			}

			if (!((CDboTSEMObject*)pObj)->AddBuildData("pctrigger", m_defTrigger, it->second, &uiWorldTblIdx))
			{
				CNtlTSLog::Log("Building the npc in the object event mapper is failed. [%s].", TS_CODE_TRACE());
				return false;
			}
		}
		else
		{
			CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMObject. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
			return false;
		}
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMItem");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMItem"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMItem*)pObj)->AddBuildData("quest", m_defQuest, sTBM.GetItemTable(), NULL)) //((CGameServer*)NtlSfxGetApp())->GetTableContainer()->GetItemTable()
		{
			CNtlTSLog::Log("Building the item in the item event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMItem*)pObj)->AddBuildData("pctrigger", m_defTrigger, sTBM.GetItemTable(), NULL))
		{
			CNtlTSLog::Log("Building the item in the item event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMItem. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMSvrEvt");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMSvrEvt"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMSvrEvt*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building server event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMSvrEvt*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building server event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMSvrEvt. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMSkill");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMSkill"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMSkill*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building skill event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMSkill*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building skill event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMSkill. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMColRgn");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMColRgn"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMColRgn*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building collision region event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMColRgn*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building collision region mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMColRgn. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMRB");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMRB"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMRB*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building rank-battle event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMRB*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building rank-battle mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMRB. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMMob");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMMob"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMNPC*)pObj)->AddBuildData("quest", m_defQuest, sTBM.GetMobTable(), NULL)) //((CGameServer*)NtlSfxGetApp())->GetTableContainer()->GetMobTable()
		{
			CNtlTSLog::Log("Building the mob in the mob event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMNPC*)pObj)->AddBuildData("pctrigger", m_defTrigger, sTBM.GetMobTable(), NULL))
		{
			CNtlTSLog::Log("Building the mob in the mob event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMMob. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMBindStone");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMBindStone"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMBindStone*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building bind stone event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMBindStone*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building bind stone event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMBindStone. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMSideIcon");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMSideIcon"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMSideIcon*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building bind stone event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMSideIcon*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building bind stone event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMSideIcon. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMQuest");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMQuest"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMQuest*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building bind stone event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMQuest*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building bind stone event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMQuest. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMFLink");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMFLink"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMFLink*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building bind stone event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMFLink*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building bind stone event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMFLink. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMDialogOpen");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMDialogOpen"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMDialogOpen*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building bind stone event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMDialogOpen*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building bind stone event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMDialogOpen. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMSearchQuest");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMSearchQuest"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMSearchQuest*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building quest search event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMSearchQuest*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building quest search event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMSearchQuest. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMItemUpgrade");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMItemUpgrade"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMItemUpgrade*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building item upgrade event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMItemUpgrade*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building item upgrade event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMItemUpgrade. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMTeleport");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMTeleport"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMTeleport*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building teleport event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMTeleport*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building teleport event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMTeleport. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMBudokai");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMBudokai"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMBudokai*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building budokai mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMBudokai*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building budokai event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMBudokai. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMSlotMachine");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMSlotMachine"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMSlotMachine*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building SlotMachine event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMSlotMachine*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building SlotMachine event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMSlotMachine. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMHoipoiMix");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMHoipoiMix"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMHoipoiMix*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building HoipoiMix event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMHoipoiMix*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building HoipoiMix event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMHoipoiMix. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMPrivateShop");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMPrivateShop"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMPrivateShop*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building PrivateShop event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMPrivateShop*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building PrivateShop event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMPrivateShop. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMFreeBattle");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMFreeBattle"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMFreeBattle*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building FreeBattle event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMFreeBattle*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building FreeBattle event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMFreeBattle. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMItemIdentity");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMItemIdentity"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMItemIdentity*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building item identity event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMItemIdentity*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building item identity event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMItemIdentity. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMUseMail");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMUseMail"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMUseMail*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building use mail event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMUseMail*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building use mail event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMUseMail. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	pObj = m_pCtrlFactory->CreateObj("CDboTSEMParty");
	if (pObj && pObj->IsDerivedClass("CNtlTSEvtMapper") && pObj->IsDerivedClass("CDboTSEMParty"))
	{
		m_defEvtMapper[pObj->GetClassName()] = (CNtlTSEvtMapper*)pObj;

		if (!((CDboTSEMParty*)pObj)->AddBuildData("quest", m_defQuest, NULL, NULL))
		{
			CNtlTSLog::Log("Building party event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}

		if (!((CDboTSEMParty*)pObj)->AddBuildData("pctrigger", m_defTrigger, NULL, NULL))
		{
			CNtlTSLog::Log("Building party event mapper is failed. [%s].", TS_CODE_TRACE());
			return false;
		}
	}
	else
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSEMParty. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		return false;
	}

	return true;
}

CGameQuestAgency* CQuestWrapper::CreateAgency_Quest(void)
{
	DeleteAgency_Quest();

	CNtlTSUIObject* pObj = m_pUIFactory->CreateObj("CDboTSSQAgency");
	if (0 == pObj || !pObj->IsDerivedClass("CDboTSSQAgency"))
	{
		CNtlTSLog::Log("Can not type cast from CNtlTSUIObject to CDboTSSQAgency. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		if (0 != pObj) m_pUIFactory->DeleteObj(pObj);
		return 0;
	}

	m_pQAgency = (CGameQuestAgency*)pObj;
	m_pQAgency->SetParent(this);
	m_pQAgency->SetRecv(GetQRecv());

	return m_pQAgency;
}

void CQuestWrapper::DeleteAgency_Quest(void)
{
	if (m_pQAgency)
	{
		DeleteAgency((CNtlTSAgency*&)m_pQAgency);
	}
}

CGameTriggerAgency* CQuestWrapper::CreateAgency_Trigger(void)
{
	DeleteAgency_Trigger();

	CNtlTSUIObject* pObj = m_pUIFactory->CreateObj("CDboTSSTAgency");
	if (0 == pObj || !pObj->IsDerivedClass("CDboTSSTAgency"))
	{
		CNtlTSLog::Log("Can not type cast from CNtlTSUIObject to CDboTSSTAgency. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		if (0 != pObj) m_pUIFactory->DeleteObj(pObj);
		return 0;
	}

	m_pTAgency = (CGameTriggerAgency*)pObj;
	m_pTAgency->SetParent(this);
	m_pTAgency->SetRecv(GetTRecv());

	return m_pTAgency;
}

void CQuestWrapper::DeleteAgency_Trigger(void)
{
	if (m_pTAgency)
	{
		DeleteAgency((CNtlTSAgency*&)m_pTAgency);
	}
}

CNtlTSTrigger* CQuestWrapper::FindQuestFromTS(NTL_TS_T_ID tId)
{
	mapdef_TLIST::iterator it = m_defQuest.find(tId);
	if (it == m_defQuest.end())
	{
		if (m_bSchedulingLoad)
		{
			if (!LoadTriggerObjectFromUnZip(tId, m_pclQuestZip, m_defQuest))
			{
				return 0;
			}
			else
			{
				it = m_defQuest.find(tId);

				if (it == m_defQuest.end())
				{
					return 0;
				}

				return it->second;
			}
		}

		return 0;
	}

	return it->second;
}

CGameObjectAgency* CQuestWrapper::CreateAgency_Object(void)
{
	DeleteAgency_Object();

	CNtlTSUIObject* pObj = m_pUIFactory->CreateObj("CDboTSSObjAgency");
	if (0 == pObj || !pObj->IsDerivedClass("CDboTSSObjAgency"))
	{
		CNtlTSLog::Log("Can not type cast from CNtlTSUIObject to CDboTSSObjAgency. Info[%s]. [%s]", pObj ? pObj->GetClassName() : "NULL", TS_CODE_TRACE());
		if (0 != pObj) m_pUIFactory->DeleteObj(pObj);
		return 0;
	}

	m_pObjAgency = (CGameObjectAgency*)pObj;
	m_pObjAgency->SetParent(this);

	return m_pObjAgency;
}

void CQuestWrapper::DeleteAgency_Object(void)
{
	if (m_pObjAgency)
	{
		DeleteAgency((CNtlTSAgency*&)m_pObjAgency);
	}
}

CNtlTSTrigger* CQuestWrapper::FindObjectFromTS(NTL_TS_T_ID tId)
{
	mapdef_TLIST::iterator it = m_defObject.find(tId);
	if (it == m_defObject.end())
	{
		if (m_bSchedulingLoad)
		{
			if (!LoadTriggerObjectFromUnZip(tId, m_pclObjectZip, m_defObject))
			{
				return 0;
			}
			else
			{
				it = m_defObject.find(tId);

				if (it == m_defObject.end())
				{
					return 0;
				}

				return it->second;
			}
		}

		return 0;
	}

	return it->second;
}

CNtlTSMain::mapdef_TLISTC_CIT CQuestWrapper::BeginObjectFromTS(void) const
{
	return m_defObject.begin();
}

CNtlTSMain::mapdef_TLISTC_CIT CQuestWrapper::EndObjectFromTS(void) const
{
	return m_defObject.end();
}

sVECTOR3* CQuestWrapper::FindNPCPosition(TBLIDX WorldIdx, TBLIDX NPCIdx)
{
	NPC_POS_KEY Key = (((NPC_POS_KEY)WorldIdx << 32) | (NPC_POS_KEY)NPCIdx);

	mapdef_NPC_POS_LIST::iterator it = m_defNPCPosList.find(Key);
	if (it == m_defNPCPosList.end()) return NULL;

	return &it->second.Pos;
}

CNtlTSMain::mapdef_TLISTC_CIT CQuestWrapper::BeginQuestFromTS(void) const
{
	return m_defQuest.begin();
}

CNtlTSMain::mapdef_TLISTC_CIT CQuestWrapper::EndQuestFromTS(void) const
{
	return m_defQuest.end();
}

CNtlTSTrigger* CQuestWrapper::FindTriggerFromTS(NTL_TS_T_ID tId)
{
	mapdef_TLIST::iterator it = m_defTrigger.find(tId);
	if (it == m_defTrigger.end())
	{
		if (m_bSchedulingLoad)
		{
			if (!LoadTriggerObjectFromUnZip(tId, m_pclTriggerZip, m_defTrigger))
			{
				return 0;
			}
			else
			{
				it = m_defTrigger.find(tId);

				if (it == m_defTrigger.end())
				{
					return 0;
				}

				return it->second;
			}
		}

		return 0;
	}

	return it->second;
}

CNtlTSMain::mapdef_TLISTC_CIT CQuestWrapper::BeginTriggerFromTS(void) const
{
	return m_defTrigger.begin();
}

CNtlTSMain::mapdef_TLISTC_CIT CQuestWrapper::EndTriggerFromTS(void) const
{
	return m_defTrigger.end();
}

CDboTSTCtrl* CQuestWrapper::MakeTriggerControllerQuest(CNtlTSTrigger* pNTLTrigger, CDboTSQAgency* questAgency)
{
	CNtlTSControlObject* pCtrlObj = m_pCtrlFactory->CreateObj("CDboTSQCtrl");
	if (!pCtrlObj->IsDerivedClass("CDboTSQCtrl"))
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSQCtrl. Info[%s]. [%s]", pCtrlObj->GetClassName(), TS_CODE_TRACE());
		m_pCtrlFactory->DeleteObj(pCtrlObj);
		return 0;
	}

	((CDboTSQCtrl*)pCtrlObj)->SetTrigger(pNTLTrigger);
	((CDboTSQCtrl*)pCtrlObj)->SetParent(questAgency);

	return (CDboTSQCtrl*)pCtrlObj;
}

void CQuestWrapper::RegisterNPCPosition(TBLIDX WorldIdx, TBLIDX NPCIdx, sVECTOR3& v3Pos)
{
	NPC_POS_KEY Key = (((NPC_POS_KEY)WorldIdx << 32) | (NPC_POS_KEY)NPCIdx);

	sNPC_POS_INFO sPosInfo;
	sPosInfo.Pos = v3Pos;

	m_defNPCPosList[Key] = sPosInfo;
}

void CQuestWrapper::ClearAllNPCPosition(void)
{
	m_defNPCPosList.clear();
}

CDboTSTCtrl* CQuestWrapper::MakeTriggerControllerTrigger(CNtlTSTrigger* pNTLTrigger, CDboTSTAgency* triggerAgency)
{
	CNtlTSControlObject* pCtrlObj = m_pCtrlFactory->CreateObj("CDboTSTCtrl");
	if (!pCtrlObj->IsDerivedClass("CDboTSTCtrl"))
	{
		CNtlTSLog::Log("Can not do type cast from CNtlTSControlObject to CDboTSTCtrl. Info[%s]. [%s]", pCtrlObj->GetClassName(), TS_CODE_TRACE());
		m_pCtrlFactory->DeleteObj(pCtrlObj);
		return 0;
	}

	((CDboTSTCtrl*)pCtrlObj)->SetTrigger(pNTLTrigger);
	((CDboTSTCtrl*)pCtrlObj)->SetParent(triggerAgency);

	return (CDboTSTCtrl*)pCtrlObj;
}