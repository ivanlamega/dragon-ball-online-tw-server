#ifndef _VECTOR
#define _VECTOR

#pragma once

#include "Base.h"
#include <Windows.h>
#include <float.h>
#include <math.h>
#include <crtdbg.h>
#include <string>

#pragma once

const unsigned char INVALID_BYTE = 0xffui8;
const unsigned short INVALID_WORD = 0xffffui16;
const unsigned int INVALID_DWORD = 0xffffffffui32;
const float INVALID_FLOAT = 3.402823466e+38F;

#define FLOAT_EPSILON 0.0001
#define FLOAT_EQ(a, b)	( ( ( b - FLOAT_EPSILON) < a ) && ( a < ( b + FLOAT_EPSILON ) ) )
const float MAX_REAL = FLT_MAX;
const float ZERO_TOLERANCE = 1e-06f;

struct VECTORXY
{
	float x;
	float z;
};

struct VECTORXYZ
{
	float x;
	float y;
	float z;
};

//////////////////////////////////////
// VECTOR
//////////////////////////////////////
class CVector
{
public:
	CVector();
	CVector(VECTORXYZ & rVector);
	CVector(VECTORXY & rVector);
	CVector(float _x, float _y, float _z);
	CVector(const float* _afTuple);
	CVector(const CVector& rhs);
	void CopyFrom(float _x, float _y, float _z);
	void CopyFrom(VECTORXYZ * pVector);
	void CopyFrom(VECTORXYZ & rVector);
	void CopyFrom(VECTORXY * pVector);
	void CopyFrom(VECTORXY & rVector);
	void CopyTo(float & rX, float &rY, float &rZ);
	void CopyTo(VECTORXYZ * pVector);
	void CopyTo(VECTORXY * pVector);
	void CopyTo(VECTORXYZ & rVector);
	void CopyTo(VECTORXY & rVector);
	CVector& operator= (const CVector& rhs);
	CVector& operator= (const VECTORXYZ& rhs);
	CVector& operator= (const VECTORXY& rhs);
	bool operator== (const CVector& rhs) const;
	bool operator== (const VECTORXYZ& rhs) const;
	bool operator!= (const CVector& rhs) const;
	bool operator<  (const CVector& rhs) const;
	bool operator<= (const CVector& rhs) const;
	bool operator>  (const CVector& rhs) const;
	bool operator>= (const CVector& rhs) const;
	CVector operator+ (const CVector& rhs) const;
	CVector operator- (const CVector& rhs) const;
	CVector operator+ (float fScalar) const;
	CVector operator- (float fScalar) const;
	CVector operator* (float fScalar) const;
	CVector operator/ (float fScalar) const;
	CVector operator- () const;
	CVector& operator+= (const CVector& rhs);
	CVector& operator-= (const CVector& rhs);
	CVector& operator+= (float fScalar);
	CVector& operator-= (float fScalar);
	CVector& operator*= (float fScalar);
	CVector& operator/= (float fScalar);
	void Reset();
	float Length() const;
	float SquaredLength() const;
	float Dot(const CVector& rhs) const;
	float Normalize();
	bool SafeNormalize();
	float Normalize(float fLength);
	CVector	Cross(const CVector& rhs) const;
	CVector UnitCross(const CVector& rhs) const;
	bool IsZero() const;
	bool IsEqual(CVector &rhs) const;
	bool IsInvalid(bool bCheckY = true) const;
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float afTuple[3];
	};
	static CVector ZERO;
	static CVector UNIT_X;
	static CVector UNIT_Y;
	static CVector UNIT_Z;
	static CVector INVALID;
	static CVector INVALID_XZ;
};

inline CVector::CVector()
	:x(0.0f), y(0.0f), z(0.0f)
{
}

inline CVector::CVector(VECTORXYZ & rVector)
	: x(rVector.x), y(rVector.y), z(rVector.z)
{
}

inline CVector::CVector(VECTORXY & rVector)
	: x(rVector.x), y(0.0f), z(rVector.z)
{
}

inline CVector::CVector(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}

inline CVector::CVector(const float* _afTuple)
{
	afTuple[0] = _afTuple[0];
	afTuple[1] = _afTuple[1];
	afTuple[2] = _afTuple[2];
}

inline CVector::CVector(const CVector& rhs)
	:x(rhs.x), y(rhs.y), z(rhs.z)
{
}

inline void CVector::CopyFrom(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

inline void CVector::CopyFrom(VECTORXYZ * pVector)
{
	x = pVector->x;
	y = pVector->y;
	z = pVector->z;
}

inline void CVector::CopyFrom(VECTORXYZ & rVector)
{
	x = rVector.x;
	y = rVector.y;
	z = rVector.z;
}

inline void CVector::CopyFrom(VECTORXY * pVector)
{
	x = pVector->x;
	y = 0.0f;
	z = pVector->z;
}

inline void CVector::CopyFrom(VECTORXY & rVector)
{
	x = rVector.x;
	y = 0.0f;
	z = rVector.z;
}

inline void CVector::CopyTo(float & rX, float & rY, float &rZ)
{
	rX = x;
	rY = y;
	rZ = z;
}

inline void CVector::CopyTo(VECTORXYZ * pVector)
{
	pVector->x = x;
	pVector->y = y;
	pVector->z = z;
}

inline void CVector::CopyTo(VECTORXY * pVector)
{
	pVector->x = x;
	pVector->z = z;
}

inline void CVector::CopyTo(VECTORXYZ & rVector)
{
	rVector.x = x;
	rVector.y = y;
	rVector.z = z;
}

inline void CVector::CopyTo(VECTORXY & rVector)
{
	rVector.x = x;
	rVector.z = z;
}

inline CVector& CVector::operator= (const CVector& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

inline CVector& CVector::operator= (const VECTORXYZ& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

inline CVector& CVector::operator= (const VECTORXY& rhs)
{
	x = rhs.x;
	y = 0.0f;
	z = rhs.z;
	return *this;
}

inline bool CVector::operator== (const CVector& rhs) const
{
	return memcmp(afTuple, rhs.afTuple, sizeof(afTuple)) == 0;
}

inline bool CVector::operator== (const VECTORXYZ& rhs) const
{
	return memcmp(afTuple, &rhs, sizeof(afTuple)) == 0;
}

inline bool CVector::operator!= (const CVector& rhs) const
{
	return memcmp(afTuple, rhs.afTuple, sizeof(afTuple)) != 0;
}

inline bool CVector::operator<  (const CVector& rhs) const
{
	return memcmp(afTuple, rhs.afTuple, sizeof(afTuple)) < 0;
}

inline bool CVector::operator<= (const CVector& rhs) const
{
	return memcmp(afTuple, rhs.afTuple, sizeof(afTuple)) <= 0;
}

inline bool CVector::operator>  (const CVector& rhs) const
{
	return memcmp(afTuple, rhs.afTuple, sizeof(afTuple)) > 0;
}

inline bool CVector::operator>= (const CVector& rhs) const
{
	return memcmp(afTuple, rhs.afTuple, sizeof(afTuple)) >= 0;
}

inline CVector CVector::operator+ (const CVector& rhs) const
{
	return CVector(x + rhs.x, y + rhs.y, z + rhs.z);
}

inline CVector CVector::operator- (const CVector& rhs) const
{
	return CVector(x - rhs.x, y - rhs.y, z - rhs.z);
}

inline CVector CVector::operator+ (float fScalar) const
{
	return CVector(x + fScalar, y + fScalar, z + fScalar);
}

inline CVector CVector::operator- (float fScalar) const
{
	return CVector(x - fScalar, y - fScalar, z - fScalar);
}

inline CVector CVector::operator* (float fScalar) const
{
	return CVector(x * fScalar, y * fScalar, z * fScalar);
}

inline CVector CVector::operator/ (float fScalar) const
{
	return CVector(x / fScalar, y / fScalar, z / fScalar);
}

inline CVector CVector::operator- () const
{
	return CVector(-x, -y, -z);
}

inline CVector& CVector::operator+= (const CVector& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

inline CVector& CVector::operator-= (const CVector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

inline CVector& CVector::operator+= (float fScalar)
{
	x += fScalar;
	y += fScalar;
	z += fScalar;

	return *this;
}

inline CVector& CVector::operator-= (float fScalar)
{
	x -= fScalar;
	y -= fScalar;
	z -= fScalar;

	return *this;
}

inline CVector& CVector::operator*= (float fScalar)
{
	x *= fScalar;
	y *= fScalar;
	z *= fScalar;
	return *this;
}

inline CVector& CVector::operator/= (float fScalar)
{
	if (fScalar != (float) 0.0f)
	{
		float fInvScalar = ((float)1.0f) / fScalar;

		x *= fInvScalar;
		y *= fInvScalar;
		z *= fInvScalar;
	}
	else
	{
		x = MAX_REAL;
		y = MAX_REAL;
		z = MAX_REAL;
	}
	return *this;
}

inline void CVector::Reset()
{
	x = y = z = 0.0f;
}

inline float CVector::Length() const
{
	return ::sqrt(afTuple[0] * afTuple[0] + afTuple[1] * afTuple[1] + afTuple[2] * afTuple[2]);
}

inline float CVector::SquaredLength() const
{
	return afTuple[0] * afTuple[0] + afTuple[1] * afTuple[1] + afTuple[2] * afTuple[2];
}

inline float CVector::Dot(const CVector& rhs) const
{
	return afTuple[0] * rhs.afTuple[0] + afTuple[1] * rhs.afTuple[1] + afTuple[2] * rhs.afTuple[2];
}

inline float CVector::Normalize()
{
	float fLength = Length();
	return Normalize(fLength);
}

inline bool CVector::SafeNormalize()
{
	float fLength = Length();
	if (ZERO_TOLERANCE > fLength)
	{
		return false;
	}
	Normalize(fLength);
	return true;
}

inline float CVector::Normalize(float fLength)
{
	if (fLength > ZERO_TOLERANCE)
	{
		float fInvLength = (1.0f) / fLength;

		afTuple[0] *= fInvLength;
		afTuple[1] *= fInvLength;
		afTuple[2] *= fInvLength;
	}
	else
	{
		fLength = 0.0f;
		afTuple[0] = 0.0f;
		afTuple[1] = 0.0f;
		afTuple[2] = 0.0f;
	}
	if (Length() < 0.8f){}
	return fLength;
}

inline CVector CVector::Cross(const CVector& rhs) const
{
	return CVector(afTuple[1] * rhs.afTuple[2] - afTuple[2] * rhs.afTuple[1],
		afTuple[2] * rhs.afTuple[0] - afTuple[0] * rhs.afTuple[2],
		afTuple[0] * rhs.afTuple[1] - afTuple[1] * rhs.afTuple[0]);

}

inline CVector CVector::UnitCross(const CVector& rhs) const
{
	CVector kCross(afTuple[1] * rhs.afTuple[2] - afTuple[2] * rhs.afTuple[1],
		afTuple[2] * rhs.afTuple[0] - afTuple[0] * rhs.afTuple[2],
		afTuple[0] * rhs.afTuple[1] - afTuple[1] * rhs.afTuple[0]);

	kCross.Normalize();
	return kCross;
}

inline bool CVector::IsZero() const
{
	if (afTuple[0] || afTuple[1] || afTuple[2])
	{
		return false;
	}
	return true;
}

inline bool CVector::IsInvalid(bool bCheckY) const
{
	if (false == bCheckY)
	{
		if (INVALID_FLOAT == afTuple[0] && INVALID_FLOAT == afTuple[2])
		{
			return true;
		}
	}
	else
	{
		if (INVALID_FLOAT == afTuple[0] && INVALID_FLOAT == afTuple[1] && INVALID_FLOAT == afTuple[2])
		{
			return true;
		}
	}
	return false;
}

inline bool CVector::IsEqual(CVector &rhs) const
{
	if (FLOAT_EQ(afTuple[0], rhs.afTuple[0]) &&
		FLOAT_EQ(afTuple[1], rhs.afTuple[1]) &&
		FLOAT_EQ(afTuple[2], rhs.afTuple[2]))
	{
		return true;
	}
	return false;
}

#endif