// Rdf2Xml.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Rdf2XmlHelper.h"
#include "Rdf2Xml.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CRdf2XmlHelper rdf2XmlHelper;

	char szInPath[MAX_PATH] = "data";
	char szOutPath[MAX_PATH] = "output";
	char szConvType[20] = "rdf2xml";
	
	// Parse command-line parameters
	int iInPath = 0;
	int iOutPath = 0;
	int iConvType = 0;

	if (argc == 3 || argc == 5 || argc == 7)
	{
		for (int i = 1; i < argc - 1; i = i + 2)
		{
			if (stricmp((const char*)argv[i], "-i") == 0)
			{
				iInPath = i;
			}
			
			if (stricmp((const char*)argv[i], "-o") == 0)
			{
				iOutPath = i;
			}

			if (stricmp((const char*)argv[i], "-t") == 0)
			{
				iConvType = i;
			}
		}
	}


	if (iInPath > 0)
	{
		strncpy(szInPath, (const char*)argv[iInPath + 1], sizeof(szInPath) - 1);
	}

	if (iOutPath > 0)
	{
		strncpy(szOutPath, (const char*)argv[iOutPath + 1], sizeof(szOutPath) - 1);
	}

	if (iConvType > 0)
	{
		strncpy(szConvType, (const char*)argv[iConvType + 1], sizeof(szConvType) - 1);
	}
	

	printf("The import path is: %s\nThe output path is: %s\nThe conversion type is: %s\n\n", szInPath, szOutPath, szConvType);

	eLOADING_METHOD loadingMethod = eLOADING_METHOD::LOADING_METHOD_BINARY;

	if (stricmp(szConvType, "xml2rdf") == 0 || stricmp(szConvType, "xml2edf") == 0)
	{
		loadingMethod = eLOADING_METHOD::LOADING_METHOD_XML;
	}

	if (stricmp(szConvType, "edf2xml") == 0)
	{
		loadingMethod = eLOADING_METHOD::LOADING_METHOD_SECURED_BINARY;
	}

	if (!rdf2XmlHelper.CreateTableContainer(szInPath, loadingMethod))
	{
		printf("Failed to load tables from RDF files.\n");

		return 0;
	}

	
	if (loadingMethod != eLOADING_METHOD::LOADING_METHOD_XML)
	{
		//rdf2XmlHelper.SaveToXml_MobTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_ItemTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_SkillTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_TextAllTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_FormulaTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_PcTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_ExpTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_QuestTextTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_PortalTable(szOutPath);
		rdf2XmlHelper.SaveToXml_TitleTable(szOutPath);

		//for (int i = 0; i < 1000001; ++i)
		//{
		//	rdf2XmlHelper.SaveToXml_MobSpawnTable(szOutPath, i);
		//	rdf2XmlHelper.SaveToXml_NPCSpawnTable(szOutPath, i);
		//	rdf2XmlHelper.SaveToXml_ObjectTable(szOutPath, i);
		//}
		//rdf2XmlHelper.SaveToXml_LandMarkTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_WorldMapTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_WorldTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_WorldPlayTable(szOutPath); // We dont have this stupid table.. No big deal. We have gotten by fine without it -- Kalisto
		//rdf2XmlHelper.SaveToXml_WorldZoneTable(szOutPath); // Errors out sometimes cause of the wszNameText I think it was bigger but not? No way to explain this other than its fixed -- Kalisto
		//rdf2XmlHelper.SaveToXml_DynamicObjectTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_VehicleTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_MobMovePatternTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_DirectionLinkTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_ScriptLinkTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_QuestNarrationTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_BasicDropTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_EachDropTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_NormalDropTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_ExcellentDropTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_LegendaryDropTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_TypeDropTable(szOutPath);
		//rdf2XmlHelper.SaveToXml_SuperiorDropTable(szOutPath);
	//	rdf2XmlHelper.SaveToXml_ItemOptionTable(szOutPath);
	//	rdf2XmlHelper.SaveToXml_SystemEffectTable(szOutPath);
	}
	else
	{
		//rdf2XmlHelper.SaveToBinary_MobTable(szOutPath);
		//rdf2XmlHelper.SaveToBinary_ItemTable(szOutPath);
		//rdf2XmlHelper.SaveToBinary_SkillTable(szOutPath);
		//rdf2XmlHelper.SaveToBinary_TextAllTable(szOutPath);
		//rdf2XmlHelper.SaveToBinary_ObjectTable(szOutPath);
		//rdf2XmlHelper.SaveToBinary_PcTable(szOutPath);
		//rdf2XmlHelper.SaveToBinary_ExpTable(szOutPath);
		//rdf2XmlHelper.SaveToBinary_QuestTextTable(szOutPath);
				
	}

	return 0;
}