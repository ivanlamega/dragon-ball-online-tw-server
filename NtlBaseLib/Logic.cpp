#include "stdafx.h"
#include "Logic.h"

Logic::Logic(){}
Logic::~Logic(){}
/*
By Luiz45
This logic will be used to get the Price for some item to sell
*/
int Logic::Logic_CalcPrice_for_Sell(sITEM_TBLDAT* pITEM_TBLDAT, sITEM_OPTION_TBLDAT* pITEM_OPTION_TBLDAT, int uiCount)
{
	int uiSellPrice;

	if (pITEM_OPTION_TBLDAT)
	{
		//uiSellPrice = (int)SELL_PRICE(pITEM_TBLDAT->bySell_Price, pITEM_TBLDAT->dwCost, pITEM_OPTION_TBLDAT->dwCost);
	}
	else
	{
		//uiSellPrice = (int)SELL_PRICE(pITEM_TBLDAT->bySell_Price, pITEM_TBLDAT->dwCost, 0);
	}

	// avooo's comment : 기획에 의해 판매가격은 최소한 1이상이다
	if (uiSellPrice == 0)
		uiSellPrice = 1;

	return uiSellPrice * uiCount;
}