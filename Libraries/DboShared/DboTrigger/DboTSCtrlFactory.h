#ifndef _DBO_TSCTRLFACTORY_H_
#define _DBO_TSCTRLFACTORY_H_
#include "NtlTSControlFactory.h" //quitar

/**
	Controller factory
*/


class CDboTSCtrlFactory : public CNtlTSControlFactory
{
// Methods
public:
	virtual	void						RegisterCtrlType(void) ;
};


#endif