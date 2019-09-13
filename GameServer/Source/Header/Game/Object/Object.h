#ifndef _OBJECT_H
#define _OBJECT_H

#include <Define.h>
#include <NtlVector.h>
#include <Game\Maps\MapReference.h>

enum eOBJTYPE;
struct sOBJECT_TBLDAT;

class Object
{
public:
	virtual				~Object();
	bool&				IsInWorld();
	virtual void		AddToWorld();
	virtual void		RemoveFromWorld();
	virtual void		Update(uint32 /*update_diff*/, uint32 /*time_diff*/) = 0;

	
	virtual void		TakeDamage(uint32 amount) = 0;

	void				GetPosition(float &x, float &y, float &z);
	void				GetOriantation(float &x, float &y, float &z);
	sVECTOR3			GetVectorPosition();
	sVECTOR3			GetVectorOriantation();
	bool				GetIsFighting();
	bool				GetIsFlying();
	bool				GetIsDead();
	bool				GetIsSkillCasting();
	virtual DWORD		GetPowerLevel() = 0;
	WORLDID				GetWorldID();
	TBLIDX				GetWorldTableID();
	Map*				GetMap();
	eOBJTYPE			GetTypeId() const;
	uint32				GetHandle() const;
	sCHARSTATE*			GetState() { return &State; }

	void				Relocate(float x, float y, float z, float Ox, float Oy, float Oz);
	void				Relocate(float x, float y, float z);
	void				SetOrientation(float x, float y, float z);
	void				SetIsDead(bool val);
	void				SetIsFighting(bool val);
	void				SetFlying(bool val);
	void				SetIsSkillCasting(bool val);
	void				SetState(eCHARSTATE _state);
	virtual void		UpdateState(eCHARSTATE _state);
protected:
	Object();
	eOBJTYPE			m_objectType;
	uint32				handle;
	sVECTOR3			m_position;
	sVECTOR3			m_rotation;
	std::mutex			mutexObject;
	bool				isDead;
	bool				isfighting;
	bool				isFlying;
	bool				isSkillCasting;

	Map*				m_currMap;
	WORLDID				WorldId;
	TBLIDX				WorldTableID;

	sCHARSTATE			State;
private:
	bool				m_inWorld;
};

class WorldObject : public Object
{
public:
	explicit			WorldObject();
	~WorldObject();
	bool				Create(sOBJECT_TBLDAT& objRef);
	void				TakeDamage(uint32 amount) {};
	virtual DWORD		GetPowerLevel() { return 0; }

	virtual void		Update(uint32 update_diff, uint32 time) override;
	//----------------------------------------
	//	GETTER
	//----------------------------------------
	DWORD				GetSequence();
	bool				GetIsUsable();
	WorldObjectReference& GetMapRef();
private:
	bool				isUsable;
	DWORD				sequence;
	WorldObjectReference m_wObjRef;
};
#endif