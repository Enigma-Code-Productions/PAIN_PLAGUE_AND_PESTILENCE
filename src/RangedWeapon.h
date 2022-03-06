#pragma once
#include "Weapon.h"
#include "Util.h"
#include "EventManager.h"
class RangedWeapon : public Weapon
{
public:
	void attack() override;
	void update() override;

	void setBulletSpeed(float speed);
	void setBulletCount(int count);
	void setAccuracy(int totalAngle);
	void setDirection();
	float getBulletSpeed();
	int getBulletCount();
	int getAccuracy();
	float getDirection();
private:
	float m_bulletSpeed;
	int m_bulletCount;
	int m_accuracy; //lower accuracy is better, and 0 is the best
	float m_direction;
};

