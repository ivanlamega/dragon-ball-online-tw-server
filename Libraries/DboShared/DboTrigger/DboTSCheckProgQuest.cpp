#include "precomp_trigger.h"
#include "DboTSCheckProgQuest.h"


/**
	Check progress quest condition
*/


NTL_TS_IMPLEMENT_RTTI( CDboTSCheckProgQuest, CNtlTSCond )


CDboTSCheckProgQuest::CDboTSCheckProgQuest( void )
: m_tQuestID( NTL_TS_T_ID_INVALID )
{
}

void CDboTSCheckProgQuest::SetQuestID( NTL_TS_T_ID tQID )
{
	m_tQuestID = tQID;
}

bool CDboTSCheckProgQuest::SetNotIdList(const std::string& strIDList)
{
	std::string strNum;
	strNum.reserve(10);

	std::string::const_iterator cit = strIDList.begin();
	for (; cit != strIDList.end(); ++cit)
	{
		if (';' == *cit)
		{
			m_vecNotIdList.push_back((NTL_TS_T_ID)atoi(strNum.c_str()));
			strNum.clear();
		}
		else if ('0' > *cit || '9' < *cit)
		{
			m_vecNotIdList.clear();
			CNtlTSLog::Log("Only must have numbers. Info[%s]. [%s]", strIDList.c_str(), TS_CODE_TRACE());
			return false;
		}
		else
		{
			strNum += *cit;
		}
	}

	if (!strNum.empty())
	{
		m_vecNotIdList.push_back((NTL_TS_T_ID)atoi(strNum.c_str()));
	}

	return true;
}

void CDboTSCheckProgQuest::ClearNotIdList(void)
{
	m_vecNotIdList.clear();
}

void CDboTSCheckProgQuest::ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty )
{
	CNtlTSCond::ApplyScriptDataForScript( clProperty );

	if ( clProperty.IsExist( "qid" ) )
	{
		SetQuestID( (NTL_TS_T_ID)clProperty.GetValueAsInt( "qid" ) );
	}

	if (clProperty.IsExist("not"))
	{
		SetNotIdList(clProperty.GetValue("not"));
	}
}

void CDboTSCheckProgQuest::TakeScriptDataForScript( CNtlTSScrProperty& clProperty )
{
	CNtlTSCond::TakeScriptDataForScript( clProperty );

	std::string strIdList;
	std::vector<NTL_TS_T_ID>::iterator it;

	sprintf_s( g_NtlTSString, "%d", GetQuestID() );
	clProperty.m_defProperty["qid"] = g_NtlTSString;

	strIdList.clear();
	it = m_vecNotIdList.begin();
	for (; it != m_vecNotIdList.end(); ++it)
	{
		sprintf_s(g_NtlTSString, "%d", *it);
		strIdList += g_NtlTSString;
		strIdList += ";";
	}
	if (!strIdList.empty())
	{
		clProperty.m_defProperty["not"] = strIdList;
	}
}
