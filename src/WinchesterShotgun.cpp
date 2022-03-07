#include "WinchesterShotgun.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Game.h"

WinchesterShotgun::WinchesterShotgun(Player* player)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Winchester-Shotgun-Animation.txt",
		"../Assets/sprites/Winchester-Shotgun-Animation.png",
		"WinchesterShotgun");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("WinchesterShotgun"));

	//SoundManager::Instance().load("../Assets/audio/Knife.flac", "Knife", SOUND_SFX);

	setWidth(144);
	setHeight(75);
	setOwner(player);
	setDamage(10);
	setBulletCount(5);
	setBulletSpeed(7);
	setAccuracy(5);
	setIsAttacking(false);
	setAttackTime(40 - 1);
	setAttackStart(0);

	getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(45, 15));
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;


	setType(RANGED_WEAPON);

	m_buildAnimations();
}

WinchesterShotgun::~WinchesterShotgun() = default;

void WinchesterShotgun::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (m_currentAnimationState)
	{
	case WINCHESTER_SHOTGUN_IDLE_RIGHT:
		if (m_direction <= -90 || m_direction > 90)
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("idle"), x - 90, y, 0.12f, (int)m_direction, 255, true, SDL_FLIP_VERTICAL);
		}
		else
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("idle"), x, y, 0.12f, (int)m_direction, 255, true);
		}
		break;
	case WINCHESTER_SHOTGUN_IDLE_LEFT:		
		if (m_direction <= -90 || m_direction > 90)
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("idle"), x + 90, y, 0.12f, (int)m_direction + 180, 255, true);
		}
		else
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("idle"), x, y, 0.12f, (int)m_direction, 255, true, SDL_FLIP_HORIZONTAL);
		}
		break;
	case WINCHESTER_SHOTGUN_ATTACK_RIGHT:
		if (m_direction <= -90 || m_direction > 90)
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("attack"), x - 90, y, 0.12f, (int)m_direction, 255, true, SDL_FLIP_VERTICAL);
		}
		else
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("attack"), x, y, 0.12f, (int)m_direction, 255, true);
		}
		break;
	case WINCHESTER_SHOTGUN_ATTACK_LEFT:
		if (m_direction <= -90 || m_direction > 90)
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("attack"), x + 90, y, 0.12f, (int)m_direction + 180, 255, true);
		}
		else
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("attack"), x, y, 0.12f, (int)m_direction, 255, true, SDL_FLIP_HORIZONTAL);
		}
		break;
	default:
		break;
	}
}

void WinchesterShotgun::update()
{
	setDirection();
	m_move();
	if (!isAttacking())
	{

		if (getOwner()->isFacingRight())
		{
			setAnimationState(WINCHESTER_SHOTGUN_IDLE_RIGHT);
		}
		else
		{
			setAnimationState(WINCHESTER_SHOTGUN_IDLE_LEFT);
		}

	}
	else
	{
		if (getOwner()->isFacingRight())
		{
			setAnimationState(WINCHESTER_SHOTGUN_ATTACK_RIGHT);
		}
		else
		{
			setAnimationState(WINCHESTER_SHOTGUN_ATTACK_LEFT);
		}
	}
	if (TheGame::Instance().getFrames() == getAttackStart() + getAttackTime())
	{
		setIsAttacking(false);
	}

}

void WinchesterShotgun::clean()
{
}

void WinchesterShotgun::attack()
{
	if (!isAttacking())
	{
		//SoundManager::Instance().playSound("Knife", 0, 0);
		//SoundManager::Instance().setSoundVolume(6);
		setAttackStart(TheGame::Instance().getFrames());
		setIsAttacking(true);

		if (getOwner()->isFacingRight())
		{
			setAnimationState(WINCHESTER_SHOTGUN_ATTACK_RIGHT);
		}
		else
		{
			setAnimationState(WINCHESTER_SHOTGUN_ATTACK_LEFT);
		}
		for (int i = 0; i < m_bulletCount; i++)
		{
			float initialBulletDirection = m_direction + (rand() % 2 - 1) * m_accuracy;
			m_pBullets.push_back(new Bullet(m_bulletSpeed, initialBulletDirection));
		}
	}
}

void WinchesterShotgun::setAnimationState(WinchesterShotgunAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void WinchesterShotgun::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-idle"));
	setAnimation(idleAnimation);

	Animation attackAnimation = Animation();

	attackAnimation.name = "attack";

	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-idle"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-attack-0"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-attack-1"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-attack-2"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-attack-3"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-reload-0"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-reload-1"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-reload-2"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-reload-3"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-reload-4"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("WinchesterShotgun-reload-5"));

	setAnimation(attackAnimation);
}

void WinchesterShotgun::m_move()
{
	if (getOwner()->isFacingRight())
	{
		getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(45, 15));
	}
	else
	{
		getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(-45, 15));
	}
}

void WinchesterShotgun::setAccuracy(float accuracy)
{
	m_accuracy = accuracy;
}

void WinchesterShotgun::setBulletCount(int count)
{
	m_bulletCount = count;
}

void WinchesterShotgun::setDirection()
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