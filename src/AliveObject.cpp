#include "AliveObject.h"
#include "Game.h"
AliveObject::AliveObject():m_bIsAlive(true), m_last_hit(0)
{
}

AliveObject::~AliveObject() = default;

bool AliveObject::isAlive()
{
	return m_bIsAlive;
}

bool AliveObject::hasCollisionDamage()
{
	return m_hasCollisionDamage;
}

int AliveObject::getMaxHealth()
{
	return m_maxHealth;
}

int AliveObject::getHealth()
{
	return m_health;
}

int AliveObject::getDamage()
{
	return m_damage;
}

int AliveObject::getLastHitFrame()
{
	return m_last_hit;
}

void AliveObject::setAlive(bool a)
{
	m_bIsAlive = a;
}

void AliveObject::setCollisionDamage(bool c)
{
	m_hasCollisionDamage = c;
}

void AliveObject::setMaxHealth(int mh)
{
	m_maxHealth = mh;
}

void AliveObject::setHealth(int h)
{
	m_health = h;
}

void AliveObject::setDamage(int d)
{
	m_damage = d;
}

void AliveObject::takeDamage(int damage)
{
	m_health -= damage;
	m_last_hit = TheGame::Instance().getFrames();
	if (m_health <= 0)
	{
		setDead();
	}
}

void AliveObject::takeHeal(int heal)
{
	m_health += heal;
	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}

void AliveObject::setDead()
{
	m_bIsAlive = false;
}
