#include "precomp_trigger.h"
#include "DboTSActAvatarDead.h"


/**
	Avatar dead
*/


NTL_TS_IMPLEMENT_RTTI(CDboTSActAvatarDead, CNtlTSAction)


CDboTSActAvatarDead::CDboTSActAvatarDead(void)
	: m_uiStart(0xffffffff)
{
}

void CDboTSActAvatarDead::SetStart(unsigned int uiStart)
{
	m_uiStart = uiStart;
}

void CDboTSActAvatarDead::ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty)
{
	CNtlTSAction::ApplyScriptDataForScript(clProperty);

	if (clProperty.IsExist("start"))
	{
		SetStart(clProperty.GetValueAsInt("start"));
	}
}

void CDboTSActAvatarDead::TakeScriptDataForScript(CNtlTSScrProperty& clProperty)
{
	CNtlTSAction::TakeScriptDataForScript(clProperty);

	sprintf_s(g_NtlTSString, "%d", GetStart());
	clProperty.m_defProperty["start"] = g_NtlTSString;
}