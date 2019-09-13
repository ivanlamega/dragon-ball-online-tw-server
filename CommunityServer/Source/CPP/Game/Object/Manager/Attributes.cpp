#include <Game\Object\Manager\Attributes.h>
#include <Game\Object\Player.h>
#include <CommunitySession.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <Packet\Community\PacketTU.h>

//----------------------------------------
//	Constructor
//----------------------------------------
AttributesManager::AttributesManager()
{
	RPCounter = 0;
	RPFilledCounter = 0;
	plr = nullptr;
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
//----------------------------------------
//	Load all attributes and calculate stats from last database save
//----------------------------------------
bool AttributesManager::LoadAttributes(CHARACTERID _id, Player* _plr)
{
	charid = _id;
	plr = _plr;

	sql::ResultSet* result = sDB.executes("SELECT * FROM characters WHERE CharacterID = '%d';", charid);
	if (result == NULL)
		return false;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return false;
	}
	PlayerClassID = result->getInt("ClassID");
	PlayerRaceID = result->getInt("RaceID");
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
	wcscpy_s(PlayerProfile.awchName, MAX_SIZE_CHAR_NAME_UNICODE, charToWChar((result->getString("Name")).c_str()));
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
	PlayerProfile.dwTutorialHint = 0; // help frame
	PlayerProfile.byBindType = DBO_BIND_TYPE_INITIAL_LOCATION;
	//PlayerProfile.bindObjectTblidx = -1;

	PlayerProfile.dwReputation = result->getInt("Reputation");
	PlayerProfile.dwMudosaPoint = result->getInt("Mudosa");
	PlayerProfile.dwSpPoint = result->getInt("SkillPoints");
	PlayerProfile.bIsGameMaster = result->getBoolean("IsGameMaster");
	PlayerProfile.sMarking.dwCode = result->getInt("Title_Marking");
	PlayerProfile.sLocalize.WP_Point = result->getInt("WP_Point");// WP Poit mensage
	PlayerProfile.sLocalize.netp = result->getInt("Token");// Token Point correct value	
	PlayerProfile.sLocalize.IsVip = result->getInt("IsVip");;// S icon Vip_Member Maybe
	cashpoit = result->getInt("CashPoint");
	WagguCoin = result->getInt("WagguCoin");
	EventCoin = result->getInt("EventCoin");
	PlayerProfile.sMixData.bNormalStart = 0;
	PlayerProfile.sMixData.bSpecialStart = 0;
	PlayerProfile.sMixData.byMixLevel = result->getInt("MixLevel");
	PlayerProfile.sMixData.bySpecialType = 0;
	PlayerProfile.sMixData.dwMixExp = result->getInt("MixExp");
	

	
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
	plr->GetState()->sCharStateBase.dwConditionFlag = 0;
	plr->GetState()->sCharStateBase.dwStateTime = 0;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sGreatNamek.bySourceGrade = 255;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sKaioken.bySourceGrade = 255;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sPureMajin.bySourceGrade = 255;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sSuperSaiyan.bySourceGrade = 255;
	plr->GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = INVALID_TBLIDX;

	plr->GetState()->sCharStateBase.isFighting = false;
	plr->GetState()->sCharStateBase.isFlying = plr->GetFlying();

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
		return false;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return false;
	}
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
	PlayerProfile.avatarAttribute.wLastPhysicalOffence = static_cast<WORD>(result->getInt("LastPhysicalOffence"));;
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

	PlayerProfile.avatarAttribute.unknown2 = 0;
	PlayerProfile.avatarAttribute.unknown3_0 = 0;
	PlayerProfile.avatarAttribute.unknown3_1 = 0;
	PlayerProfile.avatarAttribute.unknown3_10 = 0;
	PlayerProfile.avatarAttribute.unknown3_11 = 0;//
	PlayerProfile.avatarAttribute.unknown3_12 = 0;
	PlayerProfile.avatarAttribute.unknown3_13 = 0;//
	PlayerProfile.avatarAttribute.unknown3_2 = 0;
	PlayerProfile.avatarAttribute.unknown3_3 = 0;//
	PlayerProfile.avatarAttribute.unknown3_5 = 0;
	PlayerProfile.avatarAttribute.MaxWeight = 2600;
	PlayerProfile.avatarAttribute.unknown3_w6 = 0; // if != 0 weight get bugged
	PlayerProfile.avatarAttribute.unknown3_7 = 0;
	PlayerProfile.avatarAttribute.unknown3_8 = 0;//
	PlayerProfile.avatarAttribute.unknown3_9 = 0;
	PlayerProfile.avatarAttribute.unknown4_0 = 0;
	PlayerProfile.avatarAttribute.unknown4_1 = 0;
	PlayerProfile.avatarAttribute.unknown4_2 = 0;
	PlayerProfile.avatarAttribute.unknown4_3 = 0;
	PlayerProfile.avatarAttribute.unknown4_4 = 0;
	PlayerProfile.avatarAttribute.unknown4_5 = 0;
	PlayerProfile.avatarAttribute.unknown4_6 = 0;
	PlayerProfile.avatarAttribute.unknown5_1 = 0;
	PlayerProfile.avatarAttribute.unknown5_0 = 0;
	PlayerProfile.avatarAttribute.unknown5_2 = 0;
	PlayerProfile.avatarAttribute.unknown5_3 = 0;
	PlayerProfile.avatarAttribute.unknown5_4 = 0;
	PlayerProfile.avatarAttribute.unknown5_5 = 0;
	PlayerProfile.avatarAttribute.unknown6 = 0;
	PlayerProfile.avatarAttribute.unknown_float1_0 = 0;
	PlayerProfile.avatarAttribute.unknown_float1_1 = 0;
	PlayerProfile.avatarAttribute.unknown_float2_0 = 0;
	PlayerProfile.avatarAttribute.unknown_float2_1 = 0;
	PlayerProfile.avatarAttribute.unknown_rate1 = 0;
	PlayerProfile.avatarAttribute.unknown_rate2 = 0;
	// SKILL SPEED
	PlayerProfile.avatarAttribute.SkillSpeed = 60.0f;
	//LP Get up Reg
	PlayerProfile.avatarAttribute.wBaseLpRegen = 8 * (PlayerProfile.byLevel / 4);
	PlayerProfile.avatarAttribute.wLastLpRegen = 9 * (PlayerProfile.byLevel / 4);
	//LP Sit Down Reg
	PlayerProfile.avatarAttribute.wBaseLpSitdownRegen = 20 * (PlayerProfile.byLevel / 4);
	PlayerProfile.avatarAttribute.wLastLpSitdownRegen = 20 * (PlayerProfile.byLevel / 4);
	//LP Reg in Batle
	PlayerProfile.avatarAttribute.wBaseLpBattleRegen = 6 * (PlayerProfile.byLevel / 4);
	PlayerProfile.avatarAttribute.wLastLpBattleRegen = 7 * (PlayerProfile.byLevel / 4);
	//EP Get UP Reg
	PlayerProfile.avatarAttribute.wBaseEpRegen = 12 * (PlayerProfile.byLevel / 4);
	PlayerProfile.avatarAttribute.wLastEpRegen = 13 * (PlayerProfile.byLevel / 4);
	//EP Sit Down Reg
	PlayerProfile.avatarAttribute.wBaseEpSitdownRegen = 20 * (PlayerProfile.byLevel / 4);
	PlayerProfile.avatarAttribute.wLastEpSitdownRegen = 20 * (PlayerProfile.byLevel / 4);
	//EP Reg in Batle
	PlayerProfile.avatarAttribute.wBaseEpBattleRegen = 14 * (PlayerProfile.byLevel / 4);
	PlayerProfile.avatarAttribute.wLastEpBattleRegen = 15 * (PlayerProfile.byLevel / 4);
	//Rp incress rate
	PlayerProfile.avatarAttribute.wBaseRpRegen = 1;
	PlayerProfile.avatarAttribute.wLastRpRegen = 1;
	//RP diminution
	PlayerProfile.avatarAttribute.wLastRpDimimutionRate = 3;
	//Curse Sucess Rate
	PlayerProfile.avatarAttribute.wBaseCurseSuccessRate = 0;
	PlayerProfile.avatarAttribute.wLastCurseSuccessRate = 0;
	//Curse Tolerance Rate
	PlayerProfile.avatarAttribute.wBaseCurseToleranceRate = 0;
	PlayerProfile.avatarAttribute.wLastCurseToleranceRate = 0;
	//Nao sei
	PlayerProfile.avatarAttribute.fCastingTimeChangePercent = 0;
	PlayerProfile.avatarAttribute.fCoolTimeChangePercent = 0;
	PlayerProfile.avatarAttribute.fKeepTimeChangePercent = 0;
	PlayerProfile.avatarAttribute.fDotValueChangePercent = 0;
	PlayerProfile.avatarAttribute.fDotTimeChangeAbsolute = 0;
	PlayerProfile.avatarAttribute.fRequiredEpChangePercent = 0;
	//Atribute Ofense/Defese
	PlayerProfile.avatarAttribute.fHonestOffence = 0;//nao
	PlayerProfile.avatarAttribute.fHonestDefence = 0;//nao
	PlayerProfile.avatarAttribute.fStrangeOffence = 0;//nao
	PlayerProfile.avatarAttribute.fStrangeDefence = 0;//nao
	PlayerProfile.avatarAttribute.fWildOffence = 0;//nao
	PlayerProfile.avatarAttribute.fWildDefence = 0;//nao
	PlayerProfile.avatarAttribute.fEleganceOffence = 0;//nao
	PlayerProfile.avatarAttribute.fEleganceDefence = 0;//nao
	PlayerProfile.avatarAttribute.fFunnyOffence = 0;//nao
	PlayerProfile.avatarAttribute.fFunnyDefence = 0;//nao

	PlayerProfile.avatarAttribute.wParalyzeToleranceRate = 0;//nao
	PlayerProfile.avatarAttribute.wTerrorToleranceRate = 0;//nao
	PlayerProfile.avatarAttribute.wConfuseToleranceRate = 0;//nao
	PlayerProfile.avatarAttribute.wStoneToleranceRate = 0;//nao
	PlayerProfile.avatarAttribute.wCandyToleranceRate = 0;//nao
	PlayerProfile.avatarAttribute.fParalyzeKeepTimeDown = 0;//nao
	PlayerProfile.avatarAttribute.fTerrorKeepTimeDown = 0;//nao
	PlayerProfile.avatarAttribute.fConfuseKeepTimeDown = 0;//nao
	PlayerProfile.avatarAttribute.fStoneKeepTimeDown = 0;//nao
	PlayerProfile.avatarAttribute.fCandyKeepTimeDown = 0;//nao
	PlayerProfile.avatarAttribute.fBleedingKeepTimeDown = 0;//nao
	PlayerProfile.avatarAttribute.fPoisonKeepTimeDown = 0;
	PlayerProfile.avatarAttribute.fStomachacheKeepTimeDown = 0;
	PlayerProfile.avatarAttribute.fCriticalBlockSuccessRate = 0;
	PlayerProfile.avatarAttribute.wGuardRate = 0;
	PlayerProfile.avatarAttribute.fSkillDamageBlockModeSuccessRate = 0;
	PlayerProfile.avatarAttribute.fCurseBlockModeSuccessRate = 0;
	PlayerProfile.avatarAttribute.fKnockdownBlockModeSuccessRate = 0;

	PlayerProfile.avatarAttribute.fHtbBlockModeSuccessRate = 0; // Bleeding defense TW
	PlayerProfile.avatarAttribute.fSitDownLpRegenBonusRate = 0; // posion defense tw
	PlayerProfile.avatarAttribute.fSitDownEpRegenBonusRate = 0; // abdominal pain defense
	PlayerProfile.avatarAttribute.fPhysicalCriticalDamageBonusRate = 0;//Burn Defense

	PlayerProfile.avatarAttribute.fEnergyCriticalDamageBonusRate = 1;
	PlayerProfile.avatarAttribute.fItemUpgradeBonusRate = 2;
	PlayerProfile.avatarAttribute.fItemUpgradeBreakBonusRate = 3;
	PlayerProfile.avatarAttribute.fBaseAirDash2Speed = 30.0f;//Dash Fly2 TW
	PlayerProfile.avatarAttribute.fLastAirDash2Speed = 30.0f;//Dash Fly2 TW
	PlayerProfile.avatarAttribute.fBaseAirDashSpeed = 20.0f;//Dash Fly TW
	PlayerProfile.avatarAttribute.fLastAirDashSpeed = 20.0f;//Dash Fly TW
	PlayerProfile.avatarAttribute.fBaseRunSpeed = static_cast<WORD>(result->getDouble("LastRunSpeed")); //Base Run TW
	PlayerProfile.avatarAttribute.fBaseAirSpeed = 15;//Base Air Speed TW
	PlayerProfile.avatarAttribute.fLastAirSpeed = 15;//LastAir Speed TW
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

	//status Base Con/Focus Etc
	result = sDB.executes("UPDATE characters_attributes SET BaseStr = '%d', BaseCon = '%d', BaseFoc = '%d', BaseDex = '%d',BaseSol = '%d', BaseEng = '%d' WHERE CharacterID = '%d';",
		static_cast<int>(pTblData->byStr + (pTblData->fLevel_Up_Str * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->byCon + (pTblData->fLevel_Up_Con * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->byFoc + (pTblData->fLevel_Up_Foc * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->byDex + (pTblData->fLevel_Up_Dex * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->bySol + (pTblData->fLevel_Up_Sol * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->byEng + (pTblData->fLevel_Up_Eng * PlayerProfile.byLevel)),
		charid);
	if (result != NULL)
		delete result;
	
	//status Last Con/Focus Etc
	result = sDB.executes("UPDATE characters_attributes SET LastStr = '%d', LastCon = '%d', LastFoc = '%d', LastDex = '%d', LastSol = '%d', LastEng = '%d' WHERE CharacterID = '%d';",
		static_cast<int>(pTblData->byStr + (pTblData->fLevel_Up_Str * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->byCon + (pTblData->fLevel_Up_Con * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->byFoc + (pTblData->fLevel_Up_Foc * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->byDex + (pTblData->fLevel_Up_Dex * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->bySol + (pTblData->fLevel_Up_Sol * PlayerProfile.byLevel)),
		static_cast<int>(pTblData->byEng + (pTblData->fLevel_Up_Eng * PlayerProfile.byLevel)),
		charid);
	if (result != NULL)
		delete result;

	// LP Calculation
	DWORD BasicLife = pTblData->wBasic_LP + (pTblData->byLevel_Up_LP * PlayerProfile.byLevel);
	WORD LevelCon = pTblData->byCon + static_cast<WORD>(pTblData->fLevel_Up_Con * PlayerProfile.byLevel);
	float ConByPoint = 81.6; // 1con = 85 old tw
	DWORD LP = BasicLife + static_cast<DWORD>(LevelCon * ConByPoint);

	//EP Calculation
	WORD BasicEnergy = pTblData->wBasic_EP + (pTblData->byLevel_Up_EP * PlayerProfile.byLevel);
	WORD LevelEng = pTblData->byEng + static_cast<WORD>(pTblData->fLevel_Up_Eng * PlayerProfile.byLevel);
	float EngByPoint = 56; // 1Eng = 45 ep old tw
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
	float SolByPoint = 2; // 1Str = 1.66 Physical old tw
	WORD EnergyOffence = BasicEnergyOffence + static_cast<WORD>(LevelSol * SolByPoint);
	//Calculation Energy Critical Atack
	WORD BasicEnergyCritical = 0;
	WORD LevelFoc = pTblData->byFoc + static_cast<WORD>(pTblData->fLevel_Up_Foc * PlayerProfile.byLevel);
	float FocByPoint = 0.6; // 1Eng = 1 pont critical 
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
void			AttributesManager::LoadAttributesFromItems(sITEM_BRIEF *brief)
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
			
			if (eType == eEQUIP_TYPE::EQUIP_TYPE_ARMOR
				|| eType == eEQUIP_TYPE::EQUIP_TYPE_MAIN_WEAPON
				|| eType == eEQUIP_TYPE::EQUIP_TYPE_SUB_WEAPON
				|| eType == eEQUIP_TYPE::EQUIP_TYPE_SCOUTER)
			{
				if (item->wPhysicalDefence != INVALID_WORD)
					PlayerProfile.avatarAttribute.wLastPhysicalDefence += item->wPhysicalDefence;
				if (item->wPhysicalOffence != INVALID_WORD)
					PlayerProfile.avatarAttribute.wLastPhysicalOffence += item->wPhysicalOffence;
				if (item->wEnergyDefence != INVALID_WORD)
					PlayerProfile.avatarAttribute.wLastEnergyDefence += item->wEnergyDefence;
				if (item->wEnergyOffence != INVALID_WORD)
					PlayerProfile.avatarAttribute.wLastEnergyOffence += item->wEnergyOffence;
				/*sLog.outFile("\nItem: %d\n", item->tblidx);

				sLog.outFile("item->bValidity_Able = %d\n", item->bValidity_Able);
				sLog.outFile("item->byBag_Size = %u\n", item->byBag_Size);
				sLog.outFile("item->byBattle_Attribute = %u\n", item->byBattle_Attribute);
				sLog.outFile("item->byClass_Special = %u\n", item->byClass_Special);
				sLog.outFile("item->byCommonPointType = %u\n", item->byCommonPointType);
				//sLog.outFile("item->byDurability = %u\n", item->byDurability);
				//sLog.outFile("item->byDurability_Count = %u\n", item->byDurability_Count);
				sLog.outFile("item->byDurationType = %u\n", item->byDurationType);
				sLog.outFile("item->byEquip_Type = %u\n", item->byEquip_Type);
				sLog.outFile("item->byItemGroup = %u\n", item->byItemGroup);
				sLog.outFile("item->byItem_Type = %u\n", item->byItem_Type);
				sLog.outFile("item->byMax_Stack = %u\n", item->byMax_Stack);
				sLog.outFile("item->byModel_Type = %u\n", item->byModel_Type);
				sLog.outFile("item->byNeedFunction = %u\n", item->byNeedFunction);
				sLog.outFile("item->byNeed_Con = %u\n", item->byNeed_Con);
				sLog.outFile("item->byNeed_Dex = %u\n", item->byNeed_Dex);
				sLog.outFile("item->byNeed_Eng = %u\n", item->byNeed_Eng);
				sLog.outFile("item->byNeed_Foc = %u\n", item->byNeed_Foc);
				sLog.outFile("item->byNeed_Level = %u\n", item->byNeed_Level);
				sLog.outFile("item->byNeed_Sol = %u\n", item->byNeed_Sol);
				sLog.outFile("item->byNeed_Str = %u\n", item->byNeed_Str);
				sLog.outFile("item->byRace_Special = %u\n", item->byRace_Special);
				sLog.outFile("item->byRank = %u\n", item->byRank);
				sLog.outFile("item->byScouter_Parts_Type = %u\n", item->byScouter_Parts_Type);
				sLog.outFile("item->byScouter_Parts_Value = %u\n", item->byScouter_Parts_Value);
				//sLog.outFile("item->bySell_Price = %u\n", item->bySell_Price);
				sLog.outFile("item->Charm_Tblidx = %d\n", item->Charm_Tblidx);
				sLog.outFile("item->CommonPoint = %d\n", item->CommonPoint);
				sLog.outFile("item->contentsTblidx = %d\n", item->contentsTblidx);
				//sLog.outFile("item->dwCost = %d\n", item->dwCost);
				sLog.outFile("item->dwDurationGroup = %d\n", item->dwDurationGroup);

				sLog.outFile("item->dwNeed_Class_Bit_Flag = %d\n", item->dwNeed_Class_Bit_Flag);
				sLog.outFile("item->dwScouter_MaxPower = %d\n", item->dwScouter_MaxPower);
				sLog.outFile("item->dwUseDurationMax = %d\n", item->dwUseDurationMax);
				sLog.outFile("item->Item_Option_Tblidx = %d\n", item->Item_Option_Tblidx);
				sLog.outFile("item->NeedItemTblidx = %d\n", item->NeedItemTblidx);
				sLog.outFile("item->Note = %d\n", item->Note);
				sLog.outFile("item->set_Item_Tblidx = %d\n", item->set_Item_Tblidx);
				sLog.outFile("item->wCostumeHideBitFlag = %u\n", item->wCostumeHideBitFlag);
				sLog.outFile("item->Use_Item_Tblidx = %d\n", item->Use_Item_Tblidx);
				sLog.outFile("item->wEquip_Slot_Type_Bit_Flag = %u\n", item->wEquip_Slot_Type_Bit_Flag);
				sLog.outFile("item->wFunction_Bit_Flag = %u\n", item->wFunction_Bit_Flag);
				sLog.outFile("item->wScouter_Watt = %u\n", item->wScouter_Watt);

				sLog.outFile("item->dwEnergy_DefenceUpgrade = %d\n", item->dwEnergy_DefenceUpgrade);
				sLog.outFile("item->dwEnergy_OffenceUpgrade= %d\n", item->dwEnergy_OffenceUpgrade);
				sLog.outFile("item->dwPhysical_DefenceUpgrade= %d\n", item->dwPhysical_DefenceUpgrade);
				sLog.outFile("item->dwPhysical_OffenceUpgrade= %d\n", item->dwPhysical_OffenceUpgrade);
				sLog.outFile("item->wEnergy_Defence= %u\n", item->wEnergy_Defence);
				sLog.outFile("item->wEnergy_Offence= %u\n", item->wEnergy_Offence);
				sLog.outFile("item->wPhysical_Defence= %u\n", item->wPhysical_Defence);
				sLog.outFile("item->wPhysical_Offence= %u\n", item->wPhysical_Offence);
				sLog.outFile("item->fAttack_Range_Bonus= %f\n", item->fAttack_Range_Bonus);
				sLog.outFile("item->wAttack_Speed_Rate= %u\n\n", item->wAttack_Speed_Rate);

				sLog.outFile("item->unk1= %u\n", item->unk1);
				sLog.outFile("item->unk2= %d\n", item->unk2);
				sLog.outFile("item->unk3= %u\n", item->unk3);
				sLog.outFile("item->unk4= %u\n", item->unk4);
				//sLog.outFile("item->unk5= %u\n", item->unk5);
				//sLog.outFile("item->unk6= %u\n", item->unk6);

				sLog.outFile("item->unknownStruct unknown1 %u\n", item->unknownStruct.unknown1);
				sLog.outFile("item->unknownStruct unknown2 %u\n", item->unknownStruct.unknown2);
				sLog.outFile("item->unknownStruct weight %u\n", item->unknownStruct.unknown3);
				sLog.outFile("item->unknownStruct unknown4 %u\n", item->unknownStruct.unknown4);
				sLog.outFile("item->unknownStruct unknown5 %u\n", item->unknownStruct.unknown5);
				sLog.outFile("item->unknownStruct buy price %u\n", item->unknownStruct.unknown6);
				sLog.outFile("item->unknownStruct unknown7 %u\n", item->unknownStruct.unknown7);
				sLog.outFile("item->unknownStruct unknown8 %u\n", item->unknownStruct.unknown8);
				sLog.outFile("item->unknownStruct sell price %u\n", item->unknownStruct.unknown9);
				sLog.outFile("item->unknownStruct unknown10 %u\n", item->unknownStruct.unknown10);
				sLog.outFile("item->unknownStruct unknown11 %u\n", item->unknownStruct.unknown11);
				sLog.outFile("item->unknownStruct durability %u\n", item->unknownStruct.unknown12);
				sLog.outFile("item->unknownStruct unknown13 %u\n", item->unknownStruct.unknown13);
				sLog.outFile("item->unknownStruct unknown14 %u\n\n", item->unknownStruct.unknown14);

				sLog.outFile("item->unknownStruct2 unknown1 %u\n", item->unknownStruct2.unknown1);
				sLog.outFile("item->unknownStruct2 unknown2 %u\n", item->unknownStruct2.unknown2);
				sLog.outFile("item->unknownStruct2 unknown3 %u\n", item->unknownStruct2.unknown3);
				sLog.outFile("item->unknownStruct2 unknown4 %u\n", item->unknownStruct2.unknown4);
				sLog.outFile("item->unknownStruct2 unknown5 %u\n", item->unknownStruct2.unknown5);
				sLog.outFile("item->unknownStruct2 unknown6 %u\n", item->unknownStruct2.unknown6);
				sLog.outFile("item->unknownStruct2 unknown7 %u\n", item->unknownStruct2.unknown7);
				sLog.outFile("item->unknownStruct2 unknown8 %u\n", item->unknownStruct2.unknown8);
				sLog.outFile("item->unknownStruct2 unknown9 %u\n", item->unknownStruct2.unknown9);
				sLog.outFile("item->unknownStruct2 unknown10 %u\n", item->unknownStruct2.unknown10);

				sLog.outFile("item->unknownStruct33 unknown1 %u\n", item->unknownStruct3.unknown1);
				sLog.outFile("item->unknownStruct33 unknown2 %u\n", item->unknownStruct3.unknown2);
				sLog.outFile("item->unknownStruct33 unknown3 %u\n", item->unknownStruct3.unknown3);
				sLog.outFile("item->unknownStruct33 unknown4 %u\n", item->unknownStruct3.unknown4);
				sLog.outFile("item->unknownStruct33 unknown5 %u\n", item->unknownStruct3.unknown5);
				sLog.outFile("item->unknownStruct33 unknown6 %u\n", item->unknownStruct3.unknown6);
				sLog.outFile("item->unknownStruct33 unknown7 %u\n", item->unknownStruct3.unknown7);
				sLog.outFile("item->unknownStruct33 unknown8 %u\n", item->unknownStruct3.unknown8);
				sLog.outFile("item->unknownStruct33 unknown9 %u\n", item->unknownStruct3.unknown9);
				sLog.outFile("item->unknownStruct33 unknown10 %u\n", item->unknownStruct3.unknown10);
				sLog.outFile("item->unknownStruct33 unknown11 %u\n", item->unknownStruct3.unknown11);
				sLog.outFile("item->unknownStruct33 unknown12 %u\n", item->unknownStruct3.unknown12);
				sLog.outFile("item->unknownStruct33 unknown13 %u\n", item->unknownStruct3.unknown13);
				sLog.outFile("item->unknownStruct33 unknown14 %u\n", item->unknownStruct3.unknown14);
				sLog.outFile("item->unknownStruct33 unknown15 %u\n", item->unknownStruct3.unknown15);
				sLog.outFile("item->unknownStruct33 unknown16 %u\n", item->unknownStruct3.unknown16);
				sLog.outFile("item->unknownStruct33 unknown17 %u\n", item->unknownStruct3.unknown17);
				sLog.outFile("item->unknownStruct33 unknown18 %u\n", item->unknownStruct3.unknown18);
				sLog.outFile("item->unknownStruct33 unknown19 %u\n", item->unknownStruct3.unknown19);
				sLog.outFile("item->unknownStruct33 unknown20 %u\n", item->unknownStruct3.unknown20);
				sLog.outFile("item->unknownStruct33 unknown21 %u\n", item->unknownStruct3.unknown21);
				sLog.outFile("item->unknownStruct33 unknown22 %u\n", item->unknownStruct3.unknown22);
				sLog.outFile("item->unknownStruct33 unknown23 %u\n", item->unknownStruct3.unknown23);
				sLog.outFile("item->unknownStruct33 unknown24 %u\n", item->unknownStruct3.unknown24);
				sLog.outFile("item->unknownStruct33 unknown25 %u\n", item->unknownStruct3.unknown25);
				sLog.outFile("item->unknownStruct33 unknown26 %u\n", item->unknownStruct3.unknown26);
				sLog.outFile("item->unknownStruct33 unknown27 %u\n", item->unknownStruct3.unknown27);
				sLog.outFile("item->unknownStruct33 unknown28 %u\n", item->unknownStruct3.unknown28);
				sLog.outFile("item->unknownStruct33 unknown29 %u\n", item->unknownStruct3.unknown29);
				sLog.outFile("item->unknownStruct33 unknown30 %u\n", item->unknownStruct3.unknown30);
				sLog.outFile("item->unknownStruct33 unknown31 %u\n", item->unknownStruct3.unknown31);
				sLog.outFile("item->unknownStruct33 unknown32 %u\n", item->unknownStruct3.unknown32);*/
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
void AttributesManager::UpdateAttributesFromItem(sITEM_TBLDAT& item, bool remove)
{
	if (item.wPhysicalOffence < 65535 && item.wPhysicalOffence > 0)
	{
		if (remove == true)
			SetLastPhysicalOffence(Dbo_GetFinalOffence(item.wPhysicalOffence, 0,0) * -1); // 0 should be grade
		else
			SetLastPhysicalOffence(Dbo_GetFinalOffence(item.wPhysicalOffence, 0,0));
	}
	if (item.wPhysicalDefence < 65535 && item.wPhysicalDefence > 0)
	{
		if (remove)
			SetLastPhysicalDefence(Dbo_GetFinalDefence(item.wPhysicalDefence, 0,0) * -1);
		else
			SetLastPhysicalDefence(Dbo_GetFinalDefence(item.wPhysicalDefence, 0,0));
	}
	if (item.wEnergyOffence < 65535 && item.wEnergyOffence > 0)
	{
		if (remove)
			SetLastEnergyOffence(Dbo_GetFinalOffence(item.wEnergyOffence, 0,0) * -1);
		else
			SetLastEnergyOffence(Dbo_GetFinalOffence(item.wEnergyOffence, 0,0));
	}
	if (item.wEnergyDefence < 65535 && item.wEnergyDefence > 0)
	{
		if (remove)
			SetLastEnergyDefence(Dbo_GetFinalDefence(item.wEnergyDefence, 0,0) * -1);
		else
			SetLastEnergyDefence(Dbo_GetFinalDefence(item.wEnergyDefence, 0,0));
	}
	if (item.wAttackSpeedRate < 65535 && item.wAttackSpeedRate > 0)
	{
		SetLastAttackSpeedRate(item.wAttackSpeedRate);
	}
	if (item.fAttackRangeBonus < 65535 && item.fAttackRangeBonus > 0)
	{
		//SetAttackRangeBonus(item.fAttack_Range_Bonus);
	}
}
//----------------------------------------
//	Send the new players attributes
//----------------------------------------
void AttributesManager::UpdateAttributes()
{
	FillAttributesLink(); // store our attributes modded value
	DWORD buffer[2048];
	DWORD datasize = 0;

	if (SaveAvatarAttribute(&buffer, &datasize) == false)
	{
		sLog.outError("ERROR IN SaveAvatarAttribute");
	}

	sGU_AVATAR_ATTRIBUTE_UPDATE attr;
	memset(&attr, INVALID_TBLIDX, sizeof(sGU_AVATAR_ATTRIBUTE_UPDATE));

	attr.wOpCode = GU_AVATAR_ATTRIBUTE_UPDATE;
	attr.wPacketSize = sizeof(sGU_AVATAR_ATTRIBUTE_UPDATE) - 2;

	attr.byAttributeTotalCount = ATTRIBUTE_TO_UPDATE_COUNT;// 166; // 157
	attr.hHandle = plr->GetHandle();

	memcpy(attr.abyFlexibleField, &buffer, ((UCHAR_MAX - 1) / 8 + 1) + sizeof(sAVATAR_ATTRIBUTE));

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
	attrLink.unknown3_3 = &PlayerProfile.avatarAttribute.unknown3_3;
	attrLink.SkillSpeed = &PlayerProfile.avatarAttribute.SkillSpeed;
	attrLink.unknown3_5 = &PlayerProfile.avatarAttribute.unknown3_5;
	attrLink.MaxWeight = &PlayerProfile.avatarAttribute.MaxWeight;
	attrLink.unknown3_w6 = &PlayerProfile.avatarAttribute.unknown3_w6;
	attrLink.unknown3_7 = &PlayerProfile.avatarAttribute.unknown3_7;
	attrLink.unknown3_8 = &PlayerProfile.avatarAttribute.unknown3_8;
	attrLink.unknown3_9 = &PlayerProfile.avatarAttribute.unknown3_9;
	attrLink.unknown3_10 = &PlayerProfile.avatarAttribute.unknown3_10;
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