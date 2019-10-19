#include <iostream>
#include <AuthServer.h>
#include <mysqlconn_wrapper.h>
#include <XmlParser2/XmlParser2.h>

AuthServer::AuthServer(int _port, int _workerThread) : port(_port), worker(_workerThread)
{
}
AuthServer::~AuthServer()
{
}
void AuthServer::Ping()
{
	sDB.Ping();
}
bool AuthServer::ConnectToDatabase()
{
	std::string user, password, host, db;

	user = sXmlParser.GetStr("MySQL", "User");
	password = sXmlParser.GetStr("MySQL", "Password");
	host = sXmlParser.GetStr("MySQL", "Host");
	db = sXmlParser.GetStr("MySQL", "Database");

	sDB.setInfos(user, password, host, db);
	if (sDB.connect() == false)
		return false;
	sDB.switchDb(db);
	sLog.outDetail("Database connection established.");
	return true;
}
bool AuthServer::Start()
{
	if (sXmlParser.loadFile("AuthServer") == false)
		return false;
	sLog.SetLogLevel((LogLevel)sXmlParser.GetInt("LogLevel", "Value"));
	if (ConnectToDatabase() == false)
	{
		sLog.outError("Database connection failed, exiting...");
		return false;
	}
	network = new Listener<AuthSocket>(sXmlParser.GetInt("Server", "Port"), sXmlParser.GetInt("ServerWorker", "Value"));
	sLog.outString("AuthServer: Listener started on port: [%d]", sXmlParser.GetInt("Server", "Port"));
	return true;
}