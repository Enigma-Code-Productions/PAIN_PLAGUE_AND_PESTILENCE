#pragma once
#ifndef __EXPLOSION_1_
#define __EXPLOSION_1_
#include "Sprite.h"


class Explosion1 : public Sprite
{
public:
	Explosion1(glm::vec2 pos, glm::vec2 size = glm::vec2(64.0f, 64.0f));
	~Explosion1();

	void clean() override;
	void draw() override;
	void update() override;

	void dealDamage();

private:
	void m_buildAnimations();
};
#endif 