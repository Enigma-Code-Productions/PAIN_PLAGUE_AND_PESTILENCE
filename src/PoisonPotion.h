#pragma once
#ifndef __POSION_POTION__
#define __POSION_POTION__
#include "Potion.h"


class PosionPotion: public Potion
{
public:
	PosionPotion(glm::vec2 pos, glm::vec2 target);
	~PosionPotion();

	virtual void clean() override;
	virtual void draw() override;
	virtual void update() override;

	void m_buildAnimations();
};
#endif 