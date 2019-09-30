#ifndef PACKET_GU__H
# define PACKET_GU__H

#pragma once

#include <Define.h>
#include <SharedDef.h>
#include <SharedType.h>
#include <Opcodes.h>
#include <TableAll.h>


#pragma pack(push, 1)
//------------------------------------------------------------------
struct sSERVER_INFO
{
	char		szCharacterServerIP[MAX_LENGTH_OF_IP + 1];
	WORD		wCharacterServerPortForClient;
	DWORD		dwLoad;
};
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PONG)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SESSION_STATE_WRONG)
WORD			wPrevOPCode;	// ÀÌÀü¿¡ º¸³Â´ø ÄÚµå¹øÈ£
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_STATE_WRONG)
WORD			wPrevOPCode; // ÀÌÀü¿¡ º¸³Â´ø ÄÚµå¹øÈ£
HOBJECT			handle; // Ä³¸¯ÅÍ ÇÚµé
BYTE			byStateID; // ÇöÀç Ä³¸¯ÅÍ »óÅÂ
						   //sCHARSTATE		sCharState; // ÇöÀç Ä³¸¯ÅÍ »óÅÂ
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GAME_ENTER_RES)
WORD			wResultCode;
char			achCommunityServerIP[MAX_LENGTH_OF_IP + 1];
WORD			wCommunityServerPort;
DBOTIME			timeDBOEnter;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GAME_LEAVE_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ENTER_WORLD_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ENTER_WORLD_COMPLETE)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES)
WORD			wResultCode;
BYTE			abyAuthKey[MAX_SIZE_AUTH_KEY];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_CHAR_INFO)
HOBJECT			handle;
sPC_PROFILE		sPcProfile;
WORD			wCharStateSize; //-[9/7/2006 zeroera] : ¼³¸í : Å¬¶óÀÌ¾ðÆ®¸¦ À§ÇÑ Ä³¸¯ÅÍ»óÅÂ »çÀÌÁî Á¤º¸ 
sCHARSTATE		sCharState;

END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_ITEM_INFO)
BYTE			byBeginCount;
BYTE			byItemCount;
sITEM_PROFILE	aItemProfile[MAX_COUNT_USER_HAVE_INVEN_ITEM];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_SKILL_INFO)
BYTE			bySkillCount;
sSKILL_INFO		aSkillInfo[MAX_PC_HAVE_SKILL];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_HTB_INFO)
BYTE			byHTBSkillCount; // HTB ½ºÅ³ °³¼ö
sHTB_SKILL_INFO	aHTBSkillnfo[HTB_MAX_PC_HAVE_HTB_SKILL]; // HTB ½ºÅ³ Á¤º¸
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_BUFF_INFO)
BYTE			byBuffCount;
BYTE			byBuffCount2;
sBUFF_INFO		aBuffInfo[MAX_BLESS_BUFF_CHARACTER_HAS + MAX_CURSE_BUFF_CHARACTER_HAS];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_WORLD_INFO)
sVECTOR3		vCurLoc;
sVECTOR3		vCurDir;
sWORLD_INFO		worldInfo;
BYTE			byDojoCount;
sDBO_DOJO_BRIEF sDojoData[DBO_MAX_COUNT_DOJO_IN_WORLD];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_ZONE_INFO)
sWORLD_ZONE_INFO		zoneInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_QUEST_COMPLETE_INFO)
sQUEST_COMPLETE_INFO	completeInfo; // 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_QUEST_PROGRESS_INFO)
BYTE					byProgressCount; // ÇöÀç ÁøÇàÇÏ°í ÀÖ´Â Äù½ºÆ® °³¼ö
sQUEST_PROGRESS_INFO	progressInfo[20]; // ÁøÇà Äù½ºÆ® µ¥ÀÌÅ¸
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_QUEST_INVENTORY_INFO)
BYTE					byItemCount;
sQUEST_INVENTORY_INFO	aInventoryInfo[1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_INFO_END)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_ATTRIBUTE_UPDATE)
HOBJECT			hHandle;
BYTE			byAttributeTotalCount;
BYTE			abyFlexibleField[((UCHAR_MAX - 1) / 8 + 1) + sizeof(sAVATAR_ATTRIBUTE)];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_OBJECT_CREATE)
HOBJECT			handle;
sOBJECT_INFO	sObjectInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_OBJECT_DESTROY)
HOBJECT			handle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_MOVE)
HOBJECT				handle;
dVECTOR3			pos_move;
wVECTOR3			dir_move;
BYTE				move_type;
DWORD				move_flag;
//uint8_t			relleno[61];
END_PROTOCOL()
//-----------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_AIR_MOVE_SYNC)
//- yoshiki : Do we use dwTimeStamp or not?
HOBJECT				handle;
dVECTOR3			pos_move;
wVECTOR3			dir_move;
BYTE				byMoveDirection;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_DEST_MOVE)
HOBJECT         handle;
dVECTOR3		vCurLoc;
BYTE            byMoveFlag;
bool            bHaveSecondDestLoc;
dVECTOR3	    vSecondDestLoc;
BYTE			unknown;
BYTE            byDestLocCount;
dVECTOR3		avDestLoc[DBO_MAX_NEXT_DEST_LOC_COUNT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_CHANGE_HEADING)
HOBJECT			handle;
wVECTOR3		dir_move;
dVECTOR3		pos_move;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_CHANGE_JUMP_DIRECTION)
HOBJECT			handle;
DWORD			dwTimeStamp;
sVECTOR3		vJumpDir;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_CHANGE_DIRECTION_ON_FLOATING)
HOBJECT				hSubject;
DWORD				dwTimeStamp;
sVECTOR3			vCurDir;
BYTE				byMoveDirection;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_FOLLOW_MOVE)
HOBJECT			handle;
DWORD			dwTimeStamp;
HOBJECT			hTarget;
float			fDistance;
BYTE			byMovementReason;
BYTE			byMoveFlag;		// ¶Ù±â È¤Àº °È±â(ENtlMovementFlag ÂüÁ¶)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_JUMP)
HOBJECT				handle;
wVECTOR3            vDir;
wVECTOR3            jumpDir;
BYTE				unknown; // Not sure yet
dVECTOR3			vPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_JUMP_END)
HOBJECT			handle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_FIGHTMODE)
HOBJECT			handle;
bool			bFightMode; // ÀüÅõ ÀÚ¼¼ On/Off
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_BLOCK_MODE_COOL_TIME_NFY)
DWORD			dwCoolTimeRemaining;		// in Millisecs.
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_FAINT)
HOBJECT			handle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_KNOCKDOWN)
HOBJECT			handle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_SLIDING)
HOBJECT			handle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_CAMPING)
HOBJECT			handle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_CONVERT_CLASS)
HOBJECT			hTarget;
BYTE			byClass;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_DIALOG)
HOBJECT				hSubject;				// ´ëÈ­ ÇÏ´Â Ä³¸¯ÅÍ ÇÚµé
BYTE				byDialogType;			// ´ëÈ­ Á¾·ù ( eCHAR_DIALOG_TYPE )
TBLIDX				textTblidx;				// ´ëÈ­ ³»¿ë Å×ÀÌºí ¹øÈ£ ( INVALID °¡ ¾Æ´Ï¸é ÇØ´ç ÅØ½ºÆ®¸¦ Ã£¾Æ Ãâ·ÂÇÏ°í, INVALID¸é ¾Æ·¡ÀÇ ÅØ½ºÆ®¸¦ Ãâ·ÂÇØ ÁÙ °Í)
bool				bIsRefSpeechTable;		// speech table( NPCSpeechTable À» ÂüÁ¶ÇÏ´Â°¡? )
WORD				wTextLen;				// ´ëÈ­³»¿ëÀÇ ±æÀÌ
WCHAR				awchText[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1]; // ´ëÈ­³»¿ë
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_DIRECT_PLAY)
HOBJECT				hSubject;				// ¿¬Ãâ Ä³¸¯ÅÍ ÇÚµé
BYTE				byPlayMode;				// ¿¬Ãâ ¸ðµå
TBLIDX				directTblidx;			// ¿¬Ãâ ¹øÈ£
bool				bSynchronize;			// ¼­¹ö Å¬¶óÀÌ¾ðÆ® µ¿±âÈ­
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_DIRECT_PLAY_END)

END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_AWAY_RES)
bool	bIsAway;		// AwayOn 1: Awayoff: 0
WORD 	wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_MAIL_INFO)
BYTE	byMailCount;		// ÇöÀç ÀüÃ¼¸ÞÀÏ Ä«¿îÆ® 
BYTE	byManagerCount;		// ÀÐÁö ¾ÊÀº ¸Å´ÏÁ® ¸ÞÀÏ Ä«¿îÆ®
BYTE	byNormalCount;		// ÀÐÁö ¾ÊÀº ³ë¸Ö ¸ÞÀÏ Ä«¿îÆ®
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_KEY_INFO)
BYTE			byCount;
sSHORTCUT_DATA  asData[SHORTCUT_MAX_COUNT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_RANKBATTLE_SCORE)
sRANKBATTLE_SCORE_INFO	sScoreInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_KEY_UPDATE_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_ACTION_ATTACK)
HOBJECT			hSubject; // ¾×¼Ç ÁÖÃ¼ Ä³¸¯ÅÍ ÇÚµé
HOBJECT			hTarget; // ¾×¼Ç Å¸°Ù Ä³¸¯ÅÍ ÇÚµé
DWORD			dwLpEpEventId;
BYTE			bChainAttack : 1; // Ã¼ÀÎ¾îÅÃ¿©ºÎ
BYTE			byAttackResult : 7; // ¾×¼Ç °á°ú ( eBATTLE_ATTACK_RESULT )
DWORD			wAttackResultValue; // ¾×¼ÇÀÇ °á°ú °ª ( µ¥¹ÌÁö )
BYTE			byAttackSequence; // ¾îÅÃ ½ÃÄö½º ¹øÈ£ (Ã¼ÀÎ¾îÅÃ)
DWORD			fReflectedDamage; // Å¸°ÙÀ¸·ÎºÎÅÍ ¹Ý»çµÇ¾î ÀÔÀº ÇÇÇØ
BYTE			byBlockedAction;		// eDBO_GUARD_TYPE
sVECTOR3		vShift; // ¾îÅÃÀ¸·Î ÀÎÇÑ ÀÌµ¿ º¤ÅÍ
bool			bRecoveredLP;
DWORD			wRecoveredLpValue;
bool			bRecoveredEP;
DWORD			wRecoveredEpValue;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_IS_BATTLECOMBATING)
bool		fight;
BYTE		a;
BYTE		b;
BYTE		c;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_ACTION_SKILL)
HOBJECT				handle;
WORD				wResultCode;
DWORD				dwLpEpEventId;
TBLIDX				skillId;
BYTE				byRpBonusType;		// eDBO_RP_BONUS_TYPE
HOBJECT				hAppointedTarget;
bool				bIsSkillHarmful;
BYTE				bySkillResultCount;
sSKILL_RESULT		aSkillResult[32];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_ACTION_ITEM)
HOBJECT				handle;
WORD				wResultCode;
DWORD				dwLpEpEventId;
TBLIDX				itemTblidx;
BYTE				bySkillResultCount;
sSKILL_RESULT		aSkillResult[MAX_NUMBER_OF_SKILL_TARGET];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_REVIVAL_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_TELEPORT_RES)
WORD			wResultCode;
dVECTOR3		vNewLoc;
wVECTOR3		vNewDir;
DWORD			unk;
bool			bIsToMoveAnotherServer;
BYTE			unk1;
// Data in 'sWorldInfo' will not be sent if the character moves within the current world.
sWORLD_INFO		sWorldInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_BIND_RES)
WORD			wResultCode;
BYTE			byBindType;		// eDBO_BIND_TYPE
WORLDID			bindWorldId;
TBLIDX			bindObjectTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_SERVER_CHANGE_RES)
WORD					wResultCode;
char					achAuthKey[MAX_SIZE_AUTH_KEY];
sSERVER_INFO			serverInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_CHANNEL_CHANGE_RES)
WORD					wResultCode;
char					achAuthKey[MAX_SIZE_AUTH_KEY];
sSERVER_INFO			serverInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_EXIT_RES)
WORD					wResultCode;
char					achAuthKey[MAX_SIZE_AUTH_KEY];
BYTE					byServerInfoCount;
sSERVER_INFO			aServerInfo[DBO_MAX_CHARACTER_SERVER_COUNT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_SKILL_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GAME_EXIT_RES)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GAME_KICK_NFY)
WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_EFFECT_AFFECTED)
HOBJECT			handle;
HOBJECT			hCaster;
TBLIDX			effectTblidx;
BYTE            bysource;
DWORD			SyestemEffectCode;
WORD			ResultCode;
float			ActualArgument[2];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_CASTING_CANCELED_NFY)
HOBJECT			handle;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_CASTING_DELAYED_NFY)
HOBJECT			handle;
WORD			wResultCode;
DWORD			dwCastingTime;
DWORD			dwCastingTimeRemaining;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_AFFECTING_CANCELED_NFY)
HOBJECT			hSubject;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_TARGET_LIST_REQ)
BYTE			byAvatarType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_LEARN_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_LEARNED_NFY)
TBLIDX			skillId;
BYTE			bySlot;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_UPGRADE_RES)
WORD			wResultCode;
TBLIDX			skillId;
BYTE			bySlot;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_RP_BONUS_SETTING_RES)
WORD			wResultCode;
TBLIDX			skillId;
BYTE			bySlotIndex;
BYTE			byRpBonusType;		// eDBO_RP_BONUS_TYPE
bool			bIsRpBonusAuto;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_NOTIFY_EXP)
BYTE			bySlotIndex;
WORD			wSkillExp;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_AFTEREFFECT_REMAINING_TIME_NFY)
DWORD			dwTimeRemaining;		// in Millisecs.
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_COOL_TIME_STARTED_NFY)
HOBJECT			hSubject;
TBLIDX			skillTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUFF_REGISTERED)
HOBJECT			hHandle;
BYTE			Slot;
TBLIDX			tblidx;
BYTE			bySourceType;// set 0
DWORD			dwInitialDuration;//dwInitialDuration and dwTimeRemaining
DWORD			dwTimeRemaining;
bool			isactive;
sBuffType		BuffType;
bool            NeedDisplayMensage;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUFF_DROPPED)
HOBJECT			hHandle;
WORD			bySourceType;		// eDBO_OBJECT_SOURCE
//BYTE            unk;
TBLIDX			tblidx;
BYTE            unk1;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUFF_REFRESH_ALL)
HOBJECT			hHandle;
BYTE			byCount;
sBUFF_INFO		aBuffInfo[DBO_MAX_BUFF_CHARACTER_HAS];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUFF_DROP_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HTB_START_RES)
WORD			wResultCode;
BYTE			bySkillSlot;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HTB_LEARN_RES)
WORD			wResultCode;
TBLIDX			skillId;
BYTE			bySkillSlot;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HTB_FORWARD_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HTB_RP_BALL_USE_RES)
WORD			wResultCode;
BYTE			byRpBallCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HTB_RP_BALL_USED_NFY)
HOBJECT			hSubject;
BYTE			byRpBallCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HTB_RP_BALL_RESULT_DECIDED_NFY)
HOBJECT			hAttacker;
HOBJECT			hWinner;
bool			bHasSubjectRpBallUsed;
bool			bHasTargetRpBallUsed;
BYTE			bySubjectRpBallUsed;
BYTE			byTargetRpBallUsed;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_CREATE)
HOBJECT			handle;
sITEM_DATA      sItemData;
bool			bIsNew;		// Effect Ãß°¡ 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_UPDATE)
HOBJECT			handle;
sITEM_DATA      sItemData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_MOVE_RES)
WORD			wResultCode;
HOBJECT			hSrcItem;
HOBJECT			hDestItem;
BYTE			bySrcPlace;
BYTE			bySrcPos;
BYTE			byDestPlace;
BYTE			byDestPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_MOVE_STACK_RES)
WORD			wResultCode;
HOBJECT			hSrcItem;
HOBJECT			hDestItem;
BYTE			bySrcPlace;
BYTE			bySrcPos;
BYTE			byDestPlace;
BYTE			byDestPos;
BYTE			byStackCount1;//°á°úÀûÀ¸·Î ³õ¿©Áú°ª SOURCE
BYTE			byStackCount2;//°á°úÀûÀ¸·Î ³õ¿©Áú°ª DESTINATION
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_DELETE)
HOBJECT			hSrcItem;
BYTE			bySrcPlace;
BYTE			bySrcPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_DELETE_RES)
WORD			wResultCode;
BYTE			byPlace;
BYTE			byPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_EQUIP_REPAIR_RES)
HOBJECT			handle;			// hNpchandle
WORD			wResultCode;
DWORD			dwSpendedZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_REPAIR_RES)
HOBJECT				hNpchandle;
WORD				wResultCode;
HOBJECT				hItem;
DWORD				dwSpendedZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_USE_RES)
WORD			wResultCode;
TBLIDX			tblidxItem;
BYTE			byPlace;
BYTE			byPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_CASTING_CANCELED)
HOBJECT			handle;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_CASTING_DELAYED_NFY)
HOBJECT			handle;
WORD			wResultCode;
DWORD			dwCastingTime;
DWORD			dwCastingTimeRemaining;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_DUR_DOWN)
BYTE			byDur[MAX_EQUIP_ITEM_SLOT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_DUR_UPDATE)
HOBJECT			hItemHandle;
BYTE			byDur;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_STACK_UPDATE)
HOBJECT			hItemHandle;
BYTE			byStack;
bool			bIsNew;		// Effect Ãß°¡ 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_UPGRADE_RES)
WORD			wResultCode;
BYTE			byStack;			// ½ºÅæ »ç¿ëÈÄ ½ºÅÃ°¹¼ö					-> º¯°æµÉ ½ºÅÃ
BYTE			byGrade;			// º¯°æµÉ ±×·¹ÀÌµå						-> º¯°æµÉ ±×·¹ÀÌµå
BYTE			byItemPlace;		// ¾÷±×·¹ÀÌµå ÇÒ ¾ÆÀÌÅÛÀÇ ÄÁÅ×ÀÌ³Ê À§Ä¡
BYTE			byItemPos;			// ¾÷±×·¹ÀÌµå ÇÒ ¾ÆÀÌÅÛÀÇ À§Ä¡
BYTE			byStonPlace;		// È£ÀÌÆ÷ÀÌ½ºÅæ ÄÁÅ×ÀÌ³Ê À§Ä¡
BYTE			byStonPos;			// È£ÀÌÆ÷ÀÌ½ºÅæ À§Ä¡
BYTE			byBattleAttribute;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_IDENTIFY_RES)
HOBJECT			hItemHandle;
WORD			wResultCode;
sITEM_DATA      sItemData;			// ¼º°ø½Ã¿¡¸¸ ¼¼ÆÃ
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_PICK_RES)
WORD			wResultCode;
TBLIDX			itemTblidx;
bool			bByPartyHunting;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ZENNY_PICK_RES)
WORD			wResultCode;
bool			bSharedInParty;
DWORD			dwZenny;
DWORD			dwAcquisitionZenny;
DWORD			dwBonusZenny;
// 'dwOriginalZenny' MUST NOT be referred if 'bSharedInParty' is false.
// bSharedInParty°¡ falseÀÌ¸é dwOriginalZenny°ªÀº ÂüÁ¶ÇØ¼­´Â ¾È µÈ´Ù.
// by YOSHIKI(2007-10-02)
DWORD			dwOriginalZenny; //Drop ZennyÀÌ´Ù.
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_STATE)
HOBJECT			handle;
sCHARSTATE		sCharState;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_ASPECT_STATE)
HOBJECT			handle;
sASPECTSTATE	aspectState;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_CONDITION)
HOBJECT			handle;
DWORD			dwConditionFlag;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_EXP)
HOBJECT			handle;
DWORD			dwCurExp;
DWORD			dwIncreasedExp;
DWORD			dwAcquisitionExp;
DWORD			dwBonusExp;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_LEVEL)
HOBJECT			handle;
BYTE			byPrevLevel;
BYTE			byCurLevel;
DWORD			dwMaxExpInThisLevel;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_SPEED)
HOBJECT			handle;
float			fLastWalkingSpeed;
float			fLastRunningSpeed;
float			fLastFlySpeed;
float			fLastFlyBoostSpeed;
float			fLastFlySpeed2;
float			fLastFlyBoostSpeed2;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_ATTACK_SPEEDRATE)
HOBJECT			handle;
WORD			wAttackSpeedRate;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_ITEM_EQUIP)
HOBJECT			handle;
BYTE			byPos;
sITEM_BRIEF		sItemBrief;		// ÀåÂø ÇØÁ¦ µÇ¾úÀ» °æ¿ì INVALID VALUE°¡ µé¾î ¿Â´Ù.
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_ITEM_DELETED)
HOBJECT			handle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_LP)
HOBJECT			handle;
DWORD			dwLpEpEventId;
DWORD			wCurLP;
DWORD			wMaxLP;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_EP)
HOBJECT			handle;
DWORD			dwLpEpEventId;
WORD			wCurEP;
WORD			wMaxEP;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_RP)
HOBJECT			handle;
WORD			wCurRP;
WORD			wMaxRP;
bool			bHitDelay;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_LP_EP)
HOBJECT			handle;
DWORD			dwLpEpEventId;
DWORD			wCurLP;
DWORD			wMaxLP;
WORD			wCurEP;
WORD			wMaxEP;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_ZENNY)
HOBJECT			handle;
DWORD			dwZenny;
bool			bIsNew;		// Effect Ãß°¡
BYTE			byChangeType; // eZENNY_CHANGE_TYPE - NtlCharacter.h
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_MUDOSA_POINT)
DWORD			dwMudosaPoint;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SYSTEM_DISPLAY_TEXT)
WCHAR			awGMChar[MAX_SIZE_CHAR_NAME_UNICODE + 1];
BYTE			byDisplayType;				// eSERVER_TEXT_TYPE
WORD			wMessageLengthInUnicode;
WCHAR			awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1]; // ³»¿ë
END_PROTOCOL()
BEGIN_PROTOCOL(GU_SYSTEM_DISPLAY_SCRIPT_TEXT)

END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SYSTEM_DISPLAY_RESULTCODE)
BYTE			byDisplayType;				// eSERVER_TEXT_TYPE
WORD			wResultCode;				// Ãâ·ÂÇÒ ResultCode
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_START_RES)
HOBJECT			handle;
BYTE			byType; //	0: ±âº»  1:ÇÑÁ¤¼ö·® ÆÇ¸Å ÀÌº¥Æ® NPC 
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_BUY_RES)
HOBJECT			handle;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_SELL_RES)
HOBJECT			handle;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_END_RES)
WORD			wResultCode;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_ITEM_EXCHANGE_RES)
HOBJECT			handle;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CREATE_RES)
WORD			wResultCode;
WCHAR			wszPartyName[MAX_SIZE_PARTY_NAME_IN_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_DISBAND_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_DISBANDED_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVITE_RES)
WORD			wResultCode;
WCHAR			wszTargetName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
DWORD           PartyID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVITE_NFY)
WCHAR				wszInvitorPcName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_RESPONSE_INVITATION_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_JOINED_NFY)
sPARTY_MEMBER_INFO		memberInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INFO)
WCHAR		awchPartyName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
DWORD		PartyID;//??? not Sure
HOBJECT		hLeader;
BYTE		byItemLootingMethod;
BYTE		byZennyLootingMethod;
DWORD		registeredCharmTblidx[2];
DWORD		adwRemainingTime[2];
sSHARETARGET_INFO		sharetargetInfo[MAX_SHARETARGET_COUNT];
BYTE		eDiff[4];
BYTE		unk;
BYTE		byMemberInfoCount;
sPARTY_MEMBER_INFO		memberInfo[MAX_MEMBER_IN_PARTY - 1];
END_PROTOCOL()
//------------------------------------------------------------------
/*BEGIN_PROTOCOL(GU_PARTY_INVENTORY_INFO)
BYTE								bySlotInfoCount;
sDBO_PARTY_INVENTORY_SLOT_INFO		inventorySlotInfo[PARTY_INVENTORY_SLOT_COUNT];
END_PROTOCOL()*/
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_OPENED_CHARM_INVENTORY_INFO)
BYTE							byCharmInventoryIndex;
sDBO_PARTY_VICTIM_ITEM_INFO		victimItemInfo;
DWORD							dwTotalVictimZenny;
BYTE							byVictimInfoCount;
sDBO_VICTIM_INFO				aVictimInfo[MAX_MEMBER_IN_PARTY - 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVITATION_DECLINED_NFY)
WCHAR			wszPlayerName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVITATION_EXPIRED_NFY)
WCHAR			wszPlayerName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_LEAVE_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_LEFT_NFY)
HOBJECT			hMember;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_KICK_OUT_RES)
WORD			wResultCode;
HOBJECT			hTargetMember;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_KICKED_OUT_NFY)
HOBJECT			hMember;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHANGE_LEADER_RES)
WORD			wResultCode;
HOBJECT			hNewLeader;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_LEADER_CHANGED_NFY)
HOBJECT					hNewLeader;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_LEVELED_UP_NFY)
HOBJECT			hMember;
BYTE			byLevel;
WORD			wMaxLP;
WORD			wMaxEP;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_CLASS_CHANGED_NFY)
HOBJECT			hMember;
BYTE			byNewClass;		// ePC_CLASS
END_PROTOCOL()
//------------------------------------------------------------------
/*BEGIN_PROTOCOL(GU_PARTY_OPEN_CHARM_SLOT_RES)
WORD			wResultCode;
BYTE			byCharmInventoryIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHARM_SLOT_OPENED_NFY)
BYTE			byCharmInventoryIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CLOSE_CHARM_SLOT_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHARM_SLOT_CLOSED_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_REGISTER_VICTIM_ITEM_RES)
WORD			wResultCode;
BYTE			bySrcPlace;
BYTE			bySrcPos;
BYTE			byDestSlotIndex;
DWORD			dwTotalVictimItemScore;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_VICTIM_ITEM_REGISTERED_NFY)
HOBJECT			hMember;
sDBO_PARTY_VICTIM_ITEM_INFO		itemInfo;
DWORD			dwTotalVictimItemScore;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_UNREGISTER_VICTIM_ITEM_RES)
WORD			wResultCode;
BYTE			byDestSlotIndex;
DWORD			dwTotalVictimItemScore;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_VICTIM_ITEM_UNREGISTERED_NFY)
HOBJECT			hMember;
TBLIDX			itemTblidx;
BYTE			byDestSlotIndex;
DWORD			dwTotalVictimItemScore;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_REGISTER_VICTIM_ZENNY_RES)
WORD			wResultCode;
DWORD			dwRegisteredZenny;
DWORD			dwReturningZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_VICTIM_ZENNY_REGISTERED_NFY)
HOBJECT			hMember;
DWORD			dwIncreasedZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_UNREGISTER_VICTIM_ZENNY_RES)
WORD			wResultCode;
DWORD			dwUnregisteredZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_VICTIM_ZENNY_UNREGISTERED_NFY)
HOBJECT			hMember;
DWORD			dwDecreasedZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_DECLARE_ZENNY_RES)
WORD							wResultCode;

DWORD							dwInitialZenny;
DWORD							dwFinalDeclaredZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_DECLARED_ZENNY_CHANGED_NFY)
HOBJECT							hMember;
DWORD							dwDeclaredZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHARM_ACTIVATION_FAILED_NFY)
WORD							wResultCode;
HOBJECT							hMember;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_ACTIVATE_CHARM_RES)
WORD			wResultCode;
BYTE							byCharmInventoryIndex;
TBLIDX							registeredCharmTblidx;
DWORD							dwRemainingTime;
END_PROTOCOL()*/
//------------------------------------------------------------------
/*BEGIN_PROTOCOL(GU_PARTY_CHARM_ACTIVATED_NFY)
BYTE							byCharmInventoryIndex;
TBLIDX							registeredCharmTblidx;
DWORD							dwRemainingTime;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_DEACTIVATE_CHARM_RES)
WORD							wResultCode;
BYTE							byCharmInventoryIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHARM_DEACTIVATED_NFY)
BYTE							byCharmInventoryIndex;
END_PROTOCOL()*/
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHANGE_ZENNY_LOOTING_METHOD_RES)
WORD							wResultCode;
BYTE							byNewLootingMethod;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_ZENNY_LOOTING_METHOD_CHANGED_NFY)
BYTE							byNewLootingMethod;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHANGE_ITEM_LOOTING_METHOD_RES)
WORD							wResultCode;
BYTE							byNewLootingMethod;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_ITEM_LOOTING_METHOD_CHANGED_NFY)
BYTE							byNewLootingMethod;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_ZENNY_LOOTING_METHOD_UNLOCKED_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_ITEM_LOOTING_METHOD_UNLOCKED_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_ZENNY_UPDATED_NFY)
BYTE byMemberCount;
sINVEST_ZENNY_INFO aZennyInfo[MAX_MEMBER_IN_PARTY];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVENTORY_ITEM_ADDED_NFY)
BYTE							bySlotIndex;
sPARTY_INVENTORY_ITEM_INFO		newLoot;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVENTORY_ITEM_REMOVED_NFY)
BYTE					byPos;
bool					bIsYourItem;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_GAINED_ITEM_NFY)
HOBJECT					hMember;
// If itemTblidx is INVALID_TBLIDX, this means an unidentified item.
// itemTblidx°¡ INVALID_TBLIDXÀÏ °æ¿ì, °¨Á¤ÀÌ ÇÊ¿äÇÑ ¾ÆÀÌÅÛÀÓÀ» ¶æÇÑ´Ù.
// by YOSHIKI(2006-11-02)
TBLIDX					itemTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_GAINED_ZENNY_NFY)
HOBJECT					hMember;
bool					bIsShared;
DWORD					dwZenny; //dwAcquisitionZenny + dwBonusZenny
DWORD					dwAcquisitionZenny;
DWORD					dwBonusZenny;

// 'dwOriginalZenny' MUST NOT be referred if 'bSharedInParty' is false.
// bSharedInParty°¡ falseÀÌ¸é dwOriginalZenny°ªÀº ÂüÁ¶ÇØ¼­´Â ¾È µÈ´Ù.
// by YOSHIKI(2007-10-02)
DWORD					dwOriginalZenny; //MobÀÌ DropÇÑ Zenny
END_PROTOCOL()
//------------------------------------------------------------------
/*BEGIN_PROTOCOL(GU_PARTY_INVEST_ZENNY_RES)
WORD					wResultCode;
BYTE					byPos;
DWORD					dwInvestedZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEST_ZENNY_NFY)
BYTE					byPos;
DWORD					dwInvestedZenny;
HOBJECT					hMember;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVENTORY_ITEM_WINNER_CHANGED_NFY)
BYTE					byPos;
HOBJECT					hWinner;
DWORD					dwInvestedZenny;
END_PROTOCOL()*/
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_MEMBER_LOCATION_NFY)
HOBJECT					hMember;
TBLIDX					worldTblidx;
WORLDID					worldId;
sVECTOR3				vCurLoc;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BANK_START_RES)
HOBJECT			handle;			// Npc handle
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BANK_MOVE_RES)
HOBJECT			handle;
HOBJECT			hSrcItem;
HOBJECT			hDstItem;
BYTE			bySrcPlace;
BYTE			bySrcPos;
BYTE			byDestPlace;
BYTE			byDestPos;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BANK_MOVE_STACK_RES)
HOBJECT			handle;
HOBJECT			hSrcItem;
HOBJECT			hDestItem;
BYTE			bySrcPlace;
BYTE			bySrcPos;
BYTE			byDestPlace;
BYTE			byDestPos;
BYTE			byStackCount1;
BYTE			byStackCount2;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BANK_END_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BANK_ZENNY_INFO)
DWORD			dwZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BANK_ITEM_INFO)
BYTE			byBeginCount;
BYTE			byItemCount;
sITEM_PROFILE	aBankProfile[MAX_COUNT_USER_HAVE_BANK_ITEM];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BANK_ZENNY_RES)
HOBJECT				handle;
WORD				wResultCode;
DWORD				dwZenny;
bool				bIsSave;		// 1: Àú±Ý 0: ÀÎÃâ
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BANK_BUY_RES)
HOBJECT				hNpchandle;
WORD				wResultCode;
HOBJECT				hItemhandle;
sITEM_DATA			sData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BANK_ITEM_DELETE_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SOCIAL_ACTION)
HOBJECT			hSubject;
TBLIDX			socialActionId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SCOUTER_INDICATOR_RES)
HOBJECT			hTarget;
WORD			wResultCode;
DWORD			dwRetValue;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SCOUTER_PREDICT_RES)
BYTE			byPusNum;
WORD			wResultCode;
BYTE			byRetRate;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SCOUTER_EQUIP_CHECK_RES)
HOBJECT			hTarget;
WORD			wResultCode;
BYTE			byItemCount;
sITEM_PROFILE	aItemProfile[MAX_EQUIP_ITEM_SLOT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SCOUTER_CHIP_REMOVE_ALL_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TS_CONFIRM_STEP_RES)
BYTE				byTsType; // Æ®¸®°Å Å¸ÀÔ
WORD				wResultCode;
TS_T_ID			tId;
TS_TC_ID		tcCurId;
TS_TC_ID		tcNextId;
DWORD				dwParam;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TS_UPDATE_SYNC_NFY)
BYTE				byTsType; // Æ®¸®°Å Å¸ÀÔ
TS_T_ID			tId;
TS_TC_ID		tcId;
TS_TA_ID		taId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TS_UPDATE_STATE)
BYTE				byTsType; // Æ®¸®°Å Å¸ÀÔ
TS_T_ID			tId;
BYTE				byType;
WORD				wTSState;
DWORD				dwParam;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TS_UPDATE_EVENT_NFY)
BYTE				byTsType; // Æ®¸®°Å Å¸ÀÔ
TS_EVENT_ID		teid;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TS_EXCUTE_TRIGGER)
BYTE				byTsType; // Æ®¸®°Å Å¸ÀÔ
TS_T_ID			tId; // Æ®¸®°Å ¾ÆÀÌµð
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TS_EXCUTE_TRIGGER_OBJECT_RES)
WORD				wResultCode;
HOBJECT				hTriggerObject;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TS_TRIGGER_OBJECT_DIALOG_NFY)
HOBJECT				hTriggerObject;
BYTE				byDialogType;		// eNPCCONV_TYPE
TBLIDX				textTblidx;			// text
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TS_PC_DIALOG_NFY)
TBLIDX				textTblidx;			// text
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TS_SKIP_CONTAINER)
TS_T_ID			tId;
TS_TC_ID		tcId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_ITEM_CREATE_NFY)
BYTE				byPos;
TBLIDX				qItemTblidx;
BYTE				byCurCount;			// ÇöÀç Ä«¿îÆ®
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_ITEM_DELETE_NFY)
BYTE				byDeletePos;		// »èÁ¦ÇÑ ¾ÆÀÌÅÛÀÇ À§Ä¡
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_ITEM_UPDATE_NFY)
BYTE				byPos;
BYTE				byCurCount;			// ÇöÀç Ä«¿îÆ®
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_ITEM_MOVE_RES)
WORD				wResultCode;
BYTE				bySrcPos;
TBLIDX				dwSrcTblidx;
BYTE				byDestPos;
TBLIDX				dwDestTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_ITEM_DELETE_RES)
WORD				wResultCode;
BYTE				byDeletePos;		// »èÁ¦ÇÑ ¾ÆÀÌÅÛÀÇ À§Ä¡
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_SVREVT_START_NFY)
TS_T_ID				tId;
TS_TC_ID			tcId;
TS_TA_ID			taId;
BYTE				test;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_SVREVT_END_NFY)
TS_T_ID				tId;
TS_TC_ID			tcId;
TS_TA_ID			taId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_SVREVT_UPDATE_NFY)
TS_T_ID				tId;
TS_TC_ID			tcId;
TS_TA_ID			taId;
BYTE					bySvrEvtType;		// eSTOC_EVT_DATA_TYPE
BYTE					bySlot;
uSTOC_EVT_UPDATE_DATA	uEvtData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_GIVEUP_RES)
TS_T_ID			tId;
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_SHARE_NFY)				// Äù½ºÆ® °øÀ¯
WORD				wResultCode;
TS_T_ID			tId;
HOBJECT				hActor;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_RESET_NFY)			// Äù½ºÆ®ÀÇ ÁöÁ¤µÈ ¹üÀ§¸¸Å­ ÁøÇà Á¤º¸¿Í ¿Ï·á Á¤º¸¸¦ »èÁ¦ÇÑ´Ù.
QUESTID				startResetQID;		// ¹üÀ§ ÁöÁ¤
QUESTID				endResetQID;		// ¹üÀ§ ÁöÁ¤
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_OBJECT_VISIT_RES)
WORD				wResultCode;

QUESTID				qId;
WORLDID				worldId;
BYTE				byObjType;
TBLIDX				objectTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUEST_FORCED_COMPLETION_NFY)
QUESTID				questId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_FREEBATTLE_CHALLENGE_RES)
HOBJECT				hTarget; // ´ëÀüÀ» ¿äÃ»Çß´ø Å¸°ÙÀÇ ÇÚµé
WORD				wResultCode; // ÀÀ´ä ÄÚµå
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_FREEBATTLE_ACCEPT_REQ)
HOBJECT				hChallenger; // ´ëÀüÀ» ¿äÃ»ÇÑ Ä³¸¯ÅÍÀÇ ÇÚµé
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_FREEBATTLE_CANCEL_NFY)
WORD				wResultCode; // ´ëÀüÃë¼Ò¿¡ ´ëÇÑ ÀÌÀ¯
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_FREEBATTLE_START_NFY)
HOBJECT				hTarget; // ´ëÀü»ó´ë ÇÚµé
sVECTOR3			vRefreeLoc;	// ½ÉÆÇ À§Ä¡
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_FREEBATTLE_OUTSIDE_NFY)

END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_FREEBATTLE_INSIDE_NFY)

END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_FREEBATTLE_END_NFY)
BYTE				byFreeBattleResult; // eFREEBATTLE_RESULT
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUICK_SLOT_UPDATE_RES)
WORD				wResultCode;
TBLIDX				tblidx;
BYTE				bySlotID;
BYTE				byType;
BYTE				byPlace;
BYTE				byPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUICK_SLOT_DEL_NFY)
BYTE				bySlotID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_QUICK_SLOT_INFO)
BYTE				byQuickSlotCount;
sQUICK_SLOT_PROFILE	asQuickSlotData[CHAR_QUICK_SLOT_MAX_COUNT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PET_CHAR_INFO)
HOBJECT				handle;
BYTE				byObjectType;		// eOBJTYPE
union
{
	sSUMMON_PET_PROFILE		sSummonPetProfile;
	sITEM_PET_PROFILE		sItemPetProfile;
};
WORD				wCharStateSize; //-[9/7/2006 zeroera] : ¼³¸í : Å¬¶óÀÌ¾ðÆ®¸¦ À§ÇÑ Ä³¸¯ÅÍ»óÅÂ »çÀÌÁî Á¤º¸
sCHARSTATE			sCharState;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PET_SKILL_INFO)
BYTE				bySkillCount;
sSKILL_INFO_PET		aSkillInfo[MAX_NPC_HAVE_SKILL];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PET_INFO_END)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PET_DESPAWNED_NFY)
BYTE				byAvatarType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PET_DISMISS_PET_RES)
WORD				wResultCode;
BYTE				byAvatarType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ACTION_REPORT_MESSAGE)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_START_NFY)
HOBJECT				handle;			// ¿äÃ»ÀÚ ÇÚµé
HOBJECT				hTarget;		// Å¸°Ù ÇÚµé  (ÀÚ±â ÀÚ½Å)
WORD				wResultCode;	// Å¸°ÙÀÇ ÀÀ´ä¹× °¡´É À¯¹« ¿¡ µû¸¥ ¿©·¯°¡Áö °á°ú°ª
BYTE				byEmptyInven;	// »ó´ëÀÇ ÀÎº¥ÀÇ ºó°ø°£	(¸¸¾à ÃÖ´ëÄ­º¸´Ù ÀÛÀ¸¸é ºñÈ°¼ºÄ­¼ö Ç¥½Ã)	
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_START_RES)
HOBJECT				handle;			// ¿äÃ»ÀÚ ÇÚµé (ÀÚ±â ÀÚ½Å)
HOBJECT				hTarget;		// Å¸°Ù ÇÚµé
WORD				wResultCode;	// Å¸°ÙÀÇ ÀÀ´ä¹× °¡´É À¯¹« ¿¡ µû¸¥ ¿©·¯°¡Áö °á°ú°ª
BYTE				byEmptyInven;	// »ó´ëÀÇ ÀÎº¥ÀÇ ºó°ø°£	(¸¸¾à ÃÖ´ëÄ­º¸´Ù ÀÛÀ¸¸é ºñÈ°¼ºÄ­¼ö Ç¥½Ã)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_OK_REQ)
HOBJECT				handle;			// ¿äÃ»ÀÚÀÇ ÇÚµé
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_ADD_NFY)			// ¼º°øÀÏ ¶§¸¸
											//HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
HOBJECT				hItem;				// »ó´ë ¾ÆÀÌÅÛ ÇÚµé
sITEM_DATA			sItem;				// »ó´ë°¡ ¿Ã·Á ³õÀ» ¾ÆÀÌÅÛÀÇ Á¤º¸
BYTE				byCount;			// °ãÃÄÀÖ´Â ¾ÆÀÌÅÛÁß ¸î°³ÀÎ°¡? Default 1°³
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_ADD_RES)
//HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
HOBJECT				hItem;				// ³» ¾ÆÀÌÅÛ ÇÚµé
BYTE				byCount;			// °ãÃÄÀÖ´Â ¾ÆÀÌÅÛÁß ¸î°³ÀÎ°¡? Default 1°³
WORD				wResultCode;		// Å¸°ÙÀÇ ÀÀ´ä¹× °¡´É À¯¹« ¿¡ µû¸¥ ¿©·¯°¡Áö °á°ú°ª
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_DEL_NFY)			// ¼º°øÀÏ ¶§¸¸
											//HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
	HOBJECT				hItem;				// »ó´ë ¾ÆÀÌÅÛ ÇÚµé
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_DEL_RES)
//HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
HOBJECT				hItem;				// ³» ¾ÆÀÌÅÛ ÇÚµé
WORD				wResultCode;		// Å¸°ÙÀÇ ÀÀ´ä¹× °¡´É À¯¹« ¿¡ µû¸¥ ¿©·¯°¡Áö °á°ú°ª
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_MODIFY_NFY)
HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
HOBJECT				hItem;				// ³» ¾ÆÀÌÅÛ ÇÚµé
BYTE				byCount;			// °ãÃÄÀÖ´Â ¾ÆÀÌÅÛÁß ¸î°³ÀÎ°¡? Default 1°³
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_MODIFY_RES)
HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
HOBJECT				hItem;				// ³» ¾ÆÀÌÅÛ ÇÚµé
BYTE				byCount;			// °ãÃÄÀÖ´Â ¾ÆÀÌÅÛÁß ¸î°³ÀÎ°¡? Default 1°³
WORD				wResultCode;		// Å¸°ÙÀÇ ÀÀ´ä¹× °¡´É À¯¹« ¿¡ µû¸¥ ¿©·¯°¡Áö °á°ú°ª
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_ZENNY_UPDATE_NFY)	// ¼º°øÀÏ ¶§¸¸
HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
DWORD				dwZenny;			// ¿Å±æ ¸¸Å­ÀÇ Á¦´Ï (ÀÚ±â°¡ °®°í ÀÖ´Â Á¦´Ï ÇÑµµ ³»)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_ZENNY_UPDATE_RES)
HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
DWORD				dwZenny;			// ¿Å±æ ¸¸Å­ÀÇ Á¦´Ï (ÀÚ±â°¡ °®°í ÀÖ´Â Á¦´Ï ÇÑµµ ³» »ó´ëÀÇ Á¦´Ï°¡ ¿À¹ö µÇ¸é ÀÚµ¿ ½ÇÆÐ)
WORD				wResultCode;		// Å¸°ÙÀÇ ÀÀ´ä¹× °¡´É À¯¹« ¿¡ µû¸¥ ¿©·¯°¡Áö °á°ú°ª
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_END_NFY)
HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
WORD				wResultCode;		// Å¸°ÙÀÇ ÀÀ´ä¹× °¡´É À¯¹« ¿¡ µû¸¥ ¿©·¯°¡Áö °á°ú°ª
bool				bIsSet;				// false: Ç®¸² true: Àá±è
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_END_RES)
HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
DWORD				dwPacketCount;		// »ó´ë¹æÀÇ º¯°æ Ä«¿îÆ® ( »ó´ë¹æÀÌ ¹°°ÇÀ» ¿Ã·Á³õ°Å³ª »èÁ¦ È¤Àº º¯°æ µî ÆÐÅ¶¹ÞÀº °³¼ö )
WORD				wResultCode;		// Å¸°ÙÀÇ ÀÀ´ä¹× °¡´É À¯¹« ¿¡ µû¸¥ ¿©·¯°¡Áö °á°ú°ª
bool				bIsSet;				// false: Ç®¸² true: Àá±è
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_CANCEL_NFY)
HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_CANCEL_RES)
HOBJECT				hTarget;			// Å¸°Ù ÇÚµé
WORD				wResultCode;		// Å¸°ÙÀÇ ÀÀ´ä¹× °¡´É À¯¹« ¿¡ µû¸¥ ¿©·¯°¡Áö °á°ú°ª
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRADE_DENY_RES)
bool				bIsDeny;			// °ÅÀý ÇÁ·¹±× 
WORD				wResultCode;		// ¸¸¾à ±³È¯ÁßÀÌ¶ó¸é ½ÇÆÐÇÑ´Ù. ±×¿Ü ¼º°ø ¹× °á°ú
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_NAME_CHANGED_NFY)
HOBJECT				hSubject;
WCHAR				wszGuildName[MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_CREATE_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_INVITE_RES)
WORD				wResultCode;
WCHAR				wszTargetName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TOBJECT_UPDATE_STATE)
HOBJECT				handle;
sTOBJECT_BRIEF		tobjectBrief;
sTOBJECT_STATE		tobjectState;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TOBJECT_ACTION_ATTACK)
HOBJECT				hSubject;				// ¾×¼Ç ÁÖÃ¼ Ä³¸¯ÅÍ ÇÚµé
HOBJECT				hTarget;				// ¾×¼Ç Å¸°Ù Ä³¸¯ÅÍ ÇÚµé
BYTE				byAttackType;			// ¾×¼Ç °á°ú ( eBATTLE_ATTACK_RESULT )
BYTE				byAttackResult;			// ¾×¼Ç °á°ú ( eBATTLE_ATTACK_RESULT )
WORD				wAttackResultValue;		// ¾×¼ÇÀÇ °á°ú °ª ( µ¥¹ÌÁö )
sVECTOR3			vShift;					// ¾îÅÃÀ¸·Î ÀÎÇÑ ÀÌµ¿ º¤ÅÍ
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TUTORIAL_HINT_UPDATE_RES)
WORD				wResultCode;
DWORD				dwTutorialHint;
END_PROTOCOL()
//------------------------------------------------------------------
/*BEGIN_PROTOCOL( GU_TIMEQUEST_ROOM_LIST_RES )
WORD					wResultCode;			// ÀÀ´äÄÚµå
sTIMEQUEST_ROOM_TMQ_INFO	sTMQInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_TIMEQUEST_ROOM_INFO_RES )
WORD					wResultCode;			// ÀÀ´äÄÚµå
BYTE						byRoomState;			// eTIMEQUEST_ROOM_STATE
uTIMEQUEST_ROOM_ICON_INFO	sIconInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_TIMEQUEST_ROOM_JOIN_RES )
WORD					wResultCode;			// ÀÀ´äÄÚµå
sTIMEQUEST_ROOM_JOIN_INFO	sJoinInfo;
HOBJECT						hTroubleMember;			// joinÀÌ ½ÇÆÐÇÑ pcÀÇ ÇÚµé
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_TIMEQUEST_ROOM_JOIN_NFY )
sTIMEQUEST_ROOM_JOIN_INFO	sJoinInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_TIMEQUEST_ROOM_LEAVE_RES )
WORD					wResultCode;			// ÀÀ´äÄÚµå
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_TIMEQUEST_ROOM_LEAVE_NFY )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_TIMEQUEST_ROOM_SELECTION_NFY )
bool							bIsSecondWinner;
uTIMEQUEST_ROOM_SELECTION_INFO	uSelectionInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_TIMEQUEST_ROOM_TELEPORT_RES )
WORD					wResultCode;
END_PROTOCOL()*/
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_START_NFY)
WORD					wResultCode;			// °á°ú ÄÚµå ( ½ÇÆÐ ÇÒ ¼öµµ ÀÖÀ½, ¹Ýµå½Ã È®ÀÎÇÒ °Í)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_START_EXCEPTION_NFY)
WORD					wResultCode;			// °á°ú ÄÚµå
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_LEAVE_NFY)
HOBJECT					handle;					// ÅðÀåÇÑ ¸â¹öÀÇ ÇÚµé
WORD					wResultCode;			// ÀÌÀ¯¸¦ ³ªÅ¸³»´Â ÀÀ´ä ÄÚµå
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_COUNTDOWN_NFY)
bool					bCountDown;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_REWARD_NFY)
BYTE					byTriggerType;			// º¸»ó °ü·Ã tsÅ¸ÀÔ Á¤º¸
TS_EVENT_ID			teid;					// º¸»ó °ü·Ã tsÀÌº¥Æ® Á¤º¸
DWORD					dwWaitTime;				// Reward Wait ½Ã°£
DWORD					dwClearTime;			// Å¬¸®¾î ½Ã°£
DWORD					dwBonusTime;			// º¸³Ê½º ½Ã°£
bool					bIsDayRecord : 1;			// DayRecord¸¦ ¼¼¿üÀ» °æ¿ì true
bool					bIsBestRecord : 1;			// º£½ºÆ® ·¹ÄÚµå¸¦ ¼¼¿üÀ» °æ¿ì¿¡´Â true
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_INFORMATION_NFY)
BYTE					byInfoType;				// Á¤º¸ Å¸ÀÔ eTIMEQUEST_INFORMATION_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TELECAST_MESSAGE_BEG_NFY)
TBLIDX					npcTblidx;				// ¹æ¼ÛÀ» ÇÏ´Â NPC Å×ÀÌºí ÀÎµ¦½º
BYTE					byTelecastType;			// ¹æ¼Û Å¸ÀÔ eTELECAST_MESSAGE_TYPE
TBLIDX					speechTblidx;			// ¹æ¼Û³»¿ëÀ» ´ãÀº Speech Å×ÀÌºí ÀÎµ¦½º
DWORD					dwDisplayTime;			// ¹æ¼Û½Ã°£À» ³ªÅ¸³»´Â millisec ( INVALID_DWORD ÀÌ¸é telecast¸¦ °è¼Ó ¶ç¿ì°í, ¾Æ´Ï¸é ÀÌ ½Ã°£ÀÌ Áö³ª¸é ¾ø¾Ù °Í )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TELECAST_MESSAGE_END_NFY)

END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BROAD_MESSAGE_BEG_NFY)
BYTE byUIDirType;			// eBROAD_MSG_UI_DIR_TYPE
BYTE byUIShowHideTypel;		// eBROAD_MSG_UI_SHOWHIDE_DIR_TYPE
BYTE byUIBalloonShapeType;	// eBROAD_MSG_UI_BALLOON_SHAPE_TYPE
BYTE byUISpeechDirType;		// eBROAD_MSG_UI_SPEECH_DIR_TYPE
BYTE byOwnerCondition;		// eBROAD_MSG_OWNER_CONDITION
BYTE byOwnerType;			// eBROAD_MSG_OWNER_TYPE
unsigned int uiOwnerTblIdx;
unsigned int uiQuestTextTblidx;
float fDisplayTime;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BROAD_MESSAGE_END_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MINI_NARRATION_NFY)
unsigned int uiNarrtionTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PROGRESS_MESSAGE_NFY)
BYTE					byProgressType;			// ÁøÇà Å¸ÀÔ ePROGRESS_MESSAGE_TYPE
BYTE					byMessageType;			// ¸Þ½ÃÁö Å¸ÀÔ eTIMEQUEST_MESSAGE_TYPE
BYTE					byMessageValue;			// ¸Þ½ÃÁöÀÇ °ª 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DIRECTION_INDICATE_NFY)
bool					bIndicate;				// true : Arrow On, false : Arrow Off
sVECTOR3				vLoc;					// ÁöÁ¤À§Ä¡ ( Off ÀÏ°æ¿ì AccessÇÏÁö ¸»°Í )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_UPDATE_GAME_STATE)
sTIMEQUEST_STATE		sTimeQuestState;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_UPDATE_KILL_COUNT)
HOBJECT					handle;					// Å¸ÀÓ Äù½ºÆ® Áß¿¡ ±âÀýÇÑ 
BYTE					byKillCount;			// 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_UPDATE_COUPON_COUNT)
BYTE					byCouponCount;			// Å¸ÀÓ Äù½ºÆ® ÄíÆù °³¼ö
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_UPDATE_TMQ_POINT)
WORD					wTmqPoint;				// Å¸ÀÓ Äù½ºÆ® TMQ Æ÷ÀÎÆ®
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TIMEQUEST_UPDATE_GAME_TIME)
DWORD					dwClearTime;			// Å¸ÀÓ Äù½ºÆ® Å¬¸®¾î ½Ã°£ ( Áõ°¡µÇ´Â ½Ã°£ )
DWORD					dwBonusTime;			// Å¸ÀÓ Äù½ºÆ® º¸³Ê½º ½Ã°£
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_INFO_RES)
WORD					wResultCode;

WORD					byBattleMode;		// eRANKBATTLE_MODE
WORD					dwRemainTime;		// ³²Àº ½Ã°£
BYTE					byArenaCount;
sRANKBATTLE_ARENA_INFO	asArenaInfo[1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_JOIN_RES)
WORD					wResultCode;

HOBJECT					hBoardObject;
TBLIDX					rankBattleTblidx;
DWORD					dwRemainTime;		// ³²Àº ½Ã°£
BYTE					byArenaCount;
sRANKBATTLE_ARENA_INFO	asArenaInfo[1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_JOIN_NFY)
TBLIDX					rankBattleTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_LEAVE_RES)
WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_LEAVE_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_MATCH_START_NFY)
WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_MATCH_CANCELED_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
/*BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_LIST_RES )
WORD					wResultCode;

TBLIDX					rankBattleTblidx;	// RankBattle Tblidx

WORD					wTotalPage;			// °Ô½ÃÆÇ ÃÑ ÆäÀÌÁö
WORD					wCurPage;			// °Ô½ÃÆÇ Ãâ·Â Page

BYTE					byRoomMode;			// RankBattle ¸ðµå : eRANKBATTLE_MODE
BYTE					byRoomCount;		// Àü¼ÛÇÏ´Â RoomÀÇ °¹¼ö

uRANKBATTLE_ROOMINFO_LIST	uRoomList;		// Room List
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_INFO_RES )
WORD						wResultCode;

// ÆÐÅ¶ »çÀÌÁî °è»ê¿¡ ÁÖÀÇÇÑ´Ù.
// if( RANKBATTLE_MODE_INDIVIDUAL == byBattleMode )
// {
//		wMsgSize = sizeof(sGU_RANKBATTLE_ROOM_INFO_RES) - sizeof(uRANKBATTLE_ROOMINFO) + sizeof(sRANKBATTLE_ROOMINFO_INDIVIDUAL);
// }
// else if (RANKBATTLE_MODE_PARTY == byBattleMode )
// {
//		wMsgSize = sizeof(sGU_RANKBATTLE_ROOM_INFO_RES) - sizeof(uRANKBATTLE_ROOMINFO) + sizeof(sRANKBATTLE_ROOMINFO_PARTY) + sizeof(sRANKBATTLE_ROOMINFO_MEMBER) * (msg->uRoom.sParty.byMemberCount - 1);
// }

BYTE						byRoomMode;		// eRANKBATTLE_MODE
uRANKBATTLE_ROOMINFO		uRoom;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_CREATE_RES )
WORD						wResultCode;
TBLIDX						rankBattleTblidx;	// RankBattle Tblidx
ROOMID						roomId;
BYTE						byTroubleCount;		// ¹®Á¦¸¦ °¡Áö´Â ¸â¹öÀÇ ¼ö
sRANKBATTLE_MEMBER_RESULT	asTroublePc[1];		// ¹®Á¦¸¦ °¡Áö´Â ¸â¹ö Á¤º¸
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_CREATE_NFY )
WORD				wResultCode;
TBLIDX				rankBattleTblidx;	// RankBattle Tblidx
ROOMID				roomId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_LEAVE_RES )
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_LEAVE_NFY )
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_JOIN_INFO_NFY )
TBLIDX				rankBattleTblidx;	// RankBattle Tblidx
ROOMID				roomId;
BYTE				byTeamType;			// eRANKBATTLE_TEAM_TYPE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_CHALLENGE_RES )
WORD						wResultCode;
TBLIDX						rankBattleTblidx;	// RankBattle Tblidx
ROOMID						roomId;				// ¹æ ¹øÈ£
BYTE						byTroubleCount;		// ¹®Á¦¸¦ °¡Áö´Â ¸â¹öÀÇ ¼ö
sRANKBATTLE_MEMBER_RESULT	asTroublePc[1];		// ¹®Á¦¸¦ °¡Áö´Â ¸â¹ö Á¤º¸
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_CHALLENGE_NFY )
WORD				wResultCode;
TBLIDX				rankBattleTblidx;	// RankBattle Tblidx
ROOMID				roomId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_MATCH_READY_NFY )
WORD						wResultCode;
BYTE						byMemberCount;		// ¸â¹ö ¼ö
sRANKBATTLE_MEMBER_RESULT	asMemberResult[1];	// ¸â¹ö Á¤º¸
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_MATCH_START_NFY )
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_MATCH_CANCEL_RES )
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( GU_RANKBATTLE_ROOM_MATCH_CANCELED_NFY )
END_PROTOCOL()*/
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_BATTLE_STATE_UPDATE_NFY)
BYTE				byBattleState;
BYTE				byStage;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_BATTLE_TEAM_INFO_NFY)
WORD				wStraightWinCount;		// ¿¬½Â Ä«¿îÆ®
WORD				wStraightKOWinCount;	// KO ¿¬½Â Ä«¿îÆ®
BYTE				byCount;				// ÀÎ¿ø
WORD				wMemberInfo;			// sRANKBATTLE_MATCH_MEMBER_INFO [byCount]
WORD				wOwnerPartyName;		// WCHAR [MAX_SIZE_PARTY_NAME_IN_UNICODE]
WORD				wChallengerPartyName;	// WCHAR [MAX_SIZE_PARTY_NAME_IN_UNICODE]
sVARIABLE_DATA		sData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_BATTLE_PLAYER_STATE_NFY)
HOBJECT				hPc;
BYTE				byPCState;	// eRANKBATTLE_MEMBER_STATE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_BATTLE_KILLSCORE_UPDATE_NFY)
BYTE				byOwnerKillScore;
BYTE				byChallengerKillScore;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_BATTLE_STAGE_FINISH_NFY)
BYTE				byBattleResult;			// eRANKBATTLE_MATCH_RESULT
sRANKBATTLE_SCORE	sStageScore;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_BATTLE_MATCH_FINISH_NFY)
sRANKBATTLE_MATCH_FINISH_INFO	sMatchResult;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_BATTLE_END_NFY)
BYTE					byMatchWinner;		// eRANKBATTLE_MATCH_RESULT
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_BATTLE_FORCED_LEAVE_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RANKBATTLE_TOTAL_SCORE_UPDATE_NFY)
BYTE					byBattlemode;
sRANKBATTLE_SCORE_INFO	sTotalScore;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DRAGONBALL_CHECK_RES)// µå·¡°ïº¼ UI 7°³ ¹èÄ¡OK
HOBJECT				hObject;			// TS Object Á¦´Ü	
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DRAGONBALL_REWARD_RES)// µå·¡°ïº¼ ´Ù ¸ðÀ½¿¡ ´ëÇÑ º¸»ó ¼±ÅÃ ¿äÃ»
HOBJECT				hObject;			// TS Object Á¦´Ü
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DRAGONBALL_COLLECT_NFY) // ¼­¹öÀÇ ÀÏ¹æÀûÀÎ Åëº¸
HOBJECT				hObject;			// TS Object Á¦´Ü
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DRAGONBALL_SCHEDULE_INFO)
bool						bIsAlive;			// ±â°£ À¯¹« false: ±â°£ÀÌ ¾Æ´Ï´Ù
BYTE						byEventType;		// eSCHEDULE_EVENT_TYPE
__int64						nStartTime;			// ÃÖÃÊ±â°£ ½ÃÀÛ
__int64						nEndTime;           // ¸¶Áö¸· ±â°£ ³¡³ª´Â ½Ã°£
DWORD						dwMainTerm;			// ±â°£ ´ÜÀ§ (´ÞÀº ½ÃÀÛÀÏ ³ª¸ÓÁö´Â ÃÊ) 
DWORD						dwSubTerm;			// ±â°£ ´ÜÀ§ (´ÞÀº ¸¸·áÀÏ ³ª¸ÓÁö´Â ÃÊ) 
BYTE						byTermType;			// 0: ´Þ 1: ÀÏ 2: ½Ã
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_CREATE_RES)
WORD		 				wResultCode;
sPACKET_PRIVATESHOP_SHOP_DATA		sPrivateShopData;
//Private Shop ItemµéÀº GU_PRIVATESHOP_ITEM_DATA_INFO·Î º¸³½´Ù
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_CREATE_NFY)
HOBJECT							hOwner;
sSUMMARY_PRIVATESHOP_SHOP_DATA	sSummaryPrivateShopData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_EXIT_RES)
WORD						wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_OPEN_RES)
WORD						wResultCode;
sSUMMARY_PRIVATESHOP_SHOP_DATA	sSummaryPrivateShopData;
BYTE							byNoticeSize;
WCHAR							wcNotice[MAX_PRIVATESHOP_NOTICE_IN_UNICODE + 1];
//wcNotice°¡ °¡º¯ÀÌ±â ¶§¹®¿¡ wcNotice ¹Ø¿¡´Ù »õ·Î¿î º¯¼ö¸¦ ¼³Á¤ÇÏ¸é Àý´ë·Î ¾ÈµÈ´Ù.
//¹Ýµå½Ã byNoticeSizeÀ§¿¡ º¯¼ö ¼±¾ðÀ» ÇÒ°Í.[10/2/2007 SGpro]
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_OPEN_NFY)
HOBJECT							hOwner;//»óÁ¡ ÁÖÀÎ CharacterID
sSUMMARY_PRIVATESHOP_SHOP_DATA	sSummaryPrivateShopData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_CLOSE_RES)
WORD						wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_CLOSE_NFY)
HOBJECT						hOwner;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_ITEM_INSERT_RES)
WORD						wResultCode;
sPRIVATESHOP_ITEM_DATA		sPrivateShopItemData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_ITEM_UPDATE_RES)
WORD						wResultCode;
DWORD						dwZenny;
BYTE						byPrivateShopInventorySlotPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_ITEM_DELETE_RES)
WORD						wResultCode;
sPRIVATESHOP_ITEM_DATA		sPrivateShopItemData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_ITEM_BUYING_RES)
WORD						wResultCode;
sPRIVATESHOP_ITEM_DATA		sPrivateShopItemData[MAX_BUY_SHOPPING_CART];
BYTE						byBuyItemCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_ITEM_BUYING_NFY)
HOBJECT						hPrivateShopOwner;
sPRIVATESHOP_ITEM_DATA		sPrivateShopItemData[MAX_BUY_SHOPPING_CART];
BYTE						byBuyItemCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_ENTER_RES)
WORD						wResultCode;
sPACKET_PRIVATESHOP_SHOP_DATA		sPrivateShopData;
//Private Shop ItemµéÀº GU_PRIVATESHOP_ITEM_DATA_INFO·Î º¸³½´Ù
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_LEAVE_RES)
WORD						wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_ITEM_DATA_INFO)
WORD						wResultCode;
HOBJECT						hOwnerID;
sPRIVATESHOP_ITEM_DATA		sPrivateShopItemData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_ITEM_SELECT_RES)
WORD				wResultCode;
//HOBJECT				hOwner;
BYTE				byPrivateShopInventorySlotPos;
BYTE				byItemState;//eITEMSTATE °ªÀ» °®´Â´Ù
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_ITEM_SELECT_NFY)
//HOBJECT				hOwner;
BYTE				byPrivateShopInventorySlotPos;
BYTE				byItemState;//eITEMSTATE °ªÀ» °®´Â´Ù
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_ITEM_STATE_NFY)
//HOBJECT				hOwner;
BYTE				abyPrivateShopItemState[MAX_PRIVATESHOP_INVENTORY];
int					nPrivateShopItemStateCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_LEAVE_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_REQUEST_RES)
WORD						wResultCode;
BYTE						byPrivateShopInventorySlotPos;
BYTE						byItemState;//eITEMSTATE °ªÀ» °®´Â´Ù
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_REQUEST_NFY)
HOBJECT						hOwner;
BYTE						byPrivateShopInventorySlotPos;
BYTE						byItemState;//eITEMSTATE °ªÀ» °®´Â´Ù
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_CONSENT_REQ)
HOBJECT						hVisitorID;
BYTE						byPrivateShopInventorySlotPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_CONSENT_NFY)
HOBJECT						hOwner;
BYTE						byPrivateShopInventorySlotPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_WAITTIMEOUT_NFY)
HOBJECT						hOwner;
BYTE						byPrivateShopInventorySlotPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_PRICEFLUCTUATIONS_RES)
WORD						wResultCode;
BYTE						byPrivateShopInventorySlotPos;
DWORD						dwBeforeZenny;
DWORD						dwAfterZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_PRICEFLUCTUATIONS_NFY)
HOBJECT						hOwner;
BYTE						byPrivateShopInventorySlotPos;
DWORD						dwBeforeZenny;
DWORD						dwAfterZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_IMMEDIATE_ITEM_BUYING_RES)
WORD						wResultCode;
sPRIVATESHOP_ITEM_DATA		sPrivateShopItemData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_IMMEDIATE_ITEM_BUYING_NFY)
HOBJECT						hPrivateShopOwner;
sPRIVATESHOP_ITEM_DATA		sPrivateShopItemData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_WINDOWCLOSE_NFY)
HOBJECT						hPrivateShopOwner;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_CANCEL_RES)
WORD				wResultCode;
BYTE				byCancelType;
BYTE				byPrivateShopInventorySlotPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PRIVATESHOP_BUSINESS_CANCEL_NFY)
HOBJECT						hOwner;
BYTE						byCancelType;//1: ÈïÁ¤´ë±â¶§ Ãë¼Ò, 2: ÈïÁ¤¶§ Ãë¼Ò
BYTE						byPrivateShopInventorySlotPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TUTORIAL_WAIT_NFY)
WORD						wWaitingCount; // ÇöÀç ÀÚ½Å¾ÕÀÇ ´ë±â¼ö
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TUTORIAL_WAIT_CANCEL_RES)
WORD						wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TUTORIAL_PLAY_QUIT_RES)
WORD						wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_START_RES)
HOBJECT	hObject;	// ¸ÞÀÏ¼Û¼ö½ÅÅ¾ ¿ÀºêÁ§Æ® (½ºÄ«¿ìÆ®ÆÄÃ÷ Âø¿ë½Ã INVALID_OBJECT )
WORD 	wResultCode;	// °á°ú
bool	bIsAway;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_SEND_RES)
HOBJECT	hObject;	// ¸ÞÀÏ¼Û¼ö½ÅÅ¾ ¿ÀºêÁ§Æ® (½ºÄ«¿ìÆ®ÆÄÃ÷ Âø¿ë½Ã INVALID_OBJECT )
WCHAR wszTargetName[MAX_SIZE_CHAR_NAME_UNICODE + 1];	// ¹ÞÀ» Ä³¸¯ ÀÌ¸§
WORD wResultCode;	// ¼º°øÀ¯¹«
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_READ_RES)
HOBJECT	hObject;	// ¸ÞÀÏ¼Û¼ö½ÅÅ¾ ¿ÀºêÁ§Æ® (½ºÄ«¿ìÆ®ÆÄÃ÷ Âø¿ë½Ã INVALID_OBJECT )
MAILID	mailID;	// ¸ÞÀÏ ¾ÆÀÌµð
WORD	wResultCode;	// ¸ÞÀÏÀÌ ÀÌ¹Ì »èÁ¦ µÇ¾úÀ» ¶§´Â ½ÇÆÐ 
BYTE	byRemainDay;
DBOTIME endTime;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_DEL_RES)
HOBJECT	hObject;	// ¸ÞÀÏ¼Û¼ö½ÅÅ¾ ¿ÀºêÁ§Æ® (½ºÄ«¿ìÆ®ÆÄÃ÷ Âø¿ë½Ã INVALID_OBJECT )
MAILID	mailID;	// ¸ÞÀÏ ¾ÆÀÌµð
WORD	wResultCode;	// ¸ÞÀÏÀÌ ÀÌ¹Ì »èÁ¦ µÇ¾úÀ» ¶§´Â ½ÇÆÐ 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_RETURN_RES)
HOBJECT	hObject;	// ¸ÞÀÏ¼Û¼ö½ÅÅ¾ ¿ÀºêÁ§Æ® (½ºÄ«¿ìÆ®ÆÄÃ÷ Âø¿ë½Ã INVALID_OBJECT )
MAILID	mailID;	// ¸ÞÀÏ ¾ÆÀÌµð
WORD	wResultCode;	// ¸ÞÀÏÀÌ ÀÌ¹Ì »èÁ¦ µÇ¾úÀ» ¶§´Â ½ÇÆÐ 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_RELOAD_RES)
HOBJECT	hObject;	// ¸ÞÀÏ¼Û¼ö½ÅÅ¾ ¿ÀºêÁ§Æ® (½ºÄ«¿ìÆ®ÆÄÃ÷ Âø¿ë½Ã INVALID_OBJECT )
WORD wResultCode;	// ¼º°øÀ¯¹«
BYTE	byMailCount;		// ÇöÀç ÀüÃ¼¸ÞÀÏ Ä«¿îÆ® 
BYTE	byManagerCount;		// ÀÐÁö ¾ÊÀº ¸Å´ÏÁ® ¸ÞÀÏ Ä«¿îÆ®
BYTE	byNormalCount;		// ÀÐÁö ¾ÊÀº ³ë¸Ö ¸ÞÀÏ Ä«¿îÆ®
MAILID   aMailID[MAX_MAIL_SLOT_COUNT];	// Ä«¿îÆ®¿¡ ÇØ´çÇÏ´Â ÀúÀåµÈ ¸ÞÀÏ ¾ÆÀÌµð 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_RELOAD_NFY)		// ½ºÄÉÁÙ¿¡ ÀÇÇØ ÀÏÁ¤½Ã°£¿¡ µû¶ó ÀÚµ¿ ¼Û½Å
BYTE	byMailCount;		// ÇöÀç ÀüÃ¼¸ÞÀÏ Ä«¿îÆ® 
BYTE	byManagerCount;		// ÀÐÁö ¾ÊÀº ¸Å´ÏÁ® ¸ÞÀÏ Ä«¿îÆ®
BYTE	byNormalCount;		// ÀÐÁö ¾ÊÀº ³ë¸Ö ¸ÞÀÏ Ä«¿îÆ®
MAILID  aMailID[MAX_MAIL_SLOT_COUNT];	// Ä«¿îÆ®¿¡ ÇØ´çÇÏ´Â ÀúÀåµÈ ¸ÞÀÏ ¾ÆÀÌµð 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_LOAD_RES)
HOBJECT	hObject;		// ¸ÞÀÏ¼Û¼ö½ÅÅ¾ ¿ÀºêÁ§Æ® (½ºÄ«¿ìÆ®ÆÄÃ÷ Âø¿ë½Ã INVALID_OBJECT )
WORD	wResultCode;	// ¼º°øÀ¯¹«
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_LOAD_DATA)
sMAIL_NEW_PROFILE sData;
BYTE	byTextSize;
WCHAR	wszText[MAX_LENGTH_OF_MAIL_MESSAGE_IN_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_LOAD_INFO)
sMAIL_NEW_PROFILE sData;
BYTE	byTextSize;
WCHAR	wszText[MAX_LENGTH_OF_MAIL_MESSAGE_IN_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_ITEM_RECEIVE_RES)
HOBJECT	hObject;	// ¸ÞÀÏ¼Û¼ö½ÅÅ¾ ¿ÀºêÁ§Æ® (½ºÄ«¿ìÆ®ÆÄÃ÷ Âø¿ë½Ã INVALID_OBJECT )
WORD wResultCode;	// ¼º°øÀ¯¹«
MAILID	mailID;	// ¸ÞÀÏ ¾ÆÀÌµð
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_LOCK_RES)
HOBJECT	hObject;	// ¸ÞÀÏ¼Û¼ö½ÅÅ¾ ¿ÀºêÁ§Æ® (½ºÄ«¿ìÆ®ÆÄÃ÷ Âø¿ë½Ã INVALID_OBJECT )
MAILID	mailID;	// ¸ÞÀÏ ¾ÆÀÌµð
bool	bIsLock;		// Lock 1: Unlock: 0
WORD 	wResultCode;	// ¸ÞÀÏÀÌ ÀÌ¹Ì »èÁ¦ µÇ¾úÀ» ¶§´Â ½ÇÆÐ
BYTE	byExpiredDay;	// ³²Àº³¯Â¥
DBOTIME	endTime;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_CLOSE_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MAIL_MULTI_DEL_RES)
HOBJECT	hObject;		// ¸ÞÀÏ¼Û¼ö½ÅÅ¾ ¿ÀºêÁ§Æ® (½ºÄ«¿ìÆ®ÆÄÃ÷ Âø¿ë½Ã INVALID_OBJECT )
WORD	wResultCode;	// ¸ÞÀÏÀÌ ÀÌ¹Ì »èÁ¦ µÇ¾úÀ» ¶§´Â ½ÇÆÐ
BYTE	byCount;
MAILID	aMailID[MAX_COUNT_OF_MULTI_DEL];	// ¸ÞÀÏ ¾ÆÀÌµð
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PORTAL_START_RES)
WORD			wResultCode;
HOBJECT			hNpcHandle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PORTAL_INFO)
BYTE			byCount;
PORTALID		aPortalID[PORTAL_MAX_COUNT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PORTAL_ADD_RES)
WORD						wResultCode;
HOBJECT			hNpcHandle;
PORTALID		PortalID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PORTAL_RES)
WORD				wResultCode;
HOBJECT				hNpcHandle;
BYTE				byPoint;		// 0~7±îÁö ¼±ÅÃµÈ ÀÎµ¦½º
CNtlVector			vLoc;
CNtlVector			vDir;
DWORD				ZennybyPoint;
WORLDID				worldID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_WAR_FOG_INFO)
BYTE			abyWarFogInfo[MAX_SIZE_WAR_FOG];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_WAR_FOG_UPDATE_RES)
WORD			wResultCode;
HOBJECT			handle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MOB_LUCKY_DROP_NFY)
HOBJECT			hMobhandle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_UPGRADE_ALL_NFY)
BYTE			abyGrade[ITEM_UPGRADE_EQUIP_COUNT];  // ¹è¿­ ÀÎµ¦½º´Â ÇØ´ç Pos, Value´Â ÇØ´ç °á°ú ±×·¹ÀÌµå( 255 INVALID´Â ¾ÆÀÌÅÛÀÌ ¾ø´Â °æ¿ì)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BOT_BOTCAUTION_NFY)		//  [2/20/2008 SGpro]
HOBJECT			hBot;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_REPUTATION)
HOBJECT			handle;
DWORD			dwReputation;
END_PROTOCOL()
//-----------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_FUNCTION_ADD_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_GIVE_ZENNY_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_BANK_START_RES)
HOBJECT			handle;			// Npc handle
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_BANK_MOVE_RES)
HOBJECT			handle;
HOBJECT			hSrcItem;
HOBJECT			hDstItem;
BYTE			bySrcPlace;
BYTE			bySrcPos;
BYTE			byDestPlace;
BYTE			byDestPos;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_BANK_MOVE_STACK_RES)
HOBJECT			handle;
HOBJECT			hSrcItem;
HOBJECT			hDestItem;
BYTE			bySrcPlace;
BYTE			bySrcPos;
BYTE			byDestPlace;
BYTE			byDestPos;
BYTE			byStackCount1;
BYTE			byStackCount2;
ITEMID			splitItemId;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_BANK_END_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_BANK_ZENNY_INFO)
DWORD			dwZenny;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_BANK_ITEM_INFO)
BYTE            byPlace;
BYTE			byItemCount;
sITEM_PROFILE	aItemProfile[MAX_BANK_ITEM_SLOT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_BANK_ZENNY_RES)
HOBJECT			handle;
WORD			wResultCode;
DWORD			dwZenny;
bool			bIsSave;		// 1: Àú±Ý 0: ÀÎÃâ
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CROSSFIRE_RES)
HOBJECT			hTarget;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_CREATE_MARK_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_CHANGE_MARK_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_MARK_CHANGED_NFY)
HOBJECT				hSubject;
sDBO_GUILD_MARK		sMark;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BANK_LOAD_RES)
HOBJECT				handle;			// Npc handle
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_CHANGE_NAME_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_SHARETARGET_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_SHARETARGET_NFY)
sSHARETARGET_INFO		sharetargetInfo[MAX_SHARETARGET_COUNT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RIDE_ON_BUS_RES)
HOBJECT				hTarget;			// Npc handle
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_RIDE_OFF_BUS_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TRANSFORM_CANCEL_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_ITEM_IDENTIFY_RES)
WORD			wResultCode;
HOBJECT			hNpchandle;		// NpcHandle
BYTE			byPlace;
BYTE			byPos;
sITEM_DATA      sItemData;			// ¼º°ø½Ã¿¡¸¸ ¼¼ÆÃ
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MINORMATCH_STATE_UPDATE_NFY)
BYTE			byMatchState;		// eBUDOKAI_MAJORMATCH_STATE
bool			bIsEnter;			// true : Enter, false : exit
BYTE			byStage;
DWORD			dwRemainTime;		// ¹Ð¸®¼¼ÄÁµå ´ÜÀ§
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MINORMATCH_TEAM_INFO_NFY)
BYTE			byMatchIndex;		// ¸î¹øÂ° °æ±âÀÎÁö?[°³ÀÎ:0~31, ÆÀ:0~15]
BYTE			byTeamCount;
WORD			wTeamInfo_var;		// sMATCH_MINORMATCH_TEAM_INFO_VAR [MAX_MINORMATCH_TEAM_COUNT];
sVARIABLE_DATA	sData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MINORMATCH_PLAYER_STATE_NFY)
HOBJECT			hPc;
BYTE			byPcState;			// eMATCH_MEMBER_STATE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MINORMATCH_UPDATE_SCORE_NFY)
TEAMTYPE		wTeamType;
BYTE			byScore;
HOBJECT			hSlayer;			// ±âÀý½ÃÅ² character
HOBJECT			hFainter;			// ±âÀýÇÑ character
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MINORMATCH_TEAM_SCORE_NFY)
BYTE							byCount;
sMATCH_MINORMATCH_TEAM_SCORE	aTeamScore[BUDOKAI_MAX_MINORMATCH_TEAM_COUNT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MINORMATCH_SELECTION_NFY)
TEAMTYPE		teamWinner;
BYTE			byTeamCount;
sMINORMATCH_SELECTION_DATA	aSelection[BUDOKAI_MAX_MINORMATCH_TEAM_COUNT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MINORMATCH_STAGE_FINISH_NFY)
BYTE			byStageResult;		// eMATCH_RESULT
WORD			wStageWinner;		// Stage Winner TeamType
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MINORMATCH_MATCH_FINISH_NFY)
BYTE			byMatchResult;
WORD			wMatchWinner;
BYTE			byKillCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MAJORMATCH_STATE_UPDATE_NFY)
BYTE			byMatchState;		// eBUDOKAI_MAJORMATCH_STATE
bool			bIsEnter;			// true : Enter, false : exit
BYTE			byStage;
DWORD			dwRemainTime;		// ¹Ð¸®¼¼ÄÁµå ´ÜÀ§
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MAJORMATCH_TEAM_INFO_NFY)
BYTE			byMatchDepth;	// °³ÀÎ[8°­~32°­] ÆÀ[8°­~16°­]
BYTE			byMatchIndex;	// depth¿¡ µû¸¥ °æ±â À§Ä¡

BYTE			byTeamCount;
WORD			wTeamInfo_var;		// sMATCH_MINORMATCH_TEAM_INFO_VAR [2];
sVARIABLE_DATA	sData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MAJORMATCH_PLAYER_STATE_NFY)
HOBJECT			hPc;
BYTE			byPcState;			// eMATCH_MEMBER_STATE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MAJORMATCH_UPDATE_SCORE_NFY)
sMATCH_SCORE	sStageScore;		// ½ºÅ×ÀÌÁö ½ºÄÚ¾î
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MAJORMATCH_STAGE_FINISH_NFY)
BYTE			byStageResult;		// eMATCH_RESULT
WORD			wStageWinner;		// Stage Winner TeamType
sMATCH_SCORE	sMatchScore;		// °æ±â ½ºÄÚ¾î
bool			bIsObserver;		// ¿ÉÁ®¹ö ¸ðµå¿¡¼­ »ç¿ë
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_MAJORMATCH_MATCH_FINISH_NFY)
BYTE			byMatchResult;		// eMATCH_RESULT
WORD			wMatchWinner;		// Match Winner TeamType
sMATCH_SCORE	sMatchScore;		// °æ±â ½ºÄÚ¾î
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_FINALMATCH_STATE_UPDATE_NFY)
BYTE			byMatchState;		// eBUDOKAI_MAJORMATCH_STATE
bool			bIsEnter;			// true : Enter, false : exit
BYTE			byStage;
DWORD			dwRemainTime;		// ¹Ð¸®¼¼ÄÁµå ´ÜÀ§
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_FINALMATCH_TEAM_INFO_NFY)
BYTE			byMatchDepth;
BYTE			byMatchIndex;

BYTE			byTeamCount;
WORD			wTeamInfo_var;		// sMATCH_FINALMATCH_TEAM_INFO_VAR [4];
sVARIABLE_DATA	sData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_FINALMATCH_PLAYER_STATE_NFY)
HOBJECT			hPc;
BYTE			byPcState;			// eMATCH_MEMBER_STATE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_FINALMATCH_UPDATE_SCORE_NFY)
sMATCH_SCORE	sStageScore;		// ½ºÅ×ÀÌÁö ½ºÄÚ¾î
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_FINALMATCH_STAGE_FINISH_NFY)
BYTE			byStageResult;		// eMATCH_RESULT
WORD			wStageWinner;		// Stage Winner TeamType
sMATCH_SCORE	sMatchScore;		// °æ±â ½ºÄÚ¾î
bool			bIsObserver;		// ¿ÉÁ®¹ö ¸ðµå¿¡¼­ »ç¿ë
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_FINALMATCH_MATCH_FINISH_NFY)
BYTE			byMatchResult;		// eMATCH_RESULT
WORD			wMatchWinner;		// Match Winner TeamType
sMATCH_SCORE	sMatchScore;		// °æ±â ½ºÄÚ¾î
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MATCH_AWARDING_NFY)
WORD			awTeamName[MAX_FINALMATCH_RESULT];
sVARIABLE_DATA	sData;	// WCHAR wszTeamName[MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1]; : ÀúÀåµÈ °ªÀº NULLÀ» Æ÷ÇÔÇÏÁö ¾Ê´Â´Ù.
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_CONFUSE_TARGET_NFY)
HOBJECT			hSubject;
HOBJECT			hTarget;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_TERROR_COURSE_CHANGE_NFY)
HOBJECT			hSubject;
HOBJECT			hAttacker;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DICE_ROLL_RES)
WORD			wResultCode;
WORD			wDiceResult;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DICE_ROLLED_NFY)
HOBJECT			hSubject;
WORD			wDiceResult;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_STATE_INFO_NFY)
BUDOKAITIME							tmDefaultOpenTime;
bool								bRankbattleAllow;

sBUDOKAI_UPDATE_STATE_INFO			sStateInfo;
sBUDOKAI_UPDATE_MATCH_STATE_INFO	aMatchStateInfo[MAX_BUDOKAI_MATCH_TYPE];

sBUDOKAI_JOIN_INFO					sJoinInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_UPDATE_STATE_NFY)
sBUDOKAI_UPDATE_STATE_INFO			sStateInfo;
bool								bRankbattleAllow;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_UPDATE_MATCH_STATE_NFY)
BYTE								byMatchType;	// eBUDOKAI_MATCH_TYPE
sBUDOKAI_UPDATE_MATCH_STATE_INFO	sStateInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_JOIN_INDIVIDUAL_RES)
WORD			wResultCode;
WORD			wJoinId;			// Âü°¡ ¹øÈ£
bool			bDojoRecommender;	// µµÀåÃßÃµÀÚÀÎÁö?
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_LEAVE_INDIVIDUAL_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_JOIN_TEAM_INFO_RES)
WORD						wResultCode;

BYTE						byMemberCount;
sBUDOKAI_TEAM_POINT_INFO	asPointInfo[1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_JOIN_TEAM_RES)
WORD			wResultCode;
HOBJECT			hTroublePc;
float			fTotalRankPoint;
WORD			wJoinId;
WCHAR			wszTeamName[MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];

// 
BYTE						byMemberCount;
sBUDOKAI_TEAM_POINT_INFO	aTeamInfo[MAX_MEMBER_IN_PARTY];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_JOIN_TEAM_NFY)
float			fTotalRankPoint;
WORD			wJoinId;
WCHAR			wszTeamName[MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];

// 
BYTE						byMemberCount;
sBUDOKAI_TEAM_POINT_INFO	aTeamInfo[MAX_MEMBER_IN_PARTY];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_LEAVE_TEAM_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_LEAVE_TEAM_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_LEAVE_TEAM_MEMBER_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_LEAVE_TEAM_MEMBER_NFY)
WCHAR			wszMemberName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_JOIN_INFO_RES)
WORD					wResultCode;

BYTE					byMatchType;		// eBUDOKAI_MATCH_TYPE

											// ÃßÈÄ ´ÙÀ½ µ¥ÀÌÅÍ ¾ÐÃà ÇÊ¿ä
union
{
	sBUDOKAI_REGISTER_INDIVIDUAL_INFO	sIndividualInfo;
	sBUDOKAI_REGISTER_TEAM_INFO			sTeamInfo;
};
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_JOIN_STATE_RES)
WORD			wResultCode;
BYTE			byMatchType;		// eBUDOKAI_MATCH_TYPE
BYTE			byJoinState;		// eBUDOKAI_JOIN_STATE
BYTE			byJoinResult;		// Âü°¡ °á°ú
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_JOIN_STATE_NFY)
BYTE			byMatchType;		// eBUDOKAI_MATCH_TYPE
BYTE			byJoinState;		// eBUDOKAI_JOIN_STATE
BYTE			byJoinResult;		// eBUDOKAI_JOIN_RESULT
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DISCONNECTED_NFY)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_MUDOSA_INFO_RES)
WORD					wResultCode;
BYTE					byMudosaCount;
sBUDOKAI_MUDOSA_INFO	aMudosaInfo[BUDOKAI_MAX_MUDOSA_INFO_COUNT];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_MUDOSA_TELEPORT_RES)
WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_PROGRESS_MESSAGE_NFY)
BYTE					byMsgId;			// eBUDOKAI_PROGRESS_MESSAGE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_SOCIAL_ACTION_NFY)
HOBJECT				hSubject;
ANIMATIONID			socialAction;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_PRIZEWINNER_NAME_RES)
WORD				wResultCode;

// BUDOKAI_MATCH_TYPE_INDIVIDUAL
//- WCHAR		wszName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
WORD				wWinner;
WORD				wSecondWinner;

sVARIABLE_DATA		sData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_PRIZEWINNER_TEAM_NAME_RES)
WORD				wResultCode;

// BUDOKAI_MATCH_TYPE_TEAM
//- WCHAR		wszTeamName[MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
WORD				wWinner;
WORD				wSecondWinner;

sVARIABLE_DATA		sData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_GM_BUDOKAI_SERVER_ENTER_RES)
WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_GM_BUDOKAI_SERVER_LEAVE_RES)
WORD					wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_GM_MATCH_PROGRESS_INFO_RES)
WORD								wResultCode;

BYTE								byMatchType;		// eBUDOKAI_MATCH_TYPE
BYTE								byMatchWorldType;	// eMATCHWORLD_TYPE;
BYTE								byMatchDepth;		// eBUDOKAI_MATCH_DEPTH

BYTE								byStateCount;
sBUDOKAI_GM_MATCH_PROGRESS_STATE	aStateList[BUDOKAI_MAX_MATCH_COUNT];	// °¡º¯
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_GM_MATCH_ARENA_ENTER_RES)
WORD								wResultCode;

BYTE								byMatchType;		// eBUDOKAI_MATCH_TYPE
BYTE								byMatchWorldType;	// eMATCHWORLD_TYPE
BYTE								byMatchDepth;		// eBUDOKAI_MATCH_DEPTH
BYTE								byMatchIndex;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUDOKAI_GM_MATCH_ARENA_LEAVE_RES)
WORD								wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SCOUTER_TURN_ON_NFY)
HOBJECT			hSubject;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SCOUTER_TURN_OFF_NFY)
HOBJECT			hSubject;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SCOUTER_BROKEN_NFY)
HOBJECT			hSubject;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SCOUTER_ITEM_SELL_RES)
TBLIDX				itemTblidx;
BYTE				byPlace;
BYTE				byPos;
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_EVENTITEM_START_RES)
HOBJECT			handle;
BYTE			byType; //	0: ±âº»  1:ÇÑÁ¤¼ö·® ÆÇ¸Å ÀÌº¥Æ® NPC 
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_EVENTITEM_BUY_RES)
HOBJECT			handle;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_EVENTITEM_END_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_REPLACE)
HOBJECT			hDeleteItem;
HOBJECT			hCreateItem;
BYTE			byDeleteItemPlace;
BYTE			byDeleteItemPos;
sITEM_DATA      sCreateItemData;
bool			bIsNew;		// Effect Ãß°¡ 
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_GAMBLE_BUY_RES)
WORD			wResultCode;
HOBJECT			handle;
HOBJECT			hItem;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_DUNGEON_DIFF_NFY)
ePARTY_DUNGEON_STATE eDiff;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_DUNGEON_DIFF_RES)
WORD			wResultCode;
ePARTY_DUNGEON_STATE		eDiff;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_DUNGEON_INIT_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_DUNGEON_INIT_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_SP)
DWORD			dwSpPoint;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_INIT_NFY)
WORD			wResultCode;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_SKILL_INIT_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_REMOVE_NFY)
TBLIDX			skillId;
BYTE			bySlot;
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HTB_REMOVE_NFY)
TBLIDX			skillId;
BYTE			bySlot;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TELEPORT_PROPOSAL_NFY)
BYTE				byTeleportType;
BYTE				byInfoIndex;		// ¼­¹ö¿¡¼­ ÅÚ·¹Æ÷Æ® Á¤º¸¸¦ ÂüÁ¶ÇÏ±âÀ§ÇÑ ÀÎµ¦½º
WORD				wWaitTime;
TBLIDX				worldTblidx;		// ¿ùµå Å×ÀÌºí ÀÎµ¦½º : Á¤º¸¸¦ Á»´õ »ó¼¼ÇÏ°Ô Ãâ·ÂÇÏ±â À§ÇÑ ¿ëµµ.

union
{
	DWORD			dwReserve;
	BYTE			byBudokaiMatchDepth;	// ÃµÇÏÁ¦ÀÏ¹«µµÈ¸ XX°­
};

BYTE				bySummonerNameLength;
WCHAR				wszSummonnerName[MAX_SIZE_CHAR_NAME_UNICODE + 1];	// °¡º¯
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_TELEPORT_CONFIRM_RES)
WORD				wResultCode;

BYTE				byTeleportIndex;
bool				bTeleport;			// Å¬¶óÀÌ¾ðÆ®¿¡¼­ ¹ÞÀº °ª
bool				bClearInterface;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_PETITION_INFO)
PETITIONID			petitionID;
WCHAR				awchQuestionContent[MAX_SIZE_QUESTION_CONTENT_UNICODE + 1];
PETITIONCATEGORY	nCategory1;//ePETITIONSYSTEM_CATEGORY_1
PETITIONCATEGORY	nCategory2;//ePETITIONSYSTEM_CATEGORY_2
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GAME_COMMON_MSG_NFY)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HOIPOIMIX_RECIPE_REG_NFY)			// ·¹½ÃÇÇµî·Ï
TBLIDX				recipeTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HOIPOIMIX_ITEM_CHECK_RES)			// ¸¸µé¾ÆÀÌÅÛ ¼±ÅÃ (ÇÊ¿äÇÑ ¾ÆÀÌÅÛ ¼ö·® Ã¼Å©)
WORD				wResultCode;
HOBJECT				objHandle;
TBLIDX				recipeTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HOIPOIMIX_ITEM_MAKE_RES)			// ¾ÆÀÌÅÛ ¸¸µé±â
WORD				wResultCode;
BYTE				bySuccessResult;			// eITEM_MIX_RESULT_TYPE
HOBJECT				objHandle;
TBLIDX				recipeTblidx;
HOBJECT				itemHandle;
END_PROTOCOL()
//------------------------------------------------------------------			
BEGIN_PROTOCOL(GU_HOIPOIMIX_ITEM_MAKE_EP_RES)		// ¾ÆÀÌÅÛ ¸¸µé±â Áß EP ³Ö±â
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DYNAMIC_OBJECT_UPDATE_STATE)
HOBJECT				handle;
sDYNAMIC_OBJECT_BRIEF		dynamicObjBrief;
sDYNAMIC_OBJECT_STATE		dynamicObjState;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HOIPOIMIX_ITEM_MACHINE_DEL_RES)			// ¸Ó½Å ÇÊµå »èÁ¦
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HOIPOIMIX_ITEM_MAKE_EXP_NFY)
DWORD				dwCurExp;
BYTE				byCurLevel;
bool				bIsNormal; // recipe typeÀÌ eRECIPE_NORMAL ÀÎ°¡ ¾Æ´Ñ°¡.
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_TARGET_LOST_NFY)
HOBJECT						hSubject;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_TARGET_CHANGED)
HOBJECT						hSubject;
uint32						unknow;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_GUARD_CRASHED_NFY)
HOBJECT						hSubject;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_RP_BALL)
HOBJECT			handle;
BYTE			byCurRPBall;
bool			bDropByTime;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_RP_BALL_MAX)
HOBJECT			handle;
BYTE			byMaxRPBall;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HOIPOIMIX_JOB_SET_RES)
WORD				wResultCode;
HOBJECT				hNpchandle;
BYTE				byRecipeType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HOIPOIMIX_JOB_RESET_RES)
WORD				wResultCode;
HOBJECT				hNpchandle;
BYTE				byRecipeType;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_RP_INCREASE_START_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_RP_DECREASE_START_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_RP_INCREASE_STOP_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_HTB_LAST_STEP_CHANGED_NFY)
HOBJECT			hSubject;
BYTE			byLastStep;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_CHARGE_CANCELED_NFY)
HOBJECT			hSubject;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_REFRESH_LP_EP)
HOBJECT			hSubject;
WORD			wCurLp;
WORD			wMaxLp;
WORD			wCurEp;
WORD			wMaxEp;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_NONBATTLEACTIONPATTERNSET_UNITIDX_NFY)
HOBJECT				hBotHandle;
ACTIONPATTERN_FIELD unitIdx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_VEHICLE_START_NFY)//Correct for TW
HOBJECT				hDriverHandle;
TBLIDX				idFuelItemTblidx;
HOBJECT				hVehicleItem;
TBLIDX				idVehicleItemTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_VEHICLE_ENGINE_START_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_VEHICLE_ENGINE_START_NFY)
HOBJECT				hDriverHandle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_VEHICLE_ENGINE_STOP_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_VEHICLE_ENGINE_STOP_NFY)
HOBJECT				hDriverHandle;
DWORD				dwFuelRemain;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_VEHICLE_FUEL_UPDATE_NFY)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_VEHICLE_END_NFY)
HOBJECT				hDriverHandle;
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_VEHICLE_END_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_VEHICLE_STUNT_NFY)
HOBJECT			hDriverHandle;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SKILL_PASSIVE_EFFECT_APPLIED_NFY)
TBLIDX			skillTblidx;
BYTE			bySlotIndex;
sDBO_UPDATED_SKILL_DATA		sUpdatedSkillData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_AVATAR_UPDATED_SKILL_DATA_INFO)
TBLIDX			skillTblidx;
BYTE			bySlotIndex;
sDBO_UPDATED_SKILL_DATA		sUpdatedSkillData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MONSTER_TRANSFORMED_NFY)
HOBJECT			hSubject;
TBLIDX			newTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_CREATE_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_DELETE_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_FUNCTION_ADD_RES)
WORD				wResultCode;
BYTE				byFunction;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_BANK_HISTORY_RES)
WORD				wResultCode;
DWORD				dwBalance;
BYTE				byCount;
sDBO_DOJO_BANK_HISTORY_INFO asData[DBO_MAX_COUNT_DOJO_BANK_HISTORY];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOGI_CREATE_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOGI_CHANGE_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOGI_UPDATE_NFY)
HOBJECT				handle;
sDBO_DOGI_DATA		sData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_DOGI_CREATE_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GUILD_DOGI_CHANGE_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHILD_ADULT_SWITCHED_NFY)
HOBJECT				hSubject;
bool				bIsAdult;
WORD				wResultCode;
END_PROTOCOL()

//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHANGE_CLASS_AUTHORITY_CHANGED_NFY)
bool				bCanChangeClass;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PLAY_BGM)
bool				bPlay;
bool				bLoop;
DWORD				dwDelay;
BYTE				byLength;
char				szName[1];		// null À» Æ÷ÇÔÇØ¼­ º¸³½´Ù.
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_MARK_CHANGED_NFY)
TBLIDX				dojoTblidx;
GUILDID				guildId;
sDBO_GUILD_MARK		sMark;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_LEVEL_CHANGED_NFY)
TBLIDX				dojoTblidx;
BYTE				byLevel;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_NETP)
WORD				wResultCode;
NETP				netP;
NETP				dwBonusNetP;
NETP				dwAccumulationNetP;
DWORD				timeNextGainTime;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_SCRAMBLE_RES)			// µµÀåÀïÅ»Àü ½ÅÃ»¿¡ ´ëÇÑ ÀÀ´ä (µµÀüÀÚ)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_SCRAMBLE_RESPONSE_RES)
WORD				wResultCode;
WCHAR				wszGuildName[MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];
bool				bIsRetry; // true¸é ´Ù½Ã È®ÀÎÇØ¾ßÇÑ´Ù
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_NETMARBLEMEMBERIP_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUS_LOCATION_NFY)
HOBJECT				hSubject;
TBLIDX				busTblidx;
sVECTOR2			vCurLoc;
sVECTOR2			vCurDir;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUS_LOCATION_ERASED_NFY)
HOBJECT				hSubject;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_BUS_LOCATION_RESET_ALL_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_EXPIRED_NFY)
HOBJECT				hItem;
BYTE				byPlace;
BYTE				byPos;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_NETPYITEM_START_RES)
BYTE			byType; //	0: ±âº»  1:ÇÑÁ¤¼ö·® ÆÇ¸Å ÀÌº¥Æ® NPC 
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_NETPYITEM_BUY_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SHOP_NETPYITEM_END_RES)
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_REFRESH_BATTLE_ATTRIBUTE_MODIFIER)
HOBJECT				hSubject;
float				fHonestOffenceModifier;
float				fHonestDefenceModifier;
float				fStrangeOffenceModifier;
float				fStrangeDefenceModifier;
float				fWildOffenceModifier;
float				fWildDefenceModifier;
float				fEleganceOffenceModifier;
float				fEleganceDefenceModifier;
float				fFunnyOffenceModifier;
float				fFunnyDefenceModifier;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHAR_RANKBATTLE_ALLOW_NFY)
bool				bAllow;
WORD				wReasonCode;
END_PROTOCOL()
//------------------------------------------------------------------

BEGIN_PROTOCOL(GU_CHAR_RANKPOINT_RESET_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_NPC_INFO_RES)
WORD					wResultCode;
sDBO_DOJO_NPC_INFO		sData;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GAMEGUARD_AUTH_ANSWER_REQ)
BYTE				byDataSize;
BYTE				abyData[UCHAR_MAX];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_SEAL_ATTACK_BEGIN_NFY)
TBLIDX				sealObjectTblidx;
bool				bIsBeingStolen;
sVECTOR2			vLoc;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_SEAL_ATTACK_END_NFY)
TBLIDX				sealObjectTblidx;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_SEAL_CURRENT_STATE_NFY)
TBLIDX				sealObjectTblidx;
BYTE				byState;		// eTOBJECT_STATE_TYPE_C
sVECTOR2			vLoc;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_INVENTORY_CAPSULE_UNLOCK_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DOJO_SCRAMBLE_SHIFT_SEAL_STATE_NFY)
TBLIDX						dojoTblidx;
TBLIDX						objectTblidx;
GUILDID						guildId;
WCHAR						wszName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_LP_STATUS_NFY)
HOBJECT			handle;
bool			bEmergency;	// true: Emergency false: General
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DURATION_ITEM_BUY_RES)
TBLIDX				merchantTblidx;
BYTE				byPos;
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DURATION_RENEW_RES)
HOBJECT				hItemHandle;
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GMT_INFO_NFY)
BYTE					byGMTResetCount;
sGAME_MANIA_TIME_DATA	sCurrent;
sGAME_MANIA_TIME_DATA	sNext;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GMT_UPDATE_RES)
WORD				wResultCode;
sGAME_MANIA_TIME	sNext;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_GMT_CHANGED_NFY)
sGAME_MANIA_TIME	sCurrent;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_MAX_LP)
HOBJECT			hSubject;
WORD			wMaxLp;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_MAX_EP)
HOBJECT			hSubject;
WORD			wMaxEp;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_MAX_RP)
HOBJECT			hSubject;
WORD			wMaxRp;
END_PROTOCOL()

//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SERVER_CONTENTS_ONOFF)
BYTE		abyContentsBitFlag[7];
BYTE		abyQuestOnOffBitFlag[3];
BYTE		byNotSpawnNpcCount;
TBLIDX		atblNotSpawnNpcIndex[15];
BYTE		byNotLoadingHelpCount;
TBLIDX		atblNotLoadingHelpIndex[12];
DWORD		dwCCBDUse;
BYTE		unk[144];
END_PROTOCOL()
//------------------------------------------------------------------

//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SCOUTER_ACTIVATION_RES)//100%
HOBJECT			hTarget;
WORD			wResultCode;
DWORD			dwRetValue;
WORD			HITRATE;
WORD			DOGGERATE;
DWORD			powerLevel;
WORD			unk;
WORD			unk1;
WORD			unk2;
WORD			unk3;
DWORD			unk4;
DWORD			unk5;
DWORD			unk6;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHARTITLE_LIST_INFO)//Work 100%
BYTE			TitleFlagArray[64];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CHARTITLE_SELECT_NFY)//work 100%
DWORD			TitleID;
HOBJECT			handle;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CHARTITLE_SELECT_RES)//work 100%
WORD			wResultCode;
DWORD			TitleID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_UPDATE_CHAR_AP)//100%
HOBJECT			handle;
DWORD			dwCurAp;
DWORD			wBaseMaxAp;
DWORD			wLastMaxAp;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_UPGRADE_WORK_RES)//100%
WORD			ResultCode;
WORD            UpgradeResult;
BYTE            ItemPlace;
BYTE            ItemPos;
BYTE            Grade;
BYTE            StonePlace;
BYTE            StonePos;
BYTE            StoneStackCount;
BYTE            WhiteStonePlace;
BYTE            WhiteStonePos;
DWORD           WhiteStackCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_UPGRADE_BY_COUPON_RES)//Not Tested
WORD			ResultCode;
BYTE			ItemPlace;
BYTE			ItemPos;
BYTE			TicketPlace;
BYTE			TicketPos;
BYTE			Grade;
BYTE			TicketCount;
DBOTIME 		TimeStart;
DBOTIME		    TimeEnd;
BYTE			Unk;
BYTE			Unk2;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ULTIMATE_DUNGEON_ENTER_RES)//Correct struture for tw^^
BYTE			unk;//Maybe Dificulty???
WORD			wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_DROPITEM_INFO_RES)//100%
sITEM_DATA			ItemDropInfo;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_SOCKET_INSERT_BEAD_RES)//100%
WORD		wResultCode;
BYTE        ItemPlace;
BYTE        ItemPos;
WORD        BallID;
BYTE        unk[16];
WORD		DoggiEffectType;
DWORD		DoggiEffectValue;
WORD		DoggiEffectType1;
DWORD		DoggiEffectValue1;
BYTE        DogiballPlace;
BYTE        DoggiballPos;
BYTE        DoggiballCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_SOCKET_DESTROY_BEAD_RES)//100%
WORD		wResultCode;
BYTE        ItemPlace;
BYTE        ItemPos;
WORD        BallID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_CHANGE_OPTION_RES)//100%
WORD				wResultCode;
BYTE				ItemPlace;
BYTE				ItemPos;
DWORD				unk;
DWORD				unk1;
sITEM_EFFECT		aitemEffect[6];
sITEM_EXTRA_EFFECT	aitemExtraEffect[2];
BYTE				BoxPlace;
BYTE				BoxPos;
BYTE				ByCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_ITEM_CHANGE_BATTLE_ATTRIBUTE_RES)//not Tested
WORD		wResultCode;
BYTE		Place;
BYTE		Pos;
BYTE		AtributeID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MASCOT_INFO_EX)//100%
BYTE		 PetCount;
MascotInfo   pet[40];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MASCOT_SUMMON_EX_RES)//100%
WORD		ResultCode;
BYTE        PetSlot;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MASCOT_UNSUMMON_EX_RES)//100%
WORD		ResultCode;
BYTE        PetSlot;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MASCOT_DELETE_EX_RES)//100%
WORD		ResultCode;
BYTE        PetSlot;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MASCOT_SKILL_ADD_RES)//100%
WORD		ResultCode;
BYTE        PetSlot;
BYTE        SkillSlot;
TBLIDX      SkillID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_MASCOT_REGISTER_EX_NFY)//100%
DWORD          MascotID;//TBLIDX //Maybe Handle
DWORD           unk;
TBLIDX          MascotID1;//same TBLIDX 
DWORD           CurVp;
DWORD           MaxVp;
DWORD           EXP;
BYTE            SkillCount;
DWORD           Skill[4];
WORD            UNK1;//SlotID
END_PROTOCOL()
//------------------------------------------------------------------	
BEGIN_PROTOCOL(GU_HOIPOIMIX_ITEM_RECIPE_INFO)//100%
BYTE				TotalCount;
BYTE				UNK;
sRECIPE_DATA		RecipeData[200];
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CHANGED_CHAR_SIZE_NFY)//100%
HOBJECT			handle;
BYTE			size;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CHARTITLE_ADD)
WORD		ResultCode;
DWORD		TitleID;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_DRAGONBALL_SCRAMBLE_JOIN_RES)
WORD		ResultCode;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_EVENT_SCHEDULING_START)
WORD		ResultCode;
END_PROTOCOL()
// AUCTION HOUSE
BEGIN_PROTOCOL(GU_TENKAICHIDAISIJYOU_BUY_RES)
WORD		ResultCode;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_TENKAICHIDAISIJYOU_SELL_RES)
WORD		ResultCode;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_TENKAICHIDAISIJYOU_SELL_CANCEL_RES)
WORD		ResultCode;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_TENKAICHIDAISIJYOU_LIST_RES)
WORD		ResultCode;
HOBJECT     handle;
DWORD       unknown;
WORD        wUnknown;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_TENKAICHIDAISIJYOU_LIST_DATA)
DWORD				SellerHandle;
DWORD				ItemHandle;
DWORD				Unkonow;//Evry Tymes 0
BYTE				Unkonow1;//evry Times 3
BYTE				ItemType;
BYTE				ByLevel;
WCHAR				wszNameText[32 + 1];
WCHAR				sellerName[16 + 1];
DWORD				sellAmount;
//Add a comment to this line
BYTE				unkkkk[10];
WORD                Timer;
WORD                Timer1;
WORD                Timer2;
WORD                Timer3;
BYTE				dwunk2[6];//Time somewhere here
TBLIDX				itemTblidx;
BYTE				ByStackCount;
BYTE				unk;
BYTE				unk1;
BYTE				unk2;
BYTE				unk3;
BYTE				Rank;
BYTE				Grade;
BYTE				Durablity;
BYTE				test[35];//evry times 0
TBLIDX				aOptionTblidx;
TBLIDX				aOptionTblidx1;
sITEM_EFFECT		aitemEffect[6];
sITEM_EXTRA_EFFECT	aitemExtraEffect[2];
BYTE				unk8[9];
END_PROTOCOL()
// END AUCTION HOUSE

BEGIN_PROTOCOL(GU_ITEM_DISASSEMBLE_RES)
WORD ResultCode;
DWORD HItem;
DWORD HItem2;
DWORD HItem3;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_BOT_BOTCAUTION_HELPME_NFY)//Mob Ask for Help
HOBJECT			hBot;
bool			bIsRequester; // true : SOS¸¦ ¿äÃ»ÇÑ ÀÚ
END_PROTOCOL()

//------------------------------------------------------------------ 
//Cash
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_CASHITEM_START_RES)
WORD			wResultCode;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CASHITEM_INFO_RES)
WORD			wResultCode;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CASHITEM_END_RES)
WORD				wResultCode;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CASHITEM_MOVE_RES)//Correct size tw
WORD            wResultCode;
DWORD			Handle;
DWORD           dwProductId;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CASHITEM_USE_RES)
WORD				wResultCode;
DWORD				dwProductId;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CASHITEM_ADD_NFY)//correct tw
HOBJECT			handle;//Item Handle
sCASHITEM_BRIEF	sInfo;
BYTE			unk1[9];
WORD            Year;
BYTE            Moch;
BYTE            Day;
BYTE            Hour;
BYTE            Minute;
BYTE            Secound;
BYTE            unk2;
WCHAR			awchName[16 + 1];
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CASHITEM_DEL_NFY)//not sure but size correct
DWORD	        handle;
DWORD           dwProductId;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CASHITEM_HLSHOP_START_RES)//correct tw
WORD				wResultCode;
DWORD				dwRemainAmount;							// ÇöÀçÀÜ¾×
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CASHITEM_HLSHOP_END_RES)//correct tw
WORD				wResultCode;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_CASHITEM_BUY_RES)//correct tw
WORD            wResultCode;
DWORD			curCash; //Update total cash in cart
END_PROTOCOL()


BEGIN_PROTOCOL(GU_CASHITEM_INFO)
BYTE            TotalCount;
sCASHITEM_INFO  CashInfo[200];
END_PROTOCOL()
BEGIN_PROTOCOL(GU_WAGUWAGUMACHINE_COIN_INFO)
WORD				WagguCoin;
END_PROTOCOL()
//------------------------------------------------------------------ 
//Gift Shop
//------------------------------------------------------------------ 
struct GifItemProfile
{
	DWORD	ItemID;
	DWORD	Price;
};
BEGIN_PROTOCOL(GU_GIFT_SHOP_START_RES)
WORD        wResultCode;
DWORD	    WpPoit;
DWORD	    unknown;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_GIFT_SHOP_TAB_INFO_NFY)
BYTE			TabID;
BYTE			TotalItemCount;
WCHAR           TabName[16 + 1];
GifItemProfile  ItemProfile[72];
END_PROTOCOL()
BEGIN_PROTOCOL(GU_GIFT_SHOP_BUY_RES)
WORD			wResultCode;
DWORD			WpPoit;
END_PROTOCOL()
//------------------------------------------------------------------ 
//Quick Teleport Item
//------------------------------------------------------------------
struct QuickTeleportInfo
{
	BYTE    TeleportID;
	DWORD   WorldID;
	float   Loc[3];
	WORD    Year;
	BYTE    Moch;
	BYTE    Day;
	BYTE    Hour;
	BYTE    Minute;
	BYTE    Secound;
	BYTE    unk2; //NotKnow
	DWORD	MapTBLIDX;//Map Zone

};
BEGIN_PROTOCOL(GU_QUICK_TELEPORT_LOAD_RES)
WORD	wResultCode;
BYTE    BeginCount;
QuickTeleportInfo TeleportInfo[10];
END_PROTOCOL()
BEGIN_PROTOCOL(GU_QUICK_TELEPORT_UPDATE_RES)
WORD	wResultCode;
QuickTeleportInfo TeleportInfo;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_QUICK_TELEPORT_DEL_RES)
WORD	wResultCode;
QuickTeleportInfo TeleportInfo;
END_PROTOCOL()
BEGIN_PROTOCOL(GU_QUICK_TELEPORT_USE_RES)
WORD	wResultCode;
BYTE    TeleportID;
END_PROTOCOL()
//------------------------------------------------------------------
//Bot Check
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_SCS_CHECK_START_REQ)//Start the Request should got Time in
BYTE			byType;
WORD			wResultCode;
BYTE			UNK[20];
END_PROTOCOL()
BEGIN_PROTOCOL(GU_SCS_CHECK_REQ)//Start The Confirmation should open the Windows
BYTE			byType;
BYTE			unk[130];
END_PROTOCOL()
BEGIN_PROTOCOL(GU_SCS_REPLY_RES)
BYTE			unk[130];
END_PROTOCOL()
BEGIN_PROTOCOL(UG_SCS_REMAKE_REQ)
BYTE			byType;
WORD			wResultCode;
END_PROTOCOL()

BEGIN_PROTOCOL(GU_WORLD_FREE_PVP_ZONE_ENTERED_NFY)
unsigned int handle;
END_PROTOCOL()

BEGIN_PROTOCOL(GU_WORLD_FREE_PVP_ZONE_LEFT_NFY)
unsigned int handle;
END_PROTOCOL()


//To check in future those packet are not in game anymore
//------------------------------------------------------------------
/*BEGIN_PROTOCOL(GU_CHAR_MARKING_NFY)
HOBJECT			handle;
sMARKING		sMarking;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHARM_DICE_START_NFY)
DWORD			dwWaitTick;		//ms
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHARM_DICE_ROLLED_NFY)
HOBJECT			handle;	// ÇØ´ç Ä³¸¯ÅÍ ÇÚµé
DWORD			dwRet;	// °á°ú°ª
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHARM_DICE_ROLLED_RES)
DWORD			dwRet;	// °á°ú°ª
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_CHARM_DICE_END_NFY)
bool			bIsSuccess;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_ITEM_RANK_SET_RES)
WORD			wResultCode;
BYTE			byItemRank; // eITEM_RANK
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_ITEM_RANK_SET_NFY)
BYTE			byItemRank; // eITEM_RANK
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_LOCK_NFY)
bool				bIsOpen;	// 1: Open 0:Close
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_LOCK_RES)
WORD				wResultCode;
bool				bIsOpen;	// 1: Open 0:Close
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_RESET_RES)
WORD				wResultCode;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_RESET_NFY)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_ACCEPTED_RES)
BYTE				byItemSlot;	// ÆÄÆ¼ÀÎº¥ ÇØ´ç ½½·Ô ¾ÆÀÌÅÛ ³«Âû
WORD				wResultCode;
HOBJECT				hTarget;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_ACCEPTED_NFY)
BYTE				byItemSlot;	// ÆÄÆ¼ÀÎº¥ ÇØ´ç ½½·Ô ¾ÆÀÌÅÛ ³«Âû
HOBJECT				hTarget;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_GIVE_RES)
WORD				wResultCode;
BYTE				byItemSlot;		// ÆÄÆ¼ÀÎº¥ ÇØ´ç ½½·Ô ¾ÆÀÌÅÛ
HOBJECT				hTarget;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_GIVE_NFY)
BYTE				byItemSlot;		// ÆÄÆ¼ÀÎº¥ ÇØ´ç ½½·Ô ¾ÆÀÌÅÛ
HOBJECT				hTarget;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_DICE_START_RES)
WORD				wResultCode;
BYTE				byItemSlot;		// ÆÄÆ¼ÀÎº¥ ÇØ´ç ½½·Ô ¾ÆÀÌÅÛ
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_DICE_START_NFY)
BYTE				byItemSlot;		// ÆÄÆ¼ÀÎº¥ ÇØ´ç ½½·Ô ¾ÆÀÌÅÛ
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_DICE_ROLL_RES)
WORD				wResultCode;
BYTE				byRet;		// ÁÖ»çÀ§°á°úÀü¼Û
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_DICE_ROLL_NFY)
HOBJECT				handle;			// ÁÖ»çÀ§ÁÖÃ¼
BYTE				byRet;			// ÁÖ»çÀ§°á°úÀü¼Û
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(GU_PARTY_INVEN_DICE_END_NFY)
HOBJECT				hTarget;
END_PROTOCOL()*/
#pragma pack(pop)
#endif