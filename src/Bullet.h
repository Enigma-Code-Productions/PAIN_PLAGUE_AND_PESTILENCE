#pragma once
#include "DisplayObject.h"
#include "Util.h"

class Bullet : public DisplayObject
{
public:
	Bullet(float speed, float initialDirection, glm::vec2 weaponPos);
	~Bullet();

	void draw() override;
	void update() override;
	void clean() override;

	void setBulletSpeed(float speed);
	float getBulletSpeed();

private:
	void m_move();
	float m_direction;
	float m_bulletSpeed;

};