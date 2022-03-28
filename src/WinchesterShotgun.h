#pragma once
#include "RangedWeapon.h"
#include "Player.h"
#include "WinchesterShotgunAnimationState.h"
class WinchesterShotgun final : public RangedWeapon
{
private: // Properties
	WinchesterShotgunAnimationState m_currentAnimationState;

public: //Functions
	WinchesterShotgun(Player* player);
	~WinchesterShotgun() = default;

	void draw() override;
	void update() override;

	void setAnimationState(WinchesterShotgunAnimationState new_state);

private: //Functions
	void m_buildAnimations();
};