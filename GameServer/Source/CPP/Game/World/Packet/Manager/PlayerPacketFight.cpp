#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Game\Object\Player.h>
#include <Game\Object\Mob.h>
#include <Game\Object\NPC.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser2/XmlParser2.h>

//----------------------------------------
//	Handle Fight
//----------------------------------------
void WorldSession::SendToggleAutoAttack(bool val)
{
	sGU_CHAR_FIGHTMODE res;

	res.wOpCode = GU_CHAR_FIGHTMODE;
	res.wPacketSize = sizeof(sGU_CHAR_FIGHTMODE) - 2;
	_player->SetIsFighting(val);
	res.bFightMode = val;
	res.handle = _player->GetHandle();
	SendPacket((char*)&res, sizeof(sGU_CHAR_FIGHTMODE));
	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_FIGHTMODE));
}
//----------------------------------------
//	Change our player's target
//----------------------------------------
void WorldSession::SendTargetSelection(HOBJECT hTarget)
{
	Player* PlayerInfo = static_cast<Player*>(_player->GetFromList(hTarget));
	if (PlayerInfo != NULL)
	{
		sGU_CHAR_TARGET_CHANGED res;
		//sLog.outError("Target of target here ?");
		res.wOpCode = GU_CHAR_TARGET_CHANGED;
		res.wPacketSize = sizeof(sGU_CHAR_TARGET_CHANGED) - 2;

		_player->SetTarget(hTarget);
		res.hSubject = hTarget;
		try //temporal
		{
			res.unknow = PlayerInfo->GetTarget();
		}
		catch (int e)
		{
			sLog.outError("Error n: %d", e);
			res.unknow = INVALID_TBLIDX;
		}
		
		SendPacket((char*)&res, sizeof(sGU_CHAR_TARGET_CHANGED));
	}	
	Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(hTarget));
	if (MobInfo != NULL)
	{
		sGU_CHAR_TARGET_CHANGED res;
		//sLog.outError("Target of target here ?");
		res.wOpCode = GU_CHAR_TARGET_CHANGED;
		res.wPacketSize = sizeof(sGU_CHAR_TARGET_CHANGED) - 2;

		_player->SetTarget(hTarget);
		res.hSubject = hTarget;
		res.unknow = MobInfo->GetMobData().target;
		SendPacket((char*)&res, sizeof(sGU_CHAR_TARGET_CHANGED));
	}
	Npc* NpcInfo = static_cast<Npc*>(_player->GetFromList(hTarget));
	if (NpcInfo != NULL)
	{
		sGU_CHAR_TARGET_CHANGED res;
		//sLog.outError("Target of target here ?");
		res.wOpCode = GU_CHAR_TARGET_CHANGED;
		res.wPacketSize = sizeof(sGU_CHAR_TARGET_CHANGED) - 2;

		_player->SetTarget(hTarget);
		res.hSubject = hTarget;
		res.unknow = NpcInfo->GetNpcData().target;
		SendPacket((char*)&res, sizeof(sGU_CHAR_TARGET_CHANGED));
	}
}
//----------------------------------------
//Need Delet all that Shit and Remake
//	Interpret the current skill our player want to cast
//----------------------------------------

void WorldSession::UseSkill(Packet& packet)
{
	
	_player->SetIsFighting(false);
	
	sUG_CHAR_SKILL_REQ *pCharSkillReq = (sUG_CHAR_SKILL_REQ*)packet.GetPacketBuffer();	

	int skillID = _player->skillManager.getIdAtPos(pCharSkillReq->bySlotIndex);
	SkillTable * skillTable = sTBM.GetSkillTable();
	sSKILL_TBLDAT * skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(skillID));
	if (skillDataOriginal != NULL)
	{
			_player->packets = packet;
			_player->GetAtributesCalculation(pCharSkillReq->ahApplyTarget, pCharSkillReq->byApplyTargetCount, skillDataOriginal->bySkill_Type, skillDataOriginal->bySkill_Effect_Type, skillDataOriginal->SkillValue, pCharSkillReq->byRpBonusType);
			if (skillDataOriginal->dwCastingTimeInMilliSecs > 0)
			{
				sGU_UPDATE_CHAR_STATE state;

				state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
				state.wOpCode = GU_UPDATE_CHAR_STATE;

				state.handle = _player->GetHandle();
				state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_CASTING;
				_player->GetState()->sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_CASTING;
				state.sCharState.sCharStateDetail.sCharStateCasting.hTarget = _player->GetHandle();
				state.sCharState.sCharStateDetail.sCharStateCasting.skillId = skillDataOriginal->tblidx;
				state.sCharState.sCharStateDetail.sCharStateCasting.dwCastingTime = skillDataOriginal->dwCastingTimeInMilliSecs;
				state.sCharState.sCharStateDetail.sCharStateCasting.dwCastingTimeRemaining = skillDataOriginal->dwCastingTimeInMilliSecs;

				state.sCharState.sCharStateBase.vCurLoc.x = _player->GetVectorPosition().x;
				state.sCharState.sCharStateBase.vCurLoc.y = _player->GetVectorPosition().y;
				state.sCharState.sCharStateBase.vCurLoc.z = _player->GetVectorPosition().z;
				state.sCharState.sCharStateBase.vCurDir.x = _player->GetVectorOriantation().x;
				state.sCharState.sCharStateBase.vCurDir.y = _player->GetVectorOriantation().y;
				state.sCharState.sCharStateBase.vCurDir.z = _player->GetVectorOriantation().x;
				state.sCharState.sCharStateBase.dwConditionFlag = _player->GetState()->sCharStateBase.dwConditionFlag;
				state.sCharState.sCharStateBase.isFlying = false;
				state.sCharState.sCharStateBase.isFighting = false;
				state.sCharState.sCharStateBase.dwStateTime = 0x01;

				_player->SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
				_player->SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
			}			

			_player->SkillCastinTime = GetTickCount();
			_player->SkillCastinTimeRemain = skillDataOriginal->dwCastingTimeInMilliSecs;
			_player->SetIsFighting(false);
			_player->SetIsSkillCasting(true);			
	}
}
