#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

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

	int getPlayerHealth();
	int getPlayerDamage();
	bool getIsAttacking();

	void setPlayerHealth(int health);
	void setPlayerMaxHealth(int health);
	void setPlayerDamage(int damage);
	void setIsAttacking(bool attacking);

private:
	int m_playerHealth = 100;
	static int m_playerMaxHealth;
	static int m_playerDamage;

	bool m_isAttacking = false;

	void m_buildAnimations();

	const int m_speed;

	int getSpeed()
	{
		return m_speed;
	}

	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */