#include <Game\Maps\Map.h>
#include <Game\Object\Player.h>
#include <Game\Object\Npc.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Object.h>
#include <Logger.h>
#include <Game\World\World.h>
#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>

//----------------------------------------
//	Map Constructor, will insitiate the mob and npc in this world id
//----------------------------------------
Map::Map(uint32 id) :
	mapID(id), m_VisibleDistance(DEFAULT_VISIBILITY_DISTANCE), m_unloadTimer(0)
{
	performVisibity = true;

	sLog.outDebug("Map: %d created", id);
	/// <li> Fill Map Data
	sWORLD_TBLDAT* world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(id);
	/// <li> Create the data for spawn NPC
	SpawnTable *pNpcSpawnTbl = sTBM.GetNpcSpawnTable(world->tblidx);

	for (Table::TABLEIT itNPCSpawn = pNpcSpawnTbl->Begin(); itNPCSpawn != pNpcSpawnTbl->End(); ++itNPCSpawn)
	{
		sSPAWN_TBLDAT* pNPCSpwnTblData = (sSPAWN_TBLDAT*)itNPCSpawn->second;
		sNPC_TBLDAT* pNPCTblData = (sNPC_TBLDAT*)sTBM.GetNpcTable()->FindData(pNPCSpwnTblData->mob_Tblidx);
		if (pNPCTblData)
		{
			Npc *created_npc = new Npc;
			if (created_npc->Create(pNPCSpwnTblData, pNPCTblData) == true)
			{
				if (pNPCTblData->byJob == eNPC_JOB::NPC_JOB_SCOUTER_MERCHANT || pNPCTblData->byJob == eNPC_JOB::NPC_JOB_GAMBLE_MERCHANT || pNPCTblData->byJob == eNPC_JOB::NPC_JOB_MIX_MASTER || pNPCTblData->byJob == 47 || pNPCTblData->byJob == 50)
				{
					delete created_npc;
				}
				else
				created_npc->GetMapRef().link(this, created_npc);
			}
			else
				delete created_npc;
		}
	}
	/// <li> Create the data for spawn MOB
	SpawnTable* pMOBSpawnTbl = sTBM.GetMobSpawnTable(world->tblidx);
	for (Table::TABLEIT itMOBSpawn = pMOBSpawnTbl->Begin(); itMOBSpawn != pMOBSpawnTbl->End(); ++itMOBSpawn)
	{
		sSPAWN_TBLDAT* pMOBSpwnTblData = (sSPAWN_TBLDAT*)itMOBSpawn->second;
		sMOB_TBLDAT* pMOBTblData = (sMOB_TBLDAT*)sTBM.GetMobTable()->FindData(pMOBSpwnTblData->mob_Tblidx);
		if (pMOBTblData)
		{
			Mob* created_mob = new Mob;
			if (created_mob->Create(pMOBSpwnTblData, pMOBTblData) == true)
			{
				created_mob->GetMapRef().link(this, created_mob);
			}
			else
				delete created_mob;
		}
	}
	/// <li> Create the data for World dynamic Object
	DynamicObjectTable* pDYNSpwnTblData = sTBM.GetDynamicObjectTable();
	/// <li> Create the data for World Object
	ObjectTable* pOBJSpwnTblData = sTBM.GetObjectTable(world->tblidx);
	for (Table::TABLEIT itOBJSpawn = pOBJSpwnTblData->Begin(); itOBJSpawn != pOBJSpwnTblData->End(); ++itOBJSpawn)
	{
		sOBJECT_TBLDAT* objTblData = (sOBJECT_TBLDAT*)itOBJSpawn->second;
		if (objTblData)
		{
			WorldObject *worldobj = new WorldObject();
			if (worldobj->Create(*objTblData) == true)
			{
				worldobj->GetMapRef().link(this, worldobj);
			}
			else
				delete worldobj;
		}
	}
	sLog.outDebug("Map: %d loaded: %d Npc - %d Mob - %d Object", GetId(), pNpcSpawnTbl->GetNumberOfTables(), pMOBSpawnTbl->GetNumberOfTables(), pOBJSpwnTblData->GetNumberOfTables());
	updateVisibilityThread = std::thread(&Map::UpdatePlayerVisibility, this);
}
//----------------------------------------
//	Map destructor
//----------------------------------------
Map::~Map()
{
	performVisibity = false;
	m_mapRefManager.clearReferences();
	m_npcRefManager.clearReferences();
	m_mobRefManager.clearReferences();
	m_wobjRefManager.clearReferences();

	if (updateVisibilityThread.joinable())
		updateVisibilityThread.join();
	for (auto m_mobRefIter = m_mobRefManager.begin(); m_mobRefIter != m_mobRefManager.end(); ++m_mobRefIter)
	{
		delete m_mobRefIter->getSource();
	}
	for (auto iter = m_npcRefManager.begin(); iter != m_npcRefManager.end(); ++iter)
	{
		delete iter->getSource();
	}
	for (auto iter = m_wobjRefManager.begin(); iter != m_wobjRefManager.end(); ++iter)
	{
		delete iter->getSource();
	}
}
//----------------------------------------
//	Remove pending object
//----------------------------------------
void Map::RemoveAllObjectsInRemoveList()
{
	if (i_objectsToRemove.empty())
		return;
	map_mutex.lock();
	while (!i_objectsToRemove.empty())
	{
		Object* obj = *i_objectsToRemove.begin();
		i_objectsToRemove.erase(i_objectsToRemove.begin());

		switch (obj->GetTypeId())
		{
			case eOBJTYPE::OBJTYPE_PC:
			{
				Remove((Player*)obj, true);
				break;
			}
			default:
			{
				sLog.outError("Non-grid object (TypeId: %u) in grid object removing list, ignored.", obj->GetTypeId());
				break;
			}
		}
	}
	map_mutex.unlock();
}
//----------------------------------------
//	Add player to linker & in map
//----------------------------------------
bool Map::Add(Player* player)
{
	map_mutex.lock();
	player->GetMapRef().link(this, player);
	map_mutex.unlock();
	player->SetMap(this);
	player->AddToWorld();

	sGU_SYSTEM_DISPLAY_TEXT test;
	memcpy(test.awchMessage, (L"Welcome To DragonBall Online Emulator Server Test!"), 257);
	memcpy(test.awGMChar, (L" GM "), 17);
	test.byDisplayType = eSERVER_TEXT_TYPE::SERVER_TEXT_SYSTEM;
	test.wMessageLengthInUnicode = strlen("Welcome To DragonBall Online Emulator Server Test!");
	test.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	test.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;
	player->SendPacket((char*)&test, sizeof(sGU_SYSTEM_DISPLAY_TEXT));

	if (sWorld.DragonBallEventa == true)
	{
		printf("Dragon Ball Hunt %d \n", sWorld.DragonBallEventa);
		sGU_DRAGONBALL_SCHEDULE_INFO res;

		res.bIsAlive = sWorld.DragonBallEventa;
		res.byEventType = eSCHEDULE_EVENT_TYPE::SCHEDULE_EVENT_TYPE_BASIC_DRAGONBALL;
		res.byTermType = 1;
		res.dwMainTerm = 1;
		res.dwSubTerm = 1;
		res.nEndTime = 100;
		res.nStartTime = 1;
		res.wOpCode = GU_DRAGONBALL_SCHEDULE_INFO;
		res.wPacketSize = sizeof(sGU_DRAGONBALL_SCHEDULE_INFO) - 2;

		player->SendPacket((char*)&res, sizeof(sGU_DRAGONBALL_SCHEDULE_INFO));

		sGU_SYSTEM_DISPLAY_TEXT sNotice;
		sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
		sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;
		sNotice.byDisplayType = 3;
		wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH, L" Dragon Ball Hunt is Running");
		wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L"System"));
		sNotice.wMessageLengthInUnicode = 50;
		player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));
	}
	if (sWorld.BonusActive == true)
	{
		sGU_SYSTEM_DISPLAY_TEXT sNotice;
		sNotice.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
		sNotice.wPacketSize = sizeof(sGU_SYSTEM_DISPLAY_TEXT) - 2;
		sNotice.byDisplayType = 3;
		wcscpy_s(sNotice.awchMessage, BUDOKAI_MAX_NOTICE_LENGTH, L" Exp Event Is Running");
		wcscpy_s(sNotice.awGMChar, MAX_SIZE_CHAR_NAME_UNICODE, (L"System"));
		sNotice.wMessageLengthInUnicode = 50;
		player->SendPacket((char*)&sNotice, sizeof(sGU_SYSTEM_DISPLAY_TEXT));		
	 }
	return true;
}
//----------------------------------------
//	Templated add for NPC, MONEY, LOOT ETC
//----------------------------------------
template<class T>
void
Map::Add(T* obj)
{
	assert(obj);

	obj->SetMap(this);

	obj->AddToWorld();

	if (obj->isActiveObject())
		AddToActive(obj);

	obj->SetItsNewObject(true);
	UpdateObjectVisibility(obj, p);
	obj->SetItsNewObject(false);
}
//----------------------------------------
//	Templated remove for NPC, MONEY, LOOT, ETC
//----------------------------------------
template<class T>
void
Map::Remove(T* obj, bool remove)
{
	assert(obj);
	if (obj->isActiveObject())
		RemoveFromActive(obj);

	if (remove)
		obj->CleanupsBeforeDelete();
	else
		obj->RemoveFromWorld();

	UpdateObjectVisibility(obj, p);                   // i think will be better to call this function while object still in grid, this changes nothing but logically is better(as for me)
	obj->ResetMap();
	if (remove)
	{
		// if option set then object already saved at this moment
		if (!sWorld.getConfig(CONFIG_BOOL_SAVE_RESPAWN_TIME_IMMEDIATELY))
			obj->SaveRespawnTime();

		// Note: In case resurrectable corpse and pet its removed from global lists in own destructor
		delete obj;
	}
}
//----------------------------------------
//	Remove player from map and send the destruct obj to all player in the map
//----------------------------------------
void Map::Remove(Player* player, bool remove)
{
	map_mutex.lock();
	MapRefManager::iterator m_mapRefIter = NULL;
	for (m_mapRefIter = m_mapRefManager.begin(); m_mapRefIter != m_mapRefManager.end(); ++m_mapRefIter)
	{
		Player* plr = static_cast<Player*>(m_mapRefIter->getSource());
		if (player != plr)
		{
			sGU_OBJECT_DESTROY sPacket;

			sPacket.wOpCode = GU_OBJECT_DESTROY;
			sPacket.handle = player->GetHandle();
			sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

			plr->SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));
		}
	}
	if (remove == true)
		player->CleanupsBeforeDelete();
	else
		player->RemoveFromWorld();

	if (m_mapRefIter == player->GetMapRef())
		m_mapRefIter = m_mapRefIter->nocheck_prev();

	player->GetMapRef().unlink();
	player->ResetMap();
	if (remove == true)
	{
		DeleteFromWorld(player);
	}
	map_mutex.unlock();
}
//----------------------------------------
//	Delete player from this world and also delete the player it self (use for logout)
//----------------------------------------
void Map::DeleteFromWorld(Player* pl)
{
	//sObjectAccessor.RemoveObject(pl);
	delete pl;
}
//----------------------------------------
//	Update call each Tick()
//----------------------------------------
void Map::Update(const uint32& t_diff)
{
	/// update entity at tick
	map_mutex.lock();
	for (auto m_mapRefIter = m_mapRefManager.begin(); m_mapRefIter != m_mapRefManager.end(); ++m_mapRefIter)
	{
		Player* plr = static_cast<Player*>(m_mapRefIter->getSource());
		if (plr && plr->IsInWorld())
		{
			plr->Update(t_diff, t_diff);
		}
	}	
	for (auto m_wobjRefIter = m_wobjRefManager.begin(); m_wobjRefIter != m_wobjRefManager.end(); ++m_wobjRefIter)
	{
		WorldObject* curr_wObj = static_cast<WorldObject*>(m_wobjRefIter->getSource());
		if (curr_wObj)
		{
		}
	}
	for (auto m_mobRefIter = m_mobRefManager.begin(); m_mobRefIter != m_mobRefManager.end(); ++m_mobRefIter)
	{
		Mob* curr_Mob = static_cast<Mob*>(m_mobRefIter->getSource());
		if (curr_Mob && curr_Mob->IsInWorld())
		{
			curr_Mob->Update(t_diff, t_diff);
		}
	}
	for (auto m_npcRefIter = m_npcRefManager.begin(); m_npcRefIter != m_npcRefManager.end(); ++m_npcRefIter)
	{
		Npc* curr_Npc = static_cast<Npc*>(m_npcRefIter->getSource());
		if (curr_Npc && curr_Npc->IsInWorld())
		{
			curr_Npc->Update(t_diff, t_diff);
		}
	}
	map_mutex.unlock();
}
//----------------------------------------
//	Update the player and also check visibility from other player
//----------------------------------------
void Map::CheckObjectInRange()
{
	for (auto iter = m_mapRefManager.begin(); iter != m_mapRefManager.end(); ++iter)
	{
		Player* plr = static_cast<Player*>(iter->getSource());
		if (plr && plr->IsInWorld())
		{
			for (auto m_mapRefIterbis = m_mapRefManager.begin(); m_mapRefIterbis != m_mapRefManager.end(); ++m_mapRefIterbis)
			{
				Player* plrbis = static_cast<Player*>(m_mapRefIterbis->getSource());
				if (plrbis && plrbis->IsInWorld() && plr->GetHandle() != plrbis->GetHandle())
				{
					sVECTOR3 owner, other;
					plr->GetPosition(owner.x, owner.y, owner.z);
					plrbis->GetPosition(other.x, other.y, other.z);
					float distance = NtlGetDistance(owner.x, owner.z, other.x, other.z);
					if (distance <= DEFAULT_VISIBILITY_DISTANCE)
					{
						if (plr->isInList(plrbis->GetHandle()) == false)
						{
							plr->FillList(*plrbis);
							plr->BuildPacketForNewPlayer(*plrbis);
						}
					}
					else
					{
						if (plr->isInList(plrbis->GetHandle()) == true)
						{
							sGU_OBJECT_DESTROY sPacket;

							sPacket.wOpCode = GU_OBJECT_DESTROY;
							sPacket.handle = plrbis->GetHandle();
							sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

							plr->SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));

							plr->RemoveFromList(*plrbis);
						}
					}
				}
			}
		}
	}
	for (auto iter = m_npcRefManager.begin(); iter != m_npcRefManager.end(); ++iter)
	{
		Npc* curr_Npc = static_cast<Npc*>(iter->getSource());
		for (auto m_mapRefIterbis = m_mapRefManager.begin(); m_mapRefIterbis != m_mapRefManager.end(); ++m_mapRefIterbis)
		{
			Player* plr = static_cast<Player*>(m_mapRefIterbis->getSource());
			if (plr && curr_Npc && plr->IsInWorld())
			{
				sVECTOR3 owner;
				plr->GetPosition(owner.x, owner.y, owner.z);

				float distance = NtlGetDistance(owner.x, owner.z, curr_Npc->GetNpcData().curPos.x, curr_Npc->GetNpcData().curPos.z);
				if (distance <= DEFAULT_VISIBILITY_DISTANCE)
				{
					if (plr->isInList(curr_Npc->GetHandle()) == false && curr_Npc->GetIsDead() == false)
					{
						plr->FillList(*curr_Npc);
						SpawnNPC spawn;
						curr_Npc->BuildPacketForSpawn(spawn);
						plr->SendPacket((char*)&spawn, sizeof(SpawnNPC));
					}
				}
				else
				{
					if (plr->isInList(curr_Npc->GetHandle()) == true)
					{
						sGU_OBJECT_DESTROY sPacket;

						sPacket.wOpCode = GU_OBJECT_DESTROY;
						sPacket.handle = curr_Npc->GetHandle();
						sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

						plr->SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));

						plr->RemoveFromList(*curr_Npc);
					}
				}
			}
		}
	}
	for (auto iter = m_mobRefManager.begin(); iter != m_mobRefManager.end(); ++iter)
	{
		Mob* curr_Mob = static_cast<Mob*>(iter->getSource());
		if (curr_Mob && curr_Mob->IsInWorld())
		{
			// crash here m_mapRefManager.begin == NULL
			for (auto m_mapRefIterbis = m_mapRefManager.begin(); m_mapRefIterbis != m_mapRefManager.end(); ++m_mapRefIterbis)
			{
				Player* plr = static_cast<Player*>(m_mapRefIterbis->getSource());
				if (plr && plr->IsInWorld())
				{
					sVECTOR3 owner;
					plr->GetPosition(owner.x, owner.y, owner.z);

					float distance = NtlGetDistance(owner.x, owner.z, curr_Mob->GetMobData().curPos.x, curr_Mob->GetMobData().curPos.z);
					if (distance <= DEFAULT_VISIBILITY_DISTANCE && curr_Mob->GetIsSpawn() == true)
					{
						if (plr->isInList(curr_Mob->GetHandle()) == false)
						{
							plr->FillList(*curr_Mob);
							SpawnMOB spawn;
							curr_Mob->BuildPacketForSpawn(spawn);
							plr->SendPacket((char*)&spawn, sizeof(SpawnMOB));
						}
					}
					else
					{
						if (plr->isInList(curr_Mob->GetHandle()) == true)
						{
							sGU_OBJECT_DESTROY sPacket;

							sPacket.wOpCode = GU_OBJECT_DESTROY;
							sPacket.handle = curr_Mob->GetHandle();
							sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

							plr->SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));
							plr->RemoveFromList(*curr_Mob);
						}
					}
				}
			}
		}
	}
}
void Map::UpdatePlayerVisibility()
{
	while (performVisibity == true)
	{
		RemoveAllObjectsInRemoveList(); // fix crash ?
		if (GetPlayers().getSize() > 0)
		{
			map_mutex.lock();
			CheckObjectInRange();
			map_mutex.unlock();
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}