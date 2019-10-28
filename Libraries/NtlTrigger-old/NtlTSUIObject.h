

#include <string> // quitar
#include <map> // quitar
//#include "NtlTSRTTI.h"
#include "NtlTSRTTI.h"
#include "NtlTSCoreDefine.h"


/**
	UI object
*/


class CNtlTSUIObject
{
	NTL_TS_DECLARE_RTTI_ROOT(CNtlTSUIObject)
		/*const CNtlTSRTTI	RTTI = CNtlTSRTTI("CNtlTSUIObject", 0); \
		virtual	const CNtlTSRTTI&	GetRTTI(void)	const { return RTTI; } \
		const char*			GetClassName(void) const { return GetRTTI().GetClassName(); } \
		bool				IsSameClass(const CNtlTSRTTI& clVal) const { return GetRTTI().IsSameClass(clVal); } \
		bool				IsDerivedClass(const CNtlTSRTTI& clVal) const { return GetRTTI().IsDerivedClass(clVal); } \
		bool				IsDerivedClass(const std::string& strClassName) const { return GetRTTI().IsDerivedClass(strClassName); }*/

// Constructions and Destructions
public:
	virtual ~CNtlTSUIObject( void ) { return; }
};