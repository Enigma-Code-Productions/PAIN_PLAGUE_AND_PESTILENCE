#include "FirePotion.h"
#include "Game.h"
#include "TextureManager.h"

FirePotion::FirePotion(glm::vec2 pos, glm::vec2 target) : Potion(pos, target) {}

FirePotion::~FirePotion()
= default;

void FirePotion::clean()
{
	Potion::clean();
}

void FirePotion::draw()
{
	if (m_velocityHeight == 0)
	{
		TextureManager::Instance().draw("redPotion", getTransform()->position.x, getTransform()->position.y - m_height, m_rotation,
			255, false, SDL_FLIP_NONE, 0.33f);
	}
	else
	{
		TextureManager::Instance().draw("redPotion", getTransform()->position.x, getTransform()->position.y - m_height, m_rotation,
			255, false, SDL_FLIP_NONE, 0.33f);
	}
}

void FirePotion::update()
{
	Potion::update();
	if (m_height == 0.0f)
	{
		SoundManager::Instance().playSound("PotionBreak", 0, -1);
		SoundManager::Instance().setSoundVolume(4);
		getParent()->removeChildAfterUpdate(this);
	}
}
