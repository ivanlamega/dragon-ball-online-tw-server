-- phpMyAdmin SQL Dump
-- version 5.0.1
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 09-03-2020 a las 18:36:10
-- Versión del servidor: 10.4.11-MariaDB
-- Versión de PHP: 7.4.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `dragonball`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `account`
--

CREATE TABLE `account` (
  `AccountID` bigint(20) UNSIGNED NOT NULL,
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
  `ip` varchar(50) CHARACTER SET utf8 COLLATE utf8_spanish2_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `aucionhouse`
--

CREATE TABLE `aucionhouse` (
  `id` int(11) NOT NULL,
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
  `DogiAtributeValue2` int(11) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `banlist`
--

CREATE TABLE `banlist` (
  `id` int(11) NOT NULL,
  `BanIp` varchar(50) CHARACTER SET utf8 COLLATE utf8_spanish2_ci NOT NULL,
  `Rason` varchar(160) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `bind`
--

CREATE TABLE `bind` (
  `id` int(10) NOT NULL,
  `CharacterID` int(10) NOT NULL,
  `WorldID` tinyint(3) NOT NULL,
  `BindObjectTblIdx` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cashitem`
--

CREATE TABLE `cashitem` (
  `id` int(11) UNSIGNED NOT NULL,
  `tblidx` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `byStackCount` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `Year` int(10) DEFAULT NULL,
  `Month` int(10) DEFAULT NULL,
  `Day` int(10) DEFAULT NULL,
  `Hour` int(10) DEFAULT NULL,
  `Minute` int(10) DEFAULT NULL,
  `Secound` int(10) DEFAULT NULL,
  `Handle` int(11) DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=FIXED;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `characters`
--

CREATE TABLE `characters` (
  `CharacterID` bigint(20) UNSIGNED NOT NULL,
  `AccountID` bigint(20) UNSIGNED NOT NULL,
  `GuildID` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `Name` varchar(20) NOT NULL,
  `ServerID` int(10) UNSIGNED NOT NULL,
  `RaceID` int(10) UNSIGNED NOT NULL,
  `ClassID` int(10) UNSIGNED NOT NULL,
  `GenderID` int(10) UNSIGNED NOT NULL,
  `FaceID` int(10) UNSIGNED NOT NULL,
  `HairID` int(10) UNSIGNED NOT NULL,
  `HairColorID` int(10) UNSIGNED NOT NULL,
  `SkinColorID` int(10) UNSIGNED NOT NULL,
  `CurrentLevel` int(10) UNSIGNED NOT NULL DEFAULT 70,
  `CurrentExp` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `MapInfoID` bigint(20) UNSIGNED NOT NULL DEFAULT 4294967295,
  `WorldTableID` bigint(20) UNSIGNED NOT NULL DEFAULT 1,
  `WorldID` bigint(20) UNSIGNED NOT NULL DEFAULT 1,
  `BindType` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `BindWorldID` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `BindObjectID` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `Position_X` float(11,6) NOT NULL DEFAULT 0.000000,
  `Position_Y` float(11,6) NOT NULL DEFAULT 0.000000,
  `Position_Z` float(11,6) NOT NULL DEFAULT 0.000000,
  `Direction_X` float(11,6) NOT NULL DEFAULT 0.000000,
  `Direction_Y` float(11,6) NOT NULL DEFAULT 0.000000,
  `Direction_Z` float(11,6) NOT NULL DEFAULT 0.000000,
  `ZennyInventory` bigint(20) NOT NULL DEFAULT 0,
  `ZennyBank` bigint(20) NOT NULL DEFAULT 0,
  `Token` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `WP_Point` int(10) DEFAULT 0,
  `CashPoint` int(10) DEFAULT 999999,
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
  `SkillPoints` int(10) UNSIGNED NOT NULL DEFAULT 69,
  `createdAt` varchar(20) DEFAULT NULL,
  `Title_Marking` int(10) NOT NULL DEFAULT 0,
  `IsVip` int(10) DEFAULT 0,
  `MixExp` int(10) NOT NULL DEFAULT 0,
  `deletionStartedAt` varchar(20) DEFAULT NULL,
  `MailIsAway` int(10) DEFAULT 0,
  `GSHandle` int(20) DEFAULT NULL,
  `WagguCoin` int(10) DEFAULT 9999,
  `EventCoin` int(10) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `characters_attributes`
--

CREATE TABLE `characters_attributes` (
  `ID` int(10) NOT NULL,
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
  `BaseMaxAp` int(5) DEFAULT 450000
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `charquestlist`
--

CREATE TABLE `charquestlist` (
  `pkQtTable` int(11) NOT NULL,
  `charId` int(10) DEFAULT NULL,
  `tid` int(100) DEFAULT NULL,
  `isCompleted` smallint(1) NOT NULL DEFAULT 0,
  `currentStep` int(255) NOT NULL DEFAULT 255,
  `type` smallint(1) DEFAULT NULL,
  `dwEventData` int(255) DEFAULT NULL,
  `nextStep` int(255) NOT NULL DEFAULT 2,
  `timeRemaing` int(15) NOT NULL DEFAULT 255
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `friendlist`
--

CREATE TABLE `friendlist` (
  `FriendID` bigint(20) UNSIGNED NOT NULL COMMENT 'Id of friend in the database',
  `OwnerID` bigint(20) UNSIGNED NOT NULL COMMENT 'CharID of the owner of the list friend',
  `CharID` bigint(10) NOT NULL COMMENT 'Id of the friend',
  `IsBlack` tinyint(1) DEFAULT 0 COMMENT 'is in the black list?'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `guilds`
--

CREATE TABLE `guilds` (
  `GuildID` int(5) NOT NULL,
  `GuildName` varchar(30) DEFAULT NULL,
  `GuildMasterName` varchar(30) DEFAULT NULL,
  `GuildMaster` int(10) DEFAULT NULL,
  `GuildSecondMaster` int(10) DEFAULT 0,
  `GuildNotice` varchar(256) DEFAULT NULL,
  `GuildReputation` int(10) DEFAULT 0,
  `GuildPointEver` int(10) DEFAULT 0,
  `GuildDisbandTime` datetime DEFAULT NULL,
  `GuildFunctions` int(15) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `guild_members`
--

CREATE TABLE `guild_members` (
  `id` int(10) NOT NULL,
  `GuildID` int(5) NOT NULL,
  `MemberID` int(10) NOT NULL,
  `MemberName` varchar(30) NOT NULL,
  `is_guildmaster` tinyint(1) DEFAULT 0,
  `is_secondguildmaster` tinyint(1) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `hoipoimix`
--

CREATE TABLE `hoipoimix` (
  `ID` int(10) NOT NULL,
  `CharID` int(11) DEFAULT 0,
  `RecipeID` int(11) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `itematributes`
--

CREATE TABLE `itematributes` (
  `id` int(11) UNSIGNED NOT NULL,
  `tblidx` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(11) UNSIGNED NOT NULL DEFAULT 0,
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
  `DogiAtributeValue2` int(11) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `items`
--

CREATE TABLE `items` (
  `id` int(11) UNSIGNED NOT NULL,
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
  `DogiAtributeValue2` int(11) DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=FIXED;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `mail`
--

CREATE TABLE `mail` (
  `id` int(10) NOT NULL,
  `CharacterID` int(11) DEFAULT NULL,
  `byDay` tinyint(2) DEFAULT NULL,
  `tCreateTime` int(50) DEFAULT NULL,
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
  `AtributeValue6` int(11) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `mascotinfo`
--

CREATE TABLE `mascotinfo` (
  `ID` int(10) NOT NULL,
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
  `Skill4` int(11) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `portals`
--

CREATE TABLE `portals` (
  `id` int(10) NOT NULL,
  `CharacterID` int(10) DEFAULT NULL,
  `PortalID` smallint(3) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `quickslot`
--

CREATE TABLE `quickslot` (
  `quickslotID` int(10) UNSIGNED NOT NULL COMMENT 'Quick Slot ID',
  `CharID` int(10) UNSIGNED NOT NULL COMMENT 'Char ID of player',
  `Tblidx` int(10) UNSIGNED NOT NULL COMMENT 'tblidx of item',
  `SlotID` int(3) UNSIGNED NOT NULL COMMENT 'slot id',
  `Type` int(3) UNSIGNED NOT NULL COMMENT 'type item'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `quickteleporter`
--

CREATE TABLE `quickteleporter` (
  `ID` int(10) NOT NULL,
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
  `MapTblidx` int(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `realmlist`
--

CREATE TABLE `realmlist` (
  `id` int(11) UNSIGNED NOT NULL,
  `ServerID` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `ChannelID` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `realmflags` tinyint(3) UNSIGNED NOT NULL DEFAULT 2,
  `population` float UNSIGNED NOT NULL DEFAULT 0,
  `IsEvent` int(11) DEFAULT 0,
  `Name` varchar(20) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Realm System' ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------
-- Registros de realmlist
-- ----------------------------
INSERT INTO `realmlist` VALUES (1, 1, 1, 0, 0, 0, null);
INSERT INTO `realmlist` VALUES (2, 2, 1, 0, 0, 0, null);
--
-- Estructura de tabla para la tabla `skills`
--

CREATE TABLE `skills` (
  `id` int(11) UNSIGNED NOT NULL,
  `skill_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(11) UNSIGNED NOT NULL,
  `RpBonusAuto` bit(1) DEFAULT b'0',
  `RpBonusType` int(5) UNSIGNED NOT NULL DEFAULT 0,
  `SlotID` smallint(3) UNSIGNED NOT NULL DEFAULT 0,
  `TimeRemaining` int(15) UNSIGNED NOT NULL DEFAULT 0,
  `Exp` int(5) UNSIGNED NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `titlelist`
--

CREATE TABLE `titlelist` (
  `id` int(10) NOT NULL,
  `CharacterID` int(10) DEFAULT NULL,
  `TitleID` int(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `warfoginfo`
--

CREATE TABLE `warfoginfo` (
  `idFog` int(11) NOT NULL,
  `hObject` int(11) NOT NULL,
  `owner_id` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `account`
--
ALTER TABLE `account`
  ADD PRIMARY KEY (`AccountID`) USING BTREE,
  ADD UNIQUE KEY `AccountID_UNIQUE` (`AccountID`) USING BTREE;

--
-- Indices de la tabla `aucionhouse`
--
ALTER TABLE `aucionhouse`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indices de la tabla `banlist`
--
ALTER TABLE `banlist`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indices de la tabla `bind`
--
ALTER TABLE `bind`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indices de la tabla `cashitem`
--
ALTER TABLE `cashitem`
  ADD PRIMARY KEY (`id`) USING BTREE,
  ADD KEY `owner_id_idx` (`owner_id`) USING BTREE,
  ADD KEY `item_vnum_index` (`tblidx`) USING BTREE;

--
-- Indices de la tabla `characters`
--
ALTER TABLE `characters`
  ADD PRIMARY KEY (`CharacterID`) USING BTREE,
  ADD UNIQUE KEY `CharacterID_UNIQUE` (`CharacterID`) USING BTREE,
  ADD UNIQUE KEY `Name_UNIQUE` (`Name`) USING BTREE;

--
-- Indices de la tabla `characters_attributes`
--
ALTER TABLE `characters_attributes`
  ADD PRIMARY KEY (`ID`) USING BTREE;

--
-- Indices de la tabla `charquestlist`
--
ALTER TABLE `charquestlist`
  ADD PRIMARY KEY (`pkQtTable`) USING BTREE;

--
-- Indices de la tabla `friendlist`
--
ALTER TABLE `friendlist`
  ADD PRIMARY KEY (`FriendID`) USING BTREE COMMENT 'Friend ID',
  ADD KEY `CharID` (`CharID`) USING BTREE,
  ADD KEY `friendlist_ibfk_1` (`OwnerID`) USING BTREE;

--
-- Indices de la tabla `guilds`
--
ALTER TABLE `guilds`
  ADD PRIMARY KEY (`GuildID`) USING BTREE;

--
-- Indices de la tabla `guild_members`
--
ALTER TABLE `guild_members`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indices de la tabla `hoipoimix`
--
ALTER TABLE `hoipoimix`
  ADD PRIMARY KEY (`ID`) USING BTREE;

--
-- Indices de la tabla `itematributes`
--
ALTER TABLE `itematributes`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indices de la tabla `items`
--
ALTER TABLE `items`
  ADD PRIMARY KEY (`id`) USING BTREE,
  ADD KEY `owner_id_idx` (`owner_id`) USING BTREE,
  ADD KEY `item_vnum_index` (`tblidx`) USING BTREE;

--
-- Indices de la tabla `mail`
--
ALTER TABLE `mail`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indices de la tabla `mascotinfo`
--
ALTER TABLE `mascotinfo`
  ADD PRIMARY KEY (`ID`) USING BTREE;

--
-- Indices de la tabla `portals`
--
ALTER TABLE `portals`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indices de la tabla `quickslot`
--
ALTER TABLE `quickslot`
  ADD PRIMARY KEY (`quickslotID`);

--
-- Indices de la tabla `quickteleporter`
--
ALTER TABLE `quickteleporter`
  ADD PRIMARY KEY (`ID`) USING BTREE;

--
-- Indices de la tabla `realmlist`
--
ALTER TABLE `realmlist`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indices de la tabla `skills`
--
ALTER TABLE `skills`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indices de la tabla `titlelist`
--
ALTER TABLE `titlelist`
  ADD PRIMARY KEY (`id`) USING BTREE;

--
-- Indices de la tabla `warfoginfo`
--
ALTER TABLE `warfoginfo`
  ADD PRIMARY KEY (`idFog`) USING BTREE;

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `account`
--
ALTER TABLE `account`
  MODIFY `AccountID` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `aucionhouse`
--
ALTER TABLE `aucionhouse`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `banlist`
--
ALTER TABLE `banlist`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `bind`
--
ALTER TABLE `bind`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `cashitem`
--
ALTER TABLE `cashitem`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `characters`
--
ALTER TABLE `characters`
  MODIFY `CharacterID` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `characters_attributes`
--
ALTER TABLE `characters_attributes`
  MODIFY `ID` int(10) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `charquestlist`
--
ALTER TABLE `charquestlist`
  MODIFY `pkQtTable` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `friendlist`
--
ALTER TABLE `friendlist`
  MODIFY `FriendID` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Id of friend in the database';

--
-- AUTO_INCREMENT de la tabla `guilds`
--
ALTER TABLE `guilds`
  MODIFY `GuildID` int(5) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `guild_members`
--
ALTER TABLE `guild_members`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `hoipoimix`
--
ALTER TABLE `hoipoimix`
  MODIFY `ID` int(10) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `itematributes`
--
ALTER TABLE `itematributes`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `items`
--
ALTER TABLE `items`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `mail`
--
ALTER TABLE `mail`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `mascotinfo`
--
ALTER TABLE `mascotinfo`
  MODIFY `ID` int(10) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `portals`
--
ALTER TABLE `portals`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `quickslot`
--
ALTER TABLE `quickslot`
  MODIFY `quickslotID` int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Quick Slot ID';

--
-- AUTO_INCREMENT de la tabla `quickteleporter`
--
ALTER TABLE `quickteleporter`
  MODIFY `ID` int(10) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `realmlist`
--
ALTER TABLE `realmlist`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `skills`
--
ALTER TABLE `skills`
  MODIFY `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `titlelist`
--
ALTER TABLE `titlelist`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `warfoginfo`
--
ALTER TABLE `warfoginfo`
  MODIFY `idFog` int(11) NOT NULL AUTO_INCREMENT;

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `friendlist`
--
ALTER TABLE `friendlist`
  ADD CONSTRAINT `friendlist_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `characters` (`CharacterID`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
