#include "PoisonPotion.h"
#include "Game.h"
#include "TextureManager.h"

PosionPotion::PosionPotion(glm::vec2 pos, glm::vec2 target): Potion(pos, target)
{
}

PosionPotion::~PosionPotion()
= default;

void PosionPotion::clean()
{
	Potion::clean();
}

void PosionPotion::draw()
{
	if (m_velocityHeight == 0)
	{
		TextureManager::Instance().draw("greenPotion", getTransform()->position.x, getTransform()->position.y - m_height, m_rotation);
	}
	else
	{
		TextureManager::Instance().draw("greenPotion", getTransform()->position.x, getTransform()->position.y - m_height, m_rotation);
	}
}

void PosionPotion::update()
{
	Potion::update();
	if (m_height == 0.0f)
	{
		SoundManager::Instance().playSound("PotionBreak", 0, -1);
		SoundManager::Instance().setSoundVolume(4);
		getParent()->removeChildAfterUpdate(this);
	}
}

void PosionPotion::m_buildAnimations()
{
}
