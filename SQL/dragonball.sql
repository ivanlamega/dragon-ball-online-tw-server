/*
Navicat MySQL Data Transfer

Source Server         : DragonBall
Source Server Version : 50505
Source Host           : localhost:3306
Source Database       : dragonball

Target Server Type    : MYSQL
Target Server Version : 50505
File Encoding         : 65001

Date: 2019-10-11 19:30:36
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `AccountID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `UserName` varchar(16) NOT NULL,
  `UserPassword` varchar(32) NOT NULL,
  `IsBanned` tinyint(1) NOT NULL DEFAULT 0,
  `IsGM` tinyint(1) NOT NULL DEFAULT 0,
  `LastServerID` int(11) NOT NULL DEFAULT 255,
  `LastChannelID` int(11) NOT NULL DEFAULT 255,
  `AccountStatus` tinyint(1) NOT NULL DEFAULT 0,
  `email` varchar(50) DEFAULT NULL,
  `foto_user` varchar(200) CHARACTER SET utf8 COLLATE utf8_spanish2_ci DEFAULT NULL,
  `rango` int(11) DEFAULT 1,
  `estado` varchar(1) CHARACTER SET utf8 COLLATE utf8_spanish2_ci DEFAULT NULL,
  `fecha_baja` datetime DEFAULT NULL,
  `ip` varchar(50) CHARACTER SET utf8 COLLATE utf8_spanish2_ci NOT NULL,
  PRIMARY KEY (`AccountID`),
  UNIQUE KEY `AccountID_UNIQUE` (`AccountID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of account
-- ----------------------------

-- ----------------------------
-- Table structure for `aucionhouse`
-- ----------------------------
DROP TABLE IF EXISTS `aucionhouse`;
CREATE TABLE `aucionhouse` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `CharID` int(11) DEFAULT NULL,
  `ItemHandle` int(11) DEFAULT NULL,
  `SellerName` varchar(20) CHARACTER SET utf8 NOT NULL,
  `ItemTblidx` int(11) DEFAULT NULL,
  `SellAmount` int(11) DEFAULT NULL,
  `StackCount` int(11) DEFAULT NULL,
  `ItemLevel` int(11) DEFAULT NULL,
  `ItemType` int(11) DEFAULT NULL,
  `ItemGrade` int(11) DEFAULT NULL,
  `ItemRank` int(11) DEFAULT NULL,
  `AtributeType1` int(11) DEFAULT 0,
  `AtributeValue1` int(11) DEFAULT 0,
  `AtributeType2` int(11) DEFAULT 0,
  `AtributeValue2` int(11) DEFAULT 0,
  `AtributeType3` int(11) DEFAULT 0,
  `AtributeValue3` int(11) DEFAULT 0,
  `AtributeType4` int(11) DEFAULT 0,
  `AtributeValue4` int(11) DEFAULT 0,
  `AtributeType5` int(11) DEFAULT 0,
  `AtributeValue5` int(11) DEFAULT 0,
  `AtributeType6` int(11) DEFAULT 0,
  `AtributeValue6` int(11) DEFAULT 0,
  `DogiAtributeType1` int(11) DEFAULT 0,
  `DogiAtributeValue1` int(11) DEFAULT 0,
  `DogiAtributeType2` int(11) DEFAULT 0,
  `DogiAtributeValue2` int(11) DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of aucionhouse
-- ----------------------------

-- ----------------------------
-- Table structure for `banlist`
-- ----------------------------
DROP TABLE IF EXISTS `banlist`;
CREATE TABLE `banlist` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `BanIp` varchar(50) CHARACTER SET utf8 COLLATE utf8_spanish2_ci NOT NULL,
  `Rason` varchar(160) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of banlist
-- ----------------------------

-- ----------------------------
-- Table structure for `bind`
-- ----------------------------
DROP TABLE IF EXISTS `bind`;
CREATE TABLE `bind` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) NOT NULL,
  `WorldID` tinyint(3) NOT NULL,
  `BindObjectTblIdx` int(10) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of bind
-- ----------------------------

-- ----------------------------
-- Table structure for `cashitem`
-- ----------------------------
DROP TABLE IF EXISTS `cashitem`;
CREATE TABLE `cashitem` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `tblidx` int(11) unsigned NOT NULL DEFAULT 0,
  `owner_id` int(11) unsigned NOT NULL DEFAULT 0,
  `byStackCount` int(10) unsigned NOT NULL DEFAULT 1,
  `Year` int(10) DEFAULT NULL,
  `Month` int(10) DEFAULT NULL,
  `Day` int(10) DEFAULT NULL,
  `Hour` int(10) DEFAULT NULL,
  `Minute` int(10) DEFAULT NULL,
  `Secound` int(10) DEFAULT NULL,
  `Handle` int(11) DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `owner_id_idx` (`owner_id`),
  KEY `item_vnum_index` (`tblidx`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of cashitem
-- ----------------------------

-- ----------------------------
-- Table structure for `characters`
-- ----------------------------
DROP TABLE IF EXISTS `characters`;
CREATE TABLE `characters` (
  `CharacterID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `AccountID` bigint(20) unsigned NOT NULL,
  `GuildID` bigint(20) unsigned NOT NULL DEFAULT 0,
  `Name` varchar(20) NOT NULL,
  `ServerID` int(10) unsigned NOT NULL,
  `RaceID` int(10) unsigned NOT NULL,
  `ClassID` int(10) unsigned NOT NULL,
  `GenderID` int(10) unsigned NOT NULL,
  `FaceID` int(10) unsigned NOT NULL,
  `HairID` int(10) unsigned NOT NULL,
  `HairColorID` int(10) unsigned NOT NULL,
  `SkinColorID` int(10) unsigned NOT NULL,
  `CurrentLevel` int(10) unsigned NOT NULL DEFAULT 70,
  `CurrentExp` bigint(20) unsigned NOT NULL DEFAULT 0,
  `MapInfoID` bigint(20) unsigned NOT NULL DEFAULT 4294967295,
  `WorldTableID` bigint(20) unsigned NOT NULL DEFAULT 1,
  `WorldID` bigint(20) unsigned NOT NULL DEFAULT 1,
  `BindType` int(10) unsigned NOT NULL DEFAULT 0,
  `BindWorldID` bigint(20) unsigned NOT NULL DEFAULT 0,
  `BindObjectID` bigint(20) unsigned NOT NULL DEFAULT 0,
  `Position_X` float(11,6) NOT NULL DEFAULT 0.000000,
  `Position_Y` float(11,6) NOT NULL DEFAULT 0.000000,
  `Position_Z` float(11,6) NOT NULL DEFAULT 0.000000,
  `Direction_X` float(11,6) NOT NULL DEFAULT 0.000000,
  `Direction_Y` float(11,6) NOT NULL DEFAULT 0.000000,
  `Direction_Z` float(11,6) NOT NULL DEFAULT 0.000000,
  `ZennyInventory` bigint(20) NOT NULL DEFAULT 0,
  `ZennyBank` bigint(20) NOT NULL DEFAULT 0,
  `Token` int(10) unsigned NOT NULL DEFAULT 0,
  `WP_Point` int(10) DEFAULT 0,
  `CashPoint` int(10) DEFAULT 999999,
  `MixLevel` int(10) NOT NULL DEFAULT 1,
  `IsAdult` tinyint(1) NOT NULL DEFAULT 0,
  `IsTutorialDone` tinyint(1) NOT NULL DEFAULT 1,
  `IsToRename` tinyint(1) NOT NULL DEFAULT 0,
  `IsToDelete` tinyint(1) NOT NULL DEFAULT 0,
  `IsToChangeClass` tinyint(1) NOT NULL DEFAULT 0,
  `IsOnline` tinyint(1) NOT NULL DEFAULT 0,
  `IsGameMaster` tinyint(1) NOT NULL DEFAULT 0,
  `HintsDone` bigint(20) unsigned NOT NULL DEFAULT 0,
  `Reputation` bigint(20) unsigned NOT NULL DEFAULT 0,
  `Mudosa` bigint(20) unsigned NOT NULL DEFAULT 0,
  `SkillPoints` int(10) unsigned NOT NULL DEFAULT 69,
  `createdAt` varchar(20) DEFAULT NULL,
  `Title_Marking` int(10) NOT NULL DEFAULT 0,
  `IsVip` int(10) DEFAULT 0,
  `MixExp` int(10) NOT NULL DEFAULT 0,
  `deletionStartedAt` varchar(20) DEFAULT NULL,
  `MailIsAway` int(10) DEFAULT 0,
  `GSHandle` int(20) DEFAULT NULL,
  `WagguCoin` int(10) DEFAULT 9999,
  `EventCoin` int(10) DEFAULT 0,
  PRIMARY KEY (`CharacterID`),
  UNIQUE KEY `CharacterID_UNIQUE` (`CharacterID`),
  UNIQUE KEY `Name_UNIQUE` (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of characters
-- ----------------------------

-- ----------------------------
-- Table structure for `characters_attributes`
-- ----------------------------
DROP TABLE IF EXISTS `characters_attributes`;
CREATE TABLE `characters_attributes` (
  `ID` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) NOT NULL,
  `BaseStr` int(3) DEFAULT 10,
  `LastStr` int(3) DEFAULT 10,
  `BaseCon` int(3) DEFAULT 10,
  `LastCon` int(3) DEFAULT 10,
  `BaseFoc` int(3) DEFAULT 10,
  `LastFoc` int(3) DEFAULT 10,
  `BaseDex` int(3) DEFAULT 10,
  `LastDex` int(3) DEFAULT 10,
  `BaseSol` int(3) DEFAULT 10,
  `LastSol` int(3) DEFAULT 10,
  `BaseEng` int(3) DEFAULT 10,
  `LastEng` int(3) DEFAULT 10,
  `BaseMaxLP` int(5) DEFAULT 100,
  `LastMaxLP` int(5) DEFAULT 100,
  `BaseMaxEP` int(5) DEFAULT 100,
  `LastMaxEP` int(5) DEFAULT 100,
  `BaseMaxRP` int(5) DEFAULT 100,
  `LastMaxRP` int(5) DEFAULT 100,
  `BaseLpRegen` int(5) DEFAULT 0,
  `LastLpRegen` int(5) DEFAULT 0,
  `BaseLpSitdownRegen` int(5) DEFAULT 0,
  `LastLpSitdownRegen` int(5) DEFAULT 0,
  `BaseLpBattleRegen` int(5) DEFAULT 0,
  `LastLpBattleRegen` int(5) DEFAULT 0,
  `BaseEpRegen` int(5) DEFAULT 0,
  `LastEpRegen` int(5) DEFAULT 0,
  `BaseEpSitdownRegen` int(5) DEFAULT 0,
  `LastEpSitdownRegen` int(5) DEFAULT 0,
  `BaseEpBattleRegen` int(5) DEFAULT 0,
  `LastEpBattleRegen` int(5) DEFAULT 0,
  `BaseRpRegen` int(5) DEFAULT 0,
  `LastRpRegen` int(5) DEFAULT 0,
  `LastRpDimimutionRate` int(5) DEFAULT 0,
  `BasePhysicalOffence` int(5) DEFAULT 10,
  `LastPhysicalOffence` int(5) DEFAULT 10,
  `BasePhysicalDefence` int(5) DEFAULT 10,
  `LastPhysicalDefence` int(5) DEFAULT 10,
  `BaseEnergyOffence` int(5) DEFAULT 10,
  `LastEnergyOffence` int(5) DEFAULT 10,
  `BaseEnergyDefence` int(5) DEFAULT 10,
  `LastEnergyDefence` int(5) DEFAULT 10,
  `BaseAttackRate` int(5) DEFAULT 2,
  `LastAttackRate` int(5) DEFAULT 2,
  `BaseDodgeRate` int(5) DEFAULT 2,
  `LastDodgeRate` int(5) DEFAULT 2,
  `BaseBlockRate` int(5) DEFAULT 2,
  `LastBlockRate` int(5) DEFAULT 2,
  `BaseCurseSuccessRate` int(5) DEFAULT 0,
  `LastCurseSuccessRate` int(5) DEFAULT 0,
  `BaseCurseToleranceRate` int(5) DEFAULT 0,
  `LastCurseToleranceRate` int(5) DEFAULT 0,
  `BasePhysicalCriticalRate` int(5) DEFAULT 0,
  `LastPhysicalCriticalRate` int(5) DEFAULT 0,
  `BaseEnergyCriticalRate` int(5) DEFAULT 0,
  `LastEnergyCriticalRate` int(5) DEFAULT 0,
  `LastRunSpeed` float(10,5) DEFAULT 8.00000,
  `BaseAttackSpeedRate` int(5) DEFAULT 1000,
  `LastAttackSpeedRate` int(5) DEFAULT 1000,
  `BaseAttackRange` float(10,5) DEFAULT 10.00000,
  `LastAttackRange` float(10,5) DEFAULT 10.00000,
  `CastingTimeChangePercent` float(10,5) DEFAULT 100.00000,
  `CoolTimeChangePercent` float(10,5) DEFAULT 100.00000,
  `KeepTimeChangePercent` float(10,5) DEFAULT 100.00000,
  `DotValueChangePercent` float(10,5) DEFAULT 100.00000,
  `DotTimeChangeAbsolute` float(10,5) DEFAULT 100.00000,
  `RequiredEpChangePercent` float(10,5) DEFAULT 100.00000,
  `HonestOffence` float(10,5) DEFAULT 0.00000,
  `HonestDefence` float(10,5) DEFAULT 0.00000,
  `StrangeOffence` float(10,5) DEFAULT 0.00000,
  `StrangeDefence` float(10,5) DEFAULT 0.00000,
  `WildOffence` float(10,5) DEFAULT 0.00000,
  `WildDefence` float(10,5) DEFAULT 0.00000,
  `EleganceOffence` float(10,5) DEFAULT 0.00000,
  `EleganceDefence` float(10,5) DEFAULT 0.00000,
  `FunnyOffence` float(10,5) DEFAULT 0.00000,
  `FunnyDefence` float(10,5) DEFAULT 0.00000,
  `ParalyzeToleranceRate` int(5) DEFAULT 0,
  `TerrorToleranceRate` int(5) DEFAULT 0,
  `ConfuseToleranceRate` int(5) DEFAULT 0,
  `StoneToleranceRate` int(5) DEFAULT 0,
  `CandyToleranceRate` int(5) DEFAULT 0,
  `ParalyzeKeepTimeDown` float(10,5) DEFAULT 0.00000,
  `TerrorKeepTimeDown` float(10,5) DEFAULT 0.00000,
  `ConfuseKeepTimeDown` float(10,5) DEFAULT 0.00000,
  `StoneKeepTimeDown` float(10,5) DEFAULT 0.00000,
  `CandyKeepTimeDown` float(10,5) DEFAULT 0.00000,
  `BleedingKeepTimeDown` float(10,5) DEFAULT 0.00000,
  `PoisonKeepTimeDown` float(10,5) DEFAULT 0.00000,
  `StomachacheKeepTimeDown` float(10,5) DEFAULT 0.00000,
  `CriticalBlockSuccessRate` float(10,5) DEFAULT 0.00000,
  `GuardRate` int(5) DEFAULT 0,
  `SkillDamageBlockModeSuccessRate` float(10,5) DEFAULT 0.00000,
  `CurseBlockModeSuccessRate` float(10,5) DEFAULT 0.00000,
  `KnockdownBlockModeSuccessRate` float(10,5) DEFAULT 0.00000,
  `HtbBlockModeSuccessRate` float(10,5) DEFAULT 0.00000,
  `SitDownLpRegenBonusRate` float(10,5) DEFAULT 0.00000,
  `SitDownEpRegenBonusRate` float(10,5) DEFAULT 0.00000,
  `PhysicalCriticalDamageBonusRate` float(10,5) DEFAULT 0.00000,
  `EnergyCriticalDamageBonusRate` float(10,5) DEFAULT 0.00000,
  `ItemUpgradeBonusRate` float(10,5) DEFAULT 0.00000,
  `ItemUpgradeBreakBonusRate` float(10,5) DEFAULT 0.00000,
  `CurAP` int(10) DEFAULT 450000 COMMENT 'FlyingAP',
  `CurLP` int(10) DEFAULT 100,
  `CurEP` int(10) DEFAULT 100,
  `CurRP` int(10) DEFAULT 100,
  `LastMaxAp` int(5) DEFAULT 450000,
  `BaseMaxAp` int(5) DEFAULT 450000,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of characters_attributes
-- ----------------------------

-- ----------------------------
-- Table structure for `charquestlist`
-- ----------------------------
DROP TABLE IF EXISTS `charquestlist`;
CREATE TABLE `charquestlist` (
  `pkQtTable` int(11) NOT NULL AUTO_INCREMENT,
  `charId` int(10) NOT NULL,
  `questID` int(100) NOT NULL,
  `isCompleted` smallint(1) NOT NULL DEFAULT 0,
  `currentStep` int(255) NOT NULL DEFAULT 255,
  `type` smallint(1) NOT NULL,
  `dwEventData` int(255) NOT NULL,
  `nextStep` int(255) NOT NULL DEFAULT 2,
  `timeRemaing` int(15) NOT NULL DEFAULT 255,
  PRIMARY KEY (`pkQtTable`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of charquestlist
-- ----------------------------

-- ----------------------------
-- Table structure for `friendlist`
-- ----------------------------
DROP TABLE IF EXISTS `friendlist`;
CREATE TABLE `friendlist` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(10) NOT NULL,
  `friend_id` int(10) NOT NULL,
  `friend_name` varchar(20) NOT NULL,
  `blacklist` bit(1) NOT NULL DEFAULT b'0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of friendlist
-- ----------------------------

-- ----------------------------
-- Table structure for `guild_members`
-- ----------------------------
DROP TABLE IF EXISTS `guild_members`;
CREATE TABLE `guild_members` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `GuildID` int(5) NOT NULL,
  `MemberID` int(10) NOT NULL,
  `MemberName` varchar(30) NOT NULL,
  `is_guildmaster` tinyint(1) DEFAULT 0,
  `is_secondguildmaster` tinyint(1) DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of guild_members
-- ----------------------------

-- ----------------------------
-- Table structure for `guilds`
-- ----------------------------
DROP TABLE IF EXISTS `guilds`;
CREATE TABLE `guilds` (
  `GuildID` int(5) NOT NULL AUTO_INCREMENT,
  `GuildName` varchar(30) DEFAULT NULL,
  `GuildMasterName` varchar(30) DEFAULT NULL,
  `GuildMaster` int(10) DEFAULT NULL,
  `GuildSecondMaster` int(10) DEFAULT 0,
  `GuildNotice` varchar(256) DEFAULT NULL,
  `GuildReputation` int(10) DEFAULT 0,
  `GuildPointEver` int(10) DEFAULT 0,
  `GuildDisbandTime` datetime DEFAULT NULL,
  `GuildFunctions` int(15) DEFAULT 0,
  PRIMARY KEY (`GuildID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of guilds
-- ----------------------------

-- ----------------------------
-- Table structure for `hoipoimix`
-- ----------------------------
DROP TABLE IF EXISTS `hoipoimix`;
CREATE TABLE `hoipoimix` (
  `ID` int(10) NOT NULL AUTO_INCREMENT,
  `CharID` int(11) DEFAULT 0,
  `RecipeID` int(11) DEFAULT 0,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of hoipoimix
-- ----------------------------

-- ----------------------------
-- Table structure for `itematributes`
-- ----------------------------
DROP TABLE IF EXISTS `itematributes`;
CREATE TABLE `itematributes` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `tblidx` int(11) unsigned NOT NULL DEFAULT 0,
  `owner_id` int(11) unsigned NOT NULL DEFAULT 0,
  `place` int(11) DEFAULT NULL,
  `pos` int(11) DEFAULT NULL,
  `AtributeType1` int(11) DEFAULT 0,
  `AtributeValue1` int(11) DEFAULT 0,
  `AtributeType2` int(11) DEFAULT 0,
  `AtributeValue2` int(11) DEFAULT 0,
  `AtributeType3` int(11) DEFAULT 0,
  `AtributeValue3` int(11) DEFAULT 0,
  `AtributeType4` int(11) DEFAULT 0,
  `AtributeValue4` int(11) DEFAULT 0,
  `AtributeType5` int(11) DEFAULT 0,
  `AtributeValue5` int(11) DEFAULT 0,
  `AtributeType6` int(11) DEFAULT 0,
  `AtributeValue6` int(11) DEFAULT 0,
  `DogiAtributeType1` int(11) DEFAULT 0,
  `DogiAtributeValue1` int(11) DEFAULT 0,
  `DogiAtributeType2` int(11) DEFAULT 0,
  `DogiAtributeValue2` int(11) DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of itematributes
-- ----------------------------

-- ----------------------------
-- Table structure for `items`
-- ----------------------------
DROP TABLE IF EXISTS `items`;
CREATE TABLE `items` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `tblidx` int(11) unsigned NOT NULL DEFAULT 0,
  `owner_id` int(11) unsigned NOT NULL DEFAULT 0,
  `place` tinyint(1) unsigned NOT NULL DEFAULT 1,
  `pos` smallint(5) unsigned NOT NULL DEFAULT 0,
  `count` smallint(3) unsigned NOT NULL DEFAULT 1,
  `rank` tinyint(1) unsigned NOT NULL DEFAULT 1,
  `durability` smallint(3) unsigned NOT NULL DEFAULT 100,
  `grade` tinyint(1) unsigned NOT NULL DEFAULT 0,
  `battleAttribute` int(11) DEFAULT 0,
  `option0` int(11) DEFAULT 0,
  `option1` int(11) DEFAULT 0,
  `AtributeType1` int(11) DEFAULT 0,
  `AtributeValue1` int(11) DEFAULT 0,
  `AtributeType2` int(11) DEFAULT 0,
  `AtributeValue2` int(11) DEFAULT 0,
  `AtributeType3` int(11) DEFAULT 0,
  `AtributeValue3` int(11) DEFAULT 0,
  `AtributeType4` int(11) DEFAULT 0,
  `AtributeValue4` int(11) DEFAULT 0,
  `AtributeType5` int(11) DEFAULT 0,
  `AtributeValue5` int(11) DEFAULT 0,
  `AtributeType6` int(11) DEFAULT 0,
  `AtributeValue6` int(11) DEFAULT 0,
  `DogiAtributeType1` int(11) DEFAULT 0,
  `DogiAtributeValue1` int(11) DEFAULT 0,
  `DogiAtributeType2` int(11) DEFAULT 0,
  `DogiAtributeValue2` int(11) DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `owner_id_idx` (`owner_id`),
  KEY `item_vnum_index` (`tblidx`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of items
-- ----------------------------

-- ----------------------------
-- Table structure for `mail`
-- ----------------------------
DROP TABLE IF EXISTS `mail`;
CREATE TABLE `mail` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(11) DEFAULT NULL,
  `byDay` tinyint(2) DEFAULT NULL,
  `tCreateTime` int(50) NOT NULL,
  `SenderType` tinyint(1) NOT NULL DEFAULT 0,
  `byMailType` tinyint(1) NOT NULL,
  `byTextSize` int(10) DEFAULT NULL,
  `dwZenny` int(10) DEFAULT 0,
  `wszText` varchar(130) DEFAULT NULL,
  `item_id` int(11) DEFAULT NULL,
  `item_place` int(10) DEFAULT NULL,
  `item_pos` int(10) DEFAULT NULL,
  `grade` int(11) DEFAULT 0,
  `StackCount` int(10) DEFAULT 1,
  `wszTargetName` varchar(16) DEFAULT NULL,
  `wszFromName` varchar(16) DEFAULT NULL,
  `bIsAccept` int(1) DEFAULT NULL,
  `bIsLock` int(1) DEFAULT NULL,
  `bIsRead` int(1) DEFAULT NULL,
  `AtributeValue1` int(11) DEFAULT 0,
  `AtributeType2` int(11) DEFAULT 0,
  `AtributeValue2` int(11) DEFAULT 0,
  `AtributeType3` int(11) DEFAULT 0,
  `AtributeValue3` int(11) DEFAULT 0,
  `AtributeType4` int(11) DEFAULT 0,
  `AtributeValue4` int(11) DEFAULT 0,
  `AtributeType5` int(11) DEFAULT 0,
  `AtributeValue5` int(11) DEFAULT 0,
  `AtributeType6` int(11) DEFAULT 0,
  `AtributeValue6` int(11) DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of mail
-- ----------------------------

-- ----------------------------
-- Table structure for `mascotinfo`
-- ----------------------------
DROP TABLE IF EXISTS `mascotinfo`;
CREATE TABLE `mascotinfo` (
  `ID` int(10) NOT NULL AUTO_INCREMENT,
  `CharID` int(11) DEFAULT 0,
  `MascotID` int(11) DEFAULT 0,
  `Slot` int(5) DEFAULT 0,
  `CurVP` int(11) DEFAULT 0,
  `MaxVP` int(11) DEFAULT 0,
  `Exp` int(11) DEFAULT 0,
  `Skill_count` int(5) DEFAULT 1,
  `Skill1` int(11) DEFAULT 0,
  `Skill2` int(11) DEFAULT 0,
  `Skill3` int(11) DEFAULT 0,
  `Skill4` int(11) DEFAULT 0,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of mascotinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `portals`
-- ----------------------------
DROP TABLE IF EXISTS `portals`;
CREATE TABLE `portals` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) DEFAULT NULL,
  `PortalID` smallint(3) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of portals
-- ----------------------------

-- ----------------------------
-- Table structure for `quickslot`
-- ----------------------------
DROP TABLE IF EXISTS `quickslot`;
CREATE TABLE `quickslot` (
  `pkQuick` int(15) NOT NULL AUTO_INCREMENT,
  `charId` int(11) DEFAULT NULL,
  `slotId_0` int(10) unsigned DEFAULT 0,
  `slotId_1` int(10) unsigned DEFAULT 0,
  `slotId_2` int(10) unsigned DEFAULT 0,
  `slotId_3` int(10) unsigned DEFAULT 0,
  `slotId_4` int(10) unsigned DEFAULT 0,
  `slotId_5` int(10) unsigned DEFAULT 0,
  `slotId_6` int(10) unsigned DEFAULT 0,
  `slotId_7` int(10) unsigned DEFAULT 0,
  `slotId_8` int(10) unsigned DEFAULT 0,
  `slotId_9` int(10) unsigned DEFAULT 0,
  `slotId_10` int(10) unsigned DEFAULT 0,
  `slotId_11` int(10) unsigned DEFAULT 0,
  `slotId_12` int(10) unsigned DEFAULT 0,
  `slotId_13` int(10) unsigned DEFAULT 0,
  `slotId_14` int(10) unsigned DEFAULT 0,
  `slotId_15` int(10) unsigned DEFAULT 0,
  `slotId_16` int(10) unsigned DEFAULT 0,
  `slotId_17` int(10) unsigned DEFAULT 0,
  `slotId_18` int(10) unsigned DEFAULT 0,
  `slotId_19` int(10) unsigned DEFAULT 0,
  `slotId_20` int(10) unsigned DEFAULT 0,
  `slotId_21` int(10) unsigned DEFAULT 0,
  `slotId_22` int(10) unsigned DEFAULT 0,
  `slotId_23` int(10) unsigned DEFAULT 0,
  `slotId_24` int(10) unsigned DEFAULT 0,
  `slotId_25` int(10) unsigned DEFAULT 0,
  `slotId_26` int(10) unsigned DEFAULT 0,
  `slotId_27` int(10) unsigned DEFAULT 0,
  `slotId_28` int(10) unsigned DEFAULT 0,
  `slotId_29` int(10) unsigned DEFAULT 0,
  `slotId_30` int(10) unsigned DEFAULT 0,
  `slotId_31` int(10) unsigned DEFAULT 0,
  `slotId_32` int(10) unsigned DEFAULT 0,
  `slotId_33` int(10) unsigned DEFAULT 0,
  `slotId_34` int(10) unsigned DEFAULT 0,
  `slotId_35` int(10) unsigned DEFAULT 0,
  `slotId_36` int(10) unsigned DEFAULT 0,
  `slotId_37` int(10) unsigned DEFAULT 0,
  `slotId_38` int(10) unsigned DEFAULT 0,
  `slotId_39` int(10) unsigned DEFAULT 0,
  `slotId_40` int(10) unsigned DEFAULT 0,
  `slotId_41` int(10) unsigned DEFAULT 0,
  `slotId_42` int(10) unsigned DEFAULT 0,
  `slotId_43` int(10) unsigned DEFAULT 0,
  `slotId_44` int(10) unsigned DEFAULT 0,
  `slotId_45` int(10) unsigned DEFAULT 0,
  `slotId_46` int(10) unsigned DEFAULT 0,
  `slotId_47` int(10) DEFAULT NULL,
  `placeID` int(10) DEFAULT NULL,
  PRIMARY KEY (`pkQuick`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of quickslot
-- ----------------------------

-- ----------------------------
-- Table structure for `quickteleporter`
-- ----------------------------
DROP TABLE IF EXISTS `quickteleporter`;
CREATE TABLE `quickteleporter` (
  `ID` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) DEFAULT NULL,
  `TeleportID` int(10) DEFAULT NULL,
  `WorldID` int(10) DEFAULT NULL,
  `Loc_x` float(11,0) DEFAULT NULL,
  `Loc_y` float(11,0) DEFAULT NULL,
  `Loc_z` float(11,0) DEFAULT NULL,
  `Year` int(10) DEFAULT NULL,
  `Moch` int(10) DEFAULT NULL,
  `Day` int(10) DEFAULT NULL,
  `Hour` int(10) DEFAULT NULL,
  `Minute` int(10) DEFAULT NULL,
  `Secound` int(10) DEFAULT NULL,
  `MapTblidx` int(10) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of quickteleporter
-- ----------------------------

-- ----------------------------
-- Table structure for `realmlist`
-- ----------------------------
DROP TABLE IF EXISTS `realmlist`;
CREATE TABLE `realmlist` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `ServerID` int(11) unsigned NOT NULL DEFAULT 0,
  `ChannelID` int(11) unsigned NOT NULL DEFAULT 0,
  `realmflags` tinyint(3) unsigned NOT NULL DEFAULT 2,
  `population` float unsigned NOT NULL DEFAULT 0,
  `IsEvent` int(11) DEFAULT 0,
  `Name` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Realm System';

-- ----------------------------
-- Records of realmlist
-- ----------------------------
INSERT INTO `realmlist` VALUES ('1', '1', '1', '0', '0', '0', null);
INSERT INTO `realmlist` VALUES ('2', '2', '1', '0', '0', '0', null);

-- ----------------------------
-- Table structure for `skills`
-- ----------------------------
DROP TABLE IF EXISTS `skills`;
CREATE TABLE `skills` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `skill_id` int(10) unsigned NOT NULL DEFAULT 0,
  `owner_id` int(11) unsigned NOT NULL,
  `RpBonusAuto` bit(1) DEFAULT b'0',
  `RpBonusType` int(5) unsigned NOT NULL DEFAULT 0,
  `SlotID` smallint(3) unsigned NOT NULL DEFAULT 0,
  `TimeRemaining` int(15) unsigned NOT NULL DEFAULT 0,
  `Exp` int(5) unsigned NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of skills
-- ----------------------------

-- ----------------------------
-- Table structure for `titlelist`
-- ----------------------------
DROP TABLE IF EXISTS `titlelist`;
CREATE TABLE `titlelist` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) DEFAULT NULL,
  `TitleID` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of titlelist
-- ----------------------------

-- ----------------------------
-- Table structure for `warfoginfo`
-- ----------------------------
DROP TABLE IF EXISTS `warfoginfo`;
CREATE TABLE `warfoginfo` (
  `idFog` int(11) NOT NULL AUTO_INCREMENT,
  `hObject` int(11) NOT NULL,
  `owner_id` int(10) NOT NULL,
  PRIMARY KEY (`idFog`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of warfoginfo
-- ----------------------------
