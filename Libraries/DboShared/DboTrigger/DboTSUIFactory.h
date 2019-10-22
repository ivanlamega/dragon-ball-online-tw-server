#ifndef _DBO_TSUIFACTORY_H_
#define _DBO_TSUIFACTORY_H_

#include "NtlTSUIFactory.h" //quitar
/**
	Controller factory
*/


class CDboTSUIFactory : public CNtlTSUIFactory
{
// Methods
public:
	virtual	void						RegisterUIType(void) {return;};
};


#endif