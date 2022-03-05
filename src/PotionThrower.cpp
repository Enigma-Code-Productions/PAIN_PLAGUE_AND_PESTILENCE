#include "PotionThrower.h"

#include "EventManager.h"
#include "Game.h"
#include "Player.h"
#include "PoisonPotion.h"

PotionThrower::PotionThrower(Player* player)
{
	m_pPlayer = player;
	getTransform()->position = m_pPlayer->getTransform()->position;
	getTransform()->position.y -= 40.0f;
	m_buildAnimations();
}

PotionThrower::~PotionThrower() = default;

void PotionThrower::draw()
{
	for (auto potion : m_pPotions)
	{
		potion->draw();
	}
}

void PotionThrower::update()
{
	getTransform()->position = m_pPlayer->getTransform()->position;

	if (!m_pPlayer->isFacingRight())
		getTransform()->position.x -= 60.0f;

	getTransform()->position.y -= 40.0f;
	if (EventManager::Instance().keyReleased(SDL_SCANCODE_G))
	{
		throwPotion();
	}
	for (auto potion : m_pPotions)
	{
		potion->update();
	}
}

void PotionThrower::clean()
{
	if (!m_pPotions.empty())
	{
		for (int i = 0; i < m_pPotions.size(); i++)
		{
			delete m_pPotions[i];
			m_pPotions[i] = nullptr;
		}
		m_pPotions.clear();
	}
	
}

void PotionThrower::throwPotion()
{
	auto target = EventManager::Instance().getMousePosition();

	m_pPotions.push_back(new PosionPotion(getTransform()->position, target));
	
}

void PotionThrower::m_buildAnimations()
{
}
