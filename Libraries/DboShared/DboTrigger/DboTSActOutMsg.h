#ifndef _DBO_TSACTOUTMSG_H_
#define _DBO_TSACTOUTMSG_H_

#include "DboTSCoreDefine.h"

/**
	Message out action
	용도 : Client quest, client trigger
	설명 : 클라이언트 전용으로 사용되는 NPC 대화
*/

class CDboTSActOutMsg : public CNtlTSAction
{
	NTL_TS_DECLARE_RTTI

	// Member variables
protected:
	unsigned int						m_uiMsgIdx;
	// Constructions
public:
	CDboTSActOutMsg(void);

	// Methods
public:
	virtual unsigned int				GetEntityType(void) const { return DBO_ACT_TYPE_ID_ACT_NPCCONV; }
	unsigned int						GetMsgIdx(void) const;
	void								SetMsgIdx(unsigned int uiMsjIdx);

	// Implementations
protected:
	// 스크립트로 부터 컴포넌트 객체의 데이터를 로딩 및 입력 시키기 위한 함수
	virtual	void						ApplyScriptDataForScript(const CNtlTSScrProperty& clProperty);
	virtual	void						TakeScriptDataForScript(CNtlTSScrProperty& clProperty);
};

inline unsigned int CDboTSActOutMsg::GetMsgIdx(void) const
{
	return m_uiMsgIdx;
}
#endif
