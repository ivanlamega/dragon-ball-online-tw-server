#ifndef _NTL_TSMAIN_H_
#define _NTL_TSMAIN_H_

#define _NTL_TSRTTI_H_ 1
#include "NtlTSUIObject.h"


class CNtlTSTrigger;
class CNtlTSUIObject;

/** 
	Trigger system main
*/


class CNtlTSMain : public CNtlTSUIObject
{
	NTL_TS_DECLARE_RTTI(CNtlTSMain, CNtlTSUIObject)
	/*CNtlTSRTTI test = CNtlTSUIObject::RTTI;
	const CNtlTSRTTI	RTTI = CNtlTSRTTI("CNtlTSMain", &test);
		virtual	const CNtlTSRTTI&	GetRTTI(void)	const { return RTTI; } 
		const char*			GetClassName(void) const { return GetRTTI().GetClassName(); } 
		bool				IsSameClass(const CNtlTSRTTI& clVal) const { return GetRTTI().IsSameClass(clVal); } 
		bool				IsDerivedClass(const CNtlTSRTTI& clVal) const { return GetRTTI().IsDerivedClass(clVal); } 
		bool				IsDerivedClass(const std::string& strClassName) const { return GetRTTI().IsDerivedClass(strClassName); }*/
// Declarations
public:
	typedef std::map<NTL_TS_T_ID, CNtlTSTrigger*> mapdef_TLIST;
	typedef mapdef_TLIST::iterator mapdef_TLIST_IT;
	typedef mapdef_TLIST::const_iterator mapdef_TLISTC_CIT;

// Constructions and Destructions
public:
	CNtlTSMain( void );
	virtual ~CNtlTSMain( void );
};


#endif