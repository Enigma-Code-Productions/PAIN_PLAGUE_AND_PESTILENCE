#include "ExplosionPotion.h"

#include "Explosion1.h"
#include "Game.h"
#include "TextureManager.h"

ExplosionPotion::ExplosionPotion(glm::vec2 pos, glm::vec2 target) : Potion(pos, target){}

ExplosionPotion::~ExplosionPotion()
= default;

void ExplosionPotion::clean()
{
	Potion::clean();
}

void ExplosionPotion::draw()
{
	if (m_velocityHeight == 0)
	{
		TextureManager::Instance().draw("purplePotion", getTransform()->position.x, getTransform()->position.y - m_height, m_rotation);
	}
	else
	{
		TextureManager::Instance().draw("purplePotion", getTransform()->position.x, getTransform()->position.y - m_height, m_rotation);
	}
}

void ExplosionPotion::update()
{
	Potion::update();
	if (m_height <= 0.0f)
	{
		if (!m_effectTriggered)
		{
			Game::Instance().getSceneState()->addChildAfterUpdate(new Explosion1(glm::vec2(getTransform()->position.x, getTransform()->position.y), glm::vec2(96.0f, 96.0f)));
			m_effectTriggered = true;
		}
	}
}
