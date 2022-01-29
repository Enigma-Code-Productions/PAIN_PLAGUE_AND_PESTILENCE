#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"
#include"Weapon.h"
class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void setWeapon(Weapon* w);

	Weapon* getWeapon();
	bool isFacingRight();

private:
	void m_buildAnimations();

	const int m_speed;

	int getSpeed()
	{
		return m_speed;
	}

	PlayerAnimationState m_currentAnimationState;

	Weapon* m_pWeapon;
};

#endif /* defined (__PLAYER__) */