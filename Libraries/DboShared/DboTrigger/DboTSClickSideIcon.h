#ifndef _DBO_TSCLICKSIDEICON_H
#define _DBO_TSCLICKSIDEICON_H


#include "DboTSCoreDefine.h"


/**
	Click side icon
*/


class CDboTSClickSideIcon : public CNtlTSCond
{
	NTL_TS_DECLARE_RTTI

		// Member variables
protected:
	int									m_nSitype;

// Constructions
public:
	CDboTSClickSideIcon(void);

// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_COND_TYPE_ID_CHECK_LVL; }

	int									GetSitype(void) const;
	void								SetSitype(int nSityp);

	// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};

inline int CDboTSClickSideIcon::GetSitype(void) const
{
	return m_nSitype;
}
#endif