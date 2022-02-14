#pragma once
#ifndef __PLAYER_UI__
#define __PLAYER_UI__

#include "DisplayObject.h"
#include "HealthBar.h"
//#include "Player.h"

class Player;

class PlayerUI final: DisplayObject
{
private:
	HealthBar* m_pHelathBar;
	Player* m_pPlayer;

public:
	PlayerUI(Player* player);
	~PlayerUI();

	void draw() override;
	void update() override;
	void clean() override;

	//getters
	HealthBar* getHealthBar();
private:

};

#endif
