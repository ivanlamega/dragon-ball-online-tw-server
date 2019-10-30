#ifndef _DBO_TSACTAVATARDEAD_H_
#define _DBO_TSACTAVATARDEAD_H_


#include "DboTSCoreDefine.h"


/**
	Avatar dead
*/


class CDboTSActAvatarDead : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

		// Member variables
protected:
	unsigned int						m_uiStart;

	// Constructions
public:
	CDboTSActAvatarDead(void);

	// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_ACT_TYPE_ID_ACT_AVATAR_DEAD; }

	unsigned int						GetStart(void) const;
	void								SetStart(unsigned int uiStart);


// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};

inline unsigned int CDboTSActAvatarDead::GetStart(void) const
{
	return m_uiStart;
}
#endif