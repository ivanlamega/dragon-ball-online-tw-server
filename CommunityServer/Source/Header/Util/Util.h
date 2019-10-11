#ifndef _UTIL_H
#define _UTIL_H

#pragma once

#include <Timer.h>
#include <string>
#include <vector>
#include <time.h>

typedef std::vector<std::string> Tokens;

Tokens StrSplit(const std::string& src, const std::string& sep);
uint32 GetUInt32ValueFromArray(Tokens const& data, uint16 index);
float GetFloatValueFromArray(Tokens const& data, uint16 index);

void stripLineInvisibleChars(std::string& src);

inline uint32 secsToTimeBitFields(time_t secs)
{
	tm* lt = localtime(&secs);
	return (lt->tm_year - 100) << 24 | lt->tm_mon << 20 | (lt->tm_mday - 1) << 14 | lt->tm_wday << 11 | lt->tm_hour << 6 | lt->tm_min;
}

/* Return a random number in the range min..max; (max-min) must be smaller than 32768. */
int32 irand(int32 min, int32 max);

/* Return a random number in the range min..max (inclusive). For reliable results, the difference
* between max and min should be less than RAND32_MAX. */
uint32 urand(uint32 min, uint32 max);

/* Return a random number in the range min..max (inclusive). */
float frand(float min, float max);

/* Return a random number in the range RAND32_MIN .. RAND32_MAX. */
int32 irand();

/* Return a random number in the range 0 .. RAND32_MAX. */
uint32 urand();

/* Return a random double from 0.0 to 1.0 (exclusive). Floats support only 7 valid decimal digits.
* A double supports up to 15 valid decimal digits and is used internally (RAND32_MAX has 10 digits).
* With an FPU, there is usually no difference in performance between float and double. */
double rand_norm(void);

float rand_norm_f(void);

/* Return a random double from 0.0 to 99.9999999999999. Floats support only 7 valid decimal digits.
* A double supports up to 15 valid decimal digits and is used internaly (RAND32_MAX has 10 digits).
* With an FPU, there is usually no difference in performance between float and double. */
double rand_chance(void);

float rand_chance_f(void);

/* Return true if a random roll fits in the specified chance (range 0-100). */
inline bool roll_chance_f(float chance)
{
	return chance > rand_chance();
}

/* Return true if a random roll fits in the specified chance (range 0-100). */
inline bool roll_chance_i(int chance)
{
	return chance > irand(0, 99);
}

inline void ApplyModUInt32Var(uint32& var, int32 val, bool apply)
{
	int32 cur = var;
	cur += (apply ? val : -val);
	if (cur < 0)
		cur = 0;
	var = cur;
}

inline void ApplyModFloatVar(float& var, float  val, bool apply)
{
	var += (apply ? val : -val);
	if (var < 0)
		var = 0;
}

inline void ApplyPercentModFloatVar(float& var, float val, bool apply)
{
	if (val == -100.0f)     // prevent set var to zero
		val = -99.99f;
	var *= (apply ? (100.0f + val) / 100.0f : 100.0f / (100.0f + val));
}
inline bool isBasicLatinCharacter(wchar_t wchar)
{
	if (wchar >= L'a' && wchar <= L'z')                     // LATIN SMALL LETTER A - LATIN SMALL LETTER Z
		return true;
	if (wchar >= L'A' && wchar <= L'Z')                     // LATIN CAPITAL LETTER A - LATIN CAPITAL LETTER Z
		return true;
	return false;
}

inline bool isExtendedLatinCharacter(wchar_t wchar)
{
	if (isBasicLatinCharacter(wchar))
		return true;
	if (wchar >= 0x00C0 && wchar <= 0x00D6)                 // LATIN CAPITAL LETTER A WITH GRAVE - LATIN CAPITAL LETTER O WITH DIAERESIS
		return true;
	if (wchar >= 0x00D8 && wchar <= 0x00DF)                 // LATIN CAPITAL LETTER O WITH STROKE - LATIN CAPITAL LETTER THORN
		return true;
	if (wchar == 0x00DF)                                    // LATIN SMALL LETTER SHARP S
		return true;
	if (wchar >= 0x00E0 && wchar <= 0x00F6)                 // LATIN SMALL LETTER A WITH GRAVE - LATIN SMALL LETTER O WITH DIAERESIS
		return true;
	if (wchar >= 0x00F8 && wchar <= 0x00FE)                 // LATIN SMALL LETTER O WITH STROKE - LATIN SMALL LETTER THORN
		return true;
	if (wchar >= 0x0100 && wchar <= 0x012F)                 // LATIN CAPITAL LETTER A WITH MACRON - LATIN SMALL LETTER I WITH OGONEK
		return true;
	if (wchar == 0x1E9E)                                    // LATIN CAPITAL LETTER SHARP S
		return true;
	return false;
}

inline bool isCyrillicCharacter(wchar_t wchar)
{
	if (wchar >= 0x0410 && wchar <= 0x044F)                 // CYRILLIC CAPITAL LETTER A - CYRILLIC SMALL LETTER YA
		return true;
	if (wchar == 0x0401 || wchar == 0x0451)                 // CYRILLIC CAPITAL LETTER IO, CYRILLIC SMALL LETTER IO
		return true;
	return false;
}

inline bool isEastAsianCharacter(wchar_t wchar)
{
	if (wchar >= 0x1100 && wchar <= 0x11F9)                 // Hangul Jamo
		return true;
	if (wchar >= 0x3041 && wchar <= 0x30FF)                 // Hiragana + Katakana
		return true;
	if (wchar >= 0x3131 && wchar <= 0x318E)                 // Hangul Compatibility Jamo
		return true;
	if (wchar >= 0x31F0 && wchar <= 0x31FF)                 // Katakana Phonetic Ext.
		return true;
	if (wchar >= 0x3400 && wchar <= 0x4DB5)                 // CJK Ideographs Ext. A
		return true;
	if (wchar >= 0x4E00 && wchar <= 0x9FC3)                 // Unified CJK Ideographs
		return true;
	if (wchar >= 0xAC00 && wchar <= 0xD7A3)                 // Hangul Syllables
		return true;
	if (wchar >= 0xFF01 && wchar <= 0xFFEE)                 // Halfwidth forms
		return true;
	return false;
}

inline bool isWhiteSpace(char c)
{
	return ::isspace(int(c)) != 0;
}

inline bool isNumeric(wchar_t wchar)
{
	return (wchar >= L'0' && wchar <= L'9');
}

inline bool isNumeric(char c)
{
	return (c >= '0' && c <= '9');
}

inline bool isNumericOrSpace(wchar_t wchar)
{
	return isNumeric(wchar) || wchar == L' ';
}

inline bool isNumeric(char const* str)
{
	for (char const* c = str; *c; ++c)
		if (!isNumeric(*c))
			return false;

	return true;
}

inline bool isNumeric(std::string const& str)
{
	for (std::string::const_iterator itr = str.begin(); itr != str.end(); ++itr)
		if (!isNumeric(*itr))
			return false;

	return true;
}

inline bool isNumeric(std::wstring const& str)
{
	for (std::wstring::const_iterator itr = str.begin(); itr != str.end(); ++itr)
		if (!isNumeric(*itr))
			return false;

	return true;
}

inline bool isBasicLatinString(const std::wstring& wstr, bool numericOrSpace)
{
	for (size_t i = 0; i < wstr.size(); ++i)
		if (!isBasicLatinCharacter(wstr[i]) && (!numericOrSpace || !isNumericOrSpace(wstr[i])))
			return false;
	return true;
}

inline bool isExtendedLatinString(const std::wstring& wstr, bool numericOrSpace)
{
	for (size_t i = 0; i < wstr.size(); ++i)
		if (!isExtendedLatinCharacter(wstr[i]) && (!numericOrSpace || !isNumericOrSpace(wstr[i])))
			return false;
	return true;
}

inline bool isCyrillicString(const std::wstring& wstr, bool numericOrSpace)
{
	for (size_t i = 0; i < wstr.size(); ++i)
		if (!isCyrillicCharacter(wstr[i]) && (!numericOrSpace || !isNumericOrSpace(wstr[i])))
			return false;
	return true;
}

inline bool isEastAsianString(const std::wstring& wstr, bool numericOrSpace)
{
	for (size_t i = 0; i < wstr.size(); ++i)
		if (!isEastAsianCharacter(wstr[i]) && (!numericOrSpace || !isNumericOrSpace(wstr[i])))
			return false;
	return true;
}

inline void strToUpper(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), toupper);
}

inline void strToLower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}

inline wchar_t wcharToUpper(wchar_t wchar)
{
	if (wchar >= L'a' && wchar <= L'z')                     // LATIN SMALL LETTER A - LATIN SMALL LETTER Z
		return wchar_t(uint16(wchar) - 0x0020);
	if (wchar == 0x00DF)                                    // LATIN SMALL LETTER SHARP S
		return wchar_t(0x1E9E);
	if (wchar >= 0x00E0 && wchar <= 0x00F6)                 // LATIN SMALL LETTER A WITH GRAVE - LATIN SMALL LETTER O WITH DIAERESIS
		return wchar_t(uint16(wchar) - 0x0020);
	if (wchar >= 0x00F8 && wchar <= 0x00FE)                 // LATIN SMALL LETTER O WITH STROKE - LATIN SMALL LETTER THORN
		return wchar_t(uint16(wchar) - 0x0020);
	if (wchar >= 0x0101 && wchar <= 0x012F)                 // LATIN SMALL LETTER A WITH MACRON - LATIN SMALL LETTER I WITH OGONEK (only %2=1)
	{
		if (wchar % 2 == 1)
			return wchar_t(uint16(wchar) - 0x0001);
	}
	if (wchar >= 0x0430 && wchar <= 0x044F)                 // CYRILLIC SMALL LETTER A - CYRILLIC SMALL LETTER YA
		return wchar_t(uint16(wchar) - 0x0020);
	if (wchar == 0x0451)                                    // CYRILLIC SMALL LETTER IO
		return wchar_t(0x0401);

	return wchar;
}

inline wchar_t wcharToUpperOnlyLatin(wchar_t wchar)
{
	return isBasicLatinCharacter(wchar) ? wcharToUpper(wchar) : wchar;
}

inline wchar_t wcharToLower(wchar_t wchar)
{
	if (wchar >= L'A' && wchar <= L'Z')                     // LATIN CAPITAL LETTER A - LATIN CAPITAL LETTER Z
		return wchar_t(uint16(wchar) + 0x0020);
	if (wchar >= 0x00C0 && wchar <= 0x00D6)                 // LATIN CAPITAL LETTER A WITH GRAVE - LATIN CAPITAL LETTER O WITH DIAERESIS
		return wchar_t(uint16(wchar) + 0x0020);
	if (wchar >= 0x00D8 && wchar <= 0x00DE)                 // LATIN CAPITAL LETTER O WITH STROKE - LATIN CAPITAL LETTER THORN
		return wchar_t(uint16(wchar) + 0x0020);
	if (wchar >= 0x0100 && wchar <= 0x012E)                 // LATIN CAPITAL LETTER A WITH MACRON - LATIN CAPITAL LETTER I WITH OGONEK (only %2=0)
	{
		if (wchar % 2 == 0)
			return wchar_t(uint16(wchar) + 0x0001);
	}
	if (wchar == 0x1E9E)                                    // LATIN CAPITAL LETTER SHARP S
		return wchar_t(0x00DF);
	if (wchar == 0x0401)                                    // CYRILLIC CAPITAL LETTER IO
		return wchar_t(0x0451);
	if (wchar >= 0x0410 && wchar <= 0x042F)                 // CYRILLIC CAPITAL LETTER A - CYRILLIC CAPITAL LETTER YA
		return wchar_t(uint16(wchar) + 0x0020);

	return wchar;
}

inline void wstrToUpper(std::wstring& str)
{
	std::transform(str.begin(), str.end(), str.begin(), wcharToUpper);
}

inline void wstrToLower(std::wstring& str)
{
	std::transform(str.begin(), str.end(), str.begin(), wcharToLower);
}

bool IsIPAddress(char const* ipaddress);
uint32 CreatePIDFile(const std::string& filename);

void hexEncodeByteArray(uint8* bytes, uint32 arrayLen, std::string& result);
#endif
