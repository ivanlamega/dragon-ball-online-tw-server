#ifndef _LOGIC
#define _LOGIC

#include "Base.h"
#include "Def.h"
#include "TableAll.h"

/*
This class must contain only useful logic extracted from Client side
*/
class Logic{
	public:
		Logic();
		~Logic();

		int Logic_CalcPrice_for_Sell(sITEM_TBLDAT* pITEM_TBLDAT, sITEM_OPTION_TBLDAT* pITEM_OPTION_TBLDAT, int uiCount);
};
#endif