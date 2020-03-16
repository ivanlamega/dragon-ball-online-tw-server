#include <winsock2.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <wincrypt.h>
#include <comdef.h>
#include <atlbase.h>
#include <vector>
#include <cstdint>
#include "Rdf2XmlHelper.h"
#include "NtlBitFlagManager.h"
#include "FileSerializer.h"
#include "NtlStringHandler.h"
#include "TableFileNameList.h"
//Tables for Encoding/Decrypting .*df files
#include "Table.h"
#include "MobTable.h"
#include "ItemTable.h"
#include "SkillTable.h"
#include "TextAllTable.h"
#include "ObjectTable.h"
#include "FormulaTable.h"
#include "ItemEnchantTable.h"
#include "PCTable.h"
#include "ExpTable.h"
#include "QuestTextDataTable.h"
#include "PortalTable.h"
#include "WorldTable.h"
#include "SpawnTable.h"
#include "LandMarkTable.h"
#include "DynamicObjectTable.h"
#include "WorldZoneTable.h"
#include "WorldPlayTable.h"
#include "WorldMapTable.h"
#include "VehicleTable.h"
#include "HTBSetTable.h"
#include "MobMovePatternTable.h"

#include "DirectionLinkTable.h"
#include "ScriptLinkTable.h"
#include "QuestNarrationTable.h"

#include "BasicDropTable.h"
#include "EachDropTable.h"
#include "TypeDropTable.h"
#include "BasicDropTable.h"
#include "NormalDropTable.h"
#include "ExcellentDropTable.h"
#include "SuperiorDropTable.h"
#include "LegendaryDropTable.h"
#include "ItemOptionTable.h"
#include "SystemEffectTable.h"
#include "CharTitleTable.h"

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


// Add root node
int AppendRootW(MSXML2::IXMLDOMDocumentPtr & pDoc,
			    MSXML2::IXMLDOMElementPtr & pRoot,
				WCHAR * pRootName)
{
	BSTR bstrBuffer;

	bstrBuffer = SysAllocString(pRootName);

	// Create the root node
	pDoc->raw_createElement(bstrBuffer, &pRoot);
	
	// Append the root node
	pDoc->raw_appendChild(pRoot, NULL);

	MSXML2::IXMLDOMProcessingInstructionPtr pXMLProcessingNode = pDoc->createProcessingInstruction("xml", "version='1.0'");

	_variant_t vtObject;
	vtObject.vt = VT_DISPATCH;
	vtObject.pdispVal = pRoot;
	vtObject.pdispVal->AddRef();

	pDoc->insertBefore(pXMLProcessingNode, vtObject);

	SysFreeString(bstrBuffer);

	return 0;
}


// Initialize a XML document
HRESULT InitXmlDOC(MSXML2::IXMLDOMDocumentPtr & pDoc, MSXML2::IXMLDOMElementPtr & pRoot)
{
	HRESULT hr;

	hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument40));	

	if (FAILED(hr))
	{
		printf("Failed to create XML Document.\n");
	}

	AppendRootW(pDoc, pRoot, L"dataroot"); 

	return E_NOTIMPL;
}

int AppendBlockElementW(MSXML2::IXMLDOMDocumentPtr & pDoc,
	MSXML2::IXMLDOMElementPtr & pRoot,
	MSXML2::IXMLDOMElementPtr & pBlockNode,
	WCHAR * pNodeName,
	WCHAR * pNodeValue)
{
	// Add a line feed
	pRoot->appendChild(pDoc->createTextNode("\n\t"));
	BSTR bstrBuffer;

	// Create child node
	bstrBuffer = SysAllocString(pNodeName);
	pDoc->raw_createElement(bstrBuffer, &pBlockNode);

	SysFreeString(bstrBuffer);

	// Add child text for the child node
	if (NULL != pNodeValue)
	{
		bstrBuffer = SysAllocString(pNodeValue);
		pBlockNode->Puttext(bstrBuffer);

		SysFreeString(bstrBuffer);
	}

	// Append the child node as the sub-node of pRoot
	pRoot->appendChild(pBlockNode);

	return 0;
}


// Add a child node
int AppendElementW(MSXML2::IXMLDOMDocumentPtr & pDoc,
					MSXML2::IXMLDOMElementPtr & pRoot,
					WCHAR * pNodeName, 
					WCHAR * pNodeValue)
{
	// Add a line feed
	pRoot->appendChild(pDoc->createTextNode("\n\t\t"));
	BSTR bstrBuffer;


	MSXML2::IXMLDOMElementPtr childNode;  

	// Create child node
	bstrBuffer = SysAllocString(pNodeName);
	pDoc->raw_createElement(bstrBuffer, &childNode); 
	
	SysFreeString(bstrBuffer);
	
	
	// Add child text for the child node
	if (NULL != pNodeValue)
	{
		bstrBuffer = SysAllocString(pNodeValue);
		childNode->Puttext(bstrBuffer);
		//bstrBuffer = L"";
		SysFreeString(bstrBuffer);
	}

	// Append the child node as the sub-node of pRoot
	pRoot->appendChild(childNode);

	childNode.Release();

	return 0;
}

// Add a child node
int AppendElementW_f(MSXML2::IXMLDOMDocumentPtr & pDoc,
	MSXML2::IXMLDOMElementPtr & pRoot,
	WCHAR * pNodeName,
	float fNodeValue)
{
	WCHAR wszText[200] = { 0 };

	_snwprintf(wszText, 200, L"%f", fNodeValue);

	return AppendElementW(pDoc, pRoot, pNodeName, wszText);
}

// Add a child node
int AppendElementW(MSXML2::IXMLDOMDocumentPtr & pDoc,
	MSXML2::IXMLDOMElementPtr & pRoot,
	WCHAR * pNodeName,
	int dNodeValue)
{
	wchar_t wszText[20] = { 0 };

	_snwprintf(wszText, 20, L"%d", dNodeValue);

	return AppendElementW(pDoc, pRoot, pNodeName, wszText);
}

// Add a child node
int AppendElementW(MSXML2::IXMLDOMDocumentPtr & pDoc,
	MSXML2::IXMLDOMElementPtr & pRoot,
	WCHAR * pNodeName,
	CHAR * pNodeValue)
{
	USES_CONVERSION;
	return AppendElementW(pDoc, pRoot, pNodeName, A2W(pNodeValue));
}

int AppendFieldNameBlockW(MSXML2::IXMLDOMDocumentPtr & pDoc,
	MSXML2::IXMLDOMElementPtr & pRoot,
	std::vector<std::wstring>& vecFieldName)
{
	MSXML2::IXMLDOMElementPtr pBlockNode;

	// Add a line feed
	pRoot->appendChild(pDoc->createTextNode("\n\t"));

	BSTR bstrBuffer;

	// Create block node
	bstrBuffer = SysAllocString(L"Table_Data_KOR");
	pDoc->raw_createElement(bstrBuffer, &pBlockNode);

	SysFreeString(bstrBuffer);

	// Append the child node as the sub-node of pRoot
	pRoot->appendChild(pBlockNode);

	WCHAR wszNodeName[100] = { 0 };
	std::vector<std::wstring>::iterator it = vecFieldName.begin();
	for (int i = 0; i < vecFieldName.size(); i++)
	{		
		_snwprintf(wszNodeName, 100, L"FieldName_%d", i);
		AppendElementW(pDoc, pBlockNode, (WCHAR *)wszNodeName, (WCHAR *)vecFieldName[i].c_str());
	}

	// Add a line feed
	pBlockNode->appendChild(pDoc->createTextNode("\n\t"));

	return 0;
}


////////////////////////////////////////////////////////////
//
// Define all the tables for XML
//
///////////////////////////////////////////////////////////
void SetFieldNameList_MobTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Validity_Able");
	vecFieldName.push_back(L"Name");
	vecFieldName.push_back(L"Name_Text");
	vecFieldName.push_back(L"Model");
	vecFieldName.push_back(L"Level");
	vecFieldName.push_back(L"Mob_Group");
	vecFieldName.push_back(L"Mob_Kind");
	vecFieldName.push_back(L"Exp");
	vecFieldName.push_back(L"Grade");
	vecFieldName.push_back(L"Battle_Attribute");
	vecFieldName.push_back(L"Mob_type");
	vecFieldName.push_back(L"Ai_Bit_Flag");
	vecFieldName.push_back(L"Basic_LP");
	vecFieldName.push_back(L"LP_Regeneration");
	vecFieldName.push_back(L"Basic_EP");
	vecFieldName.push_back(L"EP_Regeneration");
	vecFieldName.push_back(L"Attack_Type");
	vecFieldName.push_back(L"Basic_Offence");
	vecFieldName.push_back(L"Basic_Physical_Defence");
	vecFieldName.push_back(L"Basic_Energy_Defence");
	vecFieldName.push_back(L"Str");
	vecFieldName.push_back(L"Con");
	vecFieldName.push_back(L"Foc");
	vecFieldName.push_back(L"Dex");
	vecFieldName.push_back(L"Sol");
	vecFieldName.push_back(L"Eng");
	vecFieldName.push_back(L"Scale");
	vecFieldName.push_back(L"Walk_Speed_Origin");
	vecFieldName.push_back(L"Walk_Speed");
	vecFieldName.push_back(L"Run_Speed_Origin");
	vecFieldName.push_back(L"Run_Speed");
	vecFieldName.push_back(L"Radius_X");
	vecFieldName.push_back(L"Radius_Z");
	vecFieldName.push_back(L"Attack_Speed_Rate");
	vecFieldName.push_back(L"Attack_Cool_Time");
	vecFieldName.push_back(L"Attack_Range");
	vecFieldName.push_back(L"Basic_Attack_Rate");
	vecFieldName.push_back(L"Basic_Dodge_Rate");
	vecFieldName.push_back(L"Basic_Block_Rate");
	vecFieldName.push_back(L"Basic_Curse_Success_Rate");
	vecFieldName.push_back(L"Basic_Curse_Tolerance_Rate");
	vecFieldName.push_back(L"Sight_Range");
	vecFieldName.push_back(L"Scan_Range");
	vecFieldName.push_back(L"Attack_Animation_Quantity");

	for (int i = 0; i < MAX_NPC_HAVE_SKILL; i++)
	{
		WCHAR wszBuffer[100] = { 0x00, };
		swprintf(wszBuffer, 100, L"Use_Skill_Time_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_NPC_HAVE_SKILL; i++)
	{
		WCHAR wszBuffer[100] = { 0x00, };
		swprintf(wszBuffer, 100, L"Use_Skill_Tblidx_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_NPC_HAVE_SKILL; i++)
	{
		WCHAR wszBuffer[100] = { 0x00, };
		swprintf(wszBuffer, 100, L"Use_Skill_Basis_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_NPC_HAVE_SKILL; i++)
	{
		WCHAR wszBuffer[100] = { 0x00, };
		swprintf(wszBuffer, 100, L"Use_Skill_LP_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}

	vecFieldName.push_back(L"Drop_Item_Tblidx");
	vecFieldName.push_back(L"Drop_Zenny");
	vecFieldName.push_back(L"Drop_Zenny_Rate");
	vecFieldName.push_back(L"Visible_Sight_Range");
	vecFieldName.push_back(L"Fly_Height");
	vecFieldName.push_back(L"Camera_Bone_Name");
	vecFieldName.push_back(L"ILLust");
	vecFieldName.push_back(L"Size");
	vecFieldName.push_back(L"Spawn_Animation");
	vecFieldName.push_back(L"Dialog_Group");
	vecFieldName.push_back(L"TMQ_Point");
	vecFieldName.push_back(L"Drop_Quest_Tblidx");
	vecFieldName.push_back(L"Drop_Type_Tblidx");
	vecFieldName.push_back(L"Drop_Each_Tblidx");
	vecFieldName.push_back(L"Drop_Type_Rate_Control");
	vecFieldName.push_back(L"Drop_Each_Rate_Control");
	vecFieldName.push_back(L"Drop_NItem_Rate_Control");
	vecFieldName.push_back(L"Drop_SItem_Rate_Control");
	vecFieldName.push_back(L"Drop_EItem_Rate_Control");
	vecFieldName.push_back(L"Drop_LItem_Rate_Control");
	vecFieldName.push_back(L"Alliance_Idx");
	vecFieldName.push_back(L"Aggro_Max_Count");
	vecFieldName.push_back(L"Show_Name");
	vecFieldName.push_back(L"Property");
	vecFieldName.push_back(L"HTB_Block_Rate");
	vecFieldName.push_back(L"Basic_Aggro_Point");
	vecFieldName.push_back(L"Sight_Angle");

	// sCHAR_TBLDAT.fRadius, 
	// sBOT_TBLDAT.szNameText, 
	// not processed in CMobTable::SetTableData()
	// vecFieldName.push_bak(L"Radius");       
	// vecFieldName.push_bak(L"szNameText"); 
}

void SetFieldNameList_ItemTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Validity_Able");
	vecFieldName.push_back(L"Name");
	vecFieldName.push_back(L"Name_Text");
	vecFieldName.push_back(L"Icon_Name");
	vecFieldName.push_back(L"Model_Type");
	vecFieldName.push_back(L"Model");
	vecFieldName.push_back(L"Sub_Weapon_Act_Model");
	vecFieldName.push_back(L"Item_Type");
	vecFieldName.push_back(L"Equip_Type");
	vecFieldName.push_back(L"Equip_Slot_Type_Bit_Flag");
	vecFieldName.push_back(L"Function_Bit_Flag");
	vecFieldName.push_back(L"Max_Stack");
	vecFieldName.push_back(L"Rank");
	vecFieldName.push_back(L"Cost");
	vecFieldName.push_back(L"Sell_Price");
	vecFieldName.push_back(L"Durability");
	vecFieldName.push_back(L"Durability_Count");
	vecFieldName.push_back(L"Battle_Attribute");
	vecFieldName.push_back(L"Physical_Offence");
	vecFieldName.push_back(L"Energy_Offence");
	vecFieldName.push_back(L"Physical_Defence");
	vecFieldName.push_back(L"Energy_Defence");
	vecFieldName.push_back(L"Physical_OffenceUpgrade");
	vecFieldName.push_back(L"Energy_OffenceUpgrade");
	vecFieldName.push_back(L"Physical_DefenceUpgrade");
	vecFieldName.push_back(L"Energy_DefenceUpgrade");
	vecFieldName.push_back(L"Attack_Range_Bonus");
	vecFieldName.push_back(L"Attack_Speed_Rate");
	vecFieldName.push_back(L"Need_Level");
	vecFieldName.push_back(L"Need_Class_Bit_Flag");
	vecFieldName.push_back(L"Class_Special");
	vecFieldName.push_back(L"Race_Special");
	vecFieldName.push_back(L"Need_Str");
	vecFieldName.push_back(L"Need_Con");
	vecFieldName.push_back(L"Need_Foc");
	vecFieldName.push_back(L"Need_Dex");
	vecFieldName.push_back(L"Need_Sol");
	vecFieldName.push_back(L"Need_Eng");
	vecFieldName.push_back(L"Set_Item_Tblidx");
	vecFieldName.push_back(L"Note");
	vecFieldName.push_back(L"Bag_Size");
	vecFieldName.push_back(L"Scouter_Watt");
	vecFieldName.push_back(L"Scouter_MaxPower");
	vecFieldName.push_back(L"Scouter_Parts_Type");
	vecFieldName.push_back(L"Scouter_Parts_Value");
	vecFieldName.push_back(L"Use_Item_Tblidx");
	vecFieldName.push_back(L"Item_Option_Tblidx");
	vecFieldName.push_back(L"Item_Group");
	vecFieldName.push_back(L"Charm_Tblidx");
	vecFieldName.push_back(L"Costume_Hide_Bit_Flag");
	vecFieldName.push_back(L"Need_Item_Tblidx");
	vecFieldName.push_back(L"Common_Point");
	vecFieldName.push_back(L"Common_Point_Type");
	vecFieldName.push_back(L"Need_Function");
	vecFieldName.push_back(L"Use_Duration_Max");
	vecFieldName.push_back(L"Duration_Type");
	vecFieldName.push_back(L"Contents_Tblidx");
	vecFieldName.push_back(L"Duration_Group");
}

void SetFieldNameList_SkillTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Skill_Name");
	vecFieldName.push_back(L"Name_Text");
	vecFieldName.push_back(L"Validity_Able");
	vecFieldName.push_back(L"PC_Class_Bit_Flag");
	vecFieldName.push_back(L"Skill_Class");
	vecFieldName.push_back(L"Skill_Type");
	vecFieldName.push_back(L"Skill_Active_Type");
	vecFieldName.push_back(L"Buff_Group");
	vecFieldName.push_back(L"Slot_Index");
	vecFieldName.push_back(L"Skill_Grade");
	vecFieldName.push_back(L"Function_Bit_Flag");
	vecFieldName.push_back(L"Appoint_Target");
	vecFieldName.push_back(L"Apply_Target");
	vecFieldName.push_back(L"Apply_Target_Max");
	vecFieldName.push_back(L"Apply_Range");
	vecFieldName.push_back(L"Apply_Area_Size_1");
	vecFieldName.push_back(L"Apply_Area_Size_2");
	vecFieldName.push_back(L"Skill_Effect_1");
	vecFieldName.push_back(L"Skill_Effect_Type_1");
	vecFieldName.push_back(L"Skill_Effect_Value_1");
	vecFieldName.push_back(L"Skill_Effect_2");	
	vecFieldName.push_back(L"Skill_Effect_Type_2");	
	vecFieldName.push_back(L"Skill_Effect_Value_2");

	for (BYTE byRpEffectIndex = 0; byRpEffectIndex < DBO_MAX_RP_BONUS_COUNT_PER_SKILL; byRpEffectIndex++)
	{
		WCHAR wszFieldNameEffect[100 + 1];
		WCHAR wszFieldNameEffectValue[100 + 1];

		swprintf(wszFieldNameEffect, 100, L"RP_Effect_%d", byRpEffectIndex + 1);
		swprintf(wszFieldNameEffectValue, 1024, L"RP_Effect_Value_%d", byRpEffectIndex + 1);

		vecFieldName.push_back(wszFieldNameEffect);
		vecFieldName.push_back(wszFieldNameEffectValue);
	}
	
	vecFieldName.push_back(L"Require_Train_Level");
	vecFieldName.push_back(L"Require_Zenny");
	vecFieldName.push_back(L"Next_Skill_Train_Exp");
	vecFieldName.push_back(L"Require_SP");
	vecFieldName.push_back(L"Self_Train");
	vecFieldName.push_back(L"Require_Skill_Tblidx_Min_1");
	vecFieldName.push_back(L"Require_Skill_Tblidx_Max_1");
	vecFieldName.push_back(L"Require_Skill_Tblidx_Min_2");
	vecFieldName.push_back(L"Require_Skill_Tblidx_Max_2");
	vecFieldName.push_back(L"Root_Skill");
	vecFieldName.push_back(L"Require_Epuip_Slot_Type");
	vecFieldName.push_back(L"Require_Item_Type");
	vecFieldName.push_back(L"Icon_Name");
	vecFieldName.push_back(L"Require_LP");
	vecFieldName.push_back(L"Require_EP");
	vecFieldName.push_back(L"Require_RP_Ball");
	vecFieldName.push_back(L"Casting_Time");
	vecFieldName.push_back(L"Cool_Time");
	vecFieldName.push_back(L"Keep_Time");
	vecFieldName.push_back(L"Keep_Effect");
	vecFieldName.push_back(L"Use_Range_Min");
	vecFieldName.push_back(L"Use_Range_Max");
	vecFieldName.push_back(L"Note");
	vecFieldName.push_back(L"Next_Skill_Tblidx");
	vecFieldName.push_back(L"Default_Display_Off");
	vecFieldName.push_back(L"Casting_Animation_Start");
	vecFieldName.push_back(L"Casting_Animation_Loop");
	vecFieldName.push_back(L"Action_Animation_Index");
	vecFieldName.push_back(L"Action_Loop_Animation_Index");
	vecFieldName.push_back(L"Action_End_Animation_Index");
	vecFieldName.push_back(L"Dash_Able");
	vecFieldName.push_back(L"Transform_Use_Info_Bit_Flag");
	vecFieldName.push_back(L"Success_Rate");
	vecFieldName.push_back(L"Additional_Aggro_Point");
	vecFieldName.push_back(L"PC_Class_Change");
}

void SetFieldNameList_ObjectTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Name");
	vecFieldName.push_back(L"Loc_X");
	vecFieldName.push_back(L"Loc_Y");
	vecFieldName.push_back(L"Loc_Z");
	vecFieldName.push_back(L"Dir_X");
	vecFieldName.push_back(L"Dir_Y");
	vecFieldName.push_back(L"Dir_Z");
	vecFieldName.push_back(L"Func");
	vecFieldName.push_back(L"Min_X");
	vecFieldName.push_back(L"Min_Y");
	vecFieldName.push_back(L"Min_Z");
	vecFieldName.push_back(L"Max_X");
	vecFieldName.push_back(L"Max_Y");
	vecFieldName.push_back(L"Max_Z");
	vecFieldName.push_back(L"DefMainState");
	vecFieldName.push_back(L"DefSubState");

	for (int i = 0; i < DBO_MAX_OBJECT_STATE; i++)
	{
		WCHAR wszBuffer[100] = { 0x00, };
		swprintf(wszBuffer, 100, L"State%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < DBO_MAX_OBJECT_STATE; i++)
	{
		WCHAR wszBuffer[100] = { 0x00, };
		swprintf(wszBuffer, 100, L"Click_Sound%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}
	vecFieldName.push_back(L"Boundry_Distance");
	vecFieldName.push_back(L"ModelName");
	vecFieldName.push_back(L"Note");
	vecFieldName.push_back(L"Contents_Tblidx");
	vecFieldName.push_back(L"Object_Direction_Index");
	vecFieldName.push_back(L"MinQuestId");
	vecFieldName.push_back(L"MaxQuestId");

}

void SetFieldNameList_FormulaTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Idx");
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < DBO_MAX_FORMULA_RATE_COUNT; i++)
	{

		swprintf(wszBuffer, 1024, L"Rate%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}

}

void SetFieldNameList_PortalTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Point_Name");
	vecFieldName.push_back(L"Point_Name_Text");
	vecFieldName.push_back(L"World");
	vecFieldName.push_back(L"Loc_X");
	vecFieldName.push_back(L"Loc_Y");
	vecFieldName.push_back(L"Loc_Z");
	vecFieldName.push_back(L"Dir_X");
	vecFieldName.push_back(L"Dir_Y");
	vecFieldName.push_back(L"Dir_Z");
	vecFieldName.push_back(L"Map_X");
	vecFieldName.push_back(L"Map_Y");
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < DBO_MAX_POINT_PORTAL; i++)
	{

		swprintf(wszBuffer, 1024, L"Point_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}
	WCHAR wszBuffer2[1024] = { 0x00, };
	for (int i = 0; i < DBO_MAX_POINT_PORTAL; i++)
	{

		swprintf(wszBuffer2, 1024, L"Zeny_%d", i + 1);

		vecFieldName.push_back(wszBuffer2);
	}

}

void SetFieldNameList_PcTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Race");
	vecFieldName.push_back(L"Gender");
	vecFieldName.push_back(L"Class");
	vecFieldName.push_back(L"Prior_Class_Tblidx");
	vecFieldName.push_back(L"Class_Bit_Flag");
	vecFieldName.push_back(L"Model_Child");
	vecFieldName.push_back(L"Model_Adult");
	vecFieldName.push_back(L"Basic_LP");
	vecFieldName.push_back(L"Basic_EP");
	vecFieldName.push_back(L"Basic_RP");
	vecFieldName.push_back(L"Basic_Physical_Offence");
	vecFieldName.push_back(L"Basic_Physical_Defence");
	vecFieldName.push_back(L"Basic_Energy_Offence");
	vecFieldName.push_back(L"Basic_Energy_Defence");
	vecFieldName.push_back(L"Basic_Energy_Defence");
	vecFieldName.push_back(L"Basic_Str");
	vecFieldName.push_back(L"Basic_Con");
	vecFieldName.push_back(L"Basic_Foc");
	vecFieldName.push_back(L"Basic_Dex");
	vecFieldName.push_back(L"Basic_Sol");
	vecFieldName.push_back(L"Basic_Eng");
	vecFieldName.push_back(L"Level_Up_LP");
	vecFieldName.push_back(L"Level_Up_EP");
	vecFieldName.push_back(L"Level_Up_RP");
	vecFieldName.push_back(L"Level_Up_Physical_Offence");
	vecFieldName.push_back(L"Level_Up_Physical_Defence");
	vecFieldName.push_back(L"Level_Up_Energy_Offence");
	vecFieldName.push_back(L"Level_Up_Energy_Defence");
	vecFieldName.push_back(L"Level_Up_Str");
	vecFieldName.push_back(L"Level_Up_Con");
	vecFieldName.push_back(L"Level_Up_Foc");
	vecFieldName.push_back(L"Level_Up_Dex");
	vecFieldName.push_back(L"Level_Up_Sol");
	vecFieldName.push_back(L"Level_Up_Eng");
	vecFieldName.push_back(L"Scale");
	vecFieldName.push_back(L"Child_Run_Speed_Origin");
	vecFieldName.push_back(L"Child_Run_Speed");
	vecFieldName.push_back(L"Adult_Run_Speed_Origin");
	vecFieldName.push_back(L"Adult_Run_Speed");
	vecFieldName.push_back(L"Radius");
	vecFieldName.push_back(L"Attack_Speed_Rate");
	vecFieldName.push_back(L"Attack_Range");
	vecFieldName.push_back(L"Basic_Attack_Rate");
	vecFieldName.push_back(L"Basic_Dodge_Rate");
	vecFieldName.push_back(L"Basic_Block_Rate");
	vecFieldName.push_back(L"Basic_Curse_Success_Rate");
	vecFieldName.push_back(L"Basic_Curse_Tolerance_Rate");
	vecFieldName.push_back(L"Basic_Aggro_Point");
	
}

void SetFieldNameList_ExpTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

		vecFieldName.push_back(L"Level");
		vecFieldName.push_back(L"EXP");
		vecFieldName.push_back(L"Need_EXP");
}

void SetFieldNameList_QuestTextTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Quest_Text_Index");
	vecFieldName.push_back(L"Quest_Text");
}

void SetFieldNameList_WorldTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Name");
	vecFieldName.push_back(L"Dynamic_Able");
	vecFieldName.push_back(L"Dynamic_Create_Count");
	vecFieldName.push_back(L"Field_Door_Type");
	vecFieldName.push_back(L"Mob_Spawn_Table_Name");
	vecFieldName.push_back(L"NPC_Spawn_Table_Name");
	vecFieldName.push_back(L"Object_Spawn_Table_Name");
	vecFieldName.push_back(L"Field_Start_Loc_X");
	vecFieldName.push_back(L"Field_Start_Loc_Z");
	vecFieldName.push_back(L"Field_End_Loc_X");
	vecFieldName.push_back(L"Field_End_Loc_Z");
	vecFieldName.push_back(L"Battle_Start_Loc_X");
	vecFieldName.push_back(L"Battle_Start_Loc_Z");
	vecFieldName.push_back(L"Battle_End_Loc_X");
	vecFieldName.push_back(L"Battle_End_Loc_Z");
	vecFieldName.push_back(L"Outside_Battle_Start_Loc_X");
	vecFieldName.push_back(L"Outside_Battle_Start_Loc_Z");
	vecFieldName.push_back(L"Outside_Battle_End_Loc_X");
	vecFieldName.push_back(L"Outside_Battle_End_Loc_Z");
	vecFieldName.push_back(L"Spectator_Start_Loc_X");
	vecFieldName.push_back(L"Spectator_Start_Loc_Z");
	vecFieldName.push_back(L"Spectator_End_Loc_X");
	vecFieldName.push_back(L"Spectator_End_Loc_Z");
	vecFieldName.push_back(L"Default_Loc_X");
	vecFieldName.push_back(L"Default_Loc_Y");
	vecFieldName.push_back(L"Default_Loc_Z");
	vecFieldName.push_back(L"Default_Dir_X");
	vecFieldName.push_back(L"Default_Dri_Y");
	vecFieldName.push_back(L"Default_Dir_Z");
	vecFieldName.push_back(L"Start1_Point_Loc_X");
	vecFieldName.push_back(L"Start1_Point_Loc_Y");
	vecFieldName.push_back(L"Start1_Point_Loc_Z");
	vecFieldName.push_back(L"Start1_Point_Dir_X");
	vecFieldName.push_back(L"Start1_Point_Dir_Z");
	vecFieldName.push_back(L"Start2_Point_Loc_X");
	vecFieldName.push_back(L"Start2_Point_Loc_Y");
	vecFieldName.push_back(L"Start2_Point_Loc_Z");
	vecFieldName.push_back(L"Start2_Point_Dir_X");
	vecFieldName.push_back(L"Start2_Point_Dir_Z");
	vecFieldName.push_back(L"Standard_Loc_X");
	vecFieldName.push_back(L"Standard_Loc_Z");
	vecFieldName.push_back(L"Field_Destroy_Time");
	vecFieldName.push_back(L"Split_Size");
	vecFieldName.push_back(L"Night_Able");
	vecFieldName.push_back(L"Static_Time");
	vecFieldName.push_back(L"funcflag");
	vecFieldName.push_back(L"World_Rule_Type");
	vecFieldName.push_back(L"World_Rule_Index");
	vecFieldName.push_back(L"OutField_Tblidx");
	vecFieldName.push_back(L"Out_Field_Loc_X");
	vecFieldName.push_back(L"Out_Field_Loc_Z");
	vecFieldName.push_back(L"Out_Field_Dir_X");
	vecFieldName.push_back(L"Out_Field_Dir_Z");
	vecFieldName.push_back(L"ResourceFolder");
	vecFieldName.push_back(L"BMG_Rest_Time");
	vecFieldName.push_back(L"World_Resource_ID");
	vecFieldName.push_back(L"FreeCamera_Height");
	vecFieldName.push_back(L"Enter_Resource_Flash");
	vecFieldName.push_back(L"Leave_Resource_Flash");
	vecFieldName.push_back(L"WPS_Link_Index");

}

void SetFieldNameList_SpawnTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Mob_Tblidx");
	vecFieldName.push_back(L"Spawn_Loc_X");
	vecFieldName.push_back(L"Spawn_Loc_Y");
	vecFieldName.push_back(L"Spawn_Loc_Z");
	vecFieldName.push_back(L"Spawn_Dir_X");
	vecFieldName.push_back(L"Spawn_Dir_Z");
	vecFieldName.push_back(L"Spawn_Loc_Range");
	vecFieldName.push_back(L"Spawn_Quantity");
	vecFieldName.push_back(L"Spawn_Cool_Time");
	vecFieldName.push_back(L"Spawn_Move_Type");
	vecFieldName.push_back(L"Wander_Range");
	vecFieldName.push_back(L"Move_Range");
	vecFieldName.push_back(L"Move_Delay_Time");
	vecFieldName.push_back(L"Path_Table_Index");
	vecFieldName.push_back(L"PlayScript_Number");
	vecFieldName.push_back(L"PlayScript_Scene_Number");
	vecFieldName.push_back(L"AIScript_Number");
	vecFieldName.push_back(L"AIScript_Scene_Number");
	vecFieldName.push_back(L"AIScript_Number");
	vecFieldName.push_back(L"Follow_Distance_Loc_X");
	vecFieldName.push_back(L"Follow_Distance_Loc_Z");
	vecFieldName.push_back(L"Party_Index");
	vecFieldName.push_back(L"Party_Leader_Able");
	vecFieldName.push_back(L"Spawn_Group");
}

void SetFieldNameList_LandMarkTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Landmark_Name");
	vecFieldName.push_back(L"Landmark_Type");
	vecFieldName.push_back(L"Name_Text");
	vecFieldName.push_back(L"Validity_Able");
	vecFieldName.push_back(L"Landmark_BitFlag");
	vecFieldName.push_back(L"Landmark_Display_BitFlag");
	vecFieldName.push_back(L"Landmark_Loc_X");
	vecFieldName.push_back(L"Landmark_Loc_Z");
	vecFieldName.push_back(L"Link_Map_Idx");
	vecFieldName.push_back(L"Link_Warfog_Idx");
	vecFieldName.push_back(L"Icon_Name");
	vecFieldName.push_back(L"Icon_Size");
	vecFieldName.push_back(L"Note");
	
}

void SetFieldNameList_DynamicObjectTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Validity_Able");
	vecFieldName.push_back(L"Type");
	vecFieldName.push_back(L"Model_Name");
	vecFieldName.push_back(L"State_Type");
	vecFieldName.push_back(L"Spawn_Animation");

	vecFieldName.push_back(L"Idle_Animation");
	vecFieldName.push_back(L"Despawn_Animation");
	vecFieldName.push_back(L"State1_Animation");
	vecFieldName.push_back(L"State2_Animation");
	vecFieldName.push_back(L"Boundary_Distance");
	vecFieldName.push_back(L"Despawn_Distance");
	vecFieldName.push_back(L"Note");

}

void SetFieldNameList_WorldMapTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();
	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"World_Tblidx");
	vecFieldName.push_back(L"Zone_Tblidx");
	vecFieldName.push_back(L"Worldmap_Name");
	vecFieldName.push_back(L"Name_Text");
	vecFieldName.push_back(L"Validity_Able");
	vecFieldName.push_back(L"Map_Type");
	vecFieldName.push_back(L"Standard_Loc_X");
	vecFieldName.push_back(L"Standard_Loc_Z");
	vecFieldName.push_back(L"Worldmap_Scale");
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < DBO_WORLD_MAP_TABLE_COUNT_WORLD_WARFOG; i++)
	{
		swprintf(wszBuffer, 1024, L"Warfog_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}
}

void SetFieldNameList_WorldPlayTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Group");
	vecFieldName.push_back(L"Executer_Type");
	vecFieldName.push_back(L"ShareType");
	vecFieldName.push_back(L"ShareLimitTime");
	vecFieldName.push_back(L"Desc");

}

void SetFieldNameList_WorldZoneTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Function_Bit_Flag");
	vecFieldName.push_back(L"World");
	vecFieldName.push_back(L"Name");
	vecFieldName.push_back(L"Name_Text");
	vecFieldName.push_back(L"Forbidden_Vehicle");
}

void SetFieldNameList_VehicleTable(std::vector<std::wstring>& vecFieldName)
{

		vecFieldName.clear();

		vecFieldName.push_back(L"Tblidx");
		vecFieldName.push_back(L"Model_Name");
		vecFieldName.push_back(L"SRP_Type");
		vecFieldName.push_back(L"Speed");
		vecFieldName.push_back(L"Vehicle_Type");
		vecFieldName.push_back(L"Run_Height");
		vecFieldName.push_back(L"Personnel");
}

void SetFieldNameList_HTBSetTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Model_Name");
	vecFieldName.push_back(L"SRP_Type");
	vecFieldName.push_back(L"Speed");
	vecFieldName.push_back(L"Vehicle_Type");
	vecFieldName.push_back(L"Run_Height");
	vecFieldName.push_back(L"Personnel");
}

void SetFieldNameList_MobMovePatternTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < DBO_MAX_COUNT_MOVE_PATTERN; i++)
	{

		swprintf(wszBuffer, 1024, L"Pattern_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}

}

void SetFieldNameList_BasicDropTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Max");

	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
	{
		swprintf(wszBuffer, 1024, L"Normal_Tblidx_Rate_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
	{
		swprintf(wszBuffer, 1024, L"Normal_Drop_Tblidx_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
	{
		swprintf(wszBuffer, 1024, L"Superior_Tblidx_Rate_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
	{
		swprintf(wszBuffer, 1024, L"Superior_Drop_Tblidx_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}
	
	vecFieldName.push_back(L"Superior_Drop_Rate_Control");
	vecFieldName.push_back(L"Superior_Option_Rate_Control");
	
	for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
	{
		swprintf(wszBuffer, 1024, L"Excellent_Tblidx_Rate_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
	{
		swprintf(wszBuffer, 1024, L"Excellent_Drop_Tblidx_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

	vecFieldName.push_back(L"Excellent_Drop_Rate_Control");

	for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
	{
		swprintf(wszBuffer, 1024, L"Legendary_Tblidx_Rate_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
	{
		swprintf(wszBuffer, 1024, L"Legendary_Drop_Tblidx_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}
	vecFieldName.push_back(L"Legendary_Drop_Rate_Control");

}

void SetFieldNameList_EachDropTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < MAX_EACH_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_EACH_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

}

void SetFieldNameList_TypeDropTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < MAX_EACH_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_EACH_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

}

void SetFieldNameList_NormalDropTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < MAX_NORMAL_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_NORMAL_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

}

void SetFieldNameList_ExcellentDropTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < MAX_EXCELLENT_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_EACH_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

}

void SetFieldNameList_LegendaryDropTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < MAX_LEGENDARY_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_LEGENDARY_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

}

void SetFieldNameList_SuperiorDropTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Max_Quality");
	vecFieldName.push_back(L"Option_Rate");
	
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < MAX_SUPERIOR_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_SUPERIOR_DROP; i++)
	{
		swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

}

void SetFieldNameList_DirectionLinkTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Function_Name");
	vecFieldName.push_back(L"Note");
	vecFieldName.push_back(L"Type");
	vecFieldName.push_back(L"Animation_ID");
	vecFieldName.push_back(L"Direction_Func_Flag");

}

void SetFieldNameList_ScriptLinkTable(std::vector<std::wstring>& vecFieldName)
{
	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Value");
	vecFieldName.push_back(L"Type");
	vecFieldName.push_back(L"Action");

}

void SetFieldNameList_QuestNarrationTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Type");
	vecFieldName.push_back(L"Number");
	vecFieldName.push_back(L"Time");
	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
	{

		swprintf(wszBuffer, 1024, L"UIShowHideDirection_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
	{

		swprintf(wszBuffer, 1024, L"OwnerType_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
	{

		swprintf(wszBuffer, 1024, L"Owner_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
	{

		swprintf(wszBuffer, 1024, L"Condition_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
	{

		swprintf(wszBuffer, 1024, L"Direction_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
	{

		swprintf(wszBuffer, 1024, L"Dialog_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
	{

		swprintf(wszBuffer, 1024, L"UiType_%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}
	for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
	{

		swprintf(wszBuffer, 1024, L"UIDirection__%d", i + 1);

		vecFieldName.push_back(wszBuffer);
	}

}

void SetFieldNameList_ItemOptionTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Option_Name");
	vecFieldName.push_back(L"Validity_Able");
	vecFieldName.push_back(L"Option_Rank");
	vecFieldName.push_back(L"Item_Group");
	vecFieldName.push_back(L"Max_Quality");
	vecFieldName.push_back(L"Quality");
	vecFieldName.push_back(L"Quality_Index");
	vecFieldName.push_back(L"Cost");
	vecFieldName.push_back(L"Level");

	WCHAR wszBuffer[1024] = { 0x00, };
	for (int i = 0; i < MAX_SYSTEM_EFFECT_COUNT; i++)
	{
		swprintf(wszBuffer, 1024, L"System_Effect_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_SYSTEM_EFFECT_COUNT; i++)
	{
		swprintf(wszBuffer, 1024, L"Type_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}

	for (int i = 0; i < MAX_SYSTEM_EFFECT_COUNT; i++)
	{
		swprintf(wszBuffer, 1024, L"Value_%d", i + 1);
		vecFieldName.push_back(wszBuffer);
	}
	
	vecFieldName.push_back(L"Active_Effect");
	vecFieldName.push_back(L"Active_Rate");
	vecFieldName.push_back(L"Note");
	vecFieldName.push_back(L"Scouter_Info");
}

void SetFieldNameList_SystemEffectTable(std::vector<std::wstring>& vecFieldName)
{

	vecFieldName.clear();

	vecFieldName.push_back(L"Tblidx");
	vecFieldName.push_back(L"Name");
	vecFieldName.push_back(L"Effect_Type");
	vecFieldName.push_back(L"Active_Effect_Type");
	vecFieldName.push_back(L"Effect_Info_Text");
	vecFieldName.push_back(L"Keep_Effect_Name");
	vecFieldName.push_back(L"Target_Effect_Position");
	vecFieldName.push_back(L"Success_Effect_Name");
	vecFieldName.push_back(L"Success_Projectile_Type");
	vecFieldName.push_back(L"Success_Effect_Position");
	vecFieldName.push_back(L"Success_End_Effect_Name");
	vecFieldName.push_back(L"End_Effect_Position");
	vecFieldName.push_back(L"Keep_Animation_Index");
}
/////////////////////////////////////////////////////////////
CRdf2XmlHelper::CRdf2XmlHelper()
{
	m_pTableContainer = NULL;
}
CRdf2XmlHelper::~CRdf2XmlHelper()
{
}

////////////////////////////////////////////////////////////
//
// Load all the tables
//
///////////////////////////////////////////////////////////
bool CRdf2XmlHelper::CreateTableContainer(const char* pszPath, int byLoadMethod)
{
	if (pszPath == NULL)
	{
		return false;
	}

	printf("==== LOADING GAME TABLES ... ==== \n");

	CNtlBitFlagManager flagManager;
	if (false == flagManager.Create(TableContainer::TABLE_COUNT))
	{
		return false;
	}

	TableFileNameList fileNameList;

	if (false == fileNameList.Create())
	{
		return false;
	}

	/*flagManager.Set(CTableContainer::TABLE_MOB);	
	
	flagManager.Set(CTableContainer::TABLE_SKILL);
	flagManager.Set(CTableContainer::TABLE_TEXT_ALL);
	flagManager.Set(CTableContainer::TABLE_FORMULA);
	
	flagManager.Set(CTableContainer::TABLE_OBJECT);
	flagManager.Set(CTableContainer::TABLE_PORTAL);
	flagManager.Set(CTableContainer::TABLE_NPC_SPAWN);
	flagManager.Set(CTableContainer::TABLE_MOB_SPAWN);
	flagManager.Set(CTableContainer::TABLE_LAND_MARK);
	flagManager.Set(CTableContainer::TABLE_WORLD_MAP);
	flagManager.Set(CTableContainer::TABLE_WORLD_ZONE);
	flagManager.Set(CTableContainer::TABLE_DYNAMIC_OBJECT);
	flagManager.Set(CTableContainer::TABLE_VEHICLE);
	flagManager.Set(CTableContainer::TABLE_WORLD);

	flagManager.Set(CTableContainer::TABLE_MOB_MOVE_PATTERN);

	flagManager.Set(CTableContainer::TABLE_HTB_SET);
	flagManager.Set(CTableContainer::TABLE_QUEST_TEXT_DATA);

	flagManager.Set(CTableContainer::TABLE_DIRECTION_LINK);
	flagManager.Set(CTableContainer::TABLE_SCRIPT_LINK);
	flagManager.Set(CTableContainer::TABLE_QUEST_NARRATION);*/

	/*flagManager.Set(CTableContainer::TABLE_NPC);
	flagManager.Set(CTableContainer::TABLE_NEWBIE);
	flagManager.Set(CTableContainer::TABLE_MERCHANT);
	flagManager.Set(CTableContainer::TABLE_USE_ITEM);
	flagManager.Set(CTableContainer::TABLE_SET_ITEM);
	flagManager.Set(CTableContainer::TABLE_CHARM);
	flagManager.Set(CTableContainer::TABLE_ACTION);
	flagManager.Set(CTableContainer::TABLE_CHAT_COMMAND);
	flagManager.Set(CTableContainer::TABLE_QUEST_ITEM);

	flagManager.Set(CTableContainer::TABLE_TEXT_ALL);
	flagManager.Set(CTableContainer::TABLE_HELP);
	flagManager.Set(CTableContainer::TABLE_GUIDE_HINT);
	flagManager.Set(CTableContainer::TABLE_DRAGONBALL);
	flagManager.Set(CTableContainer::TABLE_DRAGONBALL_REWARD);
	flagManager.Set(CTableContainer::TABLE_TIMEQUEST);
	flagManager.Set(CTableContainer::TABLE_BUDOKAI);
	flagManager.Set(CTableContainer::TABLE_RANKBATTLE);
	flagManager.Set(CTableContainer::TABLE_CHATTING_FILTER);
	flagManager.Set(CTableContainer::TABLE_SPEECH);
	flagManager.Set(CTableContainer::TABLE_DUNGEON);
	flagManager.Set(CTableContainer::TABLE_ITEM_RECIPE);
	flagManager.Set(CTableContainer::TABLE_ITEM_UPGRADE);
	flagManager.Set(CTableContainer::TABLE_MIX_MACHINE);
	flagManager.Set(CTableContainer::TABLE_DOJO);
	flagManager.Set(CTableContainer::TABLE_QUEST_REWARD);

	flagManager.Set(CTableContainer::TABLE_GAME_MANIA_TIME);
	flagManager.Set(CTableContainer::TABLE_BASIC_DROP);
	flagManager.Set(CTableContainer::TABLE_LEGENDARY_DROP);
	flagManager.Set(CTableContainer::TABLE_NORMAL_DROP);
	flagManager.Set(CTableContainer::TABLE_SUPERIOR_DROP);
	flagManager.Set(CTableContainer::TABLE_EACH_DROP);
	flagManager.Set(CTableContainer::TABLE_TYPE_DROP);
	flagManager.Set(CTableContainer::TABLE_PC);
	
	*/
	flagManager.Set(TableContainer::TABLE_ITEM_OPTION);
	flagManager.Set(TableContainer::TABLE_SYSTEM_EFFECT);

	fileNameList.SetFileName(TableContainer::TABLE_ITEM_OPTION, "Table_Item_Option_Data");
	fileNameList.SetFileName(TableContainer::TABLE_SYSTEM_EFFECT, "Table_System_Effect_Data");


	
	/*flagManager.Set(CTableContainer::TABLE_ITEM);
	
	flagManager.Set(CTableContainer::TABLE_BASIC_DROP);
	flagManager.Set(CTableContainer::TABLE_LEGENDARY_DROP);
	flagManager.Set(CTableContainer::TABLE_NORMAL_DROP);
	flagManager.Set(CTableContainer::TABLE_SUPERIOR_DROP);
	flagManager.Set(CTableContainer::TABLE_EACH_DROP);
	flagManager.Set(CTableContainer::TABLE_EXCELLENT_DROP);
	flagManager.Set(CTableContainer::TABLE_TYPE_DROP);

	fileNameList.SetFileName(CTableContainer::TABLE_ITEM, "Table_Item_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_PC, "Table_PC_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_BASIC_DROP, "Table_Basic_Drop_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_EACH_DROP, "Table_Each_Drop_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_NORMAL_DROP, "Table_Normal_Drop_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_LEGENDARY_DROP, "Table_Legendary_Drop_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_EXCELLENT_DROP, "Table_Excellent_Drop_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_TYPE_DROP, "Table_Type_Drop_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_SUPERIOR_DROP, "Table_Superior_Drop_Data");*/

	/*fileNameList.SetFileName(CTableContainer::TABLE_MOB, "Table_MOB_Data");	
	fileNameList.SetFileName(CTableContainer::TABLE_SKILL, "Table_Skill_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_EACH_DROP, "Table_Each_Drop_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_MOB_MOVE_PATTERN, "Table_Mob_Move_Pattern_Data");

	fileNameList.SetFileName(CTableContainer::TABLE_TEXT_ALL, "Table_Text_All_Data");

	fileNameList.SetFileName(CTableContainer::TABLE_FORMULA, "TD_Formula");
	
	fileNameList.SetFileName(CTableContainer::TABLE_WORLD, "Table_World_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_OBJECT, "Table_Object");
	fileNameList.SetFileName(CTableContainer::TABLE_PORTAL, "Table_Portal_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_LAND_MARK, "Table_Landmark_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_WORLD_MAP, "Table_Worldmap_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_WORLD_ZONE, "Table_World_Zone_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_DYNAMIC_OBJECT, "Table_Dynamic_Object_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_VEHICLE, "Table_Vehicle_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_QUEST_TEXT_DATA, "Table_Quest_Text_Data");*/

	/*fileNameList.SetFileName(CTableContainer::TABLE_DIRECTION_LINK, "Table_Direction_Link_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_SCRIPT_LINK, "Table_Script_Link_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_QUEST_NARRATION, "Table_Quest_Narration_Data");*/

	/*
	
	fileNameList.SetFileName(CTableContainer::TABLE_NPC, "Table_NPC_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_NEWBIE, "Table_Newbie_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_MERCHANT, "Table_Merchant_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_HTB_SET, "Table_HTB_Set_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_USE_ITEM, "Table_Use_Item_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_SET_ITEM, "Table_Set_Item_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_CHARM, "Table_Charm_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_ACTION, "Table_Action_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_CHAT_COMMAND, "Table_Chat_Command_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_QUEST_ITEM, "Table_Quest_Item_Data");

	fileNameList.SetFileName(CTableContainer::TABLE_TEXT_ALL, "Table_Text_All_Data");
	
	fileNameList.SetFileName(CTableContainer::TABLE_HELP, "Table_Help_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_GUIDE_HINT, "Table_Guide_Hint_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_DRAGONBALL, "Table_Dragon_Ball_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_DRAGONBALL_REWARD, "Table_DB_Reward_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_TIMEQUEST, "Table_TMQ_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_BUDOKAI, "Table_Tenkaichibudokai_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_RANKBATTLE, "Table_RankBattle_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_CHATTING_FILTER, "Table_Chatting_Filter_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_SPEECH, "Table_NPC_Speech_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_DUNGEON, "Table_Dungeon_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_ITEM_RECIPE, "Table_Item_Recipe_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_ITEM_UPGRADE, "Table_Item_Upgrade_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_MIX_MACHINE, "Table_Item_Mix_Machine_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_DOJO, "Table_Dojo_Data");
	fileNameList.SetFileName(CTableContainer::TABLE_QUEST_REWARD, "Table_Quest_Reward_Data");
	
	fileNameList.SetFileName(CTableContainer::TABLE_GAME_MANIA_TIME, "Table_GameManiaTime_Data");
	
	*/

	m_pTableContainer = new TableContainer;

	eLOADING_METHOD eLoadMethod = (eLOADING_METHOD)byLoadMethod;

	bool bResult = FALSE;

	bResult = m_pTableContainer->Create(flagManager, (char *)pszPath, &fileNameList, eLoadMethod, GetACP(), NULL);
	
	m_pTableContainer->SaveToFile(flagManager, &fileNameList, false); // Save to EDF or RDF(False = RDF True = EDF)

	printf("==== LOADING GAMETABLES COMPLETE ==== \n");

	return true;
}


//bool CRdf2XmlHelper::SaveToXml_MobTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//	
//	MobTable* pMobTable = m_pTableContainer->GetMobTable();
//
//	if (pMobTable == NULL)
//	{
//		printf("No MobTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_MOB_Data.xml";
//	
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_MobTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	Table::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pMobTableNode;
//
//	for (iter = pMobTable->Begin(); pMobTable->End() != iter; iter++)
//	{
//		sMOB_TBLDAT* pTableData = (sMOB_TBLDAT*)(iter->second);
//
//		// MobTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pMobTableNode, L"Table_Data_KOR", NULL);	
//		if (pMobTableNode == NULL)
//		{
//			printf("Failed to create MobTable XML node.\n");
//			return false;
//		}
//		
//		AppendElementW(pXMLDoc, pMobTableNode, L"TblIdx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Validity_Able", pTableData->bValidity_Able ? 1 : 0);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Name", pTableData->Name);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Name_Text", pTableData->wszNameText);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Model", pTableData->szModel);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Level", pTableData->byLevel);
//		//AppendElementW(pXMLDoc, pMobTableNode, L"Mob_Group", pTableData->dwMobGroup);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Mob_Kind", pTableData->wMob_Kind);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Exp", pTableData->wExp);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Grade", pTableData->byGrade);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Battle_Attribute", pTableData->byBattle_Attribute);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Mob_Type", pTableData->byMob_Type);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Ai_Bit_Flag", pTableData->dwAi_Bit_Flag);
////		AppendElementW(pXMLDoc, pMobTableNode, L"Basic_LP", pTableData->wBasic_LP);
//		AppendElementW(pXMLDoc, pMobTableNode, L"LP_Regeneration", pTableData->wLP_Regeneration);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Basic_EP", pTableData->wBasic_EP);		
//		AppendElementW(pXMLDoc, pMobTableNode, L"EP_Regeneration", pTableData->wEP_Regeneration);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Attack_Type", pTableData->byAttack_Type);
//		//AppendElementW(pXMLDoc, pMobTableNode, L"Basic_Offence", pTableData->wBasic_Offence);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Basic_Physical_Defence", pTableData->wBasic_Physical_Defence);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Basic_Energy_Defence", pTableData->wBasic_Energy_Defence);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Str", pTableData->byStr);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Con", pTableData->byCon);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Foc", pTableData->byFoc);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Dex", pTableData->byDex);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Sol", pTableData->bySol);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Eng", pTableData->byEng);
//		AppendElementW_f(pXMLDoc, pMobTableNode, L"Scale", pTableData->fScale);
//		AppendElementW_f(pXMLDoc, pMobTableNode, L"Walk_Speed_Origin", pTableData->fWalk_Speed_Origin);
//		AppendElementW_f(pXMLDoc, pMobTableNode, L"Walk_Speed", pTableData->fWalk_Speed);
//		AppendElementW_f(pXMLDoc, pMobTableNode, L"RunSpeedOrigin", pTableData->fRun_Speed_Origin);
//		AppendElementW_f(pXMLDoc, pMobTableNode, L"RunSpeed", pTableData->fRun_Speed);
//		AppendElementW_f(pXMLDoc, pMobTableNode, L"Radius_X", pTableData->fRadius_X);
//		AppendElementW_f(pXMLDoc, pMobTableNode, L"Radius_Z", pTableData->fRadius_Z);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Attack_Speed_Rate", pTableData->wAttack_Speed_Rate);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Attack_Cool_Time", pTableData->wAttackCoolTime);
//		AppendElementW_f(pXMLDoc, pMobTableNode, L"AttackRange", pTableData->fAttack_Range);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Basic_Attack_Rate", pTableData->wAttack_Rate);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Basic_Dodge_Rate", pTableData->wDodge_Rate);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Basic_Block_Rate", pTableData->wBlock_Rate);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Basic_Curse_Success_Rate", pTableData->wCurse_Success_Rate);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Basic_Curse_Tolerance_Rate", pTableData->wCurse_Tolerance_Rate);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Sight_Range", pTableData->bySight_Range);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Scan_Range", pTableData->byScan_Range);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Attack_Animation_Quantity", pTableData->byAttack_Animation_Quantity);
//		
//		WCHAR wszBuffer[50] = { 0x00, };
//		for (int i = 0; i < MAX_NPC_HAVE_SKILL; i++)
//		{					
//			swprintf(wszBuffer, 50, L"Use_Skill_Time_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pMobTableNode, wszBuffer, pTableData->wUse_Skill_Time[i]);
//		}
//
//		for (int i = 0; i < MAX_NPC_HAVE_SKILL; i++)
//		{
//			swprintf(wszBuffer, 50, L"Use_Skill_Tblidx_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pMobTableNode, wszBuffer, pTableData->use_Skill_Tblidx[i]);
//		}
//
//		for (int i = 0; i < MAX_NPC_HAVE_SKILL; i++)
//		{
//			swprintf(wszBuffer, 50, L"Use_Skill_Basis_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pMobTableNode, wszBuffer, pTableData->byUse_Skill_Basis[i]);
//		}
//
//		for (int i = 0; i < MAX_NPC_HAVE_SKILL; i++)
//		{
//			swprintf(wszBuffer, 50, L"Use_Skill_LP_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pMobTableNode, wszBuffer, pTableData->wUse_Skill_LP[i]);
//		}
//
//		//AppendElementW(pXMLDoc, pMobTableNode, L"Drop_Item_Tblidx", pTableData->drop_Item_Tblidx);
//		//AppendElementW(pXMLDoc, pMobTableNode, L"Drop_Zenny", pTableData->dwDrop_Zenny);
//		AppendElementW_f(pXMLDoc, pMobTableNode, L"Drop_Zenny_Rate", pTableData->fDrop_Zenny_Rate);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Visible_Sight_Range", pTableData->byVisible_Sight_Range);
//		AppendElementW_f(pXMLDoc, pMobTableNode, L"Fly_Height", pTableData->fFly_Height);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Camera_Bone_Name", pTableData->szCamera_Bone_Name);
//		AppendElementW(pXMLDoc, pMobTableNode, L"ILLust", pTableData->szILLust);
//		//AppendElementW(pXMLDoc, pMobTableNode, L"Size", pTableData->bSize);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Spawn_Animation", pTableData->bSpawn_Animation ? 1 : 0);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Dialog_Group", pTableData->dwDialogGroup);
//	//	AppendElementW(pXMLDoc, pMobTableNode, L"TMQ_Point", pTableData->wTMQPoint);
//	//	AppendElementW(pXMLDoc, pMobTableNode, L"Drop_Quest_Tblidx", pTableData->dropQuestTblidx);
//	//	AppendElementW(pXMLDoc, pMobTableNode, L"Drop_Type_Tblidx", pTableData->dropTypeTblidx);
//	//	AppendElementW(pXMLDoc, pMobTableNode, L"Drop_Each_Tblidx", pTableData->dropEachTblidx);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Drop_Type_Rate_Control", pTableData->byDropTypeRateControl);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Drop_Each_Rate_Control", pTableData->byDropEachRateControl);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Drop_NItem_Rate_Control", pTableData->byDropNItemRateControl);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Drop_SItem_Rate_Control", pTableData->byDropSItemRateControl);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Drop_EItem_Rate_Control", pTableData->byDropEItemRateControl);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Drop_LItem_Rate_Control", pTableData->byDropLItemRateControl);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Alliance_Idx", pTableData->dwAllianceIdx);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Aggro_Max_Count", pTableData->wAggroMaxCount);
////		AppendElementW(pXMLDoc, pMobTableNode, L"Show_Name", pTableData->bShow_Name ? 1 : 0);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Property", pTableData->byProperty);
//	//	AppendElementW(pXMLDoc, pMobTableNode, L"HTB_Block_Rate", pTableData->byHtbBlockRate);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Basic_Aggro_Point", pTableData->wBasic_Aggro_Point);
//		AppendElementW(pXMLDoc, pMobTableNode, L"Sight_Angle", pTableData->wSightAngle);			
//
//		// Add a line feed
//		pMobTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pMobTableNode = NULL;		
//	}
//	
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_ItemTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	ItemTable* pItemTable = m_pTableContainer->GetItemTable();
//
//	if (pItemTable == NULL)
//	{
//		printf("No ItemTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Item_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//	
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_ItemTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create ItemTable XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pItemTableNode;
//
//	for (iter = pItemTable->Begin(); pItemTable->End() != iter; iter++)
//	{
//		sITEM_TBLDAT* pTableData = (sITEM_TBLDAT*)(iter->second);
//
//		// ItemTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pItemTableNode, L"Table_Data_KOR", NULL);
//		if (pItemTableNode == NULL)
//		{
//			printf("Failed to create ItemTable XML node.\n");
//			return false;
//		}
//
//		// ItemTable.tblidx		
//		AppendElementW(pXMLDoc, pItemTableNode, L"TblIdx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Validity_Able", pTableData->bValidity_Able?1:0);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Name", pTableData->Name);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Name_Text", pTableData->wszNameText);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Icon_Name", pTableData->szIcon_Name);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Model_Type", pTableData->byModel_Type);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Model", pTableData->szModel);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Sub_Weapon_Act_Model", pTableData->szSub_Weapon_Act_Model);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Item_Type", pTableData->byItem_Type);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Equip_Type", pTableData->byEquip_Type);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Equip_Slot_Type_Bit_Flag", pTableData->wEquip_Slot_Type_Bit_Flag);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Function_Bit_Flag", pTableData->wFunction_Bit_Flag);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Max_Stack", pTableData->byMax_Stack);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Rank", pTableData->byRank);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Cost", pTableData->dwCost);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Sell_Price", pTableData->bySell_Price);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Durability", pTableData->byDurability);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Durability_Count", pTableData->byDurability_Count);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Battle_Attribute", pTableData->byBattle_Attribute);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Physical_Offence", pTableData->wPhysical_Offence);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Energy_Offence", pTableData->wEnergy_Offence);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Physical_Defence", pTableData->wPhysical_Defence);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Energy_Defence", pTableData->wEnergy_Defence);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Physical_OffenceUpgrade", pTableData->dwPhysical_OffenceUpgrade);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Energy_OffenceUpgrade", pTableData->dwEnergy_OffenceUpgrade);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Physical_DefenceUpgrade", pTableData->dwPhysical_DefenceUpgrade);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Energy_DefenceUpgrade", pTableData->dwEnergy_DefenceUpgrade);
//		AppendElementW_f(pXMLDoc, pItemTableNode, L"Attack_Range_Bonus", pTableData->fAttack_Range_Bonus);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Attack_Speed_Rate", pTableData->wAttack_Speed_Rate);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Need_Level", pTableData->byNeed_Level);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Need_Class_Bit_Flag", pTableData->dwNeed_Class_Bit_Flag);		
//		AppendElementW(pXMLDoc, pItemTableNode, L"Class_Special", pTableData->byClass_Special);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Race_Special", pTableData->byRace_Special);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Need_Str", pTableData->byNeed_Str);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Need_Con", pTableData->byNeed_Con);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Need_Foc", pTableData->byNeed_Foc);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Need_Dex", pTableData->byNeed_Dex);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Need_Sol", pTableData->byNeed_Sol);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Need_Eng", pTableData->byNeed_Eng);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Set_Item_Tblidx", pTableData->set_Item_Tblidx);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Note", pTableData->Note);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Bag_Size", pTableData->byBag_Size);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Scouter_Watt", pTableData->wScouter_Watt);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Scouter_MaxPower", pTableData->dwScouter_MaxPower);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Scouter_Parts_Type", pTableData->byScouter_Parts_Type);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Scouter_Parts_Value", pTableData->byScouter_Parts_Value);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Use_Item_Tblidx", pTableData->Use_Item_Tblidx);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Item_Option_Tblidx", pTableData->Item_Option_Tblidx);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Item_Group", pTableData->byItemGroup);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Charm_Tblidx", pTableData->Charm_Tblidx);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Costume_Hide_Bit_Flag", pTableData->wCostumeHideBitFlag);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Need_Item_Tblidx", pTableData->NeedItemTblidx);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Common_Point", pTableData->CommonPoint);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Common_Point_Type", pTableData->byCommonPointType);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Need_Function", pTableData->byNeedFunction);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Use_Duration_Max", pTableData->dwUseDurationMax);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Duration_Type", pTableData->byDurationType);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Contents_Tblidx", pTableData->contentsTblidx);
//		AppendElementW(pXMLDoc, pItemTableNode, L"Duration_Group", pTableData->dwDurationGroup);		
//
//		// Add a line feed
//		pItemTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pItemTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_SkillTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CSkillTable* pSkillTable = m_pTableContainer->GetSkillTable();
//
//	if (pSkillTable == NULL)
//	{
//		printf("No SkillTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Skill_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_SkillTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create SkillTable XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pSkillTableNode;
//
//	for (iter = pSkillTable->Begin(); pSkillTable->End() != iter; iter++)
//	{
//		sSKILL_TBLDAT* pTableData = (sSKILL_TBLDAT*)(iter->second);
//
//		// SkillTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pSkillTableNode, L"Table_Data_KOR", NULL);
//		if (pSkillTableNode == NULL)
//		{
//			printf("Failed to create SkillTable XML node.\n");
//			return false;
//		}
//
//		// SkillTable.tblidx		
//		AppendElementW(pXMLDoc, pSkillTableNode, L"TblIdx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Skill_Name", pTableData->Skill_Name);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Name_Text", pTableData->wszNameText);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Validity_Able", pTableData->bValidity_Able?1:0);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"PC_Class_Bit_Flag", pTableData->dwPC_Class_Bit_Flag);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Skill_Class", pTableData->bySkill_Class);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Skill_Type", pTableData->bySkill_Type);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Skill_Active_Type", pTableData->bySkill_Active_Type);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Buff_Group", pTableData->byBuff_Group);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Slot_Index", pTableData->bySlot_Index);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Skill_Grade", pTableData->bySkill_Grade);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Function_Bit_Flag", pTableData->wFunction_Bit_Flag);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Appoint_Target", pTableData->byAppoint_Target);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Apply_Target", pTableData->byApply_Target);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Apply_Target_Max", pTableData->byApply_Target_Max);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Apply_Range", pTableData->byApply_Range);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Apply_Area_Size_1", pTableData->byApply_Area_Size_1);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Apply_Area_Size_2", pTableData->byApply_Area_Size_2);
//
//		for (int i = 0; i < MAX_EFFECT_IN_SKILL; i++)
//		{
//			WCHAR wszSkillEffect[50 + 1] = { 0 };
//			WCHAR wszSkillEffectType[50 + 1] = { 0 };
//			WCHAR wszSkillEffectValue[50 + 1] = { 0 };
//
//			_snwprintf(wszSkillEffect, 50, L"Skill_Effect_%d", i+1);
//			_snwprintf(wszSkillEffectType, 50, L"Skill_Effect_Type_%d", i+1);
//			_snwprintf(wszSkillEffectValue, 50, L"Skill_Effect_Value_%d", i+1);
//
//			AppendElementW(pXMLDoc, pSkillTableNode, wszSkillEffect, pTableData->skill_Effect[i]);
//			AppendElementW(pXMLDoc, pSkillTableNode, wszSkillEffectType, pTableData->bySkill_Effect_Type[i]);
//			AppendElementW_f(pXMLDoc, pSkillTableNode, wszSkillEffectValue, pTableData->fSkill_Effect_Value[i]);
//		}		
//
//		for (int i = 0; i < DBO_MAX_RP_BONUS_COUNT_PER_SKILL; i++)
//		{
//			WCHAR wszRpEffect[50 + 1] = { 0 };
//			WCHAR wszRpEffectValue[50 + 1] = { 0 };
//
//			_snwprintf(wszRpEffect, 50, L"RP_Effect_%d", i + 1);
//			_snwprintf(wszRpEffectValue, 50, L"RP_Effect_Value_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pSkillTableNode, wszRpEffect, pTableData->abyRpEffect[i]);
//			AppendElementW(pXMLDoc, pSkillTableNode, wszRpEffectValue, pTableData->adwRpEffectValue[i]);
//		}
//
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_Train_Level", pTableData->byRequire_Train_Level);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_Zenny", pTableData->dwRequire_Zenny);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Next_Skill_Train_Exp", pTableData->wNext_Skill_Train_Exp);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_SP", pTableData->wRequireSP);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Self_Train", pTableData->bSelfTrain);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_Skill_Tblidx_Min_1", pTableData->uiRequire_Skill_Tblidx_Min_1);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_Skill_Tblidx_Max_1", pTableData->uiRequire_Skill_Tblidx_Max_1);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_Skill_Tblidx_Min_2", pTableData->uiRequire_Skill_Tblidx_Min_2);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_Skill_Tblidx_Max_2", pTableData->uiRequire_Skill_Tblidx_Max_2);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Root_Skill", pTableData->Root_Skill);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_Epuip_Slot_Type", pTableData->byRequire_Epuip_Slot_Type);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_Item_Type", pTableData->byRequire_Item_Type);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Icon_Name", pTableData->szIcon_Name);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_LP", pTableData->wRequire_LP);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_EP", pTableData->wRequire_EP);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Require_RP_Ball", pTableData->byRequire_RP_Ball);
//		AppendElementW_f(pXMLDoc, pSkillTableNode, L"Casting_Time", pTableData->fCasting_Time);
//		//AppendElementW(pXMLDoc, pSkillTableNode, L"CastingTimeInMilliSecs", pTableData->dwCastingTimeInMilliSecs);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Cool_Time", pTableData->wCool_Time);
//		//AppendElementW(pXMLDoc, pSkillTableNode, L"CoolTimeInMilliSecs", pTableData->dwCoolTimeInMilliSecs);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Keep_Time", pTableData->wKeep_Time);
//		//AppendElementW(pXMLDoc, pSkillTableNode, L"KeepTimeInMilliSecs", pTableData->dwKeepTimeInMilliSecs);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Keep_Effect", pTableData->bKeep_Effect?1:0);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Use_Range_Min", pTableData->byUse_Range_Min);
//		//AppendElementW_f(pXMLDoc, pSkillTableNode, L"Use_Range_Min", pTableData->fUse_Range_Min);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"UseRangeMax", pTableData->byUse_Range_Max);
//		//AppendElementW_f(pXMLDoc, pSkillTableNode, L"Use_Range_Max", pTableData->fUse_Range_Max);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Note", pTableData->Note);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Next_Skill_Tblidx", pTableData->dwNextSkillTblidx);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Default_Display_Off", pTableData->bDefaultDisplayOff?1:0);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Casting_Animation_Start", pTableData->wCasting_Animation_Start);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Casting_Animation_Loop", pTableData->wCasting_Animation_Loop);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Action_Animation_Index", pTableData->wAction_Animation_Index);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Action_Loop_Animation_Index", pTableData->wAction_Loop_Animation_Index);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Action_End_Animation_Index", pTableData->wAction_End_Animation_Index);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Dash_Able", pTableData->bDash_Able?1:0);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Transform_Use_Info_Bit_Flag", pTableData->dwTransform_Use_Info_Bit_Flag);
//		AppendElementW_f(pXMLDoc, pSkillTableNode, L"Success_Rate", pTableData->fSuccess_Rate);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"Additional_Aggro_Point", pTableData->wAdditional_Aggro_Point);
//		AppendElementW(pXMLDoc, pSkillTableNode, L"PC_Class_Change", pTableData->byPC_Class_Change);
//
//		// Add a line feed
//		pSkillTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pSkillTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_TextAllTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	CTextAllTable* pTextAllTable = m_pTableContainer->GetTextAllTable();
//
//	if (pTextAllTable == NULL)
//	{
//		printf("No TextAllTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Text_All_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//
//	// Create TextAllTable
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pBlockNode;
//
//	AppendBlockElementW(pXMLDoc, pRoot, pBlockNode, L"Table_Data_KOR", NULL);
//	if (pBlockNode == NULL)
//	{
//		printf("Failed to create Table_Data_KOR XML node.\n");
//		return false;
//	}
//	
//	for (int nIndex = 0; nIndex < CTextAllTable::TABLE_COUNT; nIndex++)
//	{
//		int nTableType = nIndex;
//		CTextTable* pTextTable = pTextAllTable->GetTextTbl((CTextAllTable::TABLETYPE)nTableType);
//
//		if (NULL != pTextTable)
//		{			
//			int nFieldIdx = 2*nTableType + 1;
//			int nFieldText = nFieldIdx + 1;
//
//			WCHAR wszFieldNameIdx[50];
//			_snwprintf(wszFieldNameIdx, 50, L"F%d", nFieldIdx);
//			WCHAR wszFieldNameText[50];
//			_snwprintf(wszFieldNameText, 50, L"F%d", nFieldText);
//
//			// Add data segments
//			int i = 0;
//
//			for (iter = pTextTable->Begin(); pTextTable->End() != iter; iter++)
//			{
//				++i;
//				sTEXT_TBLDAT* pTableData = (sTEXT_TBLDAT*)(iter->second);
//
//				AppendElementW(pXMLDoc, pBlockNode, wszFieldNameIdx, pTableData->tblidx);
//				AppendElementW(pXMLDoc, pBlockNode, wszFieldNameText, (WCHAR *)pTableData->wstrText.c_str());
//			}		
//		}
//	}	
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return true;
//}
//
//bool CRdf2XmlHelper::SaveToXml_FormulaTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CFormulaTable* pFormulaTable = m_pTableContainer->GetFormulaTable();
//
//	if (pFormulaTable == NULL)
//	{
//		printf("No FormulaTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\TD_Formula.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_FormulaTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create FormulaTable XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pFormulaTableNode;
//
//	for (iter = pFormulaTable->Begin(); pFormulaTable->End() != iter; iter++)
//	{
//		sFORMULA_TBLDAT* pTableData = (sFORMULA_TBLDAT*)(iter->second);
//
//		// FormulaTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pFormulaTableNode, L"Table_Data_KOR", NULL);
//		if (pFormulaTableNode == NULL)
//		{
//			printf("Failed to create FormulaTable XML node.\n");
//			return false;
//		}
//
//		// FormulaTable.tblidx		
//		AppendElementW(pXMLDoc, pFormulaTableNode, L"Idx", pTableData->tblidx);
//	
//		
//		for (int i = 0; i < DBO_MAX_FORMULA_RATE_COUNT; i++)
//		{
//			WCHAR szBuffer[1024] = { 0x00, };
//			_snwprintf(szBuffer, 1024, L"Rate%d", i + 1);
//			AppendElementW_f(pXMLDoc, pFormulaTableNode, szBuffer, pTableData->afRate[i]);
//			
//		}
//
//		// Add a line feed
//		pFormulaTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pFormulaTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_PcTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CPCTable* pPcTable = m_pTableContainer->GetPcTable();
//
//	if (pPcTable == NULL)
//	{
//		printf("No PcTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Pc_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_PcTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Pc-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pPcTableNode;
//
//	for (iter = pPcTable->Begin(); pPcTable->End() != iter; iter++)
//	{
//		sPC_TBLDAT* pTableData = (sPC_TBLDAT*)(iter->second);
//
//		// PcTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pPcTableNode, L"Table_Data_KOR", NULL);
//		if (pPcTableNode == NULL)
//		{
//			printf("Failed to create PcTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pPcTableNode, L"TblIdx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Race", pTableData->byRace);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Gender", pTableData->byGender);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Class", pTableData->byClass);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Prior_Class_Tblidx", pTableData->prior_Class_Tblidx);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Class_Bit_Flag", pTableData->dwClass_Bit_Flag);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Model_Child", pTableData->szModel_Child);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Model_Adult", pTableData->szModel_Adult);
////		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_LP", pTableData->wBasic_LP);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_EP", pTableData->wBasic_EP);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_RP", pTableData->wBasic_RP);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Physical_Offence", pTableData->wBasic_Physical_Offence);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Physical_Defence", pTableData->wBasic_Physical_Defence);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Energy_Offence", pTableData->wBasic_Energy_Offence);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Energy_Defence", pTableData->wBasic_Energy_Defence);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Energy_Defence", pTableData->wBasic_Energy_Defence);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Str", pTableData->byStr);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Con", pTableData->byCon);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Foc", pTableData->byFoc);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Dex", pTableData->byDex);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Sol", pTableData->bySol);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Eng", pTableData->byEng);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Level_Up_LP", pTableData->byLevel_Up_LP);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Level_Up_EP", pTableData->byLevel_Up_EP);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Level_Up_RP", pTableData->byLevel_Up_RP);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Level_Up_Physical_Offence", pTableData->byLevel_Up_Physical_Offence);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Level_Up_Physical_Defence", pTableData->byLevel_Up_Physical_Defence);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Level_Up_Energy_Offence", pTableData->byLevel_Up_Energy_Offence);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Level_Up_Energy_Defence", pTableData->byLevel_Up_Energy_Defence);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Level_Up_Str", pTableData->fLevel_Up_Str);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Level_Up_Con", pTableData->fLevel_Up_Con);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Level_Up_Foc", pTableData->fLevel_Up_Foc);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Level_Up_Dex", pTableData->fLevel_Up_Dex);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Level_Up_Sol", pTableData->fLevel_Up_Sol);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Level_Up_Eng", pTableData->fLevel_Up_Eng);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Scale", pTableData->fScale);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Child_Run_Speed_Origin", pTableData->fChild_Run_Speed_Origin);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Child_Run_Speed", pTableData->fChild_Run_Speed);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Adult_Run_Speed_Origin", pTableData->fAdult_Run_Speed_Origin);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Adult_Run_Speed", pTableData->fAdult_Run_Speed);
////		AppendElementW_f(pXMLDoc, pPcTableNode, L"Radius", pTableData->fRadius);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Attack_Speed_Rate", pTableData->wAttack_Speed_Rate);
//		AppendElementW_f(pXMLDoc, pPcTableNode, L"Attack_Range", pTableData->fAttack_Range);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Attack_Rate", pTableData->wAttack_Rate);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Dodge_Rate", pTableData->wDodge_Rate);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Block_Rate", pTableData->wBlock_Rate);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Curse_Success_Rate", pTableData->wCurse_Success_Rate);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Curse_Tolerance_Rate", pTableData->wCurse_Tolerance_Rate);
//		AppendElementW(pXMLDoc, pPcTableNode, L"Basic_Aggro_Point", pTableData->wBasic_Aggro_Point);
//
//		// Add a line feed
//		pPcTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pPcTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_ExpTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CExpTable* pExpTable = m_pTableContainer->GetExpTable();
//
//	if (pExpTable == NULL)
//	{
//		printf("No ExpTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Exp_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_ExpTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Exp-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pExpTableNode;
//
//	for (iter = pExpTable->Begin(); pExpTable->End() != iter; iter++)
//	{
//		sEXP_TBLDAT* pTableData = (sEXP_TBLDAT*)(iter->second);
//
//		// ExpTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pExpTableNode, L"Table_Data_KOR", NULL);
//		if (pExpTableNode == NULL)
//		{
//			printf("Failed to create ExpTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pExpTableNode, L"Level", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pExpTableNode, L"EXP", pTableData->dwExp);
//		AppendElementW(pXMLDoc, pExpTableNode, L"Need_EXP", pTableData->dwNeed_Exp);
//		
//
//		// Add a line feed
//		pExpTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pExpTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_QuestTextTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CQuestTextDataTable* pQuestTextTable = m_pTableContainer->GetQuestTextDataTable();
//
//	if (pQuestTextTable == NULL)
//	{
//		printf("No QuestTextTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Quest_Text_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_QuestTextTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Exp-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pQuestTextTableNode;
//
//	for (iter = pQuestTextTable->Begin(); pQuestTextTable->End() != iter; iter++)
//	{
//		sQUEST_TEXT_DATA_TBLDAT* pTableData = (sQUEST_TEXT_DATA_TBLDAT*)(iter->second);
//
//		// QuestTextTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pQuestTextTableNode, L"Table_Data_KOR", NULL);
//		if (pQuestTextTableNode == NULL)
//		{
//			printf("Failed to create QuestTextTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pQuestTextTableNode, L"Quest_Text_Index", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pQuestTextTableNode, L"Quest_Text", (WCHAR *)pTableData->wstrText.c_str());
//
//
//		// Add a line feed
//		pQuestTextTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pQuestTextTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_ObjectTable(const char* pszPath, int worldID)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CObjectTable* pObjectTable = m_pTableContainer->GetObjectTable(worldID);
//	CWorldTable* pWorldTable = m_pTableContainer->GetWorldTable();
//	sWORLD_TBLDAT* pWorldDat = (sWORLD_TBLDAT*)pWorldTable->FindData(worldID);
//	if (pObjectTable == NULL)
//	{
//		printf("No ObjectTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//
//	
//	//convert from wide char to narrow char array
//	char ch[65];
//	char DefChar = ' ';
//	WideCharToMultiByte(CP_ACP, 0, pWorldDat->wszObjSpawn_Table_Name, -1, ch, 65, &DefChar, NULL);
//	std::string ss(ch);
//	
//	strPathFilename += "\\" + ss + ".xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_ObjectTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pObjectTableNode;
//
//	for (iter = pObjectTable->Begin(); pObjectTable->End() != iter; iter++)
//	{
//		sOBJECT_TBLDAT* pTableData = (sOBJECT_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pObjectTableNode, L"Table_Data_KOR", NULL);
//		if (pObjectTableNode == NULL)
//		{
//			printf("Failed to create ObjectTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pObjectTableNode, L"TblIdx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pObjectTableNode, L"Name", pTableData->dwName);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Loc_X", pTableData->vLoc.x);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Loc_Y", pTableData->vLoc.y);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Loc_Z", pTableData->vLoc.z);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Dir_X", pTableData->vDir.x);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Dir_Y", pTableData->vDir.y);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Dir_Z", pTableData->vDir.z);
//		AppendElementW(pXMLDoc, pObjectTableNode, L"Func", pTableData->wFunction);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Min_X", pTableData->vMin.x);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Min_Y", pTableData->vMin.y);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Min_Z", pTableData->vMin.z);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Max_X", pTableData->vMax.x);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Max_Y", pTableData->vMax.y);
//		AppendElementW_f(pXMLDoc, pObjectTableNode, L"Max_Z", pTableData->vMax.z);
//		AppendElementW(pXMLDoc, pObjectTableNode, L"DefMainState", pTableData->byDefMainState);
//		AppendElementW(pXMLDoc, pObjectTableNode, L"DefSubState", pTableData->byDefSubState);
//		
//		WCHAR wszBuffer[50] = { 0x00, };
//		for (int i = 0; i < DBO_MAX_OBJECT_STATE; i++)
//		{
//			swprintf(wszBuffer, 150, L"State%d", i + 1);
//
//			AppendElementW(pXMLDoc, pObjectTableNode, wszBuffer, pTableData->abyState[i][i]);
//		}
//		for (int i = 0; i < DBO_MAX_OBJECT_STATE; i++)
//		{
//			swprintf(wszBuffer, 150, L"Click_Sound%d", i + 1);
//
//			AppendElementW(pXMLDoc, pObjectTableNode, wszBuffer, pTableData->achClickSound[i][i]);
//		}
//		AppendElementW(pXMLDoc, pObjectTableNode, L"Boundry_Distance", pTableData->byBoundaryDistance);
//		AppendElementW(pXMLDoc, pObjectTableNode, L"ModelName", pTableData->szModelName);
//		AppendElementW(pXMLDoc, pObjectTableNode, L"Note", pTableData->dwSequence);
//		AppendElementW(pXMLDoc, pObjectTableNode, L"Contents_Tblidx", pTableData->byDefSubState);
//		AppendElementW(pXMLDoc, pObjectTableNode, L"Object_Direction_Index", pTableData->objectDirectionIndex);
//		AppendElementW(pXMLDoc, pObjectTableNode, L"MinQuestId", pTableData->minQuestId);
//		AppendElementW(pXMLDoc, pObjectTableNode, L"MaxQuestId", pTableData->maxQuestId);
//
//		// Add a line feed
//		pObjectTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pObjectTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_PortalTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CPortalTable* pPortalTable = m_pTableContainer->GetPortalTable();
//
//	if (pPortalTable == NULL)
//	{
//		printf("No PortalTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Portal_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_PortalTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pPortalTableNode;
//
//	for (iter = pPortalTable->Begin(); pPortalTable->End() != iter; iter++)
//	{
//		sPORTAL_TBLDAT* pTableData = (sPORTAL_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pPortalTableNode, L"Table_Data_KOR", NULL);
//		if (pPortalTableNode == NULL)
//		{
//			printf("Failed to create PortalTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pPortalTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pPortalTableNode, L"Point_Name", pTableData->dwPointName);
//		AppendElementW(pXMLDoc, pPortalTableNode, L"Point_Name_Text", pTableData->szPointNameText);
//		AppendElementW(pXMLDoc, pPortalTableNode, L"World", pTableData->worldId);
//		AppendElementW_f(pXMLDoc, pPortalTableNode, L"Loc_X", pTableData->vLoc.x);
//		AppendElementW_f(pXMLDoc, pPortalTableNode, L"Loc_Y", pTableData->vLoc.y);
//		AppendElementW_f(pXMLDoc, pPortalTableNode, L"Loc_Z", pTableData->vLoc.z);
//		AppendElementW_f(pXMLDoc, pPortalTableNode, L"Dir_X", pTableData->vDir.x);
//		AppendElementW_f(pXMLDoc, pPortalTableNode, L"Dir_Y", pTableData->vDir.y);
//		AppendElementW_f(pXMLDoc, pPortalTableNode, L"Dir_Z", pTableData->vDir.z);
//		AppendElementW_f(pXMLDoc, pPortalTableNode, L"Map_X", pTableData->vMap.x);
//		AppendElementW_f(pXMLDoc, pPortalTableNode, L"Map_Y", pTableData->vMap.y);
//		
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < DBO_MAX_POINT_PORTAL; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Point_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pPortalTableNode, wszBuffer, pTableData->aPoint[i]);
//		}
//		for (int i = 0; i < DBO_MAX_POINT_PORTAL; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Zeny_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pPortalTableNode, wszBuffer, pTableData->adwPointZenny[i]);
//		}
//		// Add a line feed
//		pPortalTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pPortalTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_WorldTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CWorldTable* pWorldTable = m_pTableContainer->GetWorldTable();
//
//	if (pWorldTable == NULL)
//	{
//		printf("No WorldTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_World_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_WorldTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pWorldTableNode;
//
//	for (iter = pWorldTable->Begin(); pWorldTable->End() != iter; iter++)
//	{
//		sWORLD_TBLDAT* pTableData = (sWORLD_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pWorldTableNode, L"Table_Data_KOR", NULL);
//		if (pWorldTableNode == NULL)
//		{
//			printf("Failed to create WorldTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Name", pTableData->wszName);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Dynamic_Able", pTableData->bDynamic);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Dynamic_Create_Count", pTableData->nCreateCount);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Field_Door_Type", pTableData->byDoorType);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Mob_Spawn_Table_Name", pTableData->wszMobSpawn_Table_Name);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"NPC_Spawn_Table_Name", pTableData->wszNpcSpawn_Table_Name);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Object_Spawn_Table_Name", pTableData->wszObjSpawn_Table_Name);
//
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Field_Start_Loc_X", pTableData->vStart.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Field_Start_Loc_Z", pTableData->vStart.z);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Field_End_Loc_X", pTableData->vEnd.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Field_End_Loc_Z", pTableData->vEnd.z);
//		
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Battle_Start_Loc_X", pTableData->vBattleStartLoc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Battle_Start_Loc_Z", pTableData->vBattleStartLoc.z);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Battle_End_Loc_X", pTableData->vBattleEndLoc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Battle_End_Loc_Z", pTableData->vBattleEndLoc.z);
//
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Outside_Battle_Start_Loc_X", pTableData->vOutSideBattleStartLoc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Outside_Battle_Start_Loc_Z", pTableData->vOutSideBattleStartLoc.z);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Outside_Battle_End_Loc_X", pTableData->vOutSideBattleEndLoc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Outside_Battle_End_Loc_Z", pTableData->vOutSideBattleEndLoc.z);
//
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Spectator_Start_Loc_X", pTableData->vSpectatorStartLoc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Spectator_Start_Loc_Z", pTableData->vSpectatorStartLoc.z);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Spectator_End_Loc_X", pTableData->vSpectatorEndLoc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Spectator_End_Loc_Z", pTableData->vSpectatorEndLoc.z);
//
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Default_Loc_X", pTableData->vDefaultLoc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Default_Loc_Y", pTableData->vDefaultLoc.y);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Default_Loc_Z", pTableData->vDefaultLoc.z);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Default_Dir_X", pTableData->vDefaultDir.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Default_Dri_Y", pTableData->vDefaultDir.y);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Default_Dir_Z", pTableData->vDefaultDir.z);
//
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Start1_Point_Loc_X", pTableData->vStart1Loc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Start1_Point_Loc_Y", pTableData->vStart1Loc.y);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Start1_Point_Loc_Z", pTableData->vStart1Loc.z);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Start1_Point_Dir_X", pTableData->vStart1Dir.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Start1_Point_Dir_Z", pTableData->vStart1Dir.z);
//
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Start2_Point_Loc_X", pTableData->vStart2Loc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Start2_Point_Loc_Y", pTableData->vStart2Loc.y);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Start2_Point_Loc_Z", pTableData->vStart2Loc.z);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Start2_Point_Dir_X", pTableData->vStart2Dir.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Start2_Point_Dir_Z", pTableData->vStart2Dir.z);
//
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Standard_Loc_X", pTableData->vStandardLoc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Standard_Loc_Z", pTableData->vStandardLoc.z);
//
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Field_Destroy_Time", pTableData->dwDestroyTimeInMilliSec);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Split_Size", pTableData->fSplitSize);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Night_Able", pTableData->bNight_Able);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Static_Time", pTableData->byStatic_Time);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"funcflag", pTableData->wFuncFlag);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"World_Rule_Type", pTableData->byWorldRuleType);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"World_Rule_Index", pTableData->worldRuleTbldx);
//
//		AppendElementW(pXMLDoc, pWorldTableNode, L"OutField_Tblidx", pTableData->outWorldTblidx);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Out_Field_Loc_X", pTableData->outWorldLoc.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Out_Field_Loc_Z", pTableData->outWorldLoc.z);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Out_Field_Dir_X", pTableData->outWorldDir.x);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"Out_Field_Dir_Z", pTableData->outWorldDir.z);
//		
//		AppendElementW(pXMLDoc, pWorldTableNode, L"ResourceFolder", pTableData->wszResourceFolder);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"BGM_Rest_Time", pTableData->fBGMRestTime);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"World_Resource_ID", pTableData->dwWorldResourceID);
//		AppendElementW_f(pXMLDoc, pWorldTableNode, L"FreeCamera_Height", pTableData->fFreeCamera_Height);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Enter_Resource_Flash", pTableData->wszEnterResourceFlash);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"Leave_Resource_Flash", pTableData->wszLeaveResourceFlash);
//		AppendElementW(pXMLDoc, pWorldTableNode, L"WPS_Link_Index", pTableData->wpsLinkIndex);
//
//		// Add a line feed
//		pWorldTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pWorldTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_MobSpawnTable(const char* pszPath, int worldID)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CSpawnTable* pSpawnTable = m_pTableContainer->GetMobSpawnTable(worldID);
//	CWorldTable* pWorldTable = m_pTableContainer->GetWorldTable();
//	sWORLD_TBLDAT* pWorldDat = (sWORLD_TBLDAT*)pWorldTable->FindData(worldID);
//	if (pSpawnTable == NULL)
//	{
//		printf("No MobSpawnTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//
//
//	//convert from wide char to narrow char array
//	char ch[65];
//	char DefChar = ' ';
//	WideCharToMultiByte(CP_ACP, 0, pWorldDat->wszMobSpawn_Table_Name, -1, ch, 65, &DefChar, NULL);
//	std::string ss(ch);
//
//	strPathFilename += "\\" + ss + ".xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_SpawnTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pSpawnTableNode;
//
//	for (iter = pSpawnTable->Begin(); pSpawnTable->End() != iter; iter++)
//	{
//		sSPAWN_TBLDAT* pTableData = (sSPAWN_TBLDAT*)(iter->second);
//
//		// SpawnTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pSpawnTableNode, L"Table_Data_KOR", NULL);
//		if (pSpawnTableNode == NULL)
//		{
//			printf("Failed to create MobSpawnTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Mob_Tblidx", pTableData->mob_Tblidx);
//		
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Spawn_Loc_X", pTableData->vSpawn_Loc.x);
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Spawn_Loc_Y", pTableData->vSpawn_Loc.y);
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Spawn_Loc_Z", pTableData->vSpawn_Loc.z);
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Spawn_Dir_X", pTableData->vSpawn_Dir.x);
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Spawn_Dir_Z", pTableData->vSpawn_Dir.z);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Spawn_Loc_Range", pTableData->bySpawn_Loc_Range);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Spawn_Quantity", pTableData->bySpawn_Quantity);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Spawn_Cool_Time", pTableData->wSpawn_Cool_Time);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Spawn_Move_Type", pTableData->bySpawn_Move_Type);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Wander_Range", pTableData->byWander_Range);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Move_Range", pTableData->byMove_Range);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Move_Delay_Time", pTableData->byMove_DelayTime);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Path_Table_Index", pTableData->path_Table_Index);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Path_Table_Index", pTableData->path_Table_Index);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"PlayScript_Number", pTableData->playScript);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"PlayScript_Scene_Number", pTableData->playScriptScene);
//		
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"AIScript_Number", pTableData->aiScript);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"AIScript_Scene_Number", pTableData->aiScriptScene);
//
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Follow_Distance_Loc_X", pTableData->vFollowDistance.x);
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Follow_Distance_Loc_Z", pTableData->vFollowDistance.z);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Party_Index", pTableData->dwParty_Index);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Party_Leader_Able", pTableData->bParty_Leader);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Spawn_Group", pTableData->spawnGroupId);
//
//		// Add a line feed
//		pSpawnTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pSpawnTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_NPCSpawnTable(const char* pszPath, int worldID)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CSpawnTable* pSpawnTable = m_pTableContainer->GetNpcSpawnTable(worldID);
//	CWorldTable* pWorldTable = m_pTableContainer->GetWorldTable();
//	sWORLD_TBLDAT* pWorldDat = (sWORLD_TBLDAT*)pWorldTable->FindData(worldID);
//	if (pSpawnTable == NULL)
//	{
//		printf("No NpcSpawnTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//
//
//	//convert from wide char to narrow char array
//	char ch[65];
//	char DefChar = ' ';
//	WideCharToMultiByte(CP_ACP, 0, pWorldDat->wszNpcSpawn_Table_Name, -1, ch, 65, &DefChar, NULL);
//	std::string ss(ch);
//
//	strPathFilename += "\\" + ss + ".xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_SpawnTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pSpawnTableNode;
//
//	for (iter = pSpawnTable->Begin(); pSpawnTable->End() != iter; iter++)
//	{
//		sSPAWN_TBLDAT* pTableData = (sSPAWN_TBLDAT*)(iter->second);
//
//		// SpawnTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pSpawnTableNode, L"Table_Data_KOR", NULL);
//		if (pSpawnTableNode == NULL)
//		{
//			printf("Failed to create NPCSpawnTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Mob_Tblidx", pTableData->mob_Tblidx);
//
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Spawn_Loc_X", pTableData->vSpawn_Loc.x);
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Spawn_Loc_Y", pTableData->vSpawn_Loc.y);
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Spawn_Loc_Z", pTableData->vSpawn_Loc.z);
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Spawn_Dir_X", pTableData->vSpawn_Dir.x);
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Spawn_Dir_Z", pTableData->vSpawn_Dir.z);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Spawn_Loc_Range", pTableData->bySpawn_Loc_Range);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Spawn_Quantity", pTableData->bySpawn_Quantity);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Spawn_Cool_Time", pTableData->wSpawn_Cool_Time);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Spawn_Move_Type", pTableData->bySpawn_Move_Type);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Wander_Range", pTableData->byWander_Range);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Move_Range", pTableData->byMove_Range);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Move_Delay_Time", pTableData->byMove_DelayTime);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Path_Table_Index", pTableData->path_Table_Index);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Path_Table_Index", pTableData->path_Table_Index);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"PlayScript_Number", pTableData->playScript);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"PlayScript_Scene_Number", pTableData->playScriptScene);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"AIScript_Number", pTableData->aiScript);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"AIScript_Scene_Number", pTableData->aiScriptScene);
//
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Follow_Distance_Loc_X", pTableData->vFollowDistance.x);
//		AppendElementW_f(pXMLDoc, pSpawnTableNode, L"Follow_Distance_Loc_Z", pTableData->vFollowDistance.z);
//
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Party_Index", pTableData->dwParty_Index);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Party_Leader_Able", pTableData->bParty_Leader ? 1 : 0);
//		AppendElementW(pXMLDoc, pSpawnTableNode, L"Spawn_Group", pTableData->spawnGroupId);
//
//		// Add a line feed
//		pSpawnTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pSpawnTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_LandMarkTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CLandMarkTable* pLandmarkTable = m_pTableContainer->GetLandMarkTable();
//
//	if (pLandmarkTable == NULL)
//	{
//		printf("No LandmarkTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Landmark_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_LandMarkTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pLandmarkTableNode;
//
//	for (iter = pLandmarkTable->Begin(); pLandmarkTable->End() != iter; iter++)
//	{
//		sLAND_MARK_TBLDAT* pTableData = (sLAND_MARK_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pLandmarkTableNode, L"Table_Data_KOR", NULL);
//		if (pLandmarkTableNode == NULL)
//		{
//			printf("Failed to create WorldTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Landmark_Name", pTableData->LandmarkName);
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Landmark_Type", pTableData->byLandmarkType);
//		
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Name_Text", pTableData->wszNameText);
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Validity_Able", pTableData->bValidityAble);
//		
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Landmark_BitFlag", pTableData->byLandmarkBitflag);
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Landmark_Display_BitFlag", pTableData->byLandmarkDisplayBitFlag);
//		
//		AppendElementW_f(pXMLDoc, pLandmarkTableNode, L"Landmark_Loc_X", pTableData->LandmarkLoc.x);
//		AppendElementW_f(pXMLDoc, pLandmarkTableNode, L"Landmark_Loc_Z", pTableData->LandmarkLoc.z);
//
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Link_Map_Idx", pTableData->LinkMapIdx);
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Link_Warfog_Idx", pTableData->wLinkWarfogIdx);
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Icon_Name", pTableData->wszIconName);
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Icon_Size", pTableData->byIconSize);
//		AppendElementW(pXMLDoc, pLandmarkTableNode, L"Note", pTableData->Note);
//
//		// Add a line feed
//		pLandmarkTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pLandmarkTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_WorldMapTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CWorldMapTable* pWorldmapTable = m_pTableContainer->GetWorldMapTable();
//
//	if (pWorldmapTable == NULL)
//	{
//		printf("No WorldmapTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Worldmap_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_WorldMapTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pWorldmapTableNode;
//
//	for (iter = pWorldmapTable->Begin(); pWorldmapTable->End() != iter; iter++)
//	{
//		sWORLD_MAP_TBLDAT* pTableData = (sWORLD_MAP_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pWorldmapTableNode, L"Table_Data_KOR", NULL);
//		if (pWorldmapTableNode == NULL)
//		{
//			printf("Failed to create WorldTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pWorldmapTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pWorldmapTableNode, L"World_Tblidx", pTableData->World_Tblidx);
//		AppendElementW(pXMLDoc, pWorldmapTableNode, L"Zone_Tblidx", pTableData->Zone_Tblidx);
//		AppendElementW(pXMLDoc, pWorldmapTableNode, L"Worldmap_Name", pTableData->Worldmap_Name);
//		AppendElementW(pXMLDoc, pWorldmapTableNode, L"Name_Text", pTableData->wszNameText);
//		AppendElementW(pXMLDoc, pWorldmapTableNode, L"Validity_Able", pTableData->bValidityAble ? 1 : 0);
//
//		AppendElementW(pXMLDoc, pWorldmapTableNode, L"Map_Type", pTableData->byMapType);
//		AppendElementW_f(pXMLDoc, pWorldmapTableNode, L"Standard_Loc_X", pTableData->vStandardLoc.x);
//		AppendElementW_f(pXMLDoc, pWorldmapTableNode, L"Standard_Loc_Z", pTableData->vStandardLoc.z);
//		AppendElementW_f(pXMLDoc, pWorldmapTableNode, L"Worldmap_Scale", pTableData->fWorldmapScale);
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < DBO_WORLD_MAP_TABLE_COUNT_WORLD_WARFOG; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Warfog_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pWorldmapTableNode, wszBuffer, pTableData->wWarfog[i]);
//		}
//
//		
//
//		// Add a line feed
//		pWorldmapTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pWorldmapTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_WorldPlayTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CWorldPlayTable* pWorldPlayTable = m_pTableContainer->GetWorldPlayTable();
//
//	if (pWorldPlayTable == NULL)
//	{
//		printf("No WorldPlayTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_WorldPlay_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_WorldPlayTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pWorldPlayTableNode;
//
//	for (iter = pWorldPlayTable->Begin(); pWorldPlayTable->End() != iter; iter++)
//	{
//		sWORLDPLAY_TBLDAT* pTableData = (sWORLDPLAY_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pWorldPlayTableNode, L"Table_Data_KOR", NULL);
//		if (pWorldPlayTableNode == NULL)
//		{
//			printf("Failed to create WorldPlayTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pWorldPlayTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pWorldPlayTableNode, L"Group", pTableData->dwGroup);
//		AppendElementW(pXMLDoc, pWorldPlayTableNode, L"ExecuterType", pTableData->byExecuterType);
//		AppendElementW(pXMLDoc, pWorldPlayTableNode, L"ShareType", pTableData->byShareType);
//		AppendElementW(pXMLDoc, pWorldPlayTableNode, L"ShareLimitTime", pTableData->dwShareLimitTime);
//		AppendElementW(pXMLDoc, pWorldPlayTableNode, L"Desc", "");
//
//		// Add a line feed
//		pWorldPlayTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pWorldPlayTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_WorldZoneTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CWorldZoneTable* pWorldZoneTable = m_pTableContainer->GetWorldZoneTable();
//
//	if (pWorldZoneTable == NULL)
//	{
//		printf("No WorldZoneTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_World_Zone_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_WorldZoneTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pWorldZoneTableNode;
//
//	for (iter = pWorldZoneTable->Begin(); pWorldZoneTable->End() != iter; iter++)
//	{
//		sWORLD_ZONE_TBLDAT* pTableData = (sWORLD_ZONE_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pWorldZoneTableNode, L"Table_Data_KOR", NULL);
//		if (pWorldZoneTableNode == NULL)
//		{
//			printf("Failed to create WorldZoneTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pWorldZoneTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pWorldZoneTableNode, L"Function_Bit_Flag", pTableData->wFunctionBitFlag);
//		AppendElementW(pXMLDoc, pWorldZoneTableNode, L"World", pTableData->worldTblidx);
//		AppendElementW(pXMLDoc, pWorldZoneTableNode, L"Name", pTableData->nameTblidx);
//		AppendElementW(pXMLDoc, pWorldZoneTableNode, L"Name_Text", pTableData->wszName_Text);
//		AppendElementW(pXMLDoc, pWorldZoneTableNode, L"Forbidden_Vehicle", pTableData->bForbidden_Vehicle);
//
//		// Add a line feed
//		pWorldZoneTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pWorldZoneTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_DynamicObjectTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CDynamicObjectTable* pDynamicObjectTable = m_pTableContainer->GetDynamicObjectTable();
//
//	if (pDynamicObjectTable == NULL)
//	{
//		printf("No DynamicObjectTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Dynamic_Object_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_DynamicObjectTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pDynamicObjectTableNode;
//
//	for (iter = pDynamicObjectTable->Begin(); pDynamicObjectTable->End() != iter; iter++)
//	{
//		sDYNAMIC_OBJECT_TBLDAT* pTableData = (sDYNAMIC_OBJECT_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pDynamicObjectTableNode, L"Table_Data_KOR", NULL);
//		if (pDynamicObjectTableNode == NULL)
//		{
//			printf("Failed to create DynamicObjectTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"Validity_Able", pTableData->bValidityAble ? 1 : 0);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"Type", pTableData->byType);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"Model_Name", pTableData->szModelName);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"State_Type", pTableData->byStateType);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"Spawn_Animation", pTableData->spawnAnimation);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"Idle_Animation", pTableData->idleAnimation);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"Despawn_Animation", pTableData->despawnAnimation);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"State1_Animation", pTableData->state1Animation);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"State2_Animation", pTableData->state2Animation);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"Boundary_Distance", pTableData->byBoundaryDistance);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"Despawn_Distance", pTableData->byDespawnDistance);
//		AppendElementW(pXMLDoc, pDynamicObjectTableNode, L"Note", "");
//
//		// Add a line feed
//		pDynamicObjectTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pDynamicObjectTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_VehicleTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CVehicleTable* pVehicleTable = m_pTableContainer->GetVehicleTable();
//
//	if (pVehicleTable == NULL)
//	{
//		printf("No VehicleTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Vehicle_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_VehicleTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pVehicleTableNode;
//
//	for (iter = pVehicleTable->Begin(); pVehicleTable->End() != iter; iter++)
//	{
//		sVEHICLE_TBLDAT* pTableData = (sVEHICLE_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pVehicleTableNode, L"Table_Data_KOR", NULL);
//		if (pVehicleTableNode == NULL)
//		{
//			printf("Failed to create VehicleTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pVehicleTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pVehicleTableNode, L"Model_Name", pTableData->szModelName);
//		AppendElementW(pXMLDoc, pVehicleTableNode, L"SRP_Type", pTableData->bySRPType);
//		AppendElementW(pXMLDoc, pVehicleTableNode, L"Speed", pTableData->bySpeed);
//		AppendElementW(pXMLDoc, pVehicleTableNode, L"Vehicle_Type", pTableData->byVehicleType);
//		AppendElementW(pXMLDoc, pVehicleTableNode, L"Run_Height", pTableData->wRunHeight);
//		AppendElementW(pXMLDoc, pVehicleTableNode, L"Personnel", pTableData->byPersonnel);
//
//		// Add a line feed
//		pVehicleTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pVehicleTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_MobMovePatternTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CMobMovePatternTable* pMobMovePatternTable = m_pTableContainer->GetMobMovePatternTable();
//
//	if (pMobMovePatternTable == NULL)
//	{
//		printf("No MobMovePatternTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Mob_Move_Pattern_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_MobMovePatternTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pMobMovePatternTableNode;
//
//	for (iter = pMobMovePatternTable->Begin(); pMobMovePatternTable->End() != iter; iter++)
//	{
//		sMOVE_PATTERN_TBLDAT* pTableData = (sMOVE_PATTERN_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pMobMovePatternTableNode, L"Table_Data_KOR", NULL);
//		if (pMobMovePatternTableNode == NULL)
//		{
//			printf("Failed to create MobMovePattern XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pMobMovePatternTableNode, L"Tblidx", pTableData->tblidx);
//		
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < DBO_MAX_COUNT_MOVE_PATTERN; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Pattern_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pMobMovePatternTableNode, wszBuffer, pTableData->abyPattern[i]);
//		}
//		// Add a line feed
//		pMobMovePatternTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pMobMovePatternTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_DirectionLinkTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CDirectionLinkTable* pDirectionLinkTable = m_pTableContainer->GetDirectionLinkTable();
//
//	if (pDirectionLinkTable == NULL)
//	{
//		printf("No DirectionLinkTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Direction_Link_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_DirectionLinkTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pDirectionLinkTableNode;
//
//	for (iter = pDirectionLinkTable->Begin(); pDirectionLinkTable->End() != iter; iter++)
//	{
//		sDIRECTION_LINK_TBLDAT* pTableData = (sDIRECTION_LINK_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pDirectionLinkTableNode, L"Table_Data_KOR", NULL);
//		if (pDirectionLinkTableNode == NULL)
//		{
//			printf("Failed to create DirectionLinkTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pDirectionLinkTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pDirectionLinkTableNode, L"Function_Name", pTableData->szFunctionName);
//		AppendElementW(pXMLDoc, pDirectionLinkTableNode, L"Note", pTableData->szNote);
//		AppendElementW(pXMLDoc, pDirectionLinkTableNode, L"Type", pTableData->byType);
//		AppendElementW(pXMLDoc, pDirectionLinkTableNode, L"Animation_ID", pTableData->dwAnimationID);
//		AppendElementW(pXMLDoc, pDirectionLinkTableNode, L"Direction_Func_Flag", pTableData->byFuncFlag);
//
//		// Add a line feed
//		pDirectionLinkTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pDirectionLinkTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_ScriptLinkTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CScriptLinkTable* pScriptLinkTable = m_pTableContainer->GetScriptLinkTable();
//
//	if (pScriptLinkTable == NULL)
//	{
//		printf("No ScriptLinkTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Script_Link_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_ScriptLinkTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pScriptLinkTableNode;
//
//	for (iter = pScriptLinkTable->Begin(); pScriptLinkTable->End() != iter; iter++)
//	{
//		sSCRIPT_LINK_TBLDAT* pTableData = (sSCRIPT_LINK_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pScriptLinkTableNode, L"Table_Data_KOR", NULL);
//		if (pScriptLinkTableNode == NULL)
//		{
//			printf("Failed to create ScriptLinkTable XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pScriptLinkTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pScriptLinkTableNode, L"Value", pTableData->wszValue);
//		AppendElementW(pXMLDoc, pScriptLinkTableNode, L"Type", pTableData->byType);
//		AppendElementW(pXMLDoc, pScriptLinkTableNode, L"Action", pTableData->byAction);
//		// Add a line feed
//		pScriptLinkTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pScriptLinkTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_QuestNarrationTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CQuestNarrationTable* pQuestNarrationTable = m_pTableContainer->GetQuestNarrationTable();
//
//	if (pQuestNarrationTable == NULL)
//	{
//		printf("No QuestNarrationTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Quest_Narration_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_QuestNarrationTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pQuestNarrationTableNode;
//
//	for (iter = pQuestNarrationTable->Begin(); pQuestNarrationTable->End() != iter; iter++)
//	{
//		sQUEST_NARRATION_TBLDAT* pTableData = (sQUEST_NARRATION_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pQuestNarrationTableNode, L"Table_Data_KOR", NULL);
//		if (pQuestNarrationTableNode == NULL)
//		{
//			printf("Failed to create QuestNarration XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pQuestNarrationTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pQuestNarrationTableNode, L"Type", pTableData->bType);
//		AppendElementW(pXMLDoc, pQuestNarrationTableNode, L"Number", pTableData->byNumber);
//		AppendElementW(pXMLDoc, pQuestNarrationTableNode, L"Time", pTableData->byTime);
//
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
//		{
//			swprintf(wszBuffer, 1024, L"UIShowHideDirection_%d", i + 1);
//			AppendElementW(pXMLDoc, pQuestNarrationTableNode, wszBuffer, pTableData->asData[i].byUIShowHideDirection);
//		}
//		for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
//		{
//			swprintf(wszBuffer, 1024, L"OwnerType_%d", i + 1);
//			AppendElementW(pXMLDoc, pQuestNarrationTableNode, wszBuffer, pTableData->asData[i].byOwnerType);
//		}
//		for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Owner_%d", i + 1);
//			AppendElementW(pXMLDoc, pQuestNarrationTableNode, wszBuffer, pTableData->asData[i].dwOwner);
//		}
//		for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Condition_%d", i + 1);
//			AppendElementW(pXMLDoc, pQuestNarrationTableNode, wszBuffer, pTableData->asData[i].byCondition);
//		}
//		for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Direction_%d", i + 1);
//			AppendElementW(pXMLDoc, pQuestNarrationTableNode, wszBuffer, pTableData->asData[i].byDirection);
//		}
//		for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Dialog_%d", i + 1);
//			AppendElementW(pXMLDoc, pQuestNarrationTableNode, wszBuffer, pTableData->asData[i].dwDialog);
//		}
//		for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
//		{
//			swprintf(wszBuffer, 1024, L"UiType_%d", i + 1);
//			AppendElementW(pXMLDoc, pQuestNarrationTableNode, wszBuffer, pTableData->asData[i].byUiType);
//		}
//		for (int i = 0; i < DBO_MAX_COUNT_OF_NARRATION; i++)
//		{
//			swprintf(wszBuffer, 1024, L"UIDirection_%d", i + 1);
//			AppendElementW(pXMLDoc, pQuestNarrationTableNode, wszBuffer, pTableData->asData[i].byUIDirection);
//		}
//		// Add a line feed
//		pQuestNarrationTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pQuestNarrationTableNode = NULL;
//	}
//
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_BasicDropTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CBasicDropTable* pBasicDropTable = m_pTableContainer->GetBasicDropTable();
//
//	if (pBasicDropTable == NULL)
//	{
//		printf("No BasicDropTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Basic_Drop_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_BasicDropTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pBasicDropTableNode;
//
//	for (iter = pBasicDropTable->Begin(); pBasicDropTable->End() != iter; iter++)
//	{
//		sBASIC_DROP_TBLDAT* pTableData = (sBASIC_DROP_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pBasicDropTableNode, L"Table_Data_KOR", NULL);
//		if (pBasicDropTableNode == NULL)
//		{
//			printf("Failed to create BasicDrop XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pBasicDropTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pBasicDropTableNode, L"Max", pTableData->byMax);
//
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Normal_Tblidx_Rate_%d", i + 1);
//			AppendElementW_f(pXMLDoc, pBasicDropTableNode, wszBuffer, pTableData->afNoramalTblidxRate[i]);
//		}
//		for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Normal_Drop_Tblidx_%d", i + 1);
//			AppendElementW(pXMLDoc, pBasicDropTableNode, wszBuffer, pTableData->aNoramalDropTblidx[i]);
//		}
//
//		for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Superior_Tblidx_Rate_%d", i + 1);
//			AppendElementW_f(pXMLDoc, pBasicDropTableNode, wszBuffer, pTableData->afSuperiorTblidxRate[i]);
//		}
//		for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Superior_Drop_Tblidx_%d", i + 1);
//			AppendElementW(pXMLDoc, pBasicDropTableNode, wszBuffer, pTableData->aSuperiorDropTblidx[i]);
//		}
//
//		AppendElementW_f(pXMLDoc, pBasicDropTableNode, L"Superior_Drop_Rate_Control", pTableData->fSuperior_Drop_Rate_Control);
//		AppendElementW_f(pXMLDoc, pBasicDropTableNode, L"Superior_Option_Rate_Control", pTableData->fSuperior_Option_Rate_Control);
//
//		for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Excellent_Tblidx_Rate_%d", i + 1);
//			AppendElementW_f(pXMLDoc, pBasicDropTableNode, wszBuffer, pTableData->afExcellentTblidxRate[i]);
//		}
//		for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Excellent_Drop_Tblidx_%d", i + 1);
//			AppendElementW(pXMLDoc, pBasicDropTableNode, wszBuffer, pTableData->aExcellentDropTblidx[i]);
//		}
//
//		AppendElementW_f(pXMLDoc, pBasicDropTableNode, L"Excellent_Drop_Rate_Control", pTableData->fExcellent_Drop_Rate_Control);
//
//		for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Legendary_Tblidx_Rate_%d", i + 1);
//			AppendElementW_f(pXMLDoc, pBasicDropTableNode, wszBuffer, pTableData->afLegendaryTblidxRate[i]);
//		}
//		for (int i = 0; i < MAX_DROP_TABLE_SELECT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Legendary_Drop_Tblidx_%d", i + 1);
//			AppendElementW(pXMLDoc, pBasicDropTableNode, wszBuffer, pTableData->aLegendaryDropTblidx[i]);
//		}
//
//		AppendElementW_f(pXMLDoc, pBasicDropTableNode, L"Legendary_Drop_Rate_Control", pTableData->fLegendary_Drop_Rate_Control);
//
//		// Add a line feed
//		pBasicDropTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pBasicDropTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_EachDropTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CEachDropTable* pEachDropTable = m_pTableContainer->GetEachDropTable();
//
//	if (pEachDropTable == NULL)
//	{
//		printf("No EachDropTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Each_Drop_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_EachDropTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pEachDropTableNode;
//
//	for (iter = pEachDropTable->Begin(); pEachDropTable->End() != iter; iter++)
//	{
//		sEACH_DROP_TBLDAT* pTableData = (sEACH_DROP_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pEachDropTableNode, L"Table_Data_KOR", NULL);
//		if (pEachDropTableNode == NULL)
//		{
//			printf("Failed to create EachDrop XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pEachDropTableNode, L"Tblidx", pTableData->tblidx);
//
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < MAX_EACH_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pEachDropTableNode, wszBuffer, pTableData->aItem_Tblidx[i]);
//		}
//
//		for (int i = 0; i < MAX_EACH_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
//
//			AppendElementW_f(pXMLDoc, pEachDropTableNode, wszBuffer, pTableData->afDrop_Rate[i]);
//		}
//
//		// Add a line feed
//		pEachDropTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pEachDropTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_TypeDropTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CTypeDropTable* pTypeDropTable = m_pTableContainer->GetTypeDropTable();
//
//	if (pTypeDropTable == NULL)
//	{
//		printf("No TypeDropTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Type_Drop_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_TypeDropTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pTypeDropTableNode;
//
//	for (iter = pTypeDropTable->Begin(); pTypeDropTable->End() != iter; iter++)
//	{
//		sTYPE_DROP_TBLDAT* pTableData = (sTYPE_DROP_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pTypeDropTableNode, L"Table_Data_KOR", NULL);
//		if (pTypeDropTableNode == NULL)
//		{
//			printf("Failed to create TypeDrop XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pTypeDropTableNode, L"Tblidx", pTableData->tblidx);
//
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < MAX_TYPE_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pTypeDropTableNode, wszBuffer, pTableData->aItem_Tblidx[i]);
//		}
//
//		for (int i = 0; i < MAX_TYPE_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
//
//			AppendElementW_f(pXMLDoc, pTypeDropTableNode, wszBuffer, pTableData->afDrop_Rate[i]);
//		}
//
//		// Add a line feed
//		pTypeDropTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pTypeDropTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_NormalDropTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CNormalDropTable* pNormalDropTable = m_pTableContainer->GetNormalDropTable();
//
//	if (pNormalDropTable == NULL)
//	{
//		printf("No NormalDropTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Normal_Drop_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_NormalDropTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pNormalDropTableNode;
//
//	for (iter = pNormalDropTable->Begin(); pNormalDropTable->End() != iter; iter++)
//	{
//		sNORMAL_DROP_TBLDAT* pTableData = (sNORMAL_DROP_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pNormalDropTableNode, L"Table_Data_KOR", NULL);
//		if (pNormalDropTableNode == NULL)
//		{
//			printf("Failed to create NormalDrop XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pNormalDropTableNode, L"Tblidx", pTableData->tblidx);
//
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < MAX_NORMAL_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pNormalDropTableNode, wszBuffer, pTableData->aItem_Tblidx[i]);
//		}
//
//		for (int i = 0; i < MAX_NORMAL_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
//
//			AppendElementW_f(pXMLDoc, pNormalDropTableNode, wszBuffer, pTableData->afDrop_Rate[i]);
//		}
//
//		// Add a line feed
//		pNormalDropTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pNormalDropTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_SuperiorDropTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CSuperiorDropTable* pSuperiorDropTable = m_pTableContainer->GetSuperiorDropTable();
//
//	if (pSuperiorDropTable == NULL)
//	{
//		printf("No SuperiorDropTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Superior_Drop_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_SuperiorDropTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pSuperiorDropTableNode;
//
//	for (iter = pSuperiorDropTable->Begin(); pSuperiorDropTable->End() != iter; iter++)
//	{
//		sSUPERIOR_DROP_TBLDAT* pTableData = (sSUPERIOR_DROP_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pSuperiorDropTableNode, L"Table_Data_KOR", NULL);
//		if (pSuperiorDropTableNode == NULL)
//		{
//			printf("Failed to create SuperiorDrop XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pSuperiorDropTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pSuperiorDropTableNode, L"Max_Quality", pTableData->byMax_Quality);
//		AppendElementW_f(pXMLDoc, pSuperiorDropTableNode, L"Option_Rate", pTableData->fOption_Rate);
//
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < MAX_SUPERIOR_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pSuperiorDropTableNode, wszBuffer, pTableData->aItem_Tblidx[i]);
//		}
//
//		for (int i = 0; i < MAX_SUPERIOR_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
//
//			AppendElementW_f(pXMLDoc, pSuperiorDropTableNode, wszBuffer, pTableData->afDrop_Rate[i]);
//		}
//
//		// Add a line feed
//		pSuperiorDropTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pSuperiorDropTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_ExcellentDropTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CExcellentDropTable* pExcellentDropTable = m_pTableContainer->GetExcellentDropTable();
//
//	if (pExcellentDropTable == NULL)
//	{
//		printf("No ExcellentDropTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Excellent_Drop_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_ExcellentDropTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pExcellentDropTableNode;
//
//	for (iter = pExcellentDropTable->Begin(); pExcellentDropTable->End() != iter; iter++)
//	{
//		sEXCELLENT_DROP_TBLDAT* pTableData = (sEXCELLENT_DROP_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pExcellentDropTableNode, L"Table_Data_KOR", NULL);
//		if (pExcellentDropTableNode == NULL)
//		{
//			printf("Failed to create ExcellentDrop XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pExcellentDropTableNode, L"Tblidx", pTableData->tblidx);
//
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < MAX_EXCELLENT_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pExcellentDropTableNode, wszBuffer, pTableData->aItem_Tblidx[i]);
//		}
//
//		for (int i = 0; i < MAX_EXCELLENT_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
//
//			AppendElementW_f(pXMLDoc, pExcellentDropTableNode, wszBuffer, pTableData->afDrop_Rate[i]);
//		}
//
//		// Add a line feed
//		pExcellentDropTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pExcellentDropTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_LegendaryDropTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CLegendaryDropTable* pLegendaryDropTable = m_pTableContainer->GetLegendaryDropTable();
//
//	if (pLegendaryDropTable == NULL)
//	{
//		printf("No LegendaryDropTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Legendary_Drop_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_LegendaryDropTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pLegendaryDropTableNode;
//
//	for (iter = pLegendaryDropTable->Begin(); pLegendaryDropTable->End() != iter; iter++)
//	{
//		sLEGENDARY_DROP_TBLDAT* pTableData = (sLEGENDARY_DROP_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pLegendaryDropTableNode, L"Table_Data_KOR", NULL);
//		if (pLegendaryDropTableNode == NULL)
//		{
//			printf("Failed to create LegendaryDrop XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pLegendaryDropTableNode, L"Tblidx", pTableData->tblidx);
//
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < MAX_LEGENDARY_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Item_Tblidx_%d", i + 1);
//
//			AppendElementW(pXMLDoc, pLegendaryDropTableNode, wszBuffer, pTableData->aItem_Tblidx[i]);
//		}
//
//		for (int i = 0; i < MAX_LEGENDARY_DROP; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Drop_Rate_%d", i + 1);
//
//			AppendElementW_f(pXMLDoc, pLegendaryDropTableNode, wszBuffer, pTableData->afDrop_Rate[i]);
//		}
//
//		// Add a line feed
//		pLegendaryDropTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pLegendaryDropTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_ItemOptionTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CItemOptionTable* pItemOptionTable = m_pTableContainer->GetItemOptionTable();
//
//	if (pItemOptionTable == NULL)
//	{
//		printf("No ItemOptionTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_Item_Option_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_ItemOptionTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	CTable::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pItemOptionTableNode;
//
//	for (iter = pItemOptionTable->Begin(); pItemOptionTable->End() != iter; iter++)
//	{
//		sITEM_OPTION_TBLDAT* pTableData = (sITEM_OPTION_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pItemOptionTableNode, L"Table_Data_KOR", NULL);
//		if (pItemOptionTableNode == NULL)
//		{
//			printf("Failed to create ItemOption XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Option_Name", pTableData->wszOption_Name);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Validity_Able", pTableData->bValidity_Able ? 1 : 0);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Option_Rank", pTableData->byOption_Rank);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Item_Group", pTableData->byItem_Group);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Max_Quality", pTableData->byMaxQuality);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Quality", pTableData->byQuality);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Quality_Index", pTableData->byQualityIndex);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Cost", pTableData->dwCost);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Level", pTableData->byLevel);
//		
//		WCHAR wszBuffer[1024] = { 0x00, };
//		for (int i = 0; i < MAX_SYSTEM_EFFECT_COUNT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"System_Effect_%d", i + 1);
//			AppendElementW(pXMLDoc, pItemOptionTableNode, wszBuffer, pTableData->system_Effect[i]);
//		}
//		for (int i = 0; i < MAX_SYSTEM_EFFECT_COUNT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Type_%d", i + 1);
//			AppendElementW(pXMLDoc, pItemOptionTableNode, wszBuffer, pTableData->bAppliedInPercent[i]);
//		}
//
//		for (int i = 0; i < MAX_SYSTEM_EFFECT_COUNT; i++)
//		{
//			swprintf(wszBuffer, 1024, L"Value_%d", i + 1);
//			AppendElementW(pXMLDoc, pItemOptionTableNode, wszBuffer, pTableData->nValue[i]);
//		}
//		
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Active_Effect", pTableData->activeEffect);
//		AppendElementW_f(pXMLDoc, pItemOptionTableNode, L"Active_Rate", pTableData->fActiveRate);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Note", pTableData->szNote);
//		AppendElementW(pXMLDoc, pItemOptionTableNode, L"Scouter_Info", pTableData->byScouterInfo);
//
//		// Add a line feed
//		pItemOptionTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pItemOptionTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
//
//bool CRdf2XmlHelper::SaveToXml_SystemEffectTable(const char* pszPath)
//{
//	if (pszPath == NULL)
//	{
//		return false;
//	}
//
//	bool bResult = FALSE;
//
//	CSystemEffectTable* pSystemEffectTable = m_pTableContainer->GetSystemEffectTable();
//
//	if (pSystemEffectTable == NULL)
//	{
//		printf("No SystemEffectTable.\n");
//		return false;
//	}
//
//	std::string strPathFilename;
//
//	strPathFilename = pszPath;
//	if (strPathFilename[strPathFilename.length() - 1] == '\\')
//	{
//		strPathFilename.erase(strPathFilename.length() - 1, 1);
//	}
//	strPathFilename += "\\Table_System_Effect_Data.xml";
//
//	printf("Generating %s ...\n", strPathFilename.c_str());
//
//	MSXML2::IXMLDOMDocumentPtr pXMLDoc;
//	MSXML2::IXMLDOMElementPtr pRoot;
//
//	InitXmlDOC(pXMLDoc, pRoot);
//
//	// Createe Field-Name block
//	std::vector<std::wstring> vecFieldName;
//	SetFieldNameList_SystemEffectTable(vecFieldName);
//	AppendFieldNameBlockW(pXMLDoc, pRoot, vecFieldName);
//
//	// Create Mob-Table XML blocks
//	Table::TABLE::iterator iter;
//	MSXML2::IXMLDOMElementPtr pSystemEffectTableNode;
//
//	for (iter = pSystemEffectTable->Begin(); pSystemEffectTable->End() != iter; iter++)
//	{
//		sSYSTEM_EFFECT_TBLDAT* pTableData = (sSYSTEM_EFFECT_TBLDAT*)(iter->second);
//
//		// ObjectTable		
//		AppendBlockElementW(pXMLDoc, pRoot, pSystemEffectTableNode, L"Table_Data_KOR", NULL);
//		if (pSystemEffectTableNode == NULL)
//		{
//			printf("Failed to create SystemEffect XML node.\n");
//			return false;
//		}
//
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Tblidx", pTableData->tblidx);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Name", pTableData->wszName);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Effect_Type", pTableData->byEffect_Type);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Active_Effect_Type", pTableData->byActive_Effect_Type);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Effect_Info_Text", pTableData->Effect_Info_Text);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Keep_Effect_Name", pTableData->Keep_Effect_Name);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Target_Effect_Position", pTableData->byTarget_Effect_Position);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Success_Effect_Name", pTableData->szSuccess_Effect_Name);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Success_Projectile_Type", pTableData->bySuccess_Projectile_Type);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Success_Effect_Position", pTableData->bySuccess_Effect_Position);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Success_End_Effect_Name", pTableData->szSuccess_End_Effect_Name);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"End_Effect_Position", pTableData->byEnd_Effect_Position);
//		AppendElementW(pXMLDoc, pSystemEffectTableNode, L"Keep_Animation_Index", pTableData->wKeep_Animation_Index);
//	
//
//		// Add a line feed
//		pSystemEffectTableNode->appendChild(pXMLDoc->createTextNode("\n\t"));
//		pSystemEffectTableNode = NULL;
//	}
//
//	// Add a line feed
//	pRoot->appendChild(pXMLDoc->createTextNode("\n"));
//
//
//	// To save the output XML file into the specified destination.
//	pXMLDoc->save(strPathFilename.c_str());
//
//	printf("Generating %s complete.\n", strPathFilename.c_str());
//
//	return bResult;
//}
///////////////////////////////////////////////////////////////
//
//  Binary Section Begins Here
//
///////////////////////////////////////////////////////////////
bool CRdf2XmlHelper::SaveToBinary_MobTable(const char* pszPath)
{
	if (pszPath == NULL)
	{
		return false;
	}

	bool bResult = FALSE;

	MobTable* pMobTable = m_pTableContainer->GetMobTable();

	if (pMobTable == NULL)
	{
		printf("No MobTable.\n");
		return false;
	}

	std::string strPathFilename;

	strPathFilename = pszPath;
	if (strPathFilename[strPathFilename.length() - 1] == '\\')
	{
		strPathFilename.erase(strPathFilename.length() - 1, 1);
	}
	strPathFilename += "\\Table_MOB_Data.rdf";

	printf("Generating %s ...\n", strPathFilename.c_str());

	FileSerializer serializer;
	pMobTable->SaveToBinary(serializer);
	serializer.SaveFile((char *)strPathFilename.c_str());

	printf("Generating %s complete.\n", strPathFilename.c_str());
}

bool CRdf2XmlHelper::SaveToBinary_ItemTable(const char* pszPath)
{
	if (pszPath == NULL)
	{
		return false;
	}

	bool bResult = FALSE;

	ItemTable* pItemTable = m_pTableContainer->GetItemTable();

	if (pItemTable == NULL)
	{
		printf("No ItemTable.\n");
		return false;
	}

	std::string strPathFilename;

	strPathFilename = pszPath;
	if (strPathFilename[strPathFilename.length() - 1] == '\\')
	{
		strPathFilename.erase(strPathFilename.length() - 1, 1);
	}
	strPathFilename += "\\Table_Item_Data.rdf";

	printf("Generating %s ...\n", strPathFilename.c_str());

	FileSerializer serializer;
	pItemTable->SaveToBinary(serializer);
	serializer.SaveFile((char *)strPathFilename.c_str());

	printf("Generating %s complete.\n", strPathFilename.c_str());
}

bool CRdf2XmlHelper::SaveToBinary_SkillTable(const char* pszPath)
{
	if (pszPath == NULL)
	{
		return false;
	}

	bool bResult = FALSE;

	SkillTable* pSkillTable = m_pTableContainer->GetSkillTable();

	if (pSkillTable == NULL)
	{
		printf("No SkillTable.\n");
		return false;
	}

	std::string strPathFilename;

	strPathFilename = pszPath;
	if (strPathFilename[strPathFilename.length() - 1] == '\\')
	{
		strPathFilename.erase(strPathFilename.length() - 1, 1);
	}
	strPathFilename += "\\Table_Skill_Data.rdf";

	printf("Generating %s ...\n", strPathFilename.c_str());

	FileSerializer serializer;
	pSkillTable->SaveToBinary(serializer);
	serializer.SaveFile((char *)strPathFilename.c_str());

	printf("Generating %s complete.\n", strPathFilename.c_str());
}

bool CRdf2XmlHelper::SaveToBinary_TextAllTable(const char* pszPath)
{
	if (pszPath == NULL)
	{
		return false;
	}

	bool bResult = FALSE;

	TextAllTable* pTextAllTable = m_pTableContainer->GetTextAllTable();

	if (pTextAllTable == NULL)
	{
		printf("No TextAllTable.\n");
		return false;
	}

	std::string strPathFilename;

	strPathFilename = pszPath;
	if (strPathFilename[strPathFilename.length() - 1] == '\\')
	{
		strPathFilename.erase(strPathFilename.length() - 1, 1);
	}
	strPathFilename += "\\Table_Text_All_Data.rdf";

	printf("Generating %s ...\n", strPathFilename.c_str());

	FileSerializer serializer;
	pTextAllTable->SaveToBinary(serializer);
	serializer.SaveFile((char *)strPathFilename.c_str());

	printf("Generating %s complete.\n", strPathFilename.c_str());
}

bool CRdf2XmlHelper::SaveToBinary_PcTable(const char* pszPath)
{
	if (pszPath == NULL)
	{
		return false;
	}

	bool bResult = FALSE;

	PCTable* pPCTable = m_pTableContainer->GetPcTable();

	if (pPCTable == NULL)
	{
		printf("No pPCTable.\n");
		return false;
	}

	std::string strPathFilename;

	strPathFilename = pszPath;
	if (strPathFilename[strPathFilename.length() - 1] == '\\')
	{
		strPathFilename.erase(strPathFilename.length() - 1, 1);
	}
	strPathFilename += "\\Table_Pc_Data.rdf";

	printf("Generating %s ...\n", strPathFilename.c_str());

	FileSerializer serializer;
	pPCTable->SaveToBinary(serializer);
	serializer.SaveFile((char *)strPathFilename.c_str());

	printf("Generating %s complete.\n", strPathFilename.c_str());
}

bool CRdf2XmlHelper::SaveToBinary_ExpTable(const char* pszPath)
{
	if (pszPath == NULL)
	{
		return false;
	}

	bool bResult = FALSE;

	ExpTable* pExpTable = m_pTableContainer->GetExpTable();

	if (pExpTable == NULL)
	{
		printf("No pExpTable.\n");
		return false;
	}

	std::string strPathFilename;

	strPathFilename = pszPath;
	if (strPathFilename[strPathFilename.length() - 1] == '\\')
	{
		strPathFilename.erase(strPathFilename.length() - 1, 1);
	}
	strPathFilename += "\\Table_Exp_Data.rdf";

	printf("Generating %s ...\n", strPathFilename.c_str());

	FileSerializer serializer;
	pExpTable->SaveToBinary(serializer);
	serializer.SaveFile((char *)strPathFilename.c_str());

	printf("Generating %s complete.\n", strPathFilename.c_str());
}

bool CRdf2XmlHelper::SaveToBinary_QuestTextTable(const char* pszPath)
{
	if (pszPath == NULL)
	{
		return false;
	}

	bool bResult = FALSE;

	QuestTextDataTable* pQuestTextTable = m_pTableContainer->GetQuestTextDataTable();

	if (pQuestTextTable == NULL)
	{
		printf("No QuestTextTable.\n");
		return false;
	}

	std::string strPathFilename;

	strPathFilename = pszPath;
	if (strPathFilename[strPathFilename.length() - 1] == '\\')
	{
		strPathFilename.erase(strPathFilename.length() - 1, 1);
	}
	strPathFilename += "\\Table_Quest_Text_Data.rdf";

	printf("Generating %s ...\n", strPathFilename.c_str());

	FileSerializer serializer;
	pQuestTextTable->SaveToBinary(serializer);
	serializer.SaveFile((char *)strPathFilename.c_str());

	printf("Generating %s complete.\n", strPathFilename.c_str());
}

bool CRdf2XmlHelper::SaveToBinary_ObjectTable(const char* pszPath)
{
	if (pszPath == NULL)
	{
		return false;
	}

	bool bResult = FALSE;

	ObjectTable* pObjectTable = m_pTableContainer->GetObjectTable(1);

	if (pObjectTable == NULL)
	{
		printf("No ObjectTable.\n");
		return false;
	}

	std::string strPathFilename;

	strPathFilename = pszPath;
	if (strPathFilename[strPathFilename.length() - 1] == '\\')
	{
		strPathFilename.erase(strPathFilename.length() - 1, 1);
	}
	strPathFilename += "\\Table_Object.rdf";

	printf("Generating %s ...\n", strPathFilename.c_str());

	FileSerializer serializer;
	pObjectTable->SaveToBinary(serializer);
	serializer.SaveFile((char *)strPathFilename.c_str());

	printf("Generating %s complete.\n", strPathFilename.c_str());
}