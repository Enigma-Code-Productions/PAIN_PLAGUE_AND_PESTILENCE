#include "SoyKnife.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Game.h"

SoyKnife::SoyKnife(Player* player)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Soy-Knife-Animation.txt",
		"../Assets/sprites/Soy-Knife-Animation.png",
		"SoyKnife");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("SoyKnife"));

	SoundManager::Instance().load("../Assets/audio/Knife.flac", "Knife", SOUND_SFX);

	setWidth(48);
	setHeight(72);
	setOwner(player);
	setDamage(50);
	setRange(getWidth() / 2);
	setAttackTime(32 - 1);
	setIsAttacking(false);
	setAttackStart(0);
	setCollisionDamage(false);

	getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(45, 15));
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;


	setType(MELEE_WEAPON);

	m_buildAnimations();
}

//SoyKnife::SoyKnife()
//{
//}

SoyKnife::~SoyKnife() = default;

void SoyKnife::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (m_currentAnimationState)
	{
	case SOY_KNIFE_IDLE_RIGHT:
		TextureManager::Instance().playAnimation("SoyKnife", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case SOY_KNIFE_IDLE_LEFT:
		TextureManager::Instance().playAnimation("SoyKnife", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case SOY_KNIFE_ATTACK_RIGHT:
		TextureManager::Instance().playAnimation("SoyKnife", getAnimation("attack"),
			x, y, 1.0f, 0, 255, true);
		break;
	case SOY_KNIFE_ATTACK_LEFT:
		TextureManager::Instance().playAnimation("SoyKnife", getAnimation("attack"),
			x, y, 1.0f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
}

void SoyKnife::update()
{
	m_move();
	if (!isAttacking())
	{
		
		if (getOwner()->isFacingRight())
		{
			setAnimationState(SOY_KNIFE_IDLE_RIGHT);
		}
		else
		{
			setAnimationState(SOY_KNIFE_IDLE_LEFT);
		}

	}
	else
	{
		if (getOwner()->isFacingRight())
		{
			setAnimationState(SOY_KNIFE_ATTACK_RIGHT);
		}
		else
		{
			setAnimationState(SOY_KNIFE_ATTACK_LEFT);
		}
	}
	if (TheGame::Instance().getFrames() == getAttackStart() + getAttackTime())
	{
		setIsAttacking(false);
		setCollisionDamage(false);
		getRigidBody()->isColliding = false;
	}
	
}

void SoyKnife::clean()
{
}

void SoyKnife::attack()
{
	if (!isAttacking())
	{
		SoundManager::Instance().playSound("Knife", 0, 0);
		SoundManager::Instance().setSoundVolume(6);

		setAttackStart(TheGame::Instance().getFrames());
		setIsAttacking(true);
		setCollisionDamage(true);

		if (getOwner()->isFacingRight())
		{
			setAnimationState(SOY_KNIFE_ATTACK_RIGHT);
		}
		else
		{
			setAnimationState(SOY_KNIFE_ATTACK_LEFT);
		}
		
	}
	
}


void SoyKnife::setAnimationState(SoyKnifeAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void SoyKnife::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-idle"));
	setAnimation(idleAnimation);

	Animation attackAnimation = Animation();

	attackAnimation.name = "attack";

	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-idle"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-0"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-1"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-2"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-3"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-4"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-5"));
	attackAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-6"));

	setAnimation(attackAnimation);
}

void SoyKnife::m_move()
{
	if (getOwner()->isFacingRight())
	{
		getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(45, 15 ));
	}
	else
	{
		getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(-45, 15));
	}
}
