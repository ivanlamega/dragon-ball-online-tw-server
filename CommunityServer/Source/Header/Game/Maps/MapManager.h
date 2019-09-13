#ifndef AKCORE_MAPMANAGER_H
#define AKCORE_MAPMANAGER_H

#include <Define.h>
#include <Singleton.h>
#include "Map.h"
#include "Map\Tutorial.h"

#define MIN_MAP_UPDATE_DELAY    50

class Transport;
class BattleGround;

struct MapID
{
	explicit MapID(uint32 id) : nMapId(id){}
	MapID(uint32 id, uint32 instid) : nMapId(id){}

	bool operator<(const MapID& val) const
	{
		if (nMapId == val.nMapId)
			return nInstanceId < val.nInstanceId;

		return nMapId < val.nMapId;
	}

	bool operator==(const MapID& val) const { return nMapId == val.nMapId && nInstanceId == val.nInstanceId; }

	uint32 nMapId;
	uint32 nInstanceId;
};

class MapManager : public AKCore::Singleton<MapManager, AKCore::ClassLevelLockable<MapManager, std::recursive_mutex> >
{
	friend class AKCore::OperatorNew<MapManager>;

	typedef std::recursive_mutex LOCK_TYPE;
	typedef std::lock_guard<LOCK_TYPE> LOCK_TYPE_GUARD;
	typedef AKCore::ClassLevelLockable<MapManager, std::recursive_mutex>::Lock Guard;

public:
	typedef std::map<MapID, Map* > MapMapType;

	Map* CreateMap(uint32);
	Map* FindMap(uint32 mapid) const;
	void Update(uint32);
	void SetMapUpdateInterval(uint32 t)
	{
		if (t > MIN_MAP_UPDATE_DELAY)
			t = MIN_MAP_UPDATE_DELAY;

		i_timer.SetInterval(t);
		i_timer.Reset();
	}
	void UnloadAll();
	void RemoveAllObjectsInRemoveList();
	// get list of all maps
	const MapMapType& Maps() const { return i_maps; }
	template<typename Do>
	void DoForAllMapsWithMapId(uint32 mapId, Do& _do);
private:
	MapManager();
	~MapManager();
	MapManager(const MapManager&);
	MapManager& operator=(const MapManager&);
	MapMapType i_maps;
	IntervalTimer i_timer;
};

template<typename Do>
inline void MapManager::DoForAllMapsWithMapId(uint32 mapId, Do& _do)
{
	MapMapType::const_iterator start = i_maps.lower_bound(MapID(mapId));
	MapMapType::const_iterator end = i_maps.lower_bound(MapID(mapId + 1));
	for (MapMapType::const_iterator itr = start; itr != end; ++itr)
		_do(itr->second);
}

#define sMapMgr MapManager::Instance()

#endif
