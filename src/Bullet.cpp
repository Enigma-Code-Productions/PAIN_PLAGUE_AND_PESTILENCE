#include "Bullet.h"
#include <iostream>

Bullet::Bullet(float speed, float initialDirection)
{
	m_bulletSpeed = speed;
	m_direction = initialDirection;
	std::cout << "bullet created" << std::endl;
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	Util::DrawFilledRect(getTransform()->position, 10, 10, { 247, 215, 126, 255});
	std::cout << "bullet drawn" << std::endl;
}

void Bullet::update()
{
	std::cout << "bullet updated" << std::endl;
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
	std::cout << "bullet moved" << std::endl;
	getTransform()->position += glm::vec2(cos(m_direction), sin(m_direction)) * m_bulletSpeed;
}
