#include "Potion.h"

#include "TextureManager.h"

Potion::Potion(glm::vec2 pos, glm::vec2 target, float power)
{
	TextureManager::Instance().load("../Assets/textures/Circle.png", "Potion");
	getTransform()->position = pos;
	getRigidBody()->velocity = (target - getTransform()->position) * 0.01f * power;
}

Potion::~Potion() = default;

void Potion::clean()
{
}

void Potion::draw()
{
	TextureManager::Instance().draw("Potion", getTransform()->position.x, getTransform()->position.y);
}

void Potion::update()
{
	getTransform()->position += getRigidBody()->velocity;
	getRigidBody()->velocity *= 0.995;
}

void Potion::m_buildAnimations()
{
}
