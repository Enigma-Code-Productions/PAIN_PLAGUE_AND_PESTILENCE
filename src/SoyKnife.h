#pragma once
#include "Weapon.h"
#include "Player.h"
#include "SoyKnifeAnimationState.h"
class SoyKnife final : public Weapon
{
public:
	SoyKnife(Player* player);
	SoyKnife();
	~SoyKnife();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setAnimationState(SoyKnifeAnimationState new_state);
private:
	void m_buildAnimations();

	SoyKnifeAnimationState m_currentAnimationState;

	void m_move();
	void m_attack();


};

