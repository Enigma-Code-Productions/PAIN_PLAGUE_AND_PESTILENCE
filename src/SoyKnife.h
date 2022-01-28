#pragma once
#include "Weapon.h"
#include "Player.h"
class SoyKnife : public Weapon
{
public:
	SoyKnife(Player* player);
	SoyKnife();
	~SoyKnife();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_move();
	void m_attack();
};

