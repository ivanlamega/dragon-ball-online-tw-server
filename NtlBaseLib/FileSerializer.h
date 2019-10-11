#pragma once

#include "Serializer.h"
#include <Windows.h>

class FileSerializer : public Serializer
{
public:

	FileSerializer();
	FileSerializer(int iBufferSize, int iGlowSize);

	FileSerializer(char* pszFullPath);
	FileSerializer(WCHAR* pwszFullPath);

	virtual ~FileSerializer();

public:
	bool SaveFile(char* pszFullPathFileName, bool bCrypt = FALSE, char* szCryptPassword = NULL);
	bool SaveFile(WCHAR* pwszFullPathFileName, bool bCrypt = FALSE, WCHAR* szCryptPassword = NULL);

	bool LoadFile(char* pszFullPathFileName, bool bCrypt = FALSE, char* szCryptPassword = NULL);
	bool LoadFile(char* pszBuffer, int nSize, bool bCrypt = FALSE, char* szCryptPassword = NULL);

	bool LoadFile(WCHAR* pwszFullPathFileName, bool bCrypt = FALSE, WCHAR* szCryptPassword = NULL);
};