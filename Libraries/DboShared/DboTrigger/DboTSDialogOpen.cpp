#include "precomp_trigger.h"
#include "DboTSDialogOpen.h"


/**
Proposal container
*/


NTL_TS_IMPLEMENT_RTTI(CDboTSDialogOpen, CNtlTSCont)


CDboTSDialogOpen::CDboTSDialogOpen(void)
{
	m_uiDotype = 0xffffffff;
}

void CDboTSDialogOpen::SetDotype(unsigned int uiDotype)
{
	m_uiDotype = uiDotype;
}

void CDboTSDialogOpen::ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty)
{
	CNtlTSCont::ApplyScriptDataForScript(clProperty);

	if (clProperty.IsExist("dotype"))
	{
		SetDotype(clProperty.GetValueAsInt("dotype"));
	}
}

void CDboTSDialogOpen::TakeScriptDataForScript(CNtlTSScrProperty& clProperty)
{
	CNtlTSCont::TakeScriptDataForScript(clProperty);

	sprintf_s(g_NtlTSString, "%d", GetDotype());
	clProperty.m_defProperty["dotype"] = g_NtlTSString;
}