#include "dboCommon.h"
#pragma pack(4)
public struct HLSItemTable
{
DWORD   Item;
    WCHAR            wszName[20 + 1];
    WCHAR            wszCJIProductID[128 + 1];
	WCHAR            wszIcon[32 + 1];
    //need Check all Struture 
    WORD            wHLSItemType;
    bool            bOnSale;
    BYTE            bySellType;
    BYTE            byDiscount;    // ÇÒÀÎ·ü
    BYTE            byStackCount;
    bool            bCjVip;        //CJ VIP ÇÒÀÎ°¡´ÉÇÑ°¡
    BYTE            byVipDiscount; // CJ VIP ÇÒÀÎ·ü
    WORD            wDisplayBitFlag;        //eHLS_DISPLAY_ITEM_FUNC_BIT_FLAG
	BYTE				unk1;
    sSUB_ITEM       asSubItem[5];
    sDBO_TIME       sLimitedStart;
    sDBO_TIME       sLimitedEnd;
    ///// all before need to be checked
    //Correct IDS
    DWORD           itemTblidx;//Next Item ID "asSubItem"
    DWORD           itemTblidx2;//Next Item ID "asSubItem"
    DWORD           itemTblidx3;//Next Item ID "asSubItem"
                                /////////////////////
    //Maybe Price
////////??????//////
	WORD 		Price;

};

struct HLSTable
{
HLSItemTable hlstable[714];
};