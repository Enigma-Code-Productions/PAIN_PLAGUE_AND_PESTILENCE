#include "HealthBar.h"
#include "TextureManager.h"
HealthBar::HealthBar()
{
	TextureManager::Instance().load("../Assets/textures/health_bar.png", "healthBar");
	TextureManager::Instance().load("../Assets/textures/health_bar_frame.png", "healthBarFrame");

	const auto size = TextureManager::Instance().getTextureSize("healthBarFrame");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(35.0f, 10.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	m_maxHealth = 100;
	m_health = m_maxHealth;

	setType(UI_ELEMENT);
}

HealthBar::HealthBar(int max_health) : HealthBar()
{
	m_maxHealth = max_health;
	m_health = max_health;
}

HealthBar::~HealthBar() = default;

void HealthBar::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance().draw("healthBarFrame", x, y, 0, 255, true, SDL_FLIP_NONE, 3);

	if (m_health > 0)
	{
		const auto toCut = getWidth() * (1 - ((float)m_health / m_maxHealth));
		TextureManager::Instance().drawCut("healthBar", x + 34, y, 0, toCut, 0, 0, 0, 255, true, SDL_FLIP_NONE, 3);
	}
}

void HealthBar::update()
{
}

void HealthBar::clean()
{
}

void HealthBar::setMaxHealth(int mh)
{
	m_maxHealth = mh;
}

void HealthBar::setHealth(int h)
{
	m_health = h;
}


