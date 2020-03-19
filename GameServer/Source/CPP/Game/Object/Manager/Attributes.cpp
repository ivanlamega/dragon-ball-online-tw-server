#include <Game\Object\Manager\Attributes.h>
#include <Game\Object\Player.h>
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

		plr->GetAttributesManager()->SetLastStr(static_cast<int>(pTblData->byStr + (pTblData->fLevel_Up_Str * 1)));
		plr->GetAttributesManager()->SetLastCon(static_cast<int>(pTblData->byCon + (pTblData->fLevel_Up_Con * 1)));
		plr->GetAttributesManager()->SetLastFoc(static_cast<int>(pTblData->byFoc + (pTblData->fLevel_Up_Foc * 1)));
		plr->GetAttributesManager()->SetLastDex(static_cast<int>(pTblData->byDex + (pTblData->fLevel_Up_Dex * 1)));
		plr->GetAttributesManager()->SetLastSol(static_cast<int>(pTblData->bySol + (pTblData->fLevel_Up_Sol * 1)));
		plr->GetAttributesManager()->SetLastEng(static_cast<int>(pTblData->byEng + (pTblData->fLevel_Up_Eng * 1)));
	
		// LP Calculation
		DWORD BasicLife = pTblData->wBasic_LP + (pTblData->byLevel_Up_LP * 1);
		WORD LevelCon = pTblData->byCon + static_cast<WORD>(pTblData->fLevel_Up_Con * 1);
		float ConByPoint = 85; // 1con = 85 old tw
		DWORD LP = BasicLife + static_cast<DWORD>(LevelCon * ConByPoint);

		//EP Calculation
		WORD BasicEnergy = pTblData->wBasic_EP + (pTblData->byLevel_Up_EP * 1);
		WORD LevelEng = pTblData->byEng + static_cast<WORD>(pTblData->fLevel_Up_Eng * 1);
		float EngByPoint = 45; // 1Eng = 45 ep old tw
		WORD EP = BasicEnergy + static_cast<WORD>(LevelEng * EngByPoint);
	
		plr->GetAttributesManager()->SetLastMaxLP(LP);
		plr->GetAttributesManager()->SetLastMaxEP(EP);

		//Calculation Physical Atack
		WORD BasicPhysicalOffence = pTblData->wBasic_Physical_Offence + (pTblData->byLevel_Up_Physical_Offence * 1);
		WORD LevelStr = pTblData->byStr + static_cast<WORD>(pTblData->fLevel_Up_Str * 1);
		float StrByPoint = 1.66; // 1Str = 1.66 Physical old tw
		WORD PhysicalOffence = BasicPhysicalOffence + static_cast<WORD>(LevelStr * StrByPoint);
		//Calculation Physical Critical Atack 
		WORD BasicPhysicalCritical = 0;
		WORD LevelDex = pTblData->byDex + static_cast<WORD>(pTblData->fLevel_Up_Dex * 1);
		float DexByPoint = 0.5; // 1Dex = 1 critical old tw
		WORD PhysicalCriticalRate = BasicPhysicalCritical + static_cast<WORD>(LevelDex * DexByPoint);

		plr->GetAttributesManager()->SetLastPhysicalOffence(PhysicalOffence);
		plr->GetAttributesManager()->SetLastPhysicalCriticalRate(PhysicalCriticalRate);

		WORD BasicEnergyOffence = pTblData->wBasic_Energy_Offence + (pTblData->byLevel_Up_Energy_Offence * 1);
		WORD LevelSol = pTblData->bySol + static_cast<WORD>(pTblData->fLevel_Up_Sol * 1);
		float SolByPoint = 1.66; // 1Soul = 1.66 Physical old tw
		WORD EnergyOffence = BasicEnergyOffence + static_cast<WORD>(LevelSol * SolByPoint);
		//Calculation Energy Critical Atack
		WORD BasicEnergyCritical = 0;
		WORD LevelFoc = pTblData->byFoc + static_cast<WORD>(pTblData->fLevel_Up_Foc * 1);
		float FocByPoint = 0.5; // 1Focus = 1 pont critical 
		WORD EnergyCriticalRate = BasicEnergyCritical + static_cast<WORD>(LevelFoc * FocByPoint);

		plr->GetAttributesManager()->SetLastEnergyOffence(EnergyOffence);
		plr->GetAttributesManager()->SetLastEnergyCriticalRate(EnergyCriticalRate);
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
	memset(&PlayerProfile.avatarAttribute, 50, sizeof PlayerProfile.avatarAttribute);
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
	PlayerProfile.avatarAttribute.unknown_int16_0 = 1;
	PlayerProfile.avatarAttribute.unknown_int16_1 = 1;
	PlayerProfile.avatarAttribute.unknown_int16_2 = 1;
	PlayerProfile.avatarAttribute.unknown_int16_3 = 1;

	PlayerProfile.avatarAttribute.unknown2 = 144;
	PlayerProfile.avatarAttribute.unknown3_0 = 143;
	PlayerProfile.avatarAttribute.unknown3_1 = 142;
	PlayerProfile.avatarAttribute.fPhysicalCriticalDamageBonusRate = 141;
	PlayerProfile.avatarAttribute.unknown3_11 = 140;//
	PlayerProfile.avatarAttribute.unknown3_12 = 139;
	PlayerProfile.avatarAttribute.unknown3_13 = 138;//
	PlayerProfile.avatarAttribute.unknown3_2 = 137;
	PlayerProfile.avatarAttribute.baseSkillSpeed = 136;//
	PlayerProfile.avatarAttribute.baseMaxWeight = 135;
	PlayerProfile.avatarAttribute.MaxWeight = 2600;
	PlayerProfile.avatarAttribute.unknown3_w6 = 134; // if != 0 weight get bugged
	PlayerProfile.avatarAttribute.fHtbBlockModeSuccessRate = 133;
	PlayerProfile.avatarAttribute.fSitDownLpRegenBonusRate = 132;//
	PlayerProfile.avatarAttribute.fSitDownEpRegenBonusRate = 131;
	PlayerProfile.avatarAttribute.unknown4_0 = 130;
	PlayerProfile.avatarAttribute.unknown4_1 = 129;
	PlayerProfile.avatarAttribute.unknown4_2 = 128;
	PlayerProfile.avatarAttribute.unknown4_3 = 127;
	PlayerProfile.avatarAttribute.unknown4_4 = 126;
	PlayerProfile.avatarAttribute.unknown4_5 = 125;
	PlayerProfile.avatarAttribute.unknown4_6 = 124;
	PlayerProfile.avatarAttribute.unknown5_1 = 123;
	PlayerProfile.avatarAttribute.unknown5_0 = 122;
	PlayerProfile.avatarAttribute.unknown5_2 = 121;
	PlayerProfile.avatarAttribute.unknown5_3 = 120;
	PlayerProfile.avatarAttribute.unknown5_4 = 119;
	PlayerProfile.avatarAttribute.unknown5_5 = 118;
	PlayerProfile.avatarAttribute.unknown_float1_0 = 117;
	PlayerProfile.avatarAttribute.unknown_float1_1 = 116;
	PlayerProfile.avatarAttribute.unknown_float2_0 = 115;
	PlayerProfile.avatarAttribute.unknown_float2_1 = 114;
	PlayerProfile.avatarAttribute.unknown_rate1 = 113;
	PlayerProfile.avatarAttribute.unknown_rate2 = 112;
	// SKILL SPEED
	PlayerProfile.avatarAttribute.SkillSpeed = 100.0f;
	//LP Get up Reg
	PlayerProfile.avatarAttribute.wBaseLpRegen = 70;
	PlayerProfile.avatarAttribute.wLastLpRegen = 70;
	//LP Sit Down Reg
	PlayerProfile.avatarAttribute.wBaseLpSitdownRegen = PlayerProfile.avatarAttribute.wLastMaxLP / 100 * 3;
	PlayerProfile.avatarAttribute.wLastLpSitdownRegen = PlayerProfile.avatarAttribute.wLastMaxLP / 100 * 3;
	//LP Reg in Batle
	PlayerProfile.avatarAttribute.wBaseLpBattleRegen = 111;
	PlayerProfile.avatarAttribute.wLastLpBattleRegen = 110;
	//EP Get UP Reg
	PlayerProfile.avatarAttribute.wBaseEpRegen = 70;
	PlayerProfile.avatarAttribute.wLastEpRegen = 70;
	//EP Sit Down Reg
	PlayerProfile.avatarAttribute.wBaseEpSitdownRegen = PlayerProfile.avatarAttribute.wLastMaxEP / 100 * 3;
	PlayerProfile.avatarAttribute.wLastEpSitdownRegen = PlayerProfile.avatarAttribute.wLastMaxEP / 100 * 3;
	//EP Reg in Batle
	PlayerProfile.avatarAttribute.wBaseEpBattleRegen = 109;
	PlayerProfile.avatarAttribute.wLastEpBattleRegen = 108;
	//Rp incress rate
	PlayerProfile.avatarAttribute.wBaseRpRegen = 1;
	PlayerProfile.avatarAttribute.wLastRpRegen = 1;
	//RP diminution
	PlayerProfile.avatarAttribute.wLastRpDimimutionRate = 3;
	//Curse Sucess Rate
	PlayerProfile.avatarAttribute.wBaseCurseSuccessRate = 107;
	PlayerProfile.avatarAttribute.wLastCurseSuccessRate = 106;
	//Curse Tolerance Rate
	PlayerProfile.avatarAttribute.wBaseCurseToleranceRate = 105;
	PlayerProfile.avatarAttribute.wLastCurseToleranceRate = 104;
	//Nao sei
	PlayerProfile.avatarAttribute.fCastingTimeChangePercent = 103;
	PlayerProfile.avatarAttribute.fCoolTimeChangePercent = 102;//
	PlayerProfile.avatarAttribute.fKeepTimeChangePercent = 101;
	PlayerProfile.avatarAttribute.fDotValueChangePercent = 100;
	PlayerProfile.avatarAttribute.fDotTimeChangeAbsolute = 99;//Ep Skill Required
	
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

	PlayerProfile.avatarAttribute.fRequiredEpChangePercent = 98;
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
	PlayerProfile.avatarAttribute.wBaseApBattleRegen = 5000;//Regen In Battle AP TW
	PlayerProfile.avatarAttribute.wLastApBattleRegen = 5000;//LAst Regen in Battle Ap TW
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

	int baseStr = static_cast<int>(pTblData->byStr + (pTblData->fLevel_Up_Str * (PlayerProfile.byLevel - 1)));
	int baseCon = static_cast<int>(pTblData->byCon + (pTblData->fLevel_Up_Con * (PlayerProfile.byLevel - 1)));
	int baseFoc = static_cast<int>(pTblData->byFoc + (pTblData->fLevel_Up_Foc * (PlayerProfile.byLevel - 1)));
	int baseDex = static_cast<int>(pTblData->byDex + (pTblData->fLevel_Up_Dex * (PlayerProfile.byLevel - 1)));
	int baseSol = static_cast<int>(pTblData->bySol + (pTblData->fLevel_Up_Sol * (PlayerProfile.byLevel - 1)));
	int baseEng = static_cast<int>(pTblData->byEng + (pTblData->fLevel_Up_Eng * (PlayerProfile.byLevel - 1)));

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
	DWORD LP = 0;
	CLASS_INFO* classInfo = sTBM.GetFormulaTable()->FindClassInfoByClass(plr->GetMyClass());
	if (classInfo)
	{
		sLog.outBasic("Class %d lp rate tblidx %d", plr->GetMyClass(), classInfo->LP);
		sFORMULA_TBLDAT* formula = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(classInfo->LP);
		if (formula)
		{
			LP = formula->afRate[0] + (baseCon * formula->afRate[1]);
			sLog.outBasic("LP total %d rate1 %f rate2 %f lastCon %d", LP, formula->afRate[0], formula->afRate[1], baseCon);
		}
	}
	
	/*DWORD BasicLife = pTblData->wBasic_LP + (pTblData->byLevel_Up_LP * PlayerProfile.byLevel);
	WORD LevelCon = pTblData->byCon + static_cast<WORD>(pTblData->fLevel_Up_Con * PlayerProfile.byLevel);
	float ConByPoint = 85; // 1con = 85 old tw
	DWORD LP = BasicLife + static_cast<DWORD>(LevelCon * ConByPoint);*/

	//EP Calculation
	WORD BasicEnergy = pTblData->wBasic_EP + (pTblData->byLevel_Up_EP * PlayerProfile.byLevel);
	WORD LevelEng = pTblData->byEng + static_cast<WORD>(pTblData->fLevel_Up_Eng * PlayerProfile.byLevel);
	float EngByPoint = 45; // 1Eng = 45 ep old tw
	WORD EP = BasicEnergy + static_cast<WORD>(LevelEng * EngByPoint);

	//Set Data Base LP/ EP/ RP
	result = sDB.executes("UPDATE characters_attributes SET BaseMaxLP = '%d', BaseMaxEP = '%d', BaseMaxRP = '%d', LastMaxLP = '%d', LastMaxEP = '%d', LastMaxRP = '%d' WHERE CharacterID = '%d';",
		LP,
		static_cast<int>(EP),
		static_cast<int>(pTblData->wBasic_RP + (pTblData->byLevel_Up_RP * PlayerProfile.byLevel)),
		LP,
		static_cast<int>(EP),
		static_cast<int>(pTblData->wBasic_RP + (pTblData->byLevel_Up_RP * PlayerProfile.byLevel)),
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
	WORD BasicPhysicalOffence = pTblData->wBasic_Physical_Offence + (pTblData->byLevel_Up_Physical_Offence * PlayerProfile.byLevel);
	WORD LevelStr = pTblData->byStr + static_cast<WORD>(pTblData->fLevel_Up_Str * PlayerProfile.byLevel);
	float StrByPoint = 1.66; // 1Str = 1.66 Physical old tw
	WORD PhysicalOffence = BasicPhysicalOffence + static_cast<WORD>(LevelStr * StrByPoint);
	//Calculation Physical Critical Atack 
	WORD BasicPhysicalCritical = 0;
	WORD LevelDex = pTblData->byDex + static_cast<WORD>(pTblData->fLevel_Up_Dex * PlayerProfile.byLevel);
	float DexByPoint = 0.5; // 1Dex = 1 critical old tw
	WORD PhysicalCriticalRate = BasicPhysicalCritical + static_cast<WORD>(LevelDex * DexByPoint); 
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
	WORD BasicEnergyOffence = pTblData->wBasic_Energy_Offence + (pTblData->byLevel_Up_Energy_Offence * PlayerProfile.byLevel);
	WORD LevelSol = pTblData->bySol + static_cast<WORD>(pTblData->fLevel_Up_Sol * PlayerProfile.byLevel);
	float SolByPoint = 1.66; // 1Soul = 1.66 Physical old tw
	WORD EnergyOffence = BasicEnergyOffence + static_cast<WORD>(LevelSol * SolByPoint);
	//Calculation Energy Critical Atack
	WORD BasicEnergyCritical = 0;
	WORD LevelFoc = pTblData->byFoc + static_cast<WORD>(pTblData->fLevel_Up_Foc * PlayerProfile.byLevel);
	float FocByPoint = 0.5; // 1Focus = 1 pont critical 
	WORD EnergyCriticalRate = BasicEnergyCritical + static_cast<WORD>(LevelFoc * FocByPoint);
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
	WORD BasicHitRate = pTblData->wAttack_Rate  * PlayerProfile.byLevel;
	WORD LevelingFocus = pTblData->byFoc + static_cast<WORD>(pTblData->fLevel_Up_Foc * PlayerProfile.byLevel);
	float FocusByPoint = 10; // 1 point = 10 hit rate old tw
	WORD HitRate = BasicHitRate + static_cast<WORD>(LevelingFocus * FocusByPoint);
	//DoggeRate Calculation
	WORD BasicDoggeRate = pTblData->wDodge_Rate  * PlayerProfile.byLevel;
	WORD LevelingDex = pTblData->byDex + static_cast<WORD>(pTblData->fLevel_Up_Dex * PlayerProfile.byLevel);
	float DoggeByPoint = 5;
	WORD DoggeRate = BasicDoggeRate + static_cast<WORD>(LevelingDex * DoggeByPoint);
	//Set DataBase HitRate,DoggeRate,BlockRate 
	result = sDB.executes("UPDATE characters_attributes SET BaseAttackRate = '%d', LastAttackRate = '%d', BaseDodgeRate = '%d', LastDodgeRate = '%d', BaseBlockRate = '%d', LastBlockRate = '%d' WHERE CharacterID = '%d';",
		static_cast<int>(HitRate),
		static_cast<int>(HitRate),
		static_cast<int>(DoggeRate),
		static_cast<int>(DoggeRate),
		static_cast<int>(pTblData->wBlock_Rate),
		static_cast<int>(pTblData->wBlock_Rate),
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
					SetLastPhysicalOffence(Dbo_GetFinalOffence(item.wPhysicalOffence, Grade, UpGrade->PysicalValue[Grade]) * -1); // 0 should be grade
				else
					SetLastPhysicalOffence(Dbo_GetFinalOffence(item.wPhysicalOffence, Grade, UpGrade->PysicalValue[Grade]));
			}
			if (item.wPhysicalDefence < 65535 && item.wPhysicalDefence > 0)
			{
				if (remove)
					SetLastPhysicalDefence(Dbo_GetFinalDefence(item.wPhysicalDefence, Grade, UpGrade->PysicalValue[Grade]) * -1);
				else
					SetLastPhysicalDefence(Dbo_GetFinalDefence(item.wPhysicalDefence, Grade, UpGrade->PysicalValue[Grade]));
			}
			if (item.wEnergyOffence < 65535 && item.wEnergyOffence > 0)
			{
				if (remove)
					SetLastEnergyOffence(Dbo_GetFinalOffence(item.wEnergyOffence, Grade, UpGrade->EnergyValue[Grade]) * -1);
				else
					SetLastEnergyOffence(Dbo_GetFinalOffence(item.wEnergyOffence, Grade, UpGrade->EnergyValue[Grade]));
			}
			if (item.wEnergyDefence < 65535 && item.wEnergyDefence > 0)
			{
				if (remove)
					SetLastEnergyDefence(Dbo_GetFinalDefence(item.wEnergyDefence, Grade, UpGrade->EnergyValue[Grade]) * -1);
				else
					SetLastEnergyDefence(Dbo_GetFinalDefence(item.wEnergyDefence, Grade, UpGrade->EnergyValue[Grade]));
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
						plr->GetAttributesManager()->SetLastMaxLP(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->SetLastMaxLP(aitemEffect[i].dwValue);
					break;
				}
				case ACTIVE_MAX_EP_UP:
				{
					if (isRemove == true)
						plr->GetAttributesManager()->SetLastMaxEP(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->SetLastMaxEP(aitemEffect[i].dwValue);
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
						plr->GetAttributesManager()->SetLastPhysicalOffence(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->SetLastPhysicalOffence(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence >= 60000)
					{
						plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence = 0;
						plr->GetAttributesManager()->SetLastPhysicalOffence(0);
					}

					break;
				}
				case ACTIVE_ENERGY_OFFENCE_UP:
				{
					if (isRemove == true)
						plr->GetAttributesManager()->SetLastEnergyOffence(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->SetLastEnergyOffence(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence >= 60000)
					{
						plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence = 0;
						plr->GetAttributesManager()->SetLastPhysicalOffence(0);
					}
					break;
				}
				case ACTIVE_PHYSICAL_DEFENCE_UP:
				{

					if (isRemove == true)
						plr->GetAttributesManager()->SetLastPhysicalDefence(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->SetLastPhysicalDefence(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence >= 60000)
					{
						plr->GetPcProfile()->avatarAttribute.wLastPhysicalDefence = 0;
						plr->GetAttributesManager()->SetLastPhysicalDefence(0);
					}
					break;
				}
				case ACTIVE_ENERGY_DEFENCE_UP:
				{

					if (isRemove == true)
						plr->GetAttributesManager()->SetLastEnergyDefence(aitemEffect[i].dwValue * -1);
					else
						plr->GetAttributesManager()->SetLastEnergyDefence(aitemEffect[i].dwValue);
					if (plr->GetPcProfile()->avatarAttribute.wLastEnergyDefence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastEnergyDefence >= 60000)
					{
						plr->GetPcProfile()->avatarAttribute.wLastEnergyDefence = 0;
						plr->GetAttributesManager()->SetLastEnergyDefence(0);
					}
					break;
				}
				case ACTIVE_STR_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetLastStr(aitemEffect[i].dwValue * -1);

						WORD LevelStr = aitemEffect[i].dwValue;
						float StrByPoint = 1.66; // 1Str = 1.66 Physical old tw
						WORD PhysicalOffence = static_cast<WORD>(LevelStr * StrByPoint);

						plr->GetAttributesManager()->SetLastPhysicalOffence(PhysicalOffence * -1);
						if (plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence >= 60000)
						{
							plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence = 0;
							plr->GetAttributesManager()->SetLastPhysicalOffence(0);
						}
					}
					else
					{
						plr->GetAttributesManager()->SetLastStr(aitemEffect[i].dwValue);

						WORD LevelStr = aitemEffect[i].dwValue;
						float StrByPoint = 1.66; // 1Str = 1.66 Physical old tw
						WORD PhysicalOffence = static_cast<WORD>(LevelStr * StrByPoint);

						plr->GetAttributesManager()->SetLastPhysicalOffence(PhysicalOffence);
					}
					break;
				}
				case ACTIVE_CON_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetLastCon(aitemEffect[i].dwValue * -1);

						float LevelCon = aitemEffect[i].dwValue;
						float ConByPoint = 85; // 1con = 85 old tw
						float LP = static_cast<float>(LevelCon * ConByPoint);

						plr->GetAttributesManager()->SetLastMaxLP(LP * -1);
					}
					else
					{
						plr->GetAttributesManager()->SetLastCon(aitemEffect[i].dwValue);

						float LevelCon = aitemEffect[i].dwValue;
						float ConByPoint = 85; // 1con = 85 old tw
						float LP = static_cast<float>(LevelCon * ConByPoint);

						plr->GetAttributesManager()->SetLastMaxLP(LP);
					}
					break;
				}
				case ACTIVE_FOC_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetLastFoc(aitemEffect[i].dwValue * -1);
						WORD LevelFoc = aitemEffect[i].dwValue;
						float EnergyCriticalByPoint = 0.5; // 1Focus = 1 pont critical 
						float EnergyAttackByPoint = 2; // 1Focus = 1 pont critical 
						float HitRateByPoint = 10; // 1 point = 10 hit rate old tw
						WORD EnergyCriticalRate = static_cast<WORD>(LevelFoc * EnergyCriticalByPoint);
						WORD EnergyAttack = static_cast<WORD>(LevelFoc * EnergyAttackByPoint);
						WORD HitRate = static_cast<WORD>(LevelFoc * HitRateByPoint);
						plr->GetAttributesManager()->SetLastEnergyCriticalRate(EnergyCriticalRate * -1);
						plr->GetAttributesManager()->SetLastEnergyOffence(EnergyAttack * -1);
						plr->GetAttributesManager()->SetLastAttackRate(HitRate * -1);
						if (plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence >= 60000)
						{
							plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence = 0;
							plr->GetAttributesManager()->SetLastPhysicalOffence(0);
						}
					}
					else
					{
						plr->GetAttributesManager()->SetLastFoc(aitemEffect[i].dwValue);
						WORD LevelFoc = aitemEffect[i].dwValue;
						float EnergyCriticalByPoint = 0.5; // 1Focus = 1 pont critical 
						float EnergyAttackByPoint = 2; // 1Focus = 1 pont critical 
						float HitRateByPoint = 10; // 1 point = 10 hit rate old tw
						WORD EnergyCriticalRate = static_cast<WORD>(LevelFoc * EnergyCriticalByPoint);
						WORD EnergyAttack = static_cast<WORD>(LevelFoc * EnergyAttackByPoint);
						WORD HitRate = static_cast<WORD>(LevelFoc * HitRateByPoint);
						plr->GetAttributesManager()->SetLastEnergyCriticalRate(EnergyCriticalRate);
						plr->GetAttributesManager()->SetLastEnergyOffence(EnergyAttack);
						plr->GetAttributesManager()->SetLastAttackRate(HitRate);
					}
					break;
				}
				case ACTIVE_DEX_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetLastDex(aitemEffect[i].dwValue * -1);
						WORD LevelDex = aitemEffect[i].dwValue;
						float CriticalAttackByPoint = 0.5; // 1Dex = 1 critical old tw
						float PhyAttackByPoint = 2; // 1Dex = 1 phyattack old tw
						float DoggeByPoint = 5;
						WORD PhysicalCriticalRate = static_cast<WORD>(LevelDex * CriticalAttackByPoint);
						WORD PhysicalAttack = static_cast<WORD>(LevelDex * PhyAttackByPoint);
						WORD DodgeRate = static_cast<WORD>(LevelDex * DoggeByPoint);
						plr->GetAttributesManager()->SetLastPhysicalCriticalRate(PhysicalCriticalRate * -1);
						plr->GetAttributesManager()->SetLastPhysicalOffence(PhysicalAttack * -1);
						plr->GetAttributesManager()->SetLastDodgeRate(DodgeRate * -1);
						if (plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence >= 60000)
						{
							plr->GetPcProfile()->avatarAttribute.wLastPhysicalOffence = 0;
							plr->GetAttributesManager()->SetLastPhysicalOffence(0);
						}
						if (plr->GetPcProfile()->avatarAttribute.byLastDex <= 0 || plr->GetPcProfile()->avatarAttribute.byLastDex >= 60000)
						{
							plr->GetPcProfile()->avatarAttribute.byLastDex = 0;
							plr->GetAttributesManager()->SetLastDex(0);
						}
					}
					else
					{
						plr->GetAttributesManager()->SetLastDex(aitemEffect[i].dwValue);
						WORD LevelDex = aitemEffect[i].dwValue;
						float CriticalAttackByPoint = 0.5; // 1Dex = 1 critical old tw
						float PhyAttackByPoint = 2; // 1Dex = 1 phyattack old tw
						float DoggeByPoint = 5;
						WORD PhysicalCriticalRate = static_cast<WORD>(LevelDex * CriticalAttackByPoint);
						WORD PhysicalAttack = static_cast<WORD>(LevelDex * PhyAttackByPoint);
						WORD DodgeRate = static_cast<WORD>(LevelDex * DoggeByPoint);
						plr->GetAttributesManager()->SetLastPhysicalCriticalRate(PhysicalCriticalRate);
						plr->GetAttributesManager()->SetLastPhysicalOffence(PhysicalAttack);
						plr->GetAttributesManager()->SetLastDodgeRate(DodgeRate);
					}
					break;
				}
				case ACTIVE_SOL_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetLastSol(aitemEffect[i].dwValue * -1);

						WORD LevelSol = aitemEffect[i].dwValue;
						float SolByPoint = 1.66; // 1Soul = 1.66 Physical old tw
						WORD EnergyOffence = static_cast<WORD>(LevelSol * SolByPoint);

						plr->GetAttributesManager()->SetLastEnergyOffence(EnergyOffence * -1);
						if (plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence <= 0 || plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence >= 60000)
						{
							plr->GetPcProfile()->avatarAttribute.wLastEnergyOffence = 0;
							plr->GetAttributesManager()->SetLastPhysicalOffence(0);
						}
					}
					else
					{
						plr->GetAttributesManager()->SetLastSol(aitemEffect[i].dwValue);

						WORD LevelSol = aitemEffect[i].dwValue;
						float SolByPoint = 1.66; // 1Soul = 1.66 Physical old tw
						WORD EnergyOffence = static_cast<WORD>(LevelSol * SolByPoint);

						plr->GetAttributesManager()->SetLastEnergyOffence(EnergyOffence);
					}
					break;
				}
				case ACTIVE_ENG_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetLastEng(aitemEffect[i].dwValue * -1);

						WORD LevelEng = aitemEffect[i].dwValue;
						float EngByPoint = 45; // 1Eng = 45 ep old tw
						WORD EP = static_cast<WORD>(LevelEng * EngByPoint);

						plr->GetAttributesManager()->SetLastMaxEP(EP * -1);
					}
					else
					{
						plr->GetAttributesManager()->SetLastEng(aitemEffect[i].dwValue);

						WORD LevelEng = aitemEffect[i].dwValue;
						float EngByPoint = 45; // 1Eng = 45 ep old tw
						WORD EP = static_cast<WORD>(LevelEng * EngByPoint);

						plr->GetAttributesManager()->SetLastMaxEP(EP);
					}
					break;
				}
				case ACTIVE_ATTACK_RATE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetLastAttackRate(aitemEffect[i].dwValue * -1);
					}
					else
					{
						plr->GetAttributesManager()->SetLastAttackRate(aitemEffect[i].dwValue);
					}
					break;
				}
				case ACTIVE_DODGE_RATE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetLastDodgeRate(aitemEffect[i].dwValue * -1);
					}
					else
					{
						plr->GetAttributesManager()->SetLastDodgeRate(aitemEffect[i].dwValue);
					}
					break;
				}
				case ACTIVE_BLOCK_RATE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetLastBlockRate(aitemEffect[i].dwValue * -1);
					}
					else
					{
						plr->GetAttributesManager()->SetLastBlockRate(aitemEffect[i].dwValue);
					}
					break;
				}
				//Atributes//
				case ACTIVE_HONEST_DEFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetHonestDefence(0);
					}
					else
					{
						plr->GetAttributesManager()->SetHonestDefence(100.0);
					}
					break;
				}
				case ACTIVE_STRANGE_DEFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetStrangeDefence(0);
					}
					else
					{
						plr->GetAttributesManager()->SetStrangeDefence(100.0);
					}
					break;
				}
				case ACTIVE_WILD_DEFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetWildDefence(0);
					}
					else
					{
						plr->GetAttributesManager()->SetWildDefence(100.0);
					}
					break;
				}
				case ACTIVE_ELEGANCE_DEFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetEleganceDefence(0);
					}
					else
					{
						plr->GetAttributesManager()->SetEleganceDefence(100.0);
					}
					break;
				}
				case ACTIVE_FUNNY_DEFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetFunnyDefence(0);
					}
					else
					{
						plr->GetAttributesManager()->SetFunnyDefence(100.0);
					}
					break;
				}
				case ACTIVE_HONEST_OFFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetHonestOffence(0);
					}
					else
					{
						plr->GetAttributesManager()->SetHonestOffence(100.0);
					}
					break;
				}
				case ACTIVE_STRANGE_OFFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetStrangeOffence(0);
					}
					else
					{
						plr->GetAttributesManager()->SetStrangeOffence(100.0);
					}
					break;
				}
				case ACTIVE_WILD_OFFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetWildOffence(0);
					}
					else
					{
						plr->GetAttributesManager()->SetWildOffence(100.0);
					}
					break;
				}
				case ACTIVE_ELEGANCE_OFFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetEleganceOffence(0);
					}
					else
					{
						plr->GetAttributesManager()->SetEleganceOffence(100.0);
					}
					break;
				}
				case ACTIVE_FUNNY_OFFENCE_UP:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetFunnyOffence(0);
					}
					else
					{
						plr->GetAttributesManager()->SetFunnyOffence(100.0);
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
						plr->GetAttributesManager()->SetLastPhysicalCriticalRate(aitemEffect[i].dwValue * -1);
					}
					else
					{
						plr->GetAttributesManager()->SetLastPhysicalCriticalRate(aitemEffect[i].dwValue);
					}
					break;
				}
				case ACTIVE_ENERGY_CRITICAL:
				{
					if (isRemove == true)
					{
						plr->GetAttributesManager()->SetLastEnergyCriticalRate(aitemEffect[i].dwValue * -1);
					}
					else
					{
						plr->GetAttributesManager()->SetLastEnergyCriticalRate(aitemEffect[i].dwValue);
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
						plr->GetAttributesManager()->SetLastAttackSpeedRate(attackspeed);
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
	attrLink.pwunknown_rate1 = &PlayerProfile.avatarAttribute.unknown_rate1;
	attrLink.pwunknown_rate2 = &PlayerProfile.avatarAttribute.unknown_rate2;
	attrLink.pfunknown2 = &unkFLOATField; //&PlayerProfile.avatarAttribute.unknown2;
	attrLink.unknown_float1_0 = &PlayerProfile.avatarAttribute.unknown_float1_0;
	attrLink.unknown_float1_1 = &PlayerProfile.avatarAttribute.unknown_float1_1;
	attrLink.unknown_float2_0 = &PlayerProfile.avatarAttribute.unknown_float2_0;
	attrLink.unknown_float2_1 = &PlayerProfile.avatarAttribute.unknown_float2_1;
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
	attrLink.unknown4_2 = &PlayerProfile.avatarAttribute.unknown4_2;
	attrLink.unknown4_3 = &PlayerProfile.avatarAttribute.unknown4_3;
	attrLink.unknown4_4 = &PlayerProfile.avatarAttribute.unknown4_4;
	attrLink.unknown4_5 = &PlayerProfile.avatarAttribute.unknown4_5;
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