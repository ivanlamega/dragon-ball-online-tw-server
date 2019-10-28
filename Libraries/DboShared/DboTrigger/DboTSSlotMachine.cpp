#include "precomp_trigger.h"
#include "DboTSSlotMachine.h"


/**
	Slot machine
*/


NTL_TS_IMPLEMENT_RTTI( CDboTSSlotMachine, CNtlTSEvent )


CDboTSSlotMachine::CDboTSSlotMachine( void )
	: m_uiST(0xffffffff)
{
}

void CDboTSSlotMachine::SetST(unsigned int uiST)
{
	m_uiST = uiST;
}

void CDboTSSlotMachine::ApplyScriptDataForScript( const CNtlTSScrProperty& clProperty )
{
	CNtlTSEvent::ApplyScriptDataForScript( clProperty );

	if (clProperty.IsExist("st"))
	{
		SetST(clProperty.GetValueAsInt("st"));
	}
}

void CDboTSSlotMachine::TakeScriptDataForScript( CNtlTSScrProperty& clProperty )
{
	CNtlTSEvent::TakeScriptDataForScript( clProperty );

	sprintf_s(g_NtlTSString, "%d", GetST());
	clProperty.m_defProperty["st"] = g_NtlTSString;
}
