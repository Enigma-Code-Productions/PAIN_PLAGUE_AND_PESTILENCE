#include "Bullet.h"

Bullet::Bullet(float speed, float initialDirection)
{
	m_bulletSpeed = speed;
	m_direction = initialDirection;
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	Util::DrawFilledRect(getTransform()->position, 10, 10, { 247, 215, 126, 255});
}

void Bullet::update()
{
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
	getTransform()->position += glm::vec2(cos(m_direction), sin(m_direction)) * m_bulletSpeed;
}
