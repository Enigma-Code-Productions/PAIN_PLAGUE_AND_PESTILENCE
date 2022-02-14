#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "AliveObject.h"

#include"Weapon.h"
#include"HealthBar.h"

class Player final : public AliveObject
{
private: //Properties
	const int m_speed;
	int m_invTime; // inv = invulnerability
	int m_invTimeLeft;

	HealthBar* m_pHealthBar;
	Weapon* m_pWeapon;

	PlayerAnimationState m_currentAnimationState;
public: // Functions
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void setWeapon(Weapon* w);
	void setInvTime(int t);
	void setInvTimeLeft(int t);

	// getters
	Weapon* getWeapon();
	bool isFacingRight();
	int getDamage();
	int getInvTime();
	int getInvTimeLeft();

	// other functions 
	void takeDamage(int damage);

private: // Functions

	void m_buildAnimations();
	int getSpeed() const {return m_speed;}

};

#endif /* defined (__PLAYER__) */