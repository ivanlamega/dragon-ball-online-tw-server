#include "precomp_trigger.h"
#include "DboTSClickSideIcon.h"


/**
	Click side icon
*/


NTL_TS_IMPLEMENT_RTTI(CDboTSClickSideIcon, CNtlTSCond)


CDboTSClickSideIcon::CDboTSClickSideIcon(void)
	: m_nSitype(0)
{
}

void CDboTSClickSideIcon::SetSitype(int nSitype)
{
	m_nSitype = nSitype;
}

void CDboTSClickSideIcon::ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty)
{
	CNtlTSCond::ApplyScriptDataForScript(clProperty);

	if (clProperty.IsExist("sitype"))
	{
		SetSitype(clProperty.GetValueAsInt("sitype"));
	}
}

void CDboTSClickSideIcon::TakeScriptDataForScript(CNtlTSScrProperty& clProperty)
{
	CNtlTSCond::TakeScriptDataForScript(clProperty);

	sprintf_s(g_NtlTSString, "%d", GetSitype());
	clProperty.m_defProperty["sitype"] = g_NtlTSString;
}
