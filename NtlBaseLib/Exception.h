#ifndef _EXCEPTION
#define _EXCEPTION

#pragma once

#include "Base.h"
#include "GameString.h"

#define THROW_EXCEPTION(s) throw Exception(__FILE__, __LINE__, __FUNCTION__, s)

class Exception
{
public:
	Exception(const char *filename, int line, const char * func, const char * strWhat)
		:_strFile(filename), _iLine(line), _strFunc(func), _strWhat(strWhat)
	{
		printf("EXCEPTION : [%s] in file %s [Line:%d] [Func:%s]\n", GetWhat(), GetFile(), GetLine(), GetFunc());
	}
	virtual ~Exception(void) {}

	virtual void Dump(FILE * fp = stderr)
	{
		fprintf(fp, "EXCEPTION : [%s] in file %s [Line:%d] [Func:%s]\n", GetWhat(), GetFile(), GetLine(), GetFunc());
	}

	const char* GetFile() const { return _strFile.c_str(); }
	int GetLine() const { return _iLine; }
	const char* GetFunc() const { return _strFunc.c_str(); }
	const char* GetWhat() const { return _strWhat.c_str(); }

protected:
	GameString _strFile;
	int _iLine;
	GameString _strFunc;
	GameString _strWhat;
};

#endif