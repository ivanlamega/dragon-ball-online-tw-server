#include <Game\Object\Player.h>
#include <CommunitySession.h>
#include <Community.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <Packet\Community\PacketTU.h>
#include <Game\Maps\MapManager.h>
#include <Game\Object\Npc.h>

//----------------------------------------
//	Player Constructor, init all info
//----------------------------------------
Player::Player(CommunitySession* session) : Object()
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
	isFlying = GetFlying();
	handle = 0;
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
	
}
//------------------------------------------
//		SETTER
//------------------------------------------

void Player::SetMoveDirection(BYTE movementDirection)
{
	GetState()->sCharStateDetail.sCharStateMoving.byMoveDirection = movementDirection;
}
void Player::SetSession(CommunitySession* s)
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
CommunitySession* Player::GetSession() const
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
	handle = GetGSHandle();
	return true;
}
//----------------------------------------
//	Trigger by Map Tick()
//----------------------------------------
void Player::Update(uint32 _update_diff, uint32 _time)
{
		return;
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


void Player::SetFlying(bool isFlying)
{
	this->isFlying = isFlying;
}

bool Player::GetFlying()
{
	return this->isFlying;
}

void	Player::TakeDamage(uint32 amount)
{
	return;
}

HOBJECT Player::GetGSHandle()
{
	sql::ResultSet* result = sDB.executes("Select GSHandle from characters where characterID = %d", charid);
	if (result)
		return result->getInt("GSHandle");
	else
		return INVALID_ACCOUNTID;
}


