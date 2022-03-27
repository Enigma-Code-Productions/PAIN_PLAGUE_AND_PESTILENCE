#pragma once
#ifndef __FIRE_1_
#define __FIRE_1_
#include "Sprite.h"


class Fire1 : public Sprite
{
private:
	bool m_damageDone;
public:
	Fire1(glm::vec2 pos);
	~Fire1();

	void clean() override;
	void draw() override;
	void update() override;

	void dealDamage();

private:
	void m_buildAnimations();
};
#endif 
