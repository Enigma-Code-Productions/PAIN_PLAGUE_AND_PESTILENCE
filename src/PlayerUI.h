#pragma once
#ifndef __PLAYER_UI__
#define __PLAYER_UI__

#include "DisplayObject.h"
#include "HealthBar.h"
#include "Label.h"

class Player;

class PlayerUI final: public DisplayObject
{
private:
	Player* m_pPlayer;

	HealthBar* m_pHelathBar;
	Label* m_pHealsLeftLabel;
	Label* m_pPotionsAmount;
	Label* m_pScore;

public:
	PlayerUI(Player* player);
	~PlayerUI();

	void draw() override;
	void update() override;
	void clean() override;

	//getters
	HealthBar* getHealthBar();

	//setters
	void setHeals();

private:

};

#endif
