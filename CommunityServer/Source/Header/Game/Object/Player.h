#ifndef __PLAYER_H
#define __PLAYER_H

#pragma once

#include <Game\Object\Manager\Fight.h>
#include <NtlCharacter.h>
#include "Manager\Skills.h"
#include "Manager\Attributes.h"
#include "Manager\Inventory.h"
#include "Manager\Guild.h"
#include <CommunitySession.h>
#include <Packet.h>
#include <Packet\Community\PacketTU.h>
#include <Packet\Community\PacketUT.h>

class CommunitySession;
class Map;

class Player : public Object
{
	friend class CommunitySession;
public:
	explicit Player(CommunitySession* session);
	~Player();


	////FriendLists/////

	typedef std::unordered_map<CHARACTERID, HOBJECT> Friendlist;
	Friendlist friendlist;

	bool			LoadFriendList(CHARACTERID ID, Friendlist &friendlist);

	//////////////////////

	bool                isFlying = false;
	void				CleanupsBeforeDelete();
	void				AddToWorld() override;
	void				RemoveFromWorld() override;
	bool				Create(CHARACTERID id);
	void				Update(uint32 update_diff, uint32 time) override;
	//	------------------------------------------------------------------------
	// LOGIC
	//	------------------------------------------------------------------------
	void				CalculeLowLife();
	void				CalculePosition(uint32 _update_diff);
	void				LevelUp();
	//Comands
	void				LevelUpByComand(int Level);
	void				SetSpeed(int sppeed);
	void				ConvertClass(int Class);
	void				ConvertAdult(int Adult);
	void				SendUpdateSize(int Size);


	void                SetFlying(bool isFlying);
	void				SavePlayer();
	void				CalculeRpBall();

//	void				RewardExpFromMob(MonsterData& data);
	void				RewardDropFromMob(MonsterData& data);

	void				UpdateZennyAmount(DWORD amount, eZENNY_CHANGE_TYPE zennyType);
	void				UpdateModusaAmount(DWORD amount);

	HOBJECT             GetGSHandle();
	//	------------------------------------------------------------------------
	// GETTER
	//	------------------------------------------------------------------------
	CommunitySession*	GetSession() const;
	MapReference&		GetMapRef();
	CHARACTERID			GetCharacterID();
	sPC_PROFILE			*GetPcProfile();
	sITEM_BRIEF			*GetCharEquippedItems();
	std::string			GetGuildName();
	eCHARSTATE			GetCharEState();
	BYTE				GetMoveDirection();
	std::string			GetName();
	HOBJECT				GetTarget() const ;
	PORTALID			GetPortalIdFromList(HOBJECT handle);
	ePC_CLASS			GetMyClass() const;
	AttributesManager	*GetAttributesManager();
	InventoryManager	*GetInventoryManager();
	sVECTOR3			GetMoveDestinationVector();
	bool				GetIsEmergency();
	bool                GetFlying();
	virtual DWORD		GetPowerLevel() override;
	//	------------------------------------------------------------------------
	// SETTER
	//	------------------------------------------------------------------------
	void				SetGuildName(std::string GuildName);
	void				SetMoveDestinationLocation(sVECTOR3 pos);
	void				SetSession(CommunitySession* s);
	void				SetIsFighting(bool val);
	void				SetMoveDirection(BYTE _moveDir);
	void				SetName(char* name);
	void				SetWorldID(WORLDID id);
	void				SetWorldTableID(TBLIDX id);
	void				SetMap(Map* m);
	void				ResetMap();
	void				SetTarget(HOBJECT hSerial);
	void				SetMyClass(ePC_CLASS _class);
//	virtual void		UpdateState(eCHARSTATE _state) override;
	//	------------------------------------------------------------------------
	// PACKET
	//	------------------------------------------------------------------------
	bool				LoadFromDB(CHARACTERID id);
	void				BuildPacketForSpawn(SpawnPlayer& PC);
	
	void				BuildPacketForNewPlayer(Player& plr);
	void				SendPacket(char*, size_t size);
	//	------------------------------------------------------------------------
	// LIST
	//	------------------------------------------------------------------------
	void				FillList(Object& obj);
	void				RemoveFromList(Object& obj);
	void				SendToPlayerList(char* data, size_t size);
	bool				isInList(uint32 id);
	Object				*GetFromList(uint32 id);


	void				AddDropToList(DroppedObject& drop, HOBJECT dropHandle);
	void				RemoveDropFromList(HOBJECT handle);
	void				UpdateDropListTimer();
	DroppedObject		*GetPickupData(HOBJECT handle);

	void				ClearListAndReference();

private:
	//	------------------------------------------------------------------------
	// SERVER
	//	------------------------------------------------------------------------

	std::mutex			mutexPlayer;
	std::mutex			mutexDropList;

	std::map<uint32, Object*> objList;
	std::map<uint32, DroppedObject*>	DropList;
	CommunitySession*		m_session;
	MapReference		m_mapRef;
	//	------------------------------------------------------------------------
	// CHARACTER
	//	------------------------------------------------------------------------
	AttributesManager	characterManager;
	CHARACTERID			charid;
	ACCOUNTID			accID;
	std::string			m_name;
	sVECTOR3			m_position_tmp;
	sVECTOR3			m_rotation_tmp;
	sVECTOR3			m_destination_pos;
	BYTE				moveDirection;
	HOBJECT				cur_target;
	Object*				cur_obj_tagert;
	bool				isLowLifeSend;
	ePC_CLASS			myClass;
	bool				isMovingToCharServer;
	//	------------------------------------------------------------------------
	// ITEM
	//	------------------------------------------------------------------------
	InventoryManager	inventoryManager;
	//	------------------------------------------------------------------------
	// GUILD //
	std::string			GuildName;
	// SKILLS
	//	------------------------------------------------------------------------
	FightManager		fightManager;
	SkillsManager		skillManager;
	BYTE				attackCount;
	//	------------------------------------------------------------------------
	// TIMER
	//	------------------------------------------------------------------------
	time_t				rpBallTimer;

	virtual void		TakeDamage(uint32 amount) override;

};

#endif