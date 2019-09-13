// Copyright (c) 2015 by HHD Software Ltd.
// This file is part of the HHD Software Hex Editor Neo
// For usage and distribution policies, consult the license distributed with a product installation program
#pragma once
// Hex Editor Neo's Structure Viewer sample declaration file

// Constants and macros
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define TRUE 1
#define FALSE 0
#define NULL 0


// Type aliases

// Standard Windows types
typedef char CHAR;
typedef wchar_t WCHAR;
typedef short SHORT;
typedef int INT;
typedef long LONG;
typedef __int64 LONGLONG;

typedef unsigned char BYTE,UCHAR;
typedef unsigned short WORD,USHORT;
typedef unsigned int UINT;
typedef unsigned long DWORD,ULONG;
typedef unsigned __int64 ULONGLONG,FILETIME,QWORD;

// Sized integer types
typedef char int8,__int8;
typedef short int16,__int16;
typedef int int32,__int32;
typedef __int64 int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned __int64 uint64;


[display(format("{0b16Xw4f0ar}-{1b16Xw2f0ar}-{2b16Xw2f0ar}-{3b16X}{4b16X}-{5b16X}{6b16X}{7b16X}{7b16X}{9b16X}{10b16X}", Data1, Data2, Data3, 
	Data4[0], Data4[1], Data4[2], Data4[3], Data4[4], Data4[5], Data4[6], Data4[7]))]
struct GUID
{
	ULONG Data1;
	USHORT Data2;
	USHORT Data3;
	UCHAR Data4[8];
};


// Expression type, as returned by built-in type() function
enum
{
	BooleanType,
	IntegerType,
	FloatingPointType,
	StringType,
};

typedef DWORD COLORREF;
typedef float	FLOAT;
typedef double	DOUBLE;
