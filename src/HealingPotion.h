#pragma once
#ifndef __HEALING_POTION__
#define __HEALING_POTION__

#include "Sprite.h"

class Player;

class HealingPotion final : public Sprite
{
private:
	bool m_bFacingRight;

	Player* m_pPlayer;
public:
	HealingPotion(Player* player);
	~HealingPotion();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_buildAnimations();
	void m_move();

};

#endif
