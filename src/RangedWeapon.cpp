#include "RangedWeapon.h"

void RangedWeapon::attack()
{
	for (int i = 0; i < m_bulletCount; i++)
	{
		//to do
		float initialBulletDirection = m_direction + (rand() % 2 - 1) * m_accuracy;
		
	}
}

void RangedWeapon::update()
{
	setDirection();
}

void RangedWeapon::setBulletSpeed(float speed)
{
	m_bulletSpeed = speed;
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

float RangedWeapon::getBulletSpeed()
{
	return m_bulletSpeed;
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
