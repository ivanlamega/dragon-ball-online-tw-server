#include <oleauto.h>
#include <MsXml2.h>

enum EMaxConstants
{
	MAX_UNICODE_FILE_NAME_LENGTH = 128,
	MAX_UNICODE_XPATH_LENGTH = 128,
	MAX_ATTRIBUTE_NAME_IN_WCHAR = 1024
};

class XMLDoc
{
public:
	XMLDoc();
	virtual ~XMLDoc();

	bool Create();
	bool Destroy();

	bool Load(WCHAR* pwszFileName, LONG* lLineNumber, BSTR* bstrErrorReasonString);
	bool Load(WCHAR* pwszFileName);
	bool Load(char* pszFileName);

	bool LoadXML(char* szXMLBuffer);
	bool LoadXML(WCHAR* wszXMLBuffer);

	IXMLDOMNode* SelectSingleNode(WCHAR* pwszXPath);
	IXMLDOMNode* SelectSingleNode(char* pszXPath);

	IXMLDOMNodeList* SelectNodeList(WCHAR* pwszXPath);
	IXMLDOMNodeList* SelectNodeList(char* pszXPath);

	bool GetTextWithAttributeName(IXMLDOMNode* pNode, WCHAR* pwszAttributeName, WCHAR* pwszResultText, int nBufferSizeInWChars);
	bool GetTextWithAttributeName(IXMLDOMNode* pNode, char* pszAttributeName, char* pszResultText, int nBufferSizeInBytes);

	bool GetDataWithXPath(WCHAR* pwszXPath, WCHAR* pwszResultData, int nBufferSizeInWChars);
	bool GetDataWithXPath(char* pszXPath, char* pszResultData, int nBufferSizeInBytes);

	IXMLDOMDocument* GetDocument(void);
	bool SetIndent(WCHAR* szIndentFileName);

protected:
	void Init();
	static DWORD m_dwNumberOfCreatedInstances;
	IXMLDOMDocument* m_pXMLDocument;
	bool m_bIsFileLoaded;
};