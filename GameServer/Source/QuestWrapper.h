#pragma once
#include "DboTSCore.h"
struct sUZ_FILEINFO;
class CNPCTable;
class CObjectTable;
class CGameQuestAgency;
class CGameTriggerAgency;
class CGameObjectAgency;
class CGameQuestRecv;
class CGameTriggerRecv;
class CNtlUnzip;

class CQuestWrapper : public CDboTSMain
{
	NTL_TS_DECLARE_RTTI(CQuestWrapper, CDboTSMain)
	// Declarations
public:
	typedef unsigned __int64 NPC_POS_KEY;

	struct sNPC_POS_INFO
	{
		sVECTOR3							Pos;
	};

	typedef std::map< NPC_POS_KEY, sNPC_POS_INFO > mapdef_NPC_POS_LIST;
	// Constructions and Destructions
public:
	CQuestWrapper(void);
	virtual ~CQuestWrapper(void);
	static CQuestWrapper*					s_pInstance;

	// Methods
public:
	virtual bool						Create(void);
	virtual void						Delete(void);
	bool								IsCreated(void);
	void								DeleteTrigger(CNtlTSTrigger* pNTLTrigger);
	CDboTSTCtrl*						MakeTriggerControllerQuest(CNtlTSTrigger* pNTLTrigger, CDboTSQAgency* questAgency);
	CDboTSTCtrl*						MakeTriggerControllerTrigger(CNtlTSTrigger* pNTLTrigger, CDboTSTAgency* triggerAgency);

	CGameQuestAgency*					CreateAgency_Quest(void);
	void								DeleteAgency_Quest(void);

	CGameTriggerAgency*					CreateAgency_Trigger(void);
	void								DeleteAgency_Trigger(void);

	CGameObjectAgency*					CreateAgency_Object(void);
	void								DeleteAgency_Object(void);

	CGameQuestAgency*					GetQAgency(void);
	CGameTriggerAgency*					GetTAgency(void);

	CGameQuestRecv*						GetQRecv(void);
	CGameTriggerRecv*					GetTRecv(void);

	CNtlTSTrigger*						FindQuestFromTS(NTL_TS_T_ID tId);
	CNtlTSMain::mapdef_TLISTC_CIT		BeginQuestFromTS(void) const;
	CNtlTSMain::mapdef_TLISTC_CIT		EndQuestFromTS(void) const;

	CNtlTSTrigger*						FindTriggerFromTS(NTL_TS_T_ID tId);
	CNtlTSMain::mapdef_TLISTC_CIT		BeginTriggerFromTS(void) const;
	CNtlTSMain::mapdef_TLISTC_CIT		EndTriggerFromTS(void) const;

	CNtlTSTrigger*						FindObjectFromTS(NTL_TS_T_ID tId);
	CNtlTSMain::mapdef_TLISTC_CIT		BeginObjectFromTS(void) const;
	CNtlTSMain::mapdef_TLISTC_CIT		EndObjectFromTS(void) const;

	sVECTOR3*							FindNPCPosition(TBLIDX WorldIdx, TBLIDX NPCIdx);	

	// Implementations
protected:
	bool								m_bCreated;
	// Path
	std::string							m_strQuestPath;
	std::string							m_strTriggerPath;
	std::string							m_strObjectPath;

	// Agency
	CGameQuestAgency*					m_pQAgency;
	CGameTriggerAgency*					m_pTAgency;
	CGameObjectAgency*					m_pObjAgency;

	// Trigger system
	bool								m_bSchedulingLoad;

	CNtlUnzip*							m_pclQuestZip;
	CNtlTSMain::mapdef_TLIST			m_defQuest;

	CNtlUnzip*							m_pclTriggerZip;
	CNtlTSMain::mapdef_TLIST			m_defTrigger;

	CNtlUnzip*							m_pclObjectZip;
	CNtlTSMain::mapdef_TLIST			m_defObject;

	// Trigger receiver
	CGameQuestRecv*						m_pQRecv;
	CGameTriggerRecv*					m_pTRecv;
	// NPC Position list
	mapdef_NPC_POS_LIST					m_defNPCPosList;

	virtual bool						LoadLog(void);
	virtual void						UnloadLog(void);

	virtual bool						LoadFactories(void);
	virtual void						UnloadFactories(void);

	virtual bool						LoadScripts(void);
	virtual void						UnloadAllScripts(void);

	virtual bool						LoadEventMappers(void);
	virtual void						UnloadEventMappers(void);

	virtual bool						LoadRecv(void);
	virtual void						UnloadRecv(void);

	void								RegisterNPCPosition(TBLIDX WorldIdx, TBLIDX NPCIdx, sVECTOR3& v3Pos);
	void								ClearAllNPCPosition(void);

	void								LoadEventMapper(sUZ_FILEINFO* pFileInfo, char* pBuf);

	bool								HasEventMapperFromFile(void);
	bool								LoadEventMapperFromFile(void);
	bool								LoadEventMapperFromRunTime(void);

};

static CQuestWrapper* GetTSCMain(void)
{
	return CQuestWrapper::s_pInstance;
}


inline CGameQuestAgency* CQuestWrapper::GetQAgency(void)
{
	return m_pQAgency;
}

inline CGameTriggerAgency* CQuestWrapper::GetTAgency(void)
{
	return m_pTAgency;
}

inline CGameQuestRecv* CQuestWrapper::GetQRecv(void)
{
	return m_pQRecv;
}

inline CGameTriggerRecv* CQuestWrapper::GetTRecv(void)
{
	return m_pTRecv;
}
inline bool CQuestWrapper::IsCreated(void)
{
	return m_bCreated;
}