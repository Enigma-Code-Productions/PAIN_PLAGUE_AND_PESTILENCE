#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "AliveObject.h"
#include "Weapon.h"
#include "PlayerUI.h"
#include "HealingPotion.h"
#include "PotionThrower.h"

class Player final : public AliveObject
{
private: //Properties
	const int m_speed;
	int m_invTime; // inv = invulnerability
	int m_invTimeLeft;

	const int HEALING_TIME;
	int m_healingTimeLeft;
	int m_healsLeft;
	bool m_bHealing;
	bool m_bCanMove;

	//this needs to be here until weapons can be picked up from an external source like a chest
	Weapon* m_pKnife;
	Weapon* m_pShotgun;
	//-----------------------------------------------------------------------------------------

	PlayerUI* m_pPlayerUI;
	Weapon* m_pWeapon;
	HealingPotion* m_pHealingPotion;
	PlayerAnimationState m_currentAnimationState;
	PotionThrower* m_thrower;
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
	void setHealsLeft(int c);
	void setCanMove(bool m);
	// getters
	Weapon* getWeapon();
	PotionThrower* getThrower();
	bool isFacingRight();
	int getDamage();
	int getInvTime();
	int getInvTimeLeft();
	int getHealsLeft();
	bool getCanMove();
	// other functions 
	void takeDamage(int damage);
	void Death();

private: // Functions

	void m_buildAnimations();
	int getSpeed() const {return m_speed;}

	void Heal();

};

#endif /* defined (__PLAYER__) */