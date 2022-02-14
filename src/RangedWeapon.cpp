#include "RangedWeapon.h"

void RangedWeapon::attack()
{
	for (int i = 0; i < m_bulletCount; i++)
	{
		float spread = (rand() % 2 - 1) * m_accuracy;

	}
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
