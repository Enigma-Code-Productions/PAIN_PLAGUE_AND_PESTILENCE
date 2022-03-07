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
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y - m_height;

	if (m_velocityHeight == 0)
	{
		TextureManager::Instance().playAnimation("PurpleBottleAnim", getAnimation("breakingAnimation"), x, y, 0.3f, 0.0, 255);
	}
	else
	{
		TextureManager::Instance().playAnimation("PurpleBottleAnim", getAnimation("purpleBottleIdle"), x, y, 0.04f, m_rotation, 255);
	}
}

void ExplosionPotion::update()
{
	Potion::update();
	if (m_height <= 0.0f)
	{
		if (!m_effectTriggered)
		{
			Game::Instance().getSceneState()->addChildAfterUpdate(new Explosion1(glm::vec2(getTransform()->position.x, getTransform()->position.y)));
			m_effectTriggered = true;
		}
	}
	if (getAnimation("breakingAnimation").current_frame == 4)
	{
		m_forDelete = true;
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
