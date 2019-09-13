-- phpMyAdmin SQL Dump
-- version 4.7.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Sep 13, 2019 at 02:43 PM
-- Server version: 10.1.25-MariaDB
-- PHP Version: 7.1.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dbodev2`
--

-- --------------------------------------------------------

--
-- Table structure for table `account`
--

CREATE TABLE `account` (
  `AccountID` bigint(20) UNSIGNED NOT NULL,
  `UserName` varchar(16) NOT NULL,
  `UserPassword` varchar(32) NOT NULL,
  `IsBanned` tinyint(1) NOT NULL DEFAULT '0',
  `IsGM` tinyint(1) NOT NULL DEFAULT '0',
  `LastServerID` int(11) NOT NULL DEFAULT '255',
  `LastChannelID` int(11) NOT NULL DEFAULT '255',
  `AccountStatus` tinyint(1) NOT NULL DEFAULT '0',
  `email` varchar(50) DEFAULT NULL,
  `ip` varchar(50) NOT NULL DEFAULT '127.0.0.1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `account`
--

INSERT INTO `account` (`AccountID`, `UserName`, `UserPassword`, `IsBanned`, `IsGM`, `LastServerID`, `LastChannelID`, `AccountStatus`, `email`, `ip`) VALUES
(1, 'Test', '123', 0, 0, 255, 255, 0, NULL, ''),
(2, 'Test2', '123', 0, 0, 0, 255, 0, NULL, '127.0.0.1');

-- --------------------------------------------------------

--
-- Table structure for table `bind`
--

CREATE TABLE `bind` (
  `id` int(10) NOT NULL,
  `CharacterID` int(10) NOT NULL,
  `WorldID` tinyint(3) NOT NULL,
  `BindObjectTblIdx` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `bind`
--

INSERT INTO `bind` (`id`, `CharacterID`, `WorldID`, `BindObjectTblIdx`) VALUES
(1, 2, 1, 6);

-- --------------------------------------------------------

--
-- Table structure for table `characters`
--

CREATE TABLE `characters` (
  `CharacterID` bigint(20) UNSIGNED NOT NULL,
  `AccountID` bigint(20) UNSIGNED NOT NULL,
  `GuildID` bigint(20) UNSIGNED NOT NULL DEFAULT '0',
  `Name` varchar(20) NOT NULL,
  `ServerID` int(10) UNSIGNED NOT NULL,
  `RaceID` int(10) UNSIGNED NOT NULL,
  `ClassID` int(10) UNSIGNED NOT NULL,
  `GenderID` int(10) UNSIGNED NOT NULL,
  `FaceID` int(10) UNSIGNED NOT NULL,
  `HairID` int(10) UNSIGNED NOT NULL,
  `HairColorID` int(10) UNSIGNED NOT NULL,
  `SkinColorID` int(10) UNSIGNED NOT NULL,
  `CurrentLevel` int(10) UNSIGNED NOT NULL DEFAULT '1',
  `CurrentExp` bigint(20) UNSIGNED NOT NULL DEFAULT '0',
  `MapInfoID` bigint(20) UNSIGNED NOT NULL DEFAULT '4294967295',
  `WorldTableID` bigint(20) UNSIGNED NOT NULL DEFAULT '1',
  `WorldID` bigint(20) UNSIGNED NOT NULL DEFAULT '1',
  `BindType` int(10) UNSIGNED NOT NULL DEFAULT '0',
  `BindWorldID` bigint(20) UNSIGNED NOT NULL DEFAULT '0',
  `BindObjectID` bigint(20) UNSIGNED NOT NULL DEFAULT '0',
  `Position_X` float(11,6) NOT NULL DEFAULT '0.000000',
  `Position_Y` float(11,6) NOT NULL DEFAULT '0.000000',
  `Position_Z` float(11,6) NOT NULL DEFAULT '0.000000',
  `Direction_X` float(11,6) NOT NULL DEFAULT '0.000000',
  `Direction_Y` float(11,6) NOT NULL DEFAULT '0.000000',
  `Direction_Z` float(11,6) NOT NULL DEFAULT '0.000000',
  `ZennyInventory` bigint(20) NOT NULL DEFAULT '0',
  `ZennyBank` bigint(20) NOT NULL DEFAULT '0',
  `Token` int(10) UNSIGNED NOT NULL DEFAULT '0',
  `WP_Point` int(10) NOT NULL DEFAULT '0',
  `CashPoint` int(10) UNSIGNED NOT NULL DEFAULT '0',
  `IsVip` int(10) UNSIGNED NOT NULL DEFAULT '0',
  `Title_Marking` int(10) UNSIGNED NOT NULL DEFAULT '0',
  `MixExp` int(10) NOT NULL DEFAULT '0',
  `MixLevel` int(10) NOT NULL DEFAULT '1',
  `IsAdult` tinyint(1) NOT NULL DEFAULT '0',
  `IsTutorialDone` tinyint(1) NOT NULL DEFAULT '0',
  `IsToRename` tinyint(1) NOT NULL DEFAULT '0',
  `IsToDelete` tinyint(1) NOT NULL DEFAULT '0',
  `IsToChangeClass` tinyint(1) NOT NULL DEFAULT '0',
  `IsOnline` tinyint(1) NOT NULL DEFAULT '0',
  `IsGameMaster` tinyint(1) NOT NULL DEFAULT '0',
  `HintsDone` bigint(20) UNSIGNED NOT NULL DEFAULT '0',
  `Reputation` bigint(20) UNSIGNED NOT NULL DEFAULT '0',
  `Mudosa` bigint(20) UNSIGNED NOT NULL DEFAULT '0',
  `SkillPoints` int(10) UNSIGNED NOT NULL DEFAULT '0',
  `createdAt` varchar(20) DEFAULT NULL,
  `deletionStartedAt` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `characters`
--

INSERT INTO `characters` (`CharacterID`, `AccountID`, `GuildID`, `Name`, `ServerID`, `RaceID`, `ClassID`, `GenderID`, `FaceID`, `HairID`, `HairColorID`, `SkinColorID`, `CurrentLevel`, `CurrentExp`, `MapInfoID`, `WorldTableID`, `WorldID`, `BindType`, `BindWorldID`, `BindObjectID`, `Position_X`, `Position_Y`, `Position_Z`, `Direction_X`, `Direction_Y`, `Direction_Z`, `ZennyInventory`, `ZennyBank`, `Token`, `WP_Point`, `CashPoint`, `IsVip`, `Title_Marking`, `MixExp`, `MixLevel`, `IsAdult`, `IsTutorialDone`, `IsToRename`, `IsToDelete`, `IsToChangeClass`, `IsOnline`, `IsGameMaster`, `HintsDone`, `Reputation`, `Mudosa`, `SkillPoints`, `createdAt`, `deletionStartedAt`) VALUES
(2, 2, 0, 'Test', 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 4294967295, 10000, 1, 0, 0, 0, -125.820000, 48.880001, -155.899994, -0.493700, 0.000000, 0.869500, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `characters_attributes`
--

CREATE TABLE `characters_attributes` (
  `ID` int(10) NOT NULL,
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
  `BaseMaxAp` int(5) DEFAULT '450000'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `characters_attributes`
--

INSERT INTO `characters_attributes` (`ID`, `CharacterID`, `BaseStr`, `LastStr`, `BaseCon`, `LastCon`, `BaseFoc`, `LastFoc`, `BaseDex`, `LastDex`, `BaseSol`, `LastSol`, `BaseEng`, `LastEng`, `BaseMaxLP`, `LastMaxLP`, `BaseMaxEP`, `LastMaxEP`, `BaseMaxRP`, `LastMaxRP`, `BaseLpRegen`, `LastLpRegen`, `BaseLpSitdownRegen`, `LastLpSitdownRegen`, `BaseLpBattleRegen`, `LastLpBattleRegen`, `BaseEpRegen`, `LastEpRegen`, `BaseEpSitdownRegen`, `LastEpSitdownRegen`, `BaseEpBattleRegen`, `LastEpBattleRegen`, `BaseRpRegen`, `LastRpRegen`, `LastRpDimimutionRate`, `BasePhysicalOffence`, `LastPhysicalOffence`, `BasePhysicalDefence`, `LastPhysicalDefence`, `BaseEnergyOffence`, `LastEnergyOffence`, `BaseEnergyDefence`, `LastEnergyDefence`, `BaseAttackRate`, `LastAttackRate`, `BaseDodgeRate`, `LastDodgeRate`, `BaseBlockRate`, `LastBlockRate`, `BaseCurseSuccessRate`, `LastCurseSuccessRate`, `BaseCurseToleranceRate`, `LastCurseToleranceRate`, `BasePhysicalCriticalRate`, `LastPhysicalCriticalRate`, `BaseEnergyCriticalRate`, `LastEnergyCriticalRate`, `LastRunSpeed`, `BaseAttackSpeedRate`, `LastAttackSpeedRate`, `BaseAttackRange`, `LastAttackRange`, `CastingTimeChangePercent`, `CoolTimeChangePercent`, `KeepTimeChangePercent`, `DotValueChangePercent`, `DotTimeChangeAbsolute`, `RequiredEpChangePercent`, `HonestOffence`, `HonestDefence`, `StrangeOffence`, `StrangeDefence`, `WildOffence`, `WildDefence`, `EleganceOffence`, `EleganceDefence`, `FunnyOffence`, `FunnyDefence`, `ParalyzeToleranceRate`, `TerrorToleranceRate`, `ConfuseToleranceRate`, `StoneToleranceRate`, `CandyToleranceRate`, `ParalyzeKeepTimeDown`, `TerrorKeepTimeDown`, `ConfuseKeepTimeDown`, `StoneKeepTimeDown`, `CandyKeepTimeDown`, `BleedingKeepTimeDown`, `PoisonKeepTimeDown`, `StomachacheKeepTimeDown`, `CriticalBlockSuccessRate`, `GuardRate`, `SkillDamageBlockModeSuccessRate`, `CurseBlockModeSuccessRate`, `KnockdownBlockModeSuccessRate`, `HtbBlockModeSuccessRate`, `SitDownLpRegenBonusRate`, `SitDownEpRegenBonusRate`, `PhysicalCriticalDamageBonusRate`, `EnergyCriticalDamageBonusRate`, `ItemUpgradeBonusRate`, `ItemUpgradeBreakBonusRate`, `CurAP`, `CurLP`, `CurEP`, `CurRP`, `LastMaxAp`, `BaseMaxAp`) VALUES
(1, 2, 14, 14, 9, 9, 9, 9, 14, 14, 9, 9, 7, 7, 855, 855, 385, 385, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 23, 0, 0, 14, 14, 0, 0, 90, 90, 70, 70, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 8.00000, 1500, 1500, 2.00000, 2.00000, 100.00000, 100.00000, 100.00000, 100.00000, 100.00000, 100.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0, 0, 0, 0, 0, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 450000, 855, 385, 0, 450000, 450000);

-- --------------------------------------------------------

--
-- Table structure for table `items`
--

CREATE TABLE `items` (
  `id` int(11) UNSIGNED NOT NULL,
  `tblidx` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `owner_id` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `place` tinyint(1) UNSIGNED NOT NULL DEFAULT '1',
  `pos` smallint(5) UNSIGNED NOT NULL DEFAULT '0',
  `count` smallint(3) UNSIGNED NOT NULL DEFAULT '1',
  `rank` tinyint(1) UNSIGNED NOT NULL DEFAULT '1',
  `durability` smallint(3) UNSIGNED NOT NULL DEFAULT '100',
  `grade` tinyint(1) UNSIGNED NOT NULL DEFAULT '0',
  `battleAttribute` int(11) DEFAULT '0',
  `option0` int(11) DEFAULT '0',
  `option1` int(11) DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=FIXED;

--
-- Dumping data for table `items`
--

INSERT INTO `items` (`id`, `tblidx`, `owner_id`, `place`, `pos`, `count`, `rank`, `durability`, `grade`, `battleAttribute`, `option0`, `option1`) VALUES
(18, 19991, 2, 9, 0, 1, 1, 255, 0, 0, 0, 0),
(17, 60000000, 2, 7, 5, 1, 1, 50, 0, 0, 0, 0),
(16, 522003, 2, 7, 4, 1, 1, 100, 0, 0, 0, 0),
(15, 522002, 2, 7, 3, 1, 1, 100, 0, 0, 0, 0),
(14, 522001, 2, 7, 2, 1, 1, 100, 0, 0, 0, 0),
(13, 500001, 2, 7, 0, 1, 1, 100, 0, 0, 0, 0),
(12, 11140272, 2, 1, 0, 1, 1, 255, 0, 0, 0, 0),
(11, 19907, 2, 0, 6, 1, 1, 255, 0, 0, 0, 0),
(10, 19901, 2, 0, 0, 1, 1, 255, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `portals`
--

CREATE TABLE `portals` (
  `id` int(10) NOT NULL,
  `CharacterID` int(10) DEFAULT NULL,
  `PortalID` smallint(3) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `portals`
--

INSERT INTO `portals` (`id`, `CharacterID`, `PortalID`) VALUES
(1, 2, 1),
(2, 2, 15),
(3, 2, 8);

-- --------------------------------------------------------

--
-- Table structure for table `quickslot`
--

CREATE TABLE `quickslot` (
  `pkQuick` int(15) NOT NULL,
  `charId` int(11) DEFAULT NULL,
  `slotId_0` int(10) UNSIGNED DEFAULT '0',
  `slotId_1` int(10) UNSIGNED DEFAULT '0',
  `slotId_2` int(10) UNSIGNED DEFAULT '0',
  `slotId_3` int(10) UNSIGNED DEFAULT '0',
  `slotId_4` int(10) UNSIGNED DEFAULT '0',
  `slotId_5` int(10) UNSIGNED DEFAULT '0',
  `slotId_6` int(10) UNSIGNED DEFAULT '0',
  `slotId_7` int(10) UNSIGNED DEFAULT '0',
  `slotId_8` int(10) UNSIGNED DEFAULT '0',
  `slotId_9` int(10) UNSIGNED DEFAULT '0',
  `slotId_10` int(10) UNSIGNED DEFAULT '0',
  `slotId_11` int(10) UNSIGNED DEFAULT '0',
  `slotId_12` int(10) UNSIGNED DEFAULT '0',
  `slotId_13` int(10) UNSIGNED DEFAULT '0',
  `slotId_14` int(10) UNSIGNED DEFAULT '0',
  `slotId_15` int(10) UNSIGNED DEFAULT '0',
  `slotId_16` int(10) UNSIGNED DEFAULT '0',
  `slotId_17` int(10) UNSIGNED DEFAULT '0',
  `slotId_18` int(10) UNSIGNED DEFAULT '0',
  `slotId_19` int(10) UNSIGNED DEFAULT '0',
  `slotId_20` int(10) UNSIGNED DEFAULT '0',
  `slotId_21` int(10) UNSIGNED DEFAULT '0',
  `slotId_22` int(10) UNSIGNED DEFAULT '0',
  `slotId_23` int(10) UNSIGNED DEFAULT '0',
  `slotId_24` int(10) UNSIGNED DEFAULT '0',
  `slotId_25` int(10) UNSIGNED DEFAULT '0',
  `slotId_26` int(10) UNSIGNED DEFAULT '0',
  `slotId_27` int(10) UNSIGNED DEFAULT '0',
  `slotId_28` int(10) UNSIGNED DEFAULT '0',
  `slotId_29` int(10) UNSIGNED DEFAULT '0',
  `slotId_30` int(10) UNSIGNED DEFAULT '0',
  `slotId_31` int(10) UNSIGNED DEFAULT '0',
  `slotId_32` int(10) UNSIGNED DEFAULT '0',
  `slotId_33` int(10) UNSIGNED DEFAULT '0',
  `slotId_34` int(10) UNSIGNED DEFAULT '0',
  `slotId_35` int(10) UNSIGNED DEFAULT '0',
  `slotId_36` int(10) UNSIGNED DEFAULT '0',
  `slotId_37` int(10) UNSIGNED DEFAULT '0',
  `slotId_38` int(10) UNSIGNED DEFAULT '0',
  `slotId_39` int(10) UNSIGNED DEFAULT '0',
  `slotId_40` int(10) UNSIGNED DEFAULT '0',
  `slotId_41` int(10) UNSIGNED DEFAULT '0',
  `slotId_42` int(10) UNSIGNED DEFAULT '0',
  `slotId_43` int(10) UNSIGNED DEFAULT '0',
  `slotId_44` int(10) UNSIGNED DEFAULT '0',
  `slotId_45` int(10) UNSIGNED DEFAULT '0',
  `slotId_46` int(10) UNSIGNED DEFAULT '0',
  `slotId_47` int(10) DEFAULT NULL,
  `placeID` int(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `quickslot`
--

INSERT INTO `quickslot` (`pkQuick`, `charId`, `slotId_0`, `slotId_1`, `slotId_2`, `slotId_3`, `slotId_4`, `slotId_5`, `slotId_6`, `slotId_7`, `slotId_8`, `slotId_9`, `slotId_10`, `slotId_11`, `slotId_12`, `slotId_13`, `slotId_14`, `slotId_15`, `slotId_16`, `slotId_17`, `slotId_18`, `slotId_19`, `slotId_20`, `slotId_21`, `slotId_22`, `slotId_23`, `slotId_24`, `slotId_25`, `slotId_26`, `slotId_27`, `slotId_28`, `slotId_29`, `slotId_30`, `slotId_31`, `slotId_32`, `slotId_33`, `slotId_34`, `slotId_35`, `slotId_36`, `slotId_37`, `slotId_38`, `slotId_39`, `slotId_40`, `slotId_41`, `slotId_42`, `slotId_43`, `slotId_44`, `slotId_45`, `slotId_46`, `slotId_47`, `placeID`) VALUES
(1, 2, 10311, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `realmlist`
--

CREATE TABLE `realmlist` (
  `id` int(11) UNSIGNED NOT NULL,
  `ServerID` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `ChannelID` int(11) UNSIGNED NOT NULL DEFAULT '0',
  `realmflags` tinyint(3) UNSIGNED NOT NULL DEFAULT '2',
  `population` float UNSIGNED NOT NULL,
  `IsEvent` int(11) DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Realm System' ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `realmlist`
--

INSERT INTO `realmlist` (`id`, `ServerID`, `ChannelID`, `realmflags`, `population`, `IsEvent`) VALUES
(1, 1, 1, 1, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `skills`
--

CREATE TABLE `skills` (
  `id` int(11) UNSIGNED NOT NULL,
  `skill_id` int(10) UNSIGNED NOT NULL DEFAULT '0',
  `owner_id` int(11) UNSIGNED NOT NULL,
  `RpBonusAuto` bit(1) DEFAULT b'0',
  `RpBonusType` int(5) UNSIGNED NOT NULL DEFAULT '0',
  `SlotID` smallint(3) UNSIGNED NOT NULL DEFAULT '0',
  `TimeRemaining` int(15) UNSIGNED NOT NULL,
  `Exp` int(5) UNSIGNED NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `skills`
--

INSERT INTO `skills` (`id`, `skill_id`, `owner_id`, `RpBonusAuto`, `RpBonusType`, `SlotID`, `TimeRemaining`, `Exp`) VALUES
(1, 10311, 2, b'1111111111111111111111111111111', 0, 1, 0, 0),
(2, 20091, 2, b'1111111111111111111111111111111', 0, 2, 0, 0),
(3, 20111, 2, b'1111111111111111111111111111111', 0, 3, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `titlelist`
--

CREATE TABLE `titlelist` (
  `id` int(10) NOT NULL,
  `CharacterID` int(10) DEFAULT NULL,
  `TitleID` smallint(3) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Table structure for table `warfoginfo`
--

CREATE TABLE `warfoginfo` (
  `idFog` int(11) NOT NULL,
  `hObject` int(11) NOT NULL,
  `owner_id` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `account`
--
ALTER TABLE `account`
  ADD PRIMARY KEY (`AccountID`) USING BTREE,
  ADD UNIQUE KEY `AccountID_UNIQUE` (`AccountID`) USING BTREE;

--
-- Indexes for table `bind`
--
ALTER TABLE `bind`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indexes for table `characters`
--
ALTER TABLE `characters`
  ADD PRIMARY KEY (`CharacterID`) USING BTREE,
  ADD UNIQUE KEY `CharacterID_UNIQUE` (`CharacterID`) USING BTREE,
  ADD UNIQUE KEY `Name_UNIQUE` (`Name`) USING BTREE;

--
-- Indexes for table `characters_attributes`
--
ALTER TABLE `characters_attributes`
  ADD PRIMARY KEY (`ID`) USING BTREE;

--
-- Indexes for table `items`
--
ALTER TABLE `items`
  ADD PRIMARY KEY (`id`) USING BTREE,
  ADD KEY `owner_id_idx` (`owner_id`) USING BTREE,
  ADD KEY `item_vnum_index` (`tblidx`) USING BTREE;

--
-- Indexes for table `portals`
--
ALTER TABLE `portals`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indexes for table `quickslot`
--
ALTER TABLE `quickslot`
  ADD PRIMARY KEY (`pkQuick`) USING BTREE;

--
-- Indexes for table `realmlist`
--
ALTER TABLE `realmlist`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indexes for table `skills`
--
ALTER TABLE `skills`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indexes for table `titlelist`
--
ALTER TABLE `titlelist`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indexes for table `warfoginfo`
--
ALTER TABLE `warfoginfo`
  ADD PRIMARY KEY (`idFog`) USING BTREE;

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `account`
--
ALTER TABLE `account`
  MODIFY `AccountID` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT for table `bind`
--
ALTER TABLE `bind`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `characters`
--
ALTER TABLE `characters`
  MODIFY `CharacterID` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT for table `characters_attributes`
--
ALTER TABLE `characters_attributes`
  MODIFY `ID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `items`
--
ALTER TABLE `items`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=19;
--
-- AUTO_INCREMENT for table `portals`
--
ALTER TABLE `portals`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT for table `quickslot`
--
ALTER TABLE `quickslot`
  MODIFY `pkQuick` int(15) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `realmlist`
--
ALTER TABLE `realmlist`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `skills`
--
ALTER TABLE `skills`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT for table `titlelist`
--
ALTER TABLE `titlelist`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `warfoginfo`
--
ALTER TABLE `warfoginfo`
  MODIFY `idFog` int(11) NOT NULL AUTO_INCREMENT;COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
