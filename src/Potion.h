#pragma once
#ifndef __POTION__
#define __POTION__
#include "Sprite.h"


class Potion : public Sprite
{
private:
	glm::vec2 m_target;
public:
	Potion(glm::vec2 pos,glm::vec2 target, float power);
	virtual ~Potion();
	void clean() override;
	void draw() override;
	void update() override;

private:
	void m_buildAnimations();
};
#endif 