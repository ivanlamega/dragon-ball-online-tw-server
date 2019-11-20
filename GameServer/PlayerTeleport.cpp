#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>

void WorldSession::SendCharTeleportRes(Packet& packet)
{
	sGU_CHAR_TELEPORT_RES Teleport;
	memset(&Teleport, 0, sizeof(sGU_CHAR_TELEPORT_RES));
	Teleport.wOpCode = GU_CHAR_TELEPORT_RES;
	Teleport.wPacketSize = sizeof(sGU_CHAR_TELEPORT_RES) - 2;
	Teleport.wResultCode = GAME_SUCCESS;
	Teleport.vNewLoc.x = 4474.109863;
	Teleport.vNewLoc.y = -42.000000;
	Teleport.vNewLoc.z = 3958.379883;
	Teleport.vNewDir.x = -0.751000;
	Teleport.vNewDir.y = 0;
	Teleport.vNewDir.z = -0.661000;
	Teleport.unk = INVALID_TBLIDX;
	Teleport.bIsToMoveAnotherServer = false;

	_player->Relocate(Teleport.vNewLoc.x, Teleport.vNewLoc.y, Teleport.vNewLoc.z, Teleport.vNewDir.x, Teleport.vNewDir.y, Teleport.vNewDir.z);
	_player->SetWorldID(1);
	_player->SetWorldTableID(1);
	_player->GetState()->sCharStateDetail.sCharStateTeleporting.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_NPC_PORTAL;
	_player->SetState(eCHARSTATE::CHARSTATE_TELEPORTING);
	SendPacket((char*)&Teleport, sizeof(sGU_CHAR_TELEPORT_RES));
}