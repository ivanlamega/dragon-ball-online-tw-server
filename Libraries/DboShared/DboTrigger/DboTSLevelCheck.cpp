#include "precomp_trigger.h"
#include "DboTSLevelCheck.h"


/**
Check level condition
*/


NTL_TS_IMPLEMENT_RTTI(CDboTSLevelCheck, CNtlTSCond)


CDboTSLevelCheck::CDboTSLevelCheck(void)
{
}

void CDboTSLevelCheck::ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty)
{
	CNtlTSCond::ApplyScriptDataForScript(clProperty);
}

void CDboTSLevelCheck::TakeScriptDataForScript(CNtlTSScrProperty& clProperty)
{
	CNtlTSCond::TakeScriptDataForScript(clProperty);
}
