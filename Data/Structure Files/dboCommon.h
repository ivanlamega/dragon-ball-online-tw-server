#include "stddefs.h"
typedef unsigned int TBLIDX;


struct sSUB_ITEM
{
	TBLIDX	itemTblidx;
	BYTE	   byStackCount;
};


struct sDBO_TIME
{
	unsigned short   year;
	unsigned char   month;
	unsigned char   day;
	unsigned char   hour;
	unsigned char   minute;
	unsigned char   second;
};
