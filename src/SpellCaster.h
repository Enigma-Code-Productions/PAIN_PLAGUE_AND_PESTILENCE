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

private:
	void m_buildAnimations();
	const int m_speed;
	float m_detectionRadius;
	Player* m_pPlayer;
};
#endif
