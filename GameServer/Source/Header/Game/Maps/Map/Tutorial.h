#ifndef		_TUTORIAL__H
# define	_TUTORIAL__H

#pragma once

#include <Define.h>
#include <Game\Maps\Map.h>

#define		BEAN_SAIBAMAN	1411104
#define		KOWANGA			4911110
#define		RIO				7211113
#define		SEA_TURTLE		7611104

class Tutorial : public Map
{
public:
	explicit				Tutorial(uint32 id);
	virtual					~Tutorial();
	void					Update(const uint32&) override;

	void					ChangeStep(Player* plr, int stape);
};

#endif