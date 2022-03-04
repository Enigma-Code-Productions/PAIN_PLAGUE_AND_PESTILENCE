#include "PotionThrower.h"

#include "EventManager.h"
#include "Game.h"
#include "Player.h"

PotionThrower::PotionThrower(Player* player)
{
	m_pPlayer = player;
	getTransform()->position = m_pPlayer->getTransform()->position;

	m_buildAnimations();
}

PotionThrower::~PotionThrower() = default;

void PotionThrower::draw()
{
	if (m_pPotion != nullptr)
	{
		m_pPotion->draw();
	}
}

void PotionThrower::update()
{
	getTransform()->position = m_pPlayer->getTransform()->position;

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_G))
	{
		if (m_power < 1.0f)
			m_power += 0.01;
	}
	else if (EventManager::Instance().keyReleased(SDL_SCANCODE_G))
	{
		throwPotion();
		m_power = 0;
	}
	if (m_pPotion != nullptr)
	{
		m_pPotion->update();
	}
	std::cout << m_power << std::endl;
}

void PotionThrower::clean()
{
	if (m_pPotion != nullptr)
	{
		delete m_pPotion;
		m_pPotion = nullptr;
	}
	
}

void PotionThrower::throwPotion()
{
	auto target = EventManager::Instance().getMousePosition();

	m_pPotion = new Potion(getTransform()->position, target, m_power);
	
}

void PotionThrower::m_buildAnimations()
{
}
