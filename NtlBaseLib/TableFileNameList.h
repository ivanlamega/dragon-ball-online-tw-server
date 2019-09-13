#pragma once

#include "TableContainer.h"

class TableFileNameList
{
public:
	TableFileNameList();
	virtual ~TableFileNameList();

	bool Create();
	void Destroy();

	char* GetFileName(TableContainer::eTABLE eTable);
	WCHAR* GetFileNameW(TableContainer::eTABLE eTable);
	bool SetFileName(TableContainer::eTABLE eTable, char* pszFileNameWithoutExtension);
	bool SetFileName(TableContainer::eTABLE eTable, WCHAR* pwszFileNameWithoutExtension);

protected:
	void Init();

private:
	std::string	m_astrFileName[TableContainer::TABLE_COUNT];
	std::wstring m_awstrFileName[TableContainer::TABLE_COUNT];
};