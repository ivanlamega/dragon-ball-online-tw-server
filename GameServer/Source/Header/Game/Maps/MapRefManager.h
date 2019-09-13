#ifndef _MAPREFMANAGER
#define _MAPREFMANAGER

#include <LinkedElement\RefManager.h>

class MapReference;
class NpcReference;
class MobReference;
class WorldObjectReference;

class Map;
class Object;
class WorldObject;
class Player;
class Npc;
class Mob;

class MapRefManager : public RefManager<Map, Player>
{
public:
	typedef LinkedListHead::Iterator< MapReference > iterator;
	typedef LinkedListHead::Iterator< MapReference const > const_iterator;

	MapReference* getFirst() { return (MapReference*)RefManager<Map, Player>::getFirst(); }
	MapReference const* getFirst() const { return (MapReference const*)RefManager<Map, Player>::getFirst(); }
	MapReference* getLast() { return (MapReference*)RefManager<Map, Player>::getLast(); }
	MapReference const* getLast() const { return (MapReference const*)RefManager<Map, Player>::getLast(); }

	iterator begin() { return iterator(getFirst()); }
	iterator end() { return iterator(nullptr); }
	iterator rbegin() { return iterator(getLast()); }
	iterator rend() { return iterator(nullptr); }
	const_iterator begin() const { return const_iterator(getFirst()); }
	const_iterator end() const { return const_iterator(nullptr); }
};
class NpcRefManager : public RefManager<Map, Npc>
{
public:
	typedef LinkedListHead::Iterator< NpcReference > iterator;
	typedef LinkedListHead::Iterator< NpcReference const > const_iterator;

	NpcReference* getFirst() { return (NpcReference*)RefManager<Map, Npc>::getFirst(); }
	NpcReference const* getFirst() const { return (NpcReference const*)RefManager<Map, Npc>::getFirst(); }
	NpcReference* getLast() { return (NpcReference*)RefManager<Map, Npc>::getLast(); }
	NpcReference const* getLast() const { return (NpcReference const*)RefManager<Map, Npc>::getLast(); }

	iterator begin() { return iterator(getFirst()); }
	iterator end() { return iterator(nullptr); }
	iterator rbegin() { return iterator(getLast()); }
	iterator rend() { return iterator(nullptr); }
	const_iterator begin() const { return const_iterator(getFirst()); }
	const_iterator end() const { return const_iterator(nullptr); }
};
class MobRefManager : public RefManager<Map, Mob>
{
public:
	typedef LinkedListHead::Iterator< MobReference > iterator;
	typedef LinkedListHead::Iterator< MobReference const > const_iterator;

	MobReference* getFirst() { return (MobReference*)RefManager<Map, Mob>::getFirst(); }
	MobReference const* getFirst() const { return (MobReference const*)RefManager<Map, Mob>::getFirst(); }
	MobReference* getLast() { return (MobReference*)RefManager<Map, Mob>::getLast(); }
	MobReference const* getLast() const { return (MobReference const*)RefManager<Map, Mob>::getLast(); }

	iterator begin() { return iterator(getFirst()); }
	iterator end() { return iterator(nullptr); }
	iterator rbegin() { return iterator(getLast()); }
	iterator rend() { return iterator(nullptr); }
	const_iterator begin() const { return const_iterator(getFirst()); }
	const_iterator end() const { return const_iterator(nullptr); }
};
class WorldObjectRefManager : public RefManager<Map, WorldObject>
{
public:
	typedef LinkedListHead::Iterator< WorldObjectReference > iterator;
	typedef LinkedListHead::Iterator< WorldObjectReference const > const_iterator;

	WorldObjectReference* getFirst() { return (WorldObjectReference*)RefManager<Map, WorldObject>::getFirst(); }
	WorldObjectReference const* getFirst() const { return (WorldObjectReference const*)RefManager<Map, WorldObject>::getFirst(); }
	WorldObjectReference* getLast() { return (WorldObjectReference*)RefManager<Map, WorldObject>::getLast(); }
	WorldObjectReference const* getLast() const { return (WorldObjectReference const*)RefManager<Map, WorldObject>::getLast(); }

	iterator begin() { return iterator(getFirst()); }
	iterator end() { return iterator(nullptr); }
	iterator rbegin() { return iterator(getLast()); }
	iterator rend() { return iterator(nullptr); }
	const_iterator begin() const { return const_iterator(getFirst()); }
	const_iterator end() const { return const_iterator(nullptr); }
};
#endif
