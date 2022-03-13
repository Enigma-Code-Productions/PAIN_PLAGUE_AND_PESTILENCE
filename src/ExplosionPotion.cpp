#include "ExplosionPotion.h"

#include "Explosion1.h"
#include "Game.h"
#include "TextureManager.h"

ExplosionPotion::ExplosionPotion(glm::vec2 pos, glm::vec2 target) : Potion(pos, target)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/purpleBottle_sheet.txt",
		"../Assets/sprites/purpleBottle_sheet.png",
		"PurpleBottleAnim");

	setWidth(50);
	setHeight(45);

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("PurpleBottleAnim"));
	m_buildAnimations();
}

ExplosionPotion::~ExplosionPotion()
= default;

void ExplosionPotion::clean()
{
	Potion::clean();
}

void ExplosionPotion::draw()
{
	getTransform()->position.y -= m_height;

	if (m_velocityHeight == 0)
	{
		TextureManager::Instance().playAnimation(this, "breakingAnimation", 0.3f, 0.0, 255);
	}
	else
	{
		TextureManager::Instance().playAnimation(this, "purpleBottleIdle", 0.04f, m_rotation, 255);
	}
	getTransform()->position.y += m_height;
}

void ExplosionPotion::update()
{
	Potion::update();
	if (m_height <= 0.0f)
	{
		if (!m_effectTriggered)
		{
			SoundManager::Instance().playSound("PotionBreak", 0, -1);
			SoundManager::Instance().setSoundVolume(4);

			getParent()->addChildAfterUpdate(new Explosion1(glm::vec2(getTransform()->position.x, getTransform()->position.y)), EFFECTS);
			m_effectTriggered = true;
		}
	}
	if (getAnimation("breakingAnimation").current_frame == 4)
	{
		getParent()->removeChildAfterUpdate(this);
	}
}

void ExplosionPotion::m_buildAnimations()
{
	Animation breakingAnimation = Animation();

	breakingAnimation.name = "breakingAnimation";
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Purple-Bottle-0"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Purple-Bottle-1"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Purple-Bottle-2"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Purple-Bottle-3"));
	breakingAnimation.frames.push_back(getSpriteSheet()->getFrame("Purple-Bottle-Empty"));

	setAnimation(breakingAnimation);

	Animation bottle = Animation();

	bottle.name = "purpleBottleIdle";
	bottle.frames.push_back(getSpriteSheet()->getFrame("Purple-Bottle-0"));

	setAnimation(bottle);
}
