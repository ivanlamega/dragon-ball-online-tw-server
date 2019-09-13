#pragma once

#include <string>
#include <Windows.h>

#define SAFE_STRCPY(buffer, original_string) \
	if ( NULL==(char*)original_string ) buffer[0] = '\0'; \
		else strncpy_s<_countof(buffer)>(buffer, original_string, _countof(buffer) - 1); \
	buffer[_countof(buffer) - 1] = '\0';

#define SAFE_STRCPY_SIZEINPUT(buffer, buffer_size, original_string) \
	if ( NULL==(char*)original_string ) buffer[0] = '\0'; \
		else strncpy_s(buffer, buffer_size, original_string, _countof( original_string ) ); \
	buffer[buffer_size - 1] = '\0';

#define SAFE_WCSCPY(buffer, original_string) \
	if ( NULL==(WCHAR*)original_string ) buffer[0] = L'\0'; \
		else wcsncpy_s((WCHAR*)buffer, _countof(buffer), original_string, _countof(buffer) - 1); \
	buffer[_countof(buffer) - 1] = L'\0';

#define SAFE_STRNCPY(buffer, original_string, character_count) \
	if ( NULL==(char*)original_string ) buffer[0] = '\0'; \
		else strncpy_s<_countof(buffer)>(buffer, original_string, character_count); \
	buffer[character_count] = '\0';

#define SAFE_WCSNCPY(buffer, original_string, character_count) \
	if ( NULL==(WCHAR*)original_string ) buffer[0] = L'\0'; \
		else wcsncpy_s((WCHAR*)buffer, _countof(buffer), original_string, character_count); \
	buffer[character_count] = L'\0';

#define SAFE_WCSNCPY_SIZEINPUT(buffer, buffer_size, original_string, character_count) \
	if ( NULL==(WCHAR*)original_string ) buffer[0] = L'\0'; \
		else wcsncpy_s((WCHAR*)buffer, buffer_size, original_string, character_count); \
	buffer[character_count] = L'\0';

// These functions stores a result string in new heap area, so CleanUpHeapString(W) MUST be called to dealloc the memory.
// 이 함수들은 결과 문자열을 새로운 힙 영역에 저장하므로 메모리를 해제하기 위해 CleanUpHeapString(W) 함수를 호출해야 합니다.
// by YOSHIKI(2007-02-05)
WCHAR* MB2WC(char* pszOriginalString);
char* WC2MB(WCHAR* pwszOriginalString);

std::wstring s2ws(const std::string& s);


void CleanUpHeapString(char* pwszString);
void CleanUpHeapStringW(WCHAR* pwszString);

int GenerateFormattedString(std::string& rstrResult, char* pszFormat, ...);
int GenerateFormattedStringW(std::wstring& rwstrResult, WCHAR* pwszFormat, ...);
