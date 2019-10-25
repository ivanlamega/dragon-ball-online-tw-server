#include "precomp_trigger.h"
#include "DboTSActSkyDgn.h"

/**
Direction action
*/


NTL_TS_IMPLEMENT_RTTI(CDboTSActSkyDgn, CNtlTSAction)


CDboTSActSkyDgn::CDboTSActSkyDgn(void)
	:m_uiType(0xffffffff),
	m_uiIdx(0xffffffff)
{
}

void CDboTSActSkyDgn::SetType(unsigned int uiType)
{
	m_uiType = uiType;
}

void CDboTSActSkyDgn::SetIdx(unsigned int uiIdx)
{
	m_uiIdx = uiIdx;
}

void CDboTSActSkyDgn::ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty)
{
	CNtlTSAction::ApplyScriptDataForScript(clProperty);

	if (clProperty.IsExist("type"))
	{
		SetType(clProperty.GetValueAsInt("type"));
	}

	if (clProperty.IsExist("idx"))
	{
		SetIdx(clProperty.GetValueAsInt("idx"));
	}
}

void CDboTSActSkyDgn::TakeScriptDataForScript(CNtlTSScrProperty& clProperty)
{
	CNtlTSAction::TakeScriptDataForScript(clProperty);

	sprintf_s(g_NtlTSString, "%d", GetType());
	clProperty.m_defProperty["type"] = g_NtlTSString;

	sprintf_s(g_NtlTSString, "%d", GetIdx());
	clProperty.m_defProperty["idx"] = g_NtlTSString;
}

