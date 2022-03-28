#include "Bullet.h"
#include <iostream>

#include "PlayScene.h"
#include "TextureManager.h"

Bullet::Bullet(float damage, float speed, float initialDirection, glm::vec2 weaponPos, BulletOwner bullet_owner)
{
	setOwner(bullet_owner);

	m_bulletDamage = damage;
	m_bulletSpeed = speed;
	m_direction = initialDirection;

	getTransform()->position = weaponPos;
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	glm::vec4 yellow = { 255 - 247, 255 - 215, 255 - 126, 255 };
	Util::DrawFilledRect(getTransform()->position, 10, 10, yellow);
}

void Bullet::update()
{
	m_move();
	//draw();
	if (getTransform()->position.x > 800 ||getTransform()->position.x < 0 ||getTransform()->position.y > 600 || getTransform()->position.y < 0)
	{
		dynamic_cast<PlayScene*>(getParent())->removeBullet(this);
	}
}

void Bullet::clean()
{
}

void Bullet::setBulletDamage(float damage)
{
	m_bulletDamage = damage;
}

float Bullet::getBulletDamage()
{
	return m_bulletDamage;
}


void Bullet::setBulletSpeed(float speed)
{
	m_bulletSpeed = speed;
}

float Bullet::getBulletSpeed()
{
	return m_bulletSpeed;
}

void Bullet::setOwner(BulletOwner o)
{
	m_owner = o;
}


BulletOwner Bullet::getOwner()
{
	return m_owner;
}

void Bullet::m_move()
{
	getTransform()->position += glm::vec2(cos(Util::Deg2Rad * m_direction), sin(Util::Deg2Rad * m_direction)) * m_bulletSpeed;
}

