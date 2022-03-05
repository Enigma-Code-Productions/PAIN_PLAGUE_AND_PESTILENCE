#pragma once
#ifndef __POTION__
#define __POTION__
#include "Sprite.h"


class Potion : public Sprite
{
private:
	glm::vec2 m_target;
	float m_height;
	float m_accelerationHeight;
	float m_velocityHeight;
public:
	Potion(glm::vec2 pos,glm::vec2 target);
	virtual ~Potion();
	void clean() override;
	void draw() override;
	void update() override;

private:
	virtual void m_buildAnimations();
};
#endif 