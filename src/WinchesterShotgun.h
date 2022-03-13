#pragma once
#include "RangedWeapon.h"
#include "Player.h"
#include "WinchesterShotgunAnimationState.h"
class WinchesterShotgun final : public RangedWeapon
{
private: // Properties
	WinchesterShotgunAnimationState m_currentAnimationState;
	float m_direction;
	float m_bulletSpeed;
	int m_bulletCount;
	float m_accuracy;


public: //Functions
	WinchesterShotgun(Player* player);
	~WinchesterShotgun() override;

	void draw() override;
	void update() override;
	void clean() override;

	void attack() override;

	void setAnimationState(WinchesterShotgunAnimationState new_state);
	void setAccuracy(float accuracy);
	void setBulletCount(int count);
	void setDirection();


private: //Functions

	void m_buildAnimations();
	void m_move();
};