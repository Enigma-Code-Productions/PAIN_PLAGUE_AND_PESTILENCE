#include "PotionThrower.h"

#include "EventManager.h"
#include "Game.h"
#include "Player.h"
#include "PoisonPotion.h"
#include "ExplosionPotion.h"
#include "FirePotion.h"

PotionThrower::PotionThrower(Player* player) : m_MaxPotions(3), m_pPlayer(player), m_chosenPotion(POISON_POTION)
{
	getTransform()->position = m_pPlayer->getTransform()->position;
	getTransform()->position.y -= 40.0f;
	m_buildAnimations();
	
	m_amountOfPotions[POISON_POTION] = 2;
	m_amountOfPotions[FIRE_POTION] = 2;
	m_amountOfPotions[EXPLOSIVE_POTION] = 2;
	m_loadPotionsSprites();
}

PotionThrower::~PotionThrower() = default;

void PotionThrower::draw()
{
}

void PotionThrower::update()
{
	getTransform()->position = m_pPlayer->getTransform()->position;

	if (m_pPlayer->isFacingRight())
		getTransform()->position.x += 45.0f;
	else
		getTransform()->position.x -= 45.0f;
	
	if (EventManager::Instance().keyReleased(SDL_SCANCODE_G))
	{
		throwPotion();
	}
	if (EventManager::Instance().keyPressed(SDL_SCANCODE_Q))
	{
		m_chosenPotion = static_cast<Potions>(m_chosenPotion + 1);
		if (m_chosenPotion == NUM_OF_POTIONS)
		{
			m_chosenPotion = static_cast<Potions>(0);
		}
	}

}

void PotionThrower::clean()
{
}

void PotionThrower::throwPotion()
{
	if (m_amountOfPotions[m_chosenPotion] == 0)
		return;

	auto target = EventManager::Instance().getMousePosition();
	Potion* tempPotion = nullptr;

	switch (m_chosenPotion)
	{
	case POISON_POTION:
		
		tempPotion = new PosionPotion(getTransform()->position, target);
		m_amountOfPotions[POISON_POTION]--;
		break;

	case FIRE_POTION:
		tempPotion = new FirePotion(getTransform()->position, target);
		m_amountOfPotions[FIRE_POTION]--;
		break;

	case EXPLOSIVE_POTION:
		tempPotion = new ExplosionPotion(getTransform()->position, target);
		m_amountOfPotions[EXPLOSIVE_POTION]--;
		break;
	default:
		break;
	}
	
	getParent()->addChildAfterUpdate(tempPotion, FRONT_OBJECTS);

}

int PotionThrower::GetAmountPotions(Potions p)
{
	return m_amountOfPotions[p];
}

Potions PotionThrower::GetChosenPotion()
{
	return m_chosenPotion;
}

void PotionThrower::m_loadPotionsSprites()
{
	TextureManager::Instance().load("../Assets/textures/Green_Cork.png", "greenPotion");
	TextureManager::Instance().load("../Assets/textures/purple_bottle.png", "purplePotion");
	TextureManager::Instance().load("../Assets/textures/redBottle.png", "redPotion");

}

void PotionThrower::m_buildAnimations()
{
}

