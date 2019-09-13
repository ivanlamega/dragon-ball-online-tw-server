#include "stdafx.h"
#include "GameString.h"

const unsigned int	MAX_FORMAT_STR_BUFF = 2048;

GameString & GameString::operator=(const char * lpszStr)
{
	m_str.assign(lpszStr);

	return *this;
}

GameString & GameString::operator=(const WCHAR * pwszString)
{
	int nStrLen = WideCharToMultiByte(::GetACP(), 0, pwszString, -1, NULL, 0, NULL, NULL);
	char * pString = new char[nStrLen];
	if (pString)
	{
		WideCharToMultiByte(::GetACP(), 0, pwszString, -1, pString, nStrLen, NULL, NULL);

		m_str.assign(pString);

		delete[] pString;
	}

	return *this;
}

GameString::GameString(const WCHAR * pwszString)
{
	*this = pwszString;
}

int GameString::Format(const char *format, ...)
{
	int nRV = 0;
	char szBuf[MAX_FORMAT_STR_BUFF] = { 0x00, };

	va_list valist;

	memset(szBuf, 0x00, sizeof(szBuf));

	va_start(valist, format);

#if ( _MSC_VER >= 1400 ) // VS8+
	nRV = vsprintf_s(szBuf, MAX_FORMAT_STR_BUFF, format, valist);
#else
	nRV = vsprintf(szBuf, format, valist);
#endif

	va_end(valist);

	if (nRV > 0)
		m_str.assign(szBuf);
	else
		m_str.clear();

	return nRV;
}

void GameString::GetToken(std::vector<std::string>& tokens, char token)
{
	std::istringstream iss(m_str);
	std::string part;
	while (std::getline(iss, part, token))
	{
		tokens.push_back(part);
	}
}

size_t GameString::GetWCLen()
{
	return strlen(m_str.c_str()) + 1;
}

const WCHAR* GameString::wc_str()
{
	size_t conv, size = GetWCLen();
	WCHAR* wa = new WCHAR[size];
	mbstowcs_s(&conv, wa, size, m_str.c_str(), size);
	return wa;
}