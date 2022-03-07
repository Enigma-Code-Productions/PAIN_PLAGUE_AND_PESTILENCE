#pragma once
#ifndef __EXPLOSION_1_
#define __EXPLOSION_1_
#include "Sprite.h"


class Explosion1 : public Sprite
{
private:
	bool m_damageDone;
public:
	Explosion1(glm::vec2 pos);
	~Explosion1();

	void clean() override;
	void draw() override;
	void update() override;

	void dealDamage();

private:
	void m_buildAnimations();
};
#endif 