#pragma once
#ifndef __WEAPON__
#define __WEAPON__

#include "Sprite.h"
//#include "Player.h"
// Virtual class

class Player;

class Weapon : public Sprite
{
private: //Properties
	bool m_hasCollisionDamage;
	int m_damage;
	int m_range;
	Player* m_owner;

	//collision for melee and animation
	bool m_bIsAttacking;
	int m_attackTime;
	int m_attackStart;

public: //Functions
	Weapon() {}
	Weapon(Player*) {}
	virtual ~Weapon() = default;

	// Inherited via GameObject
	virtual void draw() override = 0;
	virtual void update() override = 0;
	virtual void clean() override = 0;

	virtual void attack() = 0;

	// getters
	bool hasCollisionDamage() const { return m_hasCollisionDamage; }
	bool isAttacking() const { return m_bIsAttacking; }
	int getDamage() const { return m_damage; }
	int getRange() const { return m_range; }
	int getAttackStart() const { return m_attackStart; }
	int getAttackTime() const { return m_attackTime;}
	Player* getOwner() const { return  m_owner; }
	

	// setters
	void setCollisionDamage(bool c) { m_hasCollisionDamage = c; }
	void setIsAttacking(bool s) { m_bIsAttacking = s; }
	void setDamage(int d) { m_damage = d; }
	void setRange(int r) { m_range = r; }
	void setAttackStart(int f) { m_attackStart = f; }
	void setAttackTime(int f) { m_attackTime = f; }
	void setOwner(Player* p) { m_owner = p; }
	
};


#endif /* defined (__TEMPLATE_OBJECT__) */
