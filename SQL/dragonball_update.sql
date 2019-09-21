-- phpMyAdmin SQL Dump
-- version 4.7.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Sep 20, 2019 at 01:36 AM
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
-- Database: `dboplay`
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
(10, 'Test', '123', 0, 0, 0, 255, 0, NULL, '127.0.0.1');

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
(1, 2, 1, 6),
(2, 3, 1, 6),
(3, 4, 1, 6),
(4, 5, 1, 6),
(5, 6, 1, 6),
(6, 7, 1, 6),
(7, 8, 1, 6),
(8, 9, 1, 6),
(9, 10, 1, 6),
(10, 11, 1, 6),
(11, 12, 1, 6),
(12, 13, 1, 6),
(13, 14, 1, 6),
(14, 1, 1, 6);

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
  `IsTutorialDone` tinyint(1) NOT NULL DEFAULT '1',
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
  `deletionStartedAt` varchar(20) DEFAULT NULL,
  `WagguCoin` int(11) NOT NULL DEFAULT '0',
  `EventCoin` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `characters`
--

INSERT INTO `characters` (`CharacterID`, `AccountID`, `GuildID`, `Name`, `ServerID`, `RaceID`, `ClassID`, `GenderID`, `FaceID`, `HairID`, `HairColorID`, `SkinColorID`, `CurrentLevel`, `CurrentExp`, `MapInfoID`, `WorldTableID`, `WorldID`, `BindType`, `BindWorldID`, `BindObjectID`, `Position_X`, `Position_Y`, `Position_Z`, `Direction_X`, `Direction_Y`, `Direction_Z`, `ZennyInventory`, `ZennyBank`, `Token`, `WP_Point`, `CashPoint`, `IsVip`, `Title_Marking`, `MixExp`, `MixLevel`, `IsAdult`, `IsTutorialDone`, `IsToRename`, `IsToDelete`, `IsToChangeClass`, `IsOnline`, `IsGameMaster`, `HintsDone`, `Reputation`, `Mudosa`, `SkillPoints`, `createdAt`, `deletionStartedAt`, `WagguCoin`, `EventCoin`) VALUES
(6, 10, 0, '[Dev]Test', 0, 0, 10, 0, 8, 1, 4, 2, 70, 0, 4294967295, 1, 1, 0, 0, 0, 5812.669922, -100.300003, 775.619995, 0.842000, 0.000000, 0.539300, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0);

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
(19, 6, 56, 56, 80, 80, 96, 96, 72, 72, 120, 120, 104, 104, 6528, 6528, 5824, 5824, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 92, 92, 0, 0, 240, 240, 0, 0, 960, 960, 360, 360, 0, 0, 0, 0, 0, 0, 36, 36, 57, 57, 8.00000, 1500, 1500, 35.00000, 35.00000, 100.00000, 100.00000, 100.00000, 100.00000, 100.00000, 100.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0, 0, 0, 0, 0, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 450000, 7600, 5720, 0, 450000, 450000);

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
(2212, 19991, 3, 9, 0, 1, 1, 255, 0, 0, 0, 0),
(2211, 11170034, 3, 7, 16, 1, 5, 255, 0, 0, 0, 0),
(2210, 11170037, 3, 7, 15, 1, 5, 255, 0, 0, 0, 0),
(2209, 11170002, 3, 7, 14, 1, 1, 100, 0, 0, 0, 0),
(2208, 11170108, 3, 7, 12, 1, 1, 100, 0, 0, 0, 0),
(2207, 60000000, 3, 7, 5, 1, 1, 50, 0, 0, 0, 0),
(781, 19991, 2, 9, 0, 1, 1, 255, 0, 0, 0, 0),
(780, 60000000, 2, 7, 5, 1, 1, 50, 0, 0, 0, 0),
(779, 523003, 2, 7, 4, 1, 1, 100, 0, 0, 0, 0),
(778, 523002, 2, 7, 3, 1, 1, 100, 0, 0, 0, 0),
(777, 523001, 2, 7, 2, 1, 1, 100, 0, 0, 0, 0),
(776, 505001, 2, 7, 0, 1, 1, 100, 0, 0, 0, 0),
(775, 11140272, 2, 1, 0, 1, 1, 255, 0, 0, 0, 0),
(774, 19907, 2, 0, 6, 1, 1, 255, 0, 0, 0, 0),
(773, 19901, 2, 0, 0, 1, 1, 255, 0, 0, 0, 0),
(881, 19991, 1, 9, 0, 1, 1, 255, 0, 0, 0, 0),
(880, 60000000, 1, 7, 5, 1, 1, 50, 0, 0, 0, 0),
(879, 522003, 1, 7, 4, 1, 1, 100, 0, 0, 0, 0),
(878, 522002, 1, 7, 3, 1, 1, 100, 0, 0, 0, 0),
(877, 522001, 1, 7, 2, 1, 1, 100, 0, 0, 0, 0),
(876, 500001, 1, 7, 0, 1, 1, 100, 0, 0, 0, 0),
(875, 11120041, 1, 1, 1, 1, 1, 100, 0, 0, 0, 0),
(874, 11140272, 1, 1, 0, 1, 1, 255, 0, 0, 0, 0),
(873, 19907, 1, 0, 6, 1, 1, 255, 0, 0, 0, 0),
(872, 19901, 1, 0, 0, 1, 1, 255, 0, 0, 0, 0),
(2206, 522087, 3, 7, 4, 1, 1, 100, 15, 0, 0, 0),
(2205, 522086, 3, 7, 3, 1, 1, 100, 15, 0, 0, 0),
(2204, 522085, 3, 7, 2, 1, 1, 100, 15, 0, 0, 0),
(2203, 832306, 3, 7, 1, 1, 1, 100, 15, 0, 0, 0),
(2202, 500014, 3, 7, 0, 1, 1, 100, 15, 0, 0, 0),
(2201, 522003, 3, 2, 5, 1, 1, 100, 0, 0, 0, 0),
(2200, 522002, 3, 2, 4, 1, 1, 100, 0, 0, 0, 0),
(2199, 522001, 3, 2, 3, 1, 1, 100, 0, 0, 0, 0),
(2198, 500001, 3, 2, 2, 1, 1, 100, 0, 0, 0, 0),
(2197, 95, 3, 2, 1, 1, 1, 255, 0, 0, 0, 0),
(2196, 26, 3, 2, 0, 1, 1, 255, 0, 0, 0, 0),
(2195, 11120175, 3, 1, 15, 1, 1, 255, 0, 0, 0, 0),
(2194, 11120174, 3, 1, 14, 4, 1, 255, 0, 0, 0, 0),
(1610, 19991, 4, 9, 0, 1, 1, 255, 0, 0, 0, 0),
(1609, 60000000, 4, 7, 5, 1, 1, 50, 0, 0, 0, 0),
(1608, 523003, 4, 7, 4, 1, 1, 100, 0, 0, 0, 0),
(1607, 523002, 4, 7, 3, 1, 1, 100, 0, 0, 0, 0),
(1606, 523001, 4, 7, 2, 1, 1, 100, 0, 0, 0, 0),
(1605, 505001, 4, 7, 0, 1, 1, 100, 0, 0, 0, 0),
(1604, 11140272, 4, 1, 0, 1, 1, 255, 0, 0, 0, 0),
(1603, 19907, 4, 0, 6, 1, 1, 255, 0, 0, 0, 0),
(1602, 19901, 4, 0, 0, 1, 1, 255, 0, 0, 0, 0),
(2193, 11100011, 3, 1, 13, 1, 4, 255, 0, 0, 0, 0),
(2192, 11100010, 3, 1, 12, 1, 4, 255, 0, 0, 0, 0),
(2191, 11120149, 3, 1, 11, 5, 1, 255, 0, 0, 0, 0),
(2173, 19991, 5, 9, 0, 1, 1, 255, 0, 0, 0, 0),
(2172, 60000000, 5, 7, 5, 1, 1, 50, 0, 0, 0, 0),
(2171, 525003, 5, 7, 4, 1, 1, 100, 0, 0, 0, 0),
(2170, 525002, 5, 7, 3, 1, 1, 100, 0, 0, 0, 0),
(2169, 525001, 5, 7, 2, 1, 1, 100, 0, 0, 0, 0),
(2168, 508010, 5, 7, 1, 1, 1, 100, 15, 0, 0, 0),
(2167, 500001, 5, 7, 0, 1, 1, 100, 0, 0, 0, 0),
(2166, 11140272, 5, 1, 0, 1, 1, 255, 0, 0, 0, 0),
(2190, 11140284, 3, 1, 10, 1, 2, 255, 0, 0, 0, 0),
(2189, 11120176, 3, 1, 9, 1, 1, 255, 0, 0, 0, 0),
(2188, 11100003, 3, 1, 8, 30, 1, 255, 0, 0, 0, 0),
(2187, 303007, 3, 1, 7, 1, 1, 255, 0, 0, 0, 0),
(2186, 11100005, 3, 1, 6, 30, 1, 255, 0, 0, 0, 0),
(2185, 11120149, 3, 1, 5, 10, 1, 255, 0, 0, 0, 0),
(2184, 11120174, 3, 1, 4, 4, 1, 255, 0, 0, 0, 0),
(2183, 11130001, 3, 1, 3, 1, 1, 255, 0, 0, 0, 0),
(2182, 11, 3, 1, 2, 1, 1, 255, 0, 0, 0, 0),
(2181, 65, 3, 1, 1, 1, 3, 255, 0, 0, 0, 0),
(2180, 11140277, 3, 1, 0, 1, 1, 255, 0, 0, 0, 0),
(2179, 19907, 3, 0, 6, 1, 1, 255, 0, 0, 0, 0),
(2178, 403043, 3, 0, 4, 1, 1, 255, 0, 0, 0, 0),
(2177, 403043, 3, 0, 3, 1, 1, 255, 0, 0, 0, 0),
(2176, 403043, 3, 0, 2, 1, 1, 255, 0, 0, 0, 0),
(2175, 403043, 3, 0, 1, 1, 1, 255, 0, 0, 0, 0),
(2174, 19901, 3, 0, 0, 1, 1, 255, 0, 0, 0, 0),
(2143, 19991, 8, 9, 0, 1, 1, 255, 0, 0, 0, 0),
(2142, 60000000, 8, 7, 5, 1, 1, 50, 0, 0, 0, 0),
(2141, 525003, 8, 7, 4, 1, 1, 100, 0, 0, 0, 0),
(2032, 19991, 6, 9, 0, 1, 1, 255, 0, 0, 0, 0),
(2031, 11170035, 6, 7, 16, 1, 5, 255, 0, 0, 0, 0),
(2030, 11170038, 6, 7, 15, 1, 5, 255, 0, 0, 0, 0),
(2271, 19991, 7, 9, 0, 1, 1, 255, 0, 0, 0, 0),
(2270, 60000000, 7, 7, 5, 1, 1, 50, 0, 0, 0, 0),
(2269, 523003, 7, 7, 4, 1, 1, 100, 0, 0, 0, 0),
(2268, 523002, 7, 7, 3, 1, 1, 100, 0, 0, 0, 0),
(2267, 523001, 7, 7, 2, 1, 1, 100, 0, 0, 0, 0),
(2266, 505001, 7, 7, 0, 1, 1, 100, 0, 0, 0, 0),
(2265, 23, 7, 1, 1, 1, 1, 255, 0, 0, 0, 0),
(2264, 11140272, 7, 1, 0, 1, 1, 255, 0, 0, 0, 0),
(2263, 19907, 7, 0, 6, 1, 1, 255, 0, 0, 0, 0),
(2029, 11170002, 6, 7, 14, 1, 1, 100, 0, 0, 0, 0),
(2028, 11170256, 6, 7, 12, 1, 1, 100, 0, 0, 0, 0),
(2027, 11120199, 6, 7, 11, 1, 4, 255, 0, 0, 0, 0),
(2026, 11120200, 6, 7, 10, 1, 5, 255, 0, 0, 0, 0),
(2025, 60000000, 6, 7, 5, 1, 1, 50, 0, 0, 0, 0),
(2024, 554006, 6, 7, 1, 1, 1, 100, 15, 0, 0, 0),
(2023, 505001, 6, 7, 0, 1, 1, 100, 0, 0, 0, 0),
(2022, 523021, 6, 7, 4, 1, 1, 100, 15, 0, 0, 0),
(2021, 523020, 6, 7, 3, 1, 1, 100, 15, 0, 0, 0),
(2165, 19907, 5, 0, 6, 1, 1, 255, 0, 0, 0, 0),
(2262, 19901, 7, 0, 0, 1, 1, 255, 0, 0, 0, 0),
(2164, 19901, 5, 0, 0, 1, 1, 255, 0, 0, 0, 0),
(2140, 525002, 8, 7, 3, 1, 1, 100, 0, 0, 0, 0),
(2139, 525001, 8, 7, 2, 1, 1, 100, 0, 0, 0, 0),
(2138, 500001, 8, 7, 0, 1, 1, 100, 0, 0, 0, 0),
(2137, 11140272, 8, 1, 0, 1, 1, 255, 0, 0, 0, 0),
(2136, 19907, 8, 0, 6, 1, 1, 255, 0, 0, 0, 0),
(2135, 19901, 8, 0, 0, 1, 1, 255, 0, 0, 0, 0),
(2020, 523019, 6, 7, 2, 1, 1, 100, 15, 0, 0, 0),
(2019, 19907, 6, 0, 6, 1, 1, 255, 0, 0, 0, 0),
(2018, 303007, 6, 0, 1, 1, 1, 255, 0, 0, 0, 0),
(2017, 19901, 6, 0, 0, 1, 1, 255, 0, 0, 0, 0);

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
(3, 2, 8),
(4, 3, 1),
(5, 3, 15),
(6, 3, 8),
(7, 4, 1),
(8, 4, 15),
(9, 4, 8),
(10, 5, 1),
(11, 5, 15),
(12, 5, 8),
(13, 6, 1),
(14, 6, 15),
(15, 6, 8),
(16, 7, 3),
(17, 7, 15),
(18, 7, 8),
(19, 8, 1),
(20, 8, 15),
(21, 8, 8),
(22, 9, 1),
(23, 9, 15),
(24, 9, 8),
(25, 10, 1),
(26, 10, 15),
(27, 10, 8),
(28, 11, 1),
(29, 11, 15),
(30, 11, 8),
(31, 12, 3),
(32, 12, 15),
(33, 12, 8),
(34, 13, 1),
(35, 13, 15),
(36, 13, 8),
(37, 14, 1),
(38, 14, 15),
(39, 14, 8),
(40, 1, 1),
(41, 1, 15),
(42, 1, 8),
(43, 2, 1),
(44, 2, 15),
(45, 2, 8),
(46, 3, 1),
(47, 3, 15),
(48, 3, 8),
(49, 4, 1),
(50, 4, 15),
(51, 4, 8),
(52, 3, 22),
(53, 3, 24),
(54, 5, 3),
(55, 5, 15),
(56, 5, 8),
(57, 6, 1),
(58, 6, 15),
(59, 6, 8),
(60, 7, 1),
(61, 7, 15),
(62, 7, 8),
(63, 8, 3),
(64, 8, 15),
(65, 8, 8);

-- --------------------------------------------------------

--
-- Table structure for table `questlist`
--

CREATE TABLE `questlist` (
  `type` int(11) NOT NULL,
  `tId` int(11) NOT NULL,
  `currentID` int(11) NOT NULL,
  `nextID` int(11) NOT NULL,
  `charID` int(11) NOT NULL,
  `isCompleted` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

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
(1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(2, 3, 10311, 10014, 10111, 10416, 10714, 710631, 710011, 710854, 710875, 0, 0, 0, 20117, 20515, 20614, 20815, 720032, 720631, 0, 0, 0, 20083, 21011, 20091, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(4, 5, 310111, 310011, 310311, 310511, 310411, 310211, 310221, 310711, 0, 0, 0, 0, 320112, 320031, 320041, 320051, 320061, 320611, 0, 0, 0, 0, 0, 320101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(5, 6, 110218, 1010603, 1010014, 1010624, 1010565, 1010585, 1010505, 110314, 120513, 120103, 121111, 0, 120041, 1020031, 1020041, 1020051, 1021141, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(6, 7, 110111, 110211, 110311, 110511, 0, 0, 0, 0, 0, 0, 0, 0, 120041, 120031, 110011, 110021, 110031, 110041, 120061, 120081, 120091, 120051, 120071, 120511, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(7, 8, 310111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 320111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 320101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(9, 10, 10311, 10014, 10416, 10714, 0, 0, 0, 0, 0, 0, 0, 0, 20117, 20011, 20515, 20614, 20815, 0, 0, 0, 0, 21011, 20083, 20091, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(11, 12, 310111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 320111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(12, 13, 10311, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20091, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(13, 14, 10311, 10014, 10111, 10416, 10714, 710854, 710875, 720731, 720751, 0, 0, 0, 20117, 20011, 20515, 20614, 20815, 720035, 720044, 720633, 0, 0, 20083, 20091, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(14, 1, 10311, 10014, 10111, 10416, 10714, 0, 0, 0, 0, 0, 0, 0, 20111, 20011, 20515, 20614, 20815, 0, 0, 0, 0, 20083, 21011, 20091, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(15, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(16, 3, 0, 10014, 10111, 10416, 10714, 710631, 710011, 710854, 710875, 0, 0, 0, 20117, 20515, 20614, 20815, 720032, 720631, 0, 0, 0, 20083, 21011, 20091, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(17, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(18, 5, 310111, 310011, 310311, 310511, 310411, 310211, 310221, 310711, 0, 0, 0, 0, 320112, 320031, 320041, 320051, 320061, 320611, 0, 0, 0, 0, 0, 320101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(19, 6, 110218, 1010603, 1010014, 1010624, 1010565, 1010585, 1010505, 110314, 120513, 120103, 121111, 0, 120041, 1020031, 1020041, 1020051, 1021141, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(20, 7, 110111, 110211, 110311, 110511, 0, 0, 0, 0, 0, 0, 0, 0, 120041, 120031, 110011, 110021, 110031, 110041, 120061, 120081, 120091, 120051, 120071, 120511, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL),
(21, 8, 310111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 320111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 320101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL);

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
(2, 0, 0, 2, 0, 0);

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
(94, 10311, 1, b'1111111111111111111111111111111', 0, 1, 0, 0),
(95, 20091, 1, b'1111111111111111111111111111111', 0, 2, 0, 0),
(96, 20111, 1, b'1111111111111111111111111111111', 0, 3, 0, 0),
(97, 21011, 1, b'1111111111111111111111111111111', 0, 0, 0, 0),
(98, 110111, 2, b'1111111111111111111111111111111', 0, 1, 0, 0),
(99, 120131, 2, b'1111111111111111111111111111111', 0, 2, 0, 0),
(100, 110011, 2, b'1111111111111111111111111111111', 0, 3, 0, 0),
(101, 20021, 1, b'1111111111111111111111111111111', 0, 5, 0, 0),
(102, 20011, 1, b'1111111111111111111111111111111', 0, 6, 0, 0),
(103, 20031, 1, b'1111111111111111111111111111111', 0, 7, 0, 0),
(104, 20515, 1, b'1111111111111111111111111111111', 0, 8, 0, 0),
(105, 20071, 1, b'1111111111111111111111111111111', 0, 9, 0, 0),
(106, 20614, 1, b'1111111111111111111111111111111', 0, 10, 0, 0),
(107, 20815, 1, b'1111111111111111111111111111111', 0, 11, 0, 0),
(108, 20083, 1, b'1111111111111111111111111111111', 0, 12, 0, 0),
(109, 20043, 1, b'1111111111111111111111111111111', 0, 13, 0, 0),
(110, 10014, 1, b'1111111111111111111111111111111', 0, 14, 0, 0),
(111, 10111, 1, b'1111111111111111111111111111111', 0, 15, 0, 0),
(112, 10416, 1, b'1111111111111111111111111111111', 0, 16, 0, 0),
(113, 10714, 1, b'1111111111111111111111111111111', 0, 17, 0, 0),
(114, 10311, 3, b'1111111111111111111111111111111', 0, 1, 0, 0),
(115, 20091, 3, b'1111111111111111111111111111111', 0, 2, 0, 0),
(116, 20117, 3, b'1111111111111111111111111111111', 0, 3, 0, 0),
(117, 110111, 4, b'1111111111111111111111111111111', 0, 1, 0, 0),
(118, 120131, 4, b'1111111111111111111111111111111', 0, 2, 0, 0),
(119, 110011, 4, b'1111111111111111111111111111111', 0, 3, 0, 0),
(120, 21011, 3, b'1111111111111111111111111111111', 0, 0, 0, 0),
(121, 20083, 3, b'1111111111111111111111111111111', 0, 8, 0, 0),
(122, 10014, 3, b'1111111111111111111111111111111', 0, 9, 0, 0),
(123, 10111, 3, b'1111111111111111111111111111111', 0, 10, 0, 0),
(124, 10416, 3, b'1111111111111111111111111111111', 0, 11, 0, 0),
(125, 10714, 3, b'1111111111111111111111111111111', 0, 12, 0, 0),
(126, 20043, 3, b'1111111111111111111111111111111', 0, 13, 0, 0),
(127, 20021, 3, b'1111111111111111111111111111111', 0, 14, 0, 0),
(128, 20011, 3, b'1111111111111111111111111111111', 0, 15, 0, 0),
(129, 20031, 3, b'1111111111111111111111111111111', 0, 16, 0, 0),
(130, 20515, 3, b'1111111111111111111111111111111', 0, 17, 0, 0),
(131, 20071, 3, b'1111111111111111111111111111111', 0, 18, 0, 0),
(132, 20614, 3, b'1111111111111111111111111111111', 0, 19, 0, 0),
(133, 20815, 3, b'1111111111111111111111111111111', 0, 20, 0, 0),
(136, 729991, 3, b'1111111111111111111111111111111', 0, 21, 0, 0),
(137, 720054, 3, b'1111111111111111111111111111111', 0, 22, 0, 0),
(138, 720164, 3, b'1111111111111111111111111111111', 0, 23, 0, 0),
(139, 720032, 3, b'1111111111111111111111111111111', 0, 24, 0, 0),
(140, 710631, 3, b'1111111111111111111111111111111', 0, 25, 0, 0),
(141, 710011, 3, b'1111111111111111111111111111111', 0, 26, 0, 0),
(142, 710854, 3, b'1111111111111111111111111111111', 0, 27, 0, 0),
(143, 710875, 3, b'1111111111111111111111111111111', 0, 28, 0, 0),
(144, 720071, 3, b'1111111111111111111111111111111', 0, 29, 0, 0),
(145, 720011, 3, b'1111111111111111111111111111111', 0, 30, 0, 0),
(146, 720631, 3, b'1111111111111111111111111111111', 0, 31, 0, 0),
(147, 20911, 3, b'1111111111111111111111111111111', 0, 32, 0, 0),
(148, 20221, 3, b'1111111111111111111111111111111', 0, 33, 0, 0),
(149, 20201, 3, b'1111111111111111111111111111111', 0, 34, 0, 0),
(150, 10021, 3, b'1111111111111111111111111111111', 0, 35, 0, 0),
(151, 20211, 3, b'1111111111111111111111111111111', 0, 36, 0, 0),
(152, 310111, 5, b'1111111111111111111111111111111', 0, 1, 0, 0),
(153, 320101, 5, b'1111111111111111111111111111111', 0, 2, 0, 0),
(154, 320112, 5, b'1111111111111111111111111111111', 0, 3, 0, 0),
(155, 110111, 6, b'1111111111111111111111111111111', 0, 1, 0, 0),
(156, 120131, 6, b'1111111111111111111111111111111', 0, 2, 0, 0),
(157, 110011, 6, b'1111111111111111111111111111111', 0, 3, 0, 0),
(158, 110111, 7, b'1111111111111111111111111111111', 0, 1, 0, 0),
(159, 120131, 7, b'1111111111111111111111111111111', 0, 2, 0, 0),
(160, 110011, 7, b'1111111111111111111111111111111', 0, 3, 0, 0),
(161, 121111, 6, b'1111111111111111111111111111111', 0, 4, 0, 0),
(163, 120103, 6, b'1111111111111111111111111111111', 0, 8, 0, 0),
(164, 110218, 6, b'1111111111111111111111111111111', 0, 9, 0, 0),
(165, 110314, 6, b'1111111111111111111111111111111', 0, 10, 0, 0),
(166, 110511, 6, b'1111111111111111111111111111111', 0, 11, 0, 0),
(167, 110021, 6, b'1111111111111111111111111111111', 0, 12, 0, 0),
(168, 110031, 6, b'1111111111111111111111111111111', 0, 13, 0, 0),
(169, 110041, 6, b'1111111111111111111111111111111', 0, 14, 0, 0),
(170, 120021, 6, b'1111111111111111111111111111111', 0, 15, 0, 0),
(171, 120011, 6, b'1111111111111111111111111111111', 0, 16, 0, 0),
(172, 120061, 6, b'1111111111111111111111111111111', 0, 17, 0, 0),
(173, 120041, 6, b'1111111111111111111111111111111', 0, 18, 0, 0),
(174, 120081, 6, b'1111111111111111111111111111111', 0, 19, 0, 0),
(175, 120091, 6, b'1111111111111111111111111111111', 0, 20, 0, 0),
(176, 120031, 6, b'1111111111111111111111111111111', 0, 21, 0, 0),
(177, 120071, 6, b'1111111111111111111111111111111', 0, 22, 0, 0),
(178, 120513, 6, b'1111111111111111111111111111111', 0, 23, 0, 0),
(179, 120051, 6, b'1111111111111111111111111111111', 0, 24, 0, 0),
(180, 1029991, 6, b'1111111111111111111111111111111', 0, 25, 0, 0),
(181, 120501, 6, b'1111111111111111111111111111111', 0, 26, 0, 0),
(182, 120911, 6, b'1111111111111111111111111111111', 0, 27, 0, 0),
(183, 1010441, 6, b'1111111111111111111111111111111', 0, 28, 0, 0),
(184, 1010565, 6, b'1111111111111111111111111111111', 0, 29, 0, 0),
(185, 1020031, 6, b'1111111111111111111111111111111', 0, 30, 0, 0),
(186, 1010505, 6, b'1111111111111111111111111111111', 0, 31, 0, 0),
(187, 1010603, 6, b'1111111111111111111111111111111', 0, 32, 0, 0),
(188, 1010014, 6, b'1111111111111111111111111111111', 0, 33, 0, 0),
(189, 1010624, 6, b'1111111111111111111111111111111', 0, 34, 0, 0),
(190, 1010461, 6, b'1111111111111111111111111111111', 0, 35, 0, 0),
(191, 1020041, 6, b'1111111111111111111111111111111', 0, 36, 0, 0),
(192, 1020051, 6, b'1111111111111111111111111111111', 0, 37, 0, 0),
(193, 1020841, 6, b'1111111111111111111111111111111', 0, 38, 0, 0),
(194, 1020071, 6, b'1111111111111111111111111111111', 0, 39, 0, 0),
(195, 1021141, 6, b'1111111111111111111111111111111', 0, 40, 0, 0),
(196, 1020061, 6, b'1111111111111111111111111111111', 0, 41, 0, 0),
(197, 1020121, 6, b'1111111111111111111111111111111', 0, 42, 0, 0),
(198, 1020021, 6, b'1111111111111111111111111111111', 0, 43, 0, 0),
(199, 1020011, 6, b'1111111111111111111111111111111', 0, 44, 0, 0),
(200, 1010585, 6, b'1111111111111111111111111111111', 0, 45, 0, 0),
(204, 1329996, 5, b'1111111111111111111111111111111', 0, 4, 0, 0),
(205, 310011, 5, b'1111111111111111111111111111111', 0, 5, 0, 0),
(206, 310311, 5, b'1111111111111111111111111111111', 0, 6, 0, 0),
(207, 310511, 5, b'1111111111111111111111111111111', 0, 7, 0, 0),
(208, 310411, 5, b'1111111111111111111111111111111', 0, 8, 0, 0),
(209, 310211, 5, b'1111111111111111111111111111111', 0, 9, 0, 0),
(210, 310221, 5, b'1111111111111111111111111111111', 0, 10, 0, 0),
(211, 310711, 5, b'1111111111111111111111111111111', 0, 11, 0, 0),
(212, 320031, 5, b'1111111111111111111111111111111', 0, 12, 0, 0),
(213, 320081, 5, b'1111111111111111111111111111111', 0, 13, 0, 0),
(214, 320041, 5, b'1111111111111111111111111111111', 0, 14, 0, 0),
(215, 320051, 5, b'1111111111111111111111111111111', 0, 15, 0, 0),
(216, 320511, 5, b'1111111111111111111111111111111', 0, 16, 0, 0),
(217, 320411, 5, b'1111111111111111111111111111111', 0, 17, 0, 0),
(218, 320071, 5, b'1111111111111111111111111111111', 0, 18, 0, 0),
(219, 320061, 5, b'1111111111111111111111111111111', 0, 19, 0, 0),
(220, 320611, 5, b'1111111111111111111111111111111', 0, 20, 0, 0),
(221, 320013, 5, b'1111111111111111111111111111111', 0, 21, 0, 0),
(222, 320023, 5, b'1111111111111111111111111111111', 0, 22, 0, 0),
(223, 320093, 5, b'1111111111111111111111111111111', 0, 23, 0, 0),
(224, 1320013, 5, b'1111111111111111111111111111111', 0, 24, 0, 0),
(225, 1320023, 5, b'1111111111111111111111111111111', 0, 25, 0, 0),
(226, 1320123, 5, b'1111111111111111111111111111111', 0, 26, 0, 0),
(227, 1310631, 5, b'1111111111111111111111111111111', 0, 27, 0, 0),
(228, 1310771, 5, b'1111111111111111111111111111111', 0, 28, 0, 0),
(229, 1310021, 5, b'1111111111111111111111111111111', 0, 29, 0, 0),
(230, 1310931, 5, b'1111111111111111111111111111111', 0, 30, 0, 0),
(231, 1310651, 5, b'1111111111111111111111111111111', 0, 31, 0, 0),
(232, 1310011, 5, b'1111111111111111111111111111111', 0, 32, 0, 0),
(233, 1310791, 5, b'1111111111111111111111111111111', 0, 33, 0, 0),
(234, 1310951, 5, b'1111111111111111111111111111111', 0, 34, 0, 0),
(235, 1320631, 5, b'1111111111111111111111111111111', 0, 35, 0, 0),
(236, 1320031, 5, b'1111111111111111111111111111111', 0, 36, 0, 0),
(237, 1320731, 5, b'1111111111111111111111111111111', 0, 37, 0, 0),
(238, 1320041, 5, b'1111111111111111111111111111111', 0, 38, 0, 0),
(239, 1320851, 5, b'1111111111111111111111111111111', 0, 39, 0, 0),
(240, 1320951, 5, b'1111111111111111111111111111111', 0, 40, 0, 0),
(241, 1320751, 5, b'1111111111111111111111111111111', 0, 41, 0, 0),
(242, 110211, 7, b'1111111111111111111111111111111', 0, 4, 0, 0),
(243, 110021, 7, b'1111111111111111111111111111111', 0, 5, 0, 0),
(244, 110311, 7, b'1111111111111111111111111111111', 0, 6, 0, 0),
(245, 110031, 7, b'1111111111111111111111111111111', 0, 7, 0, 0),
(246, 110511, 7, b'1111111111111111111111111111111', 0, 8, 0, 0),
(247, 110041, 7, b'1111111111111111111111111111111', 0, 9, 0, 0),
(248, 120061, 7, b'1111111111111111111111111111111', 0, 10, 0, 0),
(249, 120081, 7, b'1111111111111111111111111111111', 0, 11, 0, 0),
(250, 120041, 7, b'1111111111111111111111111111111', 0, 12, 0, 0),
(251, 120031, 7, b'1111111111111111111111111111111', 0, 13, 0, 0),
(252, 120091, 7, b'1111111111111111111111111111111', 0, 14, 0, 0),
(253, 120071, 7, b'1111111111111111111111111111111', 0, 15, 0, 0),
(254, 120051, 7, b'1111111111111111111111111111111', 0, 16, 0, 0),
(255, 120511, 7, b'1111111111111111111111111111111', 0, 17, 0, 0),
(256, 120023, 7, b'1111111111111111111111111111111', 0, 18, 0, 0);

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
-- Dumping data for table `warfoginfo`
--

INSERT INTO `warfoginfo` (`idFog`, `hObject`, `owner_id`) VALUES
(1, 100007, 3),
(2, 100004, 3);

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
  MODIFY `AccountID` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;
--
-- AUTO_INCREMENT for table `bind`
--
ALTER TABLE `bind`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;
--
-- AUTO_INCREMENT for table `characters`
--
ALTER TABLE `characters`
  MODIFY `CharacterID` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
--
-- AUTO_INCREMENT for table `characters_attributes`
--
ALTER TABLE `characters_attributes`
  MODIFY `ID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=22;
--
-- AUTO_INCREMENT for table `items`
--
ALTER TABLE `items`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2272;
--
-- AUTO_INCREMENT for table `portals`
--
ALTER TABLE `portals`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=66;
--
-- AUTO_INCREMENT for table `quickslot`
--
ALTER TABLE `quickslot`
  MODIFY `pkQuick` int(15) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=22;
--
-- AUTO_INCREMENT for table `realmlist`
--
ALTER TABLE `realmlist`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT for table `skills`
--
ALTER TABLE `skills`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=257;
--
-- AUTO_INCREMENT for table `titlelist`
--
ALTER TABLE `titlelist`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `warfoginfo`
--
ALTER TABLE `warfoginfo`
  MODIFY `idFog` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
