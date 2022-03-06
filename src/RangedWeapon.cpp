#include "RangedWeapon.h"

void RangedWeapon::attack()
{
	for (int i = 0; i < m_bulletCount; i++)
	{
		float initialBulletDirection = m_direction + (rand() % 2 - 1) * m_accuracy;
		m_pBullets.push_back(new Bullet(m_bulletSpeed, initialBulletDirection));
	}
}

void RangedWeapon::update()
{
	setDirection();
}

void RangedWeapon::setBulletCount(int count)
{
	m_bulletCount = count;
}

void RangedWeapon::setAccuracy(int totalAngle)
{
	m_accuracy = totalAngle;
}

void RangedWeapon::setDirection()
{
	m_direction = Util::signedAngle(getTransform()->position, EventManager::Instance().getMousePosition());
}

int RangedWeapon::getBulletCount()
{
	return m_bulletCount;
}

int RangedWeapon::getAccuracy()
{
	return m_accuracy;
}

float RangedWeapon::getDirection()
{
	return m_direction;
}

std::vector<Bullet*> RangedWeapon::getBullets()
{
	return m_pBullets;
}

void RangedWeapon::setBulletSpeed(float speed)
{
	m_bulletSpeed = speed;
}
