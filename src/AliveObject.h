#pragma once
#ifndef __ALIVE_OBJECT__
#define __ALIVE_OBJECT__

#include "Sprite.h"

class AliveObject : public Sprite
{
private: //Properties
	bool m_bIsAlive;
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
	int getMaxHealth();
	int getHealth();
	int getDamage();

	// setters
	void setAlive(bool a);
	void setMaxHealth(int mh);
	void setHealt(int h);
	void setDamage(int d);

	// Other functions
	void takeDamage(int damage);
	void getHeal(int heal);

private: //Functions

	void setDead();
};

#endif /* defined (__ALIVE_OBJECT__) */
