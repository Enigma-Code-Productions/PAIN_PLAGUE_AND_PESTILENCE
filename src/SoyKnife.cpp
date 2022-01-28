#include "SoyKnife.h"
#include "TextureManager.h"

SoyKnife::SoyKnife(Player* player)
{
	TextureManager::Instance().load("../Assets/textures/Soy-Knife-Anim/Soy-knife-1.png", "SoyKnife1");

	const auto size = TextureManager::Instance().getTextureSize("SoyKinfe1");
	setWidth(size.x);
	setHeight(size.y);
	setOwner(player);
	getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(45, 20));
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(WEAPON);
}

SoyKnife::SoyKnife()
{
}

SoyKnife::~SoyKnife() = default;

void SoyKnife::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance().draw("SoyKnife1", x, y, 0, 255, true);
}

void SoyKnife::update()
{
	m_move();
}

void SoyKnife::clean()
{
}

void SoyKnife::m_move()
{
	getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(45, 20));
}


void SoyKnife::m_attack()
{
}
