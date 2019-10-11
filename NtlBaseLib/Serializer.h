#ifndef __SERIALIZER_
#define __SERIALIZER_

#include <string>

class Serializer
{
public:
	Serializer();
	Serializer(int iBufferSize, int iGlowSize);
	~Serializer();

	Serializer& operator = (const Serializer& s);

	void Refresh(void);

	Serializer&	In(const void *pData, int iSize);
	Serializer& Format(const char *pData, ...);
	Serializer&	Out(void *pData, int uiSize);
	Serializer&	Out(Serializer& s, int uiSize);

	void IncrementEndPointer(int nSize);

	Serializer& operator << (char chData);
	Serializer& operator << (unsigned char byData);
	Serializer& operator << (short shData);
	Serializer& operator << (unsigned short wData);
	Serializer& operator << (int iData);
	Serializer& operator << (unsigned int uiData);
	Serializer& operator << (long lData);
	Serializer& operator << (unsigned long ulData);
	Serializer& operator << (__int64 i64Data);
	Serializer& operator << (unsigned __int64 ui64Data);
	Serializer& operator << (float fData);
	Serializer& operator << (double dData);
	Serializer& operator << (char *pData);
	Serializer& operator << (const char *pData);
	Serializer& operator << (std::string& str);

	Serializer& operator >> (char& chData);
	Serializer& operator >> (unsigned char& byData);
	Serializer& operator >> (short& shData);
	Serializer& operator >> (unsigned short& wData);
	Serializer& operator >> (int& iData);
	Serializer& operator >> (unsigned int& uiData);
	Serializer& operator >> (long& lData);
	Serializer& operator >> (unsigned long& ulData);
	Serializer& operator >> (__int64& i64Data);
	Serializer& operator >> (unsigned __int64& ui64Data);
	Serializer& operator >> (float& fData);
	Serializer& operator >> (double& dData);
	Serializer& operator >> (std::string& str);

	bool IsEmpty(void);

	int	GetBufferSize(void) const;
	int	GetGlowSize(void) const;
	int	GetDataSize(void);
	int	GetStartPointer(void) const;
	int	GetEndPointer(void) const;
	const char*	GetData(void) const;

	bool CheckInBuffer(int iSize);
	bool CheckOutBuffer(int iSize);

protected:
	char* m_pBuffer;		/** stream buffer */
	int	m_iCurrSize;		/** current buffer size */
	int	m_iStartPointer;	/** data start pointer */
	int	m_iEndPointer;		/** data end pointer */
	int	m_iGlowSize;		/** data glow size */

protected:
	void Allocate(void);
	void Dellocate(void);
};

inline int Serializer::GetBufferSize(void) const
{
	return m_iCurrSize;
}

inline int Serializer::GetGlowSize(void) const
{
	return m_iGlowSize;
}

inline int Serializer::GetStartPointer(void) const
{
	return m_iStartPointer;
}

inline int Serializer::GetEndPointer(void) const
{
	return m_iEndPointer;
}

inline const char* Serializer::GetData(void) const
{
	return m_pBuffer;
}

#endif