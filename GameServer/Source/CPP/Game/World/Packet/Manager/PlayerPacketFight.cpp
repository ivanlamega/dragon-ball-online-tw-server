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
#include <XmlParser.h>

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
	sGU_CHAR_TARGET_CHANGED res;
	//sLog.outError("Target of target here ?");
	res.wOpCode = GU_CHAR_TARGET_CHANGED;
	res.wPacketSize = sizeof(sGU_CHAR_TARGET_CHANGED) - 2;

	_player->SetTarget(hTarget);
	res.hSubject = hTarget;
	SendPacket((char*)&res, sizeof(sGU_CHAR_TARGET_CHANGED));
}
//----------------------------------------
// Necesito eliminar toda esa mierda y remake
// Interpreta la habilidad actual que nuestro jugador quiere lanzar.
//----------------------------------------
void WorldSession::HandleUseSkill(Packet& packet)
{	
	_player->SetIsSkillCasting(true);	
	_player->SetIsFighting(false);
	sUG_CHAR_SKILL_REQ *pCharSkillReq = (sUG_CHAR_SKILL_REQ*)packet.GetPacketBuffer();
	
	sGU_CHAR_SKILL_RES sSkil;
	sSkil.wPacketSize = sizeof(sGU_CHAR_SKILL_RES) - 2;
	sSkil.wOpCode = GU_CHAR_SKILL_RES;		
	sSkil.wResultCode = GAME_SKILL_CANT_CAST_NOW;
	int DemageValue[40];
	int AttackType[40];
	int skillID = _player->skillManager.getIdAtPos(pCharSkillReq->bySlotIndex);
	SkillTable * skillTable = sTBM.GetSkillTable();		
	sSKILL_TBLDAT * skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(skillID));
	if (skillDataOriginal != NULL)
	{		
		_player->GetAttributesManager()->SetSkillSpeed(skillDataOriginal->fCasting_Time);
		int Demagecount = 0;
		for (int D = 0; D < skillDataOriginal->byApply_Target_Max; D++)
		{
			DemageValue[D] = 0;
			AttackType[D] = 0;
			Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(pCharSkillReq->ahApplyTarget[D]));
			if (MobInfo != NULL && MobInfo->GetIsDead() == false)
			{				
				int CriticRate = rand() % 100;
				//Demage Calculation
				if (skillDataOriginal->bySkill_Effect_Type[0] == 0)
				{
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastPhysicalOffence + skillDataOriginal->SkillValue[0];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_physical_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;						
					}
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastEnergyOffence + skillDataOriginal->SkillValue[0];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_energy_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;						
					}
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_STATE)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastEnergyOffence + skillDataOriginal->SkillValue[0];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_energy_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;
					}
				}
				if (skillDataOriginal->bySkill_Effect_Type[1] == 0)
				{
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastPhysicalOffence + skillDataOriginal->SkillValue[1];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_physical_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;
					}
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastEnergyOffence + skillDataOriginal->SkillValue[1];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_energy_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;
					}
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_STATE)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastEnergyOffence + skillDataOriginal->SkillValue[1];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_energy_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;
					}
				}
				//Next Type
				if (skillDataOriginal->bySkill_Effect_Type[0] == 1)
				{
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastPhysicalOffence / 100 * skillDataOriginal->SkillValue[0];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_physical_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;
					}
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastEnergyOffence / 100 * skillDataOriginal->SkillValue[0];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_energy_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;
					}
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_STATE)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastEnergyOffence / 100 * skillDataOriginal->SkillValue[0];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_energy_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;
					}
				}
				if (skillDataOriginal->bySkill_Effect_Type[1] == 1)
				{
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_PHYSICAL)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastPhysicalOffence / 100 * skillDataOriginal->SkillValue[1];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_physical_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;
					}
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_ENERGY)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastEnergyOffence / 100 * skillDataOriginal->SkillValue[1];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_energy_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;
					}
					if (skillDataOriginal->bySkill_Type == eSKILL_TYPE::SKILL_TYPE_STATE)
					{
						float attack = _player->GetPcProfile()->avatarAttribute.wLastEnergyOffence / 100 * skillDataOriginal->SkillValue[1];
						int TotalAttack = attack + MobInfo->GetMobData().Basic_energy_defence;
						float FinalPercent = attack * 100 / TotalAttack;
						DemageValue[Demagecount] = attack * FinalPercent / 100;
					}
				}
				if (CriticRate >= 0 && CriticRate <= 60)
				{
					AttackType[Demagecount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
				}
				if (CriticRate >= 61 && CriticRate <= 80)
				{
					AttackType[Demagecount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_CRITICAL_HIT;
					DemageValue[Demagecount] *= 2;
				}
				if (CriticRate >= 81 && CriticRate <= 100)
				{
					AttackType[Demagecount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
					DemageValue[Demagecount] = 0;
				}
				if (DemageValue[Demagecount] < 0 || DemageValue[Demagecount] > 1000000000)
				{
					DemageValue[Demagecount] = skillDataOriginal->SkillValue[0];
				}
				Demagecount += 1;
			}
		}
		sGU_CHAR_ACTION_SKILL skillRes;
		memset(&skillRes, 0, sizeof(sGU_CHAR_ACTION_SKILL));
		skillRes.wPacketSize = sizeof(sGU_CHAR_ACTION_SKILL) - 2;
		skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
		skillRes.wResultCode = GAME_SKILL_CANT_CAST_NOW;

		BuffTypeSkill pBuffData;
		memset(&pBuffData, 0, sizeof(BuffTypeSkill));
		pBuffData.OpCode = GU_BUFF_REGISTERED;
		pBuffData.size = sizeof(BuffTypeSkill) - 2;
		pBuffData.tblidx = INVALID_TBLIDX;		
		for (int Effect = 0; Effect <= 2; Effect++)
		{				
			int count = 0;
			sSYSTEM_EFFECT_TBLDAT * SystemEffectData = NULL;			
			SystemEffectData = (sSYSTEM_EFFECT_TBLDAT*)sTBM.GetSystemEffectTable()->FindData(skillDataOriginal->skill_Effect[Effect]);
						
			if (SystemEffectData != NULL)
			{
				printf("skill_Effect %d \n", skillDataOriginal->skill_Effect[Effect]);
				printf("effectCode %d \n", SystemEffectData->effectCode);
				printf("Effect %d \n", pCharSkillReq->byAvatarType);
				switch (SystemEffectData->effectCode)
				{
					case ACTIVE_DIRECT_DAMAGE:
					{	
						sSkil.wResultCode = GAME_SUCCESS; 

						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.handle = _player->GetHandle();
						skillRes.hAppointedTarget = pCharSkillReq->hTarget;
						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.dwLpEpEventId = skillDataOriginal->tblidx;						
						skillRes.byRpBonusType = pCharSkillReq->byRpBonusType;
						skillRes.bIsSkillHarmful = false;
					
						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{							
							Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(pCharSkillReq->ahApplyTarget[i]));
							if (MobInfo != NULL && MobInfo->GetIsDead() == false)
							{									

							skillRes.aSkillResult[count].hTarget = MobInfo->GetHandle();
							skillRes.aSkillResult[count].byAttackResult = AttackType[count];

							skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
							skillRes.aSkillResult[count].effectResult[Effect].Value1 = DemageValue[count];
							skillRes.aSkillResult[count].effectResult[Effect].Value2 = 1;//0
							skillRes.aSkillResult[count].effectResult[Effect].Value3 = 2;//0
							skillRes.aSkillResult[count].effectResult[Effect].Value4 = 3;//0
							skillRes.aSkillResult[count].effectResult[Effect].Value5 = 4;//0
							skillRes.aSkillResult[count].effectResult[Effect].Value6 = 5;//0
							skillRes.aSkillResult[count].byBlockedAction = 255;								
							skillRes.bySkillResultCount = count + 1;					
							

							if (MobInfo->attackers == 0)
								MobInfo->attackers = _player->GetHandle();
							MobInfo->TakeDamage(skillRes.aSkillResult[count].effectResult[Effect].Value1);
							count += 1;
							}							
						}						
						break;
					}
					case ACTIVE_BACKSTAB:
					{	
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.handle = _player->GetHandle();
						skillRes.hAppointedTarget = pCharSkillReq->hTarget;
						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.dwLpEpEventId = skillDataOriginal->tblidx;
						skillRes.byRpBonusType = pCharSkillReq->byRpBonusType;
						skillRes.bIsSkillHarmful = false;
						
						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{						
							Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(pCharSkillReq->ahApplyTarget[i]));
							if (MobInfo != NULL && MobInfo->GetIsDead() == false)
							{								

								skillRes.aSkillResult[count].hTarget = MobInfo->GetHandle();
								skillRes.aSkillResult[count].byAttackResult = AttackType[count];

								skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
								skillRes.aSkillResult[count].effectResult[Effect].Value1 = DemageValue[count];
								skillRes.aSkillResult[count].effectResult[Effect].Value2 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value3 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value4 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value5 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value6 = 0;
								skillRes.aSkillResult[count].byBlockedAction = 255;
								skillRes.bySkillResultCount = count + 1;

								if (MobInfo->attackers == 0)
									MobInfo->attackers = _player->GetHandle();
								MobInfo->TakeDamage(skillRes.aSkillResult[count].effectResult[Effect].Value1);
								count += 1;								
							}
						}
						break;
					}
					case ACTIVE_WARP_BACK_ATTACK:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.handle = _player->GetHandle();
						skillRes.hAppointedTarget = pCharSkillReq->hTarget;
						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.dwLpEpEventId = skillDataOriginal->tblidx;
						skillRes.byRpBonusType = pCharSkillReq->byRpBonusType;
						skillRes.bIsSkillHarmful = false;

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{							
							Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(pCharSkillReq->ahApplyTarget[i]));
							if (MobInfo != NULL && MobInfo->GetIsDead() == false)
							{
								skillRes.aSkillResult[count].hTarget = MobInfo->GetHandle();
								skillRes.aSkillResult[count].byAttackResult = AttackType[count];

								skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
								skillRes.aSkillResult[count].effectResult[Effect].Value1 = DemageValue[count];
								skillRes.aSkillResult[count].effectResult[Effect].Value2 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value3 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value4 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value5 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value6 = 0;
								skillRes.aSkillResult[count].byBlockedAction = 255;
								skillRes.bySkillResultCount = count + 1;

								if (MobInfo->attackers == 0)
									MobInfo->attackers = _player->GetHandle();
								MobInfo->TakeDamage(skillRes.aSkillResult[count].effectResult[Effect].Value1);
								count += 1;
							
							}
						}
						break;
					}					
					case ACTIVE_CRITICAL_ATTACK:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.handle = _player->GetHandle();
						skillRes.hAppointedTarget = pCharSkillReq->hTarget;
						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.dwLpEpEventId = skillDataOriginal->tblidx;
						skillRes.byRpBonusType = pCharSkillReq->byRpBonusType;
						skillRes.bIsSkillHarmful = false;
					
						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{						
							Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(pCharSkillReq->ahApplyTarget[i]));
							if (MobInfo != NULL && MobInfo->GetIsDead() == false)
							{
								skillRes.aSkillResult[count].hTarget = MobInfo->GetHandle();
								skillRes.aSkillResult[count].byAttackResult = AttackType[count];

								skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
								skillRes.aSkillResult[count].effectResult[Effect].Value1 = DemageValue[count];
								skillRes.aSkillResult[count].effectResult[Effect].Value2 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value3 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value4 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value5 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value6 = 0;
								skillRes.aSkillResult[count].byBlockedAction = 255;
								skillRes.bySkillResultCount = count + 1;


								if (MobInfo->attackers == 0)
									MobInfo->attackers = _player->GetHandle();
								MobInfo->TakeDamage(skillRes.aSkillResult[count].effectResult[Effect].Value1);
								count += 1;
								//printf("count %d \n", count);
							}
						}
						break;
					}	
					case ACTIVE_DIRECT_HEAL:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.handle = _player->GetHandle();
						skillRes.hAppointedTarget = pCharSkillReq->hTarget;
						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.dwLpEpEventId = skillDataOriginal->tblidx;
						skillRes.byRpBonusType = pCharSkillReq->byRpBonusType;
						skillRes.bIsSkillHarmful = false;
						
						skillRes.aSkillResult[count].hTarget = _player->GetHandle();
						skillRes.aSkillResult[count].byAttackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
						skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DH_HOT;
						skillRes.aSkillResult[count].effectResult[Effect].Value1 = 1000;
						skillRes.aSkillResult[count].effectResult[Effect].Value2 = 0;
						skillRes.aSkillResult[count].effectResult[Effect].Value3 = 0;
						skillRes.aSkillResult[count].effectResult[Effect].Value4 = 0;
						skillRes.aSkillResult[count].effectResult[Effect].Value5 = 0;
						skillRes.aSkillResult[count].effectResult[Effect].Value6 = 0;
						skillRes.aSkillResult[count].byBlockedAction = 255;
						skillRes.bySkillResultCount = count + 1;
						
						count += 1;
							
						
						break;
					}
					case ACTIVE_SUPER_SAIYAN:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();		
						_player->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_SUPER_SAIYAN;
						_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = false;
						_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = INVALID_TBLIDX;
						_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;
						_player->UpdateAspectState(eASPECTSTATE::ASPECTSTATE_SUPER_SAIYAN);
						break;
					}
					case ACTIVE_KAIOKEN:
					{
						if (_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount >= 102)
						{
							_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount = 0;
							_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.bySourceGrade = 0;
						}
						if (_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount >= 100 && _player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount <= 101)
						{
							//You Get Kaioken Limitacion
						}
						else
						{
							sSkil.wResultCode = GAME_SUCCESS;

							skillRes.skillId = skillDataOriginal->tblidx;
							skillRes.wResultCode = GAME_SUCCESS;
							skillRes.byRpBonusType = 0;//Untested
							skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
							skillRes.handle = _player->GetHandle();//My Handle
							skillRes.hAppointedTarget = _player->GetHandle();
							_player->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_KAIOKEN;
							_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount += 1;
							_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.bySourceGrade = 0;

							_player->UpdateAspectState(eASPECTSTATE::ASPECTSTATE_KAIOKEN);
							_player->GetAttributesManager()->SetLastPhysicalOffence(100);
							_player->GetAttributesManager()->SetLastEnergyOffence(100);
						}											
						break;
					}
					case ACTIVE_MAX_LP_UP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();

						
						pBuffData.hHandle = _player->GetHandle();
						pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

						_player->GetAttributesManager()->SetLastMaxLP(pBuffData.BuffInfo[Effect].SystemEffectValue);
						printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);
						
						break;
					}
					case ACTIVE_ENERGY_OFFENCE_UP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();						

						pBuffData.hHandle = _player->GetHandle();
						pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

						
						_player->GetAttributesManager()->SetLastEnergyOffence(pBuffData.BuffInfo[Effect].SystemEffectValue);
						break;
					}
					case ACTIVE_PHYSICAL_DEFENCE_UP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();

						
						pBuffData.hHandle = _player->GetHandle();
						pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];						

						_player->GetAttributesManager()->SetLastPhysicalDefence(pBuffData.BuffInfo[Effect].SystemEffectValue);
						printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);
						break;
					}
					case ACTIVE_ENERGY_DEFENCE_UP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();

						

						pBuffData.hHandle = _player->GetHandle();
						pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

						_player->GetAttributesManager()->SetLastEnergyDefence(pBuffData.BuffInfo[Effect].SystemEffectValue);
						break;
					}
					case ACTIVE_STR_UP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();

						pBuffData.hHandle = _player->GetHandle();
						pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

						_player->GetAttributesManager()->SetLastStr(pBuffData.BuffInfo[Effect].SystemEffectValue);
						break;
					}
					case ACTIVE_CON_UP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();					

						pBuffData.hHandle = _player->GetHandle();
						pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];				

						_player->GetAttributesManager()->SetLastCon(pBuffData.BuffInfo[Effect].SystemEffectValue);

						float LevelCon = pBuffData.BuffInfo[Effect].SystemEffectValue;
						float ConByPoint = 95; // 1con = 85 old tw
						float LP = static_cast<float>(LevelCon * ConByPoint);

						_player->GetAttributesManager()->SetLastMaxLP(LP);
						break;
					}
					case ACTIVE_FOC_UP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();

						pBuffData.hHandle = _player->GetHandle();
						pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

						_player->GetAttributesManager()->SetLastFoc(pBuffData.BuffInfo[Effect].SystemEffectValue);
						break;
					}
					case ACTIVE_DEX_UP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();


						pBuffData.hHandle = _player->GetHandle();
						pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

						_player->GetAttributesManager()->SetLastDex(pBuffData.BuffInfo[Effect].SystemEffectValue);
						break;
					}
					case ACTIVE_SOL_UP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();


						pBuffData.hHandle = _player->GetHandle();
						pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

						_player->GetAttributesManager()->SetLastSol(pBuffData.BuffInfo[Effect].SystemEffectValue);
						break;
					}
					case ACTIVE_ENG_UP:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();

					
						pBuffData.hHandle = _player->GetHandle();
						pBuffData.slot = 1;
						pBuffData.tblidx = skillDataOriginal->tblidx;
						pBuffData.bySourceType = 0;
						pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

						_player->GetAttributesManager()->SetLastEng(pBuffData.BuffInfo[Effect].SystemEffectValue);
						break;
					}
					case ACTIVE_LP_STEAL:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.handle = _player->GetHandle();
						skillRes.hAppointedTarget = pCharSkillReq->hTarget;
						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.dwLpEpEventId = skillDataOriginal->tblidx;
						skillRes.byRpBonusType = pCharSkillReq->byRpBonusType;
						skillRes.bIsSkillHarmful = false;
						
						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{							
							Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(pCharSkillReq->ahApplyTarget[i]));
							if (MobInfo != NULL && MobInfo->GetIsDead() == false)
							{
								skillRes.aSkillResult[count].hTarget = MobInfo->GetHandle();
								skillRes.aSkillResult[count].byAttackResult = AttackType[count];

								skillRes.aSkillResult[count].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_LP_EP_STEAL;
								skillRes.aSkillResult[count].effectResult[Effect].Value1 = DemageValue[count];
								skillRes.aSkillResult[count].effectResult[Effect].Value2 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value3 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value4 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value5 = 0;
								skillRes.aSkillResult[count].effectResult[Effect].Value6 = 0;
								skillRes.aSkillResult[count].byBlockedAction = 255;
								skillRes.bySkillResultCount = count + 1;


								if (MobInfo->attackers == 0)
									MobInfo->attackers = _player->GetHandle();
								MobInfo->TakeDamage(skillRes.aSkillResult[count].effectResult[Effect].Value1);
								count += 1;
								//printf("count %d \n", count);
							}
						}
						break;
					}
					case ACTIVE_PARALYZE:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
							printf("ahApplyTarget %d \n", pCharSkillReq->ahApplyTarget[i]); //

							Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(pCharSkillReq->ahApplyTarget[i]));
							if (MobInfo != NULL && MobInfo->GetIsDead() == false)
							{
								
								pBuffData.hHandle = MobInfo->GetHandle();
								pBuffData.slot = 1;
								pBuffData.tblidx = skillDataOriginal->tblidx;
								pBuffData.bySourceType = 0;
								pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
								pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

								pBuffData.isactive = 1;
								pBuffData.Type = 0;
								pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
								pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
								pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

								int FreePlace = 0;
								for (int i = 0; i <= 16; i++)
								{
									if (_player->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || _player->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
									{
										FreePlace = i;
									}

								}
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
								if (MobInfo->attackers == 0)
									MobInfo->attackers = _player->GetHandle();
								MobInfo->SetState(eCHARSTATE::CHARSTATE_PARALYZED);
								count += 1;
									printf("count %d \n", count);
							}
						}
						break;
					}
					case ACTIVE_STUN:
					{
						sSkil.wResultCode = GAME_SUCCESS;

						skillRes.skillId = skillDataOriginal->tblidx;
						skillRes.wResultCode = GAME_SUCCESS;
						skillRes.byRpBonusType = 0;//Untested
						skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
						skillRes.handle = _player->GetHandle();//My Handle
						skillRes.hAppointedTarget = _player->GetHandle();

						for (int i = 0; i < skillDataOriginal->byApply_Target_Max; i++)
						{
								printf("ahApplyTarget %d \n", pCharSkillReq->ahApplyTarget[i]);

							Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(pCharSkillReq->ahApplyTarget[i]));
							if (MobInfo != NULL && MobInfo->GetIsDead() == false)
							{
								
								pBuffData.hHandle = MobInfo->GetHandle();
								
								pBuffData.tblidx = skillDataOriginal->tblidx;
								pBuffData.bySourceType = 0;
								pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
								pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;;//Time

								pBuffData.isactive = 1;
								pBuffData.Type = 0;
								pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
								pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
								pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];

								int FreePlace = 0;
								for (int i = 0; i <= 16; i++)
								{
									if (_player->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || _player->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
									{
										FreePlace = i;
									}

								}
								pBuffData.slot = FreePlace;
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
								_player->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;

								if (MobInfo->attackers == 0)
									MobInfo->attackers = _player->GetHandle();
								MobInfo->SetState(eCHARSTATE::CHARSTATE_STUNNED);
								count += 1;
								printf("count %d \n", count);
							}
						}
						break;
					}
					//NEXT CASE
				}
			}
		}		
			SendPacket((char*)&sSkil, sizeof(sGU_CHAR_SKILL_RES));
			SendPacket((char*)&skillRes, sizeof(sGU_CHAR_ACTION_SKILL));
			_player->SendToPlayerList((char*)&skillRes, sizeof(sGU_CHAR_ACTION_SKILL));		
			SendPacket((char*)&pBuffData, sizeof(BuffTypeSkill));
			_player->SendToPlayerList((char*)&pBuffData, sizeof(BuffTypeSkill));						
		}
		else
		{
			sSkil.wResultCode = GAME_SKILL_CANT_CAST_NOW;
			SendPacket((char*)&sSkil, sizeof(sGU_CHAR_SKILL_RES));
		}
	
	_player->SetIsSkillCasting(false);
}