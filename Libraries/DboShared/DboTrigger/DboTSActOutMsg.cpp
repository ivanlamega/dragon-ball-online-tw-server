#include "precomp_trigger.h"
#include "DboTSActOutMsg.h"

/**
	Message out action
*/

NTL_TS_IMPLEMENT_RTTI(CDboTSActOutMsg, CNtlTSAction)

CDboTSActOutMsg::CDboTSActOutMsg(void)
	: m_uiMsgIdx(0xffffffff)
{
}

void CDboTSActOutMsg::SetMsgIdx(unsigned int uiMsjIdx)
{
	m_uiMsgIdx = uiMsjIdx;
}

void CDboTSActOutMsg::ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty)
{
	CNtlTSAction::ApplyScriptDataForScript(clProperty);

	if (clProperty.IsExist("idx"))
	{
		SetMsgIdx(clProperty.GetValueAsInt("idx"));
	}
}

void CDboTSActOutMsg::TakeScriptDataForScript(CNtlTSScrProperty& clProperty)
{
	CNtlTSAction::TakeScriptDataForScript(clProperty);

	sprintf_s(g_NtlTSString, "%d", GetMsgIdx());
	clProperty.m_defProperty["idx"] = g_NtlTSString;
}