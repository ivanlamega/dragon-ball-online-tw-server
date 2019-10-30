#ifndef _DBO_TSACTWPSFD_H_
#define _DBO_TSACTWPSFD_H_


#include "DboTSCoreDefine.h"


/**
	unknown
*/


class CDboTSActWPSFD : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

// Member variables
protected:
	unsigned int						m_uiSid;

// Constructions
public:
	CDboTSActWPSFD(void);

	// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_ACT_TYPE_ID_ACT_WPSFD; }

	unsigned int						GetSid(void) const;
	void								SetSid(unsigned int uiSid);

// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};

inline unsigned int CDboTSActWPSFD::GetSid(void) const
{
	return m_uiSid;
}

#endif