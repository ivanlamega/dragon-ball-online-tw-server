#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <set>
#include <exception>
#include <iostream>
#include <Singleton.h>

class XmlParser
{
public:
	bool loadFile(std::string filename);
	std::string GetStr(std::string fieldname, std::string valuename);
	int GetInt(std::string fieldname, std::string valuename);
	void Free();
	std::string GetChildStr(std::string child, std::string fieldname, std::string valuename);
	int GetChildInt(std::string child, std::string fieldname, std::string valuename);

private:
	std::string filename;
	boost::property_tree::ptree cur;
	boost::property_tree::ptree doc;
};

#define sXmlParser AKCore::Singleton<XmlParser>::Instance()