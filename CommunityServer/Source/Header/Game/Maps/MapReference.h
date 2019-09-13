#ifndef _MAPREFERENCE_H
#define _MAPREFERENCE_H

#include <LinkedElement\Reference.h>
#include "Map.h"

class MapReference : public Reference<Map, Player>
{
protected:
	void targetObjectBuildLink() override
	{
		// called from link()
		getTarget()->m_mapRefManager.insertFirst(this);
		getTarget()->m_mapRefManager.incSize();
	}
	void targetObjectDestroyLink() override
	{
		// called from unlink()
		if (isValid()) getTarget()->m_mapRefManager.decSize();
	}
	void sourceObjectDestroyLink() override
	{
		// called from invalidate()
		getTarget()->m_mapRefManager.decSize();
	}
public:
	MapReference() : Reference<Map, Player>() {}
	~MapReference() { unlink(); }
	MapReference* next() { return (MapReference*)Reference<Map, Player>::next(); }
	MapReference const* next() const { return (MapReference const*)Reference<Map, Player>::next(); }
	MapReference* nockeck_prev() { return (MapReference*)Reference<Map, Player>::nocheck_prev(); }
	MapReference const* nocheck_prev() const { return (MapReference const*)Reference<Map, Player>::nocheck_prev(); }
};

class NpcReference : public Reference<Map, Npc>
{
protected:
	void targetObjectBuildLink() override
	{
		// called from link()
		getTarget()->m_npcRefManager.insertFirst(this);
		getTarget()->m_npcRefManager.incSize();
	}
	void targetObjectDestroyLink() override
	{
		// called from unlink()
		if (isValid()) getTarget()->m_npcRefManager.decSize();
	}
	void sourceObjectDestroyLink() override
	{
		// called from invalidate()
		getTarget()->m_npcRefManager.decSize();
	}
public:
	NpcReference() : Reference<Map, Npc>() {}
	~NpcReference() { unlink(); }
	NpcReference* next() { return (NpcReference*)Reference<Map, Npc>::next(); }
	NpcReference const* next() const { return (NpcReference const*)Reference<Map, Npc>::next(); }
	NpcReference* nockeck_prev() { return (NpcReference*)Reference<Map, Npc>::nocheck_prev(); }
	NpcReference const* nocheck_prev() const { return (NpcReference const*)Reference<Map, Npc>::nocheck_prev(); }
};

class MobReference : public Reference<Map, Mob>
{
protected:
	void targetObjectBuildLink() override
	{
		// called from link()
		getTarget()->m_mobRefManager.insertFirst(this);
		getTarget()->m_mobRefManager.incSize();
	}
	void targetObjectDestroyLink() override
	{
		// called from unlink()
		if (isValid()) getTarget()->m_mobRefManager.decSize();
	}
	void sourceObjectDestroyLink() override
	{
		// called from invalidate()
		getTarget()->m_mobRefManager.decSize();
	}
public:
	MobReference() : Reference<Map, Mob>() {}
	~MobReference() { unlink(); }
	MobReference* next() { return (MobReference*)Reference<Map, Mob>::next(); }
	MobReference const* next() const { return (MobReference const*)Reference<Map, Mob>::next(); }
	MobReference* nockeck_prev() { return (MobReference*)Reference<Map, Mob>::nocheck_prev(); }
	MobReference const* nocheck_prev() const { return (MobReference const*)Reference<Map, Mob>::nocheck_prev(); }
};
class WorldObjectReference : public Reference<Map, WorldObject>
{
protected:
	void targetObjectBuildLink() override
	{
		// called from link()
		getTarget()->m_wobjRefManager.insertFirst(this);
		getTarget()->m_wobjRefManager.incSize();
	}
	void targetObjectDestroyLink() override
	{
		// called from unlink()
		if (isValid()) getTarget()->m_wobjRefManager.decSize();
	}
	void sourceObjectDestroyLink() override
	{
		// called from invalidate()
		getTarget()->m_wobjRefManager.decSize();
	}
public:
	WorldObjectReference() : Reference<Map, WorldObject>() {}
	~WorldObjectReference() { unlink(); }
	WorldObjectReference* next() { return (WorldObjectReference*)Reference<Map, WorldObject>::next(); }
	WorldObjectReference const* next() const { return (WorldObjectReference const*)Reference<Map, WorldObject>::next(); }
	WorldObjectReference* nockeck_prev() { return (WorldObjectReference*)Reference<Map, WorldObject>::nocheck_prev(); }
	WorldObjectReference const* nocheck_prev() const { return (WorldObjectReference const*)Reference<Map, WorldObject>::nocheck_prev(); }
};
#endif
