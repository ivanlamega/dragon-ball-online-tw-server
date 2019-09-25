#include <XmlParser2/XmlParser2.h>
#include <Logger.h>

void XmlParser::Free()
{
	doc.clear();
}

bool XmlParser::loadFile(std::string _filename)
{
	filename = _filename;
	std::string ext = filename;
	ext.append(".xml");
	boost::property_tree::read_xml(ext, doc);

	if (doc.empty())
	{
		sLog.outError("Document not parsed successfully : %s", _filename);
		return false;
	}

	cur = doc.get_child(_filename);

	if (cur.empty())
	{
		sLog.outError("Document root not valid : %s", _filename);
		Free();
		return false;
	}

	return true;
}

int XmlParser::GetInt(std::string fieldname, std::string valuename)
{
	if (cur.empty())
	{
		sLog.outError("Error on Loading Config xml File");
		Free();
		return -1;
	}

	return cur.get<int>(fieldname + ".<xmlattr>." + valuename);
}

std::string XmlParser::GetStr(std::string fieldname, std::string valuename)
{
	if (cur.empty())
	{
		sLog.outError("Error on Loading Config xml File");
		Free();
		return "";
	}

	return cur.get<std::string>(fieldname + ".<xmlattr>." + valuename);
}

std::string XmlParser::GetChildStr(std::string child, std::string fieldname, std::string valuename)
{
	if (cur.empty())
	{
		sLog.outError("Error on Loading Config xml File");
		Free();
		return "";
	}

	return cur.get<std::string>(child + "." + fieldname + ".<xmlattr>." + valuename);
}

int XmlParser::GetChildInt(std::string child, std::string fieldname, std::string valuename)
{
	if (cur.empty())
	{
		sLog.outError("Error on Loading Config xml File");
		Free();
		return -1;
	}

	return cur.get<int>(child + "." + fieldname + ".<xmlattr>." + valuename);
}