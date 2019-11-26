#include <Game\Object\Object.h>
#include <World.h>
#include <ObjectTable.h>
#include <TableAll.h>
#include <Logger.h>
#include <Packet\Game\PacketGU.h>
#include <assert.h>

//----------------------------------------
//	Constructor
//----------------------------------------
Object::Object()
{
	m_objectType = eOBJTYPE::INVALID_OBJTYPE;
	m_inWorld = false;
	isDead = false;
	isfighting = false;
	isSkillCasting = false;
}
//----------------------------------------
//	Destructor
//----------------------------------------
Object::~Object()
{
	if (IsInWorld())
	{
		sLog.outError("Object::~Object (TypeId: %u) deleted but still in world!!", GetTypeId());
		WPError(false);
	}
}
//----------------------------------------
//	Get if our object is in world
//----------------------------------------
bool& Object::IsInWorld()
{
	return m_inWorld;
}
//----------------------------------------
//	Add our object to world
//----------------------------------------
void Object::AddToWorld()
{
	if (m_inWorld)
		return;

	m_inWorld = true;
}
//----------------------------------------
//	Remove our object from world
//----------------------------------------
void Object::RemoveFromWorld()
{
	m_inWorld = false;
}
//----------------------------------------
//	Get what is ou object type
//----------------------------------------
eOBJTYPE Object::GetTypeId() const
{
	return m_objectType;
}
//----------------------------------------
//	Get our object handle (serialid)
//----------------------------------------
uint32 Object::GetHandle() const
{
	return handle;
}
//----------------------------------------
//	Get our object tblidx
//----------------------------------------
TBLIDX Object::GetTblidx() const
{
	return tblidx;
}
//----------------------------------------
//	Relocate our object at position
//	Pos - Dir
//----------------------------------------
void Object::Relocate(float x, float y, float z, float Ox, float Oy, float Oz)
{
	if (mutexObject.try_lock() == true)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
		m_rotation.x = Ox;
		m_rotation.y = Oy;
		m_rotation.z = Oz;
		mutexObject.unlock();
	}
}
//----------------------------------------
//	Relocate our object at position
//	Pos
//----------------------------------------
void Object::Relocate(float x, float y, float z)
{
	if (mutexObject.try_lock() == true)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
		mutexObject.unlock();
	}
}
//----------------------------------------
//	Relocate our object at direction
//	Dir
//----------------------------------------
void Object::SetOrientation(float x, float y, float z)
{
	if (mutexObject.try_lock() == true)
	{
		m_rotation.x = x;
		m_rotation.y = y;
		m_rotation.z = z;
		mutexObject.unlock();
	}
}
//----------------------------------------
//	Get our object position as vector
//----------------------------------------
sVECTOR3 Object::GetVectorPosition()
{
	return m_position;
}
//----------------------------------------
//	Get our object position
//	Copy position to reference pos
//----------------------------------------
void Object::GetPosition(float &x, float &y, float &z)
{
	x = m_position.x;
	y = m_position.y;
	z = m_position.z;
}
//----------------------------------------
//	Get our object direction
//	Copy direction to reference dir
//----------------------------------------
void Object::GetOriantation(float &x, float &y, float &z)
{
	x = m_rotation.x;
	y = m_rotation.y;
	z = m_rotation.z;
}
//----------------------------------------
//	Get our object direction as vector
//----------------------------------------
sVECTOR3 Object::GetVectorOriantation()
{
	return m_rotation;
}
//----------------------------------------
//	Get if our object is in fight
//----------------------------------------
bool Object::GetIsFighting()
{
	return isfighting;
}
bool Object::GetIsFlying()
{
	return isFlying;
}
//----------------------------------------
//	Get if our object is dead
//----------------------------------------
bool Object::GetIsDead()
{
	return isDead;
}
//----------------------------------------
//	Set our new object death state
//	is dead or not
//----------------------------------------
void Object::SetIsDead(bool val)
{
	isDead = val;
}
//----------------------------------------
//	Set our new object fight state
//	is in fight or not
//----------------------------------------
void Object::SetIsFighting(bool val)
{
	isfighting = val;
}
void Object::SetFlying(bool val)
{
	isFlying = val;
}
//----------------------------------------
//	Get if our object is casting a skill (undetermined use for now)
//----------------------------------------
bool Object::GetIsSkillCasting()
{
	return isSkillCasting;
}
//----------------------------------------
//	Set our new object casting state
//	is casting or not
//----------------------------------------
void Object::SetIsSkillCasting(bool val)
{
	isSkillCasting = val;
}
//----------------------------------------
//		GETTER
//----------------------------------------
WORLDID Object::GetWorldID()
{
	return WorldId;
}
TBLIDX Object::GetWorldTableID()
{
	return WorldTableID;
}
Map* Object::GetMap()
{
	return m_currMap;
}
//------------------------------------------
//		SETTER
//------------------------------------------
void Object::SetState(eCHARSTATE _state)
{
	GetState()->sCharStateBase.byStateID = _state;

	GetState()->sCharStateBase.vCurLoc = GetVectorPosition();
	GetState()->sCharStateBase.vCurDir = GetVectorOriantation();

	GetState()->sCharStateBase.isFighting = GetIsFighting();
	GetState()->sCharStateBase.isFlying = GetIsFlying();
	GetState()->sCharStateBase.dwConditionFlag = 0;
	GetState()->sCharStateBase.dwStateTime = 0;
	UpdateState(_state);
}
//----------------------------------------
//	Tell everyone the character state changed
//----------------------------------------
void Object::UpdateState(eCHARSTATE _state)
{

}
//--------------------------------------------------------------------------------------------

WorldObject::WorldObject() : Object()
{
	m_objectType = eOBJTYPE::OBJTYPE_TOBJECT;
	isUsable = true;
}
WorldObject::~WorldObject()
{

}
bool		WorldObject::Create(sOBJECT_TBLDAT& objRef)
{
	Relocate(objRef.vLoc.x, objRef.vLoc.y, objRef.vLoc.z, objRef.vDir.x, objRef.vDir.y, objRef.vDir.z);
	sequence = objRef.dwSequence;
	handle = sequence + 100000;
	tblidx = objRef.tblidx;
	objRef.abyState;
	objRef.achClickSound;
	objRef.byBoundaryDistance;
	objRef.byDefMainState;
	objRef.byDefSubState;
	objRef.byStateType;
	objRef.contentsTblidx;

	objRef.fRadius;
	objRef.maxQuestId;
	objRef.minQuestId;
	objRef.objectDirectionIndex;
	objRef.szModelName;
	objRef.tblidx;
	objRef.vMax;
	objRef.vMin;
	objRef.wFunction;
	return true;
}
void		WorldObject::Update(uint32 update_diff, uint32 time)
{

}
//----------------------------------------
//	GETTER
//----------------------------------------
bool		WorldObject::GetIsUsable()
{
	return isUsable;
}
DWORD		WorldObject::GetSequence()
{
	return sequence;
}
WorldObjectReference& WorldObject::GetMapRef()
{
	return m_wObjRef;
}