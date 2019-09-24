#include "dboCommon.h"


public struct sSkillData{
	TBLIDX			tblidx;
	TBLIDX			Skill_Name;
	WCHAR			wszNameText[40 + 1];
	bool			bValidity_Able;
    BYTE     padding;
	DWORD			dwPC_Class_Bit_Flag;		// ePC_CLASS_FLAG
	BYTE			UnknownR;
	BYTE			bySkill_Class;				// eSKILL_CLASS
	BYTE			bySkill_Type;				// eSKILL_TYPE
	BYTE			bySkill_Active_Type;
	BYTE			byBuff_Group;
	BYTE			bySlot_Index;
	BYTE			bySkill_Grade;
	BYTE      padding;
	WORD			wFunction_Bit_Flag;

	BYTE			byAppoint_Target;
	BYTE			byApply_Target;
	BYTE			byApply_Target_Max;
	BYTE			byApply_Range;
	BYTE			byApply_Area_Size_1;
	BYTE			byApply_Area_Size_2;
	WORD			wUnknown;
	WORD    padding;
	TBLIDX			skill_Effect[2];
	BYTE			bySkill_Effect_Type[2];
	WORD    padding;
	float			fSkill_Effect_Value[2];
	WORD			wAdditional_Aggro_Point;
	/*Errors here with data misalgnment.
	* Look for issues with the following 2 structs.
	*/
	BYTE			abyRpEffect[4];		// eDBO_RP_BONUS_TYPE
	DWORD			adwRpEffectValue[3];
	WORD        Padding;

	BYTE			byRequire_Train_Level;	
	DWORD			dwRequire_Zenny;
	WORD			wNext_Skill_Train_Exp;
	WORD			wRequireSP;
	TBLIDX			uiRequire_Skill_Tblidx_Min_1;
	TBLIDX			uiRequire_Skill_Tblidx_Max_1;
	TBLIDX			uiRequire_Skill_Tblidx_Min_2;
	TBLIDX			uiRequire_Skill_Tblidx_Max_2;
	BYTE			padding[3];
	TBLIDX			Root_Skill;

	BYTE			byRequire_Epuip_Slot_Type;
	BYTE			byRequire_Item_Type;
	//	std::string		 strIcon_Name;
	WORD			wUnk;
	BYTE				bUnk;
	BYTE			padding[3];
	BYTE		bUnkArr[22];
	char			szIcon_Name[3 + 1];
	BYTE		padding;
	WORD			wRequire_LP;
	WORD			wRequire_EP;
	BYTE			byRequire_RP_Ball;
	WORD    unk;
	BYTE   padding;
	float			fCasting_Time;
	DWORD			dwCastingTimeInMilliSecs;
	WORD			wCool_Time;
	BYTE   padding[2];
	DWORD			dwCoolTimeInMilliSecs;
	WORD			wKeep_Time;
	BYTE   padding[2];
	DWORD			dwKeepTimeInMilliSecs;
	bool			bKeep_Effect;
	BYTE			byUse_Range_Min;
	BYTE   padding[2];
	float			fUse_Range_Min;
	BYTE			byUse_Range_Max;
	BYTE   padding[3];
	float			fUse_Range_Max;
	TBLIDX			Note;

	DWORD			dwNextSkillTblidx;
	bool			bDefaultDisplayOff;
     BYTE padding[3];
	DWORD			UnknownR3;

	unsigned short		wCasting_Animation_Start;
	unsigned short		wCasting_Animation_Loop;
	unsigned short		wAction_Animation_Index;
	unsigned short		wAction_Loop_Animation_Index;
	unsigned short		wAction_End_Animation_Index;
	bool			bDash_Able;

	BYTE padding;
	DWORD			dwTransform_Use_Info_Bit_Flag;
	
	float			fSuccess_Rate;

	BYTE			byPC_Class_Change;
	BYTE			UnknownR4;
	BYTE			UnknownR5;
	BYTE      padding;
	DWORD			UnknownR6;
	DWORD		unkR7;
};