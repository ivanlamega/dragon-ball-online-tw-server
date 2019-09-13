#ifndef __SKILLS_H
#define __SKILLS_H

#pragma once

#include <NtlSkill.h>
#include <TableAll.h>

class Player;
class SkillsManager
{
public:
	SkillsManager();
	~SkillsManager();

	bool					LoadSkill(CHARACTERID id);
	void					SaveSkill(Player& plr);

	BYTE					getSkillsCount() { return SkillCounter; }
	BYTE					getBuffCount() { return SkillBuffCounter; }
	BYTE					getHTBCounter() { return HTBSkillCounter; }
	BYTE					getQuickSlotsCounter() { return QuickSlotCounter; }

	sSKILL_INFO				*getSkillsInfos() { return SkillInfo; }
	sBUFF_INFO				*getBuffInfos() { return BuffInfo; }
	sHTB_SKILL_INFO			*getHTBSkillInfos() { return HTBSkillnfo; };
	sQUICK_SLOT_PROFILE		*getQuickSlots() { return QuickSlotData; }
	TBLIDX					getIdAtPos(BYTE slot_id);
	bool					isSkillLearned(DWORD SkillID);
	
	void					UpdateSlot(BYTE slot_id, TBLIDX id, BYTE byType);
private:
	bool					LoadSkillsFromDatabase();
	bool					LoadSkillBuffFromDatabase();
	bool					LoadHTBFromDatabase();
	bool					LoadQuickSlotFromDatabase();

	// SKILL
	BYTE					SkillCounter;
	BYTE					SkillBuffCounter;
	BYTE					HTBSkillCounter;
	BYTE					QuickSlotCounter;
	sSKILL_INFO				SkillInfo[MAX_PC_HAVE_SKILL];
	sBUFF_INFO				BuffInfo[MAX_BLESS_BUFF_CHARACTER_HAS + MAX_CURSE_BUFF_CHARACTER_HAS];
	sHTB_SKILL_INFO			HTBSkillnfo[HTB_MAX_PC_HAVE_HTB_SKILL];
	sQUICK_SLOT_PROFILE		QuickSlotData[CHAR_QUICK_SLOT_MAX_COUNT];

	CHARACTERID				charid;
};

#endif