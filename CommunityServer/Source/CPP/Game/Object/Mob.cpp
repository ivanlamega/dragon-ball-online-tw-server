#include <Game\Object\Mob.h>
#include <Community.h>
#include <Packet\Community\PacketTU.h>
#include <Game\Object\Player.h>
#include <Logger.h>

bool hasmoved = false;
//----------------------------------------
//	Mob Constructor
//----------------------------------------
Mob::Mob() : Object()
{
	m_objectType = eOBJTYPE::OBJTYPE_MOB;
	lastMoveTime = 0;
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
	spawnData.fLastRunningSpeed = 4;
	spawnData.fLastAirgSpeed = 4;
	spawnData.fLastAirgDashSpeed = 4;
	spawnData.fLastAirgDashAccelSpeed = 4;

	spawnData.byBallType = me.ByDagonBall;

	GetState()->sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;
	GetState()->sCharStateBase.vCurLoc.x = me.curPos.x;
	GetState()->sCharStateBase.vCurLoc.y = me.curPos.y;
	GetState()->sCharStateBase.vCurLoc.z = me.curPos.z;
	GetState()->sCharStateBase.vCurDir.x = me.Spawn_Dir.x;
	GetState()->sCharStateBase.vCurDir.y = me.Spawn_Dir.y;
	GetState()->sCharStateBase.vCurDir.z = me.Spawn_Dir.z;
	GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;

	memcpy(&spawnData.State.sCharStateBase, &GetState()->sCharStateBase, sizeof(sCHARSTATE_BASE));
	memcpy(&spawnData.State.sCharStateDetail, &GetState()->sCharStateDetail, sizeof(sCHARSTATE_DETAIL));
}
//----------------------------------------
//	Create the mob and fill all info
//----------------------------------------
bool Mob::Create(sSPAWN_TBLDAT* spawnTbl, sMOB_TBLDAT* mobTbl)
{
	me.MonsterID = mobTbl->tblidx;
	SetIsFighting(false);
	me.ShowName = true;
	me.SpawnAnimation = true;

	me.Grade = mobTbl->byGrade;
	me.Property;// = mobTbl->byProperty;
//	me.Drop_each_id = mobTbl->dropEachTblidx;
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
//	me.Drop_Zenny = mobTbl->dwDrop_Zenny;
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
//	me.Basic_Offence = mobTbl->wBasic_Offence;
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
	handle = me.UniqueID = sCommunity.AcquireSerialId();

	Relocate(me.curPos.x, me.curPos.y, me.curPos.z, me.Spawn_Dir.x, me.Spawn_Dir.y, me.Spawn_Dir.z);

	if (me.Grade != eMOB_GRADE::MOB_GRADE_HERO && me.Grade != eMOB_GRADE::MOB_GRADE_ULTRA)
	{
		AddToWorld();
		me.isSpawned = true;
	}
	
	respawnTime = me.Spawn_Cool_Time;
	/*if (me.Grade >= eMOB_GRADE::MOB_GRADE_SUPER)
	{
		respawnTime = rand() % 1000 + 500;
	}*/
	return true;
}
//----------------------------------------
//	Remove from world
//----------------------------------------
void Mob::Update(uint32 update_diff, uint32 time)
{
	if (GetIsDead() == false)
	{
		Regen();
		//MoveToPoint();
	}
	else
	{
		Respawn();
	}
}
//----------------------------------------
//	Move the mob to a point (this point should be determined with path point table)
//----------------------------------------
void Mob::MoveToPoint()
{
	lastMoveTime += 1;
	if (lastMoveTime < randMove || me.isAggro == true && hasmoved == false)
		return;
	
	sGU_UPDATE_CHAR_STATE res;
	sGU_CHAR_DEST_MOVE movement;

	memset(&movement, 0, sizeof(sGU_CHAR_DEST_MOVE));

	movement.wOpCode = GU_CHAR_DEST_MOVE;
	movement.wPacketSize = sizeof(sGU_CHAR_DEST_MOVE) - 2;

	movement.handle = GetHandle();

	movement.vCurLoc.x = me.Spawn_Loc.x;
	movement.vCurLoc.y = me.Spawn_Loc.y;
	movement.vCurLoc.z = me.Spawn_Loc.z;

	movement.byMoveFlag = MOVE_FLAG_DESTMOVE;
	movement.bHaveSecondDestLoc = false;

	movement.vSecondDestLoc.x = me.Spawn_Loc.x;
	movement.vSecondDestLoc.y = me.Spawn_Loc.y;
	movement.vSecondDestLoc.z = me.Spawn_Loc.z;

	movement.byDestLocCount = 1;

	movement.avDestLoc[0].x = me.Spawn_Loc.x + rand() % 3;
	movement.avDestLoc[0].y = me.Spawn_Loc.y;
	movement.avDestLoc[0].z = me.Spawn_Loc.z + rand() % 3;
	for (int i = 1; i < 10; i++)movement.avDestLoc[i] = movement.avDestLoc[0];

	SendToPlayerList((char*)&movement, sizeof(sGU_CHAR_DEST_MOVE));
	lastMoveTime = 0;
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
				float dist = NtlGetDistance(me.curPos.x, me.curPos.z, plr->GetVectorPosition().x, plr->GetVectorPosition().z);
				if (dist <= 100)
				{
					plr->SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
					if (attackers == plr->GetHandle())
					{
	//					plr->RewardExpFromMob(me);
		//				plr->RewardDropFromMob(me);
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
		me.Basic_physical_Offence, me.Basic_physical_defence, me.Basic_energy_Offence, me.Basic_energy_defence, me.Attack_rate, me.Dodge_rate,
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
