#include <CliRunnable.h>
#include <mysqlconn_wrapper.h>
#include <World.h>
#include <Logger.h>

#include <sstream>
#include <iostream>
#include <iterator>
#include <numeric>

#include <Util.h>

#define MAXCOMMAND		4
char *commandArray[MAXCOMMAND] =
{
	{".account create (username - password)"},
	{".population"},
	{".shutdown (duration in MS)"},
	{".announce (message)"}
};

void commandFinished(bool /*sucess*/)
{
	printf("\nAKCore>");
	fflush(stdout);
}

void SkipWhiteSpaces(char** args)
{
	if (!*args)
		return;
	while (isWhiteSpace(**args))
		++(*args);
}

bool HandleAccountCreateCommand(std::string& account_name, std::string& password)
{
	if (sDB.CreateAccount(account_name.c_str(), password.c_str()) != RESULT_SUCCESS)
		return false;
	return true;
}
bool HandleCommande(char* args)
{
	std::istringstream buf(args);
	std::istream_iterator<std::string> beg(buf), end;

	std::vector<std::string> tokens(beg, end); // done!

	if (tokens.size() >= 0)
	{
		std::string command = tokens[0];
		if (command == ".account")
		{
			if (tokens.size() < 4)
			{
				sLog.outError("Command prototype: .account create accountName accountPassword");
			}
			std::string value = tokens[1];
			if (value == "create")
			{
				if (HandleAccountCreateCommand(tokens[2], tokens[3]) == false)
				{
					sLog.outError("Account cannot be created, already exist.");
				}
				else
					sLog.outString("Account created");
			}
		}
		else if (command == ".population")
		{
			sLog.outString("Active session count: %d", sWorld.GetActiveSessionCount());
		}
		else if (command == ".shutdown")
		{
			if (tokens.size() < 3)
			{
				sLog.outError("Command prototype: .shutdown 1000 (duration in millisecond)");
			}
		}
		else if (command == ".help")
		{
			sLog.outString("Command available: ");
			for (int i = 0; i < MAXCOMMAND; i++)
			{
				sLog.outString("[%i]) %s", i, commandArray[i]);
			}
		}
		else if (command == ".announce")
		{
			if (tokens.size() < 2)
			{
				sLog.outError("Command prototype: .announce (message)");
			}
			else
			{
				std::string message;
				for (int i = 1; i < tokens.size(); i++)
					message.append(tokens[i] + " ");
				sWorld.SendAnnounce(message);
			}
		}
		else
		{
			sLog.outString("Unrecognize command, type .help to see available shell command");
		}
	}
	commandFinished(true);
	return true;
}
void utf8print(const char* str)
{
	/*wchar_t wtemp_buf[6000];
	size_t wtemp_len = 6000 - 1;
	if (!Utf8toWStr(str, strlen(str), wtemp_buf, wtemp_len))
		return;

	char temp_buf[6000];
	CharToOemBuffW(&wtemp_buf[0], &temp_buf[0], wtemp_len + 1);
	printf("%s", temp_buf);*/
}
/// %Thread start
void CliRunnable::run()
{
	char commandbuf[256];

	printf("AKCore>\n");
	///- As long as the World is running (no World::m_stopEvent), get the command line and handle it
	while (!World::IsStopped())
	{
		fflush(stdout);
		char* command_str = fgets(commandbuf, sizeof(commandbuf), stdin);
		if (command_str != nullptr)
		{
			for (int x = 0; command_str[x]; ++x)
				if (command_str[x] == '\r' || command_str[x] == '\n')
				{
					command_str[x] = 0;
					break;
				}
			if (!*command_str)
			{
				printf("AKCore>");
				continue;
			}
			std::string command;
			/*if (!consoleToUtf8(command_str, command))       // convert from console encoding to utf8
			{
				printf("origin>");
				continue;
			}*/
			//sWorld.QueueCliCommand(new CliCommandHolder(0, SEC_CONSOLE, command.c_str(), &utf8print, &commandFinished));
			HandleCommande(command_str);
		}
		else if (feof(stdin))
		{
			World::StopNow(SHUTDOWN_EXIT_CODE);
		}
	}
}
