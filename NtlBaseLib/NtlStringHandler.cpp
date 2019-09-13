#include "StdAfx.h"
#include "NtlStringHandler.h"

const DWORD MAX_LENGTH_OF_FORMAT_STRING_RESULT = 1024;

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}


WCHAR* MB2WC(char* pszOriginalString)
{
	if (NULL == pszOriginalString)
	{
		return NULL;
	}

	int iRequiredChars = ::MultiByteToWideChar(::GetACP(), 0, pszOriginalString, -1, NULL, 0);
	WCHAR* pwszResultString = new WCHAR[iRequiredChars];
	if (NULL == pwszResultString)
	{
		return NULL;
	}

	::MultiByteToWideChar(::GetACP(), 0, pszOriginalString, -1, pwszResultString, iRequiredChars);

	return pwszResultString;
}

char* WC2MB(WCHAR* pwszOriginalString)
{
	if (NULL == pwszOriginalString)
	{
		return NULL;
	}

	int iRequiredChars = ::WideCharToMultiByte(::GetACP(), 0, pwszOriginalString, -1, NULL, 0, NULL, NULL);
	char* pszResultString = new char[iRequiredChars];
	if (NULL == pszResultString)
	{
		return NULL;
	}

	::WideCharToMultiByte(::GetACP(), 0, pwszOriginalString, -1, pszResultString, iRequiredChars, NULL, NULL);

	return pszResultString;
}

void CleanUpHeapString(char* pszString)
{
	if (NULL != pszString)
	{
		delete[] pszString;
	}
}

void CleanUpHeapStringW(WCHAR* pwszString)
{
	if (NULL != pwszString)
	{
		delete[] pwszString;
	}
}

int GenerateFormattedString(std::string& rstrResult, char* pszFormat, ...)
{
	char szResult[MAX_LENGTH_OF_FORMAT_STRING_RESULT + 1];
	::ZeroMemory(szResult, _countof(szResult));

	va_list valist;
	va_start(valist, pszFormat);

	int nWrittenBytes = vsprintf_s(szResult, _countof(szResult), pszFormat, valist);

	va_end(valist);

	if (0 < nWrittenBytes)
	{
		rstrResult.assign(szResult);
	}
	else
	{
		rstrResult.clear();
	}

	return nWrittenBytes;
}

int GenerateFormattedStringW(std::wstring& rwstrResult, WCHAR* pwszFormat, ...)
{
	WCHAR wszResult[MAX_LENGTH_OF_FORMAT_STRING_RESULT + 1];
	::ZeroMemory(wszResult, _countof(wszResult));

	va_list valist;
	va_start(valist, pwszFormat);

	int nWrittenBytes = vswprintf_s(wszResult, _countof(wszResult), pwszFormat, valist);

	va_end(valist);

	if (0 < nWrittenBytes)
	{
		rwstrResult.assign(wszResult);
	}
	else
	{
		rwstrResult.clear();
	}

	return nWrittenBytes;
}