#include "dboCommon.h"


public struct sHLS_MERCHANT_TBLDAT_FIRST
{
	BYTE				ignoreBits[6];
	TBLIDX			Tab_Name;
	WCHAR			wszNameText[10 + 1];
	BYTE			byTabType;//
	TBLIDX			startItemTblidx;
	TBLIDX			endItemTblidx;
};

public struct sHLS_MERCHANT_TBLDAT
{
	unsigned int			Tab_Name;
	WCHAR			wszNameText[10 + 1];
	BYTE			byTabType;//
	unsigned int			startItemTblidx;
	unsigned int			endItemTblidx;
};