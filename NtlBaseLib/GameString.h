#ifndef _GAMESTRING
#define _GAMESTRING

#pragma once

#include "Base.h"
#include <string>
#include <stdarg.h>
#include <vector>
#include <iostream>
#include <sstream>

class GameString
{
public:
	GameString() {}
	GameString(const char * lpszStr) :m_str(lpszStr) {}
	GameString(const WCHAR * pwszString);

public:
	std::string & GetString(void) { return m_str; }
	GameString & operator=(const char * lpszStr);
	GameString & operator=(const WCHAR * pwszString);

	int Format(const char *format, ...);
	const char* c_str(void) const { return m_str.c_str(); }
	void clear(void) { m_str.clear(); }

	bool operator<(const GameString &right) const
	{
		if (m_str<right.m_str) return true;
		else return false;
	}

	void GetToken(std::vector<std::string>& tokens, char token);
	size_t GetWCLen();
	const WCHAR* wc_str();

private:
	std::string m_str;
};

#endif