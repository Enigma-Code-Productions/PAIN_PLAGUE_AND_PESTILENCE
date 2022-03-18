#pragma once
#ifndef __SpellCaster__
#define __SpellCaster__

#include "AliveObject.h"
#include "Player.h"

class SpellCaster final : public AliveObject
{
public:

	SpellCaster(Player* player);
	SpellCaster(Player* player, glm::vec2 location);

	~SpellCaster();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void m_shootProjectile();
	void m_setDirection();

private:
	void m_buildAnimations();
	const int m_speed;
	const int m_bossProjectileInterval = 3 * 60;
	float m_shootDistance = 350;
	float m_detectionRadius;
	float m_bulletSpeed;
	float m_direction;
	Player* m_pPlayer;
};
#endif
