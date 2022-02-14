#include "WinchesterShotgun.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Game.h"

void WinchesterShotgun::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (m_currentAnimationState)
	{
	case WINCHESTER_SHOTGUN_IDLE_RIGHT:
		TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case WINCHESTER_SHOTGUN_IDLE_LEFT:
		TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case WINCHESTER_SHOTGUN_ATTACK_RIGHT:
		TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("attack"),
			x, y, 1.0f, 0, 255, true);
		break;
	case WINCHESTER_SHOTGUN_ATTACK_LEFT:
		TextureManager::Instance().playAnimation("WinchesterShotgun", getAnimation("attack"),
			x, y, 1.0f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
}

void WinchesterShotgun::update()
{
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
	/*if (TheGame::Instance().getFrames() == getAttackStart() + getAttackTime())
	{
		setIsAttacking(false);
		setCollisionDamage(false);
		getRigidBody()->isColliding = false;
	}*/

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
		//setAttackStart(TheGame::Instance().getFrames());
		//setIsAttacking(true);
		//setCollisionDamage(true);

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