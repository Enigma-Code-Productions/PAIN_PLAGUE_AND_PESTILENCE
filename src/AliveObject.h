#pragma once
#ifndef __ALIVE_OBJECT__
#define __ALIVE_OBJECT__

#include "Sprite.h"

class AliveObject : public Sprite
{
private: //Properties
	bool m_bIsAlive;
	bool m_hasCollisionDamage;
	int m_health;
	int m_maxHealth;
	int m_damage;

public: //Functions
	AliveObject();
	virtual ~AliveObject();

	// Life Cycle Functions
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	//getters
	bool isAlive();
	bool hasCollisionDamage();
	int getMaxHealth();
	int getHealth();
	int getDamage();

	// setters
	void setAlive(bool a);
	void setCollisionDamage(bool c);
	void setMaxHealth(int mh);
	void setHealth(int h);
	void setDamage(int d);

	// Other functions
	void takeDamage(int damage);
	void takeHeal(int heal);

private: //Functions

	void setDead();
};

#endif /* defined (__ALIVE_OBJECT__) */
