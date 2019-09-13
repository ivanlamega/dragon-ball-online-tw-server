/*
 Navicat Premium Data Transfer

 Source Server         : dbo
 Source Server Type    : MySQL
 Source Server Version : 50718
 Source Host           : localhost:3306
 Source Schema         : dbo

 Target Server Type    : MySQL
 Target Server Version : 50718
 File Encoding         : 65001

 Date: 09/07/2017 15:33:38
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for account
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account`  (
  `AccountID` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT,
  `UserName` varchar(16) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `UserPassword` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `IsBanned` tinyint(1) NOT NULL DEFAULT 0,
  `IsGM` tinyint(1) NOT NULL DEFAULT 0,
  `LastServerID` int(11) NOT NULL DEFAULT 255,
  `LastChannelID` int(11) NOT NULL DEFAULT 255,
  `AccountStatus` tinyint(1) NOT NULL DEFAULT 0,
  `email` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `ip` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`AccountID`) USING BTREE,
  UNIQUE INDEX `AccountID_UNIQUE`(`AccountID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 3 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for bind
-- ----------------------------
DROP TABLE IF EXISTS `bind`;
CREATE TABLE `bind`  (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) NOT NULL,
  `WorldID` tinyint(3) NOT NULL,
  `BindObjectTblIdx` int(10) NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for characters
-- ----------------------------
DROP TABLE IF EXISTS `characters`;
CREATE TABLE `characters`  (
  `CharacterID` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT,
  `AccountID` bigint(20) UNSIGNED NOT NULL,
  `GuildID` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `Name` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `ServerID` int(10) UNSIGNED NOT NULL,
  `RaceID` int(10) UNSIGNED NOT NULL,
  `ClassID` int(10) UNSIGNED NOT NULL,
  `GenderID` int(10) UNSIGNED NOT NULL,
  `FaceID` int(10) UNSIGNED NOT NULL,
  `HairID` int(10) UNSIGNED NOT NULL,
  `HairColorID` int(10) UNSIGNED NOT NULL,
  `SkinColorID` int(10) UNSIGNED NOT NULL,
  `CurrentLevel` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `CurrentExp` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `MapInfoID` bigint(20) UNSIGNED NOT NULL DEFAULT 4294967295,
  `WorldTableID` bigint(20) UNSIGNED NOT NULL DEFAULT 1,
  `WorldID` bigint(20) UNSIGNED NOT NULL DEFAULT 1,
  `BindType` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `BindWorldID` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `BindObjectID` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `Position_X` float(11, 6) NOT NULL DEFAULT 0.000000,
  `Position_Y` float(11, 6) NOT NULL DEFAULT 0.000000,
  `Position_Z` float(11, 6) NOT NULL DEFAULT 0.000000,
  `Direction_X` float(11, 6) NOT NULL DEFAULT 0.000000,
  `Direction_Y` float(11, 6) NOT NULL DEFAULT 0.000000,
  `Direction_Z` float(11, 6) NOT NULL DEFAULT 0.000000,
  `ZennyInventory` bigint(20) NOT NULL DEFAULT 0,
  `ZennyBank` bigint(20) NOT NULL DEFAULT 0,
  `Token` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `WP_Point` int(10) NOT NULL DEFAULT 0,
  `CashPoint` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `IsVip` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Title_Marking` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `MixExp` int(10) NOT NULL DEFAULT 0,
  `MixLevel` int(10) NOT NULL DEFAULT 1,
  `IsAdult` tinyint(1) NOT NULL DEFAULT 0,
  `IsTutorialDone` tinyint(1) NOT NULL DEFAULT 0,
  `IsToRename` tinyint(1) NOT NULL DEFAULT 0,
  `IsToDelete` tinyint(1) NOT NULL DEFAULT 0,
  `IsToChangeClass` tinyint(1) NOT NULL DEFAULT 0,
  `IsOnline` tinyint(1) NOT NULL DEFAULT 0,
  `IsGameMaster` tinyint(1) NOT NULL DEFAULT 0,
  `HintsDone` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `Reputation` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `Mudosa` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `SkillPoints` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `createdAt` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `deletionStartedAt` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`CharacterID`) USING BTREE,
  UNIQUE INDEX `CharacterID_UNIQUE`(`CharacterID`) USING BTREE,
  UNIQUE INDEX `Name_UNIQUE`(`Name`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 2 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for characters_attributes
-- ----------------------------
DROP TABLE IF EXISTS `characters_attributes`;
CREATE TABLE `characters_attributes`  (
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
  `LastRunSpeed` float(10, 5) DEFAULT 8.00000,
  `BaseAttackSpeedRate` int(5) DEFAULT 1000,
  `LastAttackSpeedRate` int(5) DEFAULT 1000,
  `BaseAttackRange` float(10, 5) DEFAULT 10.00000,
  `LastAttackRange` float(10, 5) DEFAULT 10.00000,
  `CastingTimeChangePercent` float(10, 5) DEFAULT 100.00000,
  `CoolTimeChangePercent` float(10, 5) DEFAULT 100.00000,
  `KeepTimeChangePercent` float(10, 5) DEFAULT 100.00000,
  `DotValueChangePercent` float(10, 5) DEFAULT 100.00000,
  `DotTimeChangeAbsolute` float(10, 5) DEFAULT 100.00000,
  `RequiredEpChangePercent` float(10, 5) DEFAULT 100.00000,
  `HonestOffence` float(10, 5) DEFAULT 0.00000,
  `HonestDefence` float(10, 5) DEFAULT 0.00000,
  `StrangeOffence` float(10, 5) DEFAULT 0.00000,
  `StrangeDefence` float(10, 5) DEFAULT 0.00000,
  `WildOffence` float(10, 5) DEFAULT 0.00000,
  `WildDefence` float(10, 5) DEFAULT 0.00000,
  `EleganceOffence` float(10, 5) DEFAULT 0.00000,
  `EleganceDefence` float(10, 5) DEFAULT 0.00000,
  `FunnyOffence` float(10, 5) DEFAULT 0.00000,
  `FunnyDefence` float(10, 5) DEFAULT 0.00000,
  `ParalyzeToleranceRate` int(5) DEFAULT 0,
  `TerrorToleranceRate` int(5) DEFAULT 0,
  `ConfuseToleranceRate` int(5) DEFAULT 0,
  `StoneToleranceRate` int(5) DEFAULT 0,
  `CandyToleranceRate` int(5) DEFAULT 0,
  `ParalyzeKeepTimeDown` float(10, 5) DEFAULT 0.00000,
  `TerrorKeepTimeDown` float(10, 5) DEFAULT 0.00000,
  `ConfuseKeepTimeDown` float(10, 5) DEFAULT 0.00000,
  `StoneKeepTimeDown` float(10, 5) DEFAULT 0.00000,
  `CandyKeepTimeDown` float(10, 5) DEFAULT 0.00000,
  `BleedingKeepTimeDown` float(10, 5) DEFAULT 0.00000,
  `PoisonKeepTimeDown` float(10, 5) DEFAULT 0.00000,
  `StomachacheKeepTimeDown` float(10, 5) DEFAULT 0.00000,
  `CriticalBlockSuccessRate` float(10, 5) DEFAULT 0.00000,
  `GuardRate` int(5) DEFAULT 0,
  `SkillDamageBlockModeSuccessRate` float(10, 5) DEFAULT 0.00000,
  `CurseBlockModeSuccessRate` float(10, 5) DEFAULT 0.00000,
  `KnockdownBlockModeSuccessRate` float(10, 5) DEFAULT 0.00000,
  `HtbBlockModeSuccessRate` float(10, 5) DEFAULT 0.00000,
  `SitDownLpRegenBonusRate` float(10, 5) DEFAULT 0.00000,
  `SitDownEpRegenBonusRate` float(10, 5) DEFAULT 0.00000,
  `PhysicalCriticalDamageBonusRate` float(10, 5) DEFAULT 0.00000,
  `EnergyCriticalDamageBonusRate` float(10, 5) DEFAULT 0.00000,
  `ItemUpgradeBonusRate` float(10, 5) DEFAULT 0.00000,
  `ItemUpgradeBreakBonusRate` float(10, 5) DEFAULT 0.00000,
  `CurAP` int(10) DEFAULT 450000 COMMENT 'FlyingAP',
  `CurLP` int(10) DEFAULT 100,
  `CurEP` int(10) DEFAULT 100,
  `CurRP` int(10) DEFAULT 100,
  `LastMaxAp` int(5) DEFAULT 450000,
  `BaseMaxAp` int(5) DEFAULT 450000,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for items
-- ----------------------------
DROP TABLE IF EXISTS `items`;
CREATE TABLE `items`  (
  `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `tblidx` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `place` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `pos` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `count` smallint(3) UNSIGNED NOT NULL DEFAULT 1,
  `rank` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `durability` smallint(3) UNSIGNED NOT NULL DEFAULT 100,
  `grade` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `battleAttribute` int(11) DEFAULT 0,
  `option0` int(11) DEFAULT 0,
  `option1` int(11) DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `owner_id_idx`(`owner_id`) USING BTREE,
  INDEX `item_vnum_index`(`tblidx`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Table structure for portals
-- ----------------------------
DROP TABLE IF EXISTS `portals`;
CREATE TABLE `portals`  (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) DEFAULT NULL,
  `PortalID` smallint(3) DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for quickslot
-- ----------------------------
DROP TABLE IF EXISTS `quickslot`;
CREATE TABLE `quickslot`  (
  `pkQuick` int(15) NOT NULL AUTO_INCREMENT,
  `charId` int(11) DEFAULT NULL,
  `slotId_0` int(10) UNSIGNED DEFAULT 0,
  `slotId_1` int(10) UNSIGNED DEFAULT 0,
  `slotId_2` int(10) UNSIGNED DEFAULT 0,
  `slotId_3` int(10) UNSIGNED DEFAULT 0,
  `slotId_4` int(10) UNSIGNED DEFAULT 0,
  `slotId_5` int(10) UNSIGNED DEFAULT 0,
  `slotId_6` int(10) UNSIGNED DEFAULT 0,
  `slotId_7` int(10) UNSIGNED DEFAULT 0,
  `slotId_8` int(10) UNSIGNED DEFAULT 0,
  `slotId_9` int(10) UNSIGNED DEFAULT 0,
  `slotId_10` int(10) UNSIGNED DEFAULT 0,
  `slotId_11` int(10) UNSIGNED DEFAULT 0,
  `slotId_12` int(10) UNSIGNED DEFAULT 0,
  `slotId_13` int(10) UNSIGNED DEFAULT 0,
  `slotId_14` int(10) UNSIGNED DEFAULT 0,
  `slotId_15` int(10) UNSIGNED DEFAULT 0,
  `slotId_16` int(10) UNSIGNED DEFAULT 0,
  `slotId_17` int(10) UNSIGNED DEFAULT 0,
  `slotId_18` int(10) UNSIGNED DEFAULT 0,
  `slotId_19` int(10) UNSIGNED DEFAULT 0,
  `slotId_20` int(10) UNSIGNED DEFAULT 0,
  `slotId_21` int(10) UNSIGNED DEFAULT 0,
  `slotId_22` int(10) UNSIGNED DEFAULT 0,
  `slotId_23` int(10) UNSIGNED DEFAULT 0,
  `slotId_24` int(10) UNSIGNED DEFAULT 0,
  `slotId_25` int(10) UNSIGNED DEFAULT 0,
  `slotId_26` int(10) UNSIGNED DEFAULT 0,
  `slotId_27` int(10) UNSIGNED DEFAULT 0,
  `slotId_28` int(10) UNSIGNED DEFAULT 0,
  `slotId_29` int(10) UNSIGNED DEFAULT 0,
  `slotId_30` int(10) UNSIGNED DEFAULT 0,
  `slotId_31` int(10) UNSIGNED DEFAULT 0,
  `slotId_32` int(10) UNSIGNED DEFAULT 0,
  `slotId_33` int(10) UNSIGNED DEFAULT 0,
  `slotId_34` int(10) UNSIGNED DEFAULT 0,
  `slotId_35` int(10) UNSIGNED DEFAULT 0,
  `slotId_36` int(10) UNSIGNED DEFAULT 0,
  `slotId_37` int(10) UNSIGNED DEFAULT 0,
  `slotId_38` int(10) UNSIGNED DEFAULT 0,
  `slotId_39` int(10) UNSIGNED DEFAULT 0,
  `slotId_40` int(10) UNSIGNED DEFAULT 0,
  `slotId_41` int(10) UNSIGNED DEFAULT 0,
  `slotId_42` int(10) UNSIGNED DEFAULT 0,
  `slotId_43` int(10) UNSIGNED DEFAULT 0,
  `slotId_44` int(10) UNSIGNED DEFAULT 0,
  `slotId_45` int(10) UNSIGNED DEFAULT 0,
  `slotId_46` int(10) UNSIGNED DEFAULT 0,
  `slotId_47` int(10) DEFAULT NULL,
  `placeID` int(10) DEFAULT NULL,
  PRIMARY KEY (`pkQuick`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for realmlist
-- ----------------------------
DROP TABLE IF EXISTS `realmlist`;
CREATE TABLE `realmlist`  (
  `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `ServerID` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `ChannelID` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `realmflags` tinyint(3) UNSIGNED NOT NULL DEFAULT 2,
  `population` float unsigned NOT NULL,
  `IsEvent` int(11) DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = 'Realm System' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for skills
-- ----------------------------
DROP TABLE IF EXISTS `skills`;
CREATE TABLE `skills`  (
  `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `skill_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(11) UNSIGNED NOT NULL,
  `RpBonusAuto` bit(1) DEFAULT b'0',
  `RpBonusType` int(5) UNSIGNED NOT NULL DEFAULT 0,
  `SlotID` smallint(3) UNSIGNED NOT NULL DEFAULT 0,
  `TimeRemaining` int(15) UNSIGNED NOT NULL,
  `Exp` int(5) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for titlelist
-- ----------------------------
DROP TABLE IF EXISTS `titlelist`;
CREATE TABLE `titlelist`  (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) DEFAULT NULL,
  `TitleID` smallint(3) DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for warfoginfo
-- ----------------------------
DROP TABLE IF EXISTS `warfoginfo`;
CREATE TABLE `warfoginfo`  (
  `idFog` int(11) NOT NULL AUTO_INCREMENT,
  `hObject` int(11) NOT NULL,
  `owner_id` int(10) NOT NULL,
  PRIMARY KEY (`idFog`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
