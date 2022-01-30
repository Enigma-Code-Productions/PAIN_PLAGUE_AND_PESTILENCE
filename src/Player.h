#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "AliveObject.h"
#include "Weapon.h"
class Player final : public AliveObject
{
private: //Properties
	const int m_speed;
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

	// getters
	Weapon* getWeapon();
	bool isFacingRight();
	int getDamage();


private: // Functions


	void m_buildAnimations();
	int getSpeed() const {return m_speed;}

};

#endif /* defined (__PLAYER__) */