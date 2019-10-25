#ifndef _DBO_TSACTMAIL_H_
#define _DBO_TSACTMAIL_H_


#include "DboTSCoreDefine.h"


/**
	Mail action
*/


class CDboTSActMail : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

		// Member variables
protected:
	unsigned int						m_uiZenny;
	unsigned int						m_uiIcnt;
	unsigned int						m_uiStidx;
	unsigned int						m_uiItidx;
	unsigned int						m_uiDtidx;

	// Constructions
public:
	CDboTSActMail(void);

	// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_ACT_TYPE_ID_ACT_DIR; }

	unsigned int						GetZenny(void) const;
	void								SetZenny(unsigned int uiZenny);

	unsigned int						GetIcnt(void) const;
	void								SetIcnt(unsigned int uiIcnt);

	unsigned int						GetStidx(void) const;
	void								SetStidx(unsigned int TblIdx);

	unsigned int						GetItidx(void) const;
	void								SetItidx(unsigned int TblIdx);

	unsigned int						GetDtidx(void) const;
	void								SetDtidx(unsigned int TblIdx);

	// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};


inline unsigned int CDboTSActMail::GetZenny(void) const
{
	return m_uiZenny;
}


inline unsigned int CDboTSActMail::GetIcnt(void) const
{
	return m_uiIcnt;
}


inline unsigned int CDboTSActMail::GetStidx(void) const
{
	return m_uiStidx;
}

inline unsigned int CDboTSActMail::GetItidx(void) const
{
	return m_uiItidx;
}

inline unsigned int CDboTSActMail::GetDtidx(void) const
{
	return m_uiDtidx;
}

#endif