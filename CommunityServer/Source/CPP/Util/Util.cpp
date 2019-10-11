#include <boost/asio.hpp>

#include <Util.h>
#include <TSS.h>
#include <random>
#include <chrono>
#include <cstdarg>


std::mt19937* initRand()
{
	std::seed_seq seq = { size_t(std::time(nullptr)), size_t(std::clock()) };
	return new std::mt19937(seq);
}

static AKCore::thread_local_ptr<std::mt19937> mtRand(&initRand);

uint32 CommunityTimer::m_iTime = 0;
uint32 CommunityTimer::m_iPrevTime = 0;

uint32 CommunityTimer::tickTime() { return m_iTime; }
uint32 CommunityTimer::tickPrevTime() { return m_iPrevTime; }

uint32 CommunityTimer::tick()
{
	// save previous world tick time
	m_iPrevTime = m_iTime;

	// get the new one and don't forget to persist current system time in m_SystemTickTime
	m_iTime = CommunityTimer::getMSTime();

	// return tick diff
	return getMSTimeDiff(m_iPrevTime, m_iTime);
}

uint32 CommunityTimer::getMSTime()
{
	static auto const start_time = std::chrono::system_clock::now();
	return static_cast<uint32>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count());
}

//////////////////////////////////////////////////////////////////////////
int32 irand(int32 min, int32 max)
{
	std::uniform_int_distribution<int32> dist(min, max);
	return dist(*mtRand.get());
}

uint32 urand(uint32 min, uint32 max)
{
	std::uniform_int_distribution<uint32> dist(min, max);
	return dist(*mtRand.get());
}

float frand(float min, float max)
{
	std::uniform_real_distribution<double> dist(min, max);
	return float(dist(*mtRand.get()));
}

int32 irand()
{
	std::uniform_int_distribution<int32> dist;
	return dist(*mtRand.get());
}

uint32 urand()
{
	std::uniform_int_distribution<uint32> dist;
	return dist(*mtRand.get());
}

double rand_norm()
{
	std::uniform_real_distribution<double> dist(0, 1.0f);
	return dist(*mtRand.get());
}

float rand_norm_f()
{
	std::uniform_real_distribution<float> dist(0, 1.0f);
	return dist(*mtRand.get());
}

double rand_chance()
{
	std::uniform_real_distribution<double> dist(0, 100.0);
	return dist(*mtRand.get());
}

float rand_chance_f()
{
	std::uniform_real_distribution<double> dist(0, 100.0);
	return float(dist(*mtRand.get()));
}

Tokens StrSplit(const std::string& src, const std::string& sep)
{
	Tokens r;
	std::string s;
	for (std::string::const_iterator i = src.begin(); i != src.end(); ++i)
	{
		if (sep.find(*i) != std::string::npos)
		{
			if (s.length()) r.push_back(s);
			s = "";
		}
		else
		{
			s += *i;
		}
	}
	if (s.length()) r.push_back(s);
	return r;
}

uint32 GetUInt32ValueFromArray(Tokens const& data, uint16 index)
{
	if (index >= data.size())
		return 0;

	return (uint32)atoi(data[index].c_str());
}

float GetFloatValueFromArray(Tokens const& data, uint16 index)
{
	float result;
	uint32 temp = GetUInt32ValueFromArray(data, index);
	memcpy(&result, &temp, sizeof(result));

	return result;
}

void stripLineInvisibleChars(std::string& str)
{
	static std::string invChars = " \t\7\n";

	size_t wpos = 0;

	bool space = false;
	for (size_t pos = 0; pos < str.size(); ++pos)
	{
		if (invChars.find(str[pos]) != std::string::npos)
		{
			if (!space)
			{
				str[wpos++] = ' ';
				space = true;
			}
		}
		else
		{
			if (wpos != pos)
				str[wpos++] = str[pos];
			else
				++wpos;
			space = false;
		}
	}

	if (wpos < str.size())
		str.erase(wpos, str.size());
}
/// Check if the string is a valid ip address representation
bool IsIPAddress(char const* ipaddress)
{
	if (!ipaddress)
		return false;

	// Let the big boys do it.
	// Drawback: all valid ip address formats are recognized e.g.: 12.23,121234,0xABCD)
	boost::system::error_code ec;
	boost::asio::ip::address::from_string(ipaddress, ec);
	return !!ec;
}

/// create PID file
uint32 CreatePIDFile(const std::string& filename)
{
	FILE* pid_file = fopen(filename.c_str(), "w");
	if (pid_file == nullptr)
		return 0;

#ifdef WIN32
	DWORD pid = GetCurrentProcessId();
#else
	pid_t pid = getpid();
#endif

	fprintf(pid_file, "%d", pid);
	fclose(pid_file);

	return (uint32)pid;
}
void hexEncodeByteArray(uint8* bytes, uint32 arrayLen, std::string& result)
{
	std::ostringstream ss;
	for (uint32 i = 0; i < arrayLen; ++i)
	{
		for (uint8 j = 0; j < 2; ++j)
		{
			unsigned char nibble = 0x0F & (bytes[i] >> ((1 - j) * 4));
			char encodedNibble;
			if (nibble < 0x0A)
				encodedNibble = '0' + nibble;
			else
				encodedNibble = 'A' + nibble - 0x0A;
			ss << encodedNibble;
		}
	}
	result = ss.str();
}
bool IsLetters(std::string input)
{
	for (int i = 0; i < input.size(); i++)
	{
		int uppercaseChar = toupper(input[i]); //Convert character to upper case version of character
		if (uppercaseChar < 'A' || uppercaseChar > 'Z') //If character is not A-Z
		{
			return false;
		}
	}
	//At this point, we have gone through every character and checked it.
	return true; //Return true since every character had to be A-Z
}