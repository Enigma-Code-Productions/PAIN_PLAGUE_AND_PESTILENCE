#pragma once
#ifndef __POTION_THROWER__
#define __POTION_THROWER__

#include "Potion.h"
#include "Sprite.h"
#include <vector>
class Player;

class PotionThrower final : public Sprite
{
private: // Properties
	std::vector<Potion*> m_pPotions;
	Player* m_pPlayer;
	

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