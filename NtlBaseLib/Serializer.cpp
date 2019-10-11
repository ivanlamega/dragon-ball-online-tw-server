#include "stdafx.h"
#include "Serializer.h"

#define NTL_SERIALIZER_GROW_SIZE		1024

Serializer::Serializer()
{
	m_iCurrSize = NTL_SERIALIZER_GROW_SIZE;
	m_iStartPointer = 0;
	m_iEndPointer = 0;
	m_iGlowSize = NTL_SERIALIZER_GROW_SIZE;
	m_pBuffer = NULL;

	Allocate();
}

Serializer::Serializer(int iBufferSize, int iGlowSize)
{
	m_iCurrSize = iBufferSize;
	m_iStartPointer = 0;
	m_iEndPointer = 0;
	m_iGlowSize = iGlowSize;
	if (m_iGlowSize <= 0)
		m_iGlowSize = iBufferSize;

	Allocate();
}

Serializer::~Serializer()
{
	Dellocate();
}

Serializer& Serializer::operator = (const Serializer& s)
{
	int iBufferSize = s.GetBufferSize();
	int iGlowSize = s.GetGlowSize();
	int iStartPointer = s.GetStartPointer();
	int iEndPointer = s.GetEndPointer();
	const char *pData = s.GetData();

	Dellocate();

	m_iCurrSize = iBufferSize;
	m_iGlowSize = iGlowSize;
	m_iStartPointer = iStartPointer;
	m_iEndPointer = iEndPointer;

	Allocate();

	memcpy(m_pBuffer, pData, m_iEndPointer);

	return *this;
}

void Serializer::Allocate(void)
{
	m_pBuffer = new char[m_iCurrSize];
	memset(m_pBuffer, 0, m_iCurrSize);
}

void Serializer::Dellocate(void)
{
	if (m_pBuffer)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}

bool Serializer::CheckInBuffer(int iSize)
{
	if (m_pBuffer == NULL)
		return false;

	if (0 == iSize)
	{
		return true;
	}

	if (m_iCurrSize <= m_iEndPointer + iSize)
	{
		m_iCurrSize = ((m_iEndPointer + iSize - 1) / m_iGlowSize + 1) * m_iGlowSize;
		char *pTemp = new char[m_iCurrSize];
		memset(pTemp, 0, m_iCurrSize);
		memcpy(pTemp, m_pBuffer, m_iEndPointer);

		if (m_pBuffer)
		{
			delete[] m_pBuffer;
			m_pBuffer = NULL;
		}

		m_pBuffer = pTemp;
	}

	return true;
}

bool Serializer::CheckOutBuffer(int iSize)
{
	if (m_pBuffer == NULL)
		return false;

	int iPointer = m_iEndPointer - (m_iStartPointer + iSize);
	if (iPointer < 0)
	{
		m_iStartPointer = m_iEndPointer;
		return false;
	}

	return true;
}


void Serializer::Refresh(void)
{
	m_iStartPointer = 0;
	m_iEndPointer = 0;
}

Serializer& Serializer::operator<<(char chData)
{
	int iTypeSize = sizeof(char);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((char*)&m_pBuffer[m_iEndPointer]) = chData;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(unsigned char byData)
{
	int iTypeSize = sizeof(unsigned char);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((unsigned char*)&m_pBuffer[m_iEndPointer]) = byData;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(short shData)
{
	int iTypeSize = sizeof(short);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((short*)&m_pBuffer[m_iEndPointer]) = shData;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(unsigned short wData)
{
	int iTypeSize = sizeof(unsigned short);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((unsigned short*)&m_pBuffer[m_iEndPointer]) = wData;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(int iData)
{
	int iTypeSize = sizeof(int);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((int*)&m_pBuffer[m_iEndPointer]) = iData;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(unsigned int uiData)
{
	int iTypeSize = sizeof(unsigned int);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((unsigned int*)&m_pBuffer[m_iEndPointer]) = uiData;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(long lData)
{
	int iTypeSize = sizeof(long);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((long*)&m_pBuffer[m_iEndPointer]) = lData;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(unsigned long ulData)
{
	int iTypeSize = sizeof(unsigned long);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((unsigned long*)&m_pBuffer[m_iEndPointer]) = ulData;
	m_iEndPointer += iTypeSize;

	return *this;
}


Serializer& Serializer::operator<<(__int64 i64Data)
{
	int iTypeSize = sizeof(__int64);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((__int64*)&m_pBuffer[m_iEndPointer]) = i64Data;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(unsigned __int64 ui64Data)
{
	int iTypeSize = sizeof(unsigned __int64);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((unsigned __int64*)&m_pBuffer[m_iEndPointer]) = ui64Data;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(float fData)
{
	int iTypeSize = sizeof(float);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((float*)&m_pBuffer[m_iEndPointer]) = fData;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(double dData)
{
	int iTypeSize = sizeof(double);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	*((double*)&m_pBuffer[m_iEndPointer]) = dData;
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator<<(char *pData)
{
	int iTypeSize = (int)strlen(pData);
	if (iTypeSize == 0)
		return *this;

	if (!CheckInBuffer(iTypeSize))
		return *this;

	memcpy(&m_pBuffer[m_iEndPointer], pData, iTypeSize);
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator << (const char *pData)
{
	int iTypeSize = (int)strlen(pData);
	if (iTypeSize == 0)
		return *this;

	if (!CheckInBuffer(iTypeSize))
		return *this;

	memcpy(&m_pBuffer[m_iEndPointer], pData, iTypeSize);
	m_iEndPointer += iTypeSize;

	return *this;
}


Serializer& Serializer::operator<<(std::string	&str)
{
	int iTypeSize = (int)str.size();
	if (iTypeSize != 0)
	{
		if (!CheckInBuffer(iTypeSize))
			return *this;

		memcpy(&m_pBuffer[m_iEndPointer], str.c_str(), iTypeSize);
		m_iEndPointer += iTypeSize;
	}

	// 끝에 널문자를 넣어준다.
	operator<<('\0');

	return *this;
}


Serializer& Serializer::operator >> (char& chData)
{
	int iTypeSize = sizeof(char);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	chData = *((char*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (unsigned char& byData)
{
	int iTypeSize = sizeof(unsigned char);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	byData = *((unsigned char*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;

}

Serializer& Serializer::operator >> (short& shData)
{
	int iTypeSize = sizeof(short);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	shData = *((short*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (unsigned short& wData)
{
	int iTypeSize = sizeof(unsigned short);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	wData = *((unsigned short*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (int& iData)
{
	int iTypeSize = sizeof(int);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	iData = *((int*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (unsigned int& uiData)
{
	int iTypeSize = sizeof(unsigned int);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	uiData = *((unsigned int*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (long& lData)
{
	int iTypeSize = sizeof(long);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	lData = *((long*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (unsigned long& ulData)
{
	int iTypeSize = sizeof(unsigned long);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	ulData = *((unsigned long*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (__int64& i64Data)
{
	int iTypeSize = sizeof(__int64);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	i64Data = *((__int64*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (unsigned __int64& ui64Data)
{
	int iTypeSize = sizeof(unsigned __int64);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	ui64Data = *((unsigned __int64*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (float& fData)
{
	int iTypeSize = sizeof(float);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	fData = *((float*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (double& dData)
{
	int iTypeSize = sizeof(double);

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	dData = *((double*)&m_pBuffer[m_iStartPointer]);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::operator >> (std::string& str)
{
	str = (char*)&m_pBuffer[m_iStartPointer];
	m_iStartPointer += ((unsigned int)str.size() + 1);

	return *this;
}

Serializer& Serializer::In(const void *pData, int iSize)
{
	int iTypeSize = iSize;
	if (iTypeSize == 0)
		return *this;

	if (!CheckInBuffer(iTypeSize))
		return *this;

	memcpy(&m_pBuffer[m_iEndPointer], pData, iTypeSize);
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer& Serializer::Format(const char *pData /*= NULL*/, ...)
{
	char chBuffer[1024];

	va_list args;
	va_start(args, pData);

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
	vsprintf_s(chBuffer, 1024, pData, args);
#else
	vsprintf(chBuffer, pData, args);
#endif
	va_end(args);

	int iTypeSize = (int)strlen(chBuffer);

	if (!CheckInBuffer(iTypeSize))
		return *this;

	memcpy(&m_pBuffer[m_iEndPointer], chBuffer, iTypeSize);
	m_iEndPointer += iTypeSize;

	return *this;
}

Serializer&	Serializer::Out(void *pData, int iSize)
{
	int iTypeSize = iSize;
	if (iTypeSize == 0)
		return *this;

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	memcpy(pData, &m_pBuffer[m_iStartPointer], iTypeSize);
	m_iStartPointer += iTypeSize;

	return *this;
}

Serializer&	Serializer::Out(Serializer& s, int iSize)
{
	int iTypeSize = iSize;
	if (iTypeSize == 0)
		return *this;

	if (!CheckOutBuffer(iTypeSize))
		return *this;

	s.In(&m_pBuffer[m_iStartPointer], iTypeSize);
	m_iStartPointer += iTypeSize;

	return *this;
}

void Serializer::IncrementEndPointer(int nSize)
{
	if (nSize <= 0)
		return;

	if (m_iEndPointer + nSize > m_iCurrSize)
	{
		//NTL_ASSERTFAIL("Serializer::IncrementEndPointer => overflow");
		return;
	}

	m_iEndPointer += nSize;
}

bool Serializer::IsEmpty(void)
{
	if (m_iEndPointer - m_iStartPointer == 0)
		return true;

	return false;
}

int Serializer::GetDataSize(void)
{
	return m_iEndPointer - m_iStartPointer;
}
