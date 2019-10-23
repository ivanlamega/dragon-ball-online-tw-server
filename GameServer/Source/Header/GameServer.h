#ifndef _GAMESERVER_H
#define _GAMESERVER_H

#pragma once

#include <Listener.h>
#include <Logger.h>
#include <GameSocket.h>

class CQuestWrapper;

class GameServer
{
public:
	CQuestWrapper			*g_pQuestWrapper;
	int Run();
	bool loadQuests();
private:
	Listener<GameSocket>	*network;
	int _ServerID;
	int _ChannelID;
	bool ConnectToDatabase();
	bool loadDataTable();
};
#define sGameServer AKCore::Singleton<GameServer>::Instance()

#endif