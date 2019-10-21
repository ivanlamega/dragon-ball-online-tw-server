#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser2/XmlParser2.h>

//----------------------------------------
//	Sync the correct sate of our character
//----------------------------------------
void WorldSession::SendCharMoveSync(Packet& packet)
{
	sUG_CHAR_AIR_MOVE_SYNC *req = (sUG_CHAR_AIR_MOVE_SYNC*)packet.GetPacketBuffer();
	sGU_CHAR_AIR_MOVE_SYNC res;

	res.handle = _player->GetHandle();
	res.pos_move = req->vCurLoc;
	res.dir_move = req->vCurDir;
	res.byMoveDirection = req->byMoveDirection;
	res.wOpCode = GU_CHAR_AIR_MOVE_SYNC;
	res.wPacketSize = sizeof(sGU_CHAR_AIR_MOVE_SYNC) - 2;
	_player->Relocate(dbo_move_pos_to_float(req->vCurLoc.x), dbo_move_pos_to_float(req->vCurLoc.y), dbo_move_pos_to_float(req->vCurLoc.z));
	_player->SetOrientation(DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.x), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.y), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.z));
	_player->SetMoveDirection(req->byMoveDirection);	
	
	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_AIR_MOVE_SYNC));
}
//----------------------------------------
//	Sit or not
//----------------------------------------
void WorldSession::SendCharToggleSitDown(Packet& packet)
{
	sUG_CHAR_TOGG_SITDOWN *req = (sUG_CHAR_TOGG_SITDOWN*)packet.GetPacketBuffer();

	if (req->bSitDown == true)
		_player->SetState(eCHARSTATE::CHARSTATE_SITTING);
	else
		_player->SetState(eCHARSTATE::CHARSTATE_STANDING);

}
//----------------------------------------
//	Interpret right mouse click
//----------------------------------------
void WorldSession::SendCharHeadChanging(Packet& packet)
{
	sUG_CHAR_CHANGE_HEADING *req = (sUG_CHAR_CHANGE_HEADING*)packet.GetPacketBuffer();
	sGU_CHAR_CHANGE_HEADING res;

	res.wOpCode = GU_CHAR_CHANGE_HEADING;
	res.wPacketSize = sizeof(sGU_CHAR_CHANGE_HEADING) - 2;

	res.dir_move = req->dir_move;
	res.handle = _player->GetHandle();
	_player->SetOrientation(DBO_MOVE_DIR_TO_FLOAT(req->dir_move.x), DBO_MOVE_DIR_TO_FLOAT(req->dir_move.y), DBO_MOVE_DIR_TO_FLOAT(req->dir_move.z));

	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_CHANGE_HEADING));

}
//----------------------------------------
//	Click to move
//----------------------------------------
void WorldSession::SendCharDestLoc(Packet& packet)
{
	sUG_CHAR_DEST_MOVE* req = (sUG_CHAR_DEST_MOVE*)packet.GetPacketBuffer();
	sGU_CHAR_DEST_MOVE res;
	memset(&res, 0, sizeof(sGU_CHAR_DEST_MOVE));

	res.wOpCode = GU_CHAR_DEST_MOVE;
	res.byMoveFlag = NTL_MOVE_MOUSE_MOVEMENT;
	res.wPacketSize = sizeof(sGU_CHAR_DEST_MOVE) - 2;

	res.handle = _player->GetHandle();
	res.byDestLocCount = 1;
	res.bHaveSecondDestLoc = true;

	res.vCurLoc = req->CurLoc;
	res.avDestLoc[0] = req->DestLoc;
	res.unknown = 0;
	sVECTOR3 v3pos;
	v3pos.x = dbo_move_pos_to_float(req->DestLoc.x);
	v3pos.y = dbo_move_pos_to_float(req->DestLoc.y);
	v3pos.z = dbo_move_pos_to_float(req->DestLoc.z);
	dVECTOR3 dPos;
	//printf("Char Dest Positions        : x%d y%d z%d\n\r", req->DestLoc.x, req->DestLoc.y, req->DestLoc.z);
	//printf("Char Dest positions float  : x%f y%f z%f \n\r", dbo_move_pos_to_float(req->DestLoc.x), dbo_move_pos_to_float(req->DestLoc.y), dbo_move_pos_to_float(req->DestLoc.z));
	//printf("Char Dest back to int32    : x%d y%d z%d \n\r", dbo_move_float_to_pos(v3pos.x), dbo_move_float_to_pos(v3pos.y), dbo_move_float_to_pos(v3pos.z));
	dPos.x = dbo_move_float_to_pos(v3pos.x);
	dPos.y = dbo_move_float_to_pos(v3pos.y);
	dPos.z = dbo_move_float_to_pos(v3pos.z);
	//printf("Char Dest back to float    : x%f y%f z%f \n\r", dbo_move_pos_to_float(dPos.x), dbo_move_pos_to_float(dPos.y), dbo_move_pos_to_float(dPos.z));
/*	_player->GetState()->sCharStateDetail.sCharStateDestMove.dwTimeStamp = 0x01;
	_player->GetState()->sCharStateDetail.sCharStateDestMove.byMoveFlag = res.byMoveFlag;
	_player->GetState()->sCharStateDetail.sCharStateDestMove.vSecondDestLoc = res.vSecondDestLoc;
//	_player->GetState()->sCharStateDetail.sCharStateDestMove.unknown = INVALID_BYTE;
	_player->GetState()->sCharStateDetail.sCharStateDestMove.byDestLocCount = res.byDestLocCount;
	_player->GetState()->sCharStateDetail.sCharStateDestMove.avDestLoc[0] = res.avDestLoc[0];
	
	_player->SetState(eCHARSTATE::CHARSTATE_DESTMOVE);*/
	
	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_DEST_MOVE));
}
//----------------------------------------
//	Interpret movement
//----------------------------------------
void WorldSession::SendCharMove(Packet& packet)
{
	sUG_CHAR_MOVE *req = (sUG_CHAR_MOVE*)packet.GetPacketBuffer();
	sGU_CHAR_MOVE res;

	res.wOpCode = GU_CHAR_MOVE;
	res.wPacketSize = sizeof(sGU_CHAR_MOVE) - 2;

	res.handle = _player->GetHandle();
	res.pos_move = req->vCurLoc;
	res.dir_move = req->vCurDir;
	res.move_type = req->move_type;
	res.move_flag = NTL_MOVE_KEYBOARD_FIRST;
	//--------------------------------
	// CHECK SPEED HACK
	//--------------------------------
	// check distance between received pos and server pos should get a distance around 20 with the acceptence.
	// here
	//
	_player->Relocate(dbo_move_pos_to_float(req->vCurLoc.x), dbo_move_pos_to_float(req->vCurLoc.y), dbo_move_pos_to_float(req->vCurLoc.z));
	_player->SetOrientation(DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.x), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.y), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.z));
	_player->SetMoveDirection(req->move_type);
	if (res.move_type == 0)
	{
		_player->SetState(eCHARSTATE::CHARSTATE_STANDING);
	}
	else
	{
		_player->GetState()->sCharStateDetail.sCharStateMoving.byMoveFlag = NTL_MOVE_KEYBOARD_FIRST;
		_player->GetState()->sCharStateDetail.sCharStateMoving.dwTimeStamp = 0x01;
		_player->GetState()->sCharStateDetail.sCharStateMoving.byMoveDirection = req->move_type;
		_player->SetState(eCHARSTATE::CHARSTATE_MOVING);
		
		
	}
	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_MOVE));
}
//----------------------------------------
//	Get jump information and send it back (need fix when moving)
//----------------------------------------
void WorldSession::SendCharJumpEnd(Packet& packet)
{
	sGU_CHAR_JUMP_END res;

	res.handle = _player->GetHandle();
	res.wOpCode = GU_CHAR_JUMP_END;
	res.wPacketSize = sizeof(sGU_CHAR_JUMP_END) - 2;

	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_JUMP_END));
}
//----------------------------------------
//	Perform jump
//----------------------------------------
void WorldSession::SendCharJump(Packet& packet)
{
	sUG_CHAR_JUMP *req = (sUG_CHAR_JUMP*)packet.GetPacketBuffer();
	sGU_CHAR_JUMP res;

	res.handle = _player->GetHandle();
	res.wPacketSize = sizeof(sGU_CHAR_JUMP) - 2;
	res.wOpCode = GU_CHAR_JUMP;

	res.jumpDir.x = req->jumpDirection.x;
	res.jumpDir.y = req->jumpDirection.y;
	res.jumpDir.z = req->jumpDirection.z;
	
	res.vDir.x = req->jumpDirection.x;
	res.vDir.y = req->jumpDirection.y;
	res.vDir.z = req->jumpDirection.z;

	res.vPos.x = req->jumpLocation.x;
	res.vPos.y = req->jumpLocation.y;
	res.vPos.z = req->jumpLocation.z;

	res.unknown = _player->GetMoveDirection();
	
	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_JUMP));

}
//----------------------------------------
//	Follow a target
//	/!\ NOT WORKING	/!\
//----------------------------------------
void WorldSession::SendCharFollowMove(Packet& packet)
{
	sUG_CHAR_FOLLOW_MOVE * req = (sUG_CHAR_FOLLOW_MOVE*)packet.GetPacketBuffer();
	sGU_CHAR_FOLLOW_MOVE res;

	if (req->hTarget != _player->GetTarget())
		_player->SetTarget(req->hTarget);

	res.wOpCode = GU_CHAR_FOLLOW_MOVE;
	res.handle = _player->GetHandle();
	res.hTarget = _player->GetTarget();
	res.fDistance = req->fDistance;
	res.byMovementReason = req->byMovementReason;
	res.byMoveFlag = NTL_MOVE_FLAG_RUN;
	res.wPacketSize = sizeof(sGU_CHAR_FOLLOW_MOVE) - 2;	
	if (_player->cur_obj_tagert != NULL)
	{
		_player->SetMoveDestinationLocation(_player->cur_obj_tagert->GetVectorPosition());
	}
	else
		return;

	_player->GetState()->sCharStateDetail.sCharStateFollwing.byMoveFlag = res.byMoveFlag;
	_player->GetState()->sCharStateDetail.sCharStateFollwing.byMovementReason = req->byMovementReason;
	_player->GetState()->sCharStateDetail.sCharStateFollwing.fDistance = res.fDistance;
	_player->GetState()->sCharStateDetail.sCharStateFollwing.hTarget = req->hTarget;
	_player->SetState(eCHARSTATE::CHARSTATE_FOLLOWING);
	
	SendPacket((char*)&res, sizeof(sGU_CHAR_FOLLOW_MOVE));
	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_FOLLOW_MOVE));
}
//----------------------------------------
//	Sync data from our move
//	/!\ NOT WORKING	/!\
//----------------------------------------
void WorldSession::SendCharSyncFollow(Packet& packet)
{
	sUG_CHAR_FOLLOW_MOVE_SYNC * req = (sUG_CHAR_FOLLOW_MOVE_SYNC*)packet.GetPacketBuffer();
	sGU_CHAR_FOLLOW_MOVE res;

	if (req->hTarget != _player->GetTarget())
		_player->SetTarget(req->hTarget);
	res.byMoveFlag = NTL_MOVE_FLAG_RUN;
	res.byMovementReason = 0;
	if (_player->cur_obj_tagert != NULL)
	{
		res.fDistance = NtlGetDistance(_player->GetVectorPosition().x, _player->GetVectorPosition().z, _player->cur_obj_tagert->GetVectorPosition().x, _player->cur_obj_tagert->GetVectorPosition().z);
	}
	else
		res.fDistance = 0;
	res.handle = _player->GetHandle();
	res.hTarget = _player->GetTarget();
	res.wOpCode = GU_CHAR_FOLLOW_MOVE;
	res.wPacketSize = sizeof(sGU_CHAR_FOLLOW_MOVE) - 2;

	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_FOLLOW_MOVE));
}

void WorldSession::SendAirJumpMove(Packet & packet)
{
	sUG_CHAR_AIR_JUMP* req = (sUG_CHAR_AIR_JUMP*)packet.GetPacketBuffer();

	sGU_CHAR_MOVE res;

	res.wOpCode = GU_CHAR_MOVE;
	res.wPacketSize = sizeof(sGU_CHAR_MOVE) - 2;

	res.handle = _player->GetHandle();
	res.pos_move = req->vCurLoc;
	res.dir_move = req->vCurDir;
	res.move_type = req->move_type;
	res.move_flag = NTL_MOVE_KEYBOARD_FIRST;
	//--------------------------------
	// CHECK SPEED HACK
	//--------------------------------
	// check distance between received pos and server pos should get a distance around 20 with the acceptence.
	// here
	//
	_player->Relocate(dbo_move_pos_to_float(req->vCurLoc.x), dbo_move_pos_to_float(req->vCurLoc.y), dbo_move_pos_to_float(req->vCurLoc.z));
	_player->SetOrientation(DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.x), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.y), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.z));
	_player->SetMoveDirection(req->move_type);
	//printf("Moviment Type %d \n", res.move_type);
	sGU_UPDATE_CHAR_STATE res1;

	res1.wOpCode = GU_UPDATE_CHAR_STATE;
	res1.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;

	res1.handle = _player->GetHandle();
	res1.sCharState.sCharStateBase.vCurLoc.x = req->vCurLoc.x;
	res1.sCharState.sCharStateBase.vCurLoc.y = req->vCurLoc.y;
	res1.sCharState.sCharStateBase.vCurLoc.z = req->vCurLoc.z;
	res1.sCharState.sCharStateBase.vCurDir.x = req->vCurDir.x;
	res1.sCharState.sCharStateBase.vCurDir.y = req->vCurDir.y;
	res1.sCharState.sCharStateBase.vCurDir.z = req->vCurDir.z;
	res1.sCharState.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
	res1.sCharState.sCharStateBase.dwConditionFlag = _player->GetState()->sCharStateBase.dwConditionFlag;
	res1.sCharState.sCharStateBase.dwStateTime = 0;
	if (res.move_type == 0)
	{
		res1.sCharState.sCharStateBase.byStateID = _player->GetState()->sCharStateBase.byStateID = CHARSTATE_STANDING;
	}
	else
	{
		res1.sCharState.sCharStateBase.byStateID = _player->GetState()->sCharStateBase.byStateID = CHARSTATE_AIR_JUMP;
		res1.sCharState.sCharStateDetail.sCharStateAirJump.byMoveFlag = NTL_MOVE_KEYBOARD_FIRST;
		res1.sCharState.sCharStateDetail.sCharStateAirJump.dwTimeStamp = 0x01;
		res1.sCharState.sCharStateDetail.sCharStateAirJump.byMoveDirection = req->move_type;
		res1.sCharState.sCharStateBase.isFlying = _player->GetState()->sCharStateBase.isFlying = true;
	}
	_player->GetState()->sCharStateBase.isFlying = true;
	_player->SetFlying(true);

	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_MOVE));
	_player->SendToPlayerList((char*)&res1, sizeof(sGU_UPDATE_CHAR_STATE));
	SendPacket((char*)&res1, sizeof(sGU_UPDATE_CHAR_STATE));
}

void WorldSession::SendAirJMove(Packet & packet)
{
	sUG_CHAR_AIR_MOVE* req = (sUG_CHAR_AIR_MOVE*)packet.GetPacketBuffer();
	sGU_CHAR_MOVE res;

	res.wOpCode = GU_CHAR_MOVE;
	res.wPacketSize = sizeof(sGU_CHAR_MOVE) - 2;

	res.handle = _player->GetHandle();
	res.pos_move = req->vCurLoc;
	res.dir_move = req->vCurDir;
	res.move_type = req->move_type;
	res.move_flag = NTL_MOVE_KEYBOARD_FIRST;
	//--------------------------------
	// CHECK SPEED HACK
	//--------------------------------
	// check distance between received pos and server pos should get a distance around 20 with the acceptence.
	// here
	//
	_player->Relocate(dbo_move_pos_to_float(req->vCurLoc.x), dbo_move_pos_to_float(req->vCurLoc.y), dbo_move_pos_to_float(req->vCurLoc.z));
	_player->SetOrientation(DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.x), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.y), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.z));
	_player->SetMoveDirection(req->move_type);
	//printf("Moviment Type %d \n", res.move_type);
	if (res.move_type == 0)
	{
		_player->SetState(eCHARSTATE::CHARSTATE_STANDING);
	}
	else
	{
		_player->GetState()->sCharStateDetail.sCharStateMoving.byMoveFlag = NTL_MOVE_KEYBOARD_FIRST;
		_player->GetState()->sCharStateDetail.sCharStateMoving.dwTimeStamp = 0x01;
		_player->GetState()->sCharStateDetail.sCharStateMoving.byMoveDirection = req->move_type;
		_player->SetState(eCHARSTATE::CHARSTATE_MOVING);

	}
	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_MOVE));
}

void WorldSession::SendAirDashMove(Packet & packet)
{
	sUG_CHAR_AIR_DASH* req = (sUG_CHAR_AIR_DASH*)packet.GetPacketBuffer();

	sGU_CHAR_MOVE res;

	res.wOpCode = GU_CHAR_MOVE;
	res.wPacketSize = sizeof(sGU_CHAR_MOVE) - 2;

	res.handle = _player->GetHandle();
	res.pos_move = req->vCurLoc;
	res.dir_move = req->vCurDir;
	res.move_type = req->move_type;
	res.move_flag = NTL_MOVE_KEYBOARD_FIRST;
	//--------------------------------
	// CHECK SPEED HACK
	//--------------------------------
	// check distance between received pos and server pos should get a distance around 20 with the acceptence.
	// here
	//
	_player->Relocate(dbo_move_pos_to_float(req->vCurLoc.x), dbo_move_pos_to_float(req->vCurLoc.y), dbo_move_pos_to_float(req->vCurLoc.z));
	_player->SetOrientation(DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.x), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.y), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.z));
	_player->SetMoveDirection(req->move_type);
	sGU_UPDATE_CHAR_STATE res1;

	res1.wOpCode = GU_UPDATE_CHAR_STATE;
	res1.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;

	res1.handle = _player->GetHandle();
	res1.sCharState.sCharStateBase.vCurLoc.x = req->vCurLoc.x;
	res1.sCharState.sCharStateBase.vCurLoc.y = req->vCurLoc.y;
	res1.sCharState.sCharStateBase.vCurLoc.z = req->vCurLoc.z;
	res1.sCharState.sCharStateBase.vCurDir.x = req->vCurDir.x;
	res1.sCharState.sCharStateBase.vCurDir.y = req->vCurDir.y;
	res1.sCharState.sCharStateBase.vCurDir.z = req->vCurDir.z;
	res1.sCharState.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
	res1.sCharState.sCharStateBase.dwConditionFlag = _player->GetState()->sCharStateBase.dwConditionFlag;
	res1.sCharState.sCharStateBase.dwStateTime = 0;
	if (res.move_type == 0)
	{
		res1.sCharState.sCharStateBase.byStateID = _player->GetState()->sCharStateBase.byStateID = CHARSTATE_STANDING;
	}
	else
	{
		_player->GetState()->sCharStateBase.byStateID = CHARSTATE_AIR_DASH_ACCEL;
		res1.sCharState.sCharStateBase.byStateID = CHARSTATE_AIR_DASH_ACCEL;
		res1.sCharState.sCharStateDetail.sCharStateAirDashAccel.byMoveDirection = _player->GetState()->sCharStateDetail.sCharStateAirDashAccel.byMoveDirection = req->move_type;
		res1.sCharState.sCharStateBase.isFlying = _player->GetState()->sCharStateBase.isFlying = true;

	}

	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_MOVE));
	SendPacket((char*)&res1, sizeof(sGU_UPDATE_CHAR_STATE));
	_player->SendToPlayerList((char*)&res1, sizeof(sGU_UPDATE_CHAR_STATE));
}

void WorldSession::SendAirFalling(Packet & packet)
{
	sUG_CHAR_AIR_FALLING* req = (sUG_CHAR_AIR_FALLING*)packet.GetPacketBuffer();

	sGU_CHAR_MOVE res;

	res.wOpCode = GU_CHAR_MOVE;
	res.wPacketSize = sizeof(sGU_CHAR_MOVE) - 2;

	res.handle = _player->GetHandle();
	res.pos_move = req->vCurLoc;
	res.dir_move = req->vCurDir;
	res.move_type = req->move_type;
	res.move_flag = NTL_MOVE_KEYBOARD_FIRST;
	//--------------------------------
	// CHECK SPEED HACK
	//--------------------------------
	// check distance between received pos and server pos should get a distance around 20 with the acceptence.
	// here
	//
	_player->Relocate(dbo_move_pos_to_float(req->vCurLoc.x), dbo_move_pos_to_float(req->vCurLoc.y), dbo_move_pos_to_float(req->vCurLoc.z));
	_player->SetOrientation(DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.x), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.y), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.z));
	_player->SetMoveDirection(req->move_type);
	//printf("Moviment Type %d \n", res.move_type);
	if (res.move_type == 0)
	{
		_player->SetState(eCHARSTATE::CHARSTATE_STANDING);
	}
	else
	{
		_player->GetState()->sCharStateDetail.sCharStateFalling.dwTimeStamp = 0x01;
		_player->GetState()->sCharStateDetail.sCharStateFalling.byMoveDirection = req->move_type;
		_player->SetState(eCHARSTATE::CHARSTATE_FALLING);

	}

	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_MOVE));
}

void WorldSession::SendAirEnd(Packet & packet)
{
	sUG_CHAR_AIR_END* req = (sUG_CHAR_AIR_END*)packet.GetPacketBuffer();

	sGU_CHAR_MOVE res;

	res.wOpCode = GU_CHAR_MOVE;
	res.wPacketSize = sizeof(sGU_CHAR_MOVE) - 2;

	res.handle = _player->GetHandle();
	res.pos_move = req->vCurLoc;
	res.dir_move = req->vCurDir;
	res.move_type = 0;
	res.move_flag = NTL_MOVE_KEYBOARD_FIRST;
	//--------------------------------
	// CHECK SPEED HACK
	//--------------------------------
	// check distance between received pos and server pos should get a distance around 20 with the acceptence.
	// here
	//
	_player->Relocate(dbo_move_pos_to_float(req->vCurLoc.x), dbo_move_pos_to_float(req->vCurLoc.y), dbo_move_pos_to_float(req->vCurLoc.z));
	_player->SetOrientation(DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.x), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.y), DBO_MOVE_DIR_TO_FLOAT(req->vCurDir.z));
	_player->SetMoveDirection(0);

	_player->GetState()->sCharStateBase.isFlying = false;
	_player->SetFlying(false);
	_player->SetState(eCHARSTATE::CHARSTATE_STANDING);

	_player->SendToPlayerList((char*)&res, sizeof(sGU_CHAR_MOVE));
}
