#pragma once
#include "Weapon.h"
#include "Util.h"
#include "EventManager.h"
#include "Bullet.h"
class RangedWeapon : public Weapon
{
private:
	std::vector<Bullet*> m_pBullets;
	float m_bulletSpeed;
	int m_bulletCount;
	float m_accuracy; //lower accuracy is better, and 0 is the best
	float m_direction;

public:
	RangedWeapon() {}
	//RangedWeapon(Player*) {}
	virtual ~RangedWeapon() = default;

	void m_move();
	void attack() override;
	void update() override;
	void clean() {}

	//setters
	void setBulletCount(int count);
	void setAccuracy(float accuracy);
	void setDirection();
	void setBulletSpeed(float speed);
	void setBullets(std::vector<Bullet*> bullets);

	//getters
	int getBulletCount();
	int getAccuracy();
	float getDirection();
	std::vector<Bullet*> getBullets();
	
};

