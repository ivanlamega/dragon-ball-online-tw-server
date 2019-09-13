#include "stdafx.h"
#include "TableFileNameList.h"
#include "NtlStringHandler.h"

TableFileNameList::TableFileNameList(void)
{
	Init();
}

TableFileNameList::~TableFileNameList(void)
{
	Destroy();
}

bool TableFileNameList::Create()
{
	return true;
}

void TableFileNameList::Destroy()
{
}

void TableFileNameList::Init()
{
}

char* TableFileNameList::GetFileName(TableContainer::eTABLE eTable)
{
	if (TableContainer::TABLE_COUNT <= eTable)
	{
		return NULL;
	}

	return (char*)(m_astrFileName[eTable].c_str());
}

WCHAR* TableFileNameList::GetFileNameW(TableContainer::eTABLE eTable)
{
	if (TableContainer::TABLE_COUNT <= eTable)
	{
		return NULL;
	}

	return (WCHAR*)(m_awstrFileName[eTable].c_str());
}

bool TableFileNameList::SetFileName(TableContainer::eTABLE eTable, char* pszFileNameWithoutExtension)
{
	if (TableContainer::TABLE_COUNT <= eTable || NULL == pszFileNameWithoutExtension)
	{
		return false;
	}

	WCHAR* pwszFileNameWithoutExtension = MB2WC(pszFileNameWithoutExtension);
	if (NULL == pwszFileNameWithoutExtension)
	{
		return false;
	}

	m_astrFileName[eTable] = pszFileNameWithoutExtension;
	m_awstrFileName[eTable] = pwszFileNameWithoutExtension;

	CleanUpHeapStringW(pwszFileNameWithoutExtension);

	return true;
}

bool TableFileNameList::SetFileName(TableContainer::eTABLE eTable, WCHAR* pwszFileNameWithoutExtension)
{
	if (TableContainer::TABLE_COUNT <= eTable || NULL == pwszFileNameWithoutExtension)
	{
		return false;
	}

	char* pszFileNameWithoutExtension = WC2MB(pwszFileNameWithoutExtension);
	if (NULL == pszFileNameWithoutExtension)
	{
		return false;
	}

	m_astrFileName[eTable] = pszFileNameWithoutExtension;
	m_awstrFileName[eTable] = pwszFileNameWithoutExtension;

	CleanUpHeapString(pszFileNameWithoutExtension);

	return true;
}