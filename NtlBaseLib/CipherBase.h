#pragma once

#include <WinCrypt.h>

#ifndef		uint8
#define		uint8		unsigned char
#endif

#ifndef		uint32
#define		uint32		unsigned long int
#endif

#define	KEY_SIZE_16	16
#define	KEY_SIZE_24	24
#define	KEY_SIZE_32	32

#define	BASE_BUFFER_SIZE 1024
#define	BUFFER_SIZE	1024

#define	AES_BLOCK_SIZE		16
#define	DES_BLOCK_SIZE		8
#define TRIPLEDES_MAX_KEY_SIZE			128

#define RSA1024BIT_KEY_SIZE 148
#define RSA1024BIT_ENCBLOCK_SIZE 117
#define RSA1024BIT_DECBLOCK_SIZE 128

#define MD5_SIZE 16

enum CIPHER{
	DES_CIPHER = 1,
	TWOFISH_CIPHER,
	AES_CIPHER,
	TRIPLEDES_CIPHER,
	BLOWFISH_CIPHER,
	MD5_CIPHER,
	RSA_CIPHER,
};

enum {
	MS_ACQCONTEXT_ERROR = -11,
	NULL_CIPHER_KEY,
	CIPHER_OBJECT_ERROR,
	INVALID_CIPHER_TYPE,
	INVALID_KEY_LENGTH,
	INVALID_INPUTDATA_LENGTH,
	NULL_INPUTDATA,
	INVALID_OUTPUTDATA_SIZE,
	NULL_OUTPUTDATA,
	CONVERT_HEXA_ERROR,
	RSA_SYSTEM_ERROR,
	CIPHER_ERROR = 0,
	CIPHER_SUCCESS,
};

#pragma warning(disable : 4100 )

class CipherBase
{
public:
	CipherBase() {};
	~CipherBase() {};
	virtual	int SetKey(unsigned char * cipherKey, int cipherKeyLength) = 0;
	virtual int Encrypt(char* originalData, int originalDataLength, char* encData, int encDataSize) { return 0; };
	virtual int Decrypt(char* originalData, int originalDataLength, char* decData, int decDataSize) { return 0; };
	virtual void ReleaseCipher(void){ return; };
};

class NCGenRandomKey
{
public:
	NCGenRandomKey(void);
	~NCGenRandomKey(void);

	bool Init(void);
	bool GenerateKey(int cipherKeyLength, unsigned char *cipherKey);
	int GenerateRSAKey(int cipherKeySize, unsigned char *cipherKey);
	int GenerateRSAPrivateKey(int cipherKeySize, unsigned char *cipherKey);

private:
	HCRYPTPROV mhProv;
};