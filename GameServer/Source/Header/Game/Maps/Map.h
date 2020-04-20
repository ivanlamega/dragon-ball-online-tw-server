#ifndef		_MAP__H
# define	_MAP__H

#pragma once

#include <Define.h>
#include <ThreadingModel.h>
#include <TableAll.h>
#include "MapRefManager.h"
#include <Timer.h>
#include <set>
#include <mutex>

#define DEFAULT_VISIBILITY_DISTANCE 100.0f
#define DEFAULT_MOB_VISIBILITY_DISTANCE 100.0f
#define DEFAULT_NPC_VISIBILITY_DISTANCE 60.0f
#define DEFAULT_PC_VISIBILITY_DISTANCE 200.0f

class Packet;
class Player;
class WorldObject;

class Map
{
	friend class MapReference;
	friend class NpcReference;
	friend class MobReference;
	friend class WorldObjectReference;
protected:
	Map(uint32 id);
	Map(uint32 id, uint32 mobtblidx, SpawnMOB mobSpawn); //For adding new mobs to maps
public:
	virtual					~Map();

	virtual void			Update(const uint32&);

	uint32					GetId(void) const { return mapID; }
	bool					CanUnload(uint32 diff)
	{
		if (!m_unloadTimer) return false;
		if (m_unloadTimer <= diff) return true;
		m_unloadTimer -= diff;
		return false;
	}
	typedef MapRefManager PlayerList;
	PlayerList const& GetPlayers() const { return m_mapRefManager; }
	bool HavePlayers() const { return !m_mapRefManager.isEmpty(); }
	typedef WorldObjectRefManager WorldObjectList;
	WorldObjectList const& GetWorldObject() const { return m_wobjRefManager; }

	void					RemoveAllObjectsInRemoveList();
	virtual bool			Add(Player*);
	virtual void			Remove(Player*, bool);
	template<class T> void	Add(T*);
	template<class T> void	Remove(T*, bool);
	static void				DeleteFromWorld(Player* pl);

private:
	void					UpdatePlayerVisibility();
	void					CheckObjectInRange();
	void					movepoit();

protected:
	// SERVER
	// OBJECT REF MANAGER
	MapRefManager			m_mapRefManager;
	NpcRefManager			m_npcRefManager;
	MobRefManager			m_mobRefManager;
	WorldObjectRefManager	m_wobjRefManager;

	uint32					m_unloadTimer;
	std::set<Object*>		i_objectsToRemove;

	std::thread				updateVisibilityThread;
	std::mutex				map_mutex;
	bool					performVisibity;
	// MAP PARAMETERS
	uint32					mapID;
	float					m_VisibleDistance;
	eGAMERULE_TYPE			rules;
};
class WorldMap : public Map
{
private:
	//using Map::GetPersistentState;                      // hide in subclass for overwrite
public:
	WorldMap(uint32 id) : Map(id) {}
	~WorldMap() {}

	// can't be nullptr for loaded map
	//WorldPersistentState* GetPersistanceState() const;
};
#endif // !_MAP__H
