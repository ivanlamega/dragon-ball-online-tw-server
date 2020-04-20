#include <Game\Object\Mob.h>
#include <World.h>
#include <Packet\Game\PacketGU.h>
#include <Game\Object\Player.h>
#include <Logger.h>

bool hasmoved = false;
//----------------------------------------
//	Mob Constructor
//----------------------------------------
Mob::Mob() : Object()
{
	m_objectType = eOBJTYPE::OBJTYPE_MOB;	
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
	
	spawnData.curEP = me.CurEP;
	spawnData.curLP = me.CurLP;
	spawnData.Handle = GetHandle();
	spawnData.Level = me.Level;
	spawnData.maxEP = me.MaxEP;
	spawnData.maxLP = me.MaxLP;
	spawnData.Size = 10;
	spawnData.Type = OBJTYPE_MOB;
	
	spawnData.Tblidx = me.MonsterID;
	spawnData.fLastWalkingSpeed = 4;
	spawnData.fLastRunningSpeed = 8;
	spawnData.fLastAirgSpeed = 0;
	spawnData.fLastAirgDashSpeed = 0;
	spawnData.fLastAirgDashAccelSpeed = 0;
	//spawnData.AttackSpeedRate = 5;
	spawnData.byBallType = me.ByDagonBall;

	GetState()->sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;
	GetState()->sCharStateBase.vCurLoc.x = me.curPos.x;
	GetState()->sCharStateBase.vCurLoc.y = me.curPos.y;
	GetState()->sCharStateBase.vCurLoc.z = me.curPos.z;
	GetState()->sCharStateBase.vCurDir.x = me.Spawn_Dir.x;
	GetState()->sCharStateBase.vCurDir.y = me.Spawn_Dir.y;
	GetState()->sCharStateBase.vCurDir.z = me.Spawn_Dir.z;
	GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;

	GetState()->sCharStateDetail.sCharStateSpawning.byTeleportType = 1;
	GetState()->sCharStateDetail.sCharStateSpawning.unk = 1;

	memcpy(&spawnData.State.sCharStateBase, &GetState()->sCharStateBase, sizeof(sCHARSTATE_BASE));
	memcpy(&spawnData.State.sCharStateDetail, &GetState()->sCharStateDetail, sizeof(sCHARSTATE_DETAIL));
}
//----------------------------------------
//	Create the mob and fill all info
//----------------------------------------
bool Mob::Create(sMOB_TBLDAT* mobTbl, SpawnMOB spawnInfo)
{
	me.MonsterID = mobTbl->tblidx;
	SetIsFighting(false);
	me.ShowName = true;
	me.SpawnAnimation = true;

	me.Grade = mobTbl->byGrade;
	me.Property;// = mobTbl->byProperty;
	//me.Drop_each_id = mobTbl->dropEachTblidx;
	//	me.Drop_quest_id = mobTbl->dropQuestTblidx;
	//	me.Drop_type_id = mobTbl->dropTypeTblidx;
	//	me.Drop_item_id = mobTbl->drop_Item_Tblidx;
	//	me.Mob_group = mobTbl->dwMobGroup;
	me.Exp = mobTbl->dwDrop_Exp;
	me.Mob_Kind = mobTbl->wMob_Kind;
	me.Sight_angle = mobTbl->wSightAngle;
	//	me.TMQ_Point = mobTbl->wTMQPoint;
	me.DropEachRateControl = mobTbl->byDropEachRateControl;
	me.DropEItemRateControl = mobTbl->byDropEItemRateControl;
	me.DropLItemRateControl = mobTbl->byDropLItemRateControl;
	me.DropNItemRateControl = mobTbl->byDropNItemRateControl;
	me.DropSItemRateControl = mobTbl->byDropSItemRateControl;
	me.DropTypeRateControl;// = mobTbl->byDropTypeRateControl;
	me.DisplayID;
	me.Drop_quest_id = mobTbl->dropQuestTblidx;

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
	me.Spawn_Loc = spawnInfo.State.sCharStateBase.vCurLoc; //For spawning individual Mobs
	me.Spawn_Dir = spawnInfo.State.sCharStateBase.vCurDir; //For spawning individual Mobs
	me.Spawn_Cool_Time = 10000;
	me.MapID = spawnInfo.Tblidx; // is valid ?
	SetIsDead(false);
	me.KilledTime = 0;
	me.isAggro = false;
	me.initialSpawn = true;
	me.curPos = spawnInfo.State.sCharStateBase.vCurLoc; //For spawning individual Mobs
	me.chainAttackCount = 0;
	me.MaxchainAttackCount = 0;
	handle = me.UniqueID = spawnInfo.Handle;
	
	me.physicalCriticalDefenseRate = CalculePhysicalCriticalDefenceRate(me.Con);
	me.energyCriticalDefenseRate = CalculeEnergyCriticalDefenceRate(me.Eng);
	me.Block_rate = CalculeBlockRate(me.Dex, me.Con);
	me.Block_Damage_rate = CalculeBlockDamageRate(me.Dex, me.Con);
	
	Relocate(me.curPos.x, me.curPos.y, me.curPos.z, me.Spawn_Dir.x, me.Spawn_Dir.y, me.Spawn_Dir.z);	
	
	AddToWorld();
	me.isSpawned = true;
	respawnTime = INVALID_TBLIDX;
	return true;
	
}
bool Mob::Create(sSPAWN_TBLDAT* spawnTbl, sMOB_TBLDAT* mobTbl)
{
	me.MonsterID = mobTbl->tblidx;
	SetIsFighting(false);
	me.ShowName = true;
	me.SpawnAnimation = true;

	me.Grade = mobTbl->byGrade;
	me.Property;// = mobTbl->byProperty;
	//me.Drop_each_id = mobTbl->dropEachTblidx;
//	me.Drop_quest_id = mobTbl->dropQuestTblidx;
//	me.Drop_type_id = mobTbl->dropTypeTblidx;
//	me.Drop_item_id = mobTbl->drop_Item_Tblidx;
//	me.Mob_group = mobTbl->dwMobGroup;
	me.Exp = mobTbl->dwDrop_Exp;
	me.Mob_Kind = mobTbl->wMob_Kind;
	me.Sight_angle = mobTbl->wSightAngle;
	//	me.TMQ_Point = mobTbl->wTMQPoint;
	me.DropEachRateControl = mobTbl->byDropEachRateControl;
	me.DropEItemRateControl = mobTbl->byDropEItemRateControl;
	me.DropLItemRateControl = mobTbl->byDropLItemRateControl;
	me.DropNItemRateControl = mobTbl->byDropNItemRateControl;
	me.DropSItemRateControl = mobTbl->byDropSItemRateControl;
	me.DropTypeRateControl;// = mobTbl->byDropTypeRateControl;
	me.DisplayID;
	me.Drop_quest_id = mobTbl->dropQuestTblidx;

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
	me.initialSpawn = true;
	me.curPos = spawnTbl->vSpawn_Loc;
	me.chainAttackCount = 0;
	me.MaxchainAttackCount = 0;
	handle = me.UniqueID = sWorld.AcquireSerialId();

	me.physicalCriticalDefenseRate = CalculePhysicalCriticalDefenceRate(me.Con);
	me.energyCriticalDefenseRate = CalculeEnergyCriticalDefenceRate(me.Eng);
	me.Block_rate = CalculeBlockRate(me.Dex, me.Con);
	me.Block_Damage_rate = CalculeBlockDamageRate(me.Dex, me.Con);

	int BallRandom = rand() % 100;
	if (BallRandom >= 0 && BallRandom <= 15)
	{
		me.ByDagonBall = 1;
	}

	Relocate(me.curPos.x, me.curPos.y, me.curPos.z, me.Spawn_Dir.x, me.Spawn_Dir.y, me.Spawn_Dir.z);

	if (spawnTbl->spawnGroupId != INVALID_TBLIDX)
	{
		me.initialSpawn = false;
	}


	AddToWorld();
	me.isSpawned = true;
	respawnTime = me.Spawn_Cool_Time;
	if (respawnTime <= 5)
	{
		respawnTime = INVALID_TBLIDX;
	}

	
	
	return true;
}
//----------------------------------------
//	Remove from world marco_rafael_@sapo.pt
//----------------------------------------
void Mob::Update(uint32 update_diff, uint32 time)
{	
	DWORD RegAt = GetTickCount() - TimmerReg;
	if (RegAt >= 1400)
	{
		if (GetIsDead() == false)
		{ 					
			Regen();				
		}
		else
		{
			Respawn();
		}		
		TimmerReg = GetTickCount();
	}	
	DWORD MoveAt = GetTickCount() - TimmerMove;
	if (MoveAt >= 8000 && GetIsDead() == false && GetInitialSpawn())
	{
		if (GetState()->sCharStateBase.byStateID == eCHARSTATE::CHARSTATE_STUNNED ||
			GetState()->sCharStateBase.byStateID == eCHARSTATE::CHARSTATE_PARALYZED ||
			GetState()->sCharStateBase.byStateID == eCHARSTATE::CHARSTATE_SLEEPING)
		{
			//	printf("nothing here im stuned");
		}
		else
		{
			MoveToPoint();
		}
		
		TimmerMove = GetTickCount();
	}
	DWORD AgroAt = GetTickCount() - TimmerAgro;
	if (AgroAt >= 1400 && GetIsDead() == false && GetInitialSpawn())
	{
		if (GetState()->sCharStateBase.byStateID == eCHARSTATE::CHARSTATE_STUNNED ||
			GetState()->sCharStateBase.byStateID == eCHARSTATE::CHARSTATE_PARALYZED ||
			GetState()->sCharStateBase.byStateID == eCHARSTATE::CHARSTATE_SLEEPING)
		{
		//	printf("nothing here im stuned");
		}
		else
		{
			CheckAgro();
		}
		TimmerAgro = GetTickCount();
	}
}
void Mob::MoveToPoint()
{		
	float myX, myZ;
	for (auto it = m_MobRef.getTarget()->GetPlayers().begin(); it != m_MobRef.getTarget()->GetPlayers().end(); ++it)
	{
		if (it->getSource())
		{
			Player* plr = it->getSource();
			if (plr->IsInWorld() == true && plr->GetSession() != NULL && GetIsDead() == false && GetInitialSpawn())
			{
				float dist = NtlGetDistance(me.curPos.x, me.curPos.z, plr->GetVectorPosition().x, plr->GetVectorPosition().z);
				if (dist <= DEFAULT_VISIBILITY_DISTANCE && GetIsDead() == false && GetIsFighting() == false && me.GotAgro == false)
				{
					myX = plr->GetVectorPosition().x;
					myZ = plr->GetVectorPosition().z;
				}
			}
		}
	}
	float dist = NtlGetDistance(me.curPos.x, me.curPos.z, myX, myZ);
	float DistSpawn = NtlGetDistance(me.curPos.x, me.curPos.z, me.Spawn_Loc.x, me.Spawn_Loc.z);

	if (dist <= DEFAULT_VISIBILITY_DISTANCE && GetIsDead() == false && GetIsFighting() == false && me.GotAgro == false && GetInitialSpawn())
	{
		randMove = rand() % 10 + 1;
		sGU_CHAR_DEST_MOVE res;
		memset(&res, 0, sizeof(sGU_CHAR_DEST_MOVE));

		res.wOpCode = GU_CHAR_DEST_MOVE;
		res.byMoveFlag = NTL_MOVE_FLAG_WALK;
		res.wPacketSize = sizeof(sGU_CHAR_DEST_MOVE) - 2;
		res.handle = GetHandle();
		res.byDestLocCount = 1;
		res.bHaveSecondDestLoc = false;
		dVECTOR3 curPos, newPos;

		curPos.x = dbo_move_float_to_pos(me.curPos.x);
		curPos.y = dbo_move_float_to_pos(me.curPos.y);
		curPos.z = dbo_move_float_to_pos(me.curPos.z);
		res.vCurLoc = curPos;
		res.unknown = 0;

		if (randMove >= 0 && randMove <= 4)
		{
			//	printf("Mob move to random Loc \n");
			newPos.x = dbo_move_float_to_pos(me.curPos.x + rand() % 10);
			newPos.y = dbo_move_float_to_pos(me.curPos.y);
			newPos.z = dbo_move_float_to_pos(me.curPos.z + rand() % 10);
			res.avDestLoc[0] = newPos;
		}
		if (randMove >= 5 && randMove <= 10)
		{
			//	printf("Mob move to random Loc \n");
			newPos.x = dbo_move_float_to_pos(me.curPos.x - rand() % 10);
			newPos.y = dbo_move_float_to_pos(me.curPos.y);
			newPos.z = dbo_move_float_to_pos(me.curPos.z - rand() % 10);
			res.avDestLoc[0] = newPos;
		}
		if (DistSpawn >= 14)
		{
			//	printf("Mob Back to Spawn Loc \n");
			newPos.x = dbo_move_float_to_pos(me.Spawn_Loc.x);
			newPos.y = dbo_move_float_to_pos(me.Spawn_Loc.y);
			newPos.z = dbo_move_float_to_pos(me.Spawn_Loc.z);
			res.avDestLoc[0] = newPos;
		}
		//Relocate(dbo_move_pos_to_float(newPos.x), dbo_move_pos_to_float(newPos.y), dbo_move_pos_to_float(newPos.z), me.Spawn_Dir.x, me.Spawn_Dir.y, me.Spawn_Dir.z);

		SendToPlayerList((char*)&res, sizeof(sGU_CHAR_DEST_MOVE));
		GetState()->sCharStateBase.byStateID = CHARSTATE_STANDING;
		GetState()->sCharStateBase.vCurLoc.x = dbo_move_pos_to_float(newPos.x);
		GetState()->sCharStateBase.vCurLoc.y = dbo_move_pos_to_float(newPos.y);
		GetState()->sCharStateBase.vCurLoc.z = dbo_move_pos_to_float(newPos.z);
		me.curPos = GetState()->sCharStateBase.vCurLoc;

	}
}
//----------------------------------------
//I do some test Here Need Delet all that Shit Later and Remake
//----------------------------------------
void Mob::CheckAgro()
{		
	if (GetIsDead() == true && !GetInitialSpawn())
	{
		return;
	}
	for (auto it = m_MobRef.getTarget()->GetPlayers().begin(); it != m_MobRef.getTarget()->GetPlayers().end(); ++it)
	{
		if (it->getSource())
		{
			Player* plr = it->getSource();
			if (plr->IsInWorld() == true && plr->GetSession() != NULL && GetIsDead() == false && GetInitialSpawn())
			{				
				float dist = NtlGetDistance(me.curPos.x, me.curPos.z, plr->GetVectorPosition().x, plr->GetVectorPosition().z);
				float DistSpawn = NtlGetDistance(me.curPos.x, me.curPos.z, me.Spawn_Loc.x, me.Spawn_Loc.z);
				
				//GetAggro
				if (dist <= 10 && plr->GetIsDead() == false && plr->GetIsFlying() == false && me.GotAgro == false && me.target == INVALID_TBLIDX 
					|| GetIsFighting() == true && plr->GetIsDead() == false && plr->GetIsFlying() == false && me.GotAgro == false && me.target == INVALID_TBLIDX)
				{
					me.target = plr->GetHandle();
					me.GotAgro = true;
					SetIsFighting(true);
					if (me.isAggro == false && me.target == plr->GetHandle())
					{
						//printf("Hey Bitch Come Here \n");
						sGU_BOT_BOTCAUTION_NFY Bot;
						Bot.wOpCode = GU_BOT_BOTCAUTION_NFY;
						Bot.wPacketSize = sizeof(sGU_BOT_BOTCAUTION_NFY) - 2;
						Bot.hBot = me.UniqueID;
						SendToPlayerList((char*)&Bot, sizeof(sGU_BOT_BOTCAUTION_NFY));
						me.isAggro = true;
					}
				}
				//Lost Agro by Distance
				if (DistSpawn >= 70 && plr->GetIsDead() == false && me.GotAgro == true && me.target == plr->GetHandle())
				{					
					me.target = INVALID_TBLIDX;
					me.GotAgro = false;	
					me.isAggro = false;
					SetIsFighting(false);
					
					sGU_CHAR_DEST_MOVE res;
					memset(&res, 0, sizeof(sGU_CHAR_DEST_MOVE));

					res.wOpCode = GU_CHAR_DEST_MOVE;
					res.byMoveFlag = NTL_MOVE_FLAG_RUN;
					res.wPacketSize = sizeof(sGU_CHAR_DEST_MOVE) - 2;
					res.handle = GetHandle();
					res.byDestLocCount = 1;
					res.bHaveSecondDestLoc = true;
					dVECTOR3 curPos, newPos;

					curPos.x = dbo_move_float_to_pos(me.curPos.x);
					curPos.y = dbo_move_float_to_pos(me.curPos.y);
					curPos.z = dbo_move_float_to_pos(me.curPos.z);
					res.vCurLoc = curPos;
					res.unknown = 0;


					//printf("You are Weak i not Going Follow You Anymore \n");
					newPos.x = dbo_move_float_to_pos(me.Spawn_Loc.x);
					newPos.y = dbo_move_float_to_pos(me.Spawn_Loc.y);
					newPos.z = dbo_move_float_to_pos(me.Spawn_Loc.z);
					res.avDestLoc[0] = newPos;
					
					//Relocate(dbo_move_pos_to_float(newPos.x), dbo_move_pos_to_float(newPos.y), dbo_move_pos_to_float(newPos.z), me.Spawn_Dir.x, me.Spawn_Dir.y, me.Spawn_Dir.z);

					SendToPlayerList((char*)&res, sizeof(sGU_CHAR_DEST_MOVE));

					GetState()->sCharStateBase.vCurLoc.x = dbo_move_pos_to_float(newPos.x);
					GetState()->sCharStateBase.vCurLoc.y = dbo_move_pos_to_float(newPos.y);
					GetState()->sCharStateBase.vCurLoc.z = dbo_move_pos_to_float(newPos.z);
					me.curPos = GetState()->sCharStateBase.vCurLoc;
				}	
			//	Lost agro by Dead/Flying
				if (plr->GetIsDead() == true && me.GotAgro == true && me.target == plr->GetHandle() 
					|| plr->GetIsFlying() == true && me.GotAgro == true && me.target == plr->GetHandle())
				{
					me.target = INVALID_TBLIDX;
					me.GotAgro = false;
					me.isAggro = false;
					SetIsFighting(false);

					sGU_CHAR_DEST_MOVE res;
					memset(&res, 0, sizeof(sGU_CHAR_DEST_MOVE));

					res.wOpCode = GU_CHAR_DEST_MOVE;
					res.byMoveFlag = NTL_MOVE_FLAG_RUN;
					res.wPacketSize = sizeof(sGU_CHAR_DEST_MOVE) - 2;
					res.handle = GetHandle();
					res.byDestLocCount = 1;
					res.bHaveSecondDestLoc = true;
					dVECTOR3 curPos, newPos;

					curPos.x = dbo_move_float_to_pos(me.curPos.x);
					curPos.y = dbo_move_float_to_pos(me.curPos.y);
					curPos.z = dbo_move_float_to_pos(me.curPos.z);
					res.vCurLoc = curPos;
					res.unknown = 0;

					//printf("You are Weak i not Going Follow You Anymore \n");
					newPos.x = dbo_move_float_to_pos(me.Spawn_Loc.x);
					newPos.y = dbo_move_float_to_pos(me.Spawn_Loc.y);
					newPos.z = dbo_move_float_to_pos(me.Spawn_Loc.z);
					res.avDestLoc[0] = newPos;

					//Relocate(dbo_move_pos_to_float(newPos.x), dbo_move_pos_to_float(newPos.y), dbo_move_pos_to_float(newPos.z), me.Spawn_Dir.x, me.Spawn_Dir.y, me.Spawn_Dir.z);

					SendToPlayerList((char*)&res, sizeof(sGU_CHAR_DEST_MOVE));

					GetState()->sCharStateBase.vCurLoc.x = dbo_move_pos_to_float(newPos.x);
					GetState()->sCharStateBase.vCurLoc.y = dbo_move_pos_to_float(newPos.y);
					GetState()->sCharStateBase.vCurLoc.z = dbo_move_pos_to_float(newPos.z);
					me.curPos = GetState()->sCharStateBase.vCurLoc;
				}
				//Send Move to Target 
				if (GetIsDead() == false  && me.GotAgro == true && me.target == plr->GetHandle())
				{					
					if (GetState()->sCharStateBase.vCurLoc.x != plr->GetState()->sCharStateBase.vCurLoc.x - RandValue && GetState()->sCharStateBase.vCurLoc.z != plr->GetState()->sCharStateBase.vCurLoc.z - RandValue)
					{							
						RandValue = rand() % 3;
						sGU_CHAR_DEST_MOVE res;
						memset(&res, 0, sizeof(sGU_CHAR_DEST_MOVE));

						res.wOpCode = GU_CHAR_DEST_MOVE;
						res.byMoveFlag = NTL_MOVE_FLAG_RUN;
						res.wPacketSize = sizeof(sGU_CHAR_DEST_MOVE) - 2;
						res.handle = GetHandle();
						res.byDestLocCount = 1;
						res.bHaveSecondDestLoc = true;
						dVECTOR3 curPos, newPos;

						curPos.x = dbo_move_float_to_pos(me.curPos.x);
						curPos.y = dbo_move_float_to_pos(me.curPos.y);
						curPos.z = dbo_move_float_to_pos(me.curPos.z);
						res.vCurLoc = curPos;
						res.unknown = 0;

						
					//	printf("Im Going Fuk You \n");
						newPos.x = dbo_move_float_to_pos(plr->GetVectorPosition().x - RandValue);
						newPos.y = dbo_move_float_to_pos(plr->GetVectorPosition().y);
						newPos.z = dbo_move_float_to_pos(plr->GetVectorPosition().z - RandValue);
						res.avDestLoc[0] = newPos;
						
						//Relocate(dbo_move_pos_to_float(newPos.x), dbo_move_pos_to_float(newPos.y), dbo_move_pos_to_float(newPos.z), me.Spawn_Dir.x, me.Spawn_Dir.y, me.Spawn_Dir.z);

						SendToPlayerList((char*)&res, sizeof(sGU_CHAR_DEST_MOVE));
						
						GetState()->sCharStateBase.vCurLoc.x = dbo_move_pos_to_float(newPos.x);
						GetState()->sCharStateBase.vCurLoc.y = dbo_move_pos_to_float(newPos.y);
						GetState()->sCharStateBase.vCurLoc.z = dbo_move_pos_to_float(newPos.z);
						me.curPos = GetState()->sCharStateBase.vCurLoc;									
											
					}
					//Send Auto attack
					if (dist <= (me.Attack_range + 3) && GetIsDead() == false && plr->GetIsDead() == false && plr->GetIsFlying() == false && me.target == plr->GetHandle())
					{


						DWORD SkillMob = GetTickCount() - MobSkill;
						if (SkillMob >= 25000)
						{
							int rasdand = rand() % 6;
							SkillTable * skillTable = sTBM.GetSkillTable();
							sSKILL_TBLDAT * skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(me.use_Skill_Tblidx[rasdand]));
							if (skillDataOriginal != NULL)
							{
								switch (skillDataOriginal->bySkill_Active_Type)
								{
									case eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DD:
									{
										sGU_CHAR_ACTION_SKILL skillRes;
										memset(&skillRes, 0, sizeof(sGU_CHAR_ACTION_SKILL));
										skillRes.wPacketSize = sizeof(sGU_CHAR_ACTION_SKILL) - 2;
										skillRes.wOpCode = GU_CHAR_ACTION_SKILL;
										skillRes.wResultCode = GAME_SUCCESS;
										skillRes.handle = me.UniqueID;
										skillRes.hAppointedTarget = plr->GetHandle();
										skillRes.skillId = skillDataOriginal->tblidx;
										skillRes.dwLpEpEventId = skillDataOriginal->tblidx;
										skillRes.byRpBonusType = 255;
										skillRes.bIsSkillHarmful = false;

										skillRes.aSkillResult[0].hTarget = plr->GetHandle();
										skillRes.aSkillResult[0].byAttackResult = BATTLE_ATTACK_RESULT_HIT;

										skillRes.aSkillResult[0].effectResult[0].eResultType = DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT;
										skillRes.aSkillResult[0].effectResult[0].Value1 = skillDataOriginal->SkillValue[0] + me.Basic_physical_Offence;
										skillRes.aSkillResult[0].effectResult[0].Value2 = 0;
										skillRes.aSkillResult[0].effectResult[0].Value3 = 0;
										skillRes.aSkillResult[0].effectResult[0].Value4 = 0;
										skillRes.aSkillResult[0].effectResult[0].Value5 = 0;
										skillRes.aSkillResult[0].effectResult[0].Value6 = 0;
										skillRes.aSkillResult[0].byBlockedAction = 255;
										//skillRes.aSkillResult[count].vShift = PlayerInfo->GetVectorPosition();
										//skillRes.aSkillResult[count].vShift1 = PlayerInfo->GetVectorPosition();
										skillRes.bySkillResultCount = 1;
										plr->TakeMobDemage(skillRes.aSkillResult[0].effectResult[0].Value1);
										SendToPlayerList((char*)&skillRes, sizeof(sGU_CHAR_ACTION_SKILL));
										break;
									}
									case eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DOT:
									{
										BuffTypeSkill pBuffData;
										memset(&pBuffData, 0, sizeof(BuffTypeSkill));
										pBuffData.OpCode = GU_BUFF_REGISTERED;
										pBuffData.size = sizeof(BuffTypeSkill) - 2;
										pBuffData.tblidx = INVALID_TBLIDX;
										
										pBuffData.hHandle = plr->GetHandle();
										//pBuffData.slot = 1;
										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

										//float BleedDemage = DemageValue[i] / 3.5;
										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[0].SystemEffectValue = skillDataOriginal->SkillValue[0];
										pBuffData.BuffInfo[0].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.BuffInfo[0].dwSystemEffectValue = skillDataOriginal->SkillValue[0];

										if (pBuffData.BuffInfo[0].dwSystemEffectValue <= 0 || pBuffData.BuffInfo[0].dwSystemEffectValue > 1000000)
										{
											pBuffData.BuffInfo[0].SystemEffectValue = skillDataOriginal->SkillValue[0];
											pBuffData.BuffInfo[0].dwSystemEffectValue = skillDataOriginal->SkillValue[0];
										}
										if (pBuffData.hHandle != 0 || pBuffData.hHandle != INVALID_TBLIDX)
										{
											SendToPlayerList((char*)&pBuffData, sizeof(BuffTypeSkill));
										}
										//Handle Buff Time List
										int FreePlace = 0;
										for (int i = 0; i <= 32; i++)
										{
											if (plr->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || plr->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
											{
												//printf("Regist new buff \n");
												FreePlace = i;
											}

										}
										plr->ExecuteEffectCalculation(pBuffData.tblidx, false);

										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].isAffectPlayer = true;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].EffectType = skillDataOriginal->skill_Effect[0];
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].EffectValue[0] = pBuffData.BuffInfo[0].SystemEffectValue;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].isMob = false;

										break;
									}
									case eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DH:
									{
										break;
									}
									case eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_HOT:
									{
										BuffTypeSkill pBuffData;
										memset(&pBuffData, 0, sizeof(BuffTypeSkill));
										pBuffData.OpCode = GU_BUFF_REGISTERED;
										pBuffData.size = sizeof(BuffTypeSkill) - 2;
										pBuffData.tblidx = INVALID_TBLIDX;

										pBuffData.hHandle = me.UniqueID;
										//pBuffData.slot = 1;
										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

																											 //float BleedDemage = DemageValue[i] / 3.5;
										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[0].SystemEffectValue = skillDataOriginal->SkillValue[0];
										pBuffData.BuffInfo[0].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.BuffInfo[0].dwSystemEffectValue = skillDataOriginal->SkillValue[0];

										if (pBuffData.BuffInfo[0].dwSystemEffectValue <= 0 || pBuffData.BuffInfo[0].dwSystemEffectValue > 1000000)
										{
											pBuffData.BuffInfo[0].SystemEffectValue = skillDataOriginal->SkillValue[0];
											pBuffData.BuffInfo[0].dwSystemEffectValue = skillDataOriginal->SkillValue[0];
										}
										if (pBuffData.hHandle != 0 || pBuffData.hHandle != INVALID_TBLIDX)
										{
											SendToPlayerList((char*)&pBuffData, sizeof(BuffTypeSkill));
										}
										break;
									}
									case eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DB:
									{
										break;
									}
									case eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_BB:
									{
										BuffTypeSkill pBuffData;
										memset(&pBuffData, 0, sizeof(BuffTypeSkill));
										pBuffData.OpCode = GU_BUFF_REGISTERED;
										pBuffData.size = sizeof(BuffTypeSkill) - 2;
										pBuffData.tblidx = INVALID_TBLIDX;

										pBuffData.hHandle = plr->GetHandle();
										//pBuffData.slot = 1;
										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

										 //float BleedDemage = DemageValue[i] / 3.5;
										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[0].SystemEffectValue = skillDataOriginal->SkillValue[0];
										pBuffData.BuffInfo[0].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.BuffInfo[0].dwSystemEffectValue = skillDataOriginal->SkillValue[0];

										if (pBuffData.BuffInfo[0].dwSystemEffectValue <= 0 || pBuffData.BuffInfo[0].dwSystemEffectValue > 1000000)
										{
											pBuffData.BuffInfo[0].SystemEffectValue = skillDataOriginal->SkillValue[0];
											pBuffData.BuffInfo[0].dwSystemEffectValue = skillDataOriginal->SkillValue[0];
										}
										if (pBuffData.hHandle != 0 || pBuffData.hHandle != INVALID_TBLIDX)
										{
											SendToPlayerList((char*)&pBuffData, sizeof(BuffTypeSkill));
										}
										break;
									}
									case eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_DC:
									{
										break;
									}
									case eSKILL_ACTIVE_TYPE::SKILL_ACTIVE_TYPE_CB:
									{
										BuffTypeSkill pBuffData;
										memset(&pBuffData, 0, sizeof(BuffTypeSkill));
										pBuffData.OpCode = GU_BUFF_REGISTERED;
										pBuffData.size = sizeof(BuffTypeSkill) - 2;
										pBuffData.tblidx = INVALID_TBLIDX;

										pBuffData.hHandle = plr->GetHandle();
										//pBuffData.slot = 1;
										pBuffData.tblidx = skillDataOriginal->tblidx;
										pBuffData.bySourceType = 0;
										pBuffData.dwInitialDuration = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.dwTimeRemaining = skillDataOriginal->dwKeepTimeInMilliSecs;//Time

																											 //float BleedDemage = DemageValue[i] / 3.5;
										pBuffData.isactive = 1;
										pBuffData.Type = 0;
										pBuffData.BuffInfo[0].SystemEffectValue = skillDataOriginal->SkillValue[0];
										pBuffData.BuffInfo[0].SystemEffectTime = skillDataOriginal->dwKeepTimeInMilliSecs;
										pBuffData.BuffInfo[0].dwSystemEffectValue = skillDataOriginal->SkillValue[0];

										if (pBuffData.BuffInfo[0].dwSystemEffectValue <= 0 || pBuffData.BuffInfo[0].dwSystemEffectValue > 1000000)
										{
											pBuffData.BuffInfo[0].SystemEffectValue = skillDataOriginal->SkillValue[0];
											pBuffData.BuffInfo[0].dwSystemEffectValue = skillDataOriginal->SkillValue[0];
										}
										if (pBuffData.hHandle != 0 || pBuffData.hHandle != INVALID_TBLIDX)
										{
											SendToPlayerList((char*)&pBuffData, sizeof(BuffTypeSkill));
										}
										int FreePlace = 0;
										for (int i = 0; i <= 32; i++)
										{
											if (plr->GetAttributesManager()->sBuffTimeInfo[i].BuffID == 0 || plr->GetAttributesManager()->sBuffTimeInfo[i].BuffID == INVALID_TBLIDX)
											{
												//printf("Regist new buff \n");
												FreePlace = i;
											}

										}
										plr->ExecuteEffectCalculation(pBuffData.tblidx, false);

										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffID = pBuffData.tblidx;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffTime = GetTickCount();
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffEndTime = pBuffData.dwInitialDuration;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].PlayerHandle = pBuffData.hHandle;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffIsActive = true;
										plr->GetAttributesManager()->sBuffTimeInfo[FreePlace].BuffSlot = 0;
										break;
									}

								}							

							}
									MobSkill = GetTickCount();
						}



						AttackChain += 1;
						//	SetState(eCHARSTATE::CHARSTATE_STANDING);						
						if (AttackChain >= 3 || AttackChain <= 0)
							AttackChain = BATTLE_CHAIN_ATTACK_START;
						float MonsterAttack = 0;
						float TargetDefese = 0;
						float MonsterHitRate = 0;
						float TargetDodgeRate = 0;
						if (me.Attack_Type == eBATTLE_ATTACK_TYPE::BATTLE_ATTACK_TYPE_PHYSICAL)
						{
							 MonsterAttack = me.Basic_physical_Offence;
							 MonsterAttack += me.Basic_physical_Offence / 100 * me.Str;
							 TargetDefese = plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence;
							 MonsterHitRate = me.Attack_rate;
							 MonsterHitRate += me.Attack_rate / 100 * me.Foc;
							 TargetDodgeRate = plr->GetPcProfile()->avatarAttribute.wLastDodgeRate;
						}
						if (me.Attack_Type == eBATTLE_ATTACK_TYPE::BATTLE_ATTACK_TYPE_ENERGY)
						{
							 MonsterAttack = me.Basic_energy_Offence;
							 MonsterAttack += me.Basic_energy_Offence / 100 * me.Sol;
							 TargetDefese = plr->GetPcProfile()->avatarAttribute.wLastEnergyDefence;
							 MonsterHitRate = me.Attack_rate;
							 MonsterHitRate += me.Attack_rate / 100 * me.Foc;
							 TargetDodgeRate = plr->GetPcProfile()->avatarAttribute.wLastDodgeRate;
						}
						//int TotalAttack = MonsterAttack + TargetDefese;
						//float Attackpercent = MonsterAttack * 100 / TotalAttack;
						//float attackValue = MonsterAttack * Attackpercent / 100;	
						
						float attackValue = MonsterAttack * MonsterAttack / (MonsterAttack + TargetDefese);
						if (attackValue >= 3000)
						{
							attackValue = 2888 + rand() % 200;
						}
						else
						{
							attackValue += me.Level * me.Level / (me.Level  + plr->GetPcProfile()->byLevel);
						}
						int HitRate = plr->GetPcProfile()->avatarAttribute.wLastAttackRate;
						int DodgeRate = me.Attack_rate;
						float TotalHitPercent = HitRate + DodgeRate;
						float TotalHitRatePercent = HitRate * 100 / TotalHitPercent;
						int RandomHit = rand() % 100;
						int attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE;
						if (RandomHit >= TotalHitRatePercent && TotalHitRatePercent > 0)					
						{							
							attackResult = eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_HIT;							
						}					
						
						sGU_CHAR_ACTION_ATTACK res;
						res.wOpCode = GU_CHAR_ACTION_ATTACK;
						res.wPacketSize = sizeof(sGU_CHAR_ACTION_ATTACK) - 2;

						int guardType = eDBO_GUARD_TYPE::DBO_GUARD_TYPE_INVALID;
						int reflectedDamage = 0;

						res.bChainAttack = true;
						res.byAttackResult = attackResult;
						res.byBlockedAction = guardType;
						res.dwLpEpEventId = 0;
						res.fReflectedDamage = reflectedDamage;
						res.byAttackSequence = AttackChain;
						res.hSubject = me.UniqueID;
						res.hTarget = plr->GetHandle();
						res.vShift = GetVectorPosition();
						res.wAttackResultValue = attackValue;
						res.bRecoveredLP = false;
						res.wRecoveredLpValue = 0;
						res.bRecoveredEP = false;
						res.wRecoveredEpValue = 0;

					//	printf("Take thi MutherFuker \n");						
						SendToPlayerList((char*)&res, sizeof(sGU_CHAR_ACTION_ATTACK));
						
						if (attackResult != eBATTLE_ATTACK_RESULT::BATTLE_ATTACK_RESULT_DODGE)
						{
							//if (attackers == 0)
							//attackers = me.UniqueID;
							plr->TakeMobDemage(res.wAttackResultValue);
							
						}
					}
				}	
			}
		}
	}	
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
		sGU_UPDATE_CHAR_EP updEp;
		updEp.handle = GetHandle();
		updEp.wCurEP = me.CurEP;
		updEp.wMaxEP = me.MaxEP;
		updEp.wOpCode = GU_UPDATE_CHAR_EP;
		updEp.wPacketSize = sizeof(sGU_UPDATE_CHAR_EP) - 2;

		SendToPlayerList((char*)&updEp, sizeof(sGU_UPDATE_CHAR_EP));
	}
	if (me.CurLP < me.MaxLP)
	{
		me.CurLP += me.Lp_Regeneration;
		if (me.CurLP > me.MaxLP)
			me.CurLP = me.MaxLP;
		sGU_UPDATE_CHAR_LP updLp;
		updLp.handle = GetHandle();
		updLp.wCurLP = me.CurLP;
		updLp.wMaxLP = me.MaxLP;
		updLp.wOpCode = GU_UPDATE_CHAR_LP;
		updLp.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;

		SendToPlayerList((char*)&updLp, sizeof(sGU_UPDATE_CHAR_LP));
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
//	Calcule physical critical defence
//----------------------------------------
WORD Mob::CalculePhysicalCriticalDefenceRate(int lastCon)
{
	// = fRate1 + (Last_Con / fRate2)
	WORD criticalDefenseRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(9300);
	if (formula)
	{
		//sLog.outBasic("MonsterPhysicalCriticalDefenseRate tblidx %d lastCon %d", formula->tblidx, lastCon);
		criticalDefenseRate = formula->afRate[0] + (lastCon / formula->afRate[1]);
		//sLog.outBasic("MonsterPhysicalCriticalDefenseRate total %d rate1 %f rate2 %f", criticalDefenseRate, formula->afRate[0], formula->afRate[1]);
	}
	return criticalDefenseRate;
}
//----------------------------------------
//	Calcule energy critical defence
//----------------------------------------
WORD Mob::CalculeEnergyCriticalDefenceRate(int lastEng)
{
	// = fRate1 + (Last_Con / fRate2)
	WORD criticalDefenseRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(9400);
	if (formula)
	{
		//sLog.outBasic("MonsterEnergyCriticalDefenseRate tblidx %d lastEng %d", formula->tblidx, lastEng);
		criticalDefenseRate = formula->afRate[0] + (lastEng / formula->afRate[1]);
		//sLog.outBasic("MonsterEnergyCriticalDefenseRate total %d rate1 %f rate2 %f", criticalDefenseRate, formula->afRate[0], formula->afRate[1]);
	}
	return criticalDefenseRate;
}
//----------------------------------------
//	Calcule Block Rate
//----------------------------------------
WORD Mob::CalculeBlockRate(int lastDex, int lastCon)
{
	// = fRate1 + (Last_Dex * fRate2) + (Last_Con * fRate3)
	WORD blockRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(919);
	if (formula)
	{
		blockRate = formula->afRate[0] + (lastDex * formula->afRate[1]) + (lastCon * formula->afRate[2]);
	}
	return blockRate;
}
//----------------------------------------
//	Calcule Block Damage Rate
//----------------------------------------
WORD Mob::CalculeBlockDamageRate(int lastDex, int lastCon)
{
	// = fRate1 + (Last_Dex * fRate2) + (Last_Con * fRate3)
	WORD blockDamageRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(4819);
	if (formula)
	{
		blockDamageRate = formula->afRate[0] + (lastDex * formula->afRate[1]) + (lastCon * formula->afRate[2]);
	}
	return blockDamageRate;
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
	if (newLife <= 0 || newLife > 1000000000)
	{
		SetIsDead(true);
		SetIsFighting(false);
		me.isAggro = false;
		me.GotAgro = false;
		me.target = INVALID_TBLIDX;
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
//	Send the new mob state as Death
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
				BossEventRandom = rand() % 10;
				float dist = NtlGetDistance(me.curPos.x, me.curPos.z, plr->GetVectorPosition().x, plr->GetVectorPosition().z);
				if (dist <= 100)
				{
					if (sWorld.BossEventMajinCurCount <= sWorld.BossEventMajinMaxCount && me.MonsterID == 11253101)
					{
						sWorld.BossEventMajinCurCount += 1;
					}
					if (sWorld.BossEventMajinCurCount <= sWorld.BossEventMajinMaxCount && me.MonsterID == 11261104)
					{
						sWorld.BossEventMajinCurCount += 1;
					}
					if (BossEventRandom == 4 && sWorld.BossEventMajinCurCount <= sWorld.BossEventMajinMaxCount && plr->GetPcProfile()->byLevel >= 40 && me.Level >= 40 && me.Level <= 49)
					{
						plr->SpawnMobByID(11253101,me.curPos,me.Spawn_Dir);
						BossEventRandom = rand() % 100;
					}
					if (BossEventRandom == 8 && sWorld.BossEventMajinCurCount <= sWorld.BossEventMajinMaxCount && plr->GetPcProfile()->byLevel >= 50 && me.Level >= 50 && me.Level <= 100)
					{
						plr->SpawnMobByID(11261104, me.curPos, me.Spawn_Dir);
						BossEventRandom = rand() % 100;
					}

					if (sWorld.ActiveEventBoss== true && me.MonsterID == 14351201)
					{
						plr->SpawnNpcByID(2413115, me.curPos, me.Spawn_Dir);
						sWorld.BossNpcTimeDespawn = 60000;//5min NPC go Off
						sWorld.BossNpcTimeDespawns = GetTickCount();
						sWorld.NpcIsSpawed = true;
						sWorld.SendAnnounce("Boss Is Killed At Yellow Map" + plr->GetName());
					}
					if (sWorld.ActiveEventBoss == true && me.MonsterID == 11151101)
					{
						plr->SpawnNpcByID(2413121, me.curPos, me.Spawn_Dir);
						sWorld.BossNpcTimeDespawn = 60000;//5min NPC go Off
						sWorld.BossNpcTimeDespawns = GetTickCount();
						sWorld.NpcIsSpawed = true;
						sWorld.SendAnnounce("Boss Is Killed At Red Map" + plr->GetName());
					}
					for (int i = 0; i <= 12; i++)
					{
						if (sWorld.Boss_Info[i].Handle == me.UniqueID)
						{
							printf("Delet Boss On List");
							sWorld.Boss_Info[i].Handle = INVALID_TBLIDX;
							sWorld.BossSpawnCount -= 1;							
						}
					}
					
					plr->SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
					if (attackers == plr->GetHandle())
					{
						plr->RewardExpFromMob(me);
						plr->RewardDropFromMob(me);
						plr->RewardDropFromBossEvent(me);
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
		int BallRandom = rand() % 100;
		if (BallRandom >= 0 && BallRandom <= 25)
		{
			me.ByDagonBall = 1;
		}
		else
			me.ByDagonBall = 0;
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
	memset(&res, 0, sizeof sGU_UPDATE_CHAR_STATE);

	res.wOpCode = GU_UPDATE_CHAR_STATE;
	res.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;

	memcpy(&res.sCharState, GetState(), sizeof sCHARSTATE);

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
