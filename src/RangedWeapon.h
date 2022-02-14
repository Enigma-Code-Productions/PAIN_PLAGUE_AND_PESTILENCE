#pragma once
#include "Weapon.h"
class RangedWeapon : public Weapon
{
public:
	void attack();

	void setBulletSpeed(float speed);
	void setBulletCount(int count);
	void setAccuracy(int totalAngle);
	float getBulletSpeed();
	int getBulletCount();
	int getAccuracy();
private:
	float m_bulletSpeed;
	int m_bulletCount;
	int m_accuracy;
};

