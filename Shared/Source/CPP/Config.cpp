#include "Config.h"

Config::Config(const char* rname)
{
	rootname = _strdup(rname);
	filename = new char[MAX_PATH];
	sprintf_s(filename, MAX_PATH, "%sConfig.xml", rootname);
}

Config::~Config()
{
	Free();
}

void Config::Init()
{
	doc = std::make_unique<xmlDocPtr>(xmlParseFile(filename));
}

void Config::Free()
{
	xmlFreeDoc(*doc.get());
	doc.release();
}

int Config::GetInt(char* fieldname)
{
	return GetInt(fieldname, "value");
}

int Config::GetInt(char* fieldname, char* valuename)
{
	Init();
	if (doc)
	{
		root = xmlDocGetRootElement(*doc.get());
		if (xmlStrcmp(root->name, (const xmlChar*)rootname) != 0)
		{
			Free();
			sLog->outError("Error on Loading Config xml File, Root node not found (%s)\n", rootname);
		}

		for (node = root->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)fieldname) == 0)
			{
				xmlChar* xres = xmlGetProp(node, (const xmlChar*)valuename);
				if (xres)
				{
					Free();
					return atoi((const char*)xres);
					xmlFree(xres);
				}
			}
		}
		Free();
		return -1;
	}
	else
	{
		sLog->outError("Error on Loading Config xml File\n");
		Free();
		return -1;
	}
}

char* Config::GetStr(char* fieldname)
{
	return GetStr(fieldname, "value");
}

char* Config::GetStr(char* fieldname, char* valuename)
{
	Init();
	if (doc)
	{
		root = xmlDocGetRootElement(*doc.get());
		if (xmlStrcmp(root->name, (const xmlChar*)rootname) != 0) {
			Free();
			sLog->outError("Error on Loading Config xml File, Root node not found (%s)\n", rootname);
		}

		for (node = root->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)fieldname) == 0)
			{
				xmlChar* xres = xmlGetProp(node, (const xmlChar*)valuename);
				if (xres)
				{
					Free();
					return (char*)xres;
					xmlFree(xres);
				}
			}
		}
		return "";
	}
	else
	{
		sLog->outError("Error on Loading Config xml File\n");
		Free();
		return "";
	}
}

int Config::GetChildInt(char* child, char* fieldname)
{
	return GetChildInt(child, fieldname, "value");
}

int Config::GetChildInt(char* child, char* fieldname, char* valuename)
{
	Init();
	if (doc)
	{
		root = xmlDocGetRootElement(*doc.get());
		if (xmlStrcmp(root->name, (const xmlChar*)rootname) != 0) {
			Free();
			sLog->outError("Error on Loading Config xml File, Root node not found (%s)\n", rootname);
		}

		for (node = root->children; node; node = node->next)
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
							return atoi((const char*)xres);
							xmlFree(xres);
						}
					}
				}
			}
		}
		return -1;
	}
	else
	{
		sLog->outError("Error on Loading Config xml File\n");
		Free();
		return -1;
	}
}

char* Config::GetChildStr(char* child, char* fieldname)
{
	return GetChildStr(child, fieldname, "value");
}

char* Config::GetChildStr(char* child, char* fieldname, char* valuename)
{
	Init();
	if (doc)
	{
		root = xmlDocGetRootElement(*doc.get());
		if (xmlStrcmp(root->name, (const xmlChar*)rootname) != 0) {
			Free();
			sLog->outError("Error on Loading Config xml File, Root node not found (%s)\n", rootname);
		}

		for (node = root->children; node; node = node->next)
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
							return (char*)xres;
							xmlFree(xres);
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
		sLog->outError("Error on Loading Config xml File\n");
		Free();
		return "";
	}
}