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

	SoundManager::Instance().load("../Assets/audio/Winchester.mp3", "Winchester", SOUND_SFX);

	setWidth(144);
	setHeight(75);
	setOwner(player);
	setDamage(25);
	setBulletCount(5);
	setBulletSpeed(10);
	setAccuracy(10);
	setIsAttacking(false);
	setAttackTime(55); // to get this number: (number of frames in the animation / 2, round up) * (number of frames in the animation + 1), then give or take 1
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

	auto  angle = (double)m_direction;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	std::string animation_name = "idle";

	switch (m_currentAnimationState)
	{
	case WINCHESTER_SHOTGUN_IDLE_RIGHT:
		if (m_direction <= -90 || m_direction > 90)
		{
			flip = SDL_FLIP_VERTICAL;
		}
		else
		{
			flip = SDL_FLIP_NONE;
		}
		animation_name = "idle";
		break;
	case WINCHESTER_SHOTGUN_IDLE_LEFT:		
		if (m_direction <= -90 || m_direction > 90)
		{
			angle += 180;
			flip = SDL_FLIP_NONE;
		}
		else
		{
			flip = SDL_FLIP_HORIZONTAL;
		}
		animation_name = "idle";
		break;
	case WINCHESTER_SHOTGUN_ATTACK_RIGHT:
		if (m_direction <= -90 || m_direction > 90)
		{
			flip = SDL_FLIP_VERTICAL;
		}
		else
		{
			flip = SDL_FLIP_NONE;
		}
		animation_name = "attack";
		break;
	case WINCHESTER_SHOTGUN_ATTACK_LEFT:
		if (m_direction <= -90 || m_direction > 90)
		{
			angle += 180;
			flip = SDL_FLIP_NONE;
		}
		else
		{
			flip = SDL_FLIP_HORIZONTAL;
		}
		animation_name = "attack";
		break;
	default:
		break;
	}

	TextureManager::Instance().playAnimation(this, animation_name, 1.0f, angle, 255, flip);
}

void WinchesterShotgun::update()
{
	setDirection();
	m_move();

	if (TheGame::Instance().getFrames() == getAttackStart() + getAttackTime())
	{
		setIsAttacking(false);
	}

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

}

void WinchesterShotgun::clean()
{
}

void WinchesterShotgun::attack()
{
	if (!isAttacking())
	{
		SoundManager::Instance().playSound("Winchester", 0, 0);
		SoundManager::Instance().setSoundVolume(6);

		setAttackStart(TheGame::Instance().getFrames());
		setIsAttacking(true);

		for (int i = 0; i < m_bulletCount; i++)
		{
			float initialBulletDirection = m_direction + (Util::RandomRange(-1, 1)) * m_accuracy;
			if (!getOwner()->isFacingRight())
			{
				initialBulletDirection += 180;
			}
			auto tempBullet = new Bullet(m_bulletSpeed, initialBulletDirection, getTransform()->position, PLAYER_BULLET);

			dynamic_cast<PlayScene*>(getParent())->addBullet(tempBullet);
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
	/*if (getOwner()->isFacingRight())
	{
		getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(45, 15));

		if (m_direction <= -90 || m_direction > 90)
		{
			getTransform()->position.x -= 90;
		}
	}
	else
	{
		getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(-45, 15));

		if (m_direction <= -90 || m_direction > 90)
		{
			getTransform()->position.x += 90;
		}
	}*/

	getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(0, 25));
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
