#include "PlayerUI.h"
#include "Player.h"

PlayerUI::PlayerUI(Player* player): m_pPlayer(player)
{
	m_pHelathBar = new HealthBar(player->getMaxHealth());

	const SDL_Color red = { 230, 0, 38, 255 };
	m_pHealsLeftLabel = new Label(std::to_string(m_pPlayer->getHealsLeft()) + " Heals", "Toxia-OwOA", 30, red, glm::vec2(70.0f, 70.0f)); //800X600 window size
}

PlayerUI::~PlayerUI() = default;

void PlayerUI::draw()
{
	m_pHelathBar->draw();
	m_pHealsLeftLabel->draw();
}

void PlayerUI::update()
{
	m_pHelathBar->update();
	m_pHealsLeftLabel->update();
}

void PlayerUI::clean()
{
	m_pHelathBar->clean();
	m_pHealsLeftLabel->clean();
}

HealthBar* PlayerUI::getHealthBar()
{
	return m_pHelathBar;
}

void PlayerUI::setHeals()
{
	m_pHealsLeftLabel->setText(std::to_string(m_pPlayer->getHealsLeft()) + " Heals");
}
