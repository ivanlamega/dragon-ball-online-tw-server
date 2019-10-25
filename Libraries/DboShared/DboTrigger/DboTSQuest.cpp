#include "precomp_trigger.h"
#include "DboTSQuest.h"


/**
	Quest
*/


NTL_TS_IMPLEMENT_RTTI(CDboTSQuest, CNtlTSCond)


CDboTSQuest::CDboTSQuest(void)
{
}

void CDboTSQuest::ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty)
{
	CNtlTSCond::ApplyScriptDataForScript(clProperty);
}

void CDboTSQuest::TakeScriptDataForScript(CNtlTSScrProperty& clProperty)
{
	CNtlTSCond::TakeScriptDataForScript(clProperty);
}
