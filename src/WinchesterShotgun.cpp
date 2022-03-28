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

void WinchesterShotgun::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (m_currentAnimationState)
	{
	case WINCHESTER_SHOTGUN_IDLE_RIGHT:
		if (getDirection() <= -90 || getDirection() > 90)
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("idle"), x, y, 0.12f, (int)getDirection(), 255, true, SDL_FLIP_VERTICAL);
		}
		else
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("idle"), x, y, 0.12f, (int)getDirection(), 255, true);
		}
		break;
	case WINCHESTER_SHOTGUN_IDLE_LEFT:
		if (getDirection() <= -90 || getDirection() > 90)
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("idle"), x, y, 0.12f, (int)getDirection() + 180, 255, true);
		}
		else
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("idle"), x, y, 0.12f, (int)getDirection(), 255, true, SDL_FLIP_HORIZONTAL);
		}
		break;
	case WINCHESTER_SHOTGUN_ATTACK_RIGHT:
		if (getDirection() <= -90 || getDirection() > 90)
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("attack"), x, y, 1.0f, (int)getDirection(), 255, true, SDL_FLIP_VERTICAL);
		}
		else
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("attack"), x, y, 1.0f, (int)getDirection(), 255, true);
		}
		break;
	case WINCHESTER_SHOTGUN_ATTACK_LEFT:
		if (getDirection() <= -90 || getDirection() > 90)
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("attack"), x, y, 1.0f, (int)getDirection() + 180, 255, true);
		}
		else
		{
			TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("attack"), x, y, 1.0f, (int)getDirection(), 255, true, SDL_FLIP_HORIZONTAL);
		}
		break;
	default:
		break;
	}

	/*for (unsigned i = 0; i < getBullets().size(); i++)
	{
		getBullets()[i]->draw();
	}*/
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