#pragma once
#ifndef __EXPLOSION_POTION__
#define __EXPLOSION_POTION__
#include "Potion.h"


class ExplosionPotion : public Potion
{
public:
	ExplosionPotion(glm::vec2 pos, glm::vec2 target);
	~ExplosionPotion();

	virtual void clean() override;
	virtual void draw() override;
	virtual void update() override;

};
#endif 