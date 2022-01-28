#pragma once
#ifndef __SKULL__
#define __SKULL__

#include "DisplayObject.h"

class Skull final : public DisplayObject {
public:
	Skull();
	~Skull();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	int getEnemyHealth();
	int getEnemyDamage();

	void removeEnemyHealth(int health);
	void setEnemyHealth(int health);
	void setEnemyDamage(int damage);
	void setEnemyMaxHealth(int health);
private:
	int m_enemyHealth;
	int m_maxEnemyHealth;
	int m_enemyDamage;
};


#endif /* defined (__Skull__) */