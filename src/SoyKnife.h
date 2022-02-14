#pragma once
#include "Weapon.h"
#include "Player.h"
#include "SoyKnifeAnimationState.h"
class SoyKnife final : public Weapon
{
private: // Properties
	SoyKnifeAnimationState m_currentAnimationState;

public: //Functions
	SoyKnife(Player* player);
	//SoyKnife();
	~SoyKnife() override;

	void draw() override;
	void update() override;
	void clean() override;

	void attack() override;


	void setAnimationState(SoyKnifeAnimationState new_state);
private: //Functions

	void m_buildAnimations();
	void m_move();
};

