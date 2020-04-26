//***********************************************************************************
//
//	File		:	NtlObject.h
//
//	Begin		:	2006-04-07
//
//	Copyright	:	ⓒ NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	
//
//***********************************************************************************

#pragma once

#include "NtlCharacter.h"
#include "NtlQuest.h"
#include <stdint.h>


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
enum eOBJTYPE
{
	OBJTYPE_PC, // PC
	OBJTYPE_NPC, // NPC
	OBJTYPE_MOB, // MOB
	OBJTYPE_SUMMON_PET, // ½ºÅ³·Î ¼ÒÈ¯µÈ pet
	OBJTYPE_ITEM_PET, // ¾ÆÀÌÅÛÀ¸·Î ¼ÒÈ¯µÈ pet
	OBJTYPE_DROPMONEY, // ¶¥¿¡ ¶³¾îÁø µ·
	OBJTYPE_DROPITEM, // ¶¥¿¡ ¶³¾îÁø ¾ÆÀÌÅÛ
	OBJTYPE_TOBJECT, // Æ®¸®°Å ¿ÀºêÁ§Æ®
	OBJTYPE_DYNAMIC,	// µ¿Àû »ý¼º ¿ÀºêÁ§Æ®
	OBJTYPE_ITEM,	// ITEM TYPEÀº ÇÊµå¿¡ »ý¼ºµÇÁö ¾Ê´Â´Ù. ( Ä³¸¯ÅÍ¸¸ °¡Áö°í ÀÖ´Ù )

	MAX_OBJTYPE,
	MAX_SPAWNOBJTYPE = OBJTYPE_DYNAMIC,	// ÇÊµå¿¡ »ý¼ºµÇ´Â ¿ÀºêÁ§Æ® Å¸ÀÔÀÇ MAX
	INVALID_OBJTYPE = 0xFF,

	OBJTYPE_FIRST = OBJTYPE_PC,
	OBJTYPE_LAST = MAX_OBJTYPE - 1,
};


// Object¸¦ »ý¼ºÇÑ source
enum eDBO_OBJECT_SOURCE
{
	DBO_OBJECT_SOURCE_SKILL = 0,		// ½ºÅ³¿¡ ÀÇÇØ »ý±ä object
	DBO_OBJECT_SOURCE_ITEM,				// ¾ÆÀÌÅÛ¿¡ ÀÇÇØ »ý±ä object
	DBO_OBJECT_SOURCE_PLAYER,
	DBO_OBJECT_SOURCE_UNKNOWN = 0xFF,

	DBO_OBJECT_SOURCE_FIRST = DBO_OBJECT_SOURCE_SKILL,
	DBO_OBJECT_SOURCE_LAST = DBO_OBJECT_SOURCE_PLAYER
};


// Trigger objectÀÇ ±â´É
enum eDBO_TRIGGER_OBJECT_FUNC
{
	eDBO_TRIGGER_OBJECT_FUNC_SELECTION = 0x1,
	eDBO_TRIGGER_OBJECT_FUNC_PORTAL = 0x2,
	eDBO_TRIGGER_OBJECT_FUNC_BIND = 0x4,
	eDBO_TRIGGER_OBJECT_FUNC_SCOUTER = 0x8,
	eDBO_TRIGGER_OBJECT_FUNC_RANK_BATTLE = 0x10,
	eDBO_TRIGGER_OBJECT_FUNC_NORMAL_DRAGONBALL = 0x20,
	eDBO_TRIGGER_OBJECT_FUNC_RAID_DRAGONBALL = 0x40,
	eDBO_TRIGGER_OBJECT_FUNC_MAIL_BOX = 0x80,
	eDBO_TRIGGER_OBJECT_FUNC_TIME_MACHINE = 0x100,
	eDBO_TRIGGER_OBJECT_FUNC_NAMEKAN_SIGN = 0x200,
	eDBO_TRIGGER_OBJECT_FUNC_PARTY_INSTANCE_DUNGEON = 0x400,
	eDBO_TRIGGER_OBJECT_FUNC_TIME_LEAP_QUEST = 0x800,
	eDBO_TRIGGER_OBJECT_FUNC_HOIPOIMIX = 0x1000,
	eDBO_TRIGGER_OBJECT_FUNC_DOJO_WAREHOUSE = 0x2000,
	eDBO_TRIGGER_OBJECT_FUNC_DOJO_SEAL = 0x4000,
};

// Dynamic ObjectÀÇ state
enum eDYNAMIC_OBJECT_STATE
{
	eDYNAMIC_OBJECT_STATE_SPAWN,
	eDYNAMIC_OBJECT_STATE_IDLE,
	eDYNAMIC_OBJECT_STATE_DESPAWN,

	eDYNAMIC_OBJECT_STATE_NUMS,
	eDYNAMIC_OBJECT_STATE_INVALID = 0xFF
};

// Dynamic object function
enum eDYNAMIC_OBJECT_FUNCTION
{
	eDYNAMIC_OBJECT_FUNCTION_HOIPOIMIX = 0x1,

	eDYNAMIC_OBJECT_FUNCTION_NUMS,
	eDYNAMIC_OBJECT_FUNCTION_INVALID = 0xFF
};

// Dynamic ObjectÀÇ ±â´É
enum eDBO_DYNAMIC_OBJECT_TYPE
{
	eDBO_DYNAMIC_OBJECT_TYPE_HOIPOI_MIX_MACHINE = 1,		// È£ÀÌÆ÷ÀÌ ¹Í½º ·»Å» ¸Ó½Å
	eDBO_DYNAMIC_OBJECT_TYPE_CAPSULE_HOUSE,						// È£ÀÌÆ÷ÀÌ ¹Í½º Ä³½¬ ¸Ó½Å

	eDBO_DYNAMIC_OBJECT_TYPE_NONE = 0xFF,
};

// Dynamic object substate
enum eDYNAMIC_OBJECT_SUBSTATE
{
	eDYNAMIC_OBJECT_SUBSTATE_ALL_SHOW,
	eDYNAMIC_OBJECT_SUBSTATE_ONLY_SPAWN_AVATAR_SHOW,
	eDYNAMIC_OBJECT_SUBSTATE_ENEMY_HIDE,

	eDYNAMIC_OBJECT_SUBSTATE_NUMS,
	eDYNAMIC_OBJECT_SUBSTATE_INVALID = 0xFF
};

// Dynamic object substate
enum eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE
{
	eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_NORMAL = 1,
	eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_RENTAL,
	eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_NETP,
	eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_CASH,

	eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_NONE = 0xFF,
};


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
const unsigned int MAX_PC = 3000;	// ÀüÃ¼ PC ¼ö

const unsigned int MAX_NPC = 3000;	// ÀüÃ¼ NPC ¼ö

const unsigned int MAX_MOB = 60000;	// ÀüÃ¼ MOB ¼ö

const unsigned int MAX_SUMMON_PET = MAX_PC;	// ÀüÃ¼ Summon Pet ¼ö

const unsigned int MAX_ITEM_PET = MAX_PC;	// ÀüÃ¼ Item Pet ¼ö

const unsigned int MAX_DROP_ITEM = 3000;	// ÀüÃ¼ DROP µÇ´Â ITEM ¼ö

const unsigned int MAX_DROP_MONEY = 3000;	// ÀüÃ¼ DROP µÇ´Â MONEY ¼ö

const unsigned int MAX_PC_HAVE_ITEM = 200;	// PC°¡ °¡Áö´Â ÃÖ´ë ITEM ¼ö

const unsigned int MAX_TRIGGER_OBJECT = 20000; // ÀüÃ¼ Á¤Àû Æ®¸®°Å ¿ÀºêÁ§Æ® ¼ö

const unsigned int MAX_DYNAMIC_OBJECT = MAX_PC; // ÀüÃ¼ µ¿Àû ¿ÀºêÁ§Æ® ¼ö PC ´ç ÇÑ°³¸¸ Çã¿ë

const unsigned int MAX_BOT = MAX_NPC + MAX_MOB + MAX_SUMMON_PET + MAX_ITEM_PET;		// BOT ¼ö ( ¼­¹ö ³»ºÎ Ã³¸®¿ë )

const unsigned int MAX_ITEM = MAX_PC * MAX_PC_HAVE_ITEM;	// ÀüÃ¼ ¾ÆÀÌÅÛ ¼ö

const unsigned int MAX_GAME_OBJECT = MAX_PC + MAX_BOT + MAX_ITEM + MAX_DROP_ITEM + MAX_DROP_MONEY + MAX_TRIGGER_OBJECT + MAX_DYNAMIC_OBJECT; // ÀüÃ¼ ¿ÀºêÁ§Æ® ¼ö

const float		   DBO_MAX_DISTANCE_OF_DYNAMIC_OBJECT = 20.0f;		// DYNAMIC OBJECT ¼³Ä¡ Çã¿ë ÃÖ´ë °Å¸®

const unsigned int DYNAMIC_OBJECT_CHECK_TERM = 1000;	// ´ÙÀÌ³ª¹Í¿ÀºêÁ§Æ®ÀÇ ÁÖÀÎ°ú °Å¸® ÀÌ°Ý Ã¼Å© ÅÒ  seconds

const unsigned int DYNAMIC_OBJECT_DESPAWN_TERM = 1000;

const unsigned int DYNAMIC_OBJECT_SPAWN_TERM = 1000;
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
const char * NtlGetObjectTypeString(eOBJTYPE eObjType);
#pragma pack(1)
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef BYTE DYNAMIC_OBJECT_STATE;

struct sDYNAMIC_OBJECT_BRIEF
{
	BYTE		byObjectType;	// eDBO_DYNAMIC_OBJECT_TYPE
	TBLIDX		idObjectTblidx;	// ÇØ´çÇÏ´Â tblidx(dynamic object°¡ ¾Æ´Ñ hoipoi, capsule houseµîÀÇ tblidx)
	HOBJECT		hOwner;
};


struct sDYNAMIC_OBJECT_STATE
{
	BYTE		byState; // Main State
	sVECTOR3	vCurLoc;
};
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#define NAME_LEN (16)
#define GUILD_LEN (16)
#pragma pack(push, 1)


struct Appear
{
	BYTE			Face;
	BYTE			Hair;
	BYTE			HairColor;
	BYTE			SkinColor;
};
struct MonsterData
{
	TBLIDX			MonsterID;
	BYTE			StateID;
	DWORD			ConditionFlag;

	bool			ShowName;
	bool			SpawnAnimation;
	BYTE			Attack_Animation_Qty;
	BYTE			Attack_Type;
	WORD			Battle_Attribute;
	WORD			Con;
	WORD			Dex;
	WORD			Eng;
	WORD			Foc;
	WORD			Sol;
	WORD			Str;
	BYTE			Grade;
	WORD			HtbBlockRate;
	BYTE			Level;
	WORD			Mob_type;
	BYTE			Property;
	WORD			Scan_range;
	WORD			Sight_range;
	BYTE			Use_skill_basis[MAX_NPC_HAVE_SKILL];

	TBLIDX			Drop_each_id;
	TBLIDX			Drop_quest_id;
	TBLIDX			Drop_type_id;
	TBLIDX			Drop_item_id;

	DWORD			Ai_bit_flag;
	DWORD			AllianceID;
	DWORD			DialogGroup;
	DWORD			Drop_Zenny;
	DWORD			Mob_group;
	float			Attack_range;
	float			Drop_zenny_rate;
	float			Fly_height;
	float			Radius;
	float			Radius_x;
	float			Radius_z;
	float			Run_Speed;
	float			Run_Speed_origin;
	float			Scale;
	float			Walk_Speed;
	float			Walk_Speed_origin;
	TBLIDX			Name;

	DWORD			CurLP;
	WORD			CurEP;
	DWORD			MaxLP;
	WORD			MaxEP;
	WORD			AttackSpeedRate;
	TBLIDX			use_Skill_Tblidx[MAX_NPC_HAVE_SKILL];
	WORD			Aggro_max_count;
	WORD			Attack_cool_time;
	WORD			Attack_rate;
	WORD			Attack_speed_rate;
	WORD			Basic_aggro_point;
	WORD			Basic_physical_Offence;
	WORD			Basic_energy_Offence;
	WORD			Basic_energy_defence;	
	WORD			Basic_physical_defence;
	WORD			Block_rate;
	WORD			Block_Damage_rate;
	WORD			Curse_success_rate;
	WORD			Curse_tolerance_rate;
	WORD			Dodge_rate;
	WORD			Ep_Regeneration;
	WORD			Exp;
	WORD			Lp_Regeneration;
	WORD			Mob_Kind;
	WORD			Sight_angle;
	WORD			TMQ_Point;
	WORD			Use_skill_Lp[MAX_NPC_HAVE_SKILL];
	WORD			Use_skill_time[MAX_NPC_HAVE_SKILL];

	//New
	WORD			physicalCriticalDefenseRate;
	WORD			energyCriticalDefenseRate;

	BYTE			DropEachRateControl;
	BYTE			DropEItemRateControl;
	BYTE			DropLItemRateControl;
	BYTE			DropNItemRateControl;
	BYTE			DropSItemRateControl;
	BYTE			DropTypeRateControl;

	TBLIDX			MonsterSpawnID;
	CNtlVector		Spawn_Loc;
	CNtlVector		Spawn_Dir;
	BYTE			Spawn_Loc_Range;
	BYTE			Spawn_Quantity;
	DWORD			Spawn_Cool_Time;
	BYTE			Spawn_Move_Type;
	BYTE			Wander_Range;
	BYTE			Move_Range;
	BYTE			Move_DelayTime;
	CNtlVector		FollowDistance;
	DWORD			Party_Index;
	bool			Party_Leader;
	SPAWNGROUPID	spawnGroupId;

	WORD			MapID;
	DWORD			KilledTime;
	bool			isSpawned;
	bool			initialSpawn;
	bool			isAggro;

	DWORD			DisplayID;
	DWORD			target;
	CNtlVector		curPos;
	BYTE			chainAttackCount;
	BYTE			MaxchainAttackCount;
	DWORD			UniqueID;
	WORD			Job;
	TBLIDX			amerchant_Tblidx[MAX_MERCHANT_TAB_COUNT];
	int				ByDagonBall;
	bool			GotAgro;
};
struct sOBJECT_INFO
{
	sOBJECT_INFO() ;
	BYTE					objType;

	union
	{
		struct // pc
		{
			sPC_BRIEF		pcBrief;
			sCHARSTATE		pcState;
		};
		struct // npc
		{
			sNPC_BRIEF		npcBrief;
			sCHARSTATE		npcState;
		};
		struct // mob
		{
			sMOB_BRIEF		mobBrief;
			sCHARSTATE		mobState;
		};
		struct // summon pet
		{
			sSUMMON_PET_BRIEF		summonPetBrief;
			sCHARSTATE				summonPetState;
		};
		struct // item pet
		{
			sITEM_PET_BRIEF			itemPetBrief;
			sCHARSTATE				itemPetState;
		};
		struct // item
		{
			sITEM_BRIEF		itemBrief;
			sITEM_STATE		itemState;
		};
		struct // money
		{
			sMONEY_BRIEF	moneyBrief;
			sMONEY_STATE	moneyState;
		};
		struct // trigger object
		{
			sTOBJECT_BRIEF	tobjectBrief;
			sTOBJECT_STATE	tobjectState;
		};
		struct // dynamic object
		{
			sDYNAMIC_OBJECT_BRIEF	dynamicObjBrief;
			sDYNAMIC_OBJECT_STATE	dynamicObjState;
		};
	};
};
struct SpawnMOB
{
	WORD				wPacketSize;
	WORD				wOpCode;
	//sBOT_Brief
	DWORD				Handle;
	BYTE				Type;
	TBLIDX				Tblidx;
	DWORD				curLP;
	WORD				curEP;
	DWORD				maxLP;
	WORD				maxEP;
	float				fLastWalkingSpeed;
	float				fLastRunningSpeed;
	float				fLastAirgSpeed;
	float				fLastAirgDashSpeed;
	float				fLastAirgDashAccelSpeed;
	WORD				AttackSpeedRate;
	float				SkillAnnimationSpeedModifier;
	TBLIDX				TBLIDXMovementAcionPattern;
	TBLIDX				Name;
	BYTE				Size;
	//sMOB_BRIEF
	BYTE				Level;
	BYTE				byBallType;
	//sCHARSTATE
	sCHARSTATE			State;
};
struct SpawnNPC
{
	WORD				wPacketSize;
	WORD				wOpCode;

	uint32_t			Handle;
	BYTE				OBJType;
	TBLIDX				Tblidx;
	uint32_t			CurLP;
	WORD				CurEP;
	uint32_t			MaxLP;
	WORD				MaxEP;

	float				fLastWalkingSpeed;
	float				fLastRunningSpeed;
	float				fLastAirSpeed;
	float				fLastAirDashSpeed;
	float				fLastAirDashAccelSpeed;
	WORD				AttackSpeedRate;
	float				SkillAnimationSpeedModifier;
	TBLIDX				TblidxMovementActionPatern;
	TBLIDX				Name;
	BYTE				Size;
	BYTE				Unk;
	sCHARSTATE			State;

};
struct SpawnPlayer
{
	// The handle is the Unique number for reconyze that "thing", it can be, mob, npc, player, zenny, etc.
	WORD			wPacketSize;
	WORD			wOpCode;
	HOBJECT			Handle;
	BYTE			Type; // The type tell to the client, which is it, OBJTYPE.	

	CHARACTERID		charID;
	TBLIDX			Tblidx;
	bool			Adult;
	WCHAR			Name[NAME_LEN + 1];
	WCHAR			GuildName[GUILD_LEN + 1];
	Appear			appear;
	DWORD			maxLP;
	DWORD			curLP;
	WORD			maxEP;
	WORD			curEP;
	DWORD			maxAP;
	DWORD			curAP;
	BYTE			level;
	float			fBaseRunSpeed;
	float			fLastRunSpeed;
	float			fBaseAirSpeed;
	float			fLastAirSpeed;
	float			fBaseAirDashSpeed;
	float			fLastAirDashSpeed;
	float			fBaseAirDash2Speed;
	float			fLastAirDash2Speed;
	sITEM_BRIEF		sItemBrief[EQUIP_SLOT_TYPE_COUNT];
	WORD			wBaseAttackSpeedRate;
	float			fSkillSpeed; // NOT SURE AT ALL
	BYTE			byMarkMain;
	BYTE			byMarkMainColor;
	BYTE			byMarkInLine;
	BYTE			byMarkInColor;
	BYTE			byMarkOutLine;
	BYTE			byMarkOutColor;
	sMARKING		sMarking;//title
	BYTE			WorkshopAligment;
	//sDBO_DOGI_DATA sDogi;
	GUILDID         guildId;
	BYTE			byType;			// µµº¹Á¾·ù
	BYTE		    byGuildColor;	// ±æµåµµº¹»ö»ó
	BYTE			byDojoColor;	// µµÀåµµº¹»ö»ó
	bool			bEmergency;
	BYTE			test[3];
	TBLIDX			mascotID; // This should be UINT32_INVALID or 0xFF.... etc, because if use 1 o 2, the mascot is wrong and client crash. //mascotID is a tblidx for a mascot is why -sangawku
	BYTE			Size; // This should be 10, is the size of the object, if u use more, it wil be more great, like Giant Namek. Like the object grown up. 10 is the default.

	// WORKING ON AREA

	BYTE			bleeding;
	BYTE			poison;
	BYTE			stomachace;
	BYTE			burn;
	BYTE			confuse;

	sCHARSTATE		State;

	// END
};
struct Drop
{
	WORD		wPacketSize;
	WORD		wOpCode;
	HOBJECT		Handle; // The handle is the Unique number for reconyze that "thing", it can be, mob, npc, player, zenny, etc.
	BYTE		Type; // The type tell to the client, which is it, OBJTYPE van be  Money item Character Mob Npc etc.
	TBLIDX		Tblidx; // Table Index of Item locad on Item_Drop_Data
	BYTE		Rank;
	BYTE        Grade; // item effect
	BYTE		BattleAttribute;
	sVECTOR3	Loc; // X Y Z
	bool		NeedToIdentify;
	bool		IsNew;
	DWORD		OwnerHandle;
	DWORD		unknown;
};
struct Dropzenny
{
	WORD		wPacketSize;
	WORD		wOpCode;
	HOBJECT		Handle; // The handle is the Unique number for reconyze that "thing", it can be, mob, npc, player, zenny, etc.
	BYTE		Type; // The type tell to the client, which is it, OBJTYPE van be  Money item Character Mob Npc etc.
	DWORD		dwZenny; // Table Index of Item locad on Item_Drop_Data
	sVECTOR3	Loc; // X Y Z
	sVECTOR3	Dir; // X Y Z
	bool		IsNew;
};
struct DroppedObject
{
	BYTE				objType;
	DWORD				droppedTime;
	HOBJECT				owner;
	union
	{
		struct
		{
			Drop		item;
		};
		struct
		{
			Dropzenny	zenny;
		};
	};
};
struct MascotInfo
{
	DWORD    MascotID;
	DWORD    UNK;
	DWORD	 MascotID1;
	DWORD    CurVp;
	DWORD    MaxVp;
	DWORD    Exp;
	BYTE     Skillcount;
	DWORD    Skill[4];
	WORD     SlotPos;//incress like slot
};
#pragma pack()



