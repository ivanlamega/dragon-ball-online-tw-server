#include "StdAfx.h"
#include "ChatCommandTable.h"
#include "Serializer.h"

WCHAR* ChatCommandTable::m_pwszSheetList[] =
{
	L"Table_Data_KOR",
	NULL
};

ChatCommandTable::ChatCommandTable(void)
{
	Init();
}

ChatCommandTable::~ChatCommandTable(void)
{
	Destroy();
}

bool ChatCommandTable::Create(DWORD dwCodePage)
{
	return Table::Create(dwCodePage);
}

void ChatCommandTable::Destroy()
{
	Table::Destroy();
}

void ChatCommandTable::Init()
{
}

void* ChatCommandTable::AllocNewTable(WCHAR* pwszSheetName, DWORD dwCodePage)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHAT_COMMAND_TBLDAT* pNewChatCommand = new sCHAT_COMMAND_TBLDAT;
		if (NULL == pNewChatCommand)
			return NULL;

		CPINFO cpInfo;
		if (false == GetCPInfo(dwCodePage, &cpInfo))
		{
			delete pNewChatCommand;
			return NULL;
		}

		m_dwCodePage = dwCodePage;
		return pNewChatCommand;
	}

	return NULL;
}

bool ChatCommandTable::DeallocNewTable(void* pvTable, WCHAR* pwszSheetName)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHAT_COMMAND_TBLDAT* pChatCommand = (sCHAT_COMMAND_TBLDAT*)pvTable;
		if (FALSE != IsBadReadPtr(pChatCommand, sizeof(*pChatCommand)))
			return false;

		delete pChatCommand;

		return true;
	}

	return false;
}

bool ChatCommandTable::AddTable(void * pvTable, bool bReload)
{
	UNREFERENCED_PARAMETER(bReload);

	sCHAT_COMMAND_TBLDAT* pTbldat = (sCHAT_COMMAND_TBLDAT*)pvTable;

	if (false == pTbldat->bValidity_Able)
	{
		return false;
	}


	if (false == m_mapTableList.insert(std::pair<TBLIDX, sTBLDAT*>(pTbldat->tblidx, pTbldat)).second)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\r\n Table Tblidx[%u] is Duplicated ", m_wszXmlFileName, pTbldat->tblidx);
		_ASSERTE(0);
		return false;
	}


	return true;
}

bool ChatCommandTable::SetTableData(void* pvTable, WCHAR* pwszSheetName, std::wstring* pstrDataName, BSTR bstrData)
{
	if (0 == wcscmp(pwszSheetName, L"Table_Data_KOR"))
	{
		sCHAT_COMMAND_TBLDAT* pChatCommand = (sCHAT_COMMAND_TBLDAT*)pvTable;

		if (0 == wcscmp(pstrDataName->c_str(), L"Tblidx"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pChatCommand->tblidx = READ_DWORD(bstrData);
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Validity_Able"))
		{
			CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
			pChatCommand->bValidity_Able = READ_BOOL(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcscmp(pstrDataName->c_str(), L"Action_Animation_Index"))
		{
			pChatCommand->wAction_Animation_Index = READ_WORD(bstrData, pstrDataName->c_str());
		}
		else if (0 == wcsncmp(pstrDataName->c_str(), L"Chat_Command_", wcslen(L"Chat_Command_")))
		{
			bool bFound = false;
			WCHAR szBuffer[1024] = { 0x00, };
			for (int i = 0; i < MAX_CHAT_COMMAND; i++)
			{
				swprintf(szBuffer, 1024, L"Chat_Command_%d", i + 1);

				if (0 == wcscmp(pstrDataName->c_str(), szBuffer))
				{
					if (0 == i)
						CheckNegativeInvalid(pstrDataName->c_str(), bstrData);
					pChatCommand->aChat_Command[i] = READ_DWORD(bstrData);

					bFound = true;
					break;
				}
			}
			if (false == bFound)
			{
				Table::CallErrorCallbackFunction(L"[File] : %s\n[Error] : Unknown field name found!(Field Name = %s)", m_wszXmlFileName, pstrDataName->c_str());
				return false;
			}
		}
		else
		{
			Table::CallErrorCallbackFunction(L"[File] : %s\n[Error] : Unknown field name found!(Field Name = %s)", m_wszXmlFileName, pstrDataName->c_str());
			return false;
		}
	}
	else
	{
		_ASSERT(0);
		return false;
	}

	return true;
}


sTBLDAT* ChatCommandTable::FindData(TBLIDX tblidx)
{
	if (0 == tblidx)
		return NULL;

	TABLEIT iter;
	iter = m_mapTableList.find(tblidx);
	if (End() == iter)
		return NULL;

	return (sTBLDAT*)(iter->second);
}

bool ChatCommandTable::LoadFromBinary(Serializer& serializer, bool bReload)
{
	if (false == bReload)
	{
		Reset();
	}

	BYTE byMargin = 1;
	serializer >> byMargin;

	bool bLoop = true;
	do
	{
		sCHAT_COMMAND_TBLDAT* pTableData = new sCHAT_COMMAND_TBLDAT;
		if (NULL == pTableData)
		{
			//- yoshiki : To log system!
			Destroy();
			return false;
		}

		if (false == pTableData->LoadFromBinary(serializer))
		{
			delete pTableData;
			bLoop = false;
			break;
		}

		//  [4/26/2008 zeroera] : 설명 : 실패하더라도 Load의 종료여부는 File Loading에서 결정한다
		if (false == AddTable(pTableData, bReload))
		{
			delete pTableData;
		}

	} while (false != bLoop);

	return true;
}

bool ChatCommandTable::SaveToBinary(Serializer& serializer)
{
	serializer.Refresh();

	BYTE byMargin = 1;
	serializer << byMargin;

	TABLE::iterator iter;
	for (iter = Begin(); End() != iter; iter++)
	{
		sCHAT_COMMAND_TBLDAT* pTableData = (sCHAT_COMMAND_TBLDAT*)(iter->second);

		pTableData->SaveToBinary(serializer);
	}

	return true;
}