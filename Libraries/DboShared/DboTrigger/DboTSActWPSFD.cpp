#include "precomp_trigger.h"
#include "DboTSActWPSFD.h"


/**
Create quest item action
*/


NTL_TS_IMPLEMENT_RTTI(CDboTSActWPSFD, CNtlTSAction)

CDboTSActWPSFD::CDboTSActWPSFD(void)
	: m_uiSid(0xffffffff)
{
}

void CDboTSActWPSFD::SetSid(unsigned int uiSid)
{
	m_uiSid = uiSid;
}

void CDboTSActWPSFD::ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty)
{
	CNtlTSAction::ApplyScriptDataForScript(clProperty);

	if (clProperty.IsExist("sid"))
	{
		SetSid(clProperty.GetValueAsInt("sid"));
	}
}

void CDboTSActWPSFD::TakeScriptDataForScript(CNtlTSScrProperty& clProperty)
{
	CNtlTSAction::TakeScriptDataForScript(clProperty);

	sprintf_s(g_NtlTSString, "%d", GetSid());
	clProperty.m_defProperty["sid"] = g_NtlTSString;
}