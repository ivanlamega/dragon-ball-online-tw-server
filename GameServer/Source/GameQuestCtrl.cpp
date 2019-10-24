#include "stdafx.h"
#include "GameQuestCtrl.h"
#include "GameQuestRecv.h"
#include "GameQuestAgency.h"
//#include "NTLResultCode.h"
#include "QuestWrapper.h"
#include "TableContainer.h"
#include "ObjectTable.h"
#include "GameQuestAgency.h"
#include "QuestItemTable.h"
#include "GameServer.h"

#include "TableContainer.h"
#include "QuestRewardTable.h"

NTL_TS_IMPLEMENT_RTTI(CGameQuestCtrl, CDboTSQCtrl)

CGameQuestCtrl::CGameQuestCtrl()
{
}


CGameQuestCtrl::~CGameQuestCtrl()
{
}

void CGameQuestCtrl::CheckContainer(CNtlTSCont* pCurCont, CNtlTSCont* pNextCont, CNtlTSTrigger* pTrigger, CDboTSTCtrl* pTriggerCtrl)
{
	if (pCurCont){
		switch (pCurCont->GetEntityType())
		{
		case DBO_CONT_TYPE_ID_CONT_GCOND:
		{
			CDboTSContGCond* pCond = (CDboTSContGCond*)pCurCont;
			CheckContCond(pCond, pCurCont);
		}
		break;
		case DBO_CONT_TYPE_ID_CONT_GACT:
		{
			CDboTSContGAct* pCont = (CDboTSContGAct*)pCurCont;
			CheckContAct(pCont, pCurCont);
		}
		break;
		case DBO_CONT_TYPE_ID_CONT_USERSEL:
		{
			CDboTSContUsrSel* pContUsr = (CDboTSContUsrSel*)pCurCont;
			CheckContUserSel(pContUsr, pCurCont);
		}
		break;
		case DBO_CONT_TYPE_ID_CONT_REWARD:
		{
			CDboTSContReward* pCont = (CDboTSContReward*)pCurCont;
			CheckContReward(pCont, pCurCont);
		}
		break;
		case DBO_CONT_TYPE_ID_CONT_START:
		{
			CDboTSContStart* pStart = (CDboTSContStart*)pCurCont;
			CheckContStart(pStart, pCurCont);
		}
		break;
		case DBO_CONT_TYPE_ID_CONT_END:
		{
			CDboTSContEnd* pEnd = (CDboTSContEnd*)pCurCont;
			CheckContEnd(pEnd, pCurCont);
		}
		break;
		case DBO_CONT_TYPE_ID_CONT_NARRATION:
		{
			CDboTSContNarration* pContNarration = (CDboTSContNarration*)pCurCont;
			CheckContNarration(pContNarration, pCurCont);
		}
		break;
		case DBO_CONT_TYPE_ID_CONT_PROPOSAL:
		{
			CDboTSContProposal* pContProposal = (CDboTSContProposal*)pCurCont;
			CheckContProposal(pContProposal, pCurCont);
		}
		break;

		case DBO_CONT_TYPE_ID_CONT_SWITCH:
		{
			CDboTSContSwitch* pContSwitch = (CDboTSContSwitch*)pCurCont;
			CheckContSwitch(pContSwitch, pCurCont);
		}
		break;

		case DBO_CONT_TYPE_ID_CONT_UNIFIED_NARRATION:
		{
			CDboTSContUnifiedNarration* pContNarration = (CDboTSContUnifiedNarration*)pCurCont;
			CheckContUnifiedNarration(pContNarration, pCurCont);
		}
		break;
		}
	}
}
//Containers
void CGameQuestCtrl::CheckContCond(CDboTSContGCond* pCond, CNtlTSCont* pParent)
{
	printf("CONT_GCOND\n");
	CNtlTSEntity* pEvtEntity = pCond->GetEventEntity();
	if (pEvtEntity)
	{
		switch (pEvtEntity->GetEntityType())
		{
		case DBO_EVENT_TYPE_ID_BIND_STONE:
		{
			printf("EventBindStone\n");
			SendEvtBindStone((CDboTSBindStone*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_BUDOKAI:
		{
			printf("EventBudokai\n");
			SendEvtBudokai((CDboTSBudokai*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_CLICK_MOB:
		{
			printf("EventClickMob\n");
			SendEvtClickMob((CDboTSClickMob*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_CLICK_NPC:
		{
			printf("EventClickNPC\n");
			SendEvtClickNPC((CDboTSClickNPC*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_CLICK_OBJECT:
		{
			printf("EventClickObject\n");
			SendEvtClickObject((CDboTSClickObject*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_COL_OBJECT:
		{
			printf("EventColObject\n");
			SendEvtColObject((CDboTSColObject*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_COL_RGN:
		{
			printf("EventColRGN\n");
			SendEvtColRgn((CDboTSColRgn*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_FREEBATTLE:
		{
			printf("EventFreeBattle\n");
			SendEvtFreeBattle((CDboTSFreeBattle*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_HOIPOIMIX:
		{
			printf("EventHoiPoiMix\n");
			SendEvtHoipoiMix((CDboTSHoipoiMix*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_ITEMIDENTITY:
		{
			printf("EventItemIdentity\n");
			SendEvtItemIdentity((CDboTSItemIdentity*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_ITEM_EQUIP:
		{
			printf("EventItemEquip\n");
			SendEvtItemEquip((CDboTSItemEquip*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_ITEM_GET:
		{
			printf("EventItemGet\n");
			SendEvtItemGet((CDboTSItemGet*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_ITEM_UPGRADE:
		{
			printf("EventItemUpgrade\n");
			SendEvtItemUpgrade((CDboTSItemUpgrade*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_ITEM_USE:
		{
			printf("EventItemUse\n");
			SendEvtItemUse((CDboTSItemUse*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_PARTY:
		{
			printf("EventParty\n");
			SendEvtParty((CDboTSParty*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_PRIVATESHOP:
		{
			printf("EventPrivateShop\n");
			SendEvtPrivateShop((CDboTSPrivateShop*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_RB:
		{
			printf("EventRB\n");
			SendEvtRB((CDboTSRB*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_RCV_SVR_EVT:
		{
			printf("EventRcv_Svr_Evt\n");
			SendEvtRcvSvrEvt((CDboTSRcvSvrEvt*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_SCOUT_USE:
		{
			printf("EventScoutUse\n");
			SendEvtScoutUse((CDboTSScoutUse*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_SEARCH_QUEST:
		{
			printf("EventSearchQuest\n");
			SendEvtSearchQuest((CDboTSSearchQuest*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_SKILL_USE:
		{
			printf("EventSkillUse\n");
			SendEvtSkillUse((CDboTSSkillUse*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_SLOTMACHINE:
		{
			printf("EventSlotMachine\n");
			SendEvtSlotMachine((CDboTSSlotMachine*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_TELEPORT:
		{
			printf("EventTeleport\n");
			SendEvtTeleport((CDboTSTeleport*)pEvtEntity);
		}
		break;
		case DBO_EVENT_TYPE_ID_USERMAIL:
		{
			printf("EventUserMail\n");
			SendEvtUseMail((CDboTSUseMail*)pEvtEntity);
		}
		break;
		}
	}
}
void CGameQuestCtrl::CheckContStart(CDboTSContStart* pStart, CNtlTSCont* pParent)
{
	printf("CONT_START\n");
}
void CGameQuestCtrl::CheckContAct(CDboTSContGAct* pAct, CNtlTSCont* pParent)
{
	printf("CONT_GACT\n");
	int nSize = pAct->GetNumOfChildEntity();
	for (int i = 0; i < nSize; ++i)
	{
		CNtlTSEntity* pEntity = pAct->GetChildEntity(i);
		//You can switch by "pAct->GetEntityType()" and use DBO_ACT constants too, but i preffer identify the class by that way
		if (pEntity->IsDerivedClass("CDboTSActPortal"))
		{
			SendActPortal((CDboTSActPortal*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActBroadMsg"))
		{
			SendActBroadMsg((CDboTSActBroadMsg*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActConcCheck"))
		{
			SendActConcCheck((CDboTSActConcCheck*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActCustomEvt"))
		{
			SendActCustomEvt((CDboTSActCustomEvt*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActDir"))
		{
			SendActDir((CDboTSActDir*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActDirIndicator"))
		{
			SendActDirIndicator((CDboTSActDirIndicator*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActDojo"))
		{
			SendActDojo((CDboTSActDojo*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActDoSkill"))
		{
			SendActDoSkill((CDboTSActDoSkill*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActDrop"))
		{
			SendActDrop((CDboTSActDrop*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActEscort"))
		{
			SendActEscort((CDboTSActEscort*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActETimerE"))
		{
			SendActETimerE((CDboTSActETimerE*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActETimerS"))
		{
			SendActETimerS((CDboTSActETimerS*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActExCGroup"))
		{
			SendActExCGroup((CDboTSActExcCGroup*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActHint"))
		{
			SendActHint((CDboTSActHint*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActInSSM"))
		{
			SendActInSSM((CDboTSActInSSM*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActItem"))
		{
			SendActItem((CDboTSActItem*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActMiniNarration"))
		{
			SendActMiniNarration((CDboTSActMiniNarration*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActNPCConv"))
		{
			SendActNPCConv((CDboTSActNPCConv*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActOutMsg"))
		{
			SendActOutMsg((CDboTSActOutMsg*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActObjConv"))
		{
			SendActObjConv((CDboTSActObjConv*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActObjState"))
		{
			SendActObjState((CDboTSActObjState*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActObjWPS"))
		{
			SendActObjWPS((CDboTSActObjWPS*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActOPCam"))
		{
			SendActOPCam((CDboTSActOPCam*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActOpenWindow"))
		{
			SendActOpenWindow((CDboTSActOpenWindow*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActOPObject"))
		{
			SendActOPObject((CDboTSActOPObject*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActPCConv"))
		{
			SendActPCConv((CDboTSActPCConv*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActPIDgn"))
		{
			SendActPIDgn((CDboTSActPIDgn*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActQItem"))
		{
			SendActQItem((CDboTSActQItem*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActRegCTiming"))
		{
			SendActRegCTiming((CDboTSActRegCTiming*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActRegQInfo"))
		{
			SendActRegQInfo((CDboTSActRegQInfo*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActRmvCoupon"))
		{
			SendActRmvCoupon((CDboTSActRmvCoupon*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActSendSvrEvt"))
		{
			SendActSendSvrEvt((CDboTSActSendSvrEvt*)pEntity, pParent);
		}
		else if (pEntity->IsDerivedClass("CDboTSActSkipCont"))
		{
			SendActSkipCont((CDboTSActSkipCont*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActSToCEvt"))
		{
			SendActSToCEvt((CDboTSActSToCEvt*)pEntity);
		}
		else if (pEntity->IsDerivedClass("CDboTSActSWProbSF"))
		{
			SendActSWProbSF((CDboTSActSWProbSF*)pEntity);
		}
		else
		{
			printf("Not indentified Class at CGameQuestCtrl");
		}
	}
}
void CGameQuestCtrl::CheckContReward(CDboTSContReward* pReward, CNtlTSCont* pParent)
{
	printf("CONT_REWARD\n");
	//CQuestRewardTable* pQuestRewardTable = ((CGameServer*)NtlSfxGetApp())->GetTableContainer()->GetQuestRewardTable();
	sQUEST_REWARD_TBLDAT* pRewardTblDat = (sQUEST_REWARD_TBLDAT*)sTBM.GetQuestRewardTable()->FindData(pReward->GetRewardTableIndex());//reinterpret_cast<sQUEST_REWARD_TBLDAT*>(pQuestRewardTable->FindData(pReward->GetRewardTableIndex()));
	sREWARD_INFO m_pDefRwd[QUEST_REWARD_DEF_MAX_CNT];
	sREWARD_INFO m_pSelRwd[QUEST_REWARD_SEL_MAX_CNT];
	//Mount quest values
	for (int i = 0; i < QUEST_REWARD_DEF_MAX_CNT; i++)
	{
		m_pDefRwd[i].m_eType = (eREWARD_TYPE)pRewardTblDat->unk2[i].unk;
		m_pDefRwd[i].m_nValue = pRewardTblDat->unk2[i].Amount;
		m_pDefRwd[i].m_uiIdx = pRewardTblDat->unk2[i].Item;
	}
	for (int i = 0; i < QUEST_REWARD_SEL_MAX_CNT; i++)
	{
		m_pSelRwd[i].m_eType = (eREWARD_TYPE)pRewardTblDat->unk2[i].unk;
		m_pSelRwd[i].m_nValue = pRewardTblDat->unk2[i].Amount;
		m_pSelRwd[i].m_uiIdx = pRewardTblDat->unk2[i].Item;
	}
	//Now we gona send the quest rewards
	for (int i = 0; i < QUEST_REWARD_DEF_MAX_CNT; i++)
		CheckRewardTypeAndSend(&m_pDefRwd[i], &m_pSelRwd[i]);
}
void CGameQuestCtrl::CheckContEnd(CDboTSContEnd* pEnd, CNtlTSCont* pParent)
{
	printf("CONT_END\n");

}
void CGameQuestCtrl::CheckContUserSel(CDboTSContUsrSel* pUserSel, CNtlTSCont* pParent)
{
	printf("CONT_USERSEL\n");
}
void CGameQuestCtrl::CheckContNarration(CDboTSContNarration* pNarration, CNtlTSCont* pParent)
{
	printf("CONT_NARRATION\n");
}
void CGameQuestCtrl::CheckContProposal(CDboTSContProposal* pProposal, CNtlTSCont* pParent)
{
	printf("CONT_PROPOSAL\n");
}
void CGameQuestCtrl::CheckContSwitch(CDboTSContSwitch* pSwitch, CNtlTSCont* pParent)
{
	printf("CONT_SWITCH\n");
}
void CGameQuestCtrl::CheckContUnifiedNarration(CDboTSContUnifiedNarration* pUnifiedNarration, CNtlTSCont* pParent)
{
	printf("CONT_UNIFIED_NARRATION\n");
}
//Misc and Others
void CGameQuestCtrl::CheckRewardTypeAndSend(sREWARD_INFO* m_pDefRwd, sREWARD_INFO* m_pSelRwd)
{
	switch (m_pDefRwd->m_eType)
	{
		case eREWARD_TYPE_NORMAL_ITEM:
		{
		}
		break;
		case eREWARD_TYPE_SKILL:
		case eREWARD_TYPE_BUFF:
		{
		}
		break;
		case eREWARD_TYPE_ZENY:
		{
		}
		break;
		case eREWARD_TYPE_QUEST_ITEM:
		{
		}
		break;
		case eREWARD_TYPE_CHANGE_CLASS:
		{
		}
		break;
		case eREWARD_TYPE_PROBABILITY:
		{
		}
		break;
		case eREWARD_TYPE_REPUTATION:
		{
		}
		break;
		case eREWARD_TYPE_CHANGE_ADULT:
		{
		}
		break;
		case eREWARD_TYPE_GET_CONVERT_CLASS_RIGHT:
		{
		}
		break;
		case eREWARD_TYPE_EXP:
		{			
		}
		break;
	}
	switch (m_pSelRwd->m_eType)
	{
		case eREWARD_TYPE_NORMAL_ITEM:
		{
			
		}
		break;
		case eREWARD_TYPE_QUEST_ITEM:
		{			
		}
		break;
		case eREWARD_TYPE_CHANGE_CLASS:
		{
		}
		break;
		case eREWARD_TYPE_PROBABILITY:
		{
		}
		break;
		case eREWARD_TYPE_REPUTATION:
		{
		}
		break;
		case eREWARD_TYPE_CHANGE_ADULT:
		{
		}
		break;
		case eREWARD_TYPE_GET_CONVERT_CLASS_RIGHT:
		{
		}
		break;
		case eREWARD_TYPE_EXP:
		{
		}
		break;
		case eREWARD_TYPE_SKILL:
		case eREWARD_TYPE_BUFF:
		{
		}
		break;
		case eREWARD_TYPE_ZENY:
		{
		}
		break;
	}
}
//Actions
void CGameQuestCtrl::SendActPortal(CDboTSActPortal* pActPortal)
{
	switch (pActPortal->GetPotalType())
	{
		case ePORTAL_TYPE_TELEPORT:
		{
			sVECTOR3 pos;
			sVECTOR3 dir;
			pActPortal->GetPosition(pos.x, pos.y, pos.z);
			pActPortal->GetDirection(dir.x, dir.y, dir.z);
		}
		break;
		case ePORTAL_TYPE_GATEWAY:
		{
			sVECTOR3 pos;
			sVECTOR3 dir;
			pActPortal->GetPosition(pos.x, pos.y, pos.z);
			pActPortal->GetDirection(dir.x, dir.y, dir.z);
		}
		break;
	}
}
void CGameQuestCtrl::SendActBroadMsg(CDboTSActBroadMsg* pActBroadMsg)
{
	printf("ActBroadMsg\n");
}
void CGameQuestCtrl::SendActConcCheck(CDboTSActConcCheck* pActConcCheck)
{
	printf("ActConcCheck\n");
}
void CGameQuestCtrl::SendActCustomEvt(CDboTSActCustomEvt* pActCustomEvt)
{
	printf("ActCustomEvt\n");
}
void CGameQuestCtrl::SendActDir(CDboTSActDir* pActDir)
{
	printf("ActDir\n");
}
void CGameQuestCtrl::SendActDirIndicator(CDboTSActDirIndicator* pActDirIndicator)
{
	printf("ActDirIndicator\n");
}
void CGameQuestCtrl::SendActDojo(CDboTSActDojo* pActDojo)
{
	printf("ActDojo\n");
}
void CGameQuestCtrl::SendActDoSkill(CDboTSActDoSkill* pActDoSkill)
{
	printf("ActDoSkill\n");
}
void CGameQuestCtrl::SendActDrop(CDboTSActDrop* pActDrop)
{
	printf("ActDrop\n");
}
void CGameQuestCtrl::SendActEscort(CDboTSActEscort* pActEscort)
{
	printf("ActEscort\n");
}
void CGameQuestCtrl::SendActETimerE(CDboTSActETimerE* pActETimerE)
{
	printf("ActETimerE\n");
}
void CGameQuestCtrl::SendActETimerS(CDboTSActETimerS* pActETimerS)
{
	printf("ActETimerS\n");
}
void CGameQuestCtrl::SendActExCGroup(CDboTSActExcCGroup* pActExCGroup)
{
	printf("ActExCGroup\n");
}
void CGameQuestCtrl::SendActHint(CDboTSActHint* pActHint)
{
	printf("ActHint\n");
}
void CGameQuestCtrl::SendActInSSM(CDboTSActInSSM* pActInSSM)
{
	printf("ActInSSm\n");
}
void CGameQuestCtrl::SendActItem(CDboTSActItem* pActItem)
{
	printf("ActItem\n");
}
void CGameQuestCtrl::SendActMiniNarration(CDboTSActMiniNarration* pActMiniNarration)
{
	printf("ActMiniNarration\n");
}
void CGameQuestCtrl::SendActNPCConv(CDboTSActNPCConv* pActNPCConv)
{
	printf("ActNPCConv\n");
}
void CGameQuestCtrl::SendActOutMsg(CDboTSActOutMsg* pActOutMsg)
{
	printf("ActOutMsg\n");
}
void CGameQuestCtrl::SendActObjConv(CDboTSActObjConv* pActObjConv)
{
	printf("ActObjConv\n");
}
void CGameQuestCtrl::SendActObjState(CDboTSActObjState* pActObjState)
{
	printf("ActObjState\n");
}
void CGameQuestCtrl::SendActObjWPS(CDboTSActObjWPS* pActObjWPS)
{
	printf("ActObjWPS\n");
}
void CGameQuestCtrl::SendActOPCam(CDboTSActOPCam* pActOPCam)
{
	printf("ActOPCam\n");
}
void CGameQuestCtrl::SendActOpenWindow(CDboTSActOpenWindow* pActOpenWindow)
{
	printf("ActOpenWindow\n");
}
void CGameQuestCtrl::SendActOPObject(CDboTSActOPObject* pActOPObject)
{
	printf("ActOPObject\n");
}
void CGameQuestCtrl::SendActPCConv(CDboTSActPCConv* pActPCConv)
{
	printf("ActPCConv\n");
}
void CGameQuestCtrl::SendActPIDgn(CDboTSActPIDgn* pActPIDgn)
{
	printf("ActPIDgn\n");
}
void CGameQuestCtrl::SendActQItem(CDboTSActQItem* pActQItem)
{
	printf("ActQItem\n");
}
void CGameQuestCtrl::SendActRegCTiming(CDboTSActRegCTiming* pActRegCTiming)
{
	printf("ActRegCTiming\n");
}
void CGameQuestCtrl::SendActRegQInfo(CDboTSActRegQInfo* pActRegQInfo)
{
	printf("ActRegQInfo\n");
}
void CGameQuestCtrl::SendActRmvCoupon(CDboTSActRmvCoupon* pActRmvCoupon)
{
	printf("ActRmvCoupon\n");
}
void CGameQuestCtrl::SendActSendSvrEvt(CDboTSActSendSvrEvt* pActSendSvrEvt, CNtlTSCont* pParent)
{
	printf("ActSendSvrEvt\n");
}
void CGameQuestCtrl::SendActSkipCont(CDboTSActSkipCont* pActSkipCont)
{
	printf("ActSkipCont\n");
}
void CGameQuestCtrl::SendActSToCEvt(CDboTSActSToCEvt* pActSToCEvt)
{
	printf("ActSToCEvt\n");
}
void CGameQuestCtrl::SendActSWProbSF(CDboTSActSWProbSF* pActSWProbSF)
{
	printf("ActSWProbSF\n");
}
/*
	WARNING: the code below is a extract from client-side, i commented that because i dont know if we gonna need follow
			 the same process as client, since we are server.
*/
////Containers
//void CGameQuestCtrl::CheckContCond(CDboTSContGCond* pCond, CNtlTSCont* pParent)
//{
//	printf("CONT_GCOND\n");	
//	CDboTSContGCond* pContGCond = pCond;
//	NTL_TS_T_ID tID = GetTrigger()->GetID();
//	NTL_TS_TG_ID tgID = ((CNtlTSGroup*)pContGCond->GetParent())->GetID();
//	NTL_TS_TG_ID tcID = pContGCond->GetID();
//
//	sSQRUN_PARAM sParam;
//	sParam.SetControl(this);
//	sParam.SetAgency(GetParent());
//
//	NTL_TSRESULT tsResult = GetTrigger()->RunTarget(tgID, tcID, GetParent()->GetRecv(), &sParam);
//	if (tsResult & NTL_TSRESULT_TYPE_ERROR)
//	{
//		CNtlTSLog::Log("Can not progress the quest container. Info[%d,%d]. [%s]", tID, tcID, TS_CODE_TRACE());
//	}
//
//	if (NTL_TSRESULT_TYPE_SUCCESS == tsResult)
//	{
//		CNtlTSCont* pNextCont = GetTrigger()->GetGroup(tgID)->GetChildCont(pContGCond->GetYesLinkID());
//		if (0 == pNextCont)
//		{
//			CNtlTSLog::Log("Must have the next container. Info[%d,%d,%d,%d]. [%s]", tID, tgID, tcID, pContGCond->GetYesLinkID(), TS_CODE_TRACE());
//		}
//	}
//	else if ((tsResult & NTL_TSRESULT_TYPE_COND_CAN_PROGRESS) || (tsResult & NTL_TSRESULT_TYPE_COND_CANT_PROGRESS))
//	{
//		CNtlTSCont* pNextCont = GetTrigger()->GetGroup(tgID)->GetChildCont(pContGCond->GetNoLinkID());
//		if (pNextCont)
//		{
//		}
//	}
//}
//void CGameQuestCtrl::CheckContStart(CDboTSContStart* pStart, CNtlTSCont* pParent)
//{
//	printf("CONT_START\n");
//	CDboTSContStart* pContStart = pStart;
//	NTL_TS_T_ID tID = GetTrigger()->GetID();
//	NTL_TS_TG_ID tgID = ((CNtlTSGroup*)pContStart->GetParent())->GetID();
//	NTL_TS_TG_ID tcID = pContStart->GetID();
//
//	sSQRUN_PARAM sParam;
//	sParam.SetControl(this);
//	sParam.SetAgency(GetParent());
//	sParam.SetQuestShare(IsQuestShareMode() ? true : false);
//
//	NTL_TSRESULT tsResult = GetTrigger()->RunTarget(tgID, tcID, GetParent()->GetRecv(), &sParam);
//	if (tsResult & NTL_TSRESULT_TYPE_ERROR)
//	{
//		CNtlTSLog::Log("Can not progress the quest container. Info[%d,%d,%d]. [%s]", tID, tgID, tcID, TS_CODE_TRACE());
//	}
//
//	if (NTL_TSRESULT_TYPE_SUCCESS == tsResult)
//	{
//		CNtlTSCont* pNextCont = GetTrigger()->GetGroup(tgID)->GetChildCont(pContStart->GetYesLinkID());
//		if (0 == pNextCont)
//		{
//			CNtlTSLog::Log("Must have the next container. Info[%d,%d,%d,%d]. [%s]", tID, tgID, tcID, pContStart->GetYesLinkID(), TS_CODE_TRACE());
//		}
//
//	}
//	else if ((tsResult & NTL_TSRESULT_TYPE_COND_CAN_PROGRESS) || (tsResult & NTL_TSRESULT_TYPE_COND_CANT_PROGRESS))
//	{
//		CNtlTSCont* pNextCont = GetTrigger()->GetGroup(tgID)->GetChildCont(pContStart->GetNoLinkID());
//
//		if (pNextCont)
//		{
//			
//		}
//		else
//		{
//			CNtlTSLog::Log("Must have the next container. Info[%d,%d,%d,%d]. [%s]", tID, tgID, tcID, pContStart->GetNoLinkID(), TS_CODE_TRACE());
//		}
//	}
//}
//void CGameQuestCtrl::CheckContAct(CDboTSContGAct* pAct, CNtlTSCont* pParent)
//{
//	printf("CONT_GACT\n");
//	CDboTSContGAct* pContGAct = pAct;
//	NTL_TS_T_ID tID = GetTrigger()->GetID();
//	NTL_TS_TG_ID tgID = ((CNtlTSGroup*)pContGAct->GetParent())->GetID();
//	NTL_TS_TG_ID tcID = pContGAct->GetID();
//
//	CNtlTSCont* pNextCont = GetTrigger()->GetGroup(tgID)->GetChildCont(pContGAct->GetNextLinkID());
//	if (0 == pNextCont)
//	{
//		CNtlTSLog::Log("Must have the next container. Info[%d,%d,%d,%d]. [%s]", tID, tgID, tcID, ((CDboTSContGAct*)m_pCurTSP)->GetNextLinkID(), TS_CODE_TRACE());
//	}
//
//}
//void CGameQuestCtrl::CheckContReward(CDboTSContReward* pReward, CNtlTSCont* pParent)
//{
//	printf("CONT_REWARD\n");
//	CDboTSContReward* pContRwd = pReward;
//	NTL_TS_T_ID tID = GetTrigger()->GetID();
//	NTL_TS_TG_ID tgID = ((CNtlTSGroup*)pContRwd->GetParent())->GetID();
//	NTL_TS_TG_ID tcID = pContRwd->GetID();
//
//	sSQRUN_PARAM sParam;
//	sParam.SetControl(this);
//	sParam.SetAgency(GetParent());
//
//	NTL_TSRESULT tsResult = GetTrigger()->RunTarget(tgID, tcID, GetParent()->GetRecv(), &sParam);
//	if (tsResult & NTL_TSRESULT_TYPE_ERROR)
//	{
//		CNtlTSLog::Log("Can not progress the quest container. Info[%d,%d,%d]. [%s]", tID, tgID, tcID, TS_CODE_TRACE());
//	}
//
//	if (NTL_TSRESULT_TYPE_SUCCESS == tsResult)
//	{
//		sTS_KEY sKey; sKey.Init();
//		sKey.tID = tID;
//		sKey.tgID = tgID;
//		sKey.tcID = tcID;		
//	}
//
//}
//void CGameQuestCtrl::CheckContEnd(CDboTSContEnd* pEnd, CNtlTSCont* pParent)
//{
//	printf("CONT_END\n");
//	CDboTSContEnd* pContEnd = pEnd;
//	NTL_TS_T_ID tID = GetTrigger()->GetID();
//	NTL_TS_TG_ID tgID = ((CNtlTSGroup*)pContEnd->GetParent())->GetID();
//	NTL_TS_TG_ID tcID = pContEnd->GetID();
//
//}
//void CGameQuestCtrl::CheckContUserSel(CDboTSContUsrSel* pUserSel, CNtlTSCont* pParent)
//{
//	printf("CONT_USERSEL\n");
//	CDboTSContUsrSel* pContUsr = pUserSel;
//	NTL_TS_T_ID tID = GetTrigger()->GetID();
//	NTL_TS_TG_ID tgID = ((CNtlTSGroup*)pContUsr->GetParent())->GetID();
//	NTL_TS_TG_ID tcID = pContUsr->GetID();
//
//	sTS_KEY sKey; sKey.Init();
//	sKey.tID = tID;
//	sKey.tgID = tgID;
//	sKey.tcID = tcID;
//}
//void CGameQuestCtrl::CheckContNarration(CDboTSContNarration* pNarration, CNtlTSCont* pParent)
//{
//	printf("CONT_NARRATION\n");
//	CDboTSContNarration* pContNarration = pNarration;
//
//	sTS_KEY sKey; sKey.Init();
//	sKey.tID = GetTrigger()->GetID();
//	sKey.tgID = ((CNtlTSGroup*)pContNarration->GetParent())->GetID();
//	sKey.tcID = pContNarration->GetID();
//}
//void CGameQuestCtrl::CheckContProposal(CDboTSContProposal* pProposal, CNtlTSCont* pParent)
//{
//	CDboTSContProposal* pContProposal = pProposal;
//
//	sTS_KEY sKey; sKey.Init();
//	sKey.tID = GetTrigger()->GetID();
//	sKey.tgID = ((CNtlTSGroup*)pContProposal->GetParent())->GetID();
//	sKey.tcID = pContProposal->GetID();
//
//	CNtlTSCont* pRwd = GetTrigger()->GetGroup(NTL_TS_MAIN_GROUP_ID)->GetChildCont(pContProposal->GetReward());
//
//	if (pRwd && pRwd->IsDerivedClass("CDboTSContReward"))
//	{
//		
//	}
//	else
//	{
//		
//	}
//}
//void CGameQuestCtrl::CheckContSwitch(CDboTSContSwitch* pSwitch, CNtlTSCont* pParent)
//{
//	printf("CONT_SWITCH\n");
//	CDboTSContSwitch* pContSwitch = pSwitch;
//	NTL_TS_TG_ID tcID = pContSwitch->GetID();
//
//}
//void CGameQuestCtrl::CheckContUnifiedNarration(CDboTSContUnifiedNarration* pUnifiedNarration, CNtlTSCont* pParent)
//{
//	printf("CONT_UNIFIED_NARRATION\n");
//	CDboTSContUnifiedNarration* pContNarration = pUnifiedNarration;
//
//	sTS_KEY sKey; sKey.Init();
//	sKey.tID = GetTrigger()->GetID();
//	sKey.tgID = ((CNtlTSGroup*)pContNarration->GetParent())->GetID();
//	sKey.tcID = pContNarration->GetID();
//}

//Events
void CGameQuestCtrl::SendEvtBindStone(CDboTSBindStone* pEvtBindStone)
{
}
void CGameQuestCtrl::SendEvtBudokai(CDboTSBudokai* pEvtBudokai)
{
}
void CGameQuestCtrl::SendEvtClickMob(CDboTSClickMob* pEvtClickMob)
{
}
void CGameQuestCtrl::SendEvtClickNPC(CDboTSClickNPC* pEvtClickNPC)
{
}
void CGameQuestCtrl::SendEvtClickObject(CDboTSClickObject* pEvtClickObject)
{
}
void CGameQuestCtrl::SendEvtColObject(CDboTSColObject* pEvtColObject)
{
}
void CGameQuestCtrl::SendEvtColRgn(CDboTSColRgn* pEvtColRgn)
{
}
void CGameQuestCtrl::SendEvtFreeBattle(CDboTSFreeBattle* pEvtFreeBattle)
{
}
void CGameQuestCtrl::SendEvtHoipoiMix(CDboTSHoipoiMix* pEvtHoipoiMix)
{
}
void CGameQuestCtrl::SendEvtItemEquip(CDboTSItemEquip* pEvtItemEquip)
{
}
void CGameQuestCtrl::SendEvtItemGet(CDboTSItemGet* pEvtItemGet)
{
}
void CGameQuestCtrl::SendEvtItemIdentity(CDboTSItemIdentity* pEvtItemIdentity)
{
}
void CGameQuestCtrl::SendEvtItemUpgrade(CDboTSItemUpgrade* pEvtItemUpgrade)
{
}
void CGameQuestCtrl::SendEvtItemUse(CDboTSItemUse* pEvtItemUse)
{
}
void CGameQuestCtrl::SendEvtParty(CDboTSParty* pEvtParty)
{
}
void CGameQuestCtrl::SendEvtPrivateShop(CDboTSPrivateShop* pEvtPrivateShop)
{
}
void CGameQuestCtrl::SendEvtRB(CDboTSRB* pEvtRB)
{
}
void CGameQuestCtrl::SendEvtRcvSvrEvt(CDboTSRcvSvrEvt* pEvtRcvSvrEvt)
{
}
void CGameQuestCtrl::SendEvtScoutUse(CDboTSScoutUse* pEvtScoutUse)
{
}
void CGameQuestCtrl::SendEvtSearchQuest(CDboTSSearchQuest* pEvtSearchQuest)
{
}
void CGameQuestCtrl::SendEvtSkillUse(CDboTSSkillUse* pEvtSkillUse)
{
}
void CGameQuestCtrl::SendEvtSlotMachine(CDboTSSlotMachine* pEvtSlotMachine)
{
}
void CGameQuestCtrl::SendEvtTeleport(CDboTSTeleport* pEvtTeleport)
{
}
void CGameQuestCtrl::SendEvtUseMail(CDboTSUseMail* pEvtUseMail)
{
}