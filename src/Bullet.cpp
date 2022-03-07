#include "Bullet.h"
#include <iostream>

Bullet::Bullet(float speed, float initialDirection, glm::vec2 weaponPos)
{
	m_bulletSpeed = speed;
	m_direction = initialDirection;

	m_bulletSpeed = 7;//why

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
}

void Bullet::clean()
{
}

void Bullet::setBulletSpeed(float speed)
{
	m_bulletSpeed = speed;
}

float Bullet::getBulletSpeed()
{
	return m_bulletSpeed;
}

void Bullet::m_move()
{
	getTransform()->position += glm::vec2(cos(Util::Deg2Rad * m_direction), sin(Util::Deg2Rad * m_direction)) * m_bulletSpeed;
}
