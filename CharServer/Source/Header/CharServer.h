#ifndef _CHARSERVER_H
#define _CHARSERVER_H

#pragma once

#include <Listener.h>
#include <Logger.h>
#include <CharSocket.h>

class CharServer
{
public:
	CharServer(int _port = 50300, int _workerThread = 1);
	~CharServer();
	bool Start();
	bool ConnectToDatabase();
	void Ping();
private:
	bool loadDataTable();

	Listener<CharSocket>	*network;
	int port;
	int worker;
};

#endif