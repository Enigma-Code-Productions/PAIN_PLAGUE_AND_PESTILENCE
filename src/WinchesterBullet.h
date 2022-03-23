#pragma once
#ifndef _WINCHESTER_BULLET
#define _WINCHESTER_BULLET

#include "Bullet.h"

class WinchesterBullet : public Bullet
{
public:
	WinchesterBullet(float damage, float s, float d, glm::vec2 pos, BulletOwner o);
	void m_buildAnimations();
	void draw();
};

#endif
