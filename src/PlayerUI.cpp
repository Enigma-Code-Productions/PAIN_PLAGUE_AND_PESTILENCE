#include "PlayerUI.h"
#include "Player.h"
#include "PlayScene.h"
#include "TextureManager.h"

PlayerUI::PlayerUI(Player* player): m_pPlayer(player)
{
	m_pHelathBar = new HealthBar(player->getMaxHealth());
	
	const SDL_Color red = { 230, 0, 38, 255 };
	const SDL_Color black = { 0, 0, 0, 255 };
	m_pHealsLeftLabel = new Label(std::to_string(m_pPlayer->getHealsLeft()) + " Heals",
		"Toxia-OwOA", 30, red, glm::vec2(70.0f, 70.0f)); //800X600 window size

	m_pPotionsAmount = new Label(std::to_string(m_pPlayer->getThrower()->GetAmountPotions(m_pPlayer->getThrower()->GetChosenPotion())),
		"Toxia-OwOA", 50, black, glm::vec2(90.0f, 570.0f)); //800X600 window size

	m_pScore = new Label(std::to_string(dynamic_cast<PlayScene*>(getParent())->getScore()) + " Pts", "Toxia-OwOA", 60, black, glm::vec2(700.0f, 30.0f)); //800X600 window size

}

PlayerUI::~PlayerUI() = default;

void PlayerUI::draw()
{
	m_pHelathBar->draw();
	m_pHealsLeftLabel->draw();
	m_pPotionsAmount->draw();
	m_pScore->draw();

	auto potion = m_pPlayer->getThrower()->GetChosenPotion();
	switch (potion)
	{
	case POISON_POTION:
		TextureManager::Instance().draw("greenPotion", 0, 500);
		break;
	case FIRE_POTION:
		TextureManager::Instance().draw("redPotion", 0, 500, 0.0, 255, false, SDL_FLIP_NONE, 0.33f);
		break;
	case EXPLOSIVE_POTION:
		TextureManager::Instance().draw("purplePotion", 0, 500);
		break;
	}
}

void PlayerUI::update()
{
	m_pHelathBar->update();
	m_pHealsLeftLabel->update();
	m_pPotionsAmount->setText(std::to_string(m_pPlayer->getThrower()->GetAmountPotions(m_pPlayer->getThrower()->GetChosenPotion())));
	m_pPotionsAmount->update();
	m_pScore->setText(std::to_string(dynamic_cast<PlayScene*>(getParent())->getScore()) + " Pts");
	m_pScore->update();
}

void PlayerUI::clean()
{
	m_pHelathBar->clean();
	m_pHealsLeftLabel->clean();
	m_pPotionsAmount->clean();
	m_pScore->clean();

	delete m_pHelathBar;
	delete m_pHealsLeftLabel;
	delete m_pPotionsAmount;
	delete m_pScore;

	m_pHelathBar = nullptr;
	m_pHealsLeftLabel = nullptr;
	m_pPotionsAmount = nullptr;
	m_pScore = nullptr;
}

HealthBar* PlayerUI::getHealthBar()
{
	return m_pHelathBar;
}

void PlayerUI::setHeals()
{
	m_pHealsLeftLabel->setText(std::to_string(m_pPlayer->getHealsLeft()) + " Heals");
}
