#pragma once
#ifndef __POTION_THROWER__
#define __POTION_THROWER__

#include "Potion.h"
#include "Sprite.h"

class Player;

class PotionThrower final : public Sprite
{
private: // Properties
	Potion* m_pPotion;
	Player* m_pPlayer;

	float m_power;
	

public: // Functions
	PotionThrower(Player* player);
	~PotionThrower();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void throwPotion();

private: // Functions
	void m_buildAnimations();
};

#endif