#pragma once
#ifndef __SKULL__
#define __SKULL__

#include "AliveObject.h"
#include "Player.h"

class Skull final : public AliveObject
{
public:

	Skull(Player* player);
	Skull(Player* player, glm::vec2 location);

	~Skull();

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