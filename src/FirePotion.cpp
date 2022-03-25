#include "FirePotion.h"
#include "Game.h"
#include "TextureManager.h"

FirePotion::FirePotion(glm::vec2 pos, glm::vec2 target) : Potion(pos, target) 
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/RedAnimation.txt",
		"../Assets/sprites/RedAnimation.png",
		"RedBottleAnim");

	setWidth(50);
	setHeight(45);

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("RedBottleAnim"));
	m_buildAnimations();
}

FirePotion::~FirePotion()
= default;

void FirePotion::clean()
{
	Potion::clean();
}

void FirePotion::draw()
{
	getTransform()->position.y -= m_height;

	if (m_velocityHeight == 0)
	{
		TextureManager::Instance().playAnimation(this, "breakingAnimation", 0.3f, 0.0, 255);
	}
	else
	{
		TextureManager::Instance().playAnimation(this, "redBottleIdle", 0.04f, m_rotation, 255);
	}
	getTransform()->position.y += m_height;
}

void FirePotion::update()
{
	Potion::update();
	if (m_height <= 0.0f)
	{
		if (!m_effectTriggered)
		{
			SoundManager::Instance().playSound("PotionBreak", 0, -1);

			//getParent()->addChildAfterUpdate(new Explosion1(glm::vec2(getTransform()->position.x, getTransform()->position.y)), EFFECTS);
			//m_effectTriggered = true;
		}
	}
	if (getAnimation("breakingAnimation").current_frame == 4)
	{
		getParent()->removeChildAfterUpdate(this);
	}
}

void FirePotion::m_buildAnimations()
{
	Animation breakingAnimation = Animation();

	breakingAnimation.name = "breakingAnimation";
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Red-Bottle-0"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Red-Bottle-1"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Red-Bottle-2"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Red-Bottle-3"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Red-Bottle-Empty"));

	setAnimation(breakingAnimation);

	Animation bottle = Animation();

	bottle.name = "redBottleIdle";
	bottle.frames.push_back(getSpriteSheet()->getFrame("Red-Bottle-0"));

	setAnimation(bottle);
}
