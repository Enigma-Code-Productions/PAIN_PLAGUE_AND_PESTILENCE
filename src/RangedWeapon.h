#pragma once
#include "Weapon.h"
#include "Util.h"
#include "EventManager.h"
#include "Bullet.h"
class RangedWeapon : public Weapon
{
public:
	void attack() override;
	void update() override;

	void setBulletCount(int count);
	void setAccuracy(int totalAngle);
	void setDirection();
	int getBulletCount();
	int getAccuracy();
	float getDirection();
	std::vector<Bullet*> getBullets();
	void setBulletSpeed(float speed);

private:
	std::vector<Bullet*> m_pBullets;
	float m_bulletSpeed;
	int m_bulletCount;
	int m_accuracy; //lower accuracy is better, and 0 is the best
	float m_direction;
};

