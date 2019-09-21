/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50621
Source Host           : localhost:3306
Source Database       : dragonball

Target Server Type    : MYSQL
Target Server Version : 50621
File Encoding         : 65001

Date: 2019-09-21 23:28:15
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
  `IsBanned` tinyint(1) NOT NULL DEFAULT '0',
  `IsGM` tinyint(1) NOT NULL DEFAULT '0',
  `LastServerID` int(11) NOT NULL DEFAULT '255',
  `LastChannelID` int(11) NOT NULL DEFAULT '255',
  `AccountStatus` tinyint(1) NOT NULL DEFAULT '0',
  `email` varchar(50) DEFAULT NULL,
  `ip` varchar(50) NOT NULL DEFAULT '127.0.0.1',
  PRIMARY KEY (`AccountID`) USING BTREE,
  UNIQUE KEY `AccountID_UNIQUE` (`AccountID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of account
-- ----------------------------
INSERT INTO `account` VALUES ('10', 'Test', '123', '0', '0', '0', '255', '0', null, '127.0.0.1');
INSERT INTO `account` VALUES ('11', 'admin', 'admin', '0', '1', '0', '255', '0', null, '127.0.0.1');

-- ----------------------------
-- Table structure for `bind`
-- ----------------------------
DROP TABLE IF EXISTS `bind`;
CREATE TABLE `bind` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) NOT NULL,
  `WorldID` tinyint(3) NOT NULL,
  `BindObjectTblIdx` int(10) NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of bind
-- ----------------------------
INSERT INTO `bind` VALUES ('1', '2', '1', '6');
INSERT INTO `bind` VALUES ('2', '3', '1', '6');
INSERT INTO `bind` VALUES ('3', '4', '1', '6');
INSERT INTO `bind` VALUES ('4', '5', '1', '6');
INSERT INTO `bind` VALUES ('5', '6', '1', '6');
INSERT INTO `bind` VALUES ('6', '7', '1', '6');
INSERT INTO `bind` VALUES ('7', '8', '1', '6');
INSERT INTO `bind` VALUES ('8', '9', '1', '6');
INSERT INTO `bind` VALUES ('9', '10', '1', '6');
INSERT INTO `bind` VALUES ('10', '11', '1', '6');
INSERT INTO `bind` VALUES ('11', '12', '1', '6');
INSERT INTO `bind` VALUES ('12', '13', '1', '6');
INSERT INTO `bind` VALUES ('13', '14', '1', '6');
INSERT INTO `bind` VALUES ('14', '1', '1', '6');

-- ----------------------------
-- Table structure for `cashitem`
-- ----------------------------
DROP TABLE IF EXISTS `cashitem`;
CREATE TABLE `cashitem` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `tblidx` int(11) unsigned NOT NULL DEFAULT '0',
  `owner_id` int(11) unsigned NOT NULL DEFAULT '0',
  `byStackCount` int(10) unsigned NOT NULL DEFAULT '1',
  `Year` int(10) DEFAULT NULL,
  `Month` int(10) DEFAULT NULL,
  `Day` int(10) DEFAULT NULL,
  `Hour` int(10) DEFAULT NULL,
  `Minute` int(10) DEFAULT NULL,
  `Secound` int(10) DEFAULT NULL,
  `Handle` int(11) DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `owner_id_idx` (`owner_id`),
  KEY `item_vnum_index` (`tblidx`)
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=latin1;

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
  `GuildID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `Name` varchar(20) NOT NULL,
  `ServerID` int(10) unsigned NOT NULL,
  `RaceID` int(10) unsigned NOT NULL,
  `ClassID` int(10) unsigned NOT NULL,
  `GenderID` int(10) unsigned NOT NULL,
  `FaceID` int(10) unsigned NOT NULL,
  `HairID` int(10) unsigned NOT NULL,
  `HairColorID` int(10) unsigned NOT NULL,
  `SkinColorID` int(10) unsigned NOT NULL,
  `CurrentLevel` int(10) unsigned NOT NULL DEFAULT '1',
  `CurrentExp` bigint(20) unsigned NOT NULL DEFAULT '0',
  `MapInfoID` bigint(20) unsigned NOT NULL DEFAULT '4294967295',
  `WorldTableID` bigint(20) unsigned NOT NULL DEFAULT '1',
  `WorldID` bigint(20) unsigned NOT NULL DEFAULT '1',
  `BindType` int(10) unsigned NOT NULL DEFAULT '0',
  `BindWorldID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `BindObjectID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `Position_X` float(11,6) NOT NULL DEFAULT '0.000000',
  `Position_Y` float(11,6) NOT NULL DEFAULT '0.000000',
  `Position_Z` float(11,6) NOT NULL DEFAULT '0.000000',
  `Direction_X` float(11,6) NOT NULL DEFAULT '0.000000',
  `Direction_Y` float(11,6) NOT NULL DEFAULT '0.000000',
  `Direction_Z` float(11,6) NOT NULL DEFAULT '0.000000',
  `ZennyInventory` bigint(20) NOT NULL DEFAULT '0',
  `ZennyBank` bigint(20) NOT NULL DEFAULT '0',
  `Token` int(10) unsigned NOT NULL DEFAULT '0',
  `WP_Point` int(10) NOT NULL DEFAULT '0',
  `CashPoint` int(10) unsigned NOT NULL DEFAULT '0',
  `IsVip` int(10) unsigned NOT NULL DEFAULT '0',
  `Title_Marking` int(10) unsigned NOT NULL DEFAULT '0',
  `MixExp` int(10) NOT NULL DEFAULT '0',
  `MixLevel` int(10) NOT NULL DEFAULT '1',
  `IsAdult` tinyint(1) NOT NULL DEFAULT '0',
  `IsTutorialDone` tinyint(1) NOT NULL DEFAULT '1',
  `IsToRename` tinyint(1) NOT NULL DEFAULT '0',
  `IsToDelete` tinyint(1) NOT NULL DEFAULT '0',
  `IsToChangeClass` tinyint(1) NOT NULL DEFAULT '0',
  `IsOnline` tinyint(1) NOT NULL DEFAULT '0',
  `IsGameMaster` tinyint(1) NOT NULL DEFAULT '0',
  `HintsDone` bigint(20) unsigned NOT NULL DEFAULT '0',
  `Reputation` bigint(20) unsigned NOT NULL DEFAULT '0',
  `Mudosa` bigint(20) unsigned NOT NULL DEFAULT '0',
  `SkillPoints` int(10) unsigned NOT NULL DEFAULT '0',
  `createdAt` varchar(20) DEFAULT NULL,
  `deletionStartedAt` varchar(20) DEFAULT NULL,
  `WagguCoin` int(11) NOT NULL DEFAULT '0',
  `EventCoin` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`CharacterID`) USING BTREE,
  UNIQUE KEY `CharacterID_UNIQUE` (`CharacterID`) USING BTREE,
  UNIQUE KEY `Name_UNIQUE` (`Name`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of characters
-- ----------------------------
INSERT INTO `characters` VALUES ('6', '10', '0', '[Dev]Test', '0', '0', '10', '0', '8', '1', '4', '2', '70', '0', '4294967295', '1', '1', '0', '0', '0', '5812.669922', '-100.300003', '775.619995', '0.842000', '0.000000', '0.539300', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0');
INSERT INTO `characters` VALUES ('8', '11', '0', 'Test', '0', '0', '0', '0', '3', '1', '4', '1', '1', '0', '4294967295', '1', '1', '0', '0', '0', '4878.000000', '-65.959999', '4079.000000', '-0.361400', '0.000000', '0.932400', '1000000000', '0', '0', '0', '899999775', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '0', null, null, '0', '0');

-- ----------------------------
-- Table structure for `characters_attributes`
-- ----------------------------
DROP TABLE IF EXISTS `characters_attributes`;
CREATE TABLE `characters_attributes` (
  `ID` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) NOT NULL,
  `BaseStr` int(3) DEFAULT '10',
  `LastStr` int(3) DEFAULT '10',
  `BaseCon` int(3) DEFAULT '10',
  `LastCon` int(3) DEFAULT '10',
  `BaseFoc` int(3) DEFAULT '10',
  `LastFoc` int(3) DEFAULT '10',
  `BaseDex` int(3) DEFAULT '10',
  `LastDex` int(3) DEFAULT '10',
  `BaseSol` int(3) DEFAULT '10',
  `LastSol` int(3) DEFAULT '10',
  `BaseEng` int(3) DEFAULT '10',
  `LastEng` int(3) DEFAULT '10',
  `BaseMaxLP` int(5) DEFAULT '100',
  `LastMaxLP` int(5) DEFAULT '100',
  `BaseMaxEP` int(5) DEFAULT '100',
  `LastMaxEP` int(5) DEFAULT '100',
  `BaseMaxRP` int(5) DEFAULT '100',
  `LastMaxRP` int(5) DEFAULT '100',
  `BaseLpRegen` int(5) DEFAULT '0',
  `LastLpRegen` int(5) DEFAULT '0',
  `BaseLpSitdownRegen` int(5) DEFAULT '0',
  `LastLpSitdownRegen` int(5) DEFAULT '0',
  `BaseLpBattleRegen` int(5) DEFAULT '0',
  `LastLpBattleRegen` int(5) DEFAULT '0',
  `BaseEpRegen` int(5) DEFAULT '0',
  `LastEpRegen` int(5) DEFAULT '0',
  `BaseEpSitdownRegen` int(5) DEFAULT '0',
  `LastEpSitdownRegen` int(5) DEFAULT '0',
  `BaseEpBattleRegen` int(5) DEFAULT '0',
  `LastEpBattleRegen` int(5) DEFAULT '0',
  `BaseRpRegen` int(5) DEFAULT '0',
  `LastRpRegen` int(5) DEFAULT '0',
  `LastRpDimimutionRate` int(5) DEFAULT '0',
  `BasePhysicalOffence` int(5) DEFAULT '10',
  `LastPhysicalOffence` int(5) DEFAULT '10',
  `BasePhysicalDefence` int(5) DEFAULT '10',
  `LastPhysicalDefence` int(5) DEFAULT '10',
  `BaseEnergyOffence` int(5) DEFAULT '10',
  `LastEnergyOffence` int(5) DEFAULT '10',
  `BaseEnergyDefence` int(5) DEFAULT '10',
  `LastEnergyDefence` int(5) DEFAULT '10',
  `BaseAttackRate` int(5) DEFAULT '2',
  `LastAttackRate` int(5) DEFAULT '2',
  `BaseDodgeRate` int(5) DEFAULT '2',
  `LastDodgeRate` int(5) DEFAULT '2',
  `BaseBlockRate` int(5) DEFAULT '2',
  `LastBlockRate` int(5) DEFAULT '2',
  `BaseCurseSuccessRate` int(5) DEFAULT '0',
  `LastCurseSuccessRate` int(5) DEFAULT '0',
  `BaseCurseToleranceRate` int(5) DEFAULT '0',
  `LastCurseToleranceRate` int(5) DEFAULT '0',
  `BasePhysicalCriticalRate` int(5) DEFAULT '0',
  `LastPhysicalCriticalRate` int(5) DEFAULT '0',
  `BaseEnergyCriticalRate` int(5) DEFAULT '0',
  `LastEnergyCriticalRate` int(5) DEFAULT '0',
  `LastRunSpeed` float(10,5) DEFAULT '8.00000',
  `BaseAttackSpeedRate` int(5) DEFAULT '1000',
  `LastAttackSpeedRate` int(5) DEFAULT '1000',
  `BaseAttackRange` float(10,5) DEFAULT '10.00000',
  `LastAttackRange` float(10,5) DEFAULT '10.00000',
  `CastingTimeChangePercent` float(10,5) DEFAULT '100.00000',
  `CoolTimeChangePercent` float(10,5) DEFAULT '100.00000',
  `KeepTimeChangePercent` float(10,5) DEFAULT '100.00000',
  `DotValueChangePercent` float(10,5) DEFAULT '100.00000',
  `DotTimeChangeAbsolute` float(10,5) DEFAULT '100.00000',
  `RequiredEpChangePercent` float(10,5) DEFAULT '100.00000',
  `HonestOffence` float(10,5) DEFAULT '0.00000',
  `HonestDefence` float(10,5) DEFAULT '0.00000',
  `StrangeOffence` float(10,5) DEFAULT '0.00000',
  `StrangeDefence` float(10,5) DEFAULT '0.00000',
  `WildOffence` float(10,5) DEFAULT '0.00000',
  `WildDefence` float(10,5) DEFAULT '0.00000',
  `EleganceOffence` float(10,5) DEFAULT '0.00000',
  `EleganceDefence` float(10,5) DEFAULT '0.00000',
  `FunnyOffence` float(10,5) DEFAULT '0.00000',
  `FunnyDefence` float(10,5) DEFAULT '0.00000',
  `ParalyzeToleranceRate` int(5) DEFAULT '0',
  `TerrorToleranceRate` int(5) DEFAULT '0',
  `ConfuseToleranceRate` int(5) DEFAULT '0',
  `StoneToleranceRate` int(5) DEFAULT '0',
  `CandyToleranceRate` int(5) DEFAULT '0',
  `ParalyzeKeepTimeDown` float(10,5) DEFAULT '0.00000',
  `TerrorKeepTimeDown` float(10,5) DEFAULT '0.00000',
  `ConfuseKeepTimeDown` float(10,5) DEFAULT '0.00000',
  `StoneKeepTimeDown` float(10,5) DEFAULT '0.00000',
  `CandyKeepTimeDown` float(10,5) DEFAULT '0.00000',
  `BleedingKeepTimeDown` float(10,5) DEFAULT '0.00000',
  `PoisonKeepTimeDown` float(10,5) DEFAULT '0.00000',
  `StomachacheKeepTimeDown` float(10,5) DEFAULT '0.00000',
  `CriticalBlockSuccessRate` float(10,5) DEFAULT '0.00000',
  `GuardRate` int(5) DEFAULT '0',
  `SkillDamageBlockModeSuccessRate` float(10,5) DEFAULT '0.00000',
  `CurseBlockModeSuccessRate` float(10,5) DEFAULT '0.00000',
  `KnockdownBlockModeSuccessRate` float(10,5) DEFAULT '0.00000',
  `HtbBlockModeSuccessRate` float(10,5) DEFAULT '0.00000',
  `SitDownLpRegenBonusRate` float(10,5) DEFAULT '0.00000',
  `SitDownEpRegenBonusRate` float(10,5) DEFAULT '0.00000',
  `PhysicalCriticalDamageBonusRate` float(10,5) DEFAULT '0.00000',
  `EnergyCriticalDamageBonusRate` float(10,5) DEFAULT '0.00000',
  `ItemUpgradeBonusRate` float(10,5) DEFAULT '0.00000',
  `ItemUpgradeBreakBonusRate` float(10,5) DEFAULT '0.00000',
  `CurAP` int(10) DEFAULT '450000' COMMENT 'FlyingAP',
  `CurLP` int(10) DEFAULT '100',
  `CurEP` int(10) DEFAULT '100',
  `CurRP` int(10) DEFAULT '100',
  `LastMaxAp` int(5) DEFAULT '450000',
  `BaseMaxAp` int(5) DEFAULT '450000',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of characters_attributes
-- ----------------------------
INSERT INTO `characters_attributes` VALUES ('19', '6', '56', '56', '80', '80', '96', '96', '72', '72', '120', '120', '104', '104', '6528', '6528', '5824', '5824', '100', '100', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '92', '92', '0', '0', '240', '240', '0', '0', '960', '960', '360', '360', '0', '0', '0', '0', '0', '0', '36', '36', '57', '57', '8.00000', '1500', '1500', '35.00000', '35.00000', '100.00000', '100.00000', '100.00000', '100.00000', '100.00000', '100.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0', '0', '0', '0', '0', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '450000', '7600', '5720', '0', '450000', '450000');
INSERT INTO `characters_attributes` VALUES ('22', '8', '14', '14', '9', '9', '9', '9', '14', '14', '9', '9', '7', '7', '734', '734', '392', '392', '100', '100', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '23', '23', '0', '0', '18', '18', '0', '0', '90', '90', '70', '70', '0', '0', '0', '0', '0', '0', '7', '7', '5', '5', '8.00000', '1500', '1500', '2.00000', '2.00000', '100.00000', '100.00000', '100.00000', '100.00000', '100.00000', '100.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0', '0', '0', '0', '0', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '0.00000', '450000', '855', '385', '0', '450000', '450000');

-- ----------------------------
-- Table structure for `hoipoimix`
-- ----------------------------
DROP TABLE IF EXISTS `hoipoimix`;
CREATE TABLE `hoipoimix` (
  `ID` int(10) NOT NULL AUTO_INCREMENT,
  `CharID` int(11) DEFAULT '0',
  `RecipeID` int(11) DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of hoipoimix
-- ----------------------------

-- ----------------------------
-- Table structure for `items`
-- ----------------------------
DROP TABLE IF EXISTS `items`;
CREATE TABLE `items` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `tblidx` int(11) unsigned NOT NULL DEFAULT '0',
  `owner_id` int(11) unsigned NOT NULL DEFAULT '0',
  `place` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `pos` smallint(5) unsigned NOT NULL DEFAULT '0',
  `count` smallint(3) unsigned NOT NULL DEFAULT '1',
  `rank` tinyint(1) unsigned NOT NULL DEFAULT '1',
  `durability` smallint(3) unsigned NOT NULL DEFAULT '100',
  `grade` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `battleAttribute` int(11) DEFAULT '0',
  `option0` int(11) DEFAULT '0',
  `option1` int(11) DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE,
  KEY `owner_id_idx` (`owner_id`) USING BTREE,
  KEY `item_vnum_index` (`tblidx`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=2385 DEFAULT CHARSET=latin1 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of items
-- ----------------------------
INSERT INTO `items` VALUES ('2212', '19991', '3', '9', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2211', '11170034', '3', '7', '16', '1', '5', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2210', '11170037', '3', '7', '15', '1', '5', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2209', '11170002', '3', '7', '14', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2208', '11170108', '3', '7', '12', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2207', '60000000', '3', '7', '5', '1', '1', '50', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('781', '19991', '2', '9', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('780', '60000000', '2', '7', '5', '1', '1', '50', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('779', '523003', '2', '7', '4', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('778', '523002', '2', '7', '3', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('777', '523001', '2', '7', '2', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('776', '505001', '2', '7', '0', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('775', '11140272', '2', '1', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('774', '19907', '2', '0', '6', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('773', '19901', '2', '0', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('881', '19991', '1', '9', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('880', '60000000', '1', '7', '5', '1', '1', '50', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('879', '522003', '1', '7', '4', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('878', '522002', '1', '7', '3', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('877', '522001', '1', '7', '2', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('876', '500001', '1', '7', '0', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('875', '11120041', '1', '1', '1', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('874', '11140272', '1', '1', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('873', '19907', '1', '0', '6', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('872', '19901', '1', '0', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2206', '522087', '3', '7', '4', '1', '1', '100', '15', '0', '0', '0');
INSERT INTO `items` VALUES ('2205', '522086', '3', '7', '3', '1', '1', '100', '15', '0', '0', '0');
INSERT INTO `items` VALUES ('2204', '522085', '3', '7', '2', '1', '1', '100', '15', '0', '0', '0');
INSERT INTO `items` VALUES ('2203', '832306', '3', '7', '1', '1', '1', '100', '15', '0', '0', '0');
INSERT INTO `items` VALUES ('2202', '500014', '3', '7', '0', '1', '1', '100', '15', '0', '0', '0');
INSERT INTO `items` VALUES ('2201', '522003', '3', '2', '5', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2200', '522002', '3', '2', '4', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2199', '522001', '3', '2', '3', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2198', '500001', '3', '2', '2', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2197', '95', '3', '2', '1', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2196', '26', '3', '2', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2195', '11120175', '3', '1', '15', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2194', '11120174', '3', '1', '14', '4', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('1610', '19991', '4', '9', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('1609', '60000000', '4', '7', '5', '1', '1', '50', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('1608', '523003', '4', '7', '4', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('1607', '523002', '4', '7', '3', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('1606', '523001', '4', '7', '2', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('1605', '505001', '4', '7', '0', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('1604', '11140272', '4', '1', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('1603', '19907', '4', '0', '6', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('1602', '19901', '4', '0', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2193', '11100011', '3', '1', '13', '1', '4', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2192', '11100010', '3', '1', '12', '1', '4', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2191', '11120149', '3', '1', '11', '5', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2173', '19991', '5', '9', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2172', '60000000', '5', '7', '5', '1', '1', '50', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2171', '525003', '5', '7', '4', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2170', '525002', '5', '7', '3', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2169', '525001', '5', '7', '2', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2168', '508010', '5', '7', '1', '1', '1', '100', '15', '0', '0', '0');
INSERT INTO `items` VALUES ('2167', '500001', '5', '7', '0', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2166', '11140272', '5', '1', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2190', '11140284', '3', '1', '10', '1', '2', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2189', '11120176', '3', '1', '9', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2188', '11100003', '3', '1', '8', '30', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2187', '303007', '3', '1', '7', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2186', '11100005', '3', '1', '6', '30', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2185', '11120149', '3', '1', '5', '10', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2184', '11120174', '3', '1', '4', '4', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2183', '11130001', '3', '1', '3', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2182', '11', '3', '1', '2', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2181', '65', '3', '1', '1', '1', '3', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2180', '11140277', '3', '1', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2179', '19907', '3', '0', '6', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2178', '403043', '3', '0', '4', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2177', '403043', '3', '0', '3', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2176', '403043', '3', '0', '2', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2175', '403043', '3', '0', '1', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2174', '19901', '3', '0', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2384', '6005012', '8', '1', '9', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2383', '19991', '8', '9', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2382', '19991', '8', '9', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2032', '19991', '6', '9', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2031', '11170035', '6', '7', '16', '1', '5', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2030', '11170038', '6', '7', '15', '1', '5', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2271', '19991', '7', '9', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2270', '60000000', '7', '7', '5', '1', '1', '50', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2269', '523003', '7', '7', '4', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2268', '523002', '7', '7', '3', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2267', '523001', '7', '7', '2', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2266', '505001', '7', '7', '0', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2265', '23', '7', '1', '1', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2264', '11140272', '7', '1', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2263', '19907', '7', '0', '6', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2029', '11170002', '6', '7', '14', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2028', '11170256', '6', '7', '12', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2027', '11120199', '6', '7', '11', '1', '4', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2026', '11120200', '6', '7', '10', '1', '5', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2025', '60000000', '6', '7', '5', '1', '1', '50', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2024', '554006', '6', '7', '1', '1', '1', '100', '15', '0', '0', '0');
INSERT INTO `items` VALUES ('2023', '505001', '6', '7', '0', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2022', '523021', '6', '7', '4', '1', '1', '100', '15', '0', '0', '0');
INSERT INTO `items` VALUES ('2021', '523020', '6', '7', '3', '1', '1', '100', '15', '0', '0', '0');
INSERT INTO `items` VALUES ('2165', '19907', '5', '0', '6', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2262', '19901', '7', '0', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2164', '19901', '5', '0', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2381', '60000000', '8', '7', '5', '1', '1', '50', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2380', '60000000', '8', '7', '5', '1', '1', '50', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2379', '525003', '8', '7', '4', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2378', '522003', '8', '7', '4', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2377', '525002', '8', '7', '3', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2376', '522002', '8', '7', '3', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2020', '523019', '6', '7', '2', '1', '1', '100', '15', '0', '0', '0');
INSERT INTO `items` VALUES ('2019', '19907', '6', '0', '6', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2018', '303007', '6', '0', '1', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2017', '19901', '6', '0', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2375', '522001', '8', '7', '2', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2374', '525001', '8', '7', '2', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2373', '500001', '8', '7', '0', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2372', '500001', '8', '7', '0', '1', '1', '100', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2371', '6005013', '8', '1', '8', '5', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2370', '22', '8', '1', '7', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2369', '25', '8', '1', '6', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2368', '403000', '8', '1', '5', '10', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2367', '11140107', '8', '1', '4', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2366', '6005012', '8', '1', '2', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2365', '61', '8', '1', '1', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2364', '11140272', '8', '1', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2363', '11140272', '8', '1', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2362', '19907', '8', '0', '6', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2361', '19907', '8', '0', '6', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2360', '19901', '8', '0', '0', '1', '1', '255', '0', '0', '0', '0');
INSERT INTO `items` VALUES ('2359', '19901', '8', '0', '0', '1', '1', '255', '0', '0', '0', '0');

-- ----------------------------
-- Table structure for `mail`
-- ----------------------------
DROP TABLE IF EXISTS `mail`;
CREATE TABLE `mail` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(11) DEFAULT NULL,
  `byDay` tinyint(2) DEFAULT NULL,
  `tCreateTime` int(50) NOT NULL,
  `SenderType` tinyint(1) NOT NULL DEFAULT '0',
  `byMailType` tinyint(1) NOT NULL,
  `byTextSize` int(10) DEFAULT NULL,
  `dwZenny` int(10) DEFAULT '0',
  `wszText` varchar(130) DEFAULT NULL,
  `item_id` int(11) DEFAULT NULL,
  `item_place` int(10) DEFAULT NULL,
  `item_pos` int(10) DEFAULT NULL,
  `wszTargetName` varchar(16) DEFAULT NULL,
  `wszFromName` varchar(16) DEFAULT NULL,
  `bIsAccept` int(1) DEFAULT NULL,
  `bIsLock` int(1) DEFAULT NULL,
  `bIsRead` int(1) DEFAULT NULL,
  `StackCount` int(10) DEFAULT NULL,
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
  `CharID` int(11) DEFAULT '0',
  `MascotID` int(11) DEFAULT '0',
  `Slot` int(5) DEFAULT '0',
  `CurVP` int(11) DEFAULT '0',
  `MaxVP` int(11) DEFAULT '0',
  `Exp` int(11) DEFAULT '0',
  `Skill_count` int(5) DEFAULT '1',
  `Skill1` int(11) DEFAULT '0',
  `Skill2` int(11) DEFAULT '0',
  `Skill3` int(11) DEFAULT '0',
  `Skill4` int(11) DEFAULT '0',
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
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=69 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of portals
-- ----------------------------
INSERT INTO `portals` VALUES ('1', '2', '1');
INSERT INTO `portals` VALUES ('2', '2', '15');
INSERT INTO `portals` VALUES ('3', '2', '8');
INSERT INTO `portals` VALUES ('4', '3', '1');
INSERT INTO `portals` VALUES ('5', '3', '15');
INSERT INTO `portals` VALUES ('6', '3', '8');
INSERT INTO `portals` VALUES ('7', '4', '1');
INSERT INTO `portals` VALUES ('8', '4', '15');
INSERT INTO `portals` VALUES ('9', '4', '8');
INSERT INTO `portals` VALUES ('10', '5', '1');
INSERT INTO `portals` VALUES ('11', '5', '15');
INSERT INTO `portals` VALUES ('12', '5', '8');
INSERT INTO `portals` VALUES ('13', '6', '1');
INSERT INTO `portals` VALUES ('14', '6', '15');
INSERT INTO `portals` VALUES ('15', '6', '8');
INSERT INTO `portals` VALUES ('16', '7', '3');
INSERT INTO `portals` VALUES ('17', '7', '15');
INSERT INTO `portals` VALUES ('18', '7', '8');
INSERT INTO `portals` VALUES ('19', '8', '1');
INSERT INTO `portals` VALUES ('20', '8', '15');
INSERT INTO `portals` VALUES ('21', '8', '8');
INSERT INTO `portals` VALUES ('22', '9', '1');
INSERT INTO `portals` VALUES ('23', '9', '15');
INSERT INTO `portals` VALUES ('24', '9', '8');
INSERT INTO `portals` VALUES ('25', '10', '1');
INSERT INTO `portals` VALUES ('26', '10', '15');
INSERT INTO `portals` VALUES ('27', '10', '8');
INSERT INTO `portals` VALUES ('28', '11', '1');
INSERT INTO `portals` VALUES ('29', '11', '15');
INSERT INTO `portals` VALUES ('30', '11', '8');
INSERT INTO `portals` VALUES ('31', '12', '3');
INSERT INTO `portals` VALUES ('32', '12', '15');
INSERT INTO `portals` VALUES ('33', '12', '8');
INSERT INTO `portals` VALUES ('34', '13', '1');
INSERT INTO `portals` VALUES ('35', '13', '15');
INSERT INTO `portals` VALUES ('36', '13', '8');
INSERT INTO `portals` VALUES ('37', '14', '1');
INSERT INTO `portals` VALUES ('38', '14', '15');
INSERT INTO `portals` VALUES ('39', '14', '8');
INSERT INTO `portals` VALUES ('40', '1', '1');
INSERT INTO `portals` VALUES ('41', '1', '15');
INSERT INTO `portals` VALUES ('42', '1', '8');
INSERT INTO `portals` VALUES ('43', '2', '1');
INSERT INTO `portals` VALUES ('44', '2', '15');
INSERT INTO `portals` VALUES ('45', '2', '8');
INSERT INTO `portals` VALUES ('46', '3', '1');
INSERT INTO `portals` VALUES ('47', '3', '15');
INSERT INTO `portals` VALUES ('48', '3', '8');
INSERT INTO `portals` VALUES ('49', '4', '1');
INSERT INTO `portals` VALUES ('50', '4', '15');
INSERT INTO `portals` VALUES ('51', '4', '8');
INSERT INTO `portals` VALUES ('52', '3', '22');
INSERT INTO `portals` VALUES ('53', '3', '24');
INSERT INTO `portals` VALUES ('54', '5', '3');
INSERT INTO `portals` VALUES ('55', '5', '15');
INSERT INTO `portals` VALUES ('56', '5', '8');
INSERT INTO `portals` VALUES ('57', '6', '1');
INSERT INTO `portals` VALUES ('58', '6', '15');
INSERT INTO `portals` VALUES ('59', '6', '8');
INSERT INTO `portals` VALUES ('60', '7', '1');
INSERT INTO `portals` VALUES ('61', '7', '15');
INSERT INTO `portals` VALUES ('62', '7', '8');
INSERT INTO `portals` VALUES ('63', '8', '3');
INSERT INTO `portals` VALUES ('64', '8', '15');
INSERT INTO `portals` VALUES ('65', '8', '8');
INSERT INTO `portals` VALUES ('66', '8', '1');
INSERT INTO `portals` VALUES ('67', '8', '15');
INSERT INTO `portals` VALUES ('68', '8', '8');

-- ----------------------------
-- Table structure for `questlist`
-- ----------------------------
DROP TABLE IF EXISTS `questlist`;
CREATE TABLE `questlist` (
  `type` int(11) NOT NULL,
  `tId` int(11) NOT NULL,
  `currentID` int(11) NOT NULL,
  `nextID` int(11) NOT NULL,
  `charID` int(11) NOT NULL,
  `isCompleted` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of questlist
-- ----------------------------
INSERT INTO `questlist` VALUES ('0', '1924', '2', '3', '8', '0');

-- ----------------------------
-- Table structure for `quickslot`
-- ----------------------------
DROP TABLE IF EXISTS `quickslot`;
CREATE TABLE `quickslot` (
  `pkQuick` int(15) NOT NULL AUTO_INCREMENT,
  `charId` int(11) DEFAULT NULL,
  `slotId_0` int(10) unsigned DEFAULT '0',
  `slotId_1` int(10) unsigned DEFAULT '0',
  `slotId_2` int(10) unsigned DEFAULT '0',
  `slotId_3` int(10) unsigned DEFAULT '0',
  `slotId_4` int(10) unsigned DEFAULT '0',
  `slotId_5` int(10) unsigned DEFAULT '0',
  `slotId_6` int(10) unsigned DEFAULT '0',
  `slotId_7` int(10) unsigned DEFAULT '0',
  `slotId_8` int(10) unsigned DEFAULT '0',
  `slotId_9` int(10) unsigned DEFAULT '0',
  `slotId_10` int(10) unsigned DEFAULT '0',
  `slotId_11` int(10) unsigned DEFAULT '0',
  `slotId_12` int(10) unsigned DEFAULT '0',
  `slotId_13` int(10) unsigned DEFAULT '0',
  `slotId_14` int(10) unsigned DEFAULT '0',
  `slotId_15` int(10) unsigned DEFAULT '0',
  `slotId_16` int(10) unsigned DEFAULT '0',
  `slotId_17` int(10) unsigned DEFAULT '0',
  `slotId_18` int(10) unsigned DEFAULT '0',
  `slotId_19` int(10) unsigned DEFAULT '0',
  `slotId_20` int(10) unsigned DEFAULT '0',
  `slotId_21` int(10) unsigned DEFAULT '0',
  `slotId_22` int(10) unsigned DEFAULT '0',
  `slotId_23` int(10) unsigned DEFAULT '0',
  `slotId_24` int(10) unsigned DEFAULT '0',
  `slotId_25` int(10) unsigned DEFAULT '0',
  `slotId_26` int(10) unsigned DEFAULT '0',
  `slotId_27` int(10) unsigned DEFAULT '0',
  `slotId_28` int(10) unsigned DEFAULT '0',
  `slotId_29` int(10) unsigned DEFAULT '0',
  `slotId_30` int(10) unsigned DEFAULT '0',
  `slotId_31` int(10) unsigned DEFAULT '0',
  `slotId_32` int(10) unsigned DEFAULT '0',
  `slotId_33` int(10) unsigned DEFAULT '0',
  `slotId_34` int(10) unsigned DEFAULT '0',
  `slotId_35` int(10) unsigned DEFAULT '0',
  `slotId_36` int(10) unsigned DEFAULT '0',
  `slotId_37` int(10) unsigned DEFAULT '0',
  `slotId_38` int(10) unsigned DEFAULT '0',
  `slotId_39` int(10) unsigned DEFAULT '0',
  `slotId_40` int(10) unsigned DEFAULT '0',
  `slotId_41` int(10) unsigned DEFAULT '0',
  `slotId_42` int(10) unsigned DEFAULT '0',
  `slotId_43` int(10) unsigned DEFAULT '0',
  `slotId_44` int(10) unsigned DEFAULT '0',
  `slotId_45` int(10) unsigned DEFAULT '0',
  `slotId_46` int(10) unsigned DEFAULT '0',
  `slotId_47` int(10) DEFAULT NULL,
  `placeID` int(10) DEFAULT NULL,
  PRIMARY KEY (`pkQuick`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of quickslot
-- ----------------------------
INSERT INTO `quickslot` VALUES ('1', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('2', '3', '10311', '10014', '10111', '10416', '10714', '710631', '710011', '710854', '710875', '0', '0', '0', '20117', '20515', '20614', '20815', '720032', '720631', '0', '0', '0', '20083', '21011', '20091', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('3', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('4', '5', '310111', '310011', '310311', '310511', '310411', '310211', '310221', '310711', '0', '0', '0', '0', '320112', '320031', '320041', '320051', '320061', '320611', '0', '0', '0', '0', '0', '320101', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('5', '6', '110218', '1010603', '1010014', '1010624', '1010565', '1010585', '1010505', '110314', '120513', '120103', '121111', '0', '120041', '1020031', '1020041', '1020051', '1021141', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('6', '7', '110111', '110211', '110311', '110511', '0', '0', '0', '0', '0', '0', '0', '0', '120041', '120031', '110011', '110021', '110031', '110041', '120061', '120081', '120091', '120051', '120071', '120511', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('7', '8', '0', '10311', '20111', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('8', '9', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('9', '10', '10311', '10014', '10416', '10714', '0', '0', '0', '0', '0', '0', '0', '0', '20117', '20011', '20515', '20614', '20815', '0', '0', '0', '0', '21011', '20083', '20091', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('10', '11', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('11', '12', '310111', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '320111', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('12', '13', '10311', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '20111', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '20091', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('13', '14', '10311', '10014', '10111', '10416', '10714', '710854', '710875', '720731', '720751', '0', '0', '0', '20117', '20011', '20515', '20614', '20815', '720035', '720044', '720633', '0', '0', '20083', '20091', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('14', '1', '10311', '10014', '10111', '10416', '10714', '0', '0', '0', '0', '0', '0', '0', '20111', '20011', '20515', '20614', '20815', '0', '0', '0', '0', '20083', '21011', '20091', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('15', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('16', '3', '0', '10014', '10111', '10416', '10714', '710631', '710011', '710854', '710875', '0', '0', '0', '20117', '20515', '20614', '20815', '720032', '720631', '0', '0', '0', '20083', '21011', '20091', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('17', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('18', '5', '310111', '310011', '310311', '310511', '310411', '310211', '310221', '310711', '0', '0', '0', '0', '320112', '320031', '320041', '320051', '320061', '320611', '0', '0', '0', '0', '0', '320101', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('19', '6', '110218', '1010603', '1010014', '1010624', '1010565', '1010585', '1010505', '110314', '120513', '120103', '121111', '0', '120041', '1020031', '1020041', '1020051', '1021141', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('20', '7', '110111', '110211', '110311', '110511', '0', '0', '0', '0', '0', '0', '0', '0', '120041', '120031', '110011', '110021', '110031', '110041', '120061', '120081', '120091', '120051', '120071', '120511', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('21', '8', '0', '10311', '20111', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);
INSERT INTO `quickslot` VALUES ('22', '8', '0', '10311', '20111', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', null, null);

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
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of quickteleporter
-- ----------------------------
INSERT INTO `quickteleporter` VALUES ('2', '8', '1', '1', '4878', '-66', '4079', '2019', '9', '21', '23', '16', '50', '1');
INSERT INTO `quickteleporter` VALUES ('3', '8', '2', '1', '4878', '-66', '4079', '2019', '9', '21', '23', '17', '30', '1');

-- ----------------------------
-- Table structure for `realmlist`
-- ----------------------------
DROP TABLE IF EXISTS `realmlist`;
CREATE TABLE `realmlist` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `ServerID` int(11) unsigned NOT NULL DEFAULT '0',
  `ChannelID` int(11) unsigned NOT NULL DEFAULT '0',
  `realmflags` tinyint(3) unsigned NOT NULL DEFAULT '2',
  `population` float unsigned NOT NULL,
  `IsEvent` int(11) DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Realm System';

-- ----------------------------
-- Records of realmlist
-- ----------------------------
INSERT INTO `realmlist` VALUES ('2', '0', '0', '2', '0', '0');

-- ----------------------------
-- Table structure for `skills`
-- ----------------------------
DROP TABLE IF EXISTS `skills`;
CREATE TABLE `skills` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `skill_id` int(10) unsigned NOT NULL DEFAULT '0',
  `owner_id` int(11) unsigned NOT NULL,
  `RpBonusAuto` bit(1) DEFAULT b'0',
  `RpBonusType` int(5) unsigned NOT NULL DEFAULT '0',
  `SlotID` smallint(3) unsigned NOT NULL DEFAULT '0',
  `TimeRemaining` int(15) unsigned NOT NULL,
  `Exp` int(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=260 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of skills
-- ----------------------------
INSERT INTO `skills` VALUES ('94', '10311', '1', '', '0', '1', '0', '0');
INSERT INTO `skills` VALUES ('95', '20091', '1', '', '0', '2', '0', '0');
INSERT INTO `skills` VALUES ('96', '20111', '1', '', '0', '3', '0', '0');
INSERT INTO `skills` VALUES ('97', '21011', '1', '', '0', '0', '0', '0');
INSERT INTO `skills` VALUES ('98', '110111', '2', '', '0', '1', '0', '0');
INSERT INTO `skills` VALUES ('99', '120131', '2', '', '0', '2', '0', '0');
INSERT INTO `skills` VALUES ('100', '110011', '2', '', '0', '3', '0', '0');
INSERT INTO `skills` VALUES ('101', '20021', '1', '', '0', '5', '0', '0');
INSERT INTO `skills` VALUES ('102', '20011', '1', '', '0', '6', '0', '0');
INSERT INTO `skills` VALUES ('103', '20031', '1', '', '0', '7', '0', '0');
INSERT INTO `skills` VALUES ('104', '20515', '1', '', '0', '8', '0', '0');
INSERT INTO `skills` VALUES ('105', '20071', '1', '', '0', '9', '0', '0');
INSERT INTO `skills` VALUES ('106', '20614', '1', '', '0', '10', '0', '0');
INSERT INTO `skills` VALUES ('107', '20815', '1', '', '0', '11', '0', '0');
INSERT INTO `skills` VALUES ('108', '20083', '1', '', '0', '12', '0', '0');
INSERT INTO `skills` VALUES ('109', '20043', '1', '', '0', '13', '0', '0');
INSERT INTO `skills` VALUES ('110', '10014', '1', '', '0', '14', '0', '0');
INSERT INTO `skills` VALUES ('111', '10111', '1', '', '0', '15', '0', '0');
INSERT INTO `skills` VALUES ('112', '10416', '1', '', '0', '16', '0', '0');
INSERT INTO `skills` VALUES ('113', '10714', '1', '', '0', '17', '0', '0');
INSERT INTO `skills` VALUES ('114', '10311', '3', '', '0', '1', '0', '0');
INSERT INTO `skills` VALUES ('115', '20091', '3', '', '0', '2', '0', '0');
INSERT INTO `skills` VALUES ('116', '20117', '3', '', '0', '3', '0', '0');
INSERT INTO `skills` VALUES ('117', '110111', '4', '', '0', '1', '0', '0');
INSERT INTO `skills` VALUES ('118', '120131', '4', '', '0', '2', '0', '0');
INSERT INTO `skills` VALUES ('119', '110011', '4', '', '0', '3', '0', '0');
INSERT INTO `skills` VALUES ('120', '21011', '3', '', '0', '0', '0', '0');
INSERT INTO `skills` VALUES ('121', '20083', '3', '', '0', '8', '0', '0');
INSERT INTO `skills` VALUES ('122', '10014', '3', '', '0', '9', '0', '0');
INSERT INTO `skills` VALUES ('123', '10111', '3', '', '0', '10', '0', '0');
INSERT INTO `skills` VALUES ('124', '10416', '3', '', '0', '11', '0', '0');
INSERT INTO `skills` VALUES ('125', '10714', '3', '', '0', '12', '0', '0');
INSERT INTO `skills` VALUES ('126', '20043', '3', '', '0', '13', '0', '0');
INSERT INTO `skills` VALUES ('127', '20021', '3', '', '0', '14', '0', '0');
INSERT INTO `skills` VALUES ('128', '20011', '3', '', '0', '15', '0', '0');
INSERT INTO `skills` VALUES ('129', '20031', '3', '', '0', '16', '0', '0');
INSERT INTO `skills` VALUES ('130', '20515', '3', '', '0', '17', '0', '0');
INSERT INTO `skills` VALUES ('131', '20071', '3', '', '0', '18', '0', '0');
INSERT INTO `skills` VALUES ('132', '20614', '3', '', '0', '19', '0', '0');
INSERT INTO `skills` VALUES ('133', '20815', '3', '', '0', '20', '0', '0');
INSERT INTO `skills` VALUES ('136', '729991', '3', '', '0', '21', '0', '0');
INSERT INTO `skills` VALUES ('137', '720054', '3', '', '0', '22', '0', '0');
INSERT INTO `skills` VALUES ('138', '720164', '3', '', '0', '23', '0', '0');
INSERT INTO `skills` VALUES ('139', '720032', '3', '', '0', '24', '0', '0');
INSERT INTO `skills` VALUES ('140', '710631', '3', '', '0', '25', '0', '0');
INSERT INTO `skills` VALUES ('141', '710011', '3', '', '0', '26', '0', '0');
INSERT INTO `skills` VALUES ('142', '710854', '3', '', '0', '27', '0', '0');
INSERT INTO `skills` VALUES ('143', '710875', '3', '', '0', '28', '0', '0');
INSERT INTO `skills` VALUES ('144', '720071', '3', '', '0', '29', '0', '0');
INSERT INTO `skills` VALUES ('145', '720011', '3', '', '0', '30', '0', '0');
INSERT INTO `skills` VALUES ('146', '720631', '3', '', '0', '31', '0', '0');
INSERT INTO `skills` VALUES ('147', '20911', '3', '', '0', '32', '0', '0');
INSERT INTO `skills` VALUES ('148', '20221', '3', '', '0', '33', '0', '0');
INSERT INTO `skills` VALUES ('149', '20201', '3', '', '0', '34', '0', '0');
INSERT INTO `skills` VALUES ('150', '10021', '3', '', '0', '35', '0', '0');
INSERT INTO `skills` VALUES ('151', '20211', '3', '', '0', '36', '0', '0');
INSERT INTO `skills` VALUES ('152', '310111', '5', '', '0', '1', '0', '0');
INSERT INTO `skills` VALUES ('153', '320101', '5', '', '0', '2', '0', '0');
INSERT INTO `skills` VALUES ('154', '320112', '5', '', '0', '3', '0', '0');
INSERT INTO `skills` VALUES ('155', '110111', '6', '', '0', '1', '0', '0');
INSERT INTO `skills` VALUES ('156', '120131', '6', '', '0', '2', '0', '0');
INSERT INTO `skills` VALUES ('157', '110011', '6', '', '0', '3', '0', '0');
INSERT INTO `skills` VALUES ('158', '110111', '7', '', '0', '1', '0', '0');
INSERT INTO `skills` VALUES ('159', '120131', '7', '', '0', '2', '0', '0');
INSERT INTO `skills` VALUES ('160', '110011', '7', '', '0', '3', '0', '0');
INSERT INTO `skills` VALUES ('161', '121111', '6', '', '0', '4', '0', '0');
INSERT INTO `skills` VALUES ('163', '120103', '6', '', '0', '8', '0', '0');
INSERT INTO `skills` VALUES ('164', '110218', '6', '', '0', '9', '0', '0');
INSERT INTO `skills` VALUES ('165', '110314', '6', '', '0', '10', '0', '0');
INSERT INTO `skills` VALUES ('166', '110511', '6', '', '0', '11', '0', '0');
INSERT INTO `skills` VALUES ('167', '110021', '6', '', '0', '12', '0', '0');
INSERT INTO `skills` VALUES ('168', '110031', '6', '', '0', '13', '0', '0');
INSERT INTO `skills` VALUES ('169', '110041', '6', '', '0', '14', '0', '0');
INSERT INTO `skills` VALUES ('170', '120021', '6', '', '0', '15', '0', '0');
INSERT INTO `skills` VALUES ('171', '120011', '6', '', '0', '16', '0', '0');
INSERT INTO `skills` VALUES ('172', '120061', '6', '', '0', '17', '0', '0');
INSERT INTO `skills` VALUES ('173', '120041', '6', '', '0', '18', '0', '0');
INSERT INTO `skills` VALUES ('174', '120081', '6', '', '0', '19', '0', '0');
INSERT INTO `skills` VALUES ('175', '120091', '6', '', '0', '20', '0', '0');
INSERT INTO `skills` VALUES ('176', '120031', '6', '', '0', '21', '0', '0');
INSERT INTO `skills` VALUES ('177', '120071', '6', '', '0', '22', '0', '0');
INSERT INTO `skills` VALUES ('178', '120513', '6', '', '0', '23', '0', '0');
INSERT INTO `skills` VALUES ('179', '120051', '6', '', '0', '24', '0', '0');
INSERT INTO `skills` VALUES ('180', '1029991', '6', '', '0', '25', '0', '0');
INSERT INTO `skills` VALUES ('181', '120501', '6', '', '0', '26', '0', '0');
INSERT INTO `skills` VALUES ('182', '120911', '6', '', '0', '27', '0', '0');
INSERT INTO `skills` VALUES ('183', '1010441', '6', '', '0', '28', '0', '0');
INSERT INTO `skills` VALUES ('184', '1010565', '6', '', '0', '29', '0', '0');
INSERT INTO `skills` VALUES ('185', '1020031', '6', '', '0', '30', '0', '0');
INSERT INTO `skills` VALUES ('186', '1010505', '6', '', '0', '31', '0', '0');
INSERT INTO `skills` VALUES ('187', '1010603', '6', '', '0', '32', '0', '0');
INSERT INTO `skills` VALUES ('188', '1010014', '6', '', '0', '33', '0', '0');
INSERT INTO `skills` VALUES ('189', '1010624', '6', '', '0', '34', '0', '0');
INSERT INTO `skills` VALUES ('190', '1010461', '6', '', '0', '35', '0', '0');
INSERT INTO `skills` VALUES ('191', '1020041', '6', '', '0', '36', '0', '0');
INSERT INTO `skills` VALUES ('192', '1020051', '6', '', '0', '37', '0', '0');
INSERT INTO `skills` VALUES ('193', '1020841', '6', '', '0', '38', '0', '0');
INSERT INTO `skills` VALUES ('194', '1020071', '6', '', '0', '39', '0', '0');
INSERT INTO `skills` VALUES ('195', '1021141', '6', '', '0', '40', '0', '0');
INSERT INTO `skills` VALUES ('196', '1020061', '6', '', '0', '41', '0', '0');
INSERT INTO `skills` VALUES ('197', '1020121', '6', '', '0', '42', '0', '0');
INSERT INTO `skills` VALUES ('198', '1020021', '6', '', '0', '43', '0', '0');
INSERT INTO `skills` VALUES ('199', '1020011', '6', '', '0', '44', '0', '0');
INSERT INTO `skills` VALUES ('200', '1010585', '6', '', '0', '45', '0', '0');
INSERT INTO `skills` VALUES ('204', '1329996', '5', '', '0', '4', '0', '0');
INSERT INTO `skills` VALUES ('205', '310011', '5', '', '0', '5', '0', '0');
INSERT INTO `skills` VALUES ('206', '310311', '5', '', '0', '6', '0', '0');
INSERT INTO `skills` VALUES ('207', '310511', '5', '', '0', '7', '0', '0');
INSERT INTO `skills` VALUES ('208', '310411', '5', '', '0', '8', '0', '0');
INSERT INTO `skills` VALUES ('209', '310211', '5', '', '0', '9', '0', '0');
INSERT INTO `skills` VALUES ('210', '310221', '5', '', '0', '10', '0', '0');
INSERT INTO `skills` VALUES ('211', '310711', '5', '', '0', '11', '0', '0');
INSERT INTO `skills` VALUES ('212', '320031', '5', '', '0', '12', '0', '0');
INSERT INTO `skills` VALUES ('213', '320081', '5', '', '0', '13', '0', '0');
INSERT INTO `skills` VALUES ('214', '320041', '5', '', '0', '14', '0', '0');
INSERT INTO `skills` VALUES ('215', '320051', '5', '', '0', '15', '0', '0');
INSERT INTO `skills` VALUES ('216', '320511', '5', '', '0', '16', '0', '0');
INSERT INTO `skills` VALUES ('217', '320411', '5', '', '0', '17', '0', '0');
INSERT INTO `skills` VALUES ('218', '320071', '5', '', '0', '18', '0', '0');
INSERT INTO `skills` VALUES ('219', '320061', '5', '', '0', '19', '0', '0');
INSERT INTO `skills` VALUES ('220', '320611', '5', '', '0', '20', '0', '0');
INSERT INTO `skills` VALUES ('221', '320013', '5', '', '0', '21', '0', '0');
INSERT INTO `skills` VALUES ('222', '320023', '5', '', '0', '22', '0', '0');
INSERT INTO `skills` VALUES ('223', '320093', '5', '', '0', '23', '0', '0');
INSERT INTO `skills` VALUES ('224', '1320013', '5', '', '0', '24', '0', '0');
INSERT INTO `skills` VALUES ('225', '1320023', '5', '', '0', '25', '0', '0');
INSERT INTO `skills` VALUES ('226', '1320123', '5', '', '0', '26', '0', '0');
INSERT INTO `skills` VALUES ('227', '1310631', '5', '', '0', '27', '0', '0');
INSERT INTO `skills` VALUES ('228', '1310771', '5', '', '0', '28', '0', '0');
INSERT INTO `skills` VALUES ('229', '1310021', '5', '', '0', '29', '0', '0');
INSERT INTO `skills` VALUES ('230', '1310931', '5', '', '0', '30', '0', '0');
INSERT INTO `skills` VALUES ('231', '1310651', '5', '', '0', '31', '0', '0');
INSERT INTO `skills` VALUES ('232', '1310011', '5', '', '0', '32', '0', '0');
INSERT INTO `skills` VALUES ('233', '1310791', '5', '', '0', '33', '0', '0');
INSERT INTO `skills` VALUES ('234', '1310951', '5', '', '0', '34', '0', '0');
INSERT INTO `skills` VALUES ('235', '1320631', '5', '', '0', '35', '0', '0');
INSERT INTO `skills` VALUES ('236', '1320031', '5', '', '0', '36', '0', '0');
INSERT INTO `skills` VALUES ('237', '1320731', '5', '', '0', '37', '0', '0');
INSERT INTO `skills` VALUES ('238', '1320041', '5', '', '0', '38', '0', '0');
INSERT INTO `skills` VALUES ('239', '1320851', '5', '', '0', '39', '0', '0');
INSERT INTO `skills` VALUES ('240', '1320951', '5', '', '0', '40', '0', '0');
INSERT INTO `skills` VALUES ('241', '1320751', '5', '', '0', '41', '0', '0');
INSERT INTO `skills` VALUES ('242', '110211', '7', '', '0', '4', '0', '0');
INSERT INTO `skills` VALUES ('243', '110021', '7', '', '0', '5', '0', '0');
INSERT INTO `skills` VALUES ('244', '110311', '7', '', '0', '6', '0', '0');
INSERT INTO `skills` VALUES ('245', '110031', '7', '', '0', '7', '0', '0');
INSERT INTO `skills` VALUES ('246', '110511', '7', '', '0', '8', '0', '0');
INSERT INTO `skills` VALUES ('247', '110041', '7', '', '0', '9', '0', '0');
INSERT INTO `skills` VALUES ('248', '120061', '7', '', '0', '10', '0', '0');
INSERT INTO `skills` VALUES ('249', '120081', '7', '', '0', '11', '0', '0');
INSERT INTO `skills` VALUES ('250', '120041', '7', '', '0', '12', '0', '0');
INSERT INTO `skills` VALUES ('251', '120031', '7', '', '0', '13', '0', '0');
INSERT INTO `skills` VALUES ('252', '120091', '7', '', '0', '14', '0', '0');
INSERT INTO `skills` VALUES ('253', '120071', '7', '', '0', '15', '0', '0');
INSERT INTO `skills` VALUES ('254', '120051', '7', '', '0', '16', '0', '0');
INSERT INTO `skills` VALUES ('255', '120511', '7', '', '0', '17', '0', '0');
INSERT INTO `skills` VALUES ('256', '120023', '7', '', '0', '18', '0', '0');
INSERT INTO `skills` VALUES ('257', '10311', '8', '', '0', '1', '0', '0');
INSERT INTO `skills` VALUES ('258', '20091', '8', '', '0', '2', '0', '0');
INSERT INTO `skills` VALUES ('259', '20111', '8', '', '0', '3', '0', '0');

-- ----------------------------
-- Table structure for `titlelist`
-- ----------------------------
DROP TABLE IF EXISTS `titlelist`;
CREATE TABLE `titlelist` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `CharacterID` int(10) DEFAULT NULL,
  `TitleID` smallint(3) DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

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
  PRIMARY KEY (`idFog`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of warfoginfo
-- ----------------------------
INSERT INTO `warfoginfo` VALUES ('1', '100007', '3');
INSERT INTO `warfoginfo` VALUES ('2', '100004', '3');
