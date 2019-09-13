#ifndef _AUTHSERVER_H
# define _AUTHSERVER_H

#pragma once

#include <Listener.h>
#include <AuthSocket.h>
#include <Logger.h>

class AuthServer
{
public:
	AuthServer(int _port = 50200, int _workerThread = 1);
	~AuthServer();
	bool ConnectToDatabase();
	bool Start();
	void Ping();
private:
	Listener<AuthSocket>	*network;
	int port;
	int worker;
};

#endif