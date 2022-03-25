#pragma once
#ifndef __POISON_1_
#define __POISON_1_
#include "Sprite.h"


class Poison1 : public Sprite
{
private:
	bool m_damageDone;
public:
	Poison1(glm::vec2 pos);
	~Poison1();

	void clean() override;
	void draw() override;
	void update() override;

	void dealDamage();

private:
	void m_buildAnimations();
};
#endif 