#include <Game\Object\Player.h>
#include <WorldSession.h>
#include <World.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <Packet\Game\PacketGU.h>
#include <Game\Maps\MapManager.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Npc.h>

//----------------------------------------
//	Player Constructor, init all info
//----------------------------------------
Player::Player(WorldSession* session) : Object()
{
	attackCount = 0;
	WorldId = 0;
	WorldTableID = 0;
	m_session = session;
	charid = INVALID_CHARACTERID;
	objList.clear();
	moveDirection = 0;
	m_name = "";
	isLowLifeSend = false;
	m_currMap = nullptr;
	cur_target = 0;
	m_objectType = eOBJTYPE::OBJTYPE_PC;
	cur_obj_tagert = NULL;
	isMovingToCharServer = false;
	rpBallTimer = 0;
}


//----------------------------------------
//	Player Destructor, Remove it from world and clean the list
//----------------------------------------
Player::~Player()
{
	CleanupsBeforeDelete();
	objList.clear();
	for (auto it = DropList.begin(); it != DropList.end(); it++)
	{
		if (it->second != NULL)
			delete it->second;
	}
	DropList.clear();
	cur_obj_tagert = nullptr;
	m_session = nullptr;
}
//----------------------------------------
//	Remove from World
//----------------------------------------
void Player::CleanupsBeforeDelete()
{
	RemoveFromWorld();
}
//----------------------------------------
//	Add to world
//----------------------------------------
void Player::AddToWorld()
{
	///- Do not add/remove the player from the object storage
	///- It will crash when updating the ObjectAccessor
	///- The player should only be added when logging in
	Object::AddToWorld();
}
//----------------------------------------
//	Remove from world
//----------------------------------------
void Player::RemoveFromWorld()
{
	// cleanup
	if (IsInWorld())
	{
		///- Release charmed creatures, unsummon totems and remove pets/guardians
		ClearListAndReference();
	}
	Object::RemoveFromWorld();
}
//----------------------------------------
//	Remove all entity from our list and remove us from any list
//----------------------------------------
void Player::ClearListAndReference()
{
	mutexPlayer.lock();
	for (auto it = objList.begin(); it != objList.end();)
	{
		if (it->second != NULL)
		{
			if (it->second->GetTypeId() == OBJTYPE_PC)
			{
				Player* plr = static_cast<Player*>(it->second);
				plr->RemoveFromList(*this);
			}
			it++;
		}
	}
	objList.clear();
	mutexPlayer.unlock();
}
//----------------------------------------
//	Remove from world
//----------------------------------------
void Player::SendPacket(char* data, size_t size)
{
	if (GetSession() != NULL)
	{
		GetSession()->SendPacket(data, size);
	}
}
//------------------------------------------
//		SAVE OUR PLAYER
//------------------------------------------
void Player::SavePlayer()
{	
		GetInventoryManager()->SaveInventory();
		//skillManager.SaveSkill(*this);
		sDB.SavePlayerPositionAndWorldID(GetVectorPosition(), GetVectorOriantation(), GetWorldID(), GetWorldTableID(), GetCharacterID());
		sDB.SavePlayerLife(GetPcProfile()->dwCurLP, GetPcProfile()->wCurEP, GetCharacterID());
		sDB.SaveTitleMarket( GetPcProfile()->sMarking.dwCode, GetCharacterID());
		// do we need to save attributes as we load them at start ?
	
}
//------------------------------------------
//		SETTER
//------------------------------------------

void Player::SetMoveDirection(BYTE movementDirection)
{
	GetState()->sCharStateDetail.sCharStateMoving.byMoveDirection = movementDirection;
}
void Player::SetSession(WorldSession* s)
{
	m_session = s;
}
void Player::SetName(char* name)
{ 
	m_name = name;
}
void Player::SetIsFighting(bool val)
{ 
	isfighting = val;
}
void Player::SetFlying(bool val)
{
	isFlying = val;
}
void Player::SetWorldID(WORLDID id) 
{ 
	WorldId = id;
}
void Player::SetWorldTableID(TBLIDX id) 
{ 
	WorldTableID = id;
}
void Player::SetMap(Map* m)
{
	m_currMap = m;
	WorldId = m->GetId();
}
void Player::ResetMap()
{
	//WorldId = 0;
	m_currMap = nullptr;
}
void Player::SetTarget(HOBJECT hSerial)
{
	cur_target = hSerial;
	cur_obj_tagert = GetFromList(hSerial);
}
void Player::SetMyClass(ePC_CLASS _class)
{
	myClass = _class;
	GetAttributesManager()->PlayerClassID = _class;
}
void Player::SetMoveDestinationLocation(sVECTOR3 pos)
{
	m_destination_pos = pos;
}
//----------------------------------------
//		GETTER
//----------------------------------------
DWORD Player::GetPowerLevel()
{
	return Dbo_CalculatePowerLevel(GetPcProfile()->avatarAttribute.byLastStr, GetPcProfile()->avatarAttribute.byLastCon, GetPcProfile()->avatarAttribute.byLastFoc, GetPcProfile()->avatarAttribute.byLastDex,
	GetPcProfile()->avatarAttribute.byLastSol, GetPcProfile()->avatarAttribute.byLastEng, GetPcProfile()->avatarAttribute.wLastPhysicalOffence, GetPcProfile()->avatarAttribute.wLastPhysicalDefence, GetPcProfile()->avatarAttribute.wLastEnergyOffence,
	GetPcProfile()->avatarAttribute.wLastEnergyDefence, GetPcProfile()->avatarAttribute.wLastAttackRate, GetPcProfile()->avatarAttribute.wLastDodgeRate, GetPcProfile()->avatarAttribute.wLastCurseSuccessRate,
	GetPcProfile()->avatarAttribute.wLastCurseToleranceRate, GetPcProfile()->avatarAttribute.wLastPhysicalCriticalRate, GetPcProfile()->avatarAttribute.wLastEnergyCriticalRate, GetPcProfile()->avatarAttribute.wLastAttackRate,
	GetPcProfile()->avatarAttribute.wLastMaxLP, GetPcProfile()->avatarAttribute.wLastMaxEP, GetPcProfile()->dwCurLP, GetPcProfile()->wCurEP, 0, GetPcProfile()->byLevel, 0);
}
bool Player::GetIsEmergency()
{
	float current = static_cast<float>(GetPcProfile()->dwCurLP);
	float max = static_cast<float>(GetPcProfile()->avatarAttribute.wBaseMaxLP);
	float percent = current / max;

	return (percent <= 0.25f) ? true : false;
}
sVECTOR3 Player::GetMoveDestinationVector()
{
	return m_destination_pos;
}
InventoryManager	*Player::GetInventoryManager()
{
	return &inventoryManager;
}
AttributesManager *Player::GetAttributesManager()
{
	return &characterManager;
}
ePC_CLASS Player::GetMyClass() const
{
	return myClass;
}
HOBJECT Player::GetTarget() const
{
	return cur_target;
}
WorldSession* Player::GetSession() const
{
	return m_session;
}
CHARACTERID	Player::GetCharacterID()
{
	return charid;
}
sPC_PROFILE	*Player::GetPcProfile()
{
	return characterManager.GetPlayerProfile();
}
MapReference &Player::GetMapRef()
{
	return m_mapRef;
}
sITEM_BRIEF *Player::GetCharEquippedItems()
{
	return inventoryManager.GetEquippedItems();
}
std::string Player::GetGuildName()
{ 
	return GuildName; 
}
eCHARSTATE Player::GetCharEState()
{ 
	return (eCHARSTATE)GetState()->sCharStateBase.byStateID;
}
BYTE Player::GetMoveDirection()
{ 
	return GetState()->sCharStateDetail.sCharStateMoving.byMoveDirection;
}
std::string Player::GetName() 
{ 
	return m_name; 
}
PORTALID Player::GetPortalIdFromList(HOBJECT handle)
{
	mutexPlayer.lock();
	for (auto it = objList.begin(); it != objList.end();)
	{
		if (it->second != NULL)
		{
			if (handle == it->first && it->second->GetTypeId() == OBJTYPE_NPC)
			{
				Npc* npc = reinterpret_cast<Npc*>(it->second);
				for (auto its = sTBM.GetPortalTable()->Begin(); its != sTBM.GetPortalTable()->End(); its++)
				{
					sPORTAL_TBLDAT* portal = (sPORTAL_TBLDAT*)its->second;
					float dist = NtlGetDistance(portal->vLoc.x, portal->vLoc.z, npc->GetNpcData().curPos.x, npc->GetNpcData().curPos.z);
					if (dist <= 100)
					{
						mutexPlayer.unlock();
						return its->second->tblidx;
					}
				}
			}
		}
		it++;
	}
	mutexPlayer.unlock();
	return 255;
}
//----------------------------------------
//	Create player, fill struct and data with database
//----------------------------------------
bool Player::Create(CHARACTERID id)
{
	if (LoadFromDB(id) == false)
	{
		sLog.outError("Player::Create: Error LoadFromDB(id) return false");
		return false;
	}
	if (characterManager.LoadAttributes(charid, this) == false)
	{
		sLog.outError("Player::Create: Error LoadAttributes(charid, this) return false");
		return false;
	}
	if (skillManager.LoadSkill(charid) == false)
	{
		sLog.outError("Player::Create: Error LoadSkill(charid) return false");
		return false;
	}
	if (inventoryManager.LoadInventory(charid, this) == false)
	{
		sLog.outError("Player::Create: Error LoadInventory(charid) return false");
		return false;
	}
	characterManager.LoadAttributesFromItems(inventoryManager.GetEquippedItems());
	characterManager.CreatePlayerBaseAttributesBitFlag();
	handle = sWorld.AcquireSerialId();
	return true;
}
//----------------------------------------
//	Trigger by Map Tick()
//----------------------------------------
void Player::Update(uint32 _update_diff, uint32 _time)
{
	if (!IsInWorld() && !GetIsDead())
		return;

	characterManager.UpdateAttributes(); // update our attributes all tick

	m_position_tmp = m_position;
	m_rotation_tmp = m_rotation;
	
	if (GetIsFighting() == false)
	{
		Regen();
	}
	HandleFreeBattleRange();

	ExecuteLPFood();
	ExecuteEPFood();
	ExecuteStun();

	CalculeLowLife();
	CalculePosition(_update_diff);
	if (GetIsFighting() == true && GetCharEState() == eCHARSTATE::CHARSTATE_STANDING && GetIsSkillCasting() == false)
	{
		Attack();
		attackCount++;
	}
	
	else if (GetIsSkillCasting() == true && GetIsFighting() == false)
	{
	}

	// UPDATE DROPPED LIST
	UpdateDropListTimer();
	// UPDATE ALL TIMER
	rpBallTimer += _time;
}
//----------------------------------------
//	Trigger by Player Tick()
//	Function use to remove the dropped item each 30 seconds after it has benn dropped
//----------------------------------------
void Player::UpdateDropListTimer()
{
	mutexDropList.lock();
	for (auto it = DropList.begin(); it != DropList.end();)
	{
		if (it->second != NULL)
		{
			DWORD deletionAt = GetTickCount() - it->second->droppedTime;
			if (deletionAt >= 50000)
			{
				sGU_OBJECT_DESTROY destroy;
				destroy.handle = it->first;
				destroy.wOpCode = GU_OBJECT_DESTROY;
				destroy.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;
				SendPacket((char*)&destroy, sizeof(sGU_OBJECT_DESTROY));

				delete it->second;
				it = DropList.erase(it++);
			}
			else
				it++;
		}
	}
	mutexDropList.unlock();
}
//----------------------------------------
//	Trigger When we update our amount of money
//	amount of money to add (positive) or negative to remove
//	type of transaction
//----------------------------------------
void Player::UpdateZennyAmount(DWORD amount, eZENNY_CHANGE_TYPE zennyType)
{
	sGU_UPDATE_CHAR_ZENNY zenny;
	zenny.wOpCode = GU_UPDATE_CHAR_ZENNY;
	zenny.wPacketSize = sizeof(sGU_UPDATE_CHAR_ZENNY) - 2;

	zenny.bIsNew = true;
	zenny.byChangeType = eZENNY_CHANGE_TYPE::ZENNY_CHANGE_TYPE_PICK;
	zenny.handle = GetHandle();
	zenny.dwZenny = GetPcProfile()->dwZenny += amount;

	SendPacket((char*)&zenny, sizeof(sGU_UPDATE_CHAR_ZENNY));
}
void Player::UpdateModusaAmount(DWORD amount)
{
	sGU_UPDATE_CHAR_MUDOSA_POINT Modusa;
	Modusa.wOpCode = GU_UPDATE_CHAR_MUDOSA_POINT;
	Modusa.wPacketSize = sizeof(sGU_UPDATE_CHAR_MUDOSA_POINT) - 2;

	Modusa.dwMudosaPoint = GetPcProfile()->dwMudosaPoint += amount;
	GetPcProfile()->dwMudosaPoint = Modusa.dwMudosaPoint;
	
	SendPacket((char*)&Modusa, sizeof(sGU_UPDATE_CHAR_MUDOSA_POINT));
}
//----------------------------------------
//	Check if we are low life or not
//----------------------------------------
void Player::CalculeLowLife()
{
	bool bEmergency = GetIsEmergency();

	if (isLowLifeSend == false && bEmergency == true)
	{
		isLowLifeSend = true;
		sGU_UPDATE_CHAR_LP_STATUS_NFY res;

		res.bEmergency = true;
		res.handle = GetHandle();
		res.wOpCode = GU_UPDATE_CHAR_LP_STATUS_NFY;
		res.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP_STATUS_NFY) - 2;
		res.wResultCode = GAME_SUCCESS;

		SendPacket((char*)&res, sizeof(sGU_UPDATE_CHAR_LP_STATUS_NFY));
		SendToPlayerList((char*)&res, sizeof(sGU_UPDATE_CHAR_LP_STATUS_NFY));
	}
	else if (isLowLifeSend == true && bEmergency == false)
	{
		isLowLifeSend = false;
		sGU_UPDATE_CHAR_LP_STATUS_NFY res;

		res.bEmergency = false;
		res.handle = GetHandle();
		res.wOpCode = GU_UPDATE_CHAR_LP_STATUS_NFY;
		res.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP_STATUS_NFY) - 2;
		res.wResultCode = GAME_SUCCESS;

		SendPacket((char*)&res, sizeof(sGU_UPDATE_CHAR_LP_STATUS_NFY));
		SendToPlayerList((char*)&res, sizeof(sGU_UPDATE_CHAR_LP_STATUS_NFY));
	}
}
//----------------------------------------
//	Regen Stat each tick
//----------------------------------------
void Player::Regen()
{
	///////////////////////////////
	//Reg LP					//	
	//////////////////////////////
	if (GetPcProfile()->dwCurLP < GetPcProfile()->avatarAttribute.wLastMaxLP && GetIsDead() == false)
	{
		int curLPP = GetPcProfile()->dwCurLP;
		//printf("Reg LP %d", GetPcProfile()->dwCurLP);
		
		if (isfighting == false && GetCharEState() != eCHARSTATE::CHARSTATE_SITTING)
		{
			curLPP += GetPcProfile()->avatarAttribute.wLastLpRegen;
		}			
		else if (GetCharEState() == eCHARSTATE::CHARSTATE_SITTING)
		{
			curLPP += GetPcProfile()->avatarAttribute.wLastLpSitdownRegen;
		}	
		if (GetPcProfile()->dwCurLP >= GetPcProfile()->avatarAttribute.wLastMaxLP || curLPP >= GetPcProfile()->avatarAttribute.wLastMaxLP)
		{
			curLPP = GetPcProfile()->avatarAttribute.wLastMaxLP;
			GetPcProfile()->dwCurLP = curLPP;
		}			
		GetPcProfile()->dwCurLP = curLPP;
		sGU_UPDATE_CHAR_LP LPs;
		LPs.dwLpEpEventId = 0;
		LPs.handle = GetHandle();
		LPs.wCurLP = GetPcProfile()->dwCurLP;
		LPs.wMaxLP = GetPcProfile()->avatarAttribute.wLastMaxLP;
		LPs.wOpCode = GU_UPDATE_CHAR_LP;
		LPs.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;
		SendPacket((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
		SendToPlayerList((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
	}
	if (GetPcProfile()->dwCurLP > GetPcProfile()->avatarAttribute.wLastMaxLP)
	{
		GetPcProfile()->dwCurLP = GetPcProfile()->avatarAttribute.wLastMaxLP;		
		sGU_UPDATE_CHAR_LP LPs;
		LPs.dwLpEpEventId = 0;
		LPs.handle = GetHandle();
		LPs.wCurLP = GetPcProfile()->dwCurLP;
		LPs.wMaxLP = GetPcProfile()->avatarAttribute.wLastMaxLP;
		LPs.wOpCode = GU_UPDATE_CHAR_LP;
		LPs.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;
		SendPacket((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
		SendToPlayerList((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
	}
	///////////////////////////////
	//Reg EP					//	
	//////////////////////////////
	if (GetPcProfile()->wCurEP < GetPcProfile()->avatarAttribute.wLastMaxEP && GetIsDead() == false)
	{
		int curEPP = GetPcProfile()->wCurEP;
		//	printf("Reg LP %d", GetPcProfile()->dwCurLP);

		if (isfighting == false && GetCharEState() != eCHARSTATE::CHARSTATE_SITTING)
		{
			curEPP += GetPcProfile()->avatarAttribute.wLastEpRegen;
		}
		else if (GetCharEState() == eCHARSTATE::CHARSTATE_SITTING)
		{
			curEPP += GetPcProfile()->avatarAttribute.wLastEpSitdownRegen;
		}
		if (GetPcProfile()->wCurEP >= GetPcProfile()->avatarAttribute.wLastMaxEP || curEPP >= GetPcProfile()->avatarAttribute.wLastMaxEP)
		{
			curEPP = GetPcProfile()->avatarAttribute.wLastMaxEP;
		}
		GetPcProfile()->wCurEP = curEPP;
		sGU_UPDATE_CHAR_EP EP;
		EP.dwLpEpEventId = 0;
		EP.handle = GetHandle();
		EP.wCurEP = GetPcProfile()->wCurEP;
		EP.wMaxEP = GetPcProfile()->avatarAttribute.wLastMaxEP;
		EP.wOpCode = GU_UPDATE_CHAR_EP;
		EP.wPacketSize = sizeof(sGU_UPDATE_CHAR_EP) - 2;
		SendPacket((char*)&EP, sizeof(sGU_UPDATE_CHAR_EP));
		SendToPlayerList((char*)&EP, sizeof(sGU_UPDATE_CHAR_EP));
	}
	if (GetPcProfile()->wCurEP > GetPcProfile()->avatarAttribute.wLastMaxEP)
	{
		GetPcProfile()->wCurEP = GetPcProfile()->avatarAttribute.wLastMaxEP;
		sGU_UPDATE_CHAR_EP EP;
		EP.dwLpEpEventId = 0;
		EP.handle = GetHandle();
		EP.wCurEP = GetPcProfile()->wCurEP;
		EP.wMaxEP = GetPcProfile()->avatarAttribute.wLastMaxEP;
		EP.wOpCode = GU_UPDATE_CHAR_EP;
		EP.wPacketSize = sizeof(sGU_UPDATE_CHAR_EP) - 2;
		SendPacket((char*)&EP, sizeof(sGU_UPDATE_CHAR_EP));
		SendToPlayerList((char*)&EP, sizeof(sGU_UPDATE_CHAR_EP));
	}
	///////////////////////////////
	//Reg AP					//	
	//////////////////////////////
	if (GetPcProfile()->dwCurAp < GetPcProfile()->avatarAttribute.wLastMaxAp && GetIsDead() == false && isFlying == false)
	{
		int curAPP = GetPcProfile()->dwCurAp;
		//	printf("Reg LP %d", GetPcProfile()->dwCurLP);
		curAPP += 5000;
		GetPcProfile()->dwCurAp = curAPP;

		sGU_UPDATE_CHAR_AP AP;
	
		AP.handle = GetHandle();
		AP.dwCurAp = GetPcProfile()->dwCurAp;
		AP.wLastMaxAp = GetPcProfile()->avatarAttribute.wLastMaxAp;
		AP.wBaseMaxAp = GetPcProfile()->avatarAttribute.wBaseMaxAp;
		AP.wOpCode = GU_UPDATE_CHAR_AP;
		AP.wPacketSize = sizeof(sGU_UPDATE_CHAR_AP) - 2;
		SendPacket((char*)&AP, sizeof(sGU_UPDATE_CHAR_AP));
		SendToPlayerList((char*)&AP, sizeof(sGU_UPDATE_CHAR_AP));
	}
	if (GetPcProfile()->dwCurAp > 0 && GetIsDead() == false && isFlying == true)
	{
		int curAPP = GetPcProfile()->dwCurAp;
		//	printf("Reg LP %d", GetPcProfile()->dwCurLP);	
		curAPP -= 5000;
		if (GetPcProfile()->dwCurAp <= 0 || curAPP <= 0)
		{		
			curAPP = 0;
			GetState()->sCharStateDetail.sCharStateFalling.dwTimeStamp = 0x01;
			GetState()->sCharStateDetail.sCharStateFalling.byMoveDirection = 1;
			SetState(eCHARSTATE::CHARSTATE_FALLING);
		}	
		GetPcProfile()->dwCurAp = curAPP;
		sGU_UPDATE_CHAR_AP AP;

		AP.handle = GetHandle();
		AP.dwCurAp = GetPcProfile()->dwCurAp;
		AP.wLastMaxAp = GetPcProfile()->avatarAttribute.wLastMaxAp;
		AP.wBaseMaxAp = GetPcProfile()->avatarAttribute.wBaseMaxAp;
		AP.wOpCode = GU_UPDATE_CHAR_AP;
		AP.wPacketSize = sizeof(sGU_UPDATE_CHAR_AP) - 2;
		SendPacket((char*)&AP, sizeof(sGU_UPDATE_CHAR_AP));
		SendToPlayerList((char*)&AP, sizeof(sGU_UPDATE_CHAR_AP));

	}
	if (GetPcProfile()->dwCurAp > GetPcProfile()->avatarAttribute.wLastMaxAp)
	{
		GetPcProfile()->dwCurAp = GetPcProfile()->avatarAttribute.wLastMaxAp;
		sGU_UPDATE_CHAR_AP AP;

		AP.handle = GetHandle();
		AP.dwCurAp = GetPcProfile()->dwCurAp;
		AP.wLastMaxAp = GetPcProfile()->avatarAttribute.wLastMaxAp;
		AP.wBaseMaxAp = GetPcProfile()->avatarAttribute.wBaseMaxAp;
		AP.wOpCode = GU_UPDATE_CHAR_AP;
		AP.wPacketSize = sizeof(sGU_UPDATE_CHAR_AP) - 2;
		SendPacket((char*)&AP, sizeof(sGU_UPDATE_CHAR_AP));
		SendToPlayerList((char*)&AP, sizeof(sGU_UPDATE_CHAR_AP));
	}
	//CalculeRpBall();
}
//Need Delet all that Shit and Remake it only handle one buff
void Player::ExecuteLPFood()
{
	for (int i = 0; i <= 16; i++)
	{
		if (GetAttributesManager()->LpFoodIsActive == true && GetAttributesManager()->sFoodInfo[i].FoodItemID != 0 & GetAttributesManager()->sFoodInfo[i].FoodItemID != INVALID_TBLIDX)
		{
			sGU_EFFECT_AFFECTED afect;			
			afect.wOpCode = GU_EFFECT_AFFECTED;
			afect.wPacketSize = sizeof(sGU_EFFECT_AFFECTED) - 2;
			afect.handle = GetHandle();
			afect.hCaster = GetHandle();
			//afect.effectTblidx = effect->effectTblidx = Item->tblidx;
			afect.effectTblidx = GetAttributesManager()->sFoodInfo[i].FoodItemID;
			afect.bysource = 1;
			afect.SyestemEffectCode = GetAttributesManager()->sFoodInfo[i].TypeEffect;
			afect.ResultCode = 500;
			afect.ActualArgument[0] = GetAttributesManager()->sFoodInfo[i].FoodHealAumont[0];
			afect.ActualArgument[1] = GetAttributesManager()->sFoodInfo[i].FoodHealAumont[1];

						//ACTIVE_HEAL_OVER_TIME;			
			sGU_UPDATE_CHAR_LP LPs;
			LPs.wOpCode = GU_UPDATE_CHAR_LP;
			LPs.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;

			int newlp = GetPcProfile()->dwCurLP;
			if (newlp <= GetPcProfile()->avatarAttribute.wLastMaxLP)
			{
				newlp += GetAttributesManager()->sFoodInfo[i].FoodHealAumont[0];
			}
			if (newlp >= GetPcProfile()->avatarAttribute.wLastMaxLP)
			{
				newlp = GetPcProfile()->avatarAttribute.wLastMaxLP;
			}
			GetPcProfile()->dwCurLP = newlp;			
			LPs.dwLpEpEventId = 0;
			LPs.handle = GetHandle();
			LPs.wCurLP = GetPcProfile()->dwCurLP;
			LPs.wMaxLP = GetPcProfile()->avatarAttribute.wLastMaxLP;
			SendPacket((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
			SendToPlayerList((char*)&LPs, sizeof(sGU_UPDATE_CHAR_LP));
			SendPacket((char*)&afect, sizeof(sGU_EFFECT_AFFECTED));
			SendToPlayerList((char*)&afect, sizeof(sGU_EFFECT_AFFECTED));

			DWORD deletionAt1 = GetTickCount() - GetAttributesManager()->sFoodInfo[i].BuffTime;
			if (deletionAt1 >= GetAttributesManager()->sFoodInfo[i].BuffKeepTime || GetCharEState() != eCHARSTATE::CHARSTATE_SITTING)
			{
					sGU_BUFF_DROPPED dropbuff;
					dropbuff.wOpCode = GU_BUFF_DROPPED;
					dropbuff.wPacketSize = sizeof(sGU_BUFF_DROPPED) - 2;
					dropbuff.hHandle = GetHandle();
					dropbuff.bySourceType = eDBO_OBJECT_SOURCE::DBO_OBJECT_SOURCE_SKILL;
					//dropbuff.unk = 1;
					dropbuff.tblidx = GetAttributesManager()->sFoodInfo[i].FoodItemID;
					dropbuff.unk1 = 0;
					SendPacket((char*)&dropbuff, sizeof(sGU_BUFF_DROPPED));
					SendToPlayerList((char*)&dropbuff, sizeof(sGU_BUFF_DROPPED));					
					GetAttributesManager()->LpFoodIsActive = false;
					GetAttributesManager()->sFoodInfo[i].FoodItemID = INVALID_TBLIDX;
								
			}
		}
	}
	
}
void Player::ExecuteEPFood()
{
	for (int i = 0; i <= 16; i++)
	{
		if (GetAttributesManager()->EpFoodIsActive == true && GetAttributesManager()->sFoodInfo[i].FoodItemID != 0 & GetAttributesManager()->sFoodInfo[i].FoodItemID != INVALID_TBLIDX)
		{
			sGU_EFFECT_AFFECTED afect;
			afect.wOpCode = GU_EFFECT_AFFECTED;
			afect.wPacketSize = sizeof(sGU_EFFECT_AFFECTED) - 2;
			afect.handle = GetHandle();
			afect.hCaster = GetHandle();
			afect.effectTblidx = GetAttributesManager()->sFoodInfo[i].FoodItemID;
			afect.bysource = 1;
			afect.SyestemEffectCode = GetAttributesManager()->sFoodInfo[i].TypeEffect;
			afect.ResultCode = 500;
			afect.ActualArgument[0] = GetAttributesManager()->sFoodInfo[i].FoodHealAumont[0];
			afect.ActualArgument[1] = GetAttributesManager()->sFoodInfo[i].FoodHealAumont[1];			
			//ACTIVE_HEAL_OVER_TIME;

			sGU_UPDATE_CHAR_EP EPs;
			EPs.wOpCode = GU_UPDATE_CHAR_EP;
			EPs.wPacketSize = sizeof(sGU_UPDATE_CHAR_EP) - 2;

			int newEp = GetPcProfile()->wCurEP;
			if (newEp <= GetPcProfile()->avatarAttribute.wLastMaxEP)
			{
				newEp += GetAttributesManager()->sFoodInfo[i].FoodHealAumont[0];
			}
			if (newEp >= GetPcProfile()->avatarAttribute.wLastMaxEP)
			{
				newEp = GetPcProfile()->avatarAttribute.wLastMaxEP;
			}
			GetPcProfile()->wCurEP = newEp;
			
			EPs.dwLpEpEventId = 0;
			EPs.handle = GetHandle();
			EPs.wCurEP = GetPcProfile()->wCurEP;
			EPs.wMaxEP = GetPcProfile()->avatarAttribute.wLastMaxEP;

			SendPacket((char*)&EPs, sizeof(sGU_UPDATE_CHAR_EP));
			SendToPlayerList((char*)&EPs, sizeof(sGU_UPDATE_CHAR_EP));
			SendPacket((char*)&afect, sizeof(sGU_EFFECT_AFFECTED));
			SendToPlayerList((char*)&afect, sizeof(sGU_EFFECT_AFFECTED));

			DWORD deletionAt1 = GetTickCount() - GetAttributesManager()->sFoodInfo[i].BuffTime;
			if (deletionAt1 >= GetAttributesManager()->sFoodInfo[i].BuffKeepTime || GetCharEState() != eCHARSTATE::CHARSTATE_SITTING)
			{
				sGU_BUFF_DROPPED dropbuff;
				dropbuff.wOpCode = GU_BUFF_DROPPED;
				dropbuff.wPacketSize = sizeof(sGU_BUFF_DROPPED) - 2;
				dropbuff.hHandle = GetHandle();
				dropbuff.bySourceType = eDBO_OBJECT_SOURCE::DBO_OBJECT_SOURCE_SKILL;
				//dropbuff.unk = 1;
				dropbuff.tblidx = GetAttributesManager()->sFoodInfo[i].FoodItemID;
				dropbuff.unk1 = 0;
				SendPacket((char*)&dropbuff, sizeof(sGU_BUFF_DROPPED));
				SendToPlayerList((char*)&dropbuff, sizeof(sGU_BUFF_DROPPED));
				GetAttributesManager()->EpFoodIsActive = false;
				GetAttributesManager()->sFoodInfo[i].FoodItemID = INVALID_TBLIDX;
				GetAttributesManager()->sFoodInfo[i].BuffKeepTime = INVALID_TBLIDX;

			}
		}
	}

}
//Need Delet all that Shit and Remake it just Handle one Stun
void Player::ExecuteStun()
{
	
	for (int i = 0; i <= 16; i++)
	{
		if (GetAttributesManager()->sBuffTimeInfo[i].BuffIsActive == true && GetAttributesManager()->sBuffTimeInfo[i].BuffID != 0 & GetAttributesManager()->sBuffTimeInfo[i].BuffID != INVALID_TBLIDX)
		{			
			DWORD deletionAt1 = GetTickCount() - GetAttributesManager()->sBuffTimeInfo[i].BuffTime;
			if (deletionAt1 >= GetAttributesManager()->sBuffTimeInfo[i].BuffEndTime)
			{
				Mob* MobInfo = static_cast<Mob*>(GetFromList(GetAttributesManager()->sBuffTimeInfo[i].PlayerHandle));
				if (MobInfo != NULL && MobInfo->GetIsDead() == false)
				{
					sGU_BUFF_DROPPED dropbuff;
					dropbuff.wOpCode = GU_BUFF_DROPPED;
					dropbuff.wPacketSize = sizeof(sGU_BUFF_DROPPED) - 2;
					dropbuff.hHandle = GetAttributesManager()->sBuffTimeInfo[i].PlayerHandle;
					dropbuff.bySourceType = eDBO_OBJECT_SOURCE::DBO_OBJECT_SOURCE_SKILL;
				//	dropbuff.unk = 1;
					dropbuff.tblidx = GetAttributesManager()->sBuffTimeInfo[i].BuffID;
					dropbuff.unk1 = 1;
					SendPacket((char*)&dropbuff, sizeof(sGU_BUFF_DROPPED));
					SendToPlayerList((char*)&dropbuff, sizeof(sGU_BUFF_DROPPED));
					GetAttributesManager()->sBuffTimeInfo[i].BuffIsActive = false;
					GetAttributesManager()->sBuffTimeInfo[i].BuffEndTime = INVALID_TBLIDX;
					GetAttributesManager()->sBuffTimeInfo[i].BuffTime = INVALID_TBLIDX;
					GetAttributesManager()->sBuffTimeInfo[i].BuffID = INVALID_TBLIDX;
					MobInfo->SetState(eCHARSTATE::CHARSTATE_STANDING);
				}
			}
		}
	}
}
//Need Delet all that shit and Remake
void Player::HandleFreeBattleRange()
{
	if (GetAttributesManager()->PlayerInFreeBatle == true)
	{
		Player* PlayerInfo = static_cast<Player*>(GetFromList(GetAttributesManager()->FreeBatleChellenger));
		if (PlayerInfo != NULL)
		{
			float dist = NtlGetDistance(GetVectorPosition().x, GetVectorPosition().z, GetAttributesManager()->vRefreeLoc.x, GetAttributesManager()->vRefreeLoc.z);
			float dist1 = NtlGetDistance(PlayerInfo->GetVectorPosition().x, PlayerInfo->GetVectorPosition().z, PlayerInfo->GetAttributesManager()->vRefreeLoc.x, PlayerInfo->GetAttributesManager()->vRefreeLoc.z);
			if (dist >= 50)
			{

				if (GetAttributesManager()->showMensageOut == false && dist >= 50)
				{
					sGU_FREEBATTLE_OUTSIDE_NFY FreeBatleOut;
					FreeBatleOut.wOpCode = GU_FREEBATTLE_OUTSIDE_NFY;
					FreeBatleOut.wPacketSize = sizeof(sGU_FREEBATTLE_OUTSIDE_NFY) - 2;
					GetAttributesManager()->OutBatleTime = GetTickCount();
					GetAttributesManager()->showMensageOut = true;
					SendPacket((char*)&FreeBatleOut, sizeof(sGU_FREEBATTLE_OUTSIDE_NFY));				
				}
				if (GetAttributesManager()->showMensageOut == true && dist >= 50)
				{
					GetAttributesManager()->OutBatleFinalTime = GetTickCount() - GetAttributesManager()->OutBatleTime;
					//printf("Player1 time %d  \n", GetAttributesManager()->OutBatleFinalTime);
					if (GetAttributesManager()->OutBatleFinalTime >= 11000)
					{
						sGU_FREEBATTLE_END_NFY FreebatleEnd;
						FreebatleEnd.wOpCode = GU_FREEBATTLE_END_NFY;
						FreebatleEnd.wPacketSize = sizeof(sGU_FREEBATTLE_END_NFY) - 2;
						FreebatleEnd.byFreeBattleResult = eFREEBATTLE_RESULT::FREEBATTLE_RESULT_LOSE;
						SendPacket((char*)&FreebatleEnd, sizeof(sGU_FREEBATTLE_END_NFY));

						GetAttributesManager()->showMensageOut = false;
						GetAttributesManager()->PlayerInFreeBatle = false;
						GetAttributesManager()->FreeBatleChellenger = INVALID_TBLIDX;

						sGU_FREEBATTLE_END_NFY FreebatleEnd1;
						FreebatleEnd1.wOpCode = GU_FREEBATTLE_END_NFY;
						FreebatleEnd1.wPacketSize = sizeof(sGU_FREEBATTLE_END_NFY) - 2;
						FreebatleEnd1.byFreeBattleResult = eFREEBATTLE_RESULT::FREEBATTLE_RESULT_WIN;
						PlayerInfo->SendPacket((char*)&FreebatleEnd1, sizeof(sGU_FREEBATTLE_END_NFY));

						PlayerInfo->GetAttributesManager()->showMensageOut = false;
						PlayerInfo->GetAttributesManager()->PlayerInFreeBatle = false;
						PlayerInfo->GetAttributesManager()->FreeBatleChellenger = INVALID_TBLIDX;
					}				
				}
			}
			else if(dist < 50 && GetAttributesManager()->showMensageOut == true)
			{
				sGU_FREEBATTLE_INSIDE_NFY FreeBatlein;
				FreeBatlein.wOpCode = GU_FREEBATTLE_INSIDE_NFY;
				FreeBatlein.wPacketSize = sizeof(sGU_FREEBATTLE_INSIDE_NFY) - 2;
				GetAttributesManager()->OutBatleTime = GetTickCount();
				GetAttributesManager()->showMensageOut = false;
				SendPacket((char*)&FreeBatlein, sizeof(sGU_FREEBATTLE_INSIDE_NFY));
			}
			//Player2
			if (dist1 >= 50)
			{

				if (PlayerInfo->GetAttributesManager()->showMensageOut == false && dist1 >= 50)
				{
					sGU_FREEBATTLE_OUTSIDE_NFY FreeBatleOut;
					FreeBatleOut.wOpCode = GU_FREEBATTLE_OUTSIDE_NFY;
					FreeBatleOut.wPacketSize = sizeof(sGU_FREEBATTLE_OUTSIDE_NFY) - 2;
					PlayerInfo->GetAttributesManager()->OutBatleTime = GetTickCount();
					PlayerInfo->GetAttributesManager()->showMensageOut = true;
					PlayerInfo->SendPacket((char*)&FreeBatleOut, sizeof(sGU_FREEBATTLE_OUTSIDE_NFY));
				}
				if (PlayerInfo->GetAttributesManager()->showMensageOut == true && dist1 >= 50)
				{
					PlayerInfo->GetAttributesManager()->OutBatleFinalTime = GetTickCount() - PlayerInfo->GetAttributesManager()->OutBatleTime;
				//	printf("Player2 time %d  \n", PlayerInfo->GetAttributesManager()->OutBatleFinalTime);
					if (PlayerInfo->GetAttributesManager()->OutBatleFinalTime >= 11000)
					{
						sGU_FREEBATTLE_END_NFY FreebatleEnd;
						FreebatleEnd.wOpCode = GU_FREEBATTLE_END_NFY;
						FreebatleEnd.wPacketSize = sizeof(sGU_FREEBATTLE_END_NFY) - 2;
						FreebatleEnd.byFreeBattleResult = eFREEBATTLE_RESULT::FREEBATTLE_RESULT_LOSE;
						PlayerInfo->SendPacket((char*)&FreebatleEnd, sizeof(sGU_FREEBATTLE_END_NFY));

						PlayerInfo->GetAttributesManager()->showMensageOut = false;
						PlayerInfo->GetAttributesManager()->PlayerInFreeBatle = false;
						PlayerInfo->GetAttributesManager()->FreeBatleChellenger = INVALID_TBLIDX;

						sGU_FREEBATTLE_END_NFY FreebatleEnd1;
						FreebatleEnd1.wOpCode = GU_FREEBATTLE_END_NFY;
						FreebatleEnd1.wPacketSize = sizeof(sGU_FREEBATTLE_END_NFY) - 2;
						FreebatleEnd1.byFreeBattleResult = eFREEBATTLE_RESULT::FREEBATTLE_RESULT_WIN;
						SendPacket((char*)&FreebatleEnd1, sizeof(sGU_FREEBATTLE_END_NFY));

						GetAttributesManager()->showMensageOut = false;
						GetAttributesManager()->PlayerInFreeBatle = false;
						GetAttributesManager()->FreeBatleChellenger = INVALID_TBLIDX;
					}
				}
			}
			else if (dist1 < 50 && PlayerInfo->GetAttributesManager()->showMensageOut == true)
			{
				sGU_FREEBATTLE_INSIDE_NFY FreeBatlein;
				FreeBatlein.wOpCode = GU_FREEBATTLE_INSIDE_NFY;
				FreeBatlein.wPacketSize = sizeof(sGU_FREEBATTLE_INSIDE_NFY) - 2;
				PlayerInfo->GetAttributesManager()->OutBatleTime = GetTickCount();
				PlayerInfo->GetAttributesManager()->showMensageOut = false;
				PlayerInfo->SendPacket((char*)&FreeBatlein, sizeof(sGU_FREEBATTLE_INSIDE_NFY));
			}
		}
	}
}
void Player::HandleFreeBattleWinners()
{

}
void Player::UpdateAspectState(BYTE State)
{
	sGU_UPDATE_CHAR_ASPECT_STATE CharAspect;
	CharAspect.wOpCode = GU_UPDATE_CHAR_ASPECT_STATE;
	CharAspect.wPacketSize = sizeof(sGU_UPDATE_CHAR_ASPECT_STATE) - 2;
	CharAspect.handle = GetHandle();
	CharAspect.aspectState.sAspectStateBase.byAspectStateId = GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = State;
	CharAspect.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn;
	CharAspect.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem;
	CharAspect.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx;
	
	SendToPlayerList((char*)&CharAspect, sizeof(sGU_UPDATE_CHAR_ASPECT_STATE));
	SendPacket((char*)&CharAspect, sizeof(sGU_UPDATE_CHAR_ASPECT_STATE));
	
}
//----------------------------------------
//	Generate RP when fight or decrease when not fight
//----------------------------------------
void Player::CalculeRpBall()
{
	bool sendRpBall = true;

	if (isfighting == false)
	{
		if (GetPcProfile()->wCurRP > 0 || GetAttributesManager()->GetNumFilledRpBall() > 0)
		{
			if (rpBallTimer >= CHAR_RP_BALL_UPDATE_INTERVAL)
			{
				int rpCur = GetPcProfile()->wCurRP;
				rpCur -= 5;
				if (rpCur <= 0 && GetAttributesManager()->GetNumFilledRpBall() > 0)
				{
					GetAttributesManager()->SetNumFilledRpBall(-1);
					GetPcProfile()->wCurRP = GetPcProfile()->avatarAttribute.wBaseMaxRP;
					sGU_UPDATE_CHAR_RP_BALL newBall;
					newBall.bDropByTime = true;
					newBall.byCurRPBall = GetAttributesManager()->GetNumFilledRpBall();
					newBall.handle = GetHandle();
					newBall.wOpCode = GU_UPDATE_CHAR_RP_BALL;
					newBall.wPacketSize = sizeof(sGU_UPDATE_CHAR_RP_BALL) - 2;
					SendPacket((char*)&newBall, sizeof(sGU_UPDATE_CHAR_RP_BALL));
					SendToPlayerList((char*)&newBall, sizeof(sGU_UPDATE_CHAR_RP_BALL));
				}
				else
					GetPcProfile()->wCurRP = rpCur;
				sendRpBall = true;
			}
		}
	}
	else
	{
		if (GetPcProfile()->wCurRP < GetPcProfile()->avatarAttribute.wBaseMaxRP
			&& GetAttributesManager()->GetNumFilledRpBall() < GetAttributesManager()->GetNumRpBall())
		{
			GetPcProfile()->wCurRP += 5;
			if (GetPcProfile()->wCurRP >= GetPcProfile()->avatarAttribute.wBaseMaxRP)
			{
				GetAttributesManager()->SetNumFilledRpBall(1);
				GetPcProfile()->wCurRP = 0;
				sGU_UPDATE_CHAR_RP_BALL newBall;
				newBall.bDropByTime = true;
				newBall.byCurRPBall = GetAttributesManager()->GetNumFilledRpBall();
				newBall.handle = GetHandle();
				newBall.wOpCode = GU_UPDATE_CHAR_RP_BALL;
				newBall.wPacketSize = sizeof(sGU_UPDATE_CHAR_RP_BALL) - 2;
				SendPacket((char*)&newBall, sizeof(sGU_UPDATE_CHAR_RP_BALL));
				SendToPlayerList((char*)&newBall, sizeof(sGU_UPDATE_CHAR_RP_BALL));
			}
			sendRpBall = true;
			rpBallTimer = 0;
		}
	}
	if (sendRpBall == true)
	{
		sGU_UPDATE_CHAR_RP RP;

		RP.bHitDelay = false;
		RP.handle = GetHandle();
		RP.wCurRP = GetPcProfile()->wCurRP;
		RP.wMaxRP = GetPcProfile()->avatarAttribute.wBaseMaxRP;
		RP.wOpCode = GU_UPDATE_CHAR_RP;
		RP.wPacketSize = sizeof(sGU_UPDATE_CHAR_RP) - 2;
		SendPacket((char*)&RP, sizeof(sGU_UPDATE_CHAR_RP));
		SendToPlayerList((char*)&RP, sizeof(sGU_UPDATE_CHAR_RP));
	}
}
//----------------------------------------
//	Refresh our current position
//----------------------------------------
void Player::CalculePosition(uint32 _update_diff)
{
	//--------------------------
	//	Do calculation to determine the current player position
	//--------------------------
	BYTE moveDir = GetMoveDirection();
	if (moveDir > AKCORE_STOP && moveDir < AKCORE_COUNT && GetCharEState() == eCHARSTATE::CHARSTATE_MOVING)
	{
		CNtlVector newHeading;
		CNtlVector newPosition;
		// class those function ?
		NtlGetDestination_Keyboard(m_rotation_tmp.x, m_rotation_tmp.z, 8, m_position_tmp.x, m_position_tmp.y, m_position_tmp.z, moveDir, _update_diff, 8, newHeading, newPosition);
		if (newPosition.x != 0 && newPosition.z != 0)
		{
			Relocate(newPosition.x, newPosition.y, newPosition.z, newHeading.x, newHeading.y, newHeading.z);
		}
	}
	else if (GetCharEState() == eCHARSTATE::CHARSTATE_DESTMOVE)
	{
		//.outError("HEY ! DON't YOU FORGOT SOMETHING HERE !?");
		//NtlGetDestination_Mouse();
		CNtlVector newHeading;
		CNtlVector newPosition;
		// class those function ?
		NtlGetDestination_Keyboard(m_rotation_tmp.x, m_rotation_tmp.z, 8, m_position_tmp.x, m_position_tmp.y, m_position_tmp.z, moveDir, _update_diff, 8, newHeading, newPosition);
		if (newPosition.x != 0 && newPosition.z != 0)
		{
			Relocate(newPosition.x, newPosition.y, newPosition.z, newHeading.x, newHeading.y, newHeading.z);
		}
	}
	else if (GetCharEState() == eCHARSTATE::CHARSTATE_FOLLOWING)
	{
		CNtlVector newHeading;
		CNtlVector newPosition;

		float fDistance = NtlGetDistance(m_position_tmp.x, m_position_tmp.z, GetMoveDestinationVector().x, GetMoveDestinationVector().z);

		NtlGetDestination_Follow(m_rotation_tmp.x, m_rotation_tmp.z, 8, m_position_tmp.x, m_position_tmp.y, m_position_tmp.z, GetMoveDestinationVector().x, GetMoveDestinationVector().y, GetMoveDestinationVector().z, _update_diff, 2, newHeading, newPosition);
		if (newPosition.x != 0 && newPosition.z != 0)
		{
			Relocate(newPosition.x, newPosition.y, newPosition.z, newHeading.x, newHeading.y, newHeading.z);
		}
	}
	else if (GetCharEState() == eCHARSTATE::CHARSTATE_AIR_JUMP)
	{
		CNtlVector newHeading;
		CNtlVector newPosition;

		float fDistance = NtlGetDistance(m_position_tmp.x, m_position_tmp.z, GetMoveDestinationVector().x, GetMoveDestinationVector().z);

		NtlGetDestination_Follow(m_rotation_tmp.x, m_rotation_tmp.z, 8, m_position_tmp.x, m_position_tmp.y, m_position_tmp.z, GetMoveDestinationVector().x, GetMoveDestinationVector().y, GetMoveDestinationVector().z, _update_diff, 2, newHeading, newPosition);
		if (newPosition.x != 0 && newPosition.z != 0)
		{
			Relocate(newPosition.x, newPosition.y, newPosition.z, newHeading.x, newHeading.y, newHeading.z);
		}
	}
	else if (GetCharEState() == eCHARSTATE::CHARSTATE_AIR_DASH_ACCEL)
	{
		CNtlVector newHeading;
		CNtlVector newPosition;

		float fDistance = NtlGetDistance(m_position_tmp.x, m_position_tmp.z, GetMoveDestinationVector().x, GetMoveDestinationVector().z);

		NtlGetDestination_Follow(m_rotation_tmp.x, m_rotation_tmp.z, 8, m_position_tmp.x, m_position_tmp.y, m_position_tmp.z, GetMoveDestinationVector().x, GetMoveDestinationVector().y, GetMoveDestinationVector().z, _update_diff, 2, newHeading, newPosition);
		if (newPosition.x != 0 && newPosition.z != 0)
		{
			Relocate(newPosition.x, newPosition.y, newPosition.z, newHeading.x, newHeading.y, newHeading.z);
		}
	}
}
//----------------------------------------
//	Add a new player to our storage list
//----------------------------------------
void Player::FillList(Object& object)
{
	mutexPlayer.lock();
	objList.insert(std::make_pair(object.GetHandle(), &object));
	mutexPlayer.unlock();
}
//----------------------------------------
//	Remove an Object from our list
//----------------------------------------
void Player::RemoveFromList(Object& player)
{
	mutexPlayer.lock();
	for (auto it = objList.begin(); it != objList.end();)
	{
		if (it->second != NULL)
		{
			if (it->first == player.GetHandle())
			{
				it = objList.erase(it++);
				break;
			}
			else
				it++;
		}
	}
	mutexPlayer.unlock();
}
//----------------------------------------
//	Get a new player from our storage list
//----------------------------------------
Object *Player::GetFromList(uint32 id)
{
	mutexPlayer.lock();
	for (auto it = objList.begin(); it != objList.end();)
	{
		if (it->second != NULL)
		{
			if (it->first == id)
			{
				mutexPlayer.unlock();
				return it->second;
			}
			else
				it++;
		}
	}
	mutexPlayer.unlock();
	return NULL;
}
//----------------------------------------
//	Check if Player X is in list
//----------------------------------------
bool Player::isInList(uint32 id)
{
	mutexPlayer.lock();
	auto it = objList.find(id);
	if (it == objList.end())
	{
		mutexPlayer.unlock();
		return false;
	}
	if (it->second != NULL)
	{
		if (it->second->IsInWorld() == true)
		{
			if (it->second->GetHandle() == id)
			{
				mutexPlayer.unlock();
				return true;
			}
		}
	}
	mutexPlayer.unlock();
	return false;
}
//----------------------------------------
//	Send packet to all player in the list
//----------------------------------------
void Player::SendToPlayerList(char* data, size_t size)
{
	mutexPlayer.lock();
	for (auto it = objList.begin(); it != objList.end();)
	{
		if (it->second != NULL)
		{
			if (it->second->GetTypeId() == OBJTYPE_PC)
			{
				Player* plr = static_cast<Player*>(it->second);
				if (plr->IsInWorld() == true && plr->GetSession() != NULL)
				{
					plr->SendPacket(data, size);
				}
			}
		}
		it++;
	}
	mutexPlayer.unlock();
}
//----------------------------------------
//	Add a dropped item to our list
//----------------------------------------
void Player::AddDropToList(DroppedObject& drop, HOBJECT dropHandle)
{
	mutexDropList.lock();
	DropList.insert(std::make_pair(dropHandle, &drop));
	mutexDropList.unlock();
}
//----------------------------------------
//	Remove a dropped object from our list
//----------------------------------------
void Player::RemoveDropFromList(HOBJECT handle)
{
	mutexDropList.lock();
	for (auto it = DropList.begin(); it != DropList.end();)
	{
		if (it->second != NULL)
		{
			if (it->first == handle)
			{
				sGU_OBJECT_DESTROY destroy;
				destroy.handle = it->first;
				destroy.wOpCode = GU_OBJECT_DESTROY;
				destroy.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;
				SendPacket((char*)&destroy, sizeof(sGU_OBJECT_DESTROY));

				delete it->second;
				it = DropList.erase(it++);
				break;
			}
			else
				it++;
		}
	}
	mutexDropList.unlock();
}
//----------------------------------------
//	Get the data from object dropped
//	Requiert the dropped handle
//----------------------------------------
DroppedObject *Player::GetPickupData(HOBJECT handle)
{
	mutexDropList.lock();
	for (auto it = DropList.begin(); it != DropList.end(); ++it)
	{
		if (it->second != NULL)
		{
			if (it->first == handle)
			{
				mutexDropList.unlock();
				return it->second;
			}
		}
	}
	mutexDropList.unlock();
	return NULL;
}
//----------------------------------------
//	Perform an auto attack
//----------------------------------------
void Player::Attack()
{
	if (cur_obj_tagert == NULL || cur_obj_tagert->GetTypeId() == OBJTYPE_NPC)
	{
		SetIsFighting(false);
		return;
	}
	if (fightManager.HandleDamage(*this, *cur_obj_tagert) == false)
	{
		SetIsFighting(false);
	}
	//target->TakeDamage(attackValue);

	/*
		Physical attack	=	thing		Energy Attack	=	thing		Hit Rate	=	thing
		Physical def	=	thing		Energy Def		=	thing		Dodge		=	thing
		Crit physical	=	thing		Crit Energy		=	thing

		Abdominal		=	thing

	*/
}
//----------------------------------------
//Need Change That Shit and Remake
//	Take some damage (need to inheritance that)
//----------------------------------------
void	Player::TakeDamage(uint32 amount)
{
	
	Player* PlayerInfo = static_cast<Player*>(GetFromList(GetAttributesManager()->FreeBatleChellenger));	
	if (PlayerInfo != NULL)
	{		
	int32_t newLife = GetPcProfile()->dwCurLP;
	
	newLife -= amount;
	if (newLife <= 0)
	{
		GetAttributesManager()->LoseBatle = true;		
		SetIsFighting(false);
		newLife = 0;
	}
	GetPcProfile()->dwCurLP = newLife;

	sGU_UPDATE_CHAR_LP updLp;
	updLp.handle = handle;
	updLp.wCurLP = GetPcProfile()->dwCurLP = newLife;
	updLp.wMaxLP = GetPcProfile()->avatarAttribute.wLastMaxLP;
	updLp.wOpCode = GU_UPDATE_CHAR_LP;
	updLp.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;

	
	SendPacket((char*)&updLp, sizeof(sGU_UPDATE_CHAR_LP));
	SendToPlayerList((char*)&updLp, sizeof(sGU_UPDATE_CHAR_LP));
	
	if (GetAttributesManager()->LoseBatle == true && PlayerInfo->GetTypeId() == OBJTYPE_PC)
	{			
			sGU_FREEBATTLE_END_NFY FreebatleEnd;
			FreebatleEnd.wOpCode = GU_FREEBATTLE_END_NFY;
			FreebatleEnd.wPacketSize = sizeof(sGU_FREEBATTLE_END_NFY) - 2;
			FreebatleEnd.byFreeBattleResult = eFREEBATTLE_RESULT::FREEBATTLE_RESULT_LOSE;
			SendPacket((char*)&FreebatleEnd, sizeof(sGU_FREEBATTLE_END_NFY));
			GetAttributesManager()->showMensageOut = false;
			GetAttributesManager()->PlayerInFreeBatle = false;
			GetAttributesManager()->FreeBatleChellenger = INVALID_TBLIDX;

			sGU_FREEBATTLE_END_NFY FreebatleEnd1;
			FreebatleEnd1.wOpCode = GU_FREEBATTLE_END_NFY;
			FreebatleEnd1.wPacketSize = sizeof(sGU_FREEBATTLE_END_NFY) - 2;
			FreebatleEnd1.byFreeBattleResult = eFREEBATTLE_RESULT::FREEBATTLE_RESULT_WIN;
			PlayerInfo->SendPacket((char*)&FreebatleEnd1, sizeof(sGU_FREEBATTLE_END_NFY));
			PlayerInfo->GetAttributesManager()->showMensageOut = false;
			PlayerInfo->GetAttributesManager()->PlayerInFreeBatle = false;
			PlayerInfo->GetAttributesManager()->FreeBatleChellenger = INVALID_TBLIDX;
			GetAttributesManager()->LoseBatle = false;
			PlayerInfo->GetAttributesManager()->LoseBatle = false;
	}	
	if (PlayerInfo->GetAttributesManager()->LoseBatle == true && PlayerInfo->GetTypeId() == OBJTYPE_PC)
	{		
		sGU_FREEBATTLE_END_NFY FreebatleEnd;
		FreebatleEnd.wOpCode = GU_FREEBATTLE_END_NFY;
		FreebatleEnd.wPacketSize = sizeof(sGU_FREEBATTLE_END_NFY) - 2;
		FreebatleEnd.byFreeBattleResult = eFREEBATTLE_RESULT::FREEBATTLE_RESULT_WIN;
		SendPacket((char*)&FreebatleEnd, sizeof(sGU_FREEBATTLE_END_NFY));
		GetAttributesManager()->showMensageOut = false;
		GetAttributesManager()->PlayerInFreeBatle = false;
		GetAttributesManager()->FreeBatleChellenger = INVALID_TBLIDX;
		
		sGU_FREEBATTLE_END_NFY FreebatleEnd1;
		FreebatleEnd1.wOpCode = GU_FREEBATTLE_END_NFY;
		FreebatleEnd1.wPacketSize = sizeof(sGU_FREEBATTLE_END_NFY) - 2;
		FreebatleEnd1.byFreeBattleResult = eFREEBATTLE_RESULT::FREEBATTLE_RESULT_LOSE;
		PlayerInfo->SendPacket((char*)&FreebatleEnd1, sizeof(sGU_FREEBATTLE_END_NFY));
		PlayerInfo->GetAttributesManager()->showMensageOut = false;
		PlayerInfo->GetAttributesManager()->PlayerInFreeBatle = false;
		PlayerInfo->GetAttributesManager()->FreeBatleChellenger = INVALID_TBLIDX;
		PlayerInfo->GetAttributesManager()->LoseBatle = false;
		GetAttributesManager()->LoseBatle = false;
	}	

	}
}
void Player::TakeMobDemage(uint32 amount)
{	
		int32_t newLife = GetPcProfile()->dwCurLP;		
		newLife -= amount;
		if (newLife <= 0)
		{					
			SetIsFighting(false);
			newLife = 0;
		}
		GetPcProfile()->dwCurLP = newLife;

		sGU_UPDATE_CHAR_LP updLp;
		updLp.handle = GetHandle();
		updLp.wCurLP = GetPcProfile()->dwCurLP = newLife;
		updLp.wMaxLP = GetPcProfile()->avatarAttribute.wLastMaxLP;
		updLp.wOpCode = GU_UPDATE_CHAR_LP;
		updLp.wPacketSize = sizeof(sGU_UPDATE_CHAR_LP) - 2;

		
		SendPacket((char*)&updLp, sizeof(sGU_UPDATE_CHAR_LP));
		SendToPlayerList((char*)&updLp, sizeof(sGU_UPDATE_CHAR_LP));

		if (GetPcProfile()->dwCurLP == 0)
		{
			sGU_UPDATE_CHAR_STATE state;

			state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;
			state.wOpCode = GU_UPDATE_CHAR_STATE;

			state.handle = GetHandle();
			state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_FAINTING;
			state.sCharState.sCharStateDetail.sCharStateFainting.byReason = eFAINT_REASON::FAINT_REASON_HIT;
			
			state.sCharState.sCharStateBase.vCurLoc.x = GetVectorPosition().x;
			state.sCharState.sCharStateBase.vCurLoc.y = GetVectorPosition().y;
			state.sCharState.sCharStateBase.vCurLoc.z = GetVectorPosition().z;
			state.sCharState.sCharStateBase.vCurDir.x = GetVectorOriantation().x;
			state.sCharState.sCharStateBase.vCurDir.y = GetVectorOriantation().y;
			state.sCharState.sCharStateBase.vCurDir.z = GetVectorOriantation().x;
			state.sCharState.sCharStateBase.dwConditionFlag = 0;
			//	res.sCharState.sCharStateBase.bFightMode = false;
			state.sCharState.sCharStateBase.dwStateTime = 2;			

			SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
			SendToPlayerList((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));
		}
	
}
//----------------------------------------
//	Get zeny that is in the bank
//  Currently returning a static value
//  Need to get from the Database 
//----------------------------------------

DWORD Player::GetBankMoney()
{

	return 10000U;
}

//----------------------------------------
//	Get some XP from a mob killed
//	Mob reference
//----------------------------------------
void	Player::RewardExpFromMob(MonsterData& data)
{
	if (GetPcProfile()->byLevel < 70)
	{
		DWORD exp = data.Exp;
		int levelDiff = GetPcProfile()->byLevel - data.Level;
		(levelDiff > 0) ? levelDiff *= 1 : levelDiff *= -1;

		sGU_UPDATE_CHAR_EXP expPacket;
		// hard fix
		//exp /= 10;
		DWORD bonus = 15000;
		
		expPacket.dwIncreasedExp = exp + bonus;
		expPacket.dwAcquisitionExp = exp;
		expPacket.dwBonusExp = bonus;
		expPacket.wOpCode = GU_UPDATE_CHAR_EXP;
		expPacket.wPacketSize = sizeof(sGU_UPDATE_CHAR_EXP) - 2;
		expPacket.handle = GetHandle();
		GetPcProfile()->dwCurExp += (exp + bonus);
		expPacket.dwCurExp = GetPcProfile()->dwCurExp;

		if (GetPcProfile()->dwCurExp >= GetPcProfile()->dwMaxExpInThisLevel)
		{
			expPacket.dwCurExp = GetPcProfile()->dwCurExp -= GetPcProfile()->dwMaxExpInThisLevel;
			LevelUp();
		}
		SendPacket((char*)&expPacket, sizeof(sGU_UPDATE_CHAR_EXP));
	}
}
void Player::RewardDropFromMob(MonsterData& data)
{
	DroppedObject *dropped;
	sITEM_TBLDAT *itemSrc = NULL;
	/* /!\ NEED FUNCTION TO CREATE CORRECT DROP	/!\	*/
	/* ITEM	*/
	
	int DropAmount = rand() % 5;
	for (int i = 0; i <= DropAmount; i++)
	{
	dropped = new DroppedObject;
	dropped->droppedTime = GetTickCount();
	dropped->objType = OBJTYPE_DROPITEM;
	dropped->owner = GetHandle();

	dropped->item.wPacketSize = sizeof(Drop) - 2;
	dropped->item.wOpCode = GU_OBJECT_CREATE;

	dropped->item.Handle = sWorld.AcquireItemSerialId();
	if (rand() % 5 >= 4)
	dropped->item.Tblidx = 11170019 + rand() % 261 + 1;
	else
	dropped->item.Tblidx = 11170019 + rand() % 261 + 1;
	itemSrc = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(dropped->item.Tblidx);

	if (itemSrc == NULL)
	{
		itemSrc = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(dropped->item.Tblidx);
		if (itemSrc == NULL)
		{
			return;
		}
	}
	if (itemSrc != NULL)
	
	
		dropped->item.Type = OBJTYPE_DROPITEM;
		dropped->item.Grade = 0;
		dropped->item.Rank = itemSrc->eRank;
		dropped->item.BattleAttribute = 0;
		dropped->item.Loc.x = data.curPos.x + rand() % 6;
		dropped->item.Loc.y = data.curPos.y;
		dropped->item.Loc.z = data.curPos.z + rand() % 6;
		dropped->item.IsNew = true;
		dropped->item.NeedToIdentify = false;



			/* Add Drop to list	*/
			SendPacket((char*)&dropped->item, sizeof(Drop));
			AddDropToList(*dropped, dropped->item.Handle);
		}
	
	/*	ZENNY	*/
	dropped = new DroppedObject;
	dropped->zenny.dwZenny = data.Drop_Zenny;
	if (dropped->zenny.dwZenny == 0)
	{
		dropped->zenny.dwZenny = 15;
	}

	dropped->objType = OBJTYPE_DROPMONEY;
	dropped->droppedTime = GetTickCount();
	dropped->owner = GetHandle();

	dropped->zenny.wPacketSize = sizeof(Dropzenny) - 2;
	dropped->zenny.wOpCode = GU_OBJECT_CREATE;

	dropped->zenny.Loc.x = data.curPos.x + rand() % 6;
	dropped->zenny.Loc.y = data.curPos.y;
	dropped->zenny.Loc.z = data.curPos.z + rand() % 6;
	dropped->zenny.Dir.x = data.Spawn_Dir.x;
	//dropped->zenny.Dir.y = data.Spawn_Dir.y;
	//dropped->zenny.Dir.z = data.Spawn_Dir.z;

	dropped->zenny.Handle = sWorld.AcquireItemSerialId();
	dropped->zenny.IsNew = false;
	dropped->zenny.Type = OBJTYPE_DROPMONEY;
	SendPacket((char*)&dropped->zenny, sizeof(Dropzenny));
	AddDropToList(*dropped, dropped->zenny.Handle);

}
//----------------------------------------
//	Levelup our player
//----------------------------------------
void	Player::LevelUp()
{
	if (GetPcProfile()->byLevel < 70)
	{
		sGU_UPDATE_CHAR_LEVEL levelPacket;
		sEXP_TBLDAT *pTblExp = (sEXP_TBLDAT*)sTBM.GetExpTable()->FindData(GetPcProfile()->byLevel + 1);

		// fill new level
		GetPcProfile()->byLevel += 1;
		levelPacket.byCurLevel = GetPcProfile()->byLevel;
		levelPacket.byPrevLevel = GetPcProfile()->byLevel - 1;
		levelPacket.dwMaxExpInThisLevel = GetPcProfile()->dwMaxExpInThisLevel = pTblExp->dwNeed_Exp;
		levelPacket.handle = GetHandle();
		levelPacket.wOpCode = GU_UPDATE_CHAR_LEVEL;
		levelPacket.wPacketSize = sizeof(sGU_UPDATE_CHAR_LEVEL) - 2;
		SendPacket((char*)&levelPacket, sizeof(sGU_UPDATE_CHAR_LEVEL));
		SendToPlayerList((char*)&levelPacket, sizeof(sGU_UPDATE_CHAR_LEVEL));
		// calculate our new state
		//characterManager.LevelUp();
		//characterManager.SendRpBallInformation();
		// fill lp ep to max and calculate RP -
		GetPcProfile()->dwCurLP = GetPcProfile()->avatarAttribute.wBaseMaxLP;
		GetPcProfile()->wCurEP = GetPcProfile()->avatarAttribute.wBaseMaxEP;

		// give 1 sp pouint
		sGU_UPDATE_CHAR_SP spPoint;
		GetPcProfile()->dwSpPoint += 1;
		sDB.UpdateSPPoint(GetPcProfile()->dwSpPoint, GetCharacterID());
		spPoint.dwSpPoint = GetPcProfile()->dwSpPoint;
		spPoint.wOpCode = GU_UPDATE_CHAR_SP;
		spPoint.wPacketSize = sizeof(sGU_UPDATE_CHAR_SP) - 2;
		SendPacket((char*)&spPoint, sizeof(sGU_UPDATE_CHAR_SP));

		// save new level to db
		sDB.UpdatePlayerLevel(GetPcProfile()->byLevel, GetCharacterID(), GetPcProfile()->dwCurExp);
	}
}
void	Player::LevelUpByComand(int Level)
{

	sGU_UPDATE_CHAR_LEVEL levelPacket;
	sEXP_TBLDAT *pTblExp = (sEXP_TBLDAT*)sTBM.GetExpTable()->FindData(Level);

	// fill new level
	GetPcProfile()->byLevel = Level;
	levelPacket.byCurLevel = Level;
	levelPacket.byPrevLevel = Level - 1;
	levelPacket.dwMaxExpInThisLevel = GetPcProfile()->dwMaxExpInThisLevel = pTblExp->dwNeed_Exp;
	levelPacket.handle = GetHandle();
	levelPacket.wOpCode = GU_UPDATE_CHAR_LEVEL;
	levelPacket.wPacketSize = sizeof(sGU_UPDATE_CHAR_LEVEL) - 2;
	SendPacket((char*)&levelPacket, sizeof(sGU_UPDATE_CHAR_LEVEL));
	SendToPlayerList((char*)&levelPacket, sizeof(sGU_UPDATE_CHAR_LEVEL));
	// calculate our new state
	//characterManager.LevelUp();
	//characterManager.SendRpBallInformation();
	// fill lp ep to max and calculate RP -
	GetPcProfile()->dwCurLP = GetPcProfile()->avatarAttribute.wBaseMaxLP;
	GetPcProfile()->wCurEP = GetPcProfile()->avatarAttribute.wBaseMaxEP;

	// give 1 sp pouint
	sGU_UPDATE_CHAR_SP spPoint;


	spPoint.dwSpPoint = Level - 1;
	GetPcProfile()->dwSpPoint = spPoint.dwSpPoint;
	spPoint.wOpCode = GU_UPDATE_CHAR_SP;
	spPoint.wPacketSize = sizeof(sGU_UPDATE_CHAR_SP) - 2;
	SendPacket((char*)&spPoint, sizeof(sGU_UPDATE_CHAR_SP));

	// save new level to db
	sDB.UpdatePlayerLevel(GetPcProfile()->byLevel, GetCharacterID(), GetPcProfile()->dwCurExp);
	sDB.UpdateSPPoint(GetPcProfile()->dwSpPoint, GetCharacterID());

}
void Player::SetSpeed(int sppeed)
{
	sGU_UPDATE_CHAR_SPEED speed;
	speed.wOpCode = GU_UPDATE_CHAR_SPEED;
	speed.wPacketSize = sizeof(sGU_UPDATE_CHAR_SPEED) - 2;

	speed.handle = GetHandle();
	speed.fLastWalkingSpeed = sppeed* .50;
	speed.fLastRunningSpeed = sppeed;
	speed.fLastFlySpeed = sppeed* .50;
	speed.fLastFlyBoostSpeed = sppeed;
	speed.fLastFlySpeed2 = sppeed* .50;
	speed.fLastFlyBoostSpeed2 = sppeed;

	SendPacket((char*)&speed, sizeof(sGU_UPDATE_CHAR_SPEED));
	SendToPlayerList((char*)&speed, sizeof(sGU_UPDATE_CHAR_SPEED));
}
//Comand
void Player::ConvertClass(int Class)
{
	sGU_CHAR_CONVERT_CLASS clase;
	clase.wOpCode = GU_CHAR_CONVERT_CLASS;
	clase.wPacketSize = sizeof(sGU_CHAR_CONVERT_CLASS) - 2;

	clase.hTarget = GetHandle();
	clase.byClass = Class;
	if (Class == 0)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_HUMAN_FIGHTER);
	}
	if (Class == 1)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_HUMAN_MYSTIC);
	}
	if (Class == 2)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_HUMAN_ENGINEER);
	}
	if (Class == 3)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_NAMEK_FIGHTER);
	}
	if (Class == 4)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_NAMEK_MYSTIC);
	}
	if (Class == 5)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_MIGHTY_MAJIN);
	}
	if (Class == 6)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_WONDER_MAJIN);
	}
	if (Class == 7)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_STREET_FIGHTER);
		if(skillManager.isSkillLearned(729991) == false)
		m_session->LearnSkill(729991);
	}
	if (Class == 8)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_SWORD_MASTER);
		if (skillManager.isSkillLearned(829991) == false)
		m_session->LearnSkill(829991);
	}
	if (Class == 9)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_CRANE_ROSHI);
		if (skillManager.isSkillLearned(929991) == false)
		m_session->LearnSkill(929991);
	}
	if (Class == 10)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_TURTLE_ROSHI);
		if (skillManager.isSkillLearned(1029991) == false)
		m_session->LearnSkill(1029991);
	}
	if (Class == 11)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_GUN_MANIA);
	}
	if (Class == 12)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_MECH_MANIA);
	}
	if (Class == 13)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_DARK_WARRIOR);
		if (skillManager.isSkillLearned(1329991) == false)
		m_session->LearnSkill(1329991);
	}
	if (Class == 14)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_SHADOW_KNIGHT);
		if (skillManager.isSkillLearned(1429991) == false)
		m_session->LearnSkill(1429991);
	}
	if (Class == 15)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_DENDEN_HEALER);
		if (skillManager.isSkillLearned(1529991) == false)
		m_session->LearnSkill(1529991);
	}
	if (Class == 16)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_POCO_SUMMONER);
		if (skillManager.isSkillLearned(1629991) == false)
		m_session->LearnSkill(1629991);
	}
	if (Class == 17)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_ULTI_MA);
		if (skillManager.isSkillLearned(1729991) == false)
		m_session->LearnSkill(1729991);
	}
	if (Class == 18)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_GRAND_MA);
		if (skillManager.isSkillLearned(1829991) == false)
		m_session->LearnSkill(1829991);
	}
	if (Class == 19)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_PLAS_MA);
		if (skillManager.isSkillLearned(1929991) == false)
		m_session->LearnSkill(1929991);
	}
	if (Class == 20)
	{
		SetMyClass(ePC_CLASS::PC_CLASS_KAR_MA);
		if (skillManager.isSkillLearned(2029991) == false)
		m_session->LearnSkill(2029991);
	}

	SendPacket((char*)&clase, sizeof(sGU_CHAR_CONVERT_CLASS));
	SendToPlayerList((char*)&clase, sizeof(sGU_CHAR_CONVERT_CLASS));
}
//Comand
void Player::ConvertAdult(int Adult)
{
	sGU_CHILD_ADULT_SWITCHED_NFY IsAdult;
	IsAdult.wOpCode = GU_CHILD_ADULT_SWITCHED_NFY;
	IsAdult.wPacketSize = sizeof(sGU_CHILD_ADULT_SWITCHED_NFY) - 2;

	IsAdult.hSubject = GetHandle();
	IsAdult.bIsAdult = Adult;
	IsAdult.wResultCode = GAME_SUCCESS;	
	SendPacket((char*)&IsAdult, sizeof(sGU_CHILD_ADULT_SWITCHED_NFY));
	SendToPlayerList((char*)&IsAdult, sizeof(sGU_CHILD_ADULT_SWITCHED_NFY));
	GetPcProfile()->bIsAdult = Adult;

}
//Comand
void Player::SendUpdateSize(int Size)
{
	sGU_CHANGED_CHAR_SIZE_NFY CharSize;
	CharSize.wOpCode = GU_CHANGED_CHAR_SIZE_NFY;
	CharSize.wPacketSize = sizeof(sGU_CHANGED_CHAR_SIZE_NFY) - 2;

	CharSize.handle = GetHandle();
	CharSize.size = Size;


	SendPacket((char*)&CharSize, sizeof(sGU_CHANGED_CHAR_SIZE_NFY));
	SendToPlayerList((char*)&CharSize, sizeof(sGU_CHANGED_CHAR_SIZE_NFY));

}
//Comand
void Player::SendAddTitle(int TitleID)
{
	sGU_CHARTITLE_ADD title;

	title.wOpCode = GU_CHARTITLE_ADD;
	title.wPacketSize = sizeof(sGU_CHARTITLE_ADD) - 2;
	title.ResultCode = GAME_SUCCESS;
	title.TitleID = TitleID;
	sDB.AddTitle(charid, title.TitleID);
	SendPacket((char*)&title, sizeof(sGU_CHARTITLE_ADD));
}
DWORD Player::GetClassFlag(int Class, int ItemType) const
{

	if (Class == ePC_CLASS::PC_CLASS_HUMAN_FIGHTER)
	{
		if(ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_HUMAN_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return  PC_CLASS_FLAG_HUMAN_FIGHTER;
	}
	else if (Class == ePC_CLASS::PC_CLASS_HUMAN_MYSTIC)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return  PC_CLASS_FLAG_HUMAN_MYSTIC;
	}	
	else if (Class == ePC_CLASS::PC_CLASS_NAMEK_FIGHTER)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return  PC_CLASS_FLAG_NAMEK_FIGHTER;
	}
	else if (Class == ePC_CLASS::PC_CLASS_NAMEK_MYSTIC)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_STAFF)
			return  PC_CLASS_FLAG_NAMEK_MYSTIC;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return  PC_CLASS_FLAG_NAMEK_MYSTIC;
	}
	else if (Class == ePC_CLASS::PC_CLASS_MIGHTY_MAJIN)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return PC_CLASS_FLAG_MAJIN_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return   PC_CLASS_FLAG_MIGHTY_MAJIN;
	}
	else if (Class == ePC_CLASS::PC_CLASS_WONDER_MAJIN)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return PC_CLASS_FLAG_MAJIN_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return   PC_CLASS_FLAG_WONDER_MAJIN;
	}
	else if (Class == ePC_CLASS::PC_CLASS_STREET_FIGHTER)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_HUMAN_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return  PC_CLASS_FLAG_STREET_FIGHTER;
	}
	else if (Class == ePC_CLASS::PC_CLASS_SWORD_MASTER)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return PC_CLASS_FLAG_HUMAN_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return PC_CLASS_FLAG_SWORD_MASTER;
	}
	else if (Class == ePC_CLASS::PC_CLASS_CRANE_ROSHI)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_HUMAN_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return PC_CLASS_FLAG_CRANE_ROSHI;
	}
	else if (Class == ePC_CLASS::PC_CLASS_TURTLE_ROSHI)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return PC_CLASS_FLAG_HUMAN_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return  PC_CLASS_FLAG_TURTLE_ROSHI;
	}	
	else if (Class == ePC_CLASS::PC_CLASS_DARK_WARRIOR)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return PC_CLASS_FLAG_DARK_WARRIOR;
	}
	else if (Class == ePC_CLASS::PC_CLASS_SHADOW_KNIGHT)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3 && ItemType <= eITEM_TYPE::ITEM_TYPE_RING)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return PC_CLASS_FLAG_SHADOW_KNIGHT;
	}
	else if (Class == ePC_CLASS::PC_CLASS_DENDEN_HEALER)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_STAFF)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else 
			return  PC_CLASS_FLAG_DENDEN_HEALER;
	}
	else if (Class == ePC_CLASS::PC_CLASS_POCO_SUMMONER)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_STAFF)
			return PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else 
			return  PC_CLASS_FLAG_POCO_SUMMONER;
	}
	else if (Class == ePC_CLASS::PC_CLASS_GRAND_MA)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else 
			return  PC_CLASS_FLAG_GRAND_MA;
	}
	else if (Class == ePC_CLASS::PC_CLASS_ULTI_MA)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else 
			return  PC_CLASS_FLAG_ULTI_MA;
	}	
	else if (Class == ePC_CLASS::PC_CLASS_PLAS_MA)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else 
			return  PC_CLASS_FLAG_PLAS_MA;
	}
	else if (Class == ePC_CLASS::PC_CLASS_KAR_MA)
	{
		if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET || ItemType == eITEM_TYPE::ITEM_TYPE_PANTS || ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
			return  PC_CLASS_FLAG_NAMEK_MIX;
		else if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
			return  PC_CLASS_FLAG_MIX;
		else if (ItemType >= eITEM_TYPE::ITEM_TYPE_COSTUME && ItemType <= eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
			return  PC_CLASS_FLAG_FULLMIX;
		else
			return  PC_CLASS_FLAG_KAR_MA;
	}		
}
void Player::SetGSHandle()
{
	sql::ResultSet* result = sDB.executes("UPDATE Characters SET GSHandle = %d where characterID = %d", GetHandle(), charid);
}