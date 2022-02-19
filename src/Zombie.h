#pragma once
#ifndef __ZOMBIE__
#define __ZOMBIE__

#include "AliveObject.h"
#include "Player.h"

class Zombie final : public AliveObject
{
public:

	Zombie(Player* player);
	Zombie(Player* player, glm::vec2 location);

	~Zombie();

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


#endif /* defined (__Skull__) */

