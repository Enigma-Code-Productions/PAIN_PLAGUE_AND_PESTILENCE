#include "PoisonPotion.h"

#include "Poison1.h"
#include "Game.h"
#include "TextureManager.h"

PosionPotion::PosionPotion(glm::vec2 pos, glm::vec2 target): Potion(pos, target)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/GreenAnimation.txt",
		"../Assets/sprites/GreenAnimation1.png",
		"GreenBottleAnim");

	setWidth(50);
	setHeight(45);

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("GreenBottleAnim"));
	m_buildAnimations();
}

PosionPotion::~PosionPotion()
= default;

void PosionPotion::clean()
{
	Potion::clean();
}

void PosionPotion::draw()
{
	getTransform()->position.y -= m_height;

	if (m_velocityHeight == 0)
	{
		TextureManager::Instance().playAnimation(this, "breakingAnimation", 0.3f, 0.0, 255);
	}
	else
	{
		TextureManager::Instance().playAnimation(this, "GreenBottleIdle", 0.04f, m_rotation, 255);
	}
	getTransform()->position.y += m_height;
}

void PosionPotion::update()
{
	Potion::update();
	if (m_height <= 0.0f)
	{
		if (!m_effectTriggered)
		{
			SoundManager::Instance().playSound("PotionBreak", 0, -1);

			getParent()->addChildAfterUpdate(new Poison1(glm::vec2(getTransform()->position.x, getTransform()->position.y)), EFFECTS);
			m_effectTriggered = true;
		}
	}
	if (getAnimation("breakingAnimation").current_frame == 4)
	{
		getParent()->removeChildAfterUpdate(this);
	}
}

void PosionPotion::m_buildAnimations()
{
	Animation breakingAnimation = Animation();

	breakingAnimation.name = "breakingAnimation";
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Green-Bottle-0"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Green-Bottle-1"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Green-Bottle-2"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Green-Bottle-3"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Green-Bottle-Empty"));

	setAnimation(breakingAnimation);

	Animation bottle = Animation();

	bottle.name = "GreenBottleIdle";
	bottle.frames.push_back(getSpriteSheet()->getFrame("Green-Bottle-0"));

	setAnimation(bottle);
}
