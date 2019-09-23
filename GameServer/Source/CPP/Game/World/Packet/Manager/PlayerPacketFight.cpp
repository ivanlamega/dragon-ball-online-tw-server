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
	int HealValue[40];
	int AttackType[40];
	int skillID = _player->skillManager.getIdAtPos(pCharSkillReq->bySlotIndex);
	SkillTable * skillTable = sTBM.GetSkillTable();
	sSKILL_TBLDAT * skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(skillID));
	if (skillDataOriginal != NULL)
	{
		_player->GetAttributesManager()->SetSkillSpeed(skillDataOriginal->fCasting_Time);
		int Demagecount = 0;
		int HealCount = 0;
		for (int D = 0; D < skillDataOriginal->byApply_Target_Max; D++)
		{
			DemageValue[D] = 0;
			HealValue[D] = 0;
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
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DD)
					{
						float damage = skillDataOriginal->SkillValue[0];
						DemageValue[Demagecount] = damage;
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DOT)
					{
						for (int i = 0; i < skillDataOriginal->wKeep_Time; i++) {
							float damage = skillDataOriginal->SkillValue[0];
							DemageValue[Demagecount] = damage;
						}
					}
					/*	if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DH)
					{
					float heal = skillDataOriginal->SkillValue[0];
					HealValue[HealCount] = heal;
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_HOT)
					{
					for (int i = 0; i < skillDataOriginal->wKeep_Time; i++) {
					float heal = skillDataOriginal->SkillValue[0];
					HealValue[HealCount] = heal;
					}
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DB)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_BB)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DC)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_CB)
					{

					}*/
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
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DD)
					{
						float damage = skillDataOriginal->SkillValue[1];
						DemageValue[Demagecount] = damage;
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DOT)
					{
						for (int i = 0; i < skillDataOriginal->wKeep_Time; i++) {
							float damage = skillDataOriginal->SkillValue[1];
							DemageValue[Demagecount] = damage;
						}
					}
					/*	if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DH)
					{
					float heal = skillDataOriginal->SkillValue[1];
					HealValue[HealCount] = heal;
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_HOT)
					{
					for (int i = 0; i < skillDataOriginal->wKeep_Time; i++) {
					float heal = skillDataOriginal->SkillValue[1];
					HealValue[HealCount] = heal;
					}
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DB)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_BB)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DC)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_CB)
					{

					}*/
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
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DD)
					{
						float damage = skillDataOriginal->SkillValue[0];
						DemageValue[Demagecount] = damage;
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DOT)
					{
						for (int i = 0; i < skillDataOriginal->wKeep_Time; i++) {
							float damage = skillDataOriginal->SkillValue[0];
							DemageValue[Demagecount] = damage;
						}
					}
					/*	if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DH)
					{
					float heal = skillDataOriginal->SkillValue[0];
					HealValue[HealCount] = heal;
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_HOT)
					{
					for (int i = 0; i < skillDataOriginal->wKeep_Time; i++) {
					float heal = skillDataOriginal->SkillValue[0];
					HealValue[HealCount] = heal;
					}
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DB)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_BB)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DC)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_CB)
					{

					}*/
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
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DD)
					{
						float damage = skillDataOriginal->SkillValue[1];
						DemageValue[Demagecount] = damage;
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DOT)
					{
						for (int i = 0; i < skillDataOriginal->wKeep_Time; i++) {
							float damage = skillDataOriginal->SkillValue[1];
							DemageValue[Demagecount] = damage;
						}
					}
					/*if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DH)
					{
					float heal = skillDataOriginal->SkillValue[1];
					HealValue[HealCount] = heal;
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_HOT)
					{
					for (int i = 0; i < skillDataOriginal->wKeep_Time; i++) {
					float heal = skillDataOriginal->SkillValue[1];
					HealValue[HealCount] = heal;
					}
					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DB)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_BB)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DC)
					{

					}
					if (skillDataOriginal->bySkill_Active_Type == eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_CB)
					{

					}*/
				}
				if (CriticRate >= 0 && CriticRate <= 60)
				{
					AttackType[Demagecount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
					DemageValue[Demagecount] *= 20;
				}
				if (CriticRate >= 61 && CriticRate <= 80)
				{
					AttackType[Demagecount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_CRITICAL_HIT;
					DemageValue[Demagecount] *= 40;
				}
				if (CriticRate >= 81 && CriticRate <= 100)
				{
					AttackType[Demagecount] = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
					DemageValue[Demagecount] = 0;
				}
				if (DemageValue[Demagecount] < 500 || DemageValue[Demagecount] > 9000000000)
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
				case ACTIVE_ENERGY_DEFENCE_DOWN:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[0].hTarget = _player->GetHandle();
					skillRes.aSkillResult[0].byAttackResult = 0;
					skillRes.aSkillResult[0].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[0].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[0].byBlockedAction = 0;
					skillRes.aSkillResult[0].unk1 = 0;
					skillRes.aSkillResult[0].vShift.x = 0;
					skillRes.aSkillResult[0].vShift.y = 0;
					skillRes.aSkillResult[0].vShift.z = 0;
					skillRes.aSkillResult[0].vShift1 = _player->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = _player->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetAttributesManager()->SetLastEnergyDefence(pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect]);
					printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);

					break;
				}
				case ACTIVE_MOVE_SPEED_UP:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[0].hTarget = _player->GetHandle();
					skillRes.aSkillResult[0].byAttackResult = 0;
					skillRes.aSkillResult[0].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[0].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[0].byBlockedAction = 0;
					skillRes.aSkillResult[0].unk1 = 0;
					skillRes.aSkillResult[0].vShift.x = 0;
					skillRes.aSkillResult[0].vShift.y = 0;
					skillRes.aSkillResult[0].vShift.z = 0;
					skillRes.aSkillResult[0].vShift1 = _player->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = _player->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetAttributesManager()->SetLastRunSpeed(((pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect]) / 100) * _player->GetPcProfile()->avatarAttribute.fBaseRunSpeed);
					printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);

					break;
				}
				case ACTIVE_PHYSICAL_CRITICAL_DAMAGE_UP:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[0].hTarget = _player->GetHandle();
					skillRes.aSkillResult[0].byAttackResult = 0;
					skillRes.aSkillResult[0].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[0].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[0].byBlockedAction = 0;
					skillRes.aSkillResult[0].unk1 = 0;
					skillRes.aSkillResult[0].vShift.x = 0;
					skillRes.aSkillResult[0].vShift.y = 0;
					skillRes.aSkillResult[0].vShift.z = 0;
					skillRes.aSkillResult[0].vShift1 = _player->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = _player->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetAttributesManager()->SetPhysicalCriticalDamageBonusRate(pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect]);
					printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);
					break;
				}
				case ACTIVE_PHYSICAL_CRITICAL:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[0].hTarget = _player->GetHandle();
					skillRes.aSkillResult[0].byAttackResult = 0;
					skillRes.aSkillResult[0].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[0].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[0].byBlockedAction = 0;
					skillRes.aSkillResult[0].unk1 = 0;
					skillRes.aSkillResult[0].vShift.x = 0;
					skillRes.aSkillResult[0].vShift.y = 0;
					skillRes.aSkillResult[0].vShift.z = 0;
					skillRes.aSkillResult[0].vShift1 = _player->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = _player->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetAttributesManager()->SetLastPhysicalCriticalRate(pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect]);
					printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);

					break;
				}
				case ACTIVE_SKILL_COOL_TIME_DOWN:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[0].hTarget = _player->GetHandle();
					skillRes.aSkillResult[0].byAttackResult = 0;
					skillRes.aSkillResult[0].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[0].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[0].byBlockedAction = 0;
					skillRes.aSkillResult[0].unk1 = 0;
					skillRes.aSkillResult[0].vShift.x = 0;
					skillRes.aSkillResult[0].vShift.y = 0;
					skillRes.aSkillResult[0].vShift.z = 0;
					skillRes.aSkillResult[0].vShift1 = _player->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = _player->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetAttributesManager()->SetCoolTimeChangePercent(pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect]);
					printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);

					break;
				}
				case ACTIVE_ATTACK_RATE_UP:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[0].hTarget = _player->GetHandle();
					skillRes.aSkillResult[0].byAttackResult = 0;
					skillRes.aSkillResult[0].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[0].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[0].byBlockedAction = 0;
					skillRes.aSkillResult[0].unk1 = 0;
					skillRes.aSkillResult[0].vShift.x = 0;
					skillRes.aSkillResult[0].vShift.y = 0;
					skillRes.aSkillResult[0].vShift.z = 0;
					skillRes.aSkillResult[0].vShift1 = _player->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = _player->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetAttributesManager()->SetLastAttackRate(pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect]);
					printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);

					break;
				}
				case ACTIVE_ATTACK_RATE_DOWN:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[0].hTarget = _player->GetHandle();
					skillRes.aSkillResult[0].byAttackResult = 0;
					skillRes.aSkillResult[0].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[0].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[0].byBlockedAction = 0;
					skillRes.aSkillResult[0].unk1 = 0;
					skillRes.aSkillResult[0].vShift.x = 0;
					skillRes.aSkillResult[0].vShift.y = 0;
					skillRes.aSkillResult[0].vShift.z = 0;
					skillRes.aSkillResult[0].vShift1 = _player->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = _player->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetAttributesManager()->SetLastAttackRate(pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect]);
					printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);

					break;
				}
				case ACTIVE_MAX_LP_UP:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[0].hTarget = _player->GetHandle();
					skillRes.aSkillResult[0].byAttackResult = 0;
					skillRes.aSkillResult[0].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[0].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[0].byBlockedAction = 0xFF;
					skillRes.aSkillResult[0].unk1 = 0;
					skillRes.aSkillResult[0].vShift.x = 0.0f;
					skillRes.aSkillResult[0].vShift.y = 0.0f;
					skillRes.aSkillResult[0].vShift.z = 0.0f;
					skillRes.aSkillResult[0].vShift1.x = _player->GetVectorPosition().x;
					skillRes.aSkillResult[0].vShift1.y = _player->GetVectorPosition().y;
					skillRes.aSkillResult[0].vShift1.z = _player->GetVectorPosition().z;

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = _player->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillRes.skillId;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
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
				case ACTIVE_SUPER_SAIYAN:
				{
					WORD OriginalMaxEP = _player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.wLastMaxEP;
					WORD OriginalAttackSPDRate = _player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.wLastAttackSpeedRate;
					float OriginalRunSpeed = _player->GetAttributesManager()->GetPlayerProfile()->avatarAttribute.fBaseRunSpeed;

					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.byRpBonusType = 0;//Untested
					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();//My Handle
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = _player->GetHandle();
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = (float)skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0;
					skillRes.aSkillResult[Effect].vShift.y = 0;
					skillRes.aSkillResult[Effect].vShift.z = 0;
					skillRes.aSkillResult[Effect].vShift1 = _player->GetVectorPosition();

					_player->GetAttributesManager()->sBuffTimeInfo[Effect].BuffID = pBuffData.tblidx = skillRes.skillId;
					pBuffData.isactive = true;
					_player->GetAttributesManager()->sBuffTimeInfo[Effect].BuffIsActive = pBuffData.isactive;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_SUPER_SAIYAN;
					_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = false;
					_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = INVALID_TBLIDX;
					_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;
					_player->UpdateAspectState(eASPECTSTATE::ASPECTSTATE_SUPER_SAIYAN);

					_player->GetAttributesManager()->SetLastMaxEP(pBuffData.BuffInfo[Effect].SystemEffectValue);
					_player->GetAttributesManager()->SetLastAttackSpeedRate(pBuffData.BuffInfo[Effect].SystemEffectValue);
					_player->GetAttributesManager()->SetLastRunSpeed(((pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect]) / 1600) * _player->GetPcProfile()->avatarAttribute.fBaseRunSpeed);
					printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);


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
						skillRes.bIsSkillHarmful = 0;
						skillRes.bySkillResultCount = 1;
						skillRes.aSkillResult[Effect].hTarget = _player->GetHandle();
						skillRes.aSkillResult[Effect].byAttackResult = 0;
						skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = 0xFF;
						skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
						skillRes.aSkillResult[Effect].byBlockedAction = 0;
						skillRes.aSkillResult[Effect].unk1 = 0;
						skillRes.aSkillResult[Effect].vShift.x = 0;
						skillRes.aSkillResult[Effect].vShift.y = 0;
						skillRes.aSkillResult[Effect].vShift.z = 0;
						skillRes.aSkillResult[Effect].vShift1 = _player->GetVectorPosition();

						pBuffData.tblidx = skillRes.skillId;
						pBuffData.isactive = 1;
						pBuffData.Type = 0;
						pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
						pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
						pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

						_player->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_KAIOKEN;
						_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.byRepeatingCount += 1;
						_player->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.bySourceGrade = 0;

						_player->UpdateAspectState(eASPECTSTATE::ASPECTSTATE_KAIOKEN);
						_player->GetAttributesManager()->SetLastPhysicalOffence(pBuffData.BuffInfo[Effect].SystemEffectValue / 15);
						_player->GetAttributesManager()->SetLastEnergyOffence(pBuffData.BuffInfo[Effect].SystemEffectValue / 15);
					}
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
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = _player->GetHandle();
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0;
					skillRes.aSkillResult[Effect].vShift.y = 0;
					skillRes.aSkillResult[Effect].vShift.z = 0;
					skillRes.aSkillResult[Effect].vShift1 = _player->GetVectorPosition();

					pBuffData.tblidx = skillRes.skillId;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;


					_player->GetAttributesManager()->SetLastEnergyOffence(pBuffData.BuffInfo[Effect].SystemEffectValue);
					break;
				}
				case ACTIVE_PHYSICAL_OFFENCE_UP:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.byRpBonusType = 0;//Untested
					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();//My Handle
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = _player->GetHandle();
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0;
					skillRes.aSkillResult[Effect].vShift.y = 0;
					skillRes.aSkillResult[Effect].vShift.z = 0;
					skillRes.aSkillResult[Effect].vShift1 = _player->GetVectorPosition();

					pBuffData.tblidx = skillRes.skillId;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetAttributesManager()->SetLastPhysicalOffence(pBuffData.BuffInfo[Effect].SystemEffectValue = skillDataOriginal->SkillValue[Effect]);
					printf("SystemEffectValue %f \n", pBuffData.BuffInfo[Effect].SystemEffectValue);

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
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = _player->GetHandle();
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0;
					skillRes.aSkillResult[Effect].vShift.y = 0;
					skillRes.aSkillResult[Effect].vShift.z = 0;
					skillRes.aSkillResult[Effect].vShift1 = _player->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.tblidx = skillRes.skillId;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

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
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = _player->GetHandle();
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0;
					skillRes.aSkillResult[Effect].vShift.y = 0;
					skillRes.aSkillResult[Effect].vShift.z = 0;
					skillRes.aSkillResult[Effect].vShift1 = _player->GetVectorPosition();

					pBuffData.tblidx = skillRes.skillId;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

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
				case ACTIVE_LP_REGENERATION:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.byRpBonusType = 0;//Untested
					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();//My Handle
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = _player->GetHandle();
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0;
					skillRes.aSkillResult[Effect].vShift.y = 0;
					skillRes.aSkillResult[Effect].vShift.z = 0;
					skillRes.aSkillResult[Effect].vShift1 = _player->GetVectorPosition();

					pBuffData.tblidx = skillRes.skillId;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetAttributesManager()->SetLastLPRegen(pBuffData.BuffInfo[Effect].SystemEffectValue);
					break;
				}
				case ACTIVE_KNOCKDOWN_ATTACK_BLOCK_UP:
				{
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.wResultCode = GAME_SUCCESS;
					skillRes.byRpBonusType = 0;//Untested
					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();//My Handle
					skillRes.hAppointedTarget = _player->GetHandle();
					skillRes.bIsSkillHarmful = 0;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = _player->GetHandle();
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = 0xFF;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0;
					skillRes.aSkillResult[Effect].vShift.y = 0;
					skillRes.aSkillResult[Effect].vShift.z = 0;
					skillRes.aSkillResult[Effect].vShift1 = _player->GetVectorPosition();

					pBuffData.tblidx = skillRes.skillId;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					_player->GetAttributesManager()->SetKnockdownBlockModeSuccessRate(pBuffData.BuffInfo[Effect].SystemEffectValue);

					break;
				}
				case ACTIVE_STOMACHACHE:
				{
					Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(_player->GetTarget()));
					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = MobInfo->GetHandle();
					skillRes.bIsSkillHarmful = 1;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = MobInfo->GetHandle();
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value2 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value3 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value4 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value5 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value6 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0xFF;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0.0f;
					skillRes.aSkillResult[Effect].vShift.y = 0.0f;
					skillRes.aSkillResult[Effect].vShift.z = 0.0f;
					skillRes.aSkillResult[Effect].vShift1 = MobInfo->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = MobInfo->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;


					break;
				}
				case ACTIVE_BLEED:
				{
					Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(_player->GetTarget()));

					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = MobInfo->GetHandle();
					skillRes.bIsSkillHarmful = 1;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = skillRes.hAppointedTarget;
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value2 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value3 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value4 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value5 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value6 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0xFF;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0.0f;
					skillRes.aSkillResult[Effect].vShift.y = 0.0f;
					skillRes.aSkillResult[Effect].vShift.z = 0.0f;
					skillRes.aSkillResult[Effect].vShift1 = MobInfo->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = MobInfo->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					MobInfo->TakeDamage(pBuffData.BuffInfo[Effect].SystemEffectValue);

					break;
				}
				case ACTIVE_BURN:
				{
					Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(_player->GetTarget()));

					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = MobInfo->GetHandle();
					skillRes.bIsSkillHarmful = 1;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = skillRes.hAppointedTarget;
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value2 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value3 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value4 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value5 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value6 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0xFF;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0.0f;
					skillRes.aSkillResult[Effect].vShift.y = 0.0f;
					skillRes.aSkillResult[Effect].vShift.z = 0.0f;
					skillRes.aSkillResult[Effect].vShift1 = MobInfo->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = MobInfo->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					MobInfo->TakeDamage(pBuffData.BuffInfo[Effect].SystemEffectValue);

					break;
				}
				case ACTIVE_POISON:
				{
					Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(_player->GetTarget()));

					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = MobInfo->GetHandle();
					skillRes.bIsSkillHarmful = 1;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = skillRes.hAppointedTarget;
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value2 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value3 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value4 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value5 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value6 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0xFF;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0.0f;
					skillRes.aSkillResult[Effect].vShift.y = 0.0f;
					skillRes.aSkillResult[Effect].vShift.z = 0.0f;
					skillRes.aSkillResult[Effect].vShift1 = MobInfo->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = MobInfo->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					MobInfo->TakeDamage(pBuffData.BuffInfo[Effect].SystemEffectValue);

					break;
				}
				case ACTIVE_PHYSICAL_OFFENCE_DOWN:
				{
					Mob* MobInfo = static_cast<Mob*>(_player->GetFromList(_player->GetTarget()));

					sSkil.wResultCode = GAME_SUCCESS;

					skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
					skillRes.handle = _player->GetHandle();
					skillRes.dwLpEpEventId = 0xFFFFFFFF;
					skillRes.skillId = skillDataOriginal->tblidx;
					skillRes.byRpBonusType = 0xFF;
					skillRes.hAppointedTarget = MobInfo->GetHandle();
					skillRes.bIsSkillHarmful = 1;
					skillRes.bySkillResultCount = 1;
					skillRes.aSkillResult[Effect].hTarget = skillRes.hAppointedTarget;
					skillRes.aSkillResult[Effect].byAttackResult = 0;
					skillRes.aSkillResult[Effect].effectResult[Effect].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_GENERAL;
					skillRes.aSkillResult[Effect].effectResult[Effect].Value1 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value2 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value3 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value4 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value5 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].effectResult[Effect].Value6 = skillDataOriginal->SkillValue[Effect];
					skillRes.aSkillResult[Effect].byBlockedAction = 0xFF;
					skillRes.aSkillResult[Effect].unk1 = 0;
					skillRes.aSkillResult[Effect].vShift.x = 0.0f;
					skillRes.aSkillResult[Effect].vShift.y = 0.0f;
					skillRes.aSkillResult[Effect].vShift.z = 0.0f;
					skillRes.aSkillResult[Effect].vShift1 = MobInfo->GetVectorPosition();

					pBuffData.OpCode = GU_BUFF_REGISTERED;
					pBuffData.hHandle = MobInfo->GetHandle();
					pBuffData.slot = skillDataOriginal->bySlot_Index;
					pBuffData.tblidx = skillDataOriginal->tblidx;
					pBuffData.bySourceType = 0;
					pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs - 1;
					pBuffData.isactive = 1;
					pBuffData.Type = 0;
					pBuffData.BuffInfo[Effect].SystemEffectValue = (float)skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
					pBuffData.BuffInfo[Effect].dwSystemEffectValue = skillDataOriginal->SkillValue[Effect];
					pBuffData.BuffInfo[Effect].NeedDisplayMensage = true;

					break;
				}
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
//--------------------------------------------------
//  Buff Dropping function
//--------------------------------------------------
void WorldSession::BuffDrop(Packet& packet)
{

	sUG_BUFF_DROP_REQ *pBuffDropReq = (sUG_BUFF_DROP_REQ*)packet.GetPacketBuffer();

	TBLIDX skillID = _player->skillManager.getBuffInfos()->SourceTblidx;
	SkillTable * skillTable = sTBM.GetSkillTable();
	sSKILL_TBLDAT * skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(skillID));

	sGU_CHAR_ACTION_SKILL skillRes;

	sGU_BUFF_DROPPED buffDropped;

	BuffTypeSkill pBuffData;

	/*	pBuffDropReq->wOpCode = UG_BUFF_DROP_REQ;
	pBuffDropReq->bySourceType = 0;
	pBuffDropReq->byUnknown1 = 0;
	pBuffDropReq->tblidx = skillDataOriginal->tblidx;*/
	for (int i = 0; i < 16; i++)
	{
		buffDropped.wPacketSize = (sizeof(sGU_BUFF_DROPPED)) - 2;
		buffDropped.wOpCode = GU_BUFF_DROPPED;
		buffDropped.hHandle = _player->GetAttributesManager()->sBuffTimeInfo[i].PlayerHandle;
		buffDropped.bySourceType = DBO_OBJECT_SOURCE_SKILL;
		//buffDropped.unk = 0;
		buffDropped.tblidx = _player->GetAttributesManager()->sBuffTimeInfo[i].BuffID;
		buffDropped.unk1 = 0;
		SendPacket((char*)&buffDropped, sizeof(sGU_BUFF_DROPPED));
		_player->SendToPlayerList((char*)&buffDropped, sizeof(sGU_BUFF_DROPPED));
		_player->GetAttributesManager()->sBuffTimeInfo[i].BuffIsActive = false;
		_player->GetAttributesManager()->sBuffTimeInfo[i].BuffEndTime = INVALID_TBLIDX;
		_player->GetAttributesManager()->sBuffTimeInfo[i].BuffTime = INVALID_TBLIDX;
		_player->GetAttributesManager()->sBuffTimeInfo[i].BuffID = INVALID_TBLIDX;

	}

	//SendPacket((char*)&pBuffDropReq, sizeof(sUG_BUFF_DROP_REQ));
	//_player->SendToPlayerList((char*)&pBuffDropReq, sizeof(sUG_BUFF_DROP_REQ));

}