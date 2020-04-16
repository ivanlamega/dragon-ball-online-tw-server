#include <Logger.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <cstdarg>
#include <time.h>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <Packet.h>
#include <iomanip>
void Log::SetLogLevel(int _level)
{
	int newLevel = _level;
	if (newLevel < LOG_LVL_MINIMAL)
		newLevel = LOG_LVL_MINIMAL;
	else if (newLevel > LOG_LVL_DEBUG)
		newLevel = LOG_LVL_DEBUG;

	logLevel = LogLevel(newLevel);
}
void Log::outTime()
{
	time_t rawtime;
	struct tm * timeinfo = new struct tm;
	char buffer[80];
	time(&rawtime);
	localtime_s(timeinfo, &rawtime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%m:%S", timeinfo);
	std::string str(buffer);
	std::cout << white << "[" << str.c_str() << "] " << white;
	delete timeinfo;
}
void Log::outString()
{
	printf("\n");
	fflush(stdout);
}
void Log::outString(const char* str, ...)
{
	if (!str)
		return;
	outTime();
	std::cout << white << "[INFO]: " << white;
	va_list ap;

	va_start(ap, str);
	vprintf(str, ap);
	va_end(ap);

	printf("\n");
	fflush(stdout);
}
void Log::outBasic(const char* str, ...)
{
	if (logLevel >= LOG_LVL_BASIC)
	{
		if (!str)
			return;

		va_list ap;
		outTime();
		std::cout << green << "[BASIC]: " << white;
		va_start(ap, str);
		vprintf(str, ap);
		va_end(ap);
		printf("\n");
		fflush(stdout);
	}
}
void Log::outError(const char* err, ...)
{
	if (!err)
		return;

	va_list ap;
	outTime();
	std::cout << red << "[ERROR]: " << white;
	va_start(ap, err);
	vprintf(err, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	fflush(stderr);
}
void Log::outDetail(const char* str, ...)
{
	if (logLevel >= LOG_LVL_DETAIL)
	{
		if (!str)
			return;

		va_list ap;
		outTime();
		std::cout << yellow << "[DETAIL]: " << white;
		va_start(ap, str);
		vprintf(str, ap);
		va_end(ap);
		printf("\n");
		fflush(stdout);
	}
}
void Log::outDebug(const char* str, ...)
{
	if (logLevel >= LOG_LVL_DEBUG)
	{
		if (!str)
			return;

		va_list ap;
		outTime();
		std::cout << blue << "[DEBUG]: " << white;
		va_start(ap, str);
		vprintf(str, ap);
		va_end(ap);
		printf("\n");
		fflush(stdout);
	}
}
void Log::outPacketDebugger(Packet* paquet)
{
	if (logLevel >= LOG_LVL_DEBUG)
	{
		if (paquet == nullptr)
		{
			sLog.outError("Packet logger: null value");
			return;
		}
		outTime();
		std::cout << green << "[PACKET]: " << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\tPacket Length: \t\t\t" << yellow << paquet->GetPacketLen() << std::endl;
		void* addr = paquet->GetPacketData();
		std::cout << green << "\ttPacket Data: \t\t\t" << yellow << &addr << std::endl;
		std::cout << green << "\ttPacket Data Size: \t\t" << yellow << paquet->GetPacketDataSize() << std::endl;
		std::cout << green << "\ttPacket Used Size: \t\t" << yellow << paquet->GetUsedSize() << std::endl;

		std::cout << green << "\tHeader Encrypted: \t\t" << yellow << (paquet->GetPacketHeader()->bEncrypt ? "true" : "false") << std::endl;
		std::cout << green << "\ttHeader Length: \t\t" << yellow << (int)paquet->GetHeaderSize() << std::endl;
		std::cout << green << "\ttHeader byChecksum: \t\t" << yellow << (int)paquet->GetPacketHeader()->byChecksum << std::endl;
		std::cout << green << "\ttHeader bySequence: \t\t" << yellow << (int)paquet->GetPacketHeader()->bySequence << std::endl;
		std::cout << green << "-----------------------------------" << std::endl;
		std::cout << white;
	}
}
void Log::outFile(const char* str, ...)
{
	std::string file = ".\Debug.dat";
	std::ofstream myfile;
	va_list ap;
	char buffer[PACKET_MAX_SIZE+50];

	va_start(ap, str);

	vsnprintf(buffer, sizeof(buffer), str, ap);
	
	myfile.open(file, std::ofstream::app);
	myfile << buffer;
	myfile.close();

	va_end(ap);

	fflush(stdout);
}
void Log::outPacketFile(Packet* pPacket)
{
	std::ofstream out("packetLog.dat", std::ios::app);
	
	
	if (pPacket == nullptr)
	{
		sLog.outError("Packet logger: null value");
		return;
	}

	time_t rawtime;
	struct tm * timeinfo = new struct tm;
	char buffer[80];
	time(&rawtime);
	localtime_s(timeinfo, &rawtime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%m:%S", timeinfo);
	std::string str(buffer);
	out << "[" << str.c_str() << "] ";
	PACKETDATA *header = (PACKETDATA*)pPacket->GetPacketHeader();

	out << "[PACKET]: " << std::endl;
	out << "-----------------------------------" << std::endl;
	out << "\tPacket Opcode: \t\t\t" << header->wOpCode << std::endl;
	out << "\tPacket Length: \t\t\t" << pPacket->GetPacketLen() << std::endl;
	BYTE* addr = pPacket->GetPacketData();
	 
	out << "\tPacket Data: \t\t\t";
	int i;
	for (i = 0; i < pPacket->GetPacketDataSize() / sizeof(BYTE); i++)
		out << std::hex << "0x" << std::setw(2) << std::setfill('0') << (int)addr[i] << " ";
		
	out	<< std::endl;
	out << std::setw(0) << std::dec;
	out << "\tPacket Data Size: \t\t"<< pPacket->GetPacketDataSize() << std::endl;
	out << "\tPacket Used Size: \t\t"<< pPacket->GetUsedSize() << std::endl;

	out << "\tHeader Encrypted: \t\t" << (pPacket->GetPacketHeader()->bEncrypt ? "true" : "false") << std::endl;
	out << "\tHeader Length: \t\t\t" << (int)pPacket->GetHeaderSize() << std::endl;
	out << "\tHeader byChecksum: \t\t" << (int)pPacket->GetPacketHeader()->byChecksum << std::endl;
	out << "\tHeader bySequence: \t\t" << (int)pPacket->GetPacketHeader()->bySequence << std::endl;
	out << "-----------------------------------" << std::endl;
	delete timeinfo;

}
void Log::outDebugToFile(BYTE* data, int size, WORD opcode)
{
	if (logLevel >= LOG_LVL_DEBUG)
	{
		if (data == NULL)
		{
			outError("outDebugToFile error: data nullptr");
		}
		time_t rawtime;
		struct tm * timeinfo = new struct tm;
		char buffer[80];
		time(&rawtime);
		localtime_s(timeinfo, &rawtime);
		strftime(buffer, sizeof(buffer), "%I:%M:%S", timeinfo);
		std::string str(buffer);
		delete timeinfo;
		char* time = (char*)str.c_str();
		for (int i = 0; i < strlen(time); i++)
		{
			if (time[i] == ':')
				time[i] = '-';
		}
		std::string file = ".\packets\Packet_" + std::to_string(opcode) + "_" + time + ".dat";
		std::string file1 = ".\packets\Packet_" + std::to_string(opcode) + "_BIN" + time + ".dat";
		std::ofstream myfile;
		myfile.open(file);

		for (int i = 0; i < size; i++)
		{
			std::string value;

			value = "[" + std::to_string(i) + "]" + " : " + "[" + std::to_string(data[i]) + "]";
			myfile << value;
			myfile << "\n";
		}
		myfile.close();
	}
}