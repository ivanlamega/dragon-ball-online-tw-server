#include <Game\Object\Mob.h>
#include <World.h>
#include <Packet\Game\PacketGU.h>
#include <Game\Object\Player.h>
#include <Logger.h>

bool hasmoved = true;//false;
//----------------------------------------
//	Mob Constructor
//----------------------------------------
Mob::Mob() : Object()
{
	m_objectType = eOBJTYPE::OBJTYPE_MOB;
	lastMoveTime = 10; //0;
	randMove = rand() % 100 + 10;
}
//----------------------------------------
//	Mob Destructor
//----------------------------------------
Mob::~Mob()
{
	CleanupsBeforeDelete();
}
//----------------------------------------
//	Remove that Mob From World
//----------------------------------------
void Mob::CleanupsBeforeDelete()
{
	Object::RemoveFromWorld();
	//m_MobRef.getTarget()->Remove(this, true);
}
//----------------------------------------
//	Add that Mob to World
//----------------------------------------
void Mob::AddToWorld()
{
	Object::AddToWorld();
}
//----------------------------------------
//	Remove from world
//----------------------------------------
void Mob::RemoveFromWorld()
{
	if (IsInWorld())
	{
		///- Release charmed creatures, unsummon totems and remove pets/guardians
	}
	Object::RemoveFromWorld();
}
//----------------------------------------
//	Get the map reference
//----------------------------------------
MobReference &Mob::GetMapRef()
{
	return m_MobRef;
}
//----------------------------------------
//	Create the Mob Spawn Packet
//----------------------------------------
void Mob::BuildPacketForSpawn(SpawnMOB& spawnData)
{
	memset(&spawnData, 0, sizeof(SpawnMOB));

	spawnData.wOpCode = GU_OBJECT_CREATE;
	spawnData.wPacketSize = sizeof(SpawnMOB) - 2;

	spawnData.AspectID = 0;
	spawnData.curEP = me.CurEP;
	spawnData.curLP = me.CurLP;
	spawnData.Handle = GetHandle();
	spawnData.Level = me.Level;
	spawnData.maxEP = me.MaxEP;
	spawnData.maxLP = me.MaxLP;
	spawnData.Size = 10;
	spawnData.Type = OBJTYPE_MOB;
	spawnData.Position.x = me.curPos.x;
	spawnData.Position.y = me.curPos.y;
	spawnData.Position.z = me.curPos.z;
	spawnData.Rotation.x = me.Spawn_Dir.x;
	spawnData.Rotation.y = me.Spawn_Dir.y;
	spawnData.Rotation.z = me.Spawn_Dir.z;
	spawnData.StateID = eCHARSTATE::CHARSTATE_SPAWNING;
	spawnData.Tblidx = me.MonsterID;

	spawnData.Unknown2 = 0;

	spawnData.test0 = 0;
	spawnData.test1 = 0;
	spawnData.test2 = 0;
	spawnData.test3 = 0;
	spawnData.BurnEffect = 0;
	spawnData.PoisonEffect = 0;
	spawnData.test6 = 0;
	spawnData.test7 = 0;
	spawnData.test8 = 0;
	spawnData.test9 = 0;
	spawnData.test10 = 0;
	spawnData.test11 = 0;
	spawnData.Run_Speed = 2;
	spawnData.Run_Speed_origin = 2;
	spawnData.Walk_Speed = 2;
	spawnData.Walk_Speed_origin = 2;

	for (int i = 0; i < 10; i++) spawnData.Unknown[i] = 0;
	for (int i = 0; i < 9; i++) spawnData.Unknown4[i] = 0;
	for (int i = 0; i < 20; i++) spawnData.unkasd[i] = 0;
	
	spawnData.Unknown[3] = 0;//move pattern tblidx
	spawnData.Unknown[4] = 0;//move pattern tblidx
	spawnData.Unknown[5] = 0;//move pattern tblidx
	spawnData.Unknown[6] = 0;//move pattern tblidx
}
//----------------------------------------
//	Create the mob and fill all info, Will need to remove mob after its killed at the end. 
//----------------------------------------
bool Mob::Create(sMOB_TBLDAT* mobTbl, SpawnMOB spawnInfo)
{
	me.MonsterID = mobTbl->tblidx;
	SetIsFighting(false);
	me.ShowName = true;
	me.SpawnAnimation = true;

	me.Grade = mobTbl->byGrade;
	me.Property = mobTbl->byProperty;
	//me.Drop_each_id = mobTbl->dropEachTblidx;
//	me.Drop_quest_id = mobTbl->dropQuestTblidx;
//	me.Drop_type_id = mobTbl->dropTypeTblidx;
//	me.Drop_item_id = mobTbl->drop_Item_Tblidx;
//	me.Mob_group = mobTbl->dwMobGroup;
	me.Exp = mobTbl->fDrop_Exp_Rate;
	me.Mob_Kind = mobTbl->wMob_Kind;
	me.Sight_angle = mobTbl->wSightAngle;
//	me.TMQ_Point = mobTbl->wTMQPoint;
	me.DropEachRateControl = mobTbl->byDropEachRateControl;
	me.DropEItemRateControl = mobTbl->byDropEItemRateControl;
	me.DropLItemRateControl = mobTbl->byDropLItemRateControl;
	me.DropNItemRateControl = mobTbl->byDropNItemRateControl;
	me.DropSItemRateControl = mobTbl->byDropSItemRateControl;
	me.DropTypeRateControl = mobTbl->byDropTypeRateControl;
	me.DisplayID;

	me.target = INVALID_TBLIDX;
	me.StateID = eCHARSTATE::CHARSTATE_SPAWNING;
	me.ConditionFlag = 0;
	me.Con = mobTbl->byCon;
	me.Dex = mobTbl->byDex;
	me.Eng = mobTbl->byEng;
	me.Foc = mobTbl->byFoc;
	me.Sol = mobTbl->bySol;
	me.Str = mobTbl->byStr;
	me.Attack_Animation_Qty = mobTbl->byAttack_Animation_Quantity;
	me.Attack_Type = mobTbl->byAttack_Type;
	me.Battle_Attribute = mobTbl->byBattle_Attribute;
	me.HtbBlockRate = mobTbl->wBlock_Rate;
	me.Level = mobTbl->byLevel;
	me.Mob_type = mobTbl->byMob_Type; // need check
	me.Scan_range = mobTbl->byScan_Range;
	me.Sight_range = mobTbl->bySight_Range;
	*me.Use_skill_basis = *mobTbl->byUse_Skill_Basis;
	me.Ai_bit_flag = mobTbl->dwAi_Bit_Flag;
	me.AllianceID = mobTbl->dwAllianceIdx;
	me.DialogGroup = mobTbl->dwDialogGroup;
	me.Drop_Zenny = mobTbl->fDrop_Zenny_Rate;
	me.Attack_range = mobTbl->fAttack_Range;
	me.Drop_zenny_rate = mobTbl->fDrop_Zenny_Rate;
	me.Fly_height = mobTbl->fFly_Height;
	me.Radius = mobTbl->fRadius;
	me.Radius_x = mobTbl->fRadius_X;
	me.Radius_z = mobTbl->fRadius_Z;
	me.Run_Speed = mobTbl->fRun_Speed;
	me.Run_Speed_origin = mobTbl->fRun_Speed_Origin;
	me.Scale = mobTbl->fScale;
	me.Walk_Speed = mobTbl->fWalk_Speed;
	me.Walk_Speed_origin = mobTbl->fWalk_Speed_Origin;
	me.Name = mobTbl->Name;
	me.CurLP = mobTbl->wBasic_LP;
	me.CurEP = mobTbl->wBasic_EP;
	me.MaxLP = mobTbl->wBasic_LP;
	me.MaxEP = mobTbl->wBasic_EP;
	me.AttackSpeedRate = mobTbl->wAttack_Speed_Rate;
	*me.use_Skill_Tblidx = *mobTbl->use_Skill_Tblidx;
	me.Aggro_max_count = mobTbl->wAggroMaxCount;
	me.Attack_cool_time = mobTbl->wAttackCoolTime;
	me.Attack_rate = mobTbl->wAttack_Rate;
	me.Attack_speed_rate = mobTbl->wAttack_Speed_Rate;
	me.Basic_aggro_point = mobTbl->wBasic_Aggro_Point;
	me.Basic_energy_defence = mobTbl->wBasic_Energy_Defence;
	me.Basic_physical_Offence = mobTbl->wBasicPhysicalOffence;
	me.Basic_energy_Offence = mobTbl->wBasicEnergyOffence;
	me.Basic_physical_defence = mobTbl->wBasic_Physical_Defence;
	me.Block_rate = mobTbl->wBlock_Rate;
	me.Curse_success_rate = mobTbl->wCurse_Success_Rate;
	me.Curse_tolerance_rate = mobTbl->wCurse_Tolerance_Rate;
	me.Dodge_rate = mobTbl->wDodge_Rate;
	me.Ep_Regeneration = mobTbl->wEP_Regeneration;
	me.Lp_Regeneration = mobTbl->wLP_Regeneration;
	*me.Use_skill_Lp = *mobTbl->wUse_Skill_LP;
	*me.Use_skill_time = *mobTbl->wUse_Skill_Time;
	me.Spawn_Loc = spawnInfo.Position; //For spawning individual Mobs
	me.Spawn_Dir = spawnInfo.Rotation; //For spawning individual Mobs

	me.Spawn_Cool_Time = 10000;
	me.MapID = spawnInfo.Tblidx; // is valid ?
	SetIsDead(false);
	me.KilledTime = 0;
	me.isAggro = false;
	me.curPos = spawnInfo.Position; //For spawning individual Mobs
	me.chainAttackCount = 0;
	me.MaxchainAttackCount = 0;
	handle = me.UniqueID = sWorld.AcquireSerialId();

	Relocate(me.curPos.x, me.curPos.y, me.curPos.z, me.Spawn_Dir.x, me.Spawn_Dir.y, me.Spawn_Dir.z);

/*	if (me.Grade != eMOB_GRADE::MOB_GRADE_HERO && me.Grade != eMOB_GRADE::MOB_GRADE_ULTRA)
	{
		
	}*/
	AddToWorld();
	me.isSpawned = true;
	respawnTime = me.Spawn_Cool_Time;
	/*if (me.Grade >= eMOB_GRADE::MOB_GRADE_SUPER)
	{
		respawnTime = rand() % 1000 + 500;
	}*/
	return true;
}

//----------------------------------------
//	Crea la mafia y llena toda la información. Añade información de generación para que se pueda agregar mafia.
//----------------------------------------
bool Mob::Create(sSPAWN_TBLDAT* spawnTbl, sMOB_TBLDAT* mobTbl)
{
	me.MonsterID = mobTbl->tblidx;
	SetIsFighting(false);
	me.ShowName = true;
	me.SpawnAnimation = true;

	me.Grade = mobTbl->byGrade;
	me.Property = mobTbl->byProperty;
	//me.Drop_each_id = mobTbl->dropEachTblidx;
	//	me.Drop_quest_id = mobTbl->dropQuestTblidx;
	//	me.Drop_type_id = mobTbl->dropTypeTblidx;
	//	me.Drop_item_id = mobTbl->drop_Item_Tblidx;
	//	me.Mob_group = mobTbl->dwMobGroup;
	me.Exp = mobTbl->fDrop_Exp_Rate;
	me.Mob_Kind = mobTbl->wMob_Kind;
	me.Sight_angle = mobTbl->wSightAngle;
	//	me.TMQ_Point = mobTbl->wTMQPoint;
	me.DropEachRateControl = mobTbl->byDropEachRateControl;
	me.DropEItemRateControl = mobTbl->byDropEItemRateControl;
	me.DropLItemRateControl = mobTbl->byDropLItemRateControl;
	me.DropNItemRateControl = mobTbl->byDropNItemRateControl;
	me.DropSItemRateControl = mobTbl->byDropSItemRateControl;
	me.DropTypeRateControl = mobTbl->byDropTypeRateControl;
	me.DisplayID;

	me.target = INVALID_TBLIDX;
	me.StateID = eCHARSTATE::CHARSTATE_SPAWNING;
	me.ConditionFlag = 0;
	me.Con = mobTbl->byCon;
	me.Dex = mobTbl->byDex;
	me.Eng = mobTbl->byEng;
	me.Foc = mobTbl->byFoc;
	me.Sol = mobTbl->bySol;
	me.Str = mobTbl->byStr;
	me.Attack_Animation_Qty = mobTbl->byAttack_Animation_Quantity;
	me.Attack_Type = mobTbl->byAttack_Type;
	me.Battle_Attribute = mobTbl->byBattle_Attribute;
	me.HtbBlockRate = mobTbl->wBlock_Rate;
	me.Level = mobTbl->byLevel;
	me.Mob_type = mobTbl->byMob_Type; // need check
	me.Scan_range = mobTbl->byScan_Range;
	me.Sight_range = mobTbl->bySight_Range;
	*me.Use_skill_basis = *mobTbl->byUse_Skill_Basis;
	me.Ai_bit_flag = mobTbl->dwAi_Bit_Flag;
	me.AllianceID = mobTbl->dwAllianceIdx;
	me.DialogGroup = mobTbl->dwDialogGroup;
	me.Drop_Zenny = mobTbl->fDrop_Zenny_Rate;
	me.Attack_range = mobTbl->fAttack_Range;
	me.Drop_zenny_rate = mobTbl->fDrop_Zenny_Rate;
	me.Fly_height = mobTbl->fFly_Height;
	me.Radius = mobTbl->fRadius;
	me.Radius_x = mobTbl->fRadius_X;
	me.Radius_z = mobTbl->fRadius_Z;
	me.Run_Speed = mobTbl->fRun_Speed;
	me.Run_Speed_origin = mobTbl->fRun_Speed_Origin;
	me.Scale = mobTbl->fScale;
	me.Walk_Speed = mobTbl->fWalk_Speed;
	me.Walk_Speed_origin = mobTbl->fWalk_Speed_Origin;
	me.Name = mobTbl->Name;
	me.CurLP = mobTbl->wBasic_LP;
	me.CurEP = mobTbl->wBasic_EP;
	me.MaxLP = mobTbl->wBasic_LP;
	me.MaxEP = mobTbl->wBasic_EP;
	me.AttackSpeedRate = mobTbl->wAttack_Speed_Rate;
	*me.use_Skill_Tblidx = *mobTbl->use_Skill_Tblidx;
	me.Aggro_max_count = mobTbl->wAggroMaxCount;
	me.Attack_cool_time = mobTbl->wAttackCoolTime;
	me.Attack_rate = mobTbl->wAttack_Rate;
	me.Attack_speed_rate = mobTbl->wAttack_Speed_Rate;
	me.Basic_aggro_point = mobTbl->wBasic_Aggro_Point;
	me.Basic_energy_defence = mobTbl->wBasic_Energy_Defence;
	me.Basic_physical_Offence = mobTbl->wBasicPhysicalOffence;
	me.Basic_energy_Offence = mobTbl->wBasicEnergyOffence;
	me.Basic_physical_defence = mobTbl->wBasic_Physical_Defence;
	me.Block_rate = mobTbl->wBlock_Rate;
	me.Curse_success_rate = mobTbl->wCurse_Success_Rate;
	me.Curse_tolerance_rate = mobTbl->wCurse_Tolerance_Rate;
	me.Dodge_rate = mobTbl->wDodge_Rate;
	me.Ep_Regeneration = mobTbl->wEP_Regeneration;
	me.Lp_Regeneration = mobTbl->wLP_Regeneration;
	*me.Use_skill_Lp = *mobTbl->wUse_Skill_LP;
	*me.Use_skill_time = *mobTbl->wUse_Skill_Time;
	me.MonsterSpawnID = spawnTbl->tblidx;
	me.Spawn_Loc = spawnTbl->vSpawn_Loc;
	me.Spawn_Dir = spawnTbl->vSpawn_Dir;
	me.Spawn_Loc_Range = spawnTbl->bySpawn_Loc_Range;
	me.Spawn_Quantity = spawnTbl->bySpawn_Quantity;
	me.Spawn_Cool_Time = spawnTbl->wSpawn_Cool_Time;
	me.Spawn_Move_Type = spawnTbl->bySpawn_Move_Type;
	me.Wander_Range = spawnTbl->byWander_Range;
	me.Move_Range = spawnTbl->byMove_Range;
	me.Move_DelayTime = spawnTbl->byMove_DelayTime;
	me.FollowDistance = spawnTbl->vFollowDistance;
	me.Party_Index = spawnTbl->dwParty_Index;
	me.Party_Leader = spawnTbl->bParty_Leader;
	me.spawnGroupId = spawnTbl->spawnGroupId;
	me.MapID = spawnTbl->tblidx; // is valid ?
	SetIsDead(false);
	me.KilledTime = 0;
	me.isAggro = false;
	me.curPos = spawnTbl->vSpawn_Loc;
	me.chainAttackCount = 0;
	me.MaxchainAttackCount = 0;
	handle = me.UniqueID = sWorld.AcquireSerialId();

	Relocate(me.curPos.x, me.curPos.y, me.curPos.z, me.Spawn_Dir.x, me.Spawn_Dir.y, me.Spawn_Dir.z);

	/*	if (me.Grade != eMOB_GRADE::MOB_GRADE_HERO && me.Grade != eMOB_GRADE::MOB_GRADE_ULTRA)
	{

	}*/
	AddToWorld();
	me.isSpawned = true;
	respawnTime = me.Spawn_Cool_Time;
	/*if (me.Grade >= eMOB_GRADE::MOB_GRADE_SUPER)
	{
	respawnTime = rand() % 1000 + 500;
	}*/
	return true;
}
//----------------------------------------
//	Quitar del mundo
//----------------------------------------
void Mob::Update(uint32 update_diff, uint32 time)
{
	if (GetIsDead() == false)
	{
		if (GetIsDead() == false)
		{
			Regen();
		
		}
		//MoveToPoint();
		CheckAgro();
	}
	else
	{
		Respawn();
	}
}
void Mob::MoveToPoint()
{		
	for (auto it = m_MobRef.getTarget()->GetPlayers().begin(); it != m_MobRef.getTarget()->GetPlayers().end(); ++it)
	{
		if (it->getSource())
		{
			Player* plr = it->getSource();
			if (plr->IsInWorld() == true && plr->GetSession() != NULL)
			{
				//printf("plr->isFlying %d \n ", plr->GetFlying());
				float dist = NtlGetDistance(me.curPos.x, me.curPos.z, plr->GetVectorPosition().x, plr->GetVectorPosition().z);
				///////////////////////////////////////
				//Necesita moverse al jugador antes del ataque //
				/////////////////////////////////////
				if (dist <= 10)
				{
					sGU_CHAR_DEST_MOVE res;
					memset(&res, 0, sizeof(sGU_CHAR_DEST_MOVE));

					res.wOpCode = GU_CHAR_DEST_MOVE;
					res.byMoveFlag = NTL_MOVE_MOUSE_MOVEMENT;
					res.wPacketSize = sizeof(sGU_CHAR_DEST_MOVE) - 2;

					res.handle = GetHandle();
					res.byDestLocCount = 1;
					res.bHaveSecondDestLoc = false;

					res.vCurLoc.x = me.Spawn_Loc.x;
					res.vCurLoc.y = me.Spawn_Loc.y;
					res.vCurLoc.z = me.Spawn_Loc.z;

					res.avDestLoc[5].x = plr->GetVectorPosition().x;//0
					res.avDestLoc[5].y = plr->GetVectorPosition().y;
					res.avDestLoc[5].z = plr->GetVectorPosition().z;
					res.unknown = 0;

					GetState()->sCharStateDetail.sCharStateDestMove.dwTimeStamp = rand() % 20 - 1; //1?
					GetState()->sCharStateDetail.sCharStateDestMove.byMoveFlag = res.byMoveFlag;
					GetState()->sCharStateDetail.sCharStateDestMove.vSecondDestLoc = res.vSecondDestLoc;
					GetState()->sCharStateDetail.sCharStateDestMove.unknown = INVALID_BYTE;
					GetState()->sCharStateDetail.sCharStateDestMove.byDestLocCount = res.byDestLocCount;
					GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0] = res.avDestLoc[0];

					SetState(eCHARSTATE::CHARSTATE_DESTMOVE);

					SendToPlayerList((char*)&res, sizeof(sGU_CHAR_DEST_MOVE));
				}
			}
		}
	}
}
//----------------------------------------
//Hago un texto aquí Necesito eliminar todo lo que más tarde mierda y rehacer
//----------------------------------------
void Mob::CheckAgro()
{
	lastMoveTime += 10;	//1
	for (auto it = m_MobRef.getTarget()->GetPlayers().begin(); it != m_MobRef.getTarget()->GetPlayers().end(); ++it)
	{
		if (it->getSource())
		{
			Player* plr = it->getSource();
			if (plr->IsInWorld() == true && plr->GetSession() != NULL)
			{
				//printf("plr->isFlying %d \n ", plr->GetFlying());
				float dist = NtlGetDistance(me.curPos.x, me.curPos.z, plr->GetVectorPosition().x, plr->GetVectorPosition().z);
				///////////////////////////////////////
				//Need Move to Player Before Attack //
				/////////////////////////////////////
				if (dist <= 20 && plr->GetIsSkillCasting() == true)
				{
					
				}
				//if Distance difrence <= 10 start Mob attack...
				//need Find What mob are Agressive or not "in the moment all are Agressive"
				if (dist <= 6 && plr->GetIsDead() == false && plr->GetIsFlying() == false) //True=false
				{
					if (lastMoveTime > 3 || lastMoveTime <= 0)
						lastMoveTime = BATTLE_CHAIN_ATTACK_START;
					int attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
					int Random = rand() % 100 + 1;
					float percent = (me.Attack_rate - plr->GetPcProfile()->avatarAttribute.wLastDodgeRate) / 2;
					if (percent <= 0)
					{
						if (Random >= 0 && Random <= 50)
							attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
						else
							attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
					}
					if (percent >= 0 && percent <= 50)
					{
						if(Random >= 0 && Random <= 25)
							attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
						else
							attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
					}
					//Hit 50%
					if (percent >= 51 && percent <= 75)
					{
						if (Random >= 0 && Random <= 50)
							attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
						else
							attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
					}
					//Hit 75%
					if (percent >= 76 && percent <= 100)
					{
						if (Random >= 0 && Random <= 75)
							attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;
						else
							attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
					}
					//Hit 100%
					if (percent >= 100)
					{						
							attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;						
					}
					
					sGU_CHAR_ACTION_ATTACK res;			
					
					int guardType = eDBO_GUARD_TYPE::DBO_GUARD_TYPE_INVALID;
					int attackValue = me.Basic_physical_defence * me.Basic_physical_defence / (me.Basic_physical_defence + plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence) * 3;
					//float attackValue = me.Basic_Offence * ((1 - plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence / (plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence + me.Level * 40)) + ((me.Level - plr->GetPcProfile()->byLevel) * 0.005));
					//float attackValue = (me.Basic_Offence - plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence) / 2;
					//float attackValue = (plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence / 100) * 
					if (attackValue <= 1 || attackValue > 1000000000)
					{
						attackValue = rand() % 20 - 1;
					}
					if (attackValue <= 2 || attackValue > 1000000000)
					{
						attackValue = rand() % 30 - 1;
					}
					//printf("Moster Atack  %d \n ", me.Basic_Offence);
					//printf("Player Defense %d \n ", plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence);
					//printf("Moster Finnal Attack Value  %d \n ", PhysicalOffence);
					int reflectedDamage = 0;					

					res.bChainAttack = true;
					res.byAttackResult = attackResult;
					res.byBlockedAction = guardType;
					res.dwLpEpEventId = 0;
					res.fReflectedDamage = reflectedDamage;
					res.byAttackSequence = lastMoveTime;
					res.hSubject = me.UniqueID;
					res.hTarget = plr->GetHandle();
					res.vShift = GetVectorPosition();
					res.wAttackResultValue = attackValue;
					res.bRecoveredLP = false;
					res.wRecoveredLpValue = 0;
					res.bRecoveredEP = false;
					res.wRecoveredEpValue = 0;
					res.wOpCode = GU_CHAR_ACTION_ATTACK;
					res.wPacketSize = sizeof(sGU_CHAR_ACTION_ATTACK) - 2;

					plr->SendPacket((char*)&res, sizeof(sGU_CHAR_ACTION_ATTACK));
					plr->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_ACTION_ATTACK));

					if (attackResult != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
					{
						if (attackers == 10)		//add
							attackers = me.UniqueID;//add
						plr->TakeMobDemage(attackValue);
					}
				}
			}
		}
	}
	
	
	randMove = rand() % 100 + 10;
	hasmoved = true;
}
//----------------------------------------
//	Handle mob regen each second
//----------------------------------------
void Mob::Regen()
{
	if (GetIsFighting() == true || GetIsDead() == true)
		return;
	if (me.CurEP < me.MaxEP)
	{
		me.CurEP += me.Ep_Regeneration;
		if (me.CurEP > me.MaxEP)
			me.CurEP = me.MaxEP;
	}
	if (me.CurLP < me.MaxLP)
	{
		me.CurLP += me.Lp_Regeneration;
		if (me.CurLP > me.MaxLP)
			me.CurLP = me.MaxLP;
	}
}
//----------------------------------------
//	Return the mob struct filled
//----------------------------------------
MonsterData Mob::GetMobData() const
{
	return me;
}
//----------------------------------------
//	Return the mob struct filled
//----------------------------------------
void Mob::TakeDamage(uint32 amount)
{
	mutexMob.lock();

	int32_t newLife = me.CurLP;
	SetIsFighting(true);
	me.isAggro = true;
	newLife -= amount;
	if (newLife <= 0)
	{
		SetIsDead(true);
		SetIsFighting(false);
		newLife = 0;
	}
	me.CurLP = newLife;

	sGU_UPDATE_CHAR_LP updLp;
	updLp.handle = me.UniqueID;
	updLp.wCurLP = me.CurLP = newLife;
	updLp.wMaxLP = me.MaxLP;
	updLp.wOpCode = GU_UPDATE_CHAR_LP;
	updLp.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;
	
	mutexMob.unlock();

	SendToPlayerList((char*)&updLp, sizeof(sGU_UPDATE_CHAR_LP));
	if (GetIsDead() == true)
	{

		SendDeath();

	}
}
//----------------------------------------
//	Enviar el nuevo estado de la mafia como muerte.
//----------------------------------------
void Mob::SendDeath()
{
	sGU_UPDATE_CHAR_STATE state;
	state.handle = me.UniqueID;
	state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_FAINTING;
	state.sCharState.sCharStateDetail.sCharStateFainting.byReason = eFAINT_REASON::FAINT_REASON_HIT;
	state.wOpCode = GU_UPDATE_CHAR_STATE;
	state.sCharState.sCharStateBase.vCurLoc.x = me.curPos.x;
	state.sCharState.sCharStateBase.vCurLoc.y = me.curPos.y;
	state.sCharState.sCharStateBase.vCurLoc.z = me.curPos.z;
	state.sCharState.sCharStateBase.vCurDir.x = me.Spawn_Dir.x;
	state.sCharState.sCharStateBase.vCurDir.y = me.Spawn_Dir.y;
	state.sCharState.sCharStateBase.vCurDir.z = me.Spawn_Dir.x;
	state.sCharState.sCharStateBase.dwConditionFlag = 0;
	//	res.sCharState.sCharStateBase.bFightMode = false;
	state.sCharState.sCharStateBase.dwStateTime = 2;
	state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;

	mutexMob.lock();
	for (auto it = m_MobRef.getTarget()->GetPlayers().begin(); it != m_MobRef.getTarget()->GetPlayers().end(); ++it)
	{
		if (it->getSource())
		{
			Player* plr = it->getSource();
			if (plr->IsInWorld() == true && plr->GetSession() != NULL)
			{
				float dist = NtlGetDistance(me.curPos.x, me.curPos.z, plr->GetVectorPosition().x, plr->GetVectorPosition().z);
				if (dist <= 100)
				{
					plr->SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
					if (attackers == plr->GetHandle())
					{
						plr->RewardExpFromMob(me);
						plr->RewardDropFromMob(me);
					}
				}
			}
		}
	}
	attackers = 0;
	mutexMob.unlock();
}
//----------------------------------------
//	Respawn, calculate respawn time etc
//----------------------------------------
void Mob::Respawn()
{
	if (me.KilledTime >= respawnTime)
	{
		me.CurLP = me.MaxLP;
		me.CurEP = me.MaxEP;
		me.curPos = me.Spawn_Loc;
		SetIsDead(false);
		SetIsSpawn(true);
		me.KilledTime = 0;
	}
	else
	{
		/// set the value later to let the animation play
		if (me.KilledTime > 5)
		{
			me.StateID = eCHARSTATE::CHARSTATE_SPAWNING;
			SetIsSpawn(false);
		}
		me.KilledTime += 1;
	}
}
//----------------------------------------
//	Send packet to all player in the list
//----------------------------------------
void Mob::SendToPlayerList(char* data, size_t size)
{
	mutexMob.lock();
	for (auto it = m_MobRef.getTarget()->GetPlayers().begin(); it != m_MobRef.getTarget()->GetPlayers().end(); ++it)
	{
		if (it->getSource())
		{
			Player* plr = it->getSource();
			if (plr->IsInWorld() == true && plr->GetSession() != NULL)
			{
				float dist = NtlGetDistance(me.curPos.x, me.curPos.z, plr->GetVectorPosition().x, plr->GetVectorPosition().z);
				if (dist <= 100)
					plr->SendPacket(data, size);
			}
		}
	}
	mutexMob.unlock();
}
//----------------------------------------
//		GETTER
//----------------------------------------
DWORD Mob::GetPowerLevel()
{
	return Dbo_CalculatePowerLevel(me.Str, me.Con, me.Foc, me.Dex, me.Sol, me.Eng,
		me.Basic_physical_defence, me.Basic_physical_defence, me.Basic_energy_Offence, me.Basic_energy_defence, me.Attack_rate, me.Dodge_rate,
		me.Curse_success_rate, me.Curse_tolerance_rate, /*CRITICAL ?*/ 0, 0, me.AttackSpeedRate, me.MaxLP, me.MaxEP, me.CurLP,
		me.CurEP, BYTE(0), me.Level, me.Grade);
}

//----------------------------------------
//	Tell everyone the character state changed
//----------------------------------------
void Mob::UpdateState(eCHARSTATE _state)
{
	sGU_UPDATE_CHAR_STATE res;

	res.wOpCode = GU_UPDATE_CHAR_STATE;
	res.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;

	res.sCharState.sCharStateBase.byStateID = GetState()->sCharStateBase.byStateID = _state;
	res.sCharState.sCharStateBase.vCurLoc = GetState()->sCharStateBase.vCurLoc;
	res.sCharState.sCharStateBase.vCurDir = GetState()->sCharStateBase.vCurDir;

	res.handle = GetHandle();

	// sLog.outDetail("Need handle correct condition flag here. UpdateCharState()");

	res.sCharState.sCharStateBase.dwConditionFlag = GetState()->sCharStateBase.dwConditionFlag = 0;
	res.sCharState.sCharStateBase.dwStateTime = GetState()->sCharStateBase.dwStateTime = 0;

	GetState()->sCharStateBase.isFighting = GetIsFighting();
	GetState()->sCharStateBase.isFlying = false;

	SendToPlayerList((char*)&res, sizeof(sGU_UPDATE_CHAR_STATE));
}
