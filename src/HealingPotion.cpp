#include "HealingPotion.h"
#include "Player.h"
#include "TextureManager.h"
HealingPotion::HealingPotion(Player* player)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Healing-animation.txt",
		"../Assets/sprites/Healing-animation.png",
		"HealingAnimation");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("HealingAnimation"));

	m_pPlayer = player;

	setWidth(60);
	setHeight(60);
	m_bFacingRight = m_pPlayer->isFacingRight();

	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(USABLE);

	m_buildAnimations();
}

HealingPotion::~HealingPotion()
	= default;

void HealingPotion::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	if (m_bFacingRight)
	{
		TextureManager::Instance().playAnimation("HealingAnimation", getAnimation("healing"),
			x, y, 0.75f, 0, 255, true);
	}
	else
	{
		TextureManager::Instance().playAnimation("HealingAnimation", getAnimation("healing"),
			x, y, 0.75f, 0, 255, true, SDL_FLIP_HORIZONTAL);
	}
}

void HealingPotion::update()
{
	m_move();
	if (m_pPlayer->isFacingRight())
	{
		m_bFacingRight = true;
	}
	else
	{
		m_bFacingRight = false;
	}
}

void HealingPotion::clean()
{
}

void HealingPotion::m_move()
{
	if (m_pPlayer->isFacingRight())
	{
		getTransform()->position = glm::vec2(m_pPlayer->getTransform()->position + glm::vec2(45, 15));
	}
	else
	{
		getTransform()->position = glm::vec2(m_pPlayer->getTransform()->position + glm::vec2(-45, 15));
	}
}

void HealingPotion::m_buildAnimations()
{
	Animation healingAnimation = Animation();

	healingAnimation.name = "healing";
	healingAnimation.frames.push_back(getSpriteSheet()->getFrame("healing-animation-0"));
	healingAnimation.frames.push_back(getSpriteSheet()->getFrame("healing-animation-1"));
	healingAnimation.frames.push_back(getSpriteSheet()->getFrame("healing-animation-2"));
	healingAnimation.frames.push_back(getSpriteSheet()->getFrame("healing-animation-3"));
	healingAnimation.frames.push_back(getSpriteSheet()->getFrame("healing-animation-4"));
	healingAnimation.frames.push_back(getSpriteSheet()->getFrame("healing-animation-5"));
	healingAnimation.frames.push_back(getSpriteSheet()->getFrame("healing-animation-6"));
	healingAnimation.frames.push_back(getSpriteSheet()->getFrame("healing-animation-7"));
	healingAnimation.frames.push_back(getSpriteSheet()->getFrame("healing-animation-8"));
	healingAnimation.frames.push_back(getSpriteSheet()->getFrame("healing-animation-9"));
	setAnimation(healingAnimation);
}

