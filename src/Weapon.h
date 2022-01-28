#pragma once
#ifndef __WEAPON__
#define __WEAPON__

#include "DisplayObject.h"

class Weapon : public DisplayObject
{
private:
	int m_damage;
	int m_range;

public:
	Weapon();
	virtual ~Weapon();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	int getDamage() const { return m_damage; }
	int getRange() const { return m_range; }

	void setDamage(int d) { m_damage = d; }
	void setRange(int r) { m_range = r; }

private:
	void m_move();
	void m_checkBounds();
	void m_reset();


};


#endif /* defined (__TEMPLATE_OBJECT__) */
