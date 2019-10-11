#ifndef _BASE
#define _BASE

#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0501 	
#elif (_WIN32_WINNT < 0x0501)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#pragma once

#include <Windows.h>
#include <stdlib.h>

// NULL define
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

// memory safe delete
#if !defined(SAFE_DELETE)
#define SAFE_DELETE(p)			if(p) { delete p; p = 0; }
#endif
#define SAFE_DELETE_ARRAY(p)	if(p) { delete[] p; p = 0; }
#define SAFE_FREE(p)			if(p) { free(p); p = 0; }

// macro sleep
#define SleepSec(s) Sleep( (s) * 1000 )

#define INVALID_HSESSION		0xFFFFFFFF

// macro bit flag
#define BIT_FLAG_CLEAR(b)		( (b) = 0 )
#define BIT_FLAG_FLIP(b)		( (b) ^= (b) )
#define BIT_FLAG_SET(b, f)		( (b) |= (f) )
#define BIT_FLAG_UNSET(b, f)	( (b) &= ~(f) )
#define BIT_FLAG_TEST(b, f)		( (b) & (f) ? true : false ) 
#define BIT_FLAG_TOGGLE(b, f)	( (b) ^= (f) )
#define MAKE_BIT_FLAG(x)		( 0x01 << (x) )
#define MAKE_BIT_FLAG64(x)		( DWORD64(0x01) << (x) )

#pragma warning(disable:4819)

#endif