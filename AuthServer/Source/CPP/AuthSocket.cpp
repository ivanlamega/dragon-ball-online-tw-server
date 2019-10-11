#include <AuthSocket.h>
#include <Logger.h>
#include <stdio.h>
#include <cstdio>
#include <Opcodes.h>
#include <Encryptation.h>
#include <mysqlconn_wrapper.h>
#include <Packet\Auth\PacketAU.h>
#include <XmlParser.h>
#include <string>
#include <IPHlpApi.h>

struct sUA_LOGIN_REQ
{
	WCHAR		awchUserId[MAX_SIZE_USERID_UNICODE + 1];
	WCHAR		awchPasswd[MAX_SIZE_USERPW_UNICODE + 1];
	DWORD		dwCodePage;
	WORD		wLVersion;
	WORD		wRVersion;
	BYTE		abyMacAddress[MAX_ADAPTER_ADDRESS_LENGTH + 1];
};

AuthSocket::AuthSocket(boost::asio::io_service &service, std::function<void(Socket *)> closeHandler)
	: Socket(service, closeHandler)
{
}
void AuthSocket::OnClosed()
{
	sLog.outDebug("Client disconnected: [%s]", m_address);
}
void AuthSocket::OnConnectionDone()
{
	uint8 rawData[] = { 0x06, 0x00, 0x03, 0x00, 0x30, 0x2C, 0x67, 0x4C };

	Write((char*)rawData, sizeof(rawData));
	memset(&rawData, 0, sizeof(rawData));
	sLog.outDebug("Client connected: [%s]", m_address);
}
bool AuthSocket::_ProcessLoginPacket(Packet& packet)
{
	if (packet.GetPacketHeader()->bySequence == Opcodes::UA_LOGIN_TW_REQ) // Get the login request data
	{
		bool val = _HandleOnLogin(packet);
		return val;
	}
	else if (packet.GetPacketHeader()->bySequence == Opcodes::UA_LOGIN_DISCONNECT_REQ)
	{
		sAU_LOGIN_DISCONNECT_RES res;
		memset(&res, 0, sizeof(sAU_LOGIN_DISCONNECT_RES));
		res.wPacketSize = 2;
		res.wOpCode = Opcodes::AU_LOGIN_DISCONNECT_RES;
		Write((char*)&res, sizeof(sAU_LOGIN_DISCONNECT_RES));
		res = {};
		return true;
	}
	return false;
}
bool AuthSocket::_HandleOnLogin(Packet& packet)
{
	sUA_LOGIN_REQ *req = (sUA_LOGIN_REQ*)packet.GetPacketData();
	char username[MAX_SIZE_USERID_UNICODE + 1];
	char password[MAX_SIZE_USERPW_UNICODE + 1];

	wcstombs(username, req->awchUserId, MAX_SIZE_USERID_UNICODE + 1);
	wcstombs(password, req->awchPasswd, MAX_SIZE_USERPW_UNICODE + 1);	

	sAU_LOGIN_RES res;
	memset(&res, 0, sizeof(sAU_LOGIN_RES));

	res.wPacketSize = sizeof(sAU_LOGIN_RES) - 2; // packet body size (packet size - header)
	res.wOpCode = Opcodes::AU_LOGIN_RES;

	int AccountID = sDB.GetAccountID(username, password);
	if (AccountID == -1)
	{
		res.wResultCode = AUTH_USER_NOT_FOUND;
		res.wPacketSize = sizeof(sSERVER_INFO); // remove unused struct size (9 because we need always 1 struct size to send)
		Write((char*)&res, sizeof(sAU_LOGIN_RES));
		res = {};
		return true;
	}
	if (sDB.Confirm_IP_MAC(AccountID, (char*)m_address.c_str()) != ResultCodes::AUTH_SUCCESS)
	{
		/// return an error to the client and send an email to ask for verification
	}

	res.wResultCode = sDB.ValidateLoginRequest(username, password, AccountID);
	if (res.wResultCode != AUTH_SUCCESS)
	{
		res.wPacketSize = sizeof(sSERVER_INFO); // remove unused struct size (9 because we need always 1 struct size to send)
		Write((char*)&res, sizeof(sAU_LOGIN_RES));
		res = {};
		return true;
	}
	sDB.UpdateAccountOnline(AccountID, 1); // SET OUR USER ONLINE IN DB
	int isGameMaster = sDB.GetIsGameMaster(AccountID);
	memcpy(res.awchUserId, req->awchUserId, MAX_SIZE_USERID_UNICODE + 1);
	memcpy(res.abyAuthKey, "SE@WASDE#$RFWD@D", MAX_SIZE_AUTH_KEY);
	res.AccountID = AccountID;
	res.lastChannelID = 7;
	res.lastServerID = sDB.GetLastServerID(AccountID);
	if (isGameMaster >= 1)
	{
		res.dev = 0xFFFFFFFF;
	}	
	else
		res.dev = 0;
	res.byServerInfoCount = sXmlParser.GetInt("CharServerList", "Count");
	int i = 0;
	for (i = 0; i < res.byServerInfoCount; ++i)
	{
		int srv = i + 1;
		std::string fieldName = "CharServer";
		fieldName.append(std::to_string(srv));

		std::string addr = sXmlParser.GetChildStr("CharServerList", (char*)fieldName.c_str(), "IP");
		int port = sXmlParser.GetChildInt("CharServerList", (char*)fieldName.c_str(), "Port");

		res.CharServerInfo[i].dwLoad = 9;
		memcpy(res.CharServerInfo[i].szCharacterServerIP, addr.c_str(), strlen(addr.c_str()));
		res.CharServerInfo[i].wCharacterServerPortForClient = port;
		res.CharServerInfo[i].unknow = 1;
	}
	res.wPacketSize = (res.wPacketSize - (sizeof(sSERVER_INFO) * (9 - i))); // remove unused struct size (9 because we need always 1 struct size to send)
	Write((char*)&res, sizeof(sAU_LOGIN_RES));
	res = {};

	sAU_COMMERCIAL_SETTING_NFY commercial;
	memset(&commercial, 255, sizeof(sAU_COMMERCIAL_SETTING_NFY));

	commercial.wPacketSize = sizeof(sAU_COMMERCIAL_SETTING_NFY) - 2;
	commercial.wOpCode = Opcodes::AU_COMMERCIAL_SETTING_NFY;
	commercial.unk[0] = 55;
	Write((char*)&commercial, sizeof(sAU_COMMERCIAL_SETTING_NFY));
	commercial = {};
	return true;
}
bool AuthSocket::ProcessIncomingData()
{
	while (ReadLengthRemaining() > 0)
	{
		size_t sizeInc = ReadLengthRemaining();
		Packet *pk = new Packet();
		pk->AttachData((BYTE*)InPeak(), sizeInc);
		PACKETDATA *header = (PACKETDATA*)InPeak();
		if ((pk->GetHeaderSize() < 4) || (pk->GetHeaderSize() > PACKET_MAX_SIZE))
		{
			sLog.outError("AuthSocket::ProcessIncomingData: client sent malformed packet size = %u", pk->GetHeaderSize());
			errno = EINVAL;
			return false;
		}
		/*
			///		 DECRYPT PACKET HERE ????		\\\
		*/
		sLog.outDebug("Received opcode: [%u] from: [%s]", header->wOpCode, m_address);
		bool process = false;
		if (header->wOpCode == 4)
		{
			uint8 rawData2[] = { 0x22, 0x00, 0x10, 0x00, 0x49, 0xD1, 0xF1, 0x1C, 0x6D, 0x58, 0xF9, 0xC5, 0x30, 0x26, 0xA4, 0x7B,
				0xB2, 0xD8, 0x2C, 0x86, 0x58, 0x60, 0x7B, 0xDD, 0xF0, 0x77, 0xCF, 0x25, 0x48, 0xB3, 0x65, 0x45,
				0x38, 0x80, 0x14, 0x72 };
			Write((char*)rawData2, sizeof(rawData2));
			memset(&rawData2, 0, sizeof(rawData2));
			process = true;
		}
		else if (header->wOpCode == Opcodes::SYS_ALIVE)
		{
			process = true;
		}
		
		else if (header->wOpCode >= Opcodes::UA_OPCODE_BEGIN && pk->GetPacketHeader()->bySequence <= Opcodes::UA_LOGIN_DISCONNECT_REQ)
		{
			process = _ProcessLoginPacket(*pk);
		}
		else
		{
			sLog.outError("Packet_[%u] Unknow", header->wOpCode);
			ReadSkip(sizeInc);
			delete pk;
			return false;
		}
		/// if we reach here, it means that a valid opcode was found and the handler completed successfully
		ReadSkip(sizeInc);
		delete pk;
		return process;
	}
	return true;
}