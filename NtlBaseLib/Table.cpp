#include "stdafx.h"
#include "Table.h"
#include "XMLDoc.h"
#include "Serializer.h"
#include "NtlStringHandler.h"

Dbo_TableErrorCallback Table::m_pfnErrorCallback = NULL;
void* Table::m_pvErrorCallbackArg = NULL;

Table::Table(void)
{
	Init();
}

Table::~Table(void)
{
	Destroy();
}

bool Table::Create(DWORD dwCodePage)
{
	m_dwCodePage = dwCodePage;

	return true;
}

void Table::Destroy()
{
	Reset();
}

void Table::Init()
{
	m_mapTableList.clear();

	::ZeroMemory(m_wszXmlFileName, sizeof(m_wszXmlFileName));
}

void Table::Reset()
{
	for (TABLEIT it = m_mapTableList.begin(); it != m_mapTableList.end(); it++)
	{
		delete it->second;
	}

	m_mapTableList.clear();

	::ZeroMemory(m_wszXmlFileName, sizeof(m_wszXmlFileName));
}

bool Table::LoadFromXml(char* pszFileName, bool bReload)
{
	WCHAR* pwszFileName = MB2WC(pszFileName);
	if (NULL == pwszFileName)
	{
		return false;
	}

	bool bResult = LoadFromXml(pwszFileName, bReload);

	CleanUpHeapStringW(pwszFileName);

	return bResult;
}

bool Table::LoadFromXml(WCHAR* pwszFileName, bool bReload)
{
	if (NULL == pwszFileName)
	{
		return false;
	}

	XMLDoc doc;
	doc.Create();

	BSTR bstrErrorReasonString;
	LONG lLineNumber = 0;

	if (false == doc.Load(pwszFileName, &lLineNumber, &bstrErrorReasonString))
	{
		doc.Destroy();
		Table::CallErrorCallbackFunction("[File] : %S REASON[%S] LineNumber[%u])", pwszFileName, bstrErrorReasonString, lLineNumber);
		::SysFreeString(bstrErrorReasonString);
		_ASSERTE(!"Table data Load Fail");
		return false;
	}

	return InitializeFromXmlDoc(&doc, pwszFileName, bReload);
}

DWORD Table::HexToDec(WCHAR* pwszHexString)
{
	if (NULL == pwszHexString)
	{
		return 0;
	}

	DWORD dwValue = 0;

	bool bLoop = true;
	do
	{
		if (L'0' <= *pwszHexString && L'9' >= *pwszHexString)
		{
			dwValue = dwValue * 16;
			dwValue = dwValue + (*pwszHexString - L'0');
		}
		else if (L'a' <= *pwszHexString && L'f' >= *pwszHexString)
		{
			dwValue = dwValue * 16;
			dwValue = dwValue + 10 + (*pwszHexString - L'a');
		}
		else if (L'A' <= *pwszHexString && L'F' >= *pwszHexString)
		{
			dwValue = dwValue * 16;
			dwValue = dwValue + 10 + (*pwszHexString - L'A');
		}
		else
		{
			break;
		}

		pwszHexString++;
	} while (bLoop != false);

	return dwValue;
}

bool Table::InitializeFromXmlDoc(XMLDoc* pXmlDoc, WCHAR* pwszFileName, bool bReload)
{
	if (NULL == pXmlDoc)
	{
		return false;
	}

	if (false == bReload)
	{
		Reset();
	}

	// Stores the XML file name.
	{
		wcsncpy_s<_countof(m_wszXmlFileName)>(m_wszXmlFileName, pwszFileName, _countof(m_wszXmlFileName) - 1);
		m_wszXmlFileName[_countof(m_wszXmlFileName) - 1] = L'\0';
	}

	BSTR rowXPathFormat;
	rowXPathFormat = ::SysAllocString(L"/dataroot/%s[%d]");
	WCHAR wszXPath[MAX_UNICODE_XPATH_LENGTH + 1];

	DWORD dwSheetIndex = 0;
	WCHAR** ppwszSheetList = GetSheetListInWChar();

	while (NULL != ppwszSheetList[dwSheetIndex])
	{
		swprintf_s<_countof(wszXPath)>(wszXPath, rowXPathFormat, ppwszSheetList[dwSheetIndex], 0);

		IXMLDOMNode* pAttributeNameNode = NULL;
		pAttributeNameNode = pXmlDoc->SelectSingleNode(wszXPath);
		if (NULL == pAttributeNameNode)
		{
			::SysFreeString(rowXPathFormat);

			return false;
		}
		IXMLDOMNodeList* pAttributeNameNodeList = NULL;
		HRESULT hResult = pAttributeNameNode->get_childNodes(&pAttributeNameNodeList);
		if (S_OK != hResult)
		{
			pAttributeNameNode->Release();
			::SysFreeString(rowXPathFormat);

			return false;
		}

		long length = 0;
		if (FAILED(pAttributeNameNodeList->get_length(&length)))
		{
			pAttributeNameNodeList->Release();
			pAttributeNameNode->Release();
			::SysFreeString(rowXPathFormat);

			return false;
		}

		BSTR bstr = NULL;
		std::map<long, std::wstring> mapAttributeMapping;

		// Retrieves field names.
		for (long i = 0; i<length; i++)
		{
			IXMLDOMNode* pCellNode = NULL;
			IXMLDOMNode* pDataNode = NULL;
			if (FAILED(pAttributeNameNodeList->get_item(i, &pCellNode)))
			{
				pAttributeNameNode->Release();
				pAttributeNameNodeList->Release();
				::SysFreeString(rowXPathFormat);

				return false;
			}
			if (NULL == pCellNode)
				break;

			if (FAILED(pCellNode->get_firstChild(&pDataNode)))
			{
				pCellNode->Release();
				pAttributeNameNode->Release();
				pAttributeNameNodeList->Release();
				::SysFreeString(rowXPathFormat);

				return false;
			}
			if (NULL == pDataNode)
			{
				Table::CallErrorCallbackFunction("[File] : %S\n[Error] : A field name may be null.(Index : %d)", pwszFileName, i);

				pCellNode->Release();
				break;
			}

			if (FAILED(pDataNode->get_text(&bstr)))
			{
				::SysFreeString(bstr);
				pDataNode->Release();
				pCellNode->Release();
				pAttributeNameNode->Release();
				pAttributeNameNodeList->Release();
				::SysFreeString(rowXPathFormat);

				return false;
			}

			mapAttributeMapping.insert(std::pair<long, std::wstring>(i, std::wstring(bstr)));

			::SysFreeString(bstr);
			pDataNode->Release();
			pCellNode->Release();
		}
		pAttributeNameNode->Release();
		pAttributeNameNodeList->Release();

		int iRowIndex = 1;

		// Retrieves data.
		bool bLoop = true;
		do
		{
			IXMLDOMNode* pRoot = NULL;
			IXMLDOMNodeList* pRow = NULL;
			swprintf_s<_countof(wszXPath)>(wszXPath, rowXPathFormat, ppwszSheetList[dwSheetIndex], iRowIndex);

			pRoot = pXmlDoc->SelectSingleNode(wszXPath);
			if (NULL == pRoot)
			{
				break;
			}

			HRESULT hResult = pRoot->get_childNodes(&pRow);
			if (S_OK != hResult)
			{
				pRoot->Release();
				::SysFreeString(rowXPathFormat);

				return false;
			}

			void* pvTable = AllocNewTable(ppwszSheetList[dwSheetIndex], m_dwCodePage);
			if (NULL == pvTable)
			{
				pRow->Release();
				::SysFreeString(rowXPathFormat);

				return false;
			}

			bool bIsEndOfSheet = false;

			for (long i = 0; i<length; i++)
			{
				IXMLDOMNode* pCellNode = NULL;
				IXMLDOMNode* pDataNode = NULL;

				if (FAILED(pRow->get_item(i, &pCellNode)))
				{
					DeallocNewTable(pvTable, ppwszSheetList[dwSheetIndex]);
					pRow->Release();
					::SysFreeString(rowXPathFormat);

					return false;
				}

				if (NULL == pCellNode)
				{
					if (0 == i)
					{
						bIsEndOfSheet = true;
						break;
					}
					else
					{
						continue;
					}
				}

				std::map<long, std::wstring>::iterator mapIt;
				mapIt = mapAttributeMapping.find(i);
				if (mapAttributeMapping.end() == mapIt)
				{
					DeallocNewTable(pvTable, ppwszSheetList[dwSheetIndex]);
					pCellNode->Release();
					pRow->Release();
					::SysFreeString(rowXPathFormat);

					return false;
				}

				if (FAILED(pCellNode->get_firstChild(&pDataNode)))
				{
					Table::CallErrorCallbackFunction("[File] : %S\n[Error] : Table data is null.(Row Index : %d, Field Name = %S)", pwszFileName, iRowIndex - 1, (mapIt->second).c_str());

					DeallocNewTable(pvTable, ppwszSheetList[dwSheetIndex]);
					pCellNode->Release();
					pRow->Release();
					::SysFreeString(rowXPathFormat);

					return false;
				}

				if (NULL == pDataNode)
				{
					Table::CallErrorCallbackFunction("[File] : %S\n[Error] : Table data is null.(Row Index : %d, Field Name = %S)", pwszFileName, iRowIndex - 1, (mapIt->second).c_str());

					pCellNode->Release();

					if (0 == i)
					{
						DeallocNewTable(pvTable, ppwszSheetList[dwSheetIndex]);
						bIsEndOfSheet = true;
						break;
					}
					else
					{
						continue;
					}
				}

				if (FAILED(pDataNode->get_text(&bstr)))
				{
					pDataNode->Release();
					pCellNode->Release();
					DeallocNewTable(pvTable, ppwszSheetList[dwSheetIndex]);
					pRow->Release();
					::SysFreeString(rowXPathFormat);

					return false;
				}

				SetTableData(pvTable, ppwszSheetList[dwSheetIndex], &(mapIt->second), bstr);

				::SysFreeString(bstr);
				pDataNode->Release();
				pCellNode->Release();
			}
			pRow->Release();

			if (false == bIsEndOfSheet)
			{
				if (false == AddTable(pvTable, bReload))
				{
					DeallocNewTable(pvTable, ppwszSheetList[dwSheetIndex]);
				}

				iRowIndex++;
			}
			else
			{
				bLoop = false;
			}
		} while (false != bLoop);

		dwSheetIndex++;
	}

	::SysFreeString(rowXPathFormat);

	return true;
}

char Table::READ_CHAR(BSTR bstr, const WCHAR* pwszFieldName, BYTE chInvalidValue)
{
	if (CheckInvalidValue(bstr))
	{
		return chInvalidValue;
	}

	INT64 nTemp = _wtoi64(bstr);
	if (nTemp < -128 || nTemp > 127)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\n[Error] : The value exceeds the max. value of the field!(Field Name = %s, Field Type = char, Value = %s)", m_wszXmlFileName, pwszFieldName, bstr);
		return chInvalidValue;
	}

	return (char)nTemp;
}

BYTE Table::READ_BYTE(BSTR bstr, const WCHAR* pwszFieldName, BYTE byInvalidValue)
{
	if (CheckInvalidValue(bstr))
	{
		return byInvalidValue;
	}

	DWORD dwTemp = (DWORD)_wtoi64(bstr);
	if (dwTemp >= INVALID_BYTE)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\n[Error] : The value exceeds the max. value of the field!(Field Name = %s, Field Type = BYTE, Value = %s)", m_wszXmlFileName, pwszFieldName, bstr);
		return byInvalidValue;
	}

	return (BYTE)dwTemp;
}

WORD Table::READ_WORD(BSTR bstr, const WCHAR* pwszFieldName, WORD wInvalidValue)
{
	if (CheckInvalidValue(bstr))
	{
		return wInvalidValue;
	}

	DWORD dwTemp = (DWORD)_wtoi64(bstr);
	if (dwTemp >= INVALID_WORD)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\n[Error] : The value exceeds the max. value of the field!(Field Name = %s, Field Type = WORD, Value = %s)", m_wszXmlFileName, pwszFieldName, bstr);
		return wInvalidValue;
	}

	return (WORD)dwTemp;
}

float Table::READ_FLOAT(BSTR bstr, const WCHAR* pwszFieldName, float fInvalidValue)
{
	if (CheckInvalidValue(bstr))
	{
		return fInvalidValue;
	}

	double fTemp = _wtof(bstr);
	if (fTemp >= INVALID_FLOAT)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\n[Error] : The value exceeds the max. value of the field!(Field Name = %s, Field Type = float, Value = %s)", m_wszXmlFileName, pwszFieldName, bstr);
		return fInvalidValue;
	}

	return (float)fTemp;
}

bool Table::READ_BOOL(BSTR bstr, const WCHAR* pwszFieldName, bool bInvalidlValue)
{
	if (CheckInvalidValue(bstr))
	{
		return bInvalidlValue;
	}

	DWORD dwTemp = (DWORD)_wtoi64(bstr);
	if (dwTemp > (DWORD)true)
	{
		Table::CallErrorCallbackFunction(L"[File] : %s\n[Error] : The value exceeds the max. value of the field!(Field Name = %s, Field Type = bool, Value = %s)", m_wszXmlFileName, pwszFieldName, bstr);
		return bInvalidlValue;
	}


	return (bool)(wcscmp(L"0", bstr) ? true : false);
}

bool Table::READ_STR(std::string & rDest, BSTR bstr, const char * lpszInvalidValue)
{
	if (true == CheckInvalidValue(bstr))
	{
		rDest = lpszInvalidValue;
		return true;
	}

	int nStrLen = WideCharToMultiByte(GetACP(), 0, bstr, -1, NULL, 0, NULL, NULL);
	char * pBuffer = new char[nStrLen];
	if (pBuffer)
	{
		WideCharToMultiByte(GetACP(), 0, bstr, -1, pBuffer, nStrLen, NULL, NULL);
		rDest = pBuffer;
		delete[] pBuffer;
	}
	else
	{
		_ASSERT(0);

		return false;
	}

	return true;
}

bool Table::READ_STR(std::wstring & rDest, BSTR bstr, const WCHAR * lpwszInvalidValue)
{
	if (true == CheckInvalidValue(bstr))
	{
		rDest = lpwszInvalidValue;
		return false;
	}

	rDest = bstr;

	return true;
}

bool Table::READ_STRING(BSTR bstr, char* pszBuffer, DWORD dwBufferLength, const char* pszInvalidValue)
{
	if (NULL == pszBuffer || NULL == pszInvalidValue)
	{
		return false;
	}

	if (false == CheckInvalidValue(bstr))
	{
		int nRequiredBytes = ::WideCharToMultiByte(m_dwCodePage, 0, bstr, -1, NULL, 0, NULL, NULL);
		if (dwBufferLength < (DWORD)nRequiredBytes)
		{
			if (NULL != m_pfnErrorCallback)
			{
				CallErrorCallbackFunction(L"[File] : %s\n[Error] : The string[%s]'s length[%u] is bigger than the max. length[%u]",
					m_wszXmlFileName, bstr, (DWORD)nRequiredBytes, dwBufferLength - 1);
			}

			return false;
		}
		else
		{
			::WideCharToMultiByte(m_dwCodePage, 0, bstr, -1, pszBuffer, dwBufferLength, NULL, NULL);
		}
	}
	else
	{
		strcpy_s(pszBuffer, dwBufferLength, pszInvalidValue);
	}

	return true;
}

bool Table::READ_STRINGW(BSTR bstr, WCHAR* pwszBuffer, DWORD dwBufferLength, const WCHAR* pwszInvalidValue)
{
	if (NULL == pwszBuffer || NULL == pwszInvalidValue)
	{
		return false;
	}

	if (false == CheckInvalidValue(bstr))
	{
		if (dwBufferLength < (wcslen(bstr) + 1))
		{
			if (NULL != m_pfnErrorCallback)
			{
				CallErrorCallbackFunction(L"[File] : %s\n[Error] : The string[%s]'s length[%u] is bigger than the max. length[%u]",
					m_wszXmlFileName, bstr, wcslen(bstr), dwBufferLength - 1);
			}

			return false;
		}
		else
		{
			wcscpy_s(pwszBuffer, dwBufferLength, bstr);
		}
	}
	else
	{
		wcscpy_s(pwszBuffer, dwBufferLength, pwszInvalidValue);
	}

	return true;
}

void Table::CheckNegativeInvalid(const wchar_t* pwszFormatString, BSTR bstr)
{
	if (CheckInvalidValue(bstr))
	{
		(void)pwszFormatString;
		_ASSERTE(!"The field can not put a @.");
	}
}

void Table::SetErrorCallbackFunction(Dbo_TableErrorCallback pfnErrorCallback, void* pvErrorCallbackArg)
{
	m_pfnErrorCallback = pfnErrorCallback;
	m_pvErrorCallbackArg = pvErrorCallbackArg;
}

void Table::CallErrorCallbackFunction(char* pszFormatString, ...)
{
	if (NULL != m_pfnErrorCallback)
	{
		char szErrorMessage[1024 + 1];

		va_list args;
		va_start(args, pszFormatString);
		vsprintf_s<_countof(szErrorMessage)>(szErrorMessage, pszFormatString, args);
		va_end(args);

		m_pfnErrorCallback(szErrorMessage, m_pvErrorCallbackArg);
	}
}

void Table::CallErrorCallbackFunction(WCHAR* pwszFormatString, ...)
{
	if (NULL != m_pfnErrorCallback)
	{
		WCHAR wszErrorMessage[1024 + 1];
		char szErrorMessage[1024 + 1];

		va_list args;
		va_start(args, pwszFormatString);
		vswprintf_s<_countof(wszErrorMessage)>(wszErrorMessage, pwszFormatString, args);
		va_end(args);

		::WideCharToMultiByte(::GetACP(), 0, wszErrorMessage, -1, szErrorMessage, _countof(szErrorMessage), NULL, NULL);
		m_pfnErrorCallback(szErrorMessage, m_pvErrorCallbackArg);
	}
}
