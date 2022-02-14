#pragma once
#include "RangedWeapon.h"
#include "Player.h"
#include "WinchesterShotgunAnimationState.h"
class WinchesterShotgun : public RangedWeapon
{
private: // Properties
	WinchesterShotgunAnimationState m_currentAnimationState;

public: //Functions
	WinchesterShotgun(Player* player);
	~WinchesterShotgun() override;

	void draw() override;
	void update() override;
	void clean() override;

	void attack() override;


	void setAnimationState(WinchesterShotgunAnimationState new_state);

private: //Functions

	void m_buildAnimations();
	void m_move();
};