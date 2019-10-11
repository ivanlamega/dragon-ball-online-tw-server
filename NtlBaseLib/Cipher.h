#ifndef _CIPHER
#define _CIPHER

#include "CipherBase.h"

class Cipher
{
public:
	Cipher(void);
	~Cipher(void);

	int	SetKey(unsigned char cipher, const char * cipherKey, int cipherKeyLength);
	unsigned char	GetCipherType(void) { return mCipherType; };

	int  Encrypt(const char* originalData, int originalDataLength, char* encData, int encDataSize);
	int  Decrypt(const char* originalData, int originalDataLength, char* decData, int decDataSize);

	CipherBase* GetCipher(void) { return mCipherPtr; };

private:
	unsigned char mCipherType;
	CipherBase* mCipherPtr;
};

#endif