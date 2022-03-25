#pragma once
#ifndef __FIRE_POTION__
#define __FIRE_POTION__
#include "Potion.h"


class FirePotion : public Potion
{
public:
	FirePotion(glm::vec2 pos, glm::vec2 target);
	~FirePotion();

	virtual void clean() override;
	virtual void draw() override;
	virtual void update() override;

	void m_buildAnimations();
};
#endif 