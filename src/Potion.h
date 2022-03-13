#pragma once
#ifndef __POTION__
#define __POTION__
#include "Sprite.h"


class Potion : public Sprite
{
protected:
	glm::vec2 m_target;
	float m_height;
	float m_accelerationHeight;
	float m_velocityHeight;
	float m_rotation;
	bool m_effectTriggered;
	bool m_forDelete;
public:
	Potion(glm::vec2 pos,glm::vec2 target);
	virtual ~Potion() = 0;
	virtual void clean() override;
	virtual void draw() override;
	virtual void update() override;
};
#endif 