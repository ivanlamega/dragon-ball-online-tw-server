#ifndef _GAMESERVER_H
#define _GAMESERVER_H

#pragma once

#include <Listener.h>
#include <Logger.h>
#include <GameSocket.h>

class GameServer
{
public:
	int Run();
private:
	Listener<GameSocket>	*network;
	int _ServerID;
	int _ChannelID;
	bool ConnectToDatabase();
	bool loadDataTable();
};
#define sGameServer AKCore::Singleton<GameServer>::Instance()

#endif