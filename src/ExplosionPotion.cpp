#include "ExplosionPotion.h"
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
}
