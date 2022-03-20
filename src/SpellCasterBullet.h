#pragma once
#ifndef _SPELLCASTER_BULLET_
#define _SPELLCASTER_BULLET_

#include "Bullet.h"

class SpellCasterBullet : public Bullet
{
public:
	SpellCasterBullet(float s, float d, glm::vec2 pos, BulletOwner o);
	void m_buildAnimations();
	void draw();
};

#endif
