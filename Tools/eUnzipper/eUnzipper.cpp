
// eUnzipper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _MAX_DIR    256 /* max. length of path component */

bool LoadTSCryptoData(std::string strFile, std::string outdir)
{
	char szFPath[_MAX_DIR];
	_splitpath_s(strFile.c_str(), 0, 0, szFPath, _MAX_DIR, 0, 0, 0, 0);
	std::string strPath = szFPath;
	if ('\\' != strPath[strPath.size() - 1]) strPath += "\\";

	// 파일 로딩
	FILE* pFile;
	fopen_s(&pFile, strFile.c_str(), "rb");
	if (NULL == pFile)
	{
		std::cout << "File doesn't exist" << std::endl;
		return false;
	}

	fseek(pFile, 0, SEEK_END);
	int nReadSize = ftell(pFile) - 4;
	fseek(pFile, 0, SEEK_SET);
	char* pReadBuf = new char[nReadSize];
	int nOriginSize;
	fread(&nOriginSize, sizeof(int), 1, pFile);
	fread(pReadBuf, 1, nReadSize, pFile);
	fclose(pFile);

	// 암호화를 푼다
	std::string strKey = "dnfldbofmftkfkdgowntpdy";
	CNtlCipher Cipher;
	Cipher.SetKey(DES_CIPHER, strKey.c_str(), (int)strKey.size());
	char* pDecryptBuf = new char[nReadSize + 256];
	ZeroMemory(pDecryptBuf, nReadSize + 256);
	Cipher.Decrypt(pReadBuf, nReadSize, pDecryptBuf, nReadSize + 256);

	CNtlUnzip clZip;
	clZip.OpenZip(strFile.c_str(), pDecryptBuf, nOriginSize);

	if (!clZip.GotoFirstFile())
	{
		std::cout << "No files found in .e file" << std::endl;
		delete[] pReadBuf;
		delete[] pDecryptBuf;

		return false;
	}

	unsigned int MAX_BUFFER_SIZE = 102400;
	char* pBuf = new char[MAX_BUFFER_SIZE];

	sUZ_FILEINFO sInfo;
	do
	{
		std::cout << "File found checking info" << std::endl;
		clZip.GetFileInfo(sInfo);

		if (sInfo.bFolder) continue;

		int nNameLength = (int)strlen(sInfo.szFileName);
		if (nNameLength <= 2) continue;
		if ('.' != sInfo.szFileName[nNameLength - 2] ||
			't' != sInfo.szFileName[nNameLength - 1])
			continue;

		if (MAX_BUFFER_SIZE < sInfo.dwUncompressedSize)
		{
			MAX_BUFFER_SIZE = sInfo.dwUncompressedSize + 1;
			delete[] pBuf;
			pBuf = new char[MAX_BUFFER_SIZE];
		}

		if (!clZip.ReadFileData(pBuf, sInfo.dwUncompressedSize))
		{
			std::cout << "Load TS compressed file. Info[" <<  sInfo.szFileName << "]\n";
		}
		else
		{
			std:: cout << "unzipping [" << sInfo.szFileName << "]\n";
			clZip.UnzipFile(outdir.c_str(), false);
		}
	} while (clZip.GotoNextFile());

	delete[] pBuf;

	delete[] pReadBuf;
	delete[] pDecryptBuf;

	return true;
}

bool LoadTSCryptoData_UnZip(std::string strFile, std::string outfile)
{

	char szFPath[_MAX_DIR];
	_splitpath_s(strFile.c_str(), 0, 0, szFPath, _MAX_DIR, 0, 0, 0, 0);
	std::string strPath = szFPath;
	if ('\\' != strPath[strPath.size() - 1]) strPath += "\\";

	// 파일 로딩
	FILE* pFile;
	FILE* pFileOut;
	fopen_s(&pFile, strFile.c_str(), "rb");
	if (NULL == pFile)
	{
		return false;
	}

	fseek(pFile, 0, SEEK_END);
	int nReadSize = ftell(pFile) - 4;
	fseek(pFile, 0, SEEK_SET);
	char* pReadBuf = new char[nReadSize];
	int nOriginSize;
	fread(&nOriginSize, sizeof(int), 1, pFile);
	fread(pReadBuf, 1, nReadSize, pFile);
	fclose(pFile);

	// 암호화를 푼다
	std::string strKey = "dnfldbofmftkfkdgowntpdy";
	CNtlCipher Cipher;
	Cipher.SetKey(DES_CIPHER, strKey.c_str(), (int)strKey.size());
	char* pDecryptBuf = new char[nReadSize + 256];
	ZeroMemory(pDecryptBuf, nReadSize + 256);
	Cipher.Decrypt(pReadBuf, nReadSize, pDecryptBuf, nReadSize + 256);

	fopen_s(&pFileOut, outfile.c_str(), "wb");

	if (NULL == pFileOut)
	{
		std::cout << "Can not save the file. " << outfile.c_str() << std::endl;

		return 0;
	}

	fwrite(&nReadSize, sizeof(int), 1, pFileOut);
	fwrite(pDecryptBuf, 1, nReadSize, pFileOut);

	fclose(pFileOut);

	delete[] pReadBuf;
	delete[] pDecryptBuf;

	return true;
}


int main(int argc, char* argv[])
{

	if (argc < 3) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
		std::cout << "Usage is <infile> <outfile>\n"; // Inform the user of how to use the program
		std::cin.get();
		return 0;
	}

	const std::string iFilename = argv[1];
	const std::string oFilename = argv[2];


	LoadTSCryptoData_UnZip(iFilename, oFilename);
	return 0;
}
