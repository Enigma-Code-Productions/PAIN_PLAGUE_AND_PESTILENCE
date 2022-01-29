#pragma once
#ifndef __WEAPON__
#define __WEAPON__

#include "Sprite.h"
#include "Player.h"
// Virtual class
class Weapon : public Sprite
{
private:
	int m_damage;
	int m_range;
	Player* m_owner;

public:
	Weapon() {};
	Weapon(Player*) {};
	virtual ~Weapon() = default;

	// Inherited via GameObject
	virtual void draw() override = 0;
	virtual void update() override = 0;
	virtual void clean() override = 0;

	int getDamage() const { return m_damage; }
	int getRange() const { return m_range; }
	Player* getOwner() const { return  m_owner; }

	void setDamage(int d) { m_damage = d; }
	void setRange(int r) { m_range = r; }
	void setOwner(Player* p) { m_owner = p; }
private:


};


#endif /* defined (__TEMPLATE_OBJECT__) */
