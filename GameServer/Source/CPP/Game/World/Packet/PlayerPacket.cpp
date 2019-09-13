#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>

//----------------------------------------
//	Add the new portal to our player
//----------------------------------------
void WorldSession::SendAddPortal(Packet& packet)
{
	sUG_PORTAL_ADD_REQ* req = (sUG_PORTAL_ADD_REQ *)packet.GetPacketBuffer();
	sGU_PORTAL_ADD_RES res;

	res.wOpCode = GU_PORTAL_ADD_RES;
	res.wPacketSize = sizeof(sGU_PORTAL_ADD_RES) - 2;

	PORTALID id = _player->GetPortalIdFromList(req->handle);
	printf("hey im at portal %d \n", id);
	if (id == 255)
		res.wResultCode = GAME_PORTAL_NOT_EXIST;
	else
	{
		sDB.AddNewPortal(_player->GetCharacterID(), id);
		res.wResultCode = GAME_SUCCESS;
	}
	res.hNpcHandle = req->handle;
	res.PortalID = id;
	SendPacket((char*)&res, sizeof(sGU_PORTAL_ADD_RES));
}
//----------------------------------------
//	Send the portal teleport response
//----------------------------------------
void WorldSession::SendPortalTeleport(Packet& packet)
{
	sUG_PORTAL_REQ* req = (sUG_PORTAL_REQ *)packet.GetPacketBuffer();
	sGU_PORTAL_RES res;
	sGU_CHAR_TELEPORT_RES teleport;

	/*	 NEED CHECK ZENNY HERE !!!	*/

	PortalTable *portal = sTBM.GetPortalTable();
	sPORTAL_TBLDAT *portalTbl = (sPORTAL_TBLDAT*)portal->FindData(req->byPoint + 1);
	sWORLD_TBLDAT *world = (sWORLD_TBLDAT*)sTBM.GetWorldTable()->FindData(portalTbl->worldId);

	res.wResultCode = GAME_SUCCESS;
	res.wOpCode = GU_PORTAL_RES;
	res.wPacketSize = sizeof(sGU_PORTAL_RES) - 2;

	teleport.wResultCode = GAME_SUCCESS;
	teleport.wOpCode = GU_CHAR_TELEPORT_RES;
	teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;

	if (world == NULL || portalTbl == NULL)
	{
		res.wResultCode = GAME_PORTAL_NOT_EXIST;
		SendPacket((char*)&res, sizeof(sGU_PORTAL_RES));
	}
	else
	{
		res.byPoint = req->byPoint + 1;
		res.hNpcHandle = req->handle;
		res.vDir = portalTbl->vDir;
		res.vLoc = portalTbl->vLoc;
		res.worldID = portalTbl->worldId;

		if (portalTbl->worldId != _player->GetWorldID())
		{
			teleport.bIsToMoveAnotherServer = true;
			teleport.sWorldInfo.worldID = portalTbl->worldId;
			teleport.sWorldInfo.tblidx = world->tblidx;
			teleport.sWorldInfo.sRuleInfo.byRuleType = world->byWorldRuleType;
			_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_WORLD_MOVE;
		}
		else
		{
			teleport.bIsToMoveAnotherServer = false;
		}

		teleport.vNewDir.x = portalTbl->vDir.x;
		teleport.vNewDir.y = portalTbl->vDir.y;
		teleport.vNewDir.z = portalTbl->vDir.z;
		teleport.vNewLoc.x = portalTbl->vLoc.x;
		teleport.vNewLoc.y = portalTbl->vLoc.y;
		teleport.vNewLoc.z = portalTbl->vLoc.z;
		
		_player->Relocate(res.vLoc.x, res.vLoc.y, res.vLoc.z, res.vDir.x, res.vDir.y, res.vDir.z);
		_player->SetWorldID(portalTbl->worldId);
		_player->SetWorldTableID(world->tblidx);

		_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING); 
		SendPacket((char*)&res, sizeof(sGU_PORTAL_RES));
		SendPacket((char*)&teleport, sizeof(sGU_CHAR_TELEPORT_RES));

		/*	   NOT SURE IF THIS IS A GOOD IDEA FOR NOW		*/
		Map* map = _player->GetMap();
		map->Remove(_player, false);
		_player->ClearListAndReference();
	}
}
//----------------------------------------
//	Build spawn packet
//----------------------------------------
void Player::BuildPacketForNewPlayer(Player& plr)
{
	SpawnPlayer PC;

	plr.BuildPacketForSpawn(PC);
	SendPacket((char*)&PC, sizeof(SpawnPlayer));
}
//----------------------------------------
//	Create the packet for spawn the player X
//----------------------------------------
void Player::BuildPacketForSpawn(SpawnPlayer& PC)
{
	memset(&PC, INVALID_TBLIDX, sizeof(SpawnPlayer));

	PC.wOpCode = GU_OBJECT_CREATE;
	PC.wPacketSize = sizeof(SpawnPlayer) - 2;

	wcscpy_s(PC.Name, MAX_SIZE_CHAR_NAME_UNICODE, charToWChar(GetName().c_str()));
	wcscpy_s(PC.GuildName, MAX_SIZE_GUILD_NAME_IN_UNICODE, charToWChar(GetGuildName().c_str()));

	for (int i = 0; i < MAX_EQUIP_ITEM_SLOT; i++)
	{
		PC.sItemBrief[i].tblidx = GetCharEquippedItems()[i].tblidx;
		PC.sItemBrief[i].byRank = GetCharEquippedItems()[i].byRank;
		PC.sItemBrief[i].byGrade = GetCharEquippedItems()[i].byGrade;
		PC.sItemBrief[i].byBattleAttribute = GetCharEquippedItems()[i].byBattleAttribute;
	}

	PC.fSkillSpeed = GetPcProfile()->avatarAttribute.SkillSpeed;

	for (int i = 0; i < 3; i++) { PC.test[i] = 0; }
	
	PC.Handle = GetHandle();
	PC.Type = OBJTYPE_PC;
	PC.Tblidx = GetPcProfile()->tblidx;
	PC.Adult = GetPcProfile()->bIsAdult;
	PC.appear.Face = GetPcProfile()->sPcShape.byFace;
	PC.appear.Hair = GetPcProfile()->sPcShape.byHair;
	PC.appear.HairColor = GetPcProfile()->sPcShape.byHairColor;
	PC.appear.SkinColor = GetPcProfile()->sPcShape.bySkinColor;
	PC.curLP = GetPcProfile()->dwCurLP;
	PC.maxLP = GetPcProfile()->avatarAttribute.wBaseMaxLP;
	PC.curEP = GetPcProfile()->wCurEP;
	PC.maxEP = GetPcProfile()->avatarAttribute.wBaseMaxEP;
	PC.level = GetPcProfile()->byLevel;
	PC.Size = 10;
	PC.sMarking.dwCode = GetPcProfile()->sMarking.dwCode;
	PC.mascotID = 0xffffffff; //6000071 puerh (yamcha) // 6000056 green egg
	PC.WorkshopAligment = 0;
	PC.byMarkInColor = 0;
	PC.byMarkInLine = 0;
	PC.byMarkMain = 0;
	PC.byMarkMainColor = 0;
	PC.byMarkOutColor = 0;
	PC.byMarkOutLine = 0;
	PC.guildId = GetPcProfile()->guildId;
	PC.byType = INVALID_TBLIDX;
	PC.byGuildColor = 0;
	PC.byDojoColor = 0;
	PC.fBaseRunSpeed = GetPcProfile()->avatarAttribute.fBaseRunSpeed;
	PC.fLastRunSpeed = GetPcProfile()->avatarAttribute.fLastRunSpeed;
	PC.fBaseAirSpeed = GetPcProfile()->avatarAttribute.fBaseAirSpeed;
	PC.fLastAirSpeed = GetPcProfile()->avatarAttribute.fLastAirSpeed;
	PC.fBaseAirDashSpeed = GetPcProfile()->avatarAttribute.fBaseAirDashSpeed;
	PC.fLastAirDashSpeed = GetPcProfile()->avatarAttribute.fLastAirDashSpeed;
	PC.fBaseAirDash2Speed = GetPcProfile()->avatarAttribute.fBaseAirDash2Speed;
	PC.fLastAirDash2Speed = GetPcProfile()->avatarAttribute.fLastAirDash2Speed;
	PC.wBaseAttackSpeedRate = GetPcProfile()->avatarAttribute.wBaseAttackSpeedRate;
	PC.bEmergency = GetIsEmergency();

	PC.bleeding = 255;
	PC.burn = 255;
	PC.poison = 255;
	PC.stomachace = 255;
	PC.confuse = 255;

	memcpy(&PC.State.sCharStateBase, &GetState()->sCharStateBase, sizeof(sCHARSTATE_BASE));
	memcpy(&PC.State.sCharStateDetail, &GetState()->sCharStateDetail, sizeof(sCHARSTATE_DETAIL));
}