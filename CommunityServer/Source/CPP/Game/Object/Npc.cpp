#include <Game\Object\Npc.h>
#include <Game\Object\Player.h>
#include <Community.h>
#include <Packet\Community\PacketTU.h>

//----------------------------------------
//	Npc Constructor
//----------------------------------------
Npc::Npc() : Object()
{
	m_objectType = eOBJTYPE::OBJTYPE_NPC;
}
//----------------------------------------
//	Npc Destructor
//----------------------------------------
Npc::~Npc()
{
	CleanupsBeforeDelete();
}
//----------------------------------------
//	Remove that NPC From World
//----------------------------------------
void Npc::CleanupsBeforeDelete()
{
	Object::RemoveFromWorld();
}
//----------------------------------------
//	Add that NPC to World
//----------------------------------------
void Npc::AddToWorld()
{
	Object::AddToWorld();
}
//----------------------------------------
//	Remove from world
//----------------------------------------
void Npc::RemoveFromWorld()
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
NpcReference &Npc::GetMapRef()
{
	return m_NpcRef;
}
//----------------------------------------
//	Create the NPC Spawn Packet
//----------------------------------------
void Npc::BuildPacketForSpawn(SpawnNPC& spawnData)
{
	memset(&spawnData, 0, sizeof(SpawnNPC));

	spawnData.wOpCode = GU_OBJECT_CREATE;
	spawnData.wPacketSize = sizeof(SpawnNPC) - 2;
	
//	spawnData.AspectID = 0;
//	spawnData.BurnEffect = 0;
	spawnData.CurEP = me.CurEP;
	spawnData.CurLP = me.CurLP;
	spawnData.Handle = GetHandle();
//	spawnData.Level = me.Level;
	spawnData.MaxEP = me.MaxEP;
	spawnData.MaxLP = me.MaxLP;
//	spawnData.ModelSize = 10;
	spawnData.OBJType = OBJTYPE_NPC;
//	spawnData.PoisonEffect = 0;
//	spawnData.Position.x = me.curPos.x;
//	spawnData.Position.y = me.curPos.y;
//	spawnData.Position.z = me.curPos.z;
//	spawnData.Rotation.x = me.Spawn_Dir.x;
//	spawnData.Rotation.y = me.Spawn_Dir.y;
//	spawnData.Rotation.z = me.Spawn_Dir.z;
//	spawnData.StateID = eCHARSTATE::CHARSTATE_SPAWNING;
	spawnData.Tblidx = me.MonsterID;

//	spawnData.Unknown2 = 0;
//	for (int i = 0; i < 2; i++) spawnData.Unknown[i] = 0;
//	for (int i = 0; i < 3; i++) spawnData.Unknown3[i] = 0;
//	for (int i = 0; i < 6; i++) spawnData.Unknown4[i] = 0;
//	for (int i = 0; i < 10; i++) spawnData.Unknown5[i] = 0;
}
//----------------------------------------
//	Create the NPC and fill all info
//----------------------------------------
bool Npc::Create(sSPAWN_TBLDAT* spawnTbl, sNPC_TBLDAT* npcTbl)
{
	me.MonsterID = npcTbl->tblidx;
	SetIsDead(false);
	SetIsBecomeMob(false);
	SetIsFighting(false);
	me.ShowName = true;
	me.SpawnAnimation = true;

	me.Grade;
	me.Property;
	me.Drop_each_id;
	me.Drop_quest_id;
	me.Drop_type_id;
	me.Drop_item_id;
	me.Mob_group;
	me.Exp;
	me.Mob_Kind;
	me.Sight_angle;
	me.TMQ_Point;
	me.DropEachRateControl;
	me.DropEItemRateControl;
	me.DropLItemRateControl;
	me.DropNItemRateControl;
	me.DropSItemRateControl;
	me.DropTypeRateControl;
	me.DisplayID;

	me.target = INVALID_TBLIDX;
	me.StateID = eCHARSTATE::CHARSTATE_SPAWNING;
	me.ConditionFlag = 0;
	me.Job = npcTbl->byJob;
	me.Con = npcTbl->byCon;
	me.Dex = npcTbl->byDex;
	me.Eng = npcTbl->byEng;
	me.Foc = npcTbl->byFoc;
	me.Sol = npcTbl->bySol;
	me.Str = npcTbl->byStr;
	me.Attack_Animation_Qty = npcTbl->byAttack_Animation_Quantity;
	me.Attack_Type = npcTbl->byAttack_Type;
	me.Battle_Attribute = npcTbl->byBattle_Attribute;
	me.HtbBlockRate = npcTbl->wBlock_Rate;
	me.Level = npcTbl->byLevel;
	me.Mob_type = npcTbl->byNpcType; // need check
	me.Scan_range = npcTbl->byScan_Range;
	me.Sight_range = npcTbl->bySight_Range;
	*me.Use_skill_basis = *npcTbl->byUse_Skill_Basis;
	me.Ai_bit_flag = npcTbl->dwAi_Bit_Flag;
	me.AllianceID = npcTbl->dwAllianceIdx;
	me.DialogGroup = npcTbl->dwDialogGroup;
	me.Drop_Zenny;
	me.Attack_range = npcTbl->fAttack_Range;
	me.Drop_zenny_rate;
	me.Fly_height = npcTbl->fFly_Height;
	me.Radius = npcTbl->fRadius;
	me.Radius_x = npcTbl->fRadius_X;
	me.Radius_z = npcTbl->fRadius_Z;
	me.Run_Speed = npcTbl->fRun_Speed;
	me.Run_Speed_origin = npcTbl->fRun_Speed_Origin;
	me.Scale = npcTbl->fScale;
	me.Walk_Speed = npcTbl->fWalk_Speed;
	me.Walk_Speed_origin = npcTbl->fWalk_Speed_Origin;
	me.Name = npcTbl->Name;
	me.CurLP = npcTbl->wBasic_LP;
	me.CurEP = npcTbl->wBasic_EP;
	me.MaxLP = npcTbl->wBasic_LP;
	me.MaxEP = npcTbl->wBasic_EP;
	me.AttackSpeedRate = npcTbl->wAttack_Speed_Rate;
	me.use_Skill_Tblidx[6 + 1];
	me.Aggro_max_count = npcTbl->wAggroMaxCount;
	me.Attack_cool_time = npcTbl->wAttackCoolTime;
	me.Attack_rate = npcTbl->wAttack_Rate;
	me.Attack_speed_rate = npcTbl->wAttack_Speed_Rate;
	me.Basic_aggro_point = npcTbl->wBasic_Aggro_Point;
	me.Basic_energy_defence = npcTbl->wBasic_Energy_Defence;
	//me.Basic_Offence = npcTbl->wBasic_Offence;
	me.Basic_physical_defence = npcTbl->wBasic_Physical_Defence;
	me.Block_rate = npcTbl->wBlock_Rate;
	me.Curse_success_rate = npcTbl->wCurse_Success_Rate;
	me.Curse_tolerance_rate = npcTbl->wCurse_Tolerance_Rate;
	me.Dodge_rate = npcTbl->wDodge_Rate;
	me.Ep_Regeneration = npcTbl->wEP_Regeneration;
	me.Lp_Regeneration = npcTbl->wLP_Regeneration;
	*me.Use_skill_Lp = *npcTbl->wUse_Skill_LP;
	*me.Use_skill_time = *npcTbl->wUse_Skill_Time;
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
	me.KilledTime = 0;
	me.isSpawned = false;
	me.isAggro = false;
	me.curPos = spawnTbl->vSpawn_Loc;
	me.chainAttackCount = 0;
	me.MaxchainAttackCount = 0;
	for (int i = 0; i < 6; i++)
		me.amerchant_Tblidx[i] = npcTbl->amerchant_Tblidx[i]; // hard fix
	handle = me.UniqueID = sCommunity.AcquireSerialId();

	Relocate(me.curPos.x, me.curPos.y, me.curPos.z, me.Spawn_Dir.x, me.Spawn_Dir.y, me.Spawn_Dir.z);
	AddToWorld();

	return true;
}
//----------------------------------------
//	Remove from world
//----------------------------------------
void Npc::Update(uint32 update_diff, uint32 time)
{

}
//----------------------------------------
//	Set if npc is become a mob
//----------------------------------------
void Npc::SetIsBecomeMob(bool val)
{
	isBecomeMob = val;
}
//----------------------------------------
//	Get if npc is become a mob
//----------------------------------------
bool Npc::GetIsBecomeMob()
{
	return isBecomeMob;
}
//----------------------------------------
//	Return the npc struct filled
//----------------------------------------
MonsterData Npc::GetNpcData() const
{
	return me;
}
void Npc::TakeDamage(uint32 amount)
{
}
//----------------------------------------
//		GETTER
//----------------------------------------
DWORD Npc::GetPowerLevel()
{
	return Dbo_CalculatePowerLevel(me.Str, me.Con, me.Foc, me.Dex, me.Sol, me.Eng,
		me.Basic_physical_Offence, me.Basic_physical_defence, me.Basic_energy_Offence, me.Basic_energy_defence, me.Attack_rate, me.Dodge_rate,
		me.Curse_success_rate, me.Curse_tolerance_rate, /*CRITICAL ?*/ 0, 0, me.AttackSpeedRate, me.MaxLP, me.MaxEP, me.CurLP,
		me.CurEP, BYTE(0), me.Level, me.Grade);
}

//----------------------------------------
//	Tell everyone the character state changed
//----------------------------------------
void Npc::UpdateState(eCHARSTATE _state)
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

	res.sCharState.sCharStateBase.dwConditionFlag = GetState()->sCharStateBase.dwConditionFlag;
	res.sCharState.sCharStateBase.dwStateTime = GetState()->sCharStateBase.dwStateTime;

	GetState()->sCharStateBase.isFighting = GetIsFighting();


	GetState()->sCharStateBase.isFlying = false;

	for (auto it = m_NpcRef.getTarget()->GetPlayers().begin(); it != m_NpcRef.getTarget()->GetPlayers().end(); ++it)
	{
		if (it->getSource())
		{
			Player* plr = it->getSource();
			if (plr->IsInWorld() == true && plr->GetSession() != NULL)
			{
				float dist = NtlGetDistance(me.curPos.x, me.curPos.z, plr->GetVectorPosition().x, plr->GetVectorPosition().z);
				if (dist <= 100)
					plr->SendPacket((char*)&res, sizeof(sGU_UPDATE_CHAR_STATE));
			}
		}
	}
}
