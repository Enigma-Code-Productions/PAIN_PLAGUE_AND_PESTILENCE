#include "SoyKnife.h"
#include "TextureManager.h"
#include"EventManager.h"
#include "Game.h"

SoyKnife::SoyKnife(Player* player): m_bIsAttacking(false), ATTACK_TIME(31)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Soy-Knife-Animation.txt",
		"../Assets/sprites/Soy-Knife-Animation.png",
		"SoyKnife");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("SoyKnife"));

	setWidth(48);
	setHeight(72);
	setOwner(player);
	getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(45, 15));
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;


	setType(WEAPON);

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
	if (!m_bIsAttacking)
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
	if (TheGame::Instance().getFrames() == m_AttackStart + ATTACK_TIME)
	{
		m_bIsAttacking = false;
		std::cout << std::endl;
	}
	
}

void SoyKnife::clean()
{
}

void SoyKnife::attack()
{
	if (!m_bIsAttacking)
	{
		m_AttackStart = TheGame::Instance().getFrames();
		m_bIsAttacking = true;


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

	Animation attckAnimation = Animation();

	attckAnimation.name = "attack";

	attckAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-idle"));
	attckAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-0"));
	attckAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-1"));
	attckAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-2"));
	attckAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-3"));
	attckAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-4"));
	attckAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-5"));
	attckAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-6"));

	setAnimation(attckAnimation);
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
