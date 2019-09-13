#ifndef _DEF
#define _DEF

#include "Base.h"
#include "NtlActionPattern.h"
#include "NtlAdmin.h"
#include "NtlAvatar.h"
#include "NtlBattle.h"
#include "NtlBBox.h"
#include "NtlBudokai.h"
#include "NtlCharacter.h"
#include "NtlCharacterState.h"
#include "NtlChat.h"
#include "NtlDirection.h"
#include "NtlDojo.h"
#include "NtlDragonBall.h"
#include "NtlFriend.h"
#include "NtlGuild.h"
#include "NtlHlsItem.h"
#include "NtlItem.h"
#include "NtlLine.h"
#include "NtlMail.h"
#include "NtlMatch.h"
#include "NtlMovement.h"
#include "NtlNetP.h"
#include "NtlObject.h"
#include "NtlParty.h"
#include "NtlPartyDungeon.h"
#include "NtlPet.h"
#include "NtlPetition.h"
#include "NtlQuest.h"
#include "NtlRandom.h"
#include "NtlRankBattle.h"
#include "NtlReport.h"
#include "../Shared/Source/Header/ResultCode.h"
#include "NtlRide.h"
#include "NtlServer.h"
#include "NtlService.h"
#include "NtlSharedBotSystemDef.h"
#include "NtlSharedDef.h"
#include "NtlSharedType.h"
#include "NtlSkill.h"
#include "NtlSphere.h"
#include "NtlSvrMath.h"
#include "NtlTeleport.h"
#include "NtlTimeQuest.h"
#include "NtlTLQ.h"
#include "NtlVector.h"
#include "NtlWorld.h"

static wchar_t* charToWChar(const char* text)
{
	size_t conv, size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs_s(&conv, wa, size, text, size);
	return wa;
}

#endif