#include "PlayerUI.h"
#include "Player.h"

PlayerUI::PlayerUI(Player* player)
{
	m_pHelathBar = new HealthBar(player->getMaxHealth());
}

PlayerUI::~PlayerUI() = default;

void PlayerUI::draw()
{
	m_pHelathBar->draw();
}

void PlayerUI::update()
{
	m_pHelathBar->update();
}

void PlayerUI::clean()
{
	m_pHelathBar->clean();
}

HealthBar* PlayerUI::getHealthBar()
{
	return m_pHelathBar;
}
