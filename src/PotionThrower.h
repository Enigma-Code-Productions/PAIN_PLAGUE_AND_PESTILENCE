#pragma once
#ifndef __POTION_THROWER__
#define __POTION_THROWER__

#include "Potion.h"
#include "Sprite.h"
#include <vector>
class Player;

enum Potions
{
	POISON_POTION,
	FIRE_POTION,
	EXPLOSIVE_POTION,
	NUM_OF_POTIONS
};

class PotionThrower final : public Sprite
{
private: // Properties
	std::vector<Potion*> m_pPotions;
	Player* m_pPlayer;

	Potions m_chosenPotion;
	int m_amountOfPotions[NUM_OF_POTIONS];
	int m_MaxPotions;

public: // Functions
	PotionThrower(Player* player);
	~PotionThrower();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void throwPotion();

	int GetAmountPotions(Potions p);
	Potions GetChosenPotion();

	void deletePotion(Potion* p);

private: // Functions
	void m_loadPotions();
	void m_buildAnimations();
};

#endif