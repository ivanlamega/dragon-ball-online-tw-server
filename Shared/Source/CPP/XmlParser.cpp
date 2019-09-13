#include <XmlParser.h>
#include <Logger.h>

void XmlParser::Free()
{
	if (doc != NULL)
		xmlFreeDoc(doc);
}
bool XmlParser::loadFile(char* _filename)
{
	filename = _filename;
	std::string ext = filename;
	ext.append(".xml");
	doc = xmlParseFile(ext.c_str());
	if (doc == NULL)
	{
		sLog.outError("Document not parsed successfully : %s", _filename);
		return false;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL)
	{
		sLog.outError("Document root not valid : %s", _filename);
		xmlFreeDoc(doc);
		return false;
	}
	return true;
}
int XmlParser::GetInt(char* fieldname, char* valuename)
{
	if (loadFile((char*)filename.c_str()) == false) // check for getter etc
		return false;
	if (doc)
	{
		cur = xmlDocGetRootElement(doc);
		if (xmlStrcmp(cur->name, (const xmlChar*)filename.c_str()) != 0)
		{
			Free();
			sLog.outError("Error on Loading Config xml File, Root node not found (%s)", filename);
			return NULL;
		}
		for (node = cur->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)fieldname) == 0)
			{
				xmlChar* xres = xmlGetProp(node, (const xmlChar*)valuename);
				if (xres)
				{
					Free();
					int val = atoi((const char*)xres);
					xmlFree(xres);
					return val;
				}
			}
		}
		Free();
		return -1;
	}
	else
	{
		sLog.outError("Error on Loading Config xml File");
		Free();
		return -1;
	}
}
char* XmlParser::GetStr(char* fieldname, char* valuename)
{
	if (loadFile((char*)filename.c_str()) == false) // check for getter etc
		return false;
	if (doc != NULL)
	{
		cur = xmlDocGetRootElement(doc);
		if (xmlStrcmp(cur->name, (const xmlChar*)filename.c_str()) != 0)
		{
			Free();
			sLog.outError("Error on Loading Config xml File, Root node not found (%s)", filename);
			return NULL;
		}
		for (node = cur->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)fieldname) == 0)
			{
				xmlChar* xres = xmlGetProp(node, (const xmlChar*)valuename);
				if (xres)
				{
					Free();
					std::string val = (char*)xres;
					xmlFree(xres);
					return (char*)val.c_str();
				}
			}
		}
		return "";
	}
	else
	{
		sLog.outError("Error on Loading Config xml File");
		Free();
		return "";
	}
}
char* XmlParser::GetChildStr(char* child, char* fieldname, char* valuename)
{
	if (loadFile((char*)filename.c_str()) == false) // check for getter etc
		return false;
	if (doc)
	{
		cur = xmlDocGetRootElement(doc);
		if (xmlStrcmp(cur->name, (const xmlChar*)filename.c_str()) != 0) {
			Free();
			sLog.outError("Error on Loading Config xml File, Root node not found (%s)", filename);
		}

		for (node = cur->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)child) == 0)
			{
				xmlNodePtr cnode;
				for (cnode = node->children; cnode; cnode = cnode->next)
				{
					if (xmlStrcmp(cnode->name, (const xmlChar*)fieldname) == 0)
					{
						xmlChar* xres = xmlGetProp(cnode, (const xmlChar*)valuename);
						if (xres)
						{
							Free();
							std::string val = (char*)xres;
							xmlFree(xres);
							return (char*)val.c_str();
						}
					}
				}
			}
		}
		Free();
		return "";
	}
	else
	{
		sLog.outError("Error on Loading Config xml File");
		Free();
		return "";
	}
}
int XmlParser::GetChildInt(char* child, char* fieldname, char* valuename)
{
	if (loadFile((char*)filename.c_str()) == false) // check for getter etc
		return false;
	if (doc)
	{
		cur = xmlDocGetRootElement(doc);
		if (xmlStrcmp(cur->name, (const xmlChar*)filename.c_str()) != 0) {
			Free();
			sLog.outError("Error on Loading Config xml File, Root node not found (%s)", filename);
		}

		for (node = cur->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)child) == 0)
			{
				xmlNodePtr cnode;
				for (cnode = node->children; cnode; cnode = cnode->next)
				{
					if (xmlStrcmp(cnode->name, (const xmlChar*)fieldname) == 0)
					{
						xmlChar* xres = xmlGetProp(cnode, (const xmlChar*)valuename);
						if (xres)
						{
							Free();
							int val = atoi((const char*)xres);
							xmlFree(xres);
							return val;
						}
					}
				}
			}
		}
		return -1;
	}
	else
	{
		sLog.outError("Error on Loading Config xml File");
		Free();
		return -1;
	}
}