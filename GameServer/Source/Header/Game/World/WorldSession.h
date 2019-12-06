#ifndef __WORLDSESSION_H
#define __WORLDSESSION_H

#include <Define.h>

#include <SharedDef.h>
#include <SharedType.h>

#include <deque>
#include <mutex>
#include <memory>

#include "NtlTSCoreDefine.h" //quitar

enum AccountTypes
{
	PLAYER = 0,
	GAME_MASTER
};



enum eCHARSTATE;
enum ResultCodes;
enum eREWARD_CONTAINER_TYPE;
enum eZENNY_CHANGE_TYPE;

union uSTOC_EVT_DATA;

struct sITEM_PROFILE;
struct sUG_TS_CONFIRM_STEP_REQ;
struct sQUEST_REWARD_TBLDAT;
struct sUG_TS_EXCUTE_TRIGGER_OBJECT;
struct QuestData;

class Packet;
class GameSocket;
class Player;
class CDboTSContStart;
class CDboTSContGAct;
class CDboTSContGCond;
class CDboTSContReward;
class CDboTSActSToCEvt;
class CDboTSContEnd;


class WorldSession
{
public:
	WorldSession(uint32 id, GameSocket* sock, AccountTypes sec);
	~WorldSession();
	void			SendPacket(char* packet, size_t size);

	AccountTypes	GetSecurity() const { return _security; }
	uint32			GetAccountId() const { return _accountId; }
	void			SetSecurity(AccountTypes security) { _security = security; }
	const			std::string &GetRemoteAddress() const;
	void			QueuePacket(std::unique_ptr<Packet> new_packet);
	bool			Update();
	void			LogoutPlayer(bool save);
	void			KickPlayer();
	bool			CreatePlayer(CHARACTERID id);
	// PACKET
	void			PacketParser(Packet& packet);
	// PACKET PROCESS
	void			SendAvatarCharInfo();
	void			SendAvatarSkillInfo();
	void			SendUpdateSkillPassiveAtribute();
	void			SendUpdateSkillPassiveAtributeByID(TBLIDX SkillID, bool isRemove);
	void			SendAvatarItemInfo();
	void			SendAvatarBuffInfo();
	void			SendAvatarHTBInfo();
	void			SendPortalInfo();
	void			SendAvatarTitleInfo();
	void			SendMascotInfo();
	void			SendHoiPoiMixInfo();//Craft list
	void			SendSlotInfo();
	void			SendAvatarInfoEnd();
	void			SendAvatarWagguInfo();
	void			SendAvatarItemCashInfo();
	void			SendAvatarWarFogInfo();
	void			SendNetMarbleMemberShipNfy();
	void			SendWorldEnter();
	void			SendEnterWorldComplete();
	void			SendGameLeave(Packet& packet, bool moveToChar = false);
	void			SendGameExit(Packet& packet);
	void			SendShopRequest(Packet& packet, bool enter);
	void			SendTargetSelection(HOBJECT hTarget);
	// move
	void			SendCharMoveSync(Packet &packet);
	void			SendCharMove(Packet& packet);
	void			SendCharJump(Packet& packet);
	void			SendCharJumpEnd(Packet& packet);
	void			SendCharToggleSitDown(Packet& packet);
	void			SendCharHeadChanging(Packet& packet);
	void			SendCharDestLoc(Packet& packet);
	void			SendCharFollowMove(Packet& packet);
	void			SendCharSyncFollow(Packet& packet);
	void			SendAirJumpMove(Packet& packet);
	void			SendAirJMove(Packet& packet);
	void			SendAirDashMove(Packet& packet);
	void			SendAirFalling(Packet& packet);
	void			SendAirEnd(Packet& packet);
	// portal
	void			SendPortalTeleport(Packet& packet);
	void			SendAddPortal(Packet& packet);
	void			SendEnterWorldTeleport();
	//Dangeon Teleport
	void			SendDangeonTeleport(HOBJECT	handle, WORD Dificulty);
	// warfog
	void			SendFogOfWarRes(Packet& packet);
	// quick slot
	void			SendUpdateQuickSlots(Packet& packet);
	void			SendRemoveQuickSlots(Packet& packet);
	// inventory
	void			SendItemMove(Packet& packet);
	void			SendItemMoveStack(Packet& packet);
	void			SendRemoveItem(Packet& packet);
	void			SendItemCreate(sITEM_PROFILE *createdItem);

	void			SendPickUp(HOBJECT handle);

	void			SendUpdateCharZenny(DWORD amount, eZENNY_CHANGE_TYPE zennyType, HOBJECT handle, bool bIsNew);
	void			SendUpdateCharExp(DWORD expAmount, DWORD bonus, HOBJECT handle, DWORD curExp);
	// SHOP
	void			SendShopBuy(Packet& packet);
	void			SendShopEventBuy(Packet& packet);
	void			SendShopItemChange(Packet& packet);
	void			SendShopSell(Packet& packet);
	//HLS Shop
	void			SendHLSShopStart(Packet& packet);
	void			SendHLSShopEnd(Packet& packet);
	//Cash Shop
	void			SendCashItemStart(Packet& packet);
	void			SendCashItemBuy(Packet& packet);
	void			SendCashItemMove(Packet& packet);
	void			SendCashItemEnd(Packet& packet);
	//Token Shop
	void			SendNetPyStart(Packet& packet);
	void			SendNetPyBuy(Packet& packet);
	void			SendNetPyEnd(Packet& packet);
	//HoiPoiMix
	void			SendHoiPoiMixCreate(Packet& packet);
	// AutoAttck
	void			SendToggleAutoAttack(bool val);
	//Skills
	void			HandleUseSkill(Packet& packet);
	void			UseSkill(Packet& packet);
	void			LearnSkill(TBLIDX id);
	void			RewardSkill(TBLIDX id);
	void			LearnMestrySkill(TBLIDX id);
	void			UpgradeSkill(Packet& packet);
	void			ResetSkill(Packet& packet);
	//Budokay

	//Events
	void			SendDragonBallsCheck(Packet& packet);
	void			SendShenlongReward(Packet& packet);
	//Guilds
	void			SendGuildCreateReq(Packet& packet);
	// command
	void			ExecuteServerCommand(Packet& packet);
	// social
	void			SendSocialSkill(Packet& packet);
	// teleport
	void			SendCharTeleportRes(Packet& packet);
	// condition
	void			SendUpdateCharCondition(DWORD conditionFlag);
	// Quest Handle
	void			SendQuestAcept(Packet& packet);
	void			GetQuestInfo(DWORD QuestID, DWORD tcCurId, DWORD tcNextId);
	void			GetQuestPortalInfo(DWORD QuestID, DWORD tcCurId, DWORD tcNextId);	
	void			SendQuestCompleteInfo();
	void			SendQuestProgressInfo();
	void			SendQuestInventoryInfo();
	void			SendQuestGiveUp(Packet& packet);
	void			SendQuestItemCreate(BYTE pos, TBLIDX itemTblidx, BYTE count);
	void			SendQuestItemDelete(Packet& packet);
	void			SendQuestItemDeleteNfy(BYTE pos);
	void			SendQuestItemMove(Packet& packet);
	void			SendQuestItemUpdateNfy(BYTE pos, BYTE count);
	HOBJECT			SpawnMobForQuest(TBLIDX mobTblidx);
	HOBJECT			SpawnNPCForQuest(TBLIDX NPCTblidx);
	ResultCodes		GivePlayerQuestReward(TBLIDX tblidx, eREWARD_CONTAINER_TYPE rewardContType, DWORD dwParam);
	ResultCodes		GivePlayerItemReward(sQUEST_REWARD_TBLDAT* rewardTbl, DWORD dwParam);
	ResultCodes		CheckEvtDataType(CDboTSActSToCEvt* sToCEvt, NTL_TS_TC_ID tcId);
	// TS Quest
	ResultCodes		FindQuestInformation(sUG_TS_CONFIRM_STEP_REQ * req);
	ResultCodes		ProcessTSContStart(CDboTSContStart * contStart);
	ResultCodes		ProcessTsContGAct(CDboTSContGAct * contGAct, NTL_TS_T_ID tid, NTL_TS_TC_ID tcId);
	ResultCodes		ProcessTsContGCond(CDboTSContGCond * contGCond);
	ResultCodes		ProcessTsContReward(CDboTSContReward * contReward, DWORD dwParam);
	void			ProcessTsContEnd(CDboTSContEnd * contEnd);
	void			SendQuestSVRevtStartNotify(NTL_TS_T_ID tid, NTL_TS_TC_ID tcId, NTL_TS_TA_ID taId);
	void			SendQuestSVRevtUpdateNotify(NTL_TS_T_ID tid, NTL_TS_TC_ID tcId, NTL_TS_TA_ID taId, BYTE svrEvtType, BYTE slot, uSTOC_EVT_DATA*evtData);
	void			SendQuestSVRevtEndNotify(NTL_TS_T_ID tid, NTL_TS_TC_ID tcId, NTL_TS_TA_ID taId);
	//Trigger
	void			SendTsExcuteTriggerObject(Packet& packet);
	ResultCodes		FindObjectTriggerInformation(QuestData* questData, HOBJECT hTarget, TBLIDX objTblidx);
	//RankBatle
	void			GetPlayerFromRankList();
	
	
private:
	GameSocket * const m_Socket;                       // socket pointer is owned by the network thread which created 
	AccountTypes	_security;
	uint32			_accountId;

	std::mutex		m_recvQueueLock;
	std::deque<std::unique_ptr<Packet>> m_recvQueue;	
	bool			requestToLogout;
	/*	 PLAYER INFO	*/
	Player*			_player;
	/*		END			*/
};
#endif
/// @}
