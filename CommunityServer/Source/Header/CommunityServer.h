#ifndef _COMMUNITYSERVER_H
#define _COMMUNITYSERVER_H

#pragma once

#include <Listener.h>
#include <Logger.h>
#include <CommunitySocket.h>

class CommunityServer
{
public:
	int Run();
private:
	Listener<CommunitySocket>	*network;
	int _ServerID;
	int _ChannelID;
	bool ConnectToDatabase();
	bool loadDataTable();
};
#define sCommunityServer AKCore::Singleton<CommunityServer>::Instance()

#endif