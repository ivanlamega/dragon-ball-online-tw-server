#include "precomp_trigger.h"
#include "DboTSActMail.h"


/**
Direction action
*/


NTL_TS_IMPLEMENT_RTTI(CDboTSActMail, CNtlTSAction)


CDboTSActMail::CDboTSActMail(void)
	: m_uiZenny(0xffffffff), 
	m_uiIcnt(0xffffffff), 
	m_uiStidx(0xffffffff), 
	m_uiItidx(0xffffffff), 
	m_uiDtidx(0xffffffff)
{
}

void CDboTSActMail::SetZenny(unsigned int uiZenny)
{
	m_uiZenny = uiZenny;
}

void CDboTSActMail::SetIcnt(unsigned int uiIcnt)
{
	m_uiIcnt = uiIcnt;
}

void CDboTSActMail::SetStidx(unsigned int TblIdx)
{
	m_uiStidx = TblIdx;
}

void CDboTSActMail::SetItidx(unsigned int TblIdx)
{
	m_uiItidx = TblIdx;
}

void CDboTSActMail::SetDtidx(unsigned int TblIdx)
{
	m_uiDtidx = TblIdx;
}

void CDboTSActMail::ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty)
{
	CNtlTSAction::ApplyScriptDataForScript(clProperty);

	if (clProperty.IsExist("zenny"))
	{
		SetZenny(clProperty.GetValueAsInt("zenny"));
	}

	if (clProperty.IsExist("icnt"))
	{
		SetIcnt(clProperty.GetValueAsInt("icnt"));
	}

	if (clProperty.IsExist("stidx"))
	{
		SetStidx(clProperty.GetValueAsInt("stidx"));
	}

	if (clProperty.IsExist("itidx"))
	{
		SetItidx(clProperty.GetValueAsInt("itidx"));
	}

	if (clProperty.IsExist("dtidx"))
	{
		SetDtidx(clProperty.GetValueAsInt("dtidx"));
	}
}

void CDboTSActMail::TakeScriptDataForScript(CNtlTSScrProperty& clProperty)
{
	CNtlTSAction::TakeScriptDataForScript(clProperty);

	sprintf_s(g_NtlTSString, "%d", GetZenny());
	clProperty.m_defProperty["zenny"] = g_NtlTSString;

	sprintf_s(g_NtlTSString, "%d", GetIcnt());
	clProperty.m_defProperty["icnt"] = g_NtlTSString;

	sprintf_s(g_NtlTSString, "%d", GetStidx());
	clProperty.m_defProperty["stidx"] = g_NtlTSString;

	sprintf_s(g_NtlTSString, "%d", GetItidx());
	clProperty.m_defProperty["itidx"] = g_NtlTSString;

	sprintf_s(g_NtlTSString, "%d", GetDtidx());
	clProperty.m_defProperty["dtidx"] = g_NtlTSString;
}