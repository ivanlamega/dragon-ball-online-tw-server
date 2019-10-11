#include <Game\Maps\MapManager.h>
#include <Logger.h>
#include <World.h>
#include <WorldTable.h>

#define CLASS_LOCK AKCore::ClassLevelLockable<MapManager, std::recursive_mutex>
INSTANTIATE_SINGLETON_2(MapManager, CLASS_LOCK);
INSTANTIATE_CLASS_MUTEX(MapManager, std::recursive_mutex);

//----------------------------------------
//	Constructor
//----------------------------------------
MapManager::MapManager()
{
	i_timer.SetInterval(MIN_MAP_UPDATE_DELAY);
}
//----------------------------------------
//	Destructor
//----------------------------------------
MapManager::~MapManager()
{
	for (MapMapType::iterator iter = i_maps.begin(); iter != i_maps.end(); ++iter)
	{
		sLog.outDetail("Removing map: '%d'", iter->second->GetId());
		delete iter->second;
	}
}
//----------------------------------------
//	Create a new map
//	@param id - MapId of the to be created map. @param obj WorldObject for which the map is to be created. Must be player for Instancable maps.
//----------------------------------------
Map* MapManager::CreateMap(uint32 id)
{
	Guard _guard(*this);

	Map* m;
	// create regular non-instanceable map
	m = FindMap(id);
	if (m == nullptr)
	{
		m = new WorldMap(id);
		i_maps[MapID(id)] = m;
	}
	return m;
}
//----------------------------------------
//	Find a map
//	@param id - MapId of the to be map to found.
//----------------------------------------
Map* MapManager::FindMap(uint32 mapid) const
{
	Guard guard(*this);
	for (MapMapType::const_iterator iter = i_maps.begin(); iter != i_maps.end(); iter++)
	{
		if (iter->second->GetId() == mapid)
			return iter->second;
	}
	return nullptr;
}
//----------------------------------------
//	Ticl
//	@param id - 1000 - one second in MS + latency
//----------------------------------------
void MapManager::Update(uint32 diff)
{
	i_timer.Update(diff);
	if (!i_timer.Passed())
		return;

	for (MapMapType::iterator iter = i_maps.begin(); iter != i_maps.end(); ++iter)
		iter->second->Update((uint32)i_timer.GetCurrent());

	// remove all maps which can be unloaded
	MapMapType::iterator iter = i_maps.begin();
	while (iter != i_maps.end())
	{
		Map* pMap = iter->second;
		// check if map can be unloaded
		if (pMap->CanUnload((uint32)i_timer.GetCurrent()))
		{
			//pMap->UnloadAll(true);
			delete pMap;

			i_maps.erase(iter++);
		}
		else
			++iter;
	}

	i_timer.SetCurrent(0);
}

//----------------------------------------
//	Remove all object to have to be removed
//----------------------------------------
void MapManager::RemoveAllObjectsInRemoveList()
{
	for (MapMapType::iterator iter = i_maps.begin(); iter != i_maps.end(); ++iter)
		iter->second->RemoveAllObjectsInRemoveList();
}
//----------------------------------------
//	Unload all object at all maps
//----------------------------------------
void MapManager::UnloadAll()
{
	/*for (MapMapType::iterator iter = i_maps.begin(); iter != i_maps.end(); ++iter)
	iter->second->UnloadAll(true);*/

	while (!i_maps.empty())
	{
		delete i_maps.begin()->second;
		i_maps.erase(i_maps.begin());
	}
}