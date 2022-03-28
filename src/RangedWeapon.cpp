#include "RangedWeapon.h"
#include "Game.h"
#include "WinchesterBullet.h"
#include "SpellCasterBullet.h"

void RangedWeapon::m_move()
{
	getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(0, 25));
}

void RangedWeapon::attack()
{
	if (!isAttacking())
	{
		//SoundManager::Instance().playSound("Knife", 0, 0);
		//SoundManager::Instance().setSoundVolume(6);
		setAttackStart(TheGame::Instance().getFrames());
		setIsAttacking(true);

		for (int i = 0; i < m_bulletCount; i++)
		{
			float initialBulletDirection = m_direction + (Util::RandomRange(-1, 1)) * m_accuracy;
			if (!getOwner()->isFacingRight())
			{
				initialBulletDirection += 180;
			}

			// TODO: Change bullets back to normal

			auto tempBullet = new SpellCasterBullet(getDamage(), m_bulletSpeed, initialBulletDirection, getTransform()->position, PLAYER_BULLET);
			dynamic_cast<PlayScene*>(getParent())->addBullet(tempBullet);
		}
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

void RangedWeapon::setAccuracy(float accuracy)
{
	m_accuracy = accuracy;
}

void RangedWeapon::setDirection()
{
	float dx, dy;

	if (getOwner()->isFacingRight())
	{
		dx = getTransform()->position.x - EventManager::Instance().getMousePosition().x;
		dy = getTransform()->position.y - EventManager::Instance().getMousePosition().y;
		if (dy < 0)
		{
			m_direction = (Util::Rad2Deg * atanf(dx / dy) - 90) * -1;
		}
		if (dy >= 0)
		{
			m_direction = (Util::Rad2Deg * atanf(dx / dy) + 90) * -1;
		}
	}
	else
	{
		dx = EventManager::Instance().getMousePosition().x - getTransform()->position.x;
		dy = EventManager::Instance().getMousePosition().y - getTransform()->position.y;
		if (dy < 0)
		{
			m_direction = (Util::Rad2Deg * atanf(dx / dy) - 90) * -1;
		}
		if (dy >= 0)
		{
			m_direction = (Util::Rad2Deg * atanf(dx / dy) + 90) * -1;
		}
	}
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

void RangedWeapon::setBulletSpeed(float speed)
{
	m_bulletSpeed = speed;
}
