#pragma once
#include "Weapon.h"
class RangedWeapon : public Weapon
{
public:
	void attack();

	void setBulletSpeed(float speed);
	void setBulletCount(int count);
	void setAccuracy(int totalAngle);
	void setDirection(float angle);
	float getBulletSpeed();
	int getBulletCount();
	int getAccuracy();
	float getDirection();
private:
	float m_bulletSpeed;
	int m_bulletCount;
	int m_accuracy;
	float m_direction;
};

