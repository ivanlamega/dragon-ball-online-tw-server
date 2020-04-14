#include <Game\Object\Manager\Attributes.h>
#include <Game\Object\Player.h>
#include <Game\Object\Object.h>
#include <WorldSession.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <Packet\Game\PacketGU.h>

//----------------------------------------
//	Constructor
//----------------------------------------
AttributesManager::AttributesManager()
{
	RPCounter = 0;
	RPFilledCounter = 0;
	//sPawnMobQuest = false;
	plr = nullptr;
	//memset(&growUpInfo, 0, sizeof(growUpInfo));
	//memset(&tlq1Info, 0, sizeof(tlq1Info));
	//memset(&QuestDat, 0, sizeof(QuestDat));
	//memset(&PlayerProfile.avatarAttribute, 0, sizeof(sAVATAR_ATTRIBUTE));
}
//----------------------------------------
//	Destructor
//----------------------------------------
AttributesManager::~AttributesManager()
{
	// release name as it as been malloc by chartowchar
	memset(PlayerProfile.awchName, 0, MAX_SIZE_USERID_UNICODE + 1);
	plr = nullptr;
	changedFlag.Destroy();
}
//----------------------------------------
//	Get number of empty RP ball
//----------------------------------------
int AttributesManager::GetNumRpBall()
{
	return RPCounter;
}
//----------------------------------------
//	Get number of full rp ball
//----------------------------------------
int AttributesManager::GetNumFilledRpBall()
{
	return RPFilledCounter;
}
//----------------------------------------
//	Fill (1) or Unfill (-1) the current amount of RP ball
//----------------------------------------
void AttributesManager::SetNumFilledRpBall(int newBall)
{
	RPFilledCounter += newBall;
}
//----------------------------------------
//	Get each RP ball do we have
//----------------------------------------
void AttributesManager::SetRPBall()
{
	RPCounter = CalculateRPBallMaxByLevel(PlayerProfile.byLevel);
}
//----------------------------------------
//	Get each RP ball do we have and send it to our client
//----------------------------------------
void AttributesManager::SendRpBallInformation()
{
	sGU_UPDATE_CHAR_RP_BALL_MAX maxBall;
	sGU_UPDATE_CHAR_RP_BALL ball;

	RPCounter = CalculateRPBallMaxByLevel(PlayerProfile.byLevel);

	maxBall.wPacketSize = sizeof(sGU_UPDATE_CHAR_RP_BALL_MAX) - 2;
	maxBall.byMaxRPBall = RPCounter;
	maxBall.handle = plr->GetHandle();
	maxBall.wOpCode = GU_UPDATE_CHAR_RP_BALL_MAX;

	ball.wPacketSize = sizeof(sGU_UPDATE_CHAR_RP_BALL) - 2;
	ball.bDropByTime = true;
	ball.byCurRPBall = static_cast<BYTE>(RPCounter);
	ball.handle = plr->GetHandle();
	ball.wOpCode = GU_UPDATE_CHAR_RP_BALL;

	plr->SendPacket((char*)&maxBall, sizeof(sGU_UPDATE_CHAR_RP_BALL_MAX));
	plr->SendPacket((char*)&ball, sizeof(sGU_UPDATE_CHAR_RP_BALL));
}
void AttributesManager::UpdateLevelUpAtributes()
{
	sPC_TBLDAT *pTblData = (sPC_TBLDAT*)sTBM.GetPcTable()->GetPcTbldat(plr->GetAttributesManager()->PlayerRaceID, plr->GetAttributesManager()->PlayerRaceID, plr->GetAttributesManager()->PlayerGanderID);
	if (pTblData != NULL)
	{

		int baseStr = CalculeBasicStats(pTblData->byStr, pTblData->fLevel_Up_Str, PlayerProfile.byLevel);
		int baseCon = CalculeBasicStats(pTblData->byCon, pTblData->fLevel_Up_Con, PlayerProfile.byLevel);
		int baseFoc = CalculeBasicStats(pTblData->byFoc, pTblData->fLevel_Up_Foc, PlayerProfile.byLevel);
		int baseDex = CalculeBasicStats(pTblData->byDex, pTblData->fLevel_Up_Dex, PlayerProfile.byLevel);
		int baseSol = CalculeBasicStats(pTblData->bySol, pTblData->fLevel_Up_Sol, PlayerProfile.byLevel);
		int baseEng = CalculeBasicStats(pTblData->byEng, pTblData->fLevel_Up_Eng, PlayerProfile.byLevel);


		plr->GetAttributesManager()->UpdateStr(INVALID_SYSTEM_EFFECT_CODE, baseStr, false, false);
		plr->GetAttributesManager()->UpdateCon(INVALID_SYSTEM_EFFECT_CODE, baseCon, false, false);
		plr->GetAttributesManager()->UpdateFoc(INVALID_SYSTEM_EFFECT_CODE, baseFoc, false, false);
		plr->GetAttributesManager()->UpdateDex(INVALID_SYSTEM_EFFECT_CODE, baseDex, false, false);
		plr->GetAttributesManager()->UpdateSol(INVALID_SYSTEM_EFFECT_CODE, baseSol, false, false);
		plr->GetAttributesManager()->UpdateEng(INVALID_SYSTEM_EFFECT_CODE, baseEng, false, false);

		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.byBaseStr = baseStr;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.byBaseCon = baseCon;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.byBaseFoc = baseFoc;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.byBaseDex = baseDex;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.byBaseSol = baseSol;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.byBaseEng = baseEng;

		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wBasePhysicalOffence = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wLastPhysicalOffence;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wBaseMaxLP = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wLastMaxLP;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wBaseBlockRate = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wLastBlockRate;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wBaseEnergyOffence = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wLastEnergyOffence;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wBaseEnergyCriticalRate = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wLastEnergyCriticalRate;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wBaseAttackRate = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wLastAttackRate;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.fBaseEnergyCriticalRange = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.fLastEnergyCriticalRange;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wBasePhysicalCriticalRate = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wLastPhysicalCriticalRate;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wBaseDodgeRate = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wLastDodgeRate;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.fBasePhysicalCriticalRange = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.fLastPhysicalCriticalRange;
		plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wBaseMaxEP = plr->GetAttributesManager()->PlayerProfile.avatarAttribute.wLastMaxEP;


		/*plr->GetAttributesManager()->SetLastStr(baseStr);
		plr->GetAttributesManager()->SetLastCon(baseCon);
		plr->GetAttributesManager()->SetLastFoc(baseFoc);
		plr->GetAttributesManager()->SetLastDex(baseDex);
		plr->GetAttributesManager()->SetLastSol(baseSol);
		plr->GetAttributesManager()->SetLastEng(baseEng);
	
		// LP Calculation
		DWORD LP = CalculeLP(plr->GetMyClass(), baseCon);

		//EP Calculation
		WORD EP = CalculeEP(plr->GetMyClass(), baseEng);
	
		plr->GetAttributesManager()->SetLastMaxLP(LP);
		plr->GetAttributesManager()->SetLastMaxEP(EP);

		//Calculation Physical Atack
		WORD PhysicalOffence = CalculePhysicalOffence(plr->GetMyClass(), PlayerProfile.byLevel, baseStr, baseDex);
		//Calculation Physical Critical Atack 
		WORD PhysicalCriticalRate = CalculePhysicalCriticalRate(plr->GetMyClass(), baseDex);

		plr->GetAttributesManager()->SetLastPhysicalOffence(PhysicalOffence);
		plr->GetAttributesManager()->SetLastPhysicalCriticalRate(PhysicalCriticalRate);

		//Calculation Energy offence
		WORD EnergyOffence = CalculeEnergyOffence(plr->GetMyClass(), PlayerProfile.byLevel, baseSol, baseFoc);
		//Calculation Energy Critical Atack
		WORD EnergyCriticalRate = CalculeEnergyCriticalRate(plr->GetMyClass(), baseFoc);

		plr->GetAttributesManager()->AddLastEnergyOffence(EnergyOffence);
		plr->GetAttributesManager()->SetLastEnergyCriticalRate(EnergyCriticalRate);

		WORD HitRate = CalculeHitRate(baseFoc);
	//DoggeRate Calculation
		WORD DodgeRate = CalculeDodgeRate(baseDex);
		// BlockRate calculation
		WORD BlockRate = CalculeBlockRate(baseDex, baseCon);

		plr->GetAttributesManager()->SetLastAttackRate(HitRate);
		plr->GetAttributesManager()->SetLastDodgeRate(DodgeRate);
		plr->GetAttributesManager()->SetLastBlockRate(BlockRate);

		WORD physicalCriticalDefenceRate = CalculePhysicalCriticalDefenceRate(PlayerProfile.avatarAttribute.byLastCon);
		WORD energyCriticalDefenceRate = CalculeEnergyCriticalDefenceRate(PlayerProfile.avatarAttribute.byLastEng);
		plr->GetAttributesManager()->SetPhysicalCriticalDefenceRate(physicalCriticalDefenceRate);
		plr->GetAttributesManager()->SetEnergyCriticalDefenceRate(energyCriticalDefenceRate);*/

	}
	

}
//----------------------------------------
//	Load all attributes and calculate stats from last database save
//----------------------------------------
bool AttributesManager::LoadAttributes(CHARACTERID _id, Player* _plr)
{
	charid = _id;
	plr = _plr;

	sql::ResultSet* result = sDB.executes("SELECT * FROM characters WHERE CharacterID = '%d';", charid);
	if (result == NULL)
	{ 
		delete result;
		return false;
	}
	if (result->rowsCount() <= 0)
	{
		delete result;
		return false;
	}
	PlayerClassID = result->getInt("ClassID");
	PlayerRaceID = result->getInt("RaceID");
	PlayerGanderID = result->getInt("GenderID");
	sPC_TBLDAT *pTblData = (sPC_TBLDAT*)sTBM.GetPcTable()->GetPcTbldat(result->getInt("RaceID"), result->getInt("ClassID"), result->getInt("GenderID"));
	if (pTblData == NULL)
	{
		delete result;
		sLog.outError("LoadAttributes: Error while loading 'PCTable' on account: %d", plr->GetSession()->GetAccountId());
		return false;
	}
	PlayerProfile.byLevel = static_cast<BYTE>(result->getInt("CurrentLevel"));
	sEXP_TBLDAT *pTblExp = (sEXP_TBLDAT*)sTBM.GetExpTable()->FindData(PlayerProfile.byLevel);
	if (pTblExp == NULL)
	{
		delete result;
		sLog.outError("LoadAttributes: Error while loading 'ExpTable' on account: %d", plr->GetSession()->GetAccountId());
		return false;
	}
	PlayerProfile.dwMaxExpInThisLevel = pTblExp->dwNeed_Exp;

	PlayerProfile.guildId = INVALID_GUILDID;
	PlayerProfile.byMaxLevel = 70;

	PlayerProfile.tblidx = pTblData->tblidx;
	PlayerProfile.bChangeClass = result->getBoolean("IsToChangeClass");
	PlayerProfile.bIsAdult = result->getBoolean("IsAdult");
	PlayerProfile.charId = result->getInt("CharacterID");
	wcscpy_s(PlayerProfile.awchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, charToWChar((result->getString("Name")).c_str()));
	plr->SetName((char*)result->getString("Name").c_str());
	//PC Shape
	PlayerProfile.sPcShape.byFace = static_cast<BYTE>(result->getInt("FaceID"));
	PlayerProfile.sPcShape.byHair = static_cast<BYTE>(result->getInt("HairID"));
	PlayerProfile.sPcShape.byHairColor = static_cast<BYTE>(result->getInt("HairColorID"));
	PlayerProfile.sPcShape.bySkinColor = static_cast<BYTE>(result->getInt("SkinColorID"));
	plr->SetMyClass((ePC_CLASS)result->getInt("ClassID"));
	//Other Infos
	PlayerProfile.dwCurExp = result->getInt("CurrentExp");
	PlayerProfile.dwZenny = result->getInt("ZennyInventory");
	PlayerProfile.dwTutorialHint = -1; // help frame
	PlayerProfile.byBindType = DBO_BIND_TYPE_INITIAL_LOCATION;
	//PlayerProfile.bindObjectTblidx = -1;

	PlayerProfile.dwReputation = result->getInt("Reputation");
	PlayerProfile.dwMudosaPoint = result->getInt("Mudosa");
	PlayerProfile.dwSpPoint = result->getInt("SkillPoints");
	PlayerProfile.bIsGameMaster = result->getBoolean("IsGameMaster");
	PlayerProfile.sMarking.dwCode = result->getInt("Title_Marking");
	PlayerProfile.sLocalize.WP_Point = result->getInt("WP_Point");// WP Poit mensage
	PlayerProfile.sLocalize.netp = result->getInt("Token");// Token Point correct value	
	PlayerProfile.sLocalize.IsVip = result->getInt("IsVip");// S icon Vip_Member Maybe
	cashpoit = result->getInt("CashPoint");
	WagguCoin = result->getInt("WagguCoin");
	EventCoin = result->getInt("EventCoin");
	PlayerProfile.sMixData.bNormalStart = 1;
	PlayerProfile.sMixData.bSpecialStart = 0;
	PlayerProfile.sMixData.byMixLevel = result->getInt("MixLevel");
	PlayerProfile.sMixData.bySpecialType = eRECIPE_TYPE::eRECIPE_INVALID;
	PlayerProfile.sMixData.dwMixExp = result->getInt("MixExp");

	
	PlayerProfile.byUnknow = 0;

	PlayerProfile.sLocalize.GiftCash = 0;// Notify if recive cash item from friend "mensage say gift not confirmed"
	PlayerProfile.sLocalize.unknown = 0;// Unknow TW
	
	PlayerProfile.sLocalize.unknown1 = 0;// Unknow TW
	PlayerProfile.sLocalize.unknown2 = 0;// Unknow TW
	PlayerProfile.sLocalize.unknown3 = 0;// Unknow TW
	PlayerProfile.sLocalize.unknown4 = 0;// Unknow TW
	PlayerProfile.sLocalize.unknown5 = INVALID_TBLIDX;// Unknow TW // Mascote Ex ?
	PlayerProfile.sLocalize.unknown6 = INVALID_TBLIDX;// Unknow TW // Mascote Ex ?
	PlayerProfile.sLocalize.unknown7 = 0;// Unknow TW
	
	PlayerProfile.sLocalize.type = 0;
	/*	FILL STATE	*/
	plr->Relocate(static_cast<float>(result->getDouble("Position_X")), static_cast<float>(result->getDouble("Position_Y")), static_cast<float>(result->getDouble("Position_Z")),
		static_cast<float>(result->getDouble("Direction_X")), static_cast<float>(result->getDouble("Direction_Y")), static_cast<float>(result->getDouble("Direction_Z")));
	plr->GetPosition(plr->GetState()->sCharStateBase.vCurLoc.x, plr->GetState()->sCharStateBase.vCurLoc.y, plr->GetState()->sCharStateBase.vCurLoc.z);
	plr->GetOriantation(plr->GetState()->sCharStateBase.vCurDir.x, plr->GetState()->sCharStateBase.vCurDir.y, plr->GetState()->sCharStateBase.vCurDir.z);
	plr->SetWorldID(result->getInt("WorldID"));
	plr->SetWorldTableID(result->getInt("WorldTableID"));
	plr->GetState()->sCharStateBase.byStateID = CHARSTATE_SPAWNING;
	plr->GetState()->sCharStateDetail.sCharStateSpawning.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_GAME_IN;
	plr->GetState()->sCharStateBase.dwConditionFlag = 0;
	plr->GetState()->sCharStateBase.dwStateTime = 0;
	plr->GetState()->sCharStateBase.vCurLoc = plr->GetState()->sCharStateBase.vCurLoc;
	plr->GetState()->sCharStateBase.vCurDir = plr->GetState()->sCharStateBase.vCurDir;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sGreatNamek.bySourceGrade = 255;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.bySourceGrade = 255;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sPureMajin.bySourceGrade = 255;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sSuperSaiyan.bySourceGrade = 255;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;

	plr->GetState()->sCharStateBase.isFighting = false;
	plr->GetState()->sCharStateBase.isFlying = plr->GetIsFlying();

	

	delete result;

	if (LoadCharacterAttrFromDB(pTblData) == false)
	{
		sLog.outError("LoadAttributes::LoadCharacterAttrFromDB Error while loading character: %d", charid);
		return false;
	}
	if (LoadAttributeFromDB() == false)
	{
		sLog.outError("LoadAttributes::LoadAttributeFromDB Error while loading character: %d", charid);
		return false;
	}
	

	SetRPBall();
	
	return true;
}
//----------------------------------------
//	Load the attributes
//----------------------------------------
bool AttributesManager::LoadAttributeFromDB()
{
	sql::ResultSet* result = sDB.executes("SELECT * FROM characters_attributes WHERE CharacterID = '%d';", charid);
	if (result == NULL)
	{
		delete result;
		return false;
	}
	if (result->rowsCount() <= 0)
	{
		delete result;
		return false;
	}
	memset(&PlayerProfile.avatarAttribute, 0, sizeof PlayerProfile.avatarAttribute);
	//Load All Attributes One time only - Luiz  IN ORDER --Kalisto
	//STR 
	PlayerProfile.avatarAttribute.byBaseStr = static_cast<WORD>(result->getInt("BaseStr"));
	PlayerProfile.avatarAttribute.byLastStr = static_cast<WORD>(result->getInt("LastStr"));
	//Constitucion
	PlayerProfile.avatarAttribute.byBaseCon = static_cast<WORD>(result->getInt("BaseCon"));
	PlayerProfile.avatarAttribute.byLastCon = static_cast<WORD>(result->getInt("LastCon"));
	//Focus
	PlayerProfile.avatarAttribute.byBaseFoc = static_cast<WORD>(result->getInt("BaseFoc"));
	PlayerProfile.avatarAttribute.byLastFoc = static_cast<WORD>(result->getInt("LastFoc"));
	//Dextry
	PlayerProfile.avatarAttribute.byBaseDex = static_cast<WORD>(result->getInt("BaseDex"));
	PlayerProfile.avatarAttribute.byLastDex = static_cast<WORD>(result->getInt("LastDex"));
	//Soul
	PlayerProfile.avatarAttribute.byBaseSol = static_cast<WORD>(result->getInt("BaseSol"));
	PlayerProfile.avatarAttribute.byLastSol = static_cast<WORD>(result->getInt("LastSol"));
	//Energy
	PlayerProfile.avatarAttribute.byBaseEng = static_cast<WORD>(result->getInt("BaseEng"));
	PlayerProfile.avatarAttribute.byLastEng = static_cast<WORD>(result->getInt("LastEng"));
	//EP/LP
	PlayerProfile.avatarAttribute.wBaseMaxLP = result->getInt("BaseMaxLP");
	PlayerProfile.avatarAttribute.wLastMaxLP = result->getInt("LastMaxLP");
	PlayerProfile.avatarAttribute.wBaseMaxEP = static_cast<WORD>(result->getInt("BaseMaxEP"));
	PlayerProfile.avatarAttribute.wLastMaxEP = static_cast<WORD>(result->getInt("LastMaxEP"));
	//Physical Atack
	PlayerProfile.avatarAttribute.wBasePhysicalOffence = static_cast<WORD>(result->getInt("BasePhysicalOffence"));
	PlayerProfile.avatarAttribute.wLastPhysicalOffence = static_cast<WORD>(result->getInt("LastPhysicalOffence"));
	//Physical Defese
	PlayerProfile.avatarAttribute.wBasePhysicalDefence = static_cast<WORD>(result->getInt("BasePhysicalDefence"));
	PlayerProfile.avatarAttribute.wLastPhysicalDefence = static_cast<WORD>(result->getInt("LastPhysicalDefence"));
	//Energy Atack
	PlayerProfile.avatarAttribute.wBaseEnergyOffence = static_cast<WORD>(result->getInt("BaseEnergyOffence"));
	PlayerProfile.avatarAttribute.wLastEnergyOffence = static_cast<WORD>(result->getInt("LastEnergyOffence"));
	//Energy Defese
	PlayerProfile.avatarAttribute.wBaseEnergyDefence = static_cast<WORD>(result->getInt("BaseEnergyDefence"));
	PlayerProfile.avatarAttribute.wLastEnergyDefence = static_cast<WORD>(result->getInt("LastEnergyDefence"));
	//Hit Rate
	PlayerProfile.avatarAttribute.wBaseAttackRate = static_cast<WORD>(result->getInt("BaseAttackRate"));
	PlayerProfile.avatarAttribute.wLastAttackRate = static_cast<WORD>(result->getInt("LastAttackRate"));
	//Dogge Rate
	PlayerProfile.avatarAttribute.wBaseDodgeRate = static_cast<WORD>(result->getInt("BaseDodgeRate"));
	PlayerProfile.avatarAttribute.wLastDodgeRate = static_cast<WORD>(result->getInt("LastDodgeRate"));
	//Physical Critical Rate
	PlayerProfile.avatarAttribute.wBasePhysicalCriticalRate = static_cast<WORD>(result->getInt("BasePhysicalCriticalRate"));
	PlayerProfile.avatarAttribute.wLastPhysicalCriticalRate = static_cast<WORD>(result->getInt("LastPhysicalCriticalRate"));
	//Energy Critical Rate
	PlayerProfile.avatarAttribute.wBaseEnergyCriticalRate = static_cast<WORD>(result->getInt("BaseEnergyCriticalRate"));
	PlayerProfile.avatarAttribute.wLastEnergyCriticalRate = static_cast<WORD>(result->getInt("LastEnergyCriticalRate"));
	//RP 
	PlayerProfile.avatarAttribute.wBaseMaxRP = static_cast<WORD>(result->getInt("BaseMaxRP"));
	PlayerProfile.avatarAttribute.wLastMaxRP = static_cast<WORD>(result->getInt("LastMaxRP"));
	//Block Rate 
	PlayerProfile.avatarAttribute.wBaseBlockRate = static_cast<WORD>(result->getInt("BaseBlockRate"));
	PlayerProfile.avatarAttribute.wLastBlockRate = static_cast<WORD>(result->getInt("LastBlockRate"));
	//Run Speed
	PlayerProfile.avatarAttribute.fLastRunSpeed = static_cast<WORD>(result->getDouble("LastRunSpeed"));
	//Atack Speed
	PlayerProfile.avatarAttribute.wBaseAttackSpeedRate = static_cast<WORD>(result->getDouble("BaseAttackSpeedRate"));
	PlayerProfile.avatarAttribute.wLastAttackSpeedRate = static_cast<WORD>(result->getDouble("LastAttackSpeedRate"));
	//Atack Range
	PlayerProfile.avatarAttribute.fLastAttackRange = (float)result->getDouble("LastAttackRange");
	PlayerProfile.avatarAttribute.fBaseAttackRange = (float)result->getDouble("BaseAttackRange");
	//nao sei....
	PlayerProfile.avatarAttribute.wBaseApDegen = 5000;
	PlayerProfile.avatarAttribute.wLastApDegen = 5000;
	PlayerProfile.avatarAttribute.wBaseApBattleDegen = 0;
	PlayerProfile.avatarAttribute.wLastApBattleDegen = 0;

	PlayerProfile.avatarAttribute.unknown2 = 144;
	PlayerProfile.avatarAttribute.unknown3_0 = 143;
	PlayerProfile.avatarAttribute.unknown3_1 = 142;
	PlayerProfile.avatarAttribute.fPhysicalCriticalDamageBonusRate = 141;
	PlayerProfile.avatarAttribute.unknown3_11 = 140;//
	PlayerProfile.avatarAttribute.unknown3_12 = 139;
	PlayerProfile.avatarAttribute.unknown3_13 = 138;//
	PlayerProfile.avatarAttribute.unknown3_2 = 137;
	PlayerProfile.avatarAttribute.baseSkillSpeed = 100.0f;//
	PlayerProfile.avatarAttribute.baseMaxWeight = 135;
	PlayerProfile.avatarAttribute.MaxWeight = 2600;
	PlayerProfile.avatarAttribute.unknown3_w6 = 134; // if != 0 weight get bugged
	PlayerProfile.avatarAttribute.fHtbBlockModeSuccessRate = 133;
	PlayerProfile.avatarAttribute.fSitDownLpRegenBonusRate = 132;//
	PlayerProfile.avatarAttribute.fSitDownEpRegenBonusRate = 131;
	PlayerProfile.avatarAttribute.unknown4_0 = 130;
	PlayerProfile.avatarAttribute.unknown4_1 = 129;
	PlayerProfile.avatarAttribute.basePhysicalCriticalDefenceRate = CalculePhysicalCriticalDefenceRate(PlayerProfile.avatarAttribute.byLastCon);
	PlayerProfile.avatarAttribute.baseEnergyCriticalDefenceRate = CalculeEnergyCriticalDefenceRate(PlayerProfile.avatarAttribute.byLastEng);
	PlayerProfile.avatarAttribute.lastPhysicalCriticalDefenceRate = PlayerProfile.avatarAttribute.basePhysicalCriticalDefenceRate;
	PlayerProfile.avatarAttribute.lastEnergyCriticalDefenceRate = PlayerProfile.avatarAttribute.baseEnergyCriticalDefenceRate;
	PlayerProfile.avatarAttribute.unknown4_6 = 124;
	PlayerProfile.avatarAttribute.unknown5_1 = 123;
	PlayerProfile.avatarAttribute.unknown5_0 = 122;
	PlayerProfile.avatarAttribute.unknown5_2 = 121;
	PlayerProfile.avatarAttribute.unknown5_3 = 120;
	PlayerProfile.avatarAttribute.unknown5_4 = 119;
	PlayerProfile.avatarAttribute.unknown5_5 = 118;
	PlayerProfile.avatarAttribute.fBasePhysicalCriticalRange = CalculePhysicalCriticalRange(plr->GetMyClass(), PlayerProfile.avatarAttribute.byLastDex);
	PlayerProfile.avatarAttribute.fLastPhysicalCriticalRange = PlayerProfile.avatarAttribute.fBasePhysicalCriticalRange;
	PlayerProfile.avatarAttribute.fBaseEnergyCriticalRange = CalculeEnergyCriticalRange(plr->GetMyClass(), PlayerProfile.avatarAttribute.byLastFoc);
	PlayerProfile.avatarAttribute.fLastEnergyCriticalRange = PlayerProfile.avatarAttribute.fBaseEnergyCriticalRange;
	PlayerProfile.avatarAttribute.wBaseBlockDamageRate = 113;
	PlayerProfile.avatarAttribute.wLastBlockDamageRate = 112;
	// SKILL SPEED
	PlayerProfile.avatarAttribute.SkillSpeed = 100.0f;
	//LP Get up Reg
	PlayerProfile.avatarAttribute.wBaseLpRegen = CalculeLPRegeneration(PlayerProfile.avatarAttribute.byLastCon);
	PlayerProfile.avatarAttribute.wLastLpRegen = PlayerProfile.avatarAttribute.wBaseLpRegen;
	//LP Sit Down Reg
	PlayerProfile.avatarAttribute.wBaseLpSitdownRegen = CalculeLPSitDownRegeneration(PlayerProfile.avatarAttribute.wLastLpRegen);//PlayerProfile.avatarAttribute.wLastMaxLP / 100 * 3;
	PlayerProfile.avatarAttribute.wLastLpSitdownRegen = PlayerProfile.avatarAttribute.wBaseLpSitdownRegen;//PlayerProfile.avatarAttribute.wLastMaxLP / 100 * 3;
	//LP Reg in Batle
	PlayerProfile.avatarAttribute.wBaseLpBattleRegen = 0;
	PlayerProfile.avatarAttribute.wLastLpBattleRegen = 0;
	//EP Get UP Reg
	PlayerProfile.avatarAttribute.wBaseEpRegen = CalculeEPRegeneration(PlayerProfile.avatarAttribute.byLastEng);
	PlayerProfile.avatarAttribute.wLastEpRegen = PlayerProfile.avatarAttribute.wBaseEpRegen;
	//EP Sit Down Reg
	PlayerProfile.avatarAttribute.wBaseEpSitdownRegen = CalculeEPSitDownRegeneration(PlayerProfile.avatarAttribute.wBaseEpRegen);//PlayerProfile.avatarAttribute.wLastMaxEP / 100 * 3;
	PlayerProfile.avatarAttribute.wLastEpSitdownRegen = PlayerProfile.avatarAttribute.wBaseEpSitdownRegen;// PlayerProfile.avatarAttribute.wLastMaxEP / 100 * 3;
	//EP Reg in Batle
	PlayerProfile.avatarAttribute.wBaseEpBattleRegen = CalculeEPBattleRegeneration(PlayerProfile.avatarAttribute.wBaseEpRegen);
	PlayerProfile.avatarAttribute.wLastEpBattleRegen = PlayerProfile.avatarAttribute.wBaseEpBattleRegen;
	//Rp incress rate
	PlayerProfile.avatarAttribute.wBaseRpRegen = CalculeRPRegeneration(PlayerProfile.avatarAttribute.wLastMaxRP);
	PlayerProfile.avatarAttribute.wLastRpRegen = PlayerProfile.avatarAttribute.wBaseRpRegen;
	//RP diminution
	PlayerProfile.avatarAttribute.wLastRpDimimutionRate = CalculeRPDiminution(PlayerProfile.avatarAttribute.wLastMaxRP);
	//Curse Sucess Rate
	PlayerProfile.avatarAttribute.wBaseCurseSuccessRate = CalculeCurseSuccessRate(PlayerProfile.avatarAttribute.byLastFoc);
	PlayerProfile.avatarAttribute.wLastCurseSuccessRate = PlayerProfile.avatarAttribute.wBaseCurseSuccessRate;
	//Curse Tolerance Rate
	PlayerProfile.avatarAttribute.wBaseCurseToleranceRate = CalculeCurseToleranceRate(PlayerProfile.avatarAttribute.byLastDex);
	PlayerProfile.avatarAttribute.wLastCurseToleranceRate = PlayerProfile.avatarAttribute.wBaseCurseToleranceRate;
	//Nao sei
	PlayerProfile.avatarAttribute.fCastingTimeChangePercent = 0;
	PlayerProfile.avatarAttribute.fCoolTimeChangePercent = 0;//
	PlayerProfile.avatarAttribute.fKeepTimeChangePercent = 0;
	PlayerProfile.avatarAttribute.fDotValueChangePercent = 0;
	PlayerProfile.avatarAttribute.fDotTimeChangeAbsolute = 0;//Ep Skill Required

	//Atribute Ofense/Defese
	PlayerProfile.avatarAttribute.fHonestOffence = 15;//nao
	PlayerProfile.avatarAttribute.fHonestDefence = 25;//nao
	PlayerProfile.avatarAttribute.fStrangeOffence = 35;//nao
	PlayerProfile.avatarAttribute.fStrangeDefence = 45;//nao
	PlayerProfile.avatarAttribute.fWildOffence = 55;//nao
	PlayerProfile.avatarAttribute.fWildDefence = 65;//nao
	PlayerProfile.avatarAttribute.fEleganceOffence = 75;//nao
	PlayerProfile.avatarAttribute.fEleganceDefence = 85;//nao
	PlayerProfile.avatarAttribute.fFunnyOffence = 95;//nao
	PlayerProfile.avatarAttribute.fFunnyDefence = 105;//nao

	PlayerProfile.avatarAttribute.fRequiredEpChangePercent = 0;
	PlayerProfile.avatarAttribute.wParalyzeToleranceRate = 97;//nao
	PlayerProfile.avatarAttribute.wTerrorToleranceRate = 96;//nao
	PlayerProfile.avatarAttribute.wConfuseToleranceRate = 95;//nao
	PlayerProfile.avatarAttribute.wStoneToleranceRate = 94;//nao
	PlayerProfile.avatarAttribute.wCandyToleranceRate = 93;//nao
	PlayerProfile.avatarAttribute.fParalyzeKeepTimeDown = 92;//nao
	PlayerProfile.avatarAttribute.fTerrorKeepTimeDown = 91;//nao
	PlayerProfile.avatarAttribute.fConfuseKeepTimeDown = 90;//nao
	PlayerProfile.avatarAttribute.fStoneKeepTimeDown = 89;//nao
	PlayerProfile.avatarAttribute.fCandyKeepTimeDown = 88;//nao
	PlayerProfile.avatarAttribute.fBleedingKeepTimeDown = 87;//nao
	PlayerProfile.avatarAttribute.fPoisonKeepTimeDown = 86;
	PlayerProfile.avatarAttribute.fStomachacheKeepTimeDown = 85;
	PlayerProfile.avatarAttribute.fCriticalBlockSuccessRate = 50;
	PlayerProfile.avatarAttribute.wGuardRate = 84;
	PlayerProfile.avatarAttribute.unknown6 = 83;
	PlayerProfile.avatarAttribute.fSkillDamageBlockModeSuccessRate = 82;
	PlayerProfile.avatarAttribute.fCurseBlockModeSuccessRate = 81;
	PlayerProfile.avatarAttribute.fKnockdownBlockModeSuccessRate = 80;

	PlayerProfile.avatarAttribute.baseAbdominalPainDefense = 66;
	PlayerProfile.avatarAttribute.AbdominalPainDefense = 66; // abdominal pain defense
	PlayerProfile.avatarAttribute.basePoisonDefense = 67;
	PlayerProfile.avatarAttribute.PoisonDefense = 67; // posion defense tw
	PlayerProfile.avatarAttribute.baseBleedingDefense = 68;
	PlayerProfile.avatarAttribute.BleedingDefense = 68;// Bleeding defense TW 
	PlayerProfile.avatarAttribute.baseBurnDefense = 69;
	PlayerProfile.avatarAttribute.BurnDefense = 69;//Burn Defense

	PlayerProfile.avatarAttribute.fEnergyCriticalDamageBonusRate = 0;
	PlayerProfile.avatarAttribute.fItemUpgradeBonusRate = 0;
	PlayerProfile.avatarAttribute.fItemUpgradeBreakBonusRate = 0;
	PlayerProfile.avatarAttribute.fBaseAirDash2Speed = 30.0f;//Dash Fly2 TW
	PlayerProfile.avatarAttribute.fLastAirDash2Speed = 30.0f;//Dash Fly2 TW
	PlayerProfile.avatarAttribute.fBaseAirDashSpeed = 20.0f;//Dash Fly TW
	PlayerProfile.avatarAttribute.fLastAirDashSpeed = 20.0f;//Dash Fly TW
	PlayerProfile.avatarAttribute.fBaseRunSpeed = static_cast<WORD>(result->getDouble("LastRunSpeed")); //Base Run TW
	PlayerProfile.avatarAttribute.fBaseAirSpeed = 15.0f;//Base Air Speed TW
	PlayerProfile.avatarAttribute.fLastAirSpeed = 15.0f;//LastAir Speed TW
	PlayerProfile.avatarAttribute.wLastMaxAp = result->getInt("LastMaxAp");//Max AP
	PlayerProfile.avatarAttribute.wBaseMaxAp = result->getInt("BaseMaxAp");//Base Max Ap
	PlayerProfile.avatarAttribute.wBaseApBattleRegen = 1000;//Regen In Battle AP TW
	PlayerProfile.avatarAttribute.wLastApBattleRegen = 1000;//LAst Regen in Battle Ap TW
	PlayerProfile.avatarAttribute.wBaseApRegen = 5000;//Base Ap Regen TW
	PlayerProfile.avatarAttribute.wLastApRegen = 5000;//Base While Sitting Regen AP TW
	PlayerProfile.avatarAttribute.wBaseApSitdownRegen = 5000;//AP Regen TW
	PlayerProfile.avatarAttribute.wLastApSitdownRegen = 5000;//AP Regen TW

	delete result;

	return true;
}
//----------------------------------------
//	Load attributes
//----------------------------------------
bool AttributesManager::LoadCharacterAttrFromDB(sPC_TBLDAT* pTblData)
{

	sql::ResultSet* result = sDB.executes("SELECT * FROM characters_attributes WHERE CharacterID = '%d';", charid);
	if (result == NULL)
	{
		delete result;
		sLog.outError("result == NULL begin");
		return false;
	}
	if (result->rowsCount() <= 0)
	{
		delete result;
		return false;
	}
	// create and load character attribute
	PlayerProfile.dwCurLP = result->getInt("CurLP");
	PlayerProfile.wCurEP = static_cast<WORD>(result->getInt("CurEP"));
	PlayerProfile.wCurRP = static_cast<WORD>(result->getInt("CurRP"));
	PlayerProfile.dwCurAp = result->getInt("CurAp");//New AP TW

	delete result;
	//static_cast<int>(pTblData->byStr + (pTblData->fLevel_Up_Str * (PlayerProfile.byLevel - 1)));
	int baseStr = CalculeBasicStats(pTblData->byStr, pTblData->fLevel_Up_Str, PlayerProfile.byLevel);
	int baseCon = CalculeBasicStats(pTblData->byCon, pTblData->fLevel_Up_Con, PlayerProfile.byLevel);
	int baseFoc = CalculeBasicStats(pTblData->byFoc, pTblData->fLevel_Up_Foc, PlayerProfile.byLevel);
	int baseDex = CalculeBasicStats(pTblData->byDex, pTblData->fLevel_Up_Dex, PlayerProfile.byLevel);
	int baseSol = CalculeBasicStats(pTblData->bySol, pTblData->fLevel_Up_Sol, PlayerProfile.byLevel);
	int baseEng = CalculeBasicStats(pTblData->byEng, pTblData->fLevel_Up_Eng, PlayerProfile.byLevel);

	//status Base Con/Focus Etc
	result = sDB.executes("UPDATE characters_attributes SET BaseStr = '%d', BaseCon = '%d', BaseFoc = '%d', BaseDex = '%d',BaseSol = '%d', BaseEng = '%d' WHERE CharacterID = '%d';",
		baseStr, baseCon, baseFoc, baseDex, baseSol, baseEng, charid);
	if (result != NULL)
		delete result;
	
	//status Last Con/Focus Etc
	result = sDB.executes("UPDATE characters_attributes SET LastStr = '%d', LastCon = '%d', LastFoc = '%d', LastDex = '%d', LastSol = '%d', LastEng = '%d' WHERE CharacterID = '%d';",
		baseStr, baseCon, baseFoc, baseDex, baseSol, baseEng, charid);
	if (result != NULL)
		delete result;

	// LP Calculation
	DWORD LP = CalculeLP(plr->GetMyClass(), baseCon);
	/*CLASS_INFO* classInfo = sTBM.GetFormulaTable()->FindClassInfoByClass(plr->GetMyClass());
	if (classInfo)
	{
		sLog.outBasic("Class %d lp rate tblidx %d", plr->GetMyClass(), classInfo->LP);
		sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(classInfo->LP);
		if (formula)
		{
			LP = formula->afRate[0] + (baseCon * formula->afRate[1]);
			sLog.outBasic("LP total %d rate1 %f rate2 %f lastCon %d", LP, formula->afRate[0], formula->afRate[1], baseCon);
		}
	}*/
	
	/*DWORD BasicLife = pTblData->wBasic_LP + (pTblData->byLevel_Up_LP * PlayerProfile.byLevel);
	WORD LevelCon = pTblData->byCon + static_cast<WORD>(pTblData->fLevel_Up_Con * PlayerProfile.byLevel);
	float ConByPoint = 85; // 1con = 85 old tw
	DWORD LP = BasicLife + static_cast<DWORD>(LevelCon * ConByPoint);*/

	//EP Calculation
	/*WORD BasicEnergy = pTblData->wBasic_EP + (pTblData->byLevel_Up_EP * PlayerProfile.byLevel);
	WORD LevelEng = pTblData->byEng + static_cast<WORD>(pTblData->fLevel_Up_Eng * PlayerProfile.byLevel);
	float EngByPoint = 45; // 1Eng = 45 ep old tw*/
	WORD EP = CalculeEP(plr->GetMyClass(), baseEng);//BasicEnergy + static_cast<WORD>(LevelEng * EngByPoint);

	WORD RP = CalculeRP(PlayerProfile.byLevel);
	//Set Data Base LP/ EP/ RP
	result = sDB.executes("UPDATE characters_attributes SET BaseMaxLP = '%d', BaseMaxEP = '%d', BaseMaxRP = '%d', LastMaxLP = '%d', LastMaxEP = '%d', LastMaxRP = '%d' WHERE CharacterID = '%d';",
		LP,
		static_cast<int>(EP),
		static_cast<int>(RP),//pTblData->wBasic_RP + (pTblData->byLevel_Up_RP * PlayerProfile.byLevel)),
		LP,
		static_cast<int>(EP),
		static_cast<int>(RP),//pTblData->wBasic_RP + (pTblData->byLevel_Up_RP * PlayerProfile.byLevel)),
		charid);
	if (result != NULL)
		delete result;

	//Atack Speed Rate // Range / Attack Rate
	result = sDB.executes("UPDATE characters_attributes SET BaseAttackSpeedRate = '%d', LastAttackSpeedRate = '%d', BaseAttackRange = '%d', LastAttackRange = '%d' WHERE CharacterID = '%d';",
		static_cast<int>(pTblData->wAttack_Speed_Rate),
		static_cast<int>(pTblData->wAttack_Speed_Rate),
		static_cast<int>(pTblData->fAttack_Range),
		static_cast<int>(pTblData->fAttack_Range),
		charid);
	if (result != NULL)
		delete result;

	//Calculation Physical Atack
	/*WORD BasicPhysicalOffence = pTblData->wBasic_Physical_Offence + (pTblData->byLevel_Up_Physical_Offence * PlayerProfile.byLevel);
	WORD LevelStr = pTblData->byStr + static_cast<WORD>(pTblData->fLevel_Up_Str * PlayerProfile.byLevel);
	float StrByPoint = 1.66; // 1Str = 1.66 Physical old tw*/
	WORD PhysicalOffence = CalculePhysicalOffence(plr->GetMyClass(), PlayerProfile.byLevel, baseStr, baseDex);//BasicPhysicalOffence + static_cast<WORD>(LevelStr * StrByPoint);
	//Calculation Physical Critical Atack 
	/*WORD BasicPhysicalCritical = 0;
	WORD LevelDex = pTblData->byDex + static_cast<WORD>(pTblData->fLevel_Up_Dex * PlayerProfile.byLevel);
	float DexByPoint = 0.5; // 1Dex = 1 critical old tw*/
	WORD PhysicalCriticalRate = CalculePhysicalCriticalRate(plr->GetMyClass(), baseDex);//BasicPhysicalCritical + static_cast<WORD>(LevelDex * DexByPoint); 
	// Atack Defese Physical
	result = sDB.executes("UPDATE characters_attributes SET BasePhysicalOffence = '%d', LastPhysicalOffence = '%d', BasePhysicalDefence = '%d', LastPhysicalDefence = '%d', BasePhysicalCriticalRate = '%d', LastPhysicalCriticalRate = '%d' WHERE CharacterID = '%d';",
		static_cast<int>(PhysicalOffence),
		static_cast<int>(PhysicalOffence),
		static_cast<int>(pTblData->wBasic_Physical_Defence + (pTblData->byLevel_Up_Physical_Defence * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->wBasic_Physical_Defence + (pTblData->byLevel_Up_Physical_Defence * PlayerProfile.byLevel)),
		static_cast<int>(PhysicalCriticalRate),
		static_cast<int>(PhysicalCriticalRate),
		charid);
	if (result != NULL)
		delete result;

	//Calculation Energy Atack
	/*WORD BasicEnergyOffence = pTblData->wBasic_Energy_Offence + (pTblData->byLevel_Up_Energy_Offence * PlayerProfile.byLevel);
	WORD LevelSol = pTblData->bySol + static_cast<WORD>(pTblData->fLevel_Up_Sol * PlayerProfile.byLevel);
	float SolByPoint = 1.66; // 1Soul = 1.66 Physical old tw*/
	WORD EnergyOffence = CalculeEnergyOffence(plr->GetMyClass(), PlayerProfile.byLevel, baseSol, baseFoc);//BasicEnergyOffence + static_cast<WORD>(LevelSol * SolByPoint);
	//Calculation Energy Critical Atack
	/*WORD BasicEnergyCritical = 0;
	WORD LevelFoc = pTblData->byFoc + static_cast<WORD>(pTblData->fLevel_Up_Foc * PlayerProfile.byLevel);
	float FocByPoint = 0.5; // 1Focus = 1 pont critical */
	WORD EnergyCriticalRate = CalculeEnergyCriticalRate(plr->GetMyClass(), baseFoc);// BasicEnergyCritical + static_cast<WORD>(LevelFoc * FocByPoint);
	// Atack Defese Energy
	result = sDB.executes("UPDATE characters_attributes SET BaseEnergyOffence = '%d', LastEnergyOffence = '%d', BaseEnergyDefence = '%d', LastEnergyDefence = '%d', BaseEnergyCriticalRate = '%d', LastEnergyCriticalRate = '%d' WHERE CharacterID = '%d';",
		static_cast<int>(EnergyOffence),
		static_cast<int>(EnergyOffence),
		static_cast<int>(pTblData->wBasic_Energy_Defence + (pTblData->byLevel_Up_Energy_Defence * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->wBasic_Energy_Defence + (pTblData->byLevel_Up_Energy_Defence * PlayerProfile.byLevel)),
		static_cast<int>(EnergyCriticalRate),
		static_cast<int>(EnergyCriticalRate),
		charid);
	if (result != NULL)
		delete result;

	//HitRate Calculation
	/*WORD BasicHitRate = pTblData->wAttack_Rate  * PlayerProfile.byLevel;
	WORD LevelingFocus = pTblData->byFoc + static_cast<WORD>(pTblData->fLevel_Up_Foc * PlayerProfile.byLevel);
	float FocusByPoint = 10; // 1 point = 10 hit rate old tw*/
	WORD HitRate = CalculeHitRate(baseFoc);//BasicHitRate + static_cast<WORD>(LevelingFocus * FocusByPoint);
	//DoggeRate Calculation
	/*WORD BasicDoggeRate = pTblData->wDodge_Rate  * PlayerProfile.byLevel;
	WORD LevelingDex = pTblData->byDex + static_cast<WORD>(pTblData->fLevel_Up_Dex * PlayerProfile.byLevel);
	float DoggeByPoint = 5;*/
	WORD DoggeRate = CalculeDodgeRate(baseDex);// BasicDoggeRate + static_cast<WORD>(LevelingDex * DoggeByPoint);
	// BlockRate calculation
	WORD BlockRate = CalculeBlockRate(baseDex, baseCon);
	//Set DataBase HitRate,DoggeRate,BlockRate 
	result = sDB.executes("UPDATE characters_attributes SET BaseAttackRate = '%d', LastAttackRate = '%d', BaseDodgeRate = '%d', LastDodgeRate = '%d', BaseBlockRate = '%d', LastBlockRate = '%d' WHERE CharacterID = '%d';",
		static_cast<int>(HitRate),
		static_cast<int>(HitRate),
		static_cast<int>(DoggeRate),
		static_cast<int>(DoggeRate),
		BlockRate,//static_cast<int>(pTblData->wBlock_Rate),
		BlockRate,//static_cast<int>(pTblData->wBlock_Rate),
		charid);
	if (result != NULL)
		delete result;
	return true;
}
//----------------------------------------
//	Load and add the items attributes to our player.avatarattribute
//----------------------------------------
void AttributesManager::LoadAttributesFromItems(sITEM_BRIEF *brief)
{
	for (int i = 0; i < EQUIP_SLOT_TYPE_COUNT; i++)
	{
		sITEM_TBLDAT *item = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(brief[i].tblidx);
		if (item == NULL)
		{
			item = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(brief[i].tblidx);
		}
		if (item != NULL)
		{
			eBATTLE_ATTRIBUTE bAttribute = (eBATTLE_ATTRIBUTE)item->eBattleAttribute;
			eEQUIP_TYPE eType = (eEQUIP_TYPE)item->eEquipType;
			ItemUpgradeTable * Grade = sTBM.GetItemUpgradeTable();
			sITEM_UPGRADE_TBLDAT * UpGrade = reinterpret_cast<sITEM_UPGRADE_TBLDAT*>(Grade->FindData(item->tblidx));
			if (UpGrade != NULL)
			{
				if (eType == eEQUIP_TYPE::EQUIP_TYPE_ARMOR || eType == eEQUIP_TYPE::EQUIP_TYPE_MAIN_WEAPON)
				{
					if (brief[i].byGrade == 0)
					{
						if (item->wPhysicalDefence != INVALID_WORD)
							PlayerProfile.avatarAttribute.wLastPhysicalDefence += item->wPhysicalDefence;
						if (item->wPhysicalOffence != INVALID_WORD)
							PlayerProfile.avatarAttribute.wLastPhysicalOffence += item->wPhysicalOffence;
						if (item->wEnergyDefence != INVALID_WORD)
							PlayerProfile.avatarAttribute.wLastEnergyDefence += item->wEnergyDefence;
						if (item->wEnergyOffence != INVALID_WORD)
							PlayerProfile.avatarAttribute.wLastEnergyOffence += item->wEnergyOffence;
					}
					else
					{
						if (item->wPhysicalDefence != INVALID_WORD)
							PlayerProfile.avatarAttribute.wLastPhysicalDefence += UpGrade->PysicalValue[brief[i].byGrade];
						if (item->wPhysicalOffence != INVALID_WORD)
							PlayerProfile.avatarAttribute.wLastPhysicalOffence += UpGrade->PysicalValue[brief[i].byGrade];
						if (item->wEnergyDefence != INVALID_WORD)
							PlayerProfile.avatarAttribute.wLastEnergyDefence += UpGrade->EnergyValue[brief[i].byGrade];
						if (item->wEnergyOffence != INVALID_WORD)
							PlayerProfile.avatarAttribute.wLastEnergyOffence += UpGrade->EnergyValue[brief[i].byGrade];
					}

				}
			}
		}
	}
	sLog.outDebug("first item id: %d", sTBM.GetItemTable()->Begin()->first);
}
//----------------------------------------
//	Create the default bit flag attribute
//----------------------------------------
void AttributesManager::CreatePlayerBaseAttributesBitFlag()
{
	changedFlag.Create(&PlayerProfile.avatarAttribute, ATTRIBUTE_TO_UPDATE_COUNT);
	FillAttributesLink();
	for (BYTE byIndex = ATTRIBUTE_TO_UPDATE_FIRST; byIndex <= ATTRIBUTE_TO_UPDATE_LAST; byIndex++) // unset all flag at login
	{
		if (changedFlag.IsSet(byIndex) == true)
		{
			changedFlag.Unset(byIndex);
		}
	}
}
//----------------------------------------
//	Update (add - remove) item attributes during game
//----------------------------------------
void AttributesManager::UpdateAttributesFromItem(sITEM_TBLDAT& item, BYTE Grade, bool remove)
{
	eEQUIP_TYPE eType = (eEQUIP_TYPE)item.eEquipType;
	ItemUpgradeTable * TableUpGrade = sTBM.GetItemUpgradeTable();
	sITEM_UPGRADE_TBLDAT * UpGrade = reinterpret_cast<sITEM_UPGRADE_TBLDAT*>(TableUpGrade->FindData(item.tblidx));
	if (UpGrade != NULL)
	{
		if (eType == eEQUIP_TYPE::EQUIP_TYPE_ARMOR || eType == eEQUIP_TYPE::EQUIP_TYPE_MAIN_WEAPON)
		{
			if (item.wPhysicalOffence < 65535 && item.wPhysicalOffence > 0)
			{
				if (remove == true)
					AddLastPhysicalOffence(Dbo_GetFinalOffence(item.wPhysicalOffence, Grade, UpGrade->PysicalValue[Grade]) * -1); // 0 should be grade
				else
					AddLastPhysicalOffence(Dbo_GetFinalOffence(item.wPhysicalOffence, Grade, UpGrade->PysicalValue[Grade]));
			}
			if (item.wPhysicalDefence < 65535 && item.wPhysicalDefence > 0)
			{
				if (remove)
					AddLastPhysicalDefence(Dbo_GetFinalDefence(item.wPhysicalDefence, Grade, UpGrade->PysicalValue[Grade]) * -1);
				else
					AddLastPhysicalDefence(Dbo_GetFinalDefence(item.wPhysicalDefence, Grade, UpGrade->PysicalValue[Grade]));
			}
			if (item.wEnergyOffence < 65535 && item.wEnergyOffence > 0)
			{
				if (remove)
					AddLastEnergyOffence(Dbo_GetFinalOffence(item.wEnergyOffence, Grade, UpGrade->EnergyValue[Grade]) * -1);
				else
					AddLastEnergyOffence(Dbo_GetFinalOffence(item.wEnergyOffence, Grade, UpGrade->EnergyValue[Grade]));
			}
			if (item.wEnergyDefence < 65535 && item.wEnergyDefence > 0)
			{
				if (remove)
					AddLastEnergyDefence(Dbo_GetFinalDefence(item.wEnergyDefence, Grade, UpGrade->EnergyValue[Grade]) * -1);
				else
					AddLastEnergyDefence(Dbo_GetFinalDefence(item.wEnergyDefence, Grade, UpGrade->EnergyValue[Grade]));
			}
		/*	if (item.wAttackSpeedRate < 65535 && item.wAttackSpeedRate > 0)
			{
				SetLastAttackSpeedRate(item.wAttackSpeedRate);
			}*/
		}
	}
}
void AttributesManager::UpdateExtraAttributesFromItem(sITEM_EFFECT aitemEffect[6], bool isRemove)
{	
	sITEM_ENCHANT_TBLDAT *EnchantTable = NULL;
	for (int i = 0; i <= 6; i++)
	{
		EnchantTable = (sITEM_ENCHANT_TBLDAT*)sTBM.GetItemEnchantTable()->FindData(aitemEffect[i].wType);
		if (EnchantTable != NULL)
		{
			int count = 0;
			sSYSTEM_EFFECT_TBLDAT * SystemEffectData = NULL;
			SystemEffectData = (sSYSTEM_EFFECT_TBLDAT*)sTBM.GetSystemEffectTable()->FindData(EnchantTable->tbxSystemEffect);
			if (SystemEffectData != NULL)
			{
				//printf("skill_Effect %d \n", skillDataOriginal->skill_Effect[Effect]);
				//printf("effectCode %d \n", SystemEffectData->effectCode);
				//	printf("Effect %d \n", Effect);
				switch (SystemEffectData->effectCode)
				{
				case ACTIVE_MAX_LP_UP:
				{
					if (isRemove == true)
						plr->GetAttributesManager()->AddLastMaxLP(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->AddLastMaxLP(aitemEffect[i].dwValue);
					break;
				}
				case ACTIVE_MAX_EP_UP:
				{
					if (isRemove == true)
						plr->GetAttributesManager()->AddLastMaxEP(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->AddLastMaxEP(aitemEffect[i].dwValue);
					break;
				}
				case ACTIVE_MAX_RP_UP:
				{

					if (isRemove == true)
						plr->GetAttributesManager()->SetLastMaxRP(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->SetLastMaxRP(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.wLastMaxRP <= 0 || plr->GetPcProfile()->avatarAttribute.wLastMaxRP >= 60000)
						plr->GetAttributesManager()->SetLastMaxRP(0);
					break;
				}
				case ACTIVE_PHYSICAL_OFFENCE_UP:
				{
					if (isRemove == true)
						plr->GetAttributesManager()->AddLastPhysicalOffence(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->AddLastPhysicalOffence(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence >= 60000)
					{
						plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence = 0;
						plr->GetAttributesManager()->AddLastPhysicalOffence(0);
					}

					break;
				}
				case ACTIVE_ENERGY_OFFENCE_UP:
				{
					if (isRemove == true)
						plr->GetAttributesManager()->AddLastEnergyOffence(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->AddLastEnergyOffence(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence >= 60000)
					{
						plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence = 0;
						plr->GetAttributesManager()->AddLastPhysicalOffence(0);
					}
					break;
				}
				case ACTIVE_PHYSICAL_DEFENCE_UP:
				{

					if (isRemove == true)
						plr->GetAttributesManager()->AddLastPhysicalDefence(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->AddLastPhysicalDefence(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence >= 60000)
					{
						plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence = 0;
						plr->GetAttributesManager()->AddLastPhysicalDefence(0);
					}
					break;
				}
				case ACTIVE_ENERGY_DEFENCE_UP:
				{

					if (isRemove == true)
						plr->GetAttributesManager()->AddLastEnergyDefence(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->AddLastEnergyDefence(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.wLastEnergyDefence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastEnergyDefence >= 60000)
					{
						plr->GetPcProfile()->avatarAttribute.wLastEnergyDefence = 0;
						plr->GetAttributesManager()->AddLastEnergyDefence(0);
					}
					break;
				}
				case ACTIVE_STR_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastStr(aitemEffect[i].dwValue * -1);

						WORD LevelStr = aitemEffect[i].dwValue;
						float StrByPoint = 1.66; // 1Str = 1.66 Physical old tw
						WORD PhysicalOffence = static_cast<WORD>(LevelStr * StrByPoint);

						plr->GetAttributesManager()->AddLastPhysicalOffence(PhysicalOffence * -1);
						if (plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence >= 60000)
						{
							plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence = 0;
							plr->GetAttributesManager()->AddLastPhysicalOffence(0);
						}
					}
					else
					{
						plr->GetAttributesManager()->AddLastStr(aitemEffect[i].dwValue);

						WORD LevelStr = aitemEffect[i].dwValue;
						float StrByPoint = 1.66; // 1Str = 1.66 Physical old tw
						WORD PhysicalOffence = static_cast<WORD>(LevelStr * StrByPoint);

						plr->GetAttributesManager()->AddLastPhysicalOffence(PhysicalOffence);
					}
					break;
				}
				case ACTIVE_CON_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastCon(aitemEffect[i].dwValue * -1);

						float LevelCon = aitemEffect[i].dwValue;
						float ConByPoint = 85; // 1con = 85 old tw
						float LP = static_cast<float>(LevelCon * ConByPoint);

						plr->GetAttributesManager()->AddLastMaxLP(LP * -1);
					}
					else
					{
						plr->GetAttributesManager()->AddLastCon(aitemEffect[i].dwValue);

						float LevelCon = aitemEffect[i].dwValue;
						float ConByPoint = 85; // 1con = 85 old tw
						float LP = static_cast<float>(LevelCon * ConByPoint);

						plr->GetAttributesManager()->AddLastMaxLP(LP);
					}
					break;
				}
				case ACTIVE_FOC_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastFoc(aitemEffect[i].dwValue * -1);
						WORD LevelFoc = aitemEffect[i].dwValue;
						float EnergyCriticalByPoint = 0.5; // 1Focus = 1 pont critical 
						float EnergyAttackByPoint = 2; // 1Focus = 1 pont critical 
						float HitRateByPoint = 10; // 1 point = 10 hit rate old tw
						WORD EnergyCriticalRate = static_cast<WORD>(LevelFoc * EnergyCriticalByPoint);
						WORD EnergyAttack = static_cast<WORD>(LevelFoc * EnergyAttackByPoint);
						WORD HitRate = static_cast<WORD>(LevelFoc * HitRateByPoint);
						plr->GetAttributesManager()->AddLastEnergyCriticalRate(EnergyCriticalRate * -1);
						plr->GetAttributesManager()->AddLastEnergyOffence(EnergyAttack * -1);
						plr->GetAttributesManager()->AddLastAttackRate(HitRate * -1);
						if (plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence >= 60000)
						{
							plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence = 0;
							plr->GetAttributesManager()->AddLastPhysicalOffence(0);
						}
					}
					else
					{
						plr->GetAttributesManager()->AddLastFoc(aitemEffect[i].dwValue);
						WORD LevelFoc = aitemEffect[i].dwValue;
						float EnergyCriticalByPoint = 0.5; // 1Focus = 1 pont critical 
						float EnergyAttackByPoint = 2; // 1Focus = 1 pont critical 
						float HitRateByPoint = 10; // 1 point = 10 hit rate old tw
						WORD EnergyCriticalRate = static_cast<WORD>(LevelFoc * EnergyCriticalByPoint);
						WORD EnergyAttack = static_cast<WORD>(LevelFoc * EnergyAttackByPoint);
						WORD HitRate = static_cast<WORD>(LevelFoc * HitRateByPoint);
						plr->GetAttributesManager()->AddLastEnergyCriticalRate(EnergyCriticalRate);
						plr->GetAttributesManager()->AddLastEnergyOffence(EnergyAttack);
						plr->GetAttributesManager()->AddLastAttackRate(HitRate);
					}
					break;
				}
				case ACTIVE_DEX_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastDex(aitemEffect[i].dwValue * -1);
						WORD LevelDex = aitemEffect[i].dwValue;
						float CriticalAttackByPoint = 0.5; // 1Dex = 1 critical old tw
						float PhyAttackByPoint = 2; // 1Dex = 1 phyattack old tw
						float DoggeByPoint = 5;
						WORD PhysicalCriticalRate = static_cast<WORD>(LevelDex * CriticalAttackByPoint);
						WORD PhysicalAttack = static_cast<WORD>(LevelDex * PhyAttackByPoint);
						WORD DodgeRate = static_cast<WORD>(LevelDex * DoggeByPoint);
						plr->GetAttributesManager()->AddLastPhysicalCriticalRate(PhysicalCriticalRate * -1);
						plr->GetAttributesManager()->AddLastPhysicalOffence(PhysicalAttack * -1);
						plr->GetAttributesManager()->AddLastDodgeRate(DodgeRate * -1);
						if (plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence >= 60000)
						{
							plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence = 0;
							plr->GetAttributesManager()->AddLastPhysicalOffence(0);
						}
						if (plr->GetPcProfile()->avatarAttribute.byLastDex <= 0 || plr->GetPcProfile()->avatarAttribute.byLastDex >= 60000)
						{
							plr->GetPcProfile()->avatarAttribute.byLastDex = 0;
							plr->GetAttributesManager()->AddLastDex(0);
						}
					}
					else
					{
						plr->GetAttributesManager()->AddLastDex(aitemEffect[i].dwValue);
						WORD LevelDex = aitemEffect[i].dwValue;
						float CriticalAttackByPoint = 0.5; // 1Dex = 1 critical old tw
						float PhyAttackByPoint = 2; // 1Dex = 1 phyattack old tw
						float DoggeByPoint = 5;
						WORD PhysicalCriticalRate = static_cast<WORD>(LevelDex * CriticalAttackByPoint);
						WORD PhysicalAttack = static_cast<WORD>(LevelDex * PhyAttackByPoint);
						WORD DodgeRate = static_cast<WORD>(LevelDex * DoggeByPoint);
						plr->GetAttributesManager()->AddLastPhysicalCriticalRate(PhysicalCriticalRate);
						plr->GetAttributesManager()->AddLastPhysicalOffence(PhysicalAttack);
						plr->GetAttributesManager()->AddLastDodgeRate(DodgeRate);
					}
					break;
				}
				case ACTIVE_SOL_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastSol(aitemEffect[i].dwValue * -1);

						WORD LevelSol = aitemEffect[i].dwValue;
						float SolByPoint = 1.66; // 1Soul = 1.66 Physical old tw
						WORD EnergyOffence = static_cast<WORD>(LevelSol * SolByPoint);

						plr->GetAttributesManager()->AddLastEnergyOffence(EnergyOffence * -1);
						if (plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence >= 60000)
						{
							plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence = 0;
							plr->GetAttributesManager()->AddLastPhysicalOffence(0);
						}
					}
					else
					{
						plr->GetAttributesManager()->AddLastSol(aitemEffect[i].dwValue);

						WORD LevelSol = aitemEffect[i].dwValue;
						float SolByPoint = 1.66; // 1Soul = 1.66 Physical old tw
						WORD EnergyOffence = static_cast<WORD>(LevelSol * SolByPoint);

						plr->GetAttributesManager()->AddLastEnergyOffence(EnergyOffence);
					}
					break;
				}
				case ACTIVE_ENG_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastEng(aitemEffect[i].dwValue * -1);

						WORD LevelEng = aitemEffect[i].dwValue;
						float EngByPoint = 45; // 1Eng = 45 ep old tw
						WORD EP = static_cast<WORD>(LevelEng * EngByPoint);

						plr->GetAttributesManager()->AddLastMaxEP(EP * -1);
					}
					else
					{
						plr->GetAttributesManager()->AddLastEng(aitemEffect[i].dwValue);

						WORD LevelEng = aitemEffect[i].dwValue;
						float EngByPoint = 45; // 1Eng = 45 ep old tw
						WORD EP = static_cast<WORD>(LevelEng * EngByPoint);

						plr->GetAttributesManager()->AddLastMaxEP(EP);
					}
					break;
				}
				case ACTIVE_ATTACK_RATE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastAttackRate(aitemEffect[i].dwValue * -1);
					}
					else
					{
						plr->GetAttributesManager()->AddLastAttackRate(aitemEffect[i].dwValue);
					}
					break;
				}
				case ACTIVE_DODGE_RATE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastDodgeRate(aitemEffect[i].dwValue * -1);
					}
					else
					{
						plr->GetAttributesManager()->AddLastDodgeRate(aitemEffect[i].dwValue);
					}
					break;
				}
				case ACTIVE_BLOCK_RATE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastBlockRate(aitemEffect[i].dwValue * -1);
					}
					else
					{
						plr->GetAttributesManager()->AddLastBlockRate(aitemEffect[i].dwValue);
					}
					break;
				}
				//Atributes//
				case ACTIVE_HONEST_DEFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddHonestDefence(0);
					}
					else
					{
						plr->GetAttributesManager()->AddHonestDefence(100.0);
					}
					break;
				}
				case ACTIVE_STRANGE_DEFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddStrangeDefence(0);
					}
					else
					{
						plr->GetAttributesManager()->AddStrangeDefence(100.0);
					}
					break;
				}
				case ACTIVE_WILD_DEFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddWildDefence(0);
					}
					else
					{
						plr->GetAttributesManager()->AddWildDefence(100.0);
					}
					break;
				}
				case ACTIVE_ELEGANCE_DEFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddEleganceDefence(0);
					}
					else
					{
						plr->GetAttributesManager()->AddEleganceDefence(100.0);
					}
					break;
				}
				case ACTIVE_FUNNY_DEFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddFunnyDefence(0);
					}
					else
					{
						plr->GetAttributesManager()->AddFunnyDefence(100.0);
					}
					break;
				}
				case ACTIVE_HONEST_OFFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddHonestOffence(0);
					}
					else
					{
						plr->GetAttributesManager()->AddHonestOffence(100.0);
					}
					break;
				}
				case ACTIVE_STRANGE_OFFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddStrangeOffence(0);
					}
					else
					{
						plr->GetAttributesManager()->AddStrangeOffence(100.0);
					}
					break;
				}
				case ACTIVE_WILD_OFFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddWildOffence(0);
					}
					else
					{
						plr->GetAttributesManager()->AddWildOffence(100.0);
					}
					break;
				}
				case ACTIVE_ELEGANCE_OFFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddEleganceOffence(0);
					}
					else
					{
						plr->GetAttributesManager()->AddEleganceOffence(100.0);
					}
					break;
				}
				case ACTIVE_FUNNY_OFFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddFunnyOffence(0);
					}
					else
					{
						plr->GetAttributesManager()->AddFunnyOffence(100.0);
					}
					break;
				}
				case ACTIVE_ENERGY_REFLECTION:
				{
					if (isRemove == true)
					{
					}
					else
					{
					}
					break;
				}
				case ACTIVE_LP_REGENERATION:
				{
					if (isRemove == true)
					{
					}
					else
					{
					}
					break;
				}
				case ACTIVE_EP_REGENERATION:
				{
					if (isRemove == true)
					{
					}
					else
					{
					}
					break;
				}
				case ACTIVE_RP_CHARGE_SPEED:
				{
					if (isRemove == true)
					{
					}
					else
					{
					}
					break;
				}
				case ACTIVE_CURSE_SUCCESS:
				{
					if (isRemove == true)
					{
					}
					else
					{
					}
					break;
				}
				case ACTIVE_CURSE_TOLERANCE:
				{
					if (isRemove == true)
					{
					}
					else
					{
					}
					break;
				}
				case ACTIVE_PHYSICAL_CRITICAL:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastPhysicalCriticalRate(aitemEffect[i].dwValue * -1);
					}
					else
					{
						plr->GetAttributesManager()->AddLastPhysicalCriticalRate(aitemEffect[i].dwValue);
					}
					break;
				}
				case ACTIVE_ENERGY_CRITICAL:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->AddLastEnergyCriticalRate(aitemEffect[i].dwValue * -1);
					}
					else
					{
						plr->GetAttributesManager()->AddLastEnergyCriticalRate(aitemEffect[i].dwValue);
					}
					break;
				}
				case ACTIVE_SKILL_CASTING_TIME_DOWN:
				{
					if (isRemove == true)
					{
					}
					else
					{
					}
					break;
				}
				case ACTIVE_PHYSICAL_CRITICAL_DAMAGE_UP:
				{					
					if (isRemove == true)
						plr->GetAttributesManager()->SetPhysicalCriticalDamageBonusRate(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->SetPhysicalCriticalDamageBonusRate(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate <= 0 || plr->GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate >= 60000)
					{
						plr->GetPcProfile()->avatarAttribute.fPhysicalCriticalDamageBonusRate = 0;
						plr->GetAttributesManager()->SetPhysicalCriticalDamageBonusRate(0);
					}
					break;
				}
				case ACTIVE_ENERGY_CRITICAL_DAMAGE_UP:
				{					
					if (isRemove == true)
						plr->GetAttributesManager()->SetEnergyCriticalDamageBonusRate(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->SetEnergyCriticalDamageBonusRate(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.fEnergyCriticalDamageBonusRate <= 0 || plr->GetPcProfile()->avatarAttribute.fEnergyCriticalDamageBonusRate >= 60000)
					{
						plr->GetPcProfile()->avatarAttribute.fEnergyCriticalDamageBonusRate = 0;
						plr->GetAttributesManager()->SetEnergyCriticalDamageBonusRate(0);
					}
					break;
				}
				/*case ACTIVE_SKILL_COOL_TIME_DOWN:
				{
					float CoolDown = aitemEffect[i].dwValue;
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetCoolTimeChangePercent(CoolDown);
						printf("Remove Cool Down \n");
					}
					else
					{
						printf("Adiciona Cool Down \n");
						plr->GetAttributesManager()->SetCoolTimeChangePercent(CoolDown * -1);
						
					}
					break;
				}*/
				/*case ACTIVE_ATTACK_SPEED_UP:
				{
					if (isRemove == true)
					{
						sGU_UPDATE_CHAR_ATTACK_SPEEDRATE sAttackSpeed;
						sAttackSpeed.wOpCode = GU_UPDATE_CHAR_ATTACK_SPEEDRATE;
						sAttackSpeed.wPacketSize = sizeof(sGU_UPDATE_CHAR_ATTACK_SPEEDRATE) - 2;
						sAttackSpeed.handle = plr->GetHandle();
						int attackspeed = 1400 / 100 * aitemEffect[i].dwValue;
						plr->GetAttributesManager()->AddLastAttackSpeedRate(attackspeed);
						sAttackSpeed.wAttackSpeedRate = plr->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate;						

						if (plr->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate <= 0 || plr->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate >= 1400)
						{
							plr->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate = 1400;
							plr->GetAttributesManager()->SetLastAttackSpeedRate(0);
							sAttackSpeed.wAttackSpeedRate = plr->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate;
						}

						plr->SendPacket((char*)&sAttackSpeed, sizeof(sGU_UPDATE_CHAR_ATTACK_SPEEDRATE));
						plr->SendToPlayerList((char*)&sAttackSpeed, sizeof(sGU_UPDATE_CHAR_ATTACK_SPEEDRATE));
					}
					else
					{
						sGU_UPDATE_CHAR_ATTACK_SPEEDRATE sAttackSpeed;
						sAttackSpeed.wOpCode = GU_UPDATE_CHAR_ATTACK_SPEEDRATE;
						sAttackSpeed.wPacketSize = sizeof(sGU_UPDATE_CHAR_ATTACK_SPEEDRATE) - 2;
						sAttackSpeed.handle = plr->GetHandle();
						int attackspeed = 1400 / 100 * aitemEffect[i].dwValue;
						plr->GetAttributesManager()->SetLastAttackSpeedRate(attackspeed * -1);
						sAttackSpeed.wAttackSpeedRate = plr->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate;
						

						if (plr->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate <= 0 || plr->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate >= 1400)
						{
							plr->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate = 1400;
							plr->GetAttributesManager()->SetLastAttackSpeedRate(0);
							sAttackSpeed.wAttackSpeedRate = plr->GetPcProfile()->avatarAttribute.wLastAttackSpeedRate;
						}

						plr->SendPacket((char*)&sAttackSpeed, sizeof(sGU_UPDATE_CHAR_ATTACK_SPEEDRATE));
						plr->SendToPlayerList((char*)&sAttackSpeed, sizeof(sGU_UPDATE_CHAR_ATTACK_SPEEDRATE));
					}
					break;
				}*/
				//Next Case

				}
			}
		}
	}
}
//----------------------------------------
//	Send the new players attributes
//----------------------------------------
void AttributesManager::UpdateAttributes()
{
	FillAttributesLink(); // store our attributes modded value
	/*DWORD buffer[2048];
	DWORD datasize = 0;

	if (SaveAvatarAttribute(&buffer, &datasize) == false)
	{
		sLog.outError("ERROR IN SaveAvatarAttribute");
	}*/

	sGU_AVATAR_ATTRIBUTE_UPDATE attr;
	memset(&attr, INVALID_TBLIDX, sizeof(sGU_AVATAR_ATTRIBUTE_UPDATE));

	attr.wOpCode = GU_AVATAR_ATTRIBUTE_UPDATE;
	attr.wPacketSize = sizeof(sGU_AVATAR_ATTRIBUTE_UPDATE) - 2;

	attr.byAttributeTotalCount = ATTRIBUTE_TO_UPDATE_COUNT + 1;// 166; // 157
	attr.hHandle = plr->GetHandle();

	// Aca se guarda los atributos que deseas activar en formato bit
	// Si quieres activar los dos primeros entonces envias en el primer byte 128(10000000)
	// y en el count envias 1
	// Si envias los dos primeros entonces 192(11000000) y count 2
	// El ultimo byte siempre es 0x3f
	memset(attr.bitmask, 0xff, sizeof attr.bitmask);
	attr.bitmask[19] = 0x3f;

	attr.unknown[0] = 100;
	attr.unknown[1] = 100;
	attr.unknown[2] = 100;

	memcpy(&attr.attributes, &PlayerProfile.avatarAttribute, sizeof sAVATAR_ATTRIBUTE);

	plr->SendPacket((char*)&attr, sizeof(sGU_AVATAR_ATTRIBUTE_UPDATE));
}
//----------------------------------------
//	Fill link to get a ref of attributes
//----------------------------------------
void AttributesManager::FillAttributesLink()
{
	unsigned short unkWORDField = 0;
	float unkFLOATField = 0;

	attrLink.pbyBaseCon = &PlayerProfile.avatarAttribute.byBaseCon;
	attrLink.pbyBaseDex = &PlayerProfile.avatarAttribute.byBaseDex;
	attrLink.pbyBaseEng = &PlayerProfile.avatarAttribute.byBaseEng;
	attrLink.pbyBaseFoc = &PlayerProfile.avatarAttribute.byBaseFoc;
	attrLink.pbyBaseSol = &PlayerProfile.avatarAttribute.byBaseSol;
	attrLink.pbyBaseStr = &PlayerProfile.avatarAttribute.byBaseStr;

	attrLink.pbyLastCon = &PlayerProfile.avatarAttribute.byLastCon;
	attrLink.pbyLastDex = &PlayerProfile.avatarAttribute.byLastDex;
	attrLink.pbyLastEng = &PlayerProfile.avatarAttribute.byLastEng;
	attrLink.pbyLastFoc = &PlayerProfile.avatarAttribute.byLastFoc;
	attrLink.pbyLastSol = &PlayerProfile.avatarAttribute.byLastSol;
	attrLink.pbyLastStr = &PlayerProfile.avatarAttribute.byLastStr;

	attrLink.pfBaseAirDash2Speed = &PlayerProfile.avatarAttribute.fBaseAirDash2Speed;
	attrLink.pfBaseAirDashSpeed = &PlayerProfile.avatarAttribute.fBaseAirDashSpeed;
	attrLink.pfBaseAirSpeed = &PlayerProfile.avatarAttribute.fBaseAirSpeed;
	attrLink.pfLastAirSpeed = &PlayerProfile.avatarAttribute.fLastAirSpeed;
	attrLink.pfBaseAttackRange = &PlayerProfile.avatarAttribute.fBaseAttackRange;
	attrLink.pfBaseRunSpeed = &PlayerProfile.avatarAttribute.fBaseRunSpeed;

	attrLink.pfBleedingKeepTimeDown = &PlayerProfile.avatarAttribute.fBleedingKeepTimeDown;
	attrLink.pfCandyKeepTimeDown = &PlayerProfile.avatarAttribute.fCandyKeepTimeDown;
	attrLink.pfCastingTimeChangePercent = &PlayerProfile.avatarAttribute.fCastingTimeChangePercent;
	attrLink.pfConfuseKeepTimeDown = &PlayerProfile.avatarAttribute.fConfuseKeepTimeDown;
	attrLink.pfCoolTimeChangePercent = &PlayerProfile.avatarAttribute.fCoolTimeChangePercent;
	attrLink.pfCriticalBlockSuccessRate = &PlayerProfile.avatarAttribute.fCriticalBlockSuccessRate;
	attrLink.pfCurseBlockModeSuccessRate = &PlayerProfile.avatarAttribute.fCurseBlockModeSuccessRate;
	attrLink.pfDotTimeChangeAbsolute = &PlayerProfile.avatarAttribute.fDotTimeChangeAbsolute;
	attrLink.pfDotValueChangePercent = &PlayerProfile.avatarAttribute.fDotValueChangePercent;
	attrLink.pfEleganceDefence = &PlayerProfile.avatarAttribute.fEleganceDefence;
	attrLink.pfEleganceOffence = &PlayerProfile.avatarAttribute.fEleganceOffence;

	attrLink.pfEnergyCriticalDamageBonusRate = &PlayerProfile.avatarAttribute.fEnergyCriticalDamageBonusRate;
	attrLink.pfFunnyDefence = &PlayerProfile.avatarAttribute.fFunnyDefence;
	attrLink.pfFunnyOffence = &PlayerProfile.avatarAttribute.fFunnyOffence;
	attrLink.pfHonestDefence = &PlayerProfile.avatarAttribute.fHonestDefence;
	attrLink.pfHonestOffence = &PlayerProfile.avatarAttribute.fHonestOffence;
	attrLink.pfHtbBlockModeSuccessRate = &PlayerProfile.avatarAttribute.fHtbBlockModeSuccessRate;
	attrLink.pfItemUpgradeBonusRate = &PlayerProfile.avatarAttribute.fItemUpgradeBonusRate;
	attrLink.pfItemUpgradeBreakBonusRate = &PlayerProfile.avatarAttribute.fItemUpgradeBreakBonusRate;
	attrLink.pfKeepTimeChangePercent = &PlayerProfile.avatarAttribute.fKeepTimeChangePercent;
	attrLink.pfKnockdownBlockModeSuccessRate = &PlayerProfile.avatarAttribute.fKnockdownBlockModeSuccessRate;
	attrLink.pfLastAirDash2Speed = &PlayerProfile.avatarAttribute.fLastAirDash2Speed;
	attrLink.pfLastAirDashSpeed = &PlayerProfile.avatarAttribute.fLastAirDashSpeed;
	attrLink.pfLastAttackRange = &PlayerProfile.avatarAttribute.fLastAttackRange;

	attrLink.pfLastRunSpeed = &PlayerProfile.avatarAttribute.fLastRunSpeed;
	attrLink.pfParalyzeKeepTimeDown = &PlayerProfile.avatarAttribute.fParalyzeKeepTimeDown;
	attrLink.pfPhysicalCriticalDamageBonusRate = &PlayerProfile.avatarAttribute.fPhysicalCriticalDamageBonusRate;
	attrLink.pfPoisonKeepTimeDown = &PlayerProfile.avatarAttribute.fPoisonKeepTimeDown;
	attrLink.pfRequiredEpChangePercent = &PlayerProfile.avatarAttribute.fRequiredEpChangePercent;
	attrLink.pfSitDownEpRegenBonusRate = &PlayerProfile.avatarAttribute.fSitDownEpRegenBonusRate;
	attrLink.pfSitDownLpRegenBonusRate = &PlayerProfile.avatarAttribute.fSitDownLpRegenBonusRate;
	attrLink.pfSkillDamageBlockModeSuccessRate = &PlayerProfile.avatarAttribute.fSkillDamageBlockModeSuccessRate;
	attrLink.pfStomachacheKeepTimeDown = &PlayerProfile.avatarAttribute.fStomachacheKeepTimeDown;
	attrLink.pfStoneKeepTimeDown = &PlayerProfile.avatarAttribute.fStoneKeepTimeDown;
	attrLink.pfStrangeDefence = &PlayerProfile.avatarAttribute.fStrangeDefence;
	attrLink.pfStrangeOffence = &PlayerProfile.avatarAttribute.fStrangeOffence;
	attrLink.pfTerrorKeepTimeDown = &PlayerProfile.avatarAttribute.fTerrorKeepTimeDown;

	attrLink.pfWildDefence = &PlayerProfile.avatarAttribute.fWildDefence;
	attrLink.pfWildOffence = &PlayerProfile.avatarAttribute.fWildOffence;
	attrLink.pwBaseApBattleRegen = &PlayerProfile.avatarAttribute.wBaseApBattleRegen;
	attrLink.pwBaseApRegen = &PlayerProfile.avatarAttribute.wBaseApRegen;
	attrLink.pwBaseApSitdownRegen = &PlayerProfile.avatarAttribute.wBaseApSitdownRegen;
	attrLink.pwBaseAttackRate = &PlayerProfile.avatarAttribute.wBaseAttackRate;
	attrLink.pwBaseAttackSpeedRate = &PlayerProfile.avatarAttribute.wBaseAttackSpeedRate;
	attrLink.pwBaseBlockRate = &PlayerProfile.avatarAttribute.wBaseBlockRate;
	attrLink.pwBaseCurseSuccessRate = &PlayerProfile.avatarAttribute.wBaseCurseSuccessRate;
	attrLink.pwBaseCurseToleranceRate = &PlayerProfile.avatarAttribute.wBaseCurseToleranceRate;

	attrLink.pwBaseDodgeRate = &PlayerProfile.avatarAttribute.wBaseDodgeRate;
	attrLink.pwBaseEnergyCriticalRate = &PlayerProfile.avatarAttribute.wBaseEnergyCriticalRate;
	attrLink.pwBaseEnergyDefence = &PlayerProfile.avatarAttribute.wBaseEnergyDefence;
	attrLink.pwBaseEnergyOffence = &PlayerProfile.avatarAttribute.wBaseEnergyOffence;
	attrLink.pwBaseEpBattleRegen = &PlayerProfile.avatarAttribute.wBaseEpBattleRegen;
	attrLink.pwBaseEpRegen = &PlayerProfile.avatarAttribute.wBaseEpRegen;
	attrLink.pwBaseEpSitdownRegen = &PlayerProfile.avatarAttribute.wBaseEpSitdownRegen;
	attrLink.pwBaseLpBattleRegen = &PlayerProfile.avatarAttribute.wBaseLpBattleRegen;
	attrLink.pwBaseLpRegen = &PlayerProfile.avatarAttribute.wBaseLpRegen;
	attrLink.pwBaseLpSitdownRegen = &PlayerProfile.avatarAttribute.wBaseLpSitdownRegen;
	attrLink.pwBaseMaxAp = &PlayerProfile.avatarAttribute.wBaseMaxAp;
	attrLink.pwBaseMaxEP = &PlayerProfile.avatarAttribute.wBaseMaxEP;
	attrLink.pwBaseMaxLP = &PlayerProfile.avatarAttribute.wBaseMaxLP;
	attrLink.pwBaseMaxRP = &PlayerProfile.avatarAttribute.wBaseMaxRP;
	attrLink.pwBasePhysicalCriticalRate = &PlayerProfile.avatarAttribute.wBasePhysicalCriticalRate;
	attrLink.pwBasePhysicalDefence = &PlayerProfile.avatarAttribute.wBasePhysicalDefence;
	attrLink.pwBasePhysicalOffence = &PlayerProfile.avatarAttribute.wBasePhysicalOffence;

	attrLink.pwBaseRpRegen = &PlayerProfile.avatarAttribute.wBaseRpRegen;
	attrLink.pwCandyToleranceRate = &PlayerProfile.avatarAttribute.wCandyToleranceRate;
	attrLink.pwConfuseToleranceRate = &PlayerProfile.avatarAttribute.wConfuseToleranceRate;
	attrLink.pwGuardRate = &PlayerProfile.avatarAttribute.wGuardRate;
	attrLink.pwLastApBattleRegen = &PlayerProfile.avatarAttribute.wLastApBattleRegen;
	attrLink.pwLastApRegen = &PlayerProfile.avatarAttribute.wLastApRegen;
	attrLink.pwLastApSitdownRegen = &PlayerProfile.avatarAttribute.wLastApSitdownRegen;
	attrLink.pwLastAttackRate = &PlayerProfile.avatarAttribute.wLastAttackRate;
	attrLink.pwLastAttackSpeedRate = &PlayerProfile.avatarAttribute.wLastAttackSpeedRate;
	attrLink.pwLastBlockRate = &PlayerProfile.avatarAttribute.wLastBlockRate;
	attrLink.pwLastCurseSuccessRate = &PlayerProfile.avatarAttribute.wLastCurseSuccessRate;
	attrLink.pwLastCurseToleranceRate = &PlayerProfile.avatarAttribute.wLastCurseToleranceRate;
	attrLink.pwLastDodgeRate = &PlayerProfile.avatarAttribute.wLastDodgeRate;
	attrLink.pwLastEnergyCriticalRate = &PlayerProfile.avatarAttribute.wLastEnergyCriticalRate;
	attrLink.pwLastEnergyDefence = &PlayerProfile.avatarAttribute.wLastEnergyDefence;
	attrLink.pwLastEnergyOffence = &PlayerProfile.avatarAttribute.wLastEnergyOffence;
	attrLink.pwLastEpBattleRegen = &PlayerProfile.avatarAttribute.wLastEpBattleRegen;
	attrLink.pwLastEpRegen = &PlayerProfile.avatarAttribute.wLastEpRegen;
	attrLink.pwLastEpSitdownRegen = &PlayerProfile.avatarAttribute.wLastEpSitdownRegen;

	attrLink.pwLastLpBattleRegen = &PlayerProfile.avatarAttribute.wLastLpBattleRegen;
	attrLink.pwLastLpRegen = &PlayerProfile.avatarAttribute.wLastLpRegen;
	attrLink.pwLastLpSitdownRegen = &PlayerProfile.avatarAttribute.wLastLpSitdownRegen;
	attrLink.pwLastMaxAp = &PlayerProfile.avatarAttribute.wLastMaxAp;
	attrLink.pwLastMaxEP = &PlayerProfile.avatarAttribute.wLastMaxEP;
	attrLink.pwLastMaxLP = &PlayerProfile.avatarAttribute.wLastMaxLP;
	attrLink.pwLastMaxRP = &PlayerProfile.avatarAttribute.wLastMaxRP;
	attrLink.pwLastPhysicalCriticalRate = &PlayerProfile.avatarAttribute.wLastPhysicalCriticalRate;
	attrLink.pwLastPhysicalDefence = &PlayerProfile.avatarAttribute.wLastPhysicalDefence;
	attrLink.pwLastPhysicalOffence = &PlayerProfile.avatarAttribute.wLastPhysicalOffence;
	attrLink.pwLastRpDimimutionRate = &PlayerProfile.avatarAttribute.wLastRpDimimutionRate;
	attrLink.pwLastRpRegen = &PlayerProfile.avatarAttribute.wLastRpRegen;
	attrLink.pwParalyzeToleranceRate = &PlayerProfile.avatarAttribute.wParalyzeToleranceRate;
	attrLink.pwStoneToleranceRate = &PlayerProfile.avatarAttribute.wStoneToleranceRate;
	attrLink.pwTerrorToleranceRate = &PlayerProfile.avatarAttribute.wTerrorToleranceRate;
	
	attrLink.pwunknown6 = &PlayerProfile.avatarAttribute.unknown6;
	attrLink.pwunknown7 = &PlayerProfile.avatarAttribute.unknown7;;
	attrLink.pwunknown_rate1 = &PlayerProfile.avatarAttribute.wBaseBlockDamageRate;
	attrLink.pwunknown_rate2 = &PlayerProfile.avatarAttribute.wLastBlockDamageRate;
	attrLink.pfunknown2 = &unkFLOATField; //&PlayerProfile.avatarAttribute.unknown2;
	attrLink.pfBasePhysicalCriticalRange = &PlayerProfile.avatarAttribute.fBasePhysicalCriticalRange;
	attrLink.pfLastPhysicalCriticalRange = &PlayerProfile.avatarAttribute.fLastPhysicalCriticalRange;
	attrLink.pfBaseEnergyCriticalRange = &PlayerProfile.avatarAttribute.fBaseEnergyCriticalRange;
	attrLink.pfLastEnergyCriticalRange = &PlayerProfile.avatarAttribute.fLastEnergyCriticalRange;
	attrLink.unknown3_0 = &PlayerProfile.avatarAttribute.unknown3_0;
	attrLink.unknown3_1 = &PlayerProfile.avatarAttribute.unknown3_1;
	attrLink.unknown3_2 = &PlayerProfile.avatarAttribute.unknown3_2;
	attrLink.unknown3_3 = &PlayerProfile.avatarAttribute.baseSkillSpeed;
	attrLink.SkillSpeed = &PlayerProfile.avatarAttribute.SkillSpeed;
	attrLink.unknown3_5 = &PlayerProfile.avatarAttribute.baseMaxWeight;
	attrLink.MaxWeight = &PlayerProfile.avatarAttribute.MaxWeight;
	attrLink.unknown3_w6 = &PlayerProfile.avatarAttribute.unknown3_w6;
	attrLink.pfHtbBlockModeSuccessRate = &PlayerProfile.avatarAttribute.fHtbBlockModeSuccessRate;
	attrLink.pfSitDownLpRegenBonusRate = &PlayerProfile.avatarAttribute.fSitDownLpRegenBonusRate;
	attrLink.pfSitDownEpRegenBonusRate = &PlayerProfile.avatarAttribute.fSitDownEpRegenBonusRate;
	attrLink.pfPhysicalCriticalDamageBonusRate = &PlayerProfile.avatarAttribute.fPhysicalCriticalDamageBonusRate;
	attrLink.unknown3_11 = &PlayerProfile.avatarAttribute.unknown3_11;
	attrLink.unknown3_12 = &PlayerProfile.avatarAttribute.unknown3_12;
	attrLink.unknown3_13 = &PlayerProfile.avatarAttribute.unknown3_13;
	attrLink.unknown4_0 = &PlayerProfile.avatarAttribute.unknown4_0;
	attrLink.unknown4_1 = &PlayerProfile.avatarAttribute.unknown4_1;
	attrLink.basePhysicalCriticalDefenceRate = &PlayerProfile.avatarAttribute.basePhysicalCriticalDefenceRate;
	attrLink.baseEnergyCriticalDefenceRate = &PlayerProfile.avatarAttribute.baseEnergyCriticalDefenceRate;
	attrLink.lastPhysicalCriticalDefenceRate = &PlayerProfile.avatarAttribute.lastPhysicalCriticalDefenceRate;
	attrLink.lastEnergyCriticalDefenceRate = &PlayerProfile.avatarAttribute.lastEnergyCriticalDefenceRate;
	attrLink.unknown4_6 = &PlayerProfile.avatarAttribute.unknown4_6;
	attrLink.unknown5_0 = &PlayerProfile.avatarAttribute.unknown5_0;
	attrLink.unknown5_1 = &PlayerProfile.avatarAttribute.unknown5_1;
	attrLink.unknown5_2 = &PlayerProfile.avatarAttribute.unknown5_2;
	attrLink.unknown5_3 = &PlayerProfile.avatarAttribute.unknown5_3;
	attrLink.unknown5_4 = &PlayerProfile.avatarAttribute.unknown5_4;
	attrLink.unknown5_5 = &PlayerProfile.avatarAttribute.unknown5_5;
}
//----------------------------------------
//	Determine what bit flag are to be updated
//----------------------------------------
bool AttributesManager::SaveAvatarAttribute(void* pvBuffer, DWORD* pwdDataSize)
{
	BYTE* pbyBuffer = (BYTE*)pvBuffer;
	BYTE* pbyAttributeDataLink = (BYTE*)&attrLink;

	*pwdDataSize = 0;

	::CopyMemory(pbyBuffer, changedFlag.GetRawData(), changedFlag.GetBytesUsed());

	pbyBuffer += changedFlag.GetBytesUsed();
	*pwdDataSize += changedFlag.GetBytesUsed();

	for (BYTE byIndex = ATTRIBUTE_TO_UPDATE_FIRST; byIndex <= ATTRIBUTE_TO_UPDATE_LAST; byIndex++)
	{
		if (false != changedFlag.IsSet(byIndex))
		{
			void* pvAttributeFieldLink = *((void**)(pbyAttributeDataLink + byIndex * sizeof(void*)));
			if (NULL == pvAttributeFieldLink)
			{
				continue;
			}
			DWORD dwDataSize = CNtlAvatar::GetInstance()->m_attributeLogic[byIndex].pCopyAttributeFunction(pvAttributeFieldLink, pbyBuffer);
			if (0 == dwDataSize)
			{
				return false;
			}
			else
			{
				pbyBuffer += dwDataSize;
				*pwdDataSize += dwDataSize;
			}
			changedFlag.Unset(byIndex);
		}
	}

	return true;
}
//----------------------------------------
// Buff list 
//----------------------------------------
//Add a new buff
void AttributesManager::AddBuff(BuffTimeInfo buff)
{
	vBuffTimeInfo.push_back(buff);
}

void AttributesManager::DeleteBuff(TBLIDX buffIdx)
{
	typedef std::vector<BuffTimeInfo> BuffList;
	typedef BuffList::const_iterator BuffListIt;

	const BuffTimeInfo* buff = nullptr;
	for (BuffListIt iter = vBuffTimeInfo.cbegin(); iter != vBuffTimeInfo.cend(); ++iter)
	{
		buff = &(*iter);

		if (buff == nullptr)
		{
			continue;
		}

		sLog.outDebug("Buff id %d", buff->BuffID);

		if (buff->BuffID == buffIdx)
		{
			//GetAttributesManager()->questSubCls.objData[index].mobsTblidx.erase(iter);
			vBuffTimeInfo.erase(iter);
			sLog.outDebug("Buff deleted");
			break;
		}
	}
}

BuffTimeInfo* AttributesManager::GetBuff(TBLIDX buffIdx)
{
	for (int i = 0; i < vBuffTimeInfo.size(); i++)
	{
		if (vBuffTimeInfo[i].BuffID == buffIdx)
		{
			return &vBuffTimeInfo[i];
		}
	}
	return NULL;
}
//----------------------------------------
// Effect list
//----------------------------------------
float AttributesManager::AddAttrEffect(WORD effectType, float value)
{
	ATTR_EFFECTSIT iter2;
	iter2 = effectsApplied.find(effectType);
	if (effectsApplied.end() == iter2)
	{
		effectsApplied[effectType] = std::vector<float>();
		effectsApplied[effectType].push_back(value);
	}
	else
	{
		effectsApplied[effectType].push_back(value);
	}
	sLog.outDebug("Attr effect added type %d value %f size %d", effectType, value, effectsApplied[effectType].size());
	return value;
}

float AttributesManager::DeleteAttrEffect(WORD effectType, float value)
{
	typedef std::vector<float> EffectList;
	typedef EffectList::const_iterator EffectListIt;

	float effect = 0xffffffff;
	for (EffectListIt iter = effectsApplied[effectType].cbegin(); iter != effectsApplied[effectType].cend(); ++iter)
	{
		effect = (*iter);

		if (effect == 0xffffffff)
		{
			continue;
		}

		sLog.outDebug("Effect type %d value %f", effectType, value);

		if (effect == value)
		{
			//GetAttributesManager()->questSubCls.objData[index].mobsTblidx.erase(iter);
			effectsApplied[effectType].erase(iter);
			sLog.outDebug("Effect deleted");
			return value*-1;
		}
	}
	return 0.0f;
}

float AttributesManager::GetAttrEffectByType(WORD effectType, float value, bool addRemove)
{
	// Add
	if (addRemove)
	{
		return AddAttrEffect(effectType, value);
	}
	else
	{
		return DeleteAttrEffect(effectType, value);
	}
}

std::vector<float> AttributesManager::GetAttrEffects(WORD effectType)
{
	return effectsApplied[effectType];
}

float AttributesManager::SetAllEffects(WORD actEffectUp, WORD actEffectDown, WORD pasEffectType, float originalValue)
{
	float newValue = originalValue;
	for (int i = 0; i < effectsApplied[actEffectUp].size(); i++)
	{
		newValue += effectsApplied[actEffectUp][i];
		sLog.outBasic("active value original %f effectApplied %f effectType %d", originalValue, effectsApplied[actEffectUp][i], actEffectUp);
	}
	for (int i = 0; i < effectsApplied[actEffectDown].size(); i++)
	{
		newValue += effectsApplied[actEffectDown][i];
		sLog.outBasic("original value2 original %f effectApplied %f effectType %d", originalValue, effectsApplied[actEffectDown][i], actEffectDown);
	}
	for (int i = 0; i < effectsApplied[pasEffectType].size(); i++)
	{
		newValue += effectsApplied[pasEffectType][i];
		sLog.outBasic("original value2 original %f effectApplied %f effectType %d", originalValue, effectsApplied[pasEffectType][i], pasEffectType);
	}
	sLog.outBasic("total effect %f", newValue);
	return newValue;
}
//----------------------------------------
// Mob list for spin attack
//----------------------------------------
// Check if object is in list
bool AttributesManager::IsInListSpin(HOBJECT hTarget)
{
	for (int i = 0; i < spinInfo.enemyList.size(); i++)
	{
		if (spinInfo.enemyList[i]->GetHandle() == hTarget)
		{
			return true;
		}
	}
	return false;
}
// Add an enemy in list
void AttributesManager::AddEnemyToSpinList(Object* enemy)
{
	spinInfo.enemyList.push_back(enemy);
	sLog.outBasic("Enemy spin added");
}

// Delete enemy from list
void AttributesManager::DeleteEnemy(HOBJECT hTarget)
{
	typedef std::vector<Object*> EnemyList;
	typedef EnemyList::const_iterator EnemyListIt;

	const Object* enemy = nullptr;
	for (EnemyListIt iter = spinInfo.enemyList.cbegin(); iter != spinInfo.enemyList.cend(); ++iter)
	{
		enemy = (*iter);

		if (enemy == nullptr)
		{
			continue;
		}

		sLog.outDebug("Enemy spin handle %d type %d", enemy->GetHandle(), enemy->GetTypeId());

		if (enemy->GetHandle() == hTarget)
		{
			//GetAttributesManager()->questSubCls.objData[index].mobsTblidx.erase(iter);
			spinInfo.enemyList.erase(iter);
			sLog.outDebug("Enemy spin Deleted");
			break;
		}
	}
}

//----------------------------------------
//	Calcule basic stats  str, con, foc, dex, sol, eng
//----------------------------------------
int AttributesManager::CalculeBasicStats(WORD basicStat, float basicStatLvUp, BYTE playerLevel)
{
	sLog.outBasic("basicStat %d, statLvUp %f playerLevel %d", basicStat, basicStatLvUp, playerLevel);
	return static_cast<float>(basicStat) + (basicStatLvUp * (static_cast<float>(playerLevel) - 1.0f));
}

DWORD AttributesManager::CalculeLP(BYTE pcClass, int lastCon)
{
	DWORD LP = 0;
	CLASS_INFO* classInfo = sTBM.GetFormulaTable()->FindClassInfoByClass(pcClass);
	if (classInfo)
	{
		sLog.outBasic("Class %d lp rate tblidx %d", pcClass, classInfo->LP);
		sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(classInfo->LP);
		if (formula)
		{
			LP = formula->afRate[0] + (lastCon * formula->afRate[1]);
			sLog.outBasic("LP total %d rate1 %f rate2 %f lastCon %d", LP, formula->afRate[0], formula->afRate[1], lastCon);
		}
	}
	return LP;
}

WORD AttributesManager::CalculeEP(BYTE pcClass, int lastEng)
{
	WORD EP = 0;
	CLASS_INFO* classInfo = sTBM.GetFormulaTable()->FindClassInfoByClass(pcClass);
	if (classInfo)
	{
		sLog.outBasic("Class %d ep rate tblidx %d", pcClass, classInfo->EP);
		sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(classInfo->EP);
		if (formula)
		{
			EP = formula->afRate[0] + (lastEng * formula->afRate[1]);
			sLog.outBasic("EP total %d rate1 %f rate2 %f lastEng %d", EP, formula->afRate[0], formula->afRate[1], lastEng);
		}
	}
	return EP;
}

int AttributesManager::CalculeRP(BYTE playerLevel)
{
	int RP = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(2300);
	if (formula)
	{
		// = fRate1 + Level * fRate2
		RP = formula->afRate[0] + (playerLevel * formula->afRate[1]);
		sLog.outBasic("RP total %d rate1 %f rate2 %f", RP, formula->afRate[0], formula->afRate[1]);
	}
	return RP;
}

WORD AttributesManager::CalculePhysicalOffence(BYTE pcClass, BYTE playerLevel, int lastStr, int lastDex)
{
	// = LV* fRate1 + (Last_Str * fRate2) + (Last_Dex * fRate3) - fRate4
	WORD PhysicalOffence = 0;
	CLASS_INFO* classInfo = sTBM.GetFormulaTable()->FindClassInfoByClass(pcClass);
	if (classInfo)
	{
		sLog.outBasic("Class %d Physical_Offence rate tblidx %d lastStr %d lastDex %d", pcClass, classInfo->Physical_Offence, lastStr, lastDex);
		sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(classInfo->Physical_Offence);
		if (formula)
		{
			PhysicalOffence = playerLevel * formula->afRate[0] + (lastStr * formula->afRate[1]) + (lastDex * formula->afRate[2]) - formula->afRate[3];
			sLog.outBasic("PhysicalOffence total %d rate1 %f rate2 %f rate3 %f rate4 %f", 
				PhysicalOffence, formula->afRate[0], formula->afRate[1], formula->afRate[2], formula->afRate[3]);
		}
	}
	return PhysicalOffence;
}

WORD AttributesManager::CalculeEnergyOffence(BYTE pcClass, BYTE playerLevel, int lastSol, int lastFoc)
{
	//  = LV* fRate1 + (Last_Sol * fRate2) + (Last_Foc * fRate3) - fRate4
	WORD EnergyOffence = 0;
	CLASS_INFO* classInfo = sTBM.GetFormulaTable()->FindClassInfoByClass(pcClass);
	if (classInfo)
	{
		sLog.outBasic("Class %d Energy_Offence rate tblidx %d lastSol %d lastFoc %d", pcClass, classInfo->Energy_Offence, lastSol, lastFoc);
		sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(classInfo->Energy_Offence);
		if (formula)
		{
			EnergyOffence = playerLevel * formula->afRate[0] + (lastSol * formula->afRate[1]) + (lastFoc * formula->afRate[2]) - formula->afRate[3];
			sLog.outBasic("EnergyOffence total %d rate1 %f rate2 %f rate3 %f rate4 %f",
				EnergyOffence, formula->afRate[0], formula->afRate[1], formula->afRate[2], formula->afRate[3]);
		}
	}
	return EnergyOffence;
}

WORD AttributesManager::CalculePhysicalCriticalRate(BYTE pcClass, int lastDex)
{
	//  = fRate1 + (Last_Dex / fRate2) 
	WORD PhysicalCriticalRate = 0;
	CLASS_INFO* classInfo = sTBM.GetFormulaTable()->FindClassInfoByClass(pcClass);
	if (classInfo)
	{
		sLog.outBasic("Class %d PhysicalCriticalRate rate tblidx %d lastDex %d", pcClass, classInfo->Physical_Critical_Rate, lastDex);
		sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(classInfo->Physical_Critical_Rate);
		if (formula)
		{
			PhysicalCriticalRate = formula->afRate[0] + (lastDex / formula->afRate[1]);
			sLog.outBasic("PhysicalCriticalRate total %d rate1 %f rate2 %f", PhysicalCriticalRate, formula->afRate[0], formula->afRate[1]);
		}
	}
	return PhysicalCriticalRate;
}

WORD AttributesManager::CalculeEnergyCriticalRate(BYTE pcClass, int lastFoc)
{
	// = fRate1 + (Last_Foc / fRate2)
	WORD EnergyCriticalRate = 0;
	CLASS_INFO* classInfo = sTBM.GetFormulaTable()->FindClassInfoByClass(pcClass);
	if (classInfo)
	{
		sLog.outBasic("Class %d EnergyCriticalRate rate tblidx %d lastFoc %d", pcClass, classInfo->Energy_Critical_Rate, lastFoc);
		sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(classInfo->Energy_Critical_Rate);
		if (formula)
		{
			EnergyCriticalRate = formula->afRate[0] + (lastFoc / formula->afRate[1]);
			sLog.outBasic("EnergyCriticalRate total %d rate1 %f rate2 %f", EnergyCriticalRate, formula->afRate[0], formula->afRate[1]);
		}
	}
	return EnergyCriticalRate;
}
// Attack rate
WORD AttributesManager::CalculeHitRate(int lastFoc)
{
	// = (Last_Foc / fRate1) * fRate2
	WORD HitRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(600);
	if (formula)
	{
		sLog.outBasic("HitRate tblidx %d lastFoc %d", formula->tblidx, lastFoc);
		HitRate = (lastFoc / formula->afRate[0]) * formula->afRate[1];
		sLog.outBasic("HitRate total %d rate1 %f rate2 %f", HitRate, formula->afRate[0], formula->afRate[1]);
	}
	return HitRate;
}

WORD AttributesManager::CalculeDodgeRate(int lastDex)
{
	// = (Last_Foc / fRate1) * fRate2
	WORD DodgeRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(800);
	if (formula)
	{
		sLog.outBasic("DodgeRate tblidx %d lastDex %d", formula->tblidx, lastDex);
		DodgeRate = (lastDex / formula->afRate[0]) * formula->afRate[1];
		sLog.outBasic("DodgeRate total %d rate1 %f rate2 %f", DodgeRate, formula->afRate[0], formula->afRate[1]);
	}
	return DodgeRate;
}

WORD AttributesManager::CalculeBlockRate(int lastDex, int lastCon)
{
	//  = fRate1 + (Last_Dex * fRate2) + (Last_Con * fRate3)
	WORD BlockRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(900);
	if (formula)
	{
		sLog.outBasic("BlockRate tblidx %d lastDex %d lastCon %d", formula->tblidx, lastDex, lastCon);
		BlockRate = formula->afRate[0] + (lastDex * formula->afRate[1]) + (lastCon * formula->afRate[2]);
		sLog.outBasic("BlockRate total %d rate1 %f rate2 %f rate3 %f", BlockRate, formula->afRate[0], formula->afRate[1], formula->afRate[2]);
	}
	return BlockRate;
}

WORD AttributesManager::CalculePhysicalCriticalDefenceRate(int lastCon)
{
	// = fRate1 + (Last_Con / fRate2)
	WORD criticalDefenseRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(9100);
	if (formula)
	{
		sLog.outBasic("CharacterPhysicalCriticalDefenseRate tblidx %d lastCon %d", formula->tblidx, lastCon);
		criticalDefenseRate = formula->afRate[0] + (lastCon / formula->afRate[1]);
		sLog.outBasic("CharacterPhysicalCriticalDefenseRate total %d rate1 %f rate2 %f", criticalDefenseRate, formula->afRate[0], formula->afRate[1]);
	}
	return criticalDefenseRate;
}

WORD AttributesManager::CalculeEnergyCriticalDefenceRate(int lastEng)
{
	// = fRate1 + (Last_Con / fRate2)
	WORD criticalDefenseRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(9200);
	if (formula)
	{
		sLog.outBasic("CharacteEnergyCriticalDefenseRate tblidx %d lastEng %d", formula->tblidx, lastEng);
		criticalDefenseRate = formula->afRate[0] + (lastEng / formula->afRate[1]);
		sLog.outBasic("CharacteEnergyCriticalDefenseRate total %d rate1 %f rate2 %f", criticalDefenseRate, formula->afRate[0], formula->afRate[1]);
	}
	return criticalDefenseRate;
}

float AttributesManager::CalculePhysicalCriticalRange(BYTE pcClass, int lastDex)
{
	//  = fRate1 + (Last_Dex / fRate2)
	float physicalCriticalRange = 0;
	CLASS_INFO* classInfo = sTBM.GetFormulaTable()->FindClassInfoByClass(pcClass);
	if (classInfo)
	{
		sLog.outBasic("Class %d physicalCriticalRange rate tblidx %d lastDex %d", pcClass, classInfo->Physical_Critical_Range, lastDex);
		sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(classInfo->Physical_Critical_Range);
		if (formula)
		{
			physicalCriticalRange = formula->afRate[0] + (lastDex / formula->afRate[1]);
			sLog.outBasic("physicalCriticalRange total %f rate1 %f rate2 %f", physicalCriticalRange, formula->afRate[0], formula->afRate[1]);
		}
	}
	return physicalCriticalRange;
}

float AttributesManager::CalculeEnergyCriticalRange(BYTE pcClass, int lastFoc)
{
	// = fRate1 + (Last_Foc / fRate2)
	float energyCriticalRange = 0;
	CLASS_INFO* classInfo = sTBM.GetFormulaTable()->FindClassInfoByClass(pcClass);
	if (classInfo)
	{
		sLog.outBasic("Class %d energyCriticalRange rate tblidx %d lastFoc %d", pcClass, classInfo->Energy_Critical_Range, lastFoc);
		sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(classInfo->Energy_Critical_Range);
		if (formula)
		{
			energyCriticalRange = formula->afRate[0] + (lastFoc / formula->afRate[1]);
			sLog.outBasic("energyCriticalRange total %f rate1 %f rate2 %f", energyCriticalRange, formula->afRate[0], formula->afRate[1]);
		}
	}
	return energyCriticalRange;
}

WORD AttributesManager::CalculeLPRegeneration(int lastCon)
{
	// = (fRate4 초당) fRate1 + (Last_Con * fRate2) (cada fRate4 segundos)
	WORD LpRegen;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(300);
	if (formula)
	{
		LpRegen = formula->afRate[0] + (lastCon * formula->afRate[1]);
		sLog.outBasic("LpRegen total %d rate1 %f rate2 %f lastCon %d every %f seconds", 
			LpRegen, formula->afRate[0], formula->afRate[1], lastCon, formula->afRate[3]);
	}
	return LpRegen;
}

WORD AttributesManager::CalculeLPSitDownRegeneration(WORD lastLpRegeneration)
{
	// = (fRate4 초당) Last_LP_Regeneration * fRate1 (cada fRate4 segundos)
	WORD lpSitdDownRegen;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(400);
	if (formula)
	{
		lpSitdDownRegen = lastLpRegeneration * formula->afRate[0];
		sLog.outBasic("lpSitdDownRegen total %d rate1 %f lastLpRegeneration %d every %f seconds",
			lpSitdDownRegen, formula->afRate[0], lastLpRegeneration, formula->afRate[3]);
	}
	return lpSitdDownRegen;
}

WORD AttributesManager::CalculeEPRegeneration(int lastEng)
{
	//  = (fRate4 초당) fRate1 + (Last_Eng * fRate2) (cada fRate4 segundos)
	WORD EpRegen;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(1400);
	if (formula)
	{
		EpRegen = formula->afRate[0] + (lastEng * formula->afRate[1]);
		sLog.outBasic("EpRegen total %d rate1 %f rate2 %f lastEng %d every %f seconds",
			EpRegen, formula->afRate[0], formula->afRate[1], lastEng, formula->afRate[3]);
	}
	return EpRegen;
}

WORD AttributesManager::CalculeEPSitDownRegeneration(WORD lastEpRegeneration)
{
	// = (fRate4 초당) Last_EP_Regeneration * fRate1 (cada fRate4 segundos)
	WORD epSitdDownRegen;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(1500);
	if (formula)
	{
		epSitdDownRegen = lastEpRegeneration * formula->afRate[0];
		sLog.outBasic("epSitdDownRegen total %d rate1 %f lastEpRegeneration %d every %f seconds",
			epSitdDownRegen, formula->afRate[0], lastEpRegeneration, formula->afRate[3]);
	}
	return epSitdDownRegen;
}

WORD AttributesManager::CalculeEPBattleRegeneration(WORD lastEpRegeneration)
{
	// = (fRate4 초당) Last_EP_Regeneration * fRate1(cada fRate4 segundos)
	WORD epBattleRegen;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(1600);
	if (formula)
	{
		epBattleRegen = lastEpRegeneration * formula->afRate[0];
		sLog.outBasic("epBattleRegen total %d rate1 %f lastEpRegeneration %d every %f seconds",
			epBattleRegen, formula->afRate[0], lastEpRegeneration, formula->afRate[3]);
	}
	return epBattleRegen;
}

WORD AttributesManager::CalculeRPRegeneration(WORD maxRP)
{
	// = (fRate4 초당) fRate1+ (Last_Max_RP * fRate2) (cada fRate4 segundos)
	WORD rpRegen;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(2400);
	if (formula)
	{
		rpRegen = formula->afRate[0] + (maxRP * formula->afRate[1]);
		sLog.outBasic("rpRegen total %d rate1 %f maxRP %d every %f seconds",
			rpRegen, formula->afRate[0], maxRP, formula->afRate[3]);
	}
	return rpRegen;
}

WORD AttributesManager::CalculeRPDiminution(WORD maxRP)
{
	// = (fRate4 초당) fRate1+ (Last_Max_RP * fRate2) (cada fRate4 segundos)
	WORD rpDiminution;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(2500);
	if (formula)
	{
		rpDiminution = formula->afRate[0] + (maxRP * formula->afRate[1]);
		sLog.outBasic("rpDiminution total %d rate1 %f maxRP %d every %f seconds",
			rpDiminution, formula->afRate[0], maxRP, formula->afRate[3]);
	}
	return rpDiminution;
}

WORD AttributesManager::CalculeRPHitCharge(BYTE deffLevel, BYTE attLevel)
{
	//= fRate1 - (fRate2 * min(max((방어자 Level - 공격자 Level), 0), 5))
	WORD rpHitCharge;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(2600);
	if (formula)
	{
		rpHitCharge = formula->afRate[0] - (formula->afRate[1] * min(max(static_cast<float>(deffLevel - attLevel), 0), 5));
		sLog.outBasic("rpHitCharge total %d rate1 %f rate2 %d deffLevel %d attLevel %d",
			rpHitCharge, formula->afRate[0], formula->afRate[1], deffLevel, attLevel);
	}
	return rpHitCharge;
}

WORD AttributesManager::CalculeRPHitChargeRate(BYTE deffLevel, BYTE attLevel)
{
	WORD hitRpChargeRate = 50 - (deffLevel - attLevel);
	sLog.outBasic("hitRpChargeRate total %d deffLevel %d attLevel %d", hitRpChargeRate, deffLevel, attLevel);
	return hitRpChargeRate;
}

WORD AttributesManager::CalculeCurseSuccessRate(int lastFoc)
{
	//= (Last_Foc / fRate1) * fRate2
	WORD curseSuccessRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(700);
	if (formula)
	{
		curseSuccessRate = (lastFoc / formula->afRate[0]) * formula->afRate[1];
		sLog.outBasic("curseSuccessRate total %d rate1 %f rate2 %f lastFoc %d", curseSuccessRate, formula->afRate[0], formula->afRate[1], lastFoc);
	}
	return curseSuccessRate;
}

WORD AttributesManager::CalculeCurseToleranceRate(int lastDex)
{
	//= (Last_Dex / fRate1) * fRate2
	WORD curseToleranceRate = 0;
	sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(1200);
	if (formula)
	{
		curseToleranceRate = (lastDex / formula->afRate[0]) * formula->afRate[1];
		sLog.outBasic("curseToleranceRate total %d rate1 %f rate2 %f lastDex %d", curseToleranceRate, formula->afRate[0], formula->afRate[1], lastDex);
	}
	return curseToleranceRate;
}

float AttributesManager::GetPercent(float percent, float value)
{
	return percent * value / 100.0f;
}

// Update phyicalOffence
void AttributesManager::UpdateStr(WORD effectType, int lastStr, bool add, bool addRemove)
{
	if (add)
	{
		int totalStr = GetAttrEffectByType(effectType, lastStr, addRemove);
		AddLastStr(totalStr);
	}
	else
	{
		int totalStr = SetAllEffects(ACTIVE_STR_UP, ACTIVE_STR_DOWN, PASSIVE_STR_UP, lastStr);
		SetLastStr(totalStr);
	}

	WORD PhysicalOffence = CalculePhysicalOffence(plr->GetMyClass(), PlayerProfile.byLevel, 
		PlayerProfile.avatarAttribute.byLastStr, PlayerProfile.avatarAttribute.byLastDex);
	UpdatePhysicalOffence(PhysicalOffence, false);
}
// Update LP, blockRate, physicalCriticalDefenceRate
void AttributesManager::UpdateCon(WORD effectType, int lastCon, bool add, bool addRemove)
{
	if (add)
	{
		int totalCon = GetAttrEffectByType(effectType, lastCon, addRemove);
		AddLastCon(totalCon);
	}
	else
	{
		int totalCon = SetAllEffects(ACTIVE_CON_UP, ACTIVE_CON_DOWN, PASSIVE_CON_UP, lastCon);
		SetLastCon(totalCon);
	}

	DWORD LP = CalculeLP(plr->GetMyClass(), PlayerProfile.avatarAttribute.byLastCon);
	WORD BlockRate = CalculeBlockRate(PlayerProfile.avatarAttribute.byLastDex, PlayerProfile.avatarAttribute.byLastCon);
	WORD PhysicalCriticalDefenceRate = CalculePhysicalCriticalDefenceRate(PlayerProfile.avatarAttribute.byLastCon);
	WORD LpRegen = CalculeLPRegeneration(PlayerProfile.avatarAttribute.byLastCon);

	UpdateLP(LP, false);
	UpdateBlockRate(BlockRate, false);
	UpdatePhysicalCriticalDefenceRate(PhysicalCriticalDefenceRate, false);
	UpdateLPRegeneration(LpRegen, false);
}
// Update energyOffence, energyCriticalRate, hitRate(attackRateattackRate), energyCriticalRange, curseSuccessRate
void AttributesManager::UpdateFoc(WORD effectType, int lastFoc, bool add, bool addRemove)
{
	if (add)
	{
		int totalFoc = GetAttrEffectByType(effectType, lastFoc, addRemove);
		AddLastFoc(totalFoc);
	}
	else
	{
		int totalFoc = SetAllEffects(ACTIVE_FOC_UP, ACTIVE_FOC_DOWN, PASSIVE_FOC_UP, lastFoc);
		SetLastFoc(totalFoc);
	}

	WORD energyOffence = CalculeEnergyOffence(plr->GetMyClass(), PlayerProfile.byLevel, 
		PlayerProfile.avatarAttribute.byLastSol, PlayerProfile.avatarAttribute.byLastFoc);
	WORD energyCriticalRate = CalculeEnergyCriticalRate(plr->GetMyClass(), PlayerProfile.avatarAttribute.byLastFoc);
	WORD hitRate = CalculeHitRate(PlayerProfile.avatarAttribute.byLastFoc);
	float energyCriticalRange = CalculeEnergyCriticalRange(plr->GetMyClass(), PlayerProfile.avatarAttribute.byLastFoc);
	WORD curseSuccessRat = CalculeCurseSuccessRate(PlayerProfile.avatarAttribute.byLastFoc);

	UpdateEnergyOffence(energyOffence, false);
	UpdateEnergyCriticalRate(energyCriticalRate, false);
	UpdateHitRate(hitRate, false);
	UpdateEnergyCriticalRange(energyCriticalRange, false);
	UpdateCurseSuccessRate(curseSuccessRat, false);
}
// Update physicalOffence, physicalCriticalRate, dodgeRate, blockRate, physicalCriticalRange, curseToleranceRate
void AttributesManager::UpdateDex(WORD effectType, int lastDex, bool add, bool addRemove)
{
	if (add)
	{
		int totalDex = GetAttrEffectByType(effectType, lastDex, addRemove);
		AddLastDex(totalDex);
	}
	else
	{
		int totalDex = SetAllEffects(ACTIVE_DEX_UP, ACTIVE_DEX_DOWN, PASSIVE_DEX_UP, lastDex);
		SetLastDex(totalDex);
	}

	WORD physicalOffence = CalculePhysicalOffence(plr->GetMyClass(), PlayerProfile.byLevel,
		PlayerProfile.avatarAttribute.byLastStr, PlayerProfile.avatarAttribute.byLastDex);
	WORD physicalCriticalRate = CalculePhysicalCriticalRate(plr->GetMyClass(), PlayerProfile.avatarAttribute.byLastDex);
	WORD dodgeRate = CalculeDodgeRate(PlayerProfile.avatarAttribute.byLastDex);
	WORD blockRate = CalculeBlockRate(PlayerProfile.avatarAttribute.byLastDex, PlayerProfile.avatarAttribute.byLastCon);
	float physicalCriticalRange = CalculePhysicalCriticalRange(plr->GetMyClass(), PlayerProfile.avatarAttribute.byLastDex);
	WORD curseToleranceRate = CalculeCurseToleranceRate(PlayerProfile.avatarAttribute.byLastDex);

	UpdatePhysicalOffence(physicalOffence, false);
	UpdatePhysicalCriticalRate(physicalCriticalRate, false);
	UpdateDodgeRate(dodgeRate, false);
	UpdateBlockRate(blockRate, false);
	UpdatePhysicalCriticalRange(physicalCriticalRange, false);
	UpdateCurseToleranceRate(curseToleranceRate, false);
}
// Update energyOffence
void AttributesManager::UpdateSol(WORD effectType, int lastSol, bool add, bool addRemove)
{
	if (add)
	{
		int totalSol = GetAttrEffectByType(effectType, lastSol, addRemove);
		AddLastSol(totalSol);
	}
	else
	{
		int totalSol = SetAllEffects(ACTIVE_SOL_UP, ACTIVE_SOL_DOWN, PASSIVE_SOL_UP, lastSol);
		SetLastSol(totalSol);
	}

	WORD energyOffence = CalculeEnergyOffence(plr->GetMyClass(), PlayerProfile.byLevel, 
		PlayerProfile.avatarAttribute.byLastSol, PlayerProfile.avatarAttribute.byLastFoc);

	UpdateEnergyOffence(energyOffence, false);
}
// Update EP EnergyCriticalDefenceRate, EPRegeneration
void AttributesManager::UpdateEng(WORD effectType, int lastEng, bool add, bool addRemove)
{
	if (add)
	{
		int totalEng = GetAttrEffectByType(effectType, lastEng, addRemove);
		AddLastEng(totalEng);
	}
	else
	{
		int totalEng = SetAllEffects(ACTIVE_ENG_UP, ACTIVE_ENG_DOWN, PASSIVE_ENG_UP, lastEng);
		SetLastEng(totalEng);
	}

	WORD EP = CalculeEP(plr->GetMyClass(), PlayerProfile.avatarAttribute.byLastEng);
	WORD energyCriticalDefenceRate = CalculeEnergyCriticalDefenceRate(PlayerProfile.avatarAttribute.byLastEng);
	WORD epRegen = CalculeEPRegeneration(PlayerProfile.avatarAttribute.byLastEng);

	UpdateEP(EP, false);
	UpdateEnergyCriticalDefenceRate(energyCriticalDefenceRate, false);
	UpdateEPRegeneration(epRegen, false);
}

void AttributesManager::UpdateLP(DWORD lp, bool add)
{
	if (add)
	{
		AddLastMaxLP(lp);
	}
	else
	{
		SetLastMaxLP(lp);
	}
}

void AttributesManager::UpdateEP(WORD ep, bool add)
{
	if (add)
	{

		AddLastMaxEP(ep);
	}
	else
	{
		SetLastMaxEP(ep);
	}
}

void AttributesManager::UpdateRP(int rp, bool add)
{
	if (add)
	{
		AddLastMaxRP(rp);
	}
	else
	{
		SetLastMaxRP(rp);
	}

	WORD RpRegen = CalculeRPRegeneration(PlayerProfile.avatarAttribute.wLastMaxRP);
	WORD RpDimimutionRate = CalculeRPDiminution(PlayerProfile.avatarAttribute.wLastMaxRP);

	UpdateRPRegeneration(RpRegen, false);
	UpdateRPDiminution(RpDimimutionRate, false);
}

void AttributesManager::UpdateRPRegeneration(WORD RPRegen, bool add) 
{
	if (add)
	{
		AddLastRpRegen(RPRegen);
	}
	else
	{
		SetLastRpRegen(RPRegen);
	}
}

void AttributesManager::UpdateRPDiminution(WORD RPDimin, bool add)
{
	if (add)
	{
		AddLastRpDimimution(RPDimin);
	}
	else
	{
		SetLastRpDimimution(RPDimin);
	}
}

void AttributesManager::UpdatePhysicalOffence(WORD physicalOffence, bool add)
{
	if (add)
	{
		AddLastPhysicalOffence(physicalOffence);
	}
	else
	{
		SetLastPhysicalOffence(physicalOffence);
	}
}

void AttributesManager::UpdatePhysicalDefence(WORD physicalDefence, bool add)
{
	if (add)
	{
		AddLastPhysicalDefence(physicalDefence);
	}
	else
	{
		SetLastPhysicalDefence(physicalDefence);
	}
}

void AttributesManager::UpdateEnergyOffence(WORD energyOffence, bool add)
{
	if (add)
	{
		AddLastEnergyOffence(energyOffence);
	}
	else
	{
		SetLastEnergyOffence(energyOffence);
	}
}

void AttributesManager::UpdateEnergyDefence(WORD energyDefence, bool add)
{
	if (add)
	{
		AddLastEnergyDefence(energyDefence);
	}
	else
	{
		SetLastEnergyDefence(energyDefence);
	}
}

void AttributesManager::UpdatePhysicalCriticalRate(WORD physicalCriticalRate, bool add)
{
	if (add)
	{
		AddLastPhysicalCriticalRate(physicalCriticalRate);
	}
	else
	{
		SetLastPhysicalCriticalRate(physicalCriticalRate);
	}
}

void AttributesManager::UpdateEnergyCriticalRate(WORD energyCriticalRate, bool add)
{
	if (add)
	{
		AddLastEnergyCriticalRate(energyCriticalRate);
	}
	else
	{
		SetLastEnergyCriticalRate(energyCriticalRate);
	}
}

void AttributesManager::UpdateHitRate(WORD hitRate, bool add)
{
	if (add)
	{
		AddLastAttackRate(hitRate);
	}
	else
	{
		SetLastAttackRate(hitRate);
	}
}

void AttributesManager::UpdateDodgeRate(WORD dodgeRate, bool add)
{
	if (add)
	{
		AddLastDodgeRate(dodgeRate);
	}
	else
	{
		SetLastDodgeRate(dodgeRate);
	}
}

void AttributesManager::UpdateBlockRate(WORD blockRate, bool add)
{
	if (add)
	{
		AddLastBlockRate(blockRate);
	}
	else
	{
		SetLastBlockRate(blockRate);
	}
}

void AttributesManager::UpdatePhysicalCriticalDefenceRate(WORD physicalCriticalDefenceRate, bool add)
{
	if (add)
	{
		AddLastPhysicalCriticalDefenceRate(physicalCriticalDefenceRate);
	}
	else
	{
		SetLastPhysicalCriticalDefenceRate(physicalCriticalDefenceRate);
	}
}

void AttributesManager::UpdateEnergyCriticalDefenceRate(WORD energyCriticalDefenceRate, bool add)
{
	if (add)
	{
		AddLastEnergyCriticalDefenceRate(energyCriticalDefenceRate);
	}
	else
	{
		SetLastEnergyCriticalDefenceRate(energyCriticalDefenceRate);
	}
}

void AttributesManager::UpdatePhysicalCriticalRange(float physicalCriticalRange, bool add)
{
	if (add)
	{
		AddLastPhysicalCriticalRange(physicalCriticalRange);
	}
	else
	{
		SetLastPhysicalCriticalRange(physicalCriticalRange);
	}
}

void AttributesManager::UpdateEnergyCriticalRange(float energyCriticalRange, bool add)
{
	if (add)
	{
		AddLastEnergyCriticalRange(energyCriticalRange);
	}
	else
	{
		SetLastEnergyCriticalRange(energyCriticalRange);
	}
}
// Update LPSitDownRegeneration
void AttributesManager::UpdateLPRegeneration(WORD LpRegen, bool add)
{
	if (add)
	{
		AddLastLPRegen(LpRegen);
	}
	else
	{
		SetLastLPRegen(LpRegen);
	}

	WORD lpSitDownRegen = CalculeLPSitDownRegeneration(PlayerProfile.avatarAttribute.wLastLpRegen);

	UpdateLPSitDownRegeneration(lpSitDownRegen, false);
}

void AttributesManager::UpdateLPSitDownRegeneration(WORD lpSitDownRegen, bool add)
{
	if (add)
	{
		AddLastLPSitDownRegeneration(lpSitDownRegen);
	}
	else
	{
		SetLastLPSitDownRegeneration(lpSitDownRegen);
	}
}

void AttributesManager::UpdateEPRegeneration(WORD EpRegen, bool add)
{
	if (add)
	{
		AddLastEPRegen(EpRegen);
	}
	else
	{
		SetLastEPRegen(EpRegen);
	}

	WORD EpSitDownRegen = CalculeEPSitDownRegeneration(PlayerProfile.avatarAttribute.wLastEpRegen);
	WORD EpBattleRegen = CalculeEPBattleRegeneration(PlayerProfile.avatarAttribute.wLastEpRegen);

	UpdateEPSitDownRegeneration(EpSitDownRegen, false);
	UpdateEPBattleRegeneration(EpBattleRegen, false);
}

void AttributesManager::UpdateEPSitDownRegeneration(WORD epSitDownRegen, bool add)
{
	if (add)
	{
		AddLastEPSitDownRegeneration(epSitDownRegen);
	}
	else
	{
		SetLastEPSitDownRegeneration(epSitDownRegen);
	}
}

void AttributesManager::UpdateEPBattleRegeneration(WORD epBattleRegen, bool add)
{
	if (add)
	{
		AddLastEPBattleRegeneration(epBattleRegen);
	}
	else
	{
		SetLastEPBattleRegeneration(epBattleRegen);
	}
}

void AttributesManager::UpdateCurseSuccessRate(WORD curseSuccessRate, bool add)
{
	if (add)
	{
		AddLastCurseSuccessRate(curseSuccessRate);
	}
	else
	{
		SetLastCurseSuccessRate(curseSuccessRate);
	}
}

void AttributesManager::UpdateCurseToleranceRate(WORD curseToleranceRate, bool add)
{
	if (add)
	{
		AddLastCurseToleranceRate(curseToleranceRate);
	}
	else
	{
		SetLastCurseToleranceRate(curseToleranceRate);
	}
}

void AttributesManager::UpdateRunSpeed(float runSpeed, bool add)
{
	if (add)
	{
		AddLastRunSpeed(runSpeed);
	}
	else
	{
		SetLastRunSpeed(runSpeed);
	}
}

void AttributesManager::UpdateCoolTimeChangePercent(float coolTimeChange, bool add)
{
	if (add)
	{
		AddCoolTimeChangePercent(coolTimeChange);
	}
	else
	{
		SetCoolTimeChangePercent(coolTimeChange);
	}
}

void AttributesManager::UpdateAttackspeedRate(WORD attackSpeed, bool add)
{
	if (add)
	{
		AddLastAttackSpeedRate(attackSpeed);
	}
	else
	{
		SetLastAttackSpeedRate(attackSpeed);
	}
}