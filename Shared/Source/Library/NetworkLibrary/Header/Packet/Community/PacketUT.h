#pragma once

#include <Define.h>
#include <SharedDef.h>
#include <SharedType.h>
#include <Opcodes.h>
#include <TableAll.h>


//------------------------------------------------------------------
//
//------------------------------------------------------------------
const char * NtlGetPacketName_UT(WORD wOpCode);
//------------------------------------------------------------------


#pragma pack(1)

//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_ENTER_CHAT)
    ACCOUNTID			accountId;
	BYTE				abyAuthKey[MAX_SIZE_AUTH_KEY];
	DWORD               dwUnk;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_CHAT_MESSAGE_SAY)
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_CHAT_MESSAGE_SHOUT)
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
	END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_CHAT_MESSAGE_FIND_PARTY)
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_CHAT_MESSAGE_TRADE)
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_CHAT_MESSAGE_WHISPER)
	WCHAR				awchReceiverCharName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
	//- yoshiki : I don't remember why "dwTellMessageID" was needed before.
//	DWORD				dwTellMessageID;
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_CHAT_MESSAGE_PARTY)
	BYTE				byChattingType;		// eDBO_CHATTING_TYPE
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_CHAT_MESSAGE_GUILD)
	BYTE				byChattingType;		// eDBO_CHATTING_TYPE
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_GUILD_DISBAND_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_GUILD_DISBAND_CANCEL_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_GUILD_RESPONSE_INVITATION)
	BYTE				byResponse;		// eINVITATION_RESPONSE
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_GUILD_LEAVE_REQ)
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_GUILD_KICK_OUT_REQ)
	CHARACTERID			targetMemberCharId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_GUILD_APPOINT_SECOND_MASTER_REQ)
	CHARACTERID			targetMemberCharId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_GUILD_DISMISS_SECOND_MASTER_REQ)
	CHARACTERID			targetMemberCharId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_GUILD_CHANGE_GUILD_MASTER_REQ)
	CHARACTERID			targetMemberCharId;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_CHAT_MESSAGE_PRIVATESHOP_BUSINESS)
	WCHAR				awchReceiverCharName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
	//- yoshiki : I don't remember why "dwTellMessageID" was needed before.
	//	DWORD				dwTellMessageID;
	WORD				wMessageLengthInUnicode;
	WCHAR				awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_FRIEND_ADD_REQ)	// 친구 추가
	WCHAR				wchName[MAX_SIZE_CHAR_NAME_UNICODE + 1];	
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_FRIEND_DEL_REQ)	// 친구 삭제
	CHARACTERID			targetID;
	WCHAR				wchName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_FRIEND_MOVE_REQ)	// 친구 -> 블랙리스트로 이동
	CHARACTERID			targetID;
	WCHAR				wchName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( UT_FRIEND_BLACK_ADD_REQ )	// 친구 블랙 리스트 추가
	WCHAR				awchName[MAX_SIZE_CHAR_NAME_UNICODE + 1];	
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( UT_FRIEND_BLACK_DEL_REQ )	// 친구 블랙 리스트 삭제
	CHARACTERID			targetID;
	WCHAR				awchName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_RANKBATTLE_RANK_LIST_REQ)
	DWORD				dwPage;
	BYTE				byCompareDay;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_RANKBATTLE_RANK_FIND_CHARACTER_REQ)
	DWORD				dwPage;
	BYTE				byCompareDay;

	WCHAR				wszCharName[MAX_SIZE_CHAR_NAME_UNICODE + 1];// 찾을 character
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_RANKBATTLE_RANK_COMPARE_DAY_REQ)
	DWORD				dwPage;
	BYTE				byCompareDay;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_GUILD_CHANGE_NOTICE_REQ)
	WORD				wNoticeLengthInUnicode;	
	WCHAR				awchNotice[MAX_LENGTH_OF_GUILD_NOTICE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_TMQ_RECORD_LIST_REQ)
	TBLIDX						tmqTblidx;
	BYTE						byDifficult;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_TMQ_MEMBER_LIST_REQ)
	TBLIDX						tmqTblidx;
	BYTE						byDifficult;
	BYTE						byRank;		// 0 : Best 1~5: 현재랭킹
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_BUDOKAI_TOURNAMENT_INDIVIDUAL_LIST_REQ)
	// 초기값 : INVALID_BYTE - 본선 진출자들의 JoinId를 같이 전송
	// 클라이언트에 저장하고 있는 리스트(경기 정보)의 갯수
	BYTE						byReceivedListCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_BUDOKAI_TOURNAMENT_INDIVIDUAL_INFO_REQ)
	WORD						awJoinId[2];
END_PROTOCOL()
//------------------------------------------------------------------
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_BUDOKAI_TOURNAMENT_TEAM_LIST_REQ)
	// 초기값 : INVALID_BYTE - 본선 진출자들의 JoinId를 같이 전송
	// 클라이언트에 저장하고 있는 리스트(경기 정보)의 갯수
	BYTE						byReceivedListCount;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_BUDOKAI_TOURNAMENT_TEAM_INFO_REQ)
	WORD						awJoinId[2];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( UT_PETITION_CHAT_START_RES )
	//PETITIONID					petitionID;
	WORD						wResultCode;
	ACCOUNTID					gmAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( UT_PETITION_CHAT_USER_SAY_REQ )
	//PETITIONID					petitionID;
	ACCOUNTID					gmAccountID;
	WORD						wMessageLengthInUnicode;
	WCHAR						awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( UT_PETITION_CHAT_USER_END_NFY )
	ACCOUNTID					gmAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( UT_PETITION_CHAT_GM_SAY_RES )
	WORD						wResultCode;
	ACCOUNTID					gmAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( UT_PETITION_USER_INSERT_REQ )
	WCHAR						awchUserCharName[MAX_SIZE_CHAR_NAME_UNICODE+ 1];
	WCHAR						awchQuestionContent[MAX_SIZE_QUESTION_CONTENT_UNICODE + 1];
	PETITIONCATEGORY			nCategory1;//ePETITIONSYSTEM_CATEGORY_1
	PETITIONCATEGORY			nCategory2;//ePETITIONSYSTEM_CATEGORY_2
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( UT_PETITION_CONTENT_MODIFY_REQ )
	PETITIONID					petitionID;
	WCHAR						awchQuestionContent[MAX_SIZE_QUESTION_CONTENT_UNICODE + 1];
	PETITIONCATEGORY			nCategory1;//ePETITIONSYSTEM_CATEGORY_1
	PETITIONCATEGORY			nCategory2;//ePETITIONSYSTEM_CATEGORY_2
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( UT_PETITION_SATISFACTION_NFY )
	PETITIONID					petitionID;
	ACCOUNTID					gmAccountID;
	BYTE						bySatisfactionRate;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL( UT_PETITION_USER_CANCEL_REQ )
	PETITIONID					petitionID;
	ACCOUNTID					gmAccountID;
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_DOJO_BUDOKAI_SEED_ADD_REQ)
	WCHAR				wszCharName[MAX_SIZE_CHAR_NAME_UNICODE + 1];// 등록할 character
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_DOJO_BUDOKAI_SEED_DEL_REQ)	
	WCHAR				wszCharName[MAX_SIZE_CHAR_NAME_UNICODE + 1];// 삭제할 character
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_DOJO_NOTICE_CHANGE_REQ)
	WORD				wNoticeLengthInUnicode;	
	WCHAR				awchNotice[MAX_LENGTH_OF_GUILD_NOTICE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_CHAT_USER_ON_CHANNEL_UPDATE_NFY)
	//WORD				wMessageLengthInUnicode;
	//WCHAR				awchMessage[MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE + 1];
END_PROTOCOL()
//------------------------------------------------------------------
BEGIN_PROTOCOL(UT_HLS_SLOT_MACHINE_INFO_REQ)
BYTE TabType;//0 Waggu 1 Event
BYTE   unk;
END_PROTOCOL()
BEGIN_PROTOCOL(UT_HLS_SLOT_MACHINE_EXTRACT_REQ)
BYTE MachineID;
BYTE   unk;
BYTE   PlayTimes;
END_PROTOCOL()
BEGIN_PROTOCOL(UT_HLS_SLOT_MACHINE_WINNER_INFO_REQ)
BYTE MachineID;
BYTE unk;
END_PROTOCOL()
//------------------------------------------------------------------
#pragma pack()
