#pragma once
#include "DisplayObject.h"
#include "Sprite.h"
#include "Util.h"

enum BulletOwner
{
	PLAYER_BULLET,
	ENEMY_BULLET
};

class Bullet : public Sprite
{
public:
	Bullet(float speed, float initialDirection, glm::vec2 weaponPos, BulletOwner bullet_owner);
	~Bullet();

	void draw() override;
	void update() override;
	void clean() override;

	void setBulletSpeed(float speed);
	float getBulletSpeed();

	void setOwner(BulletOwner o);
	BulletOwner getOwner();

private:
	void m_buildAnimations();
	void m_move();
	float m_direction;
	float m_bulletSpeed;

	BulletOwner m_owner;
};