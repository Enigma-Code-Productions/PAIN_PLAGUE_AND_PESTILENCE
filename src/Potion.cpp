#include "Potion.h"
#include "TextureManager.h"
#include "Util.h"

Potion::Potion(glm::vec2 pos, glm::vec2 target) : m_height(0.0f), m_accelerationHeight(-0.098), m_velocityHeight(3.0f), m_rotation(0), m_effectTriggered(false), m_forDelete(false)
{
	//TextureManager::Instance().load("../Assets/textures/Circle.png", "Potion");
	getTransform()->position = pos;
	getRigidBody()->velocity = (target - getTransform()->position) * 0.0155f;

}

Potion::~Potion() = default;

void Potion::clean()
{
}

void Potion::draw()
{
	//TextureManager::Instance().draw("Potion", getTransform()->position.x, getTransform()->position.y - m_height);
}

void Potion::update()
{
	getTransform()->position += getRigidBody()->velocity;
	m_height += m_velocityHeight + m_accelerationHeight;
	m_velocityHeight += m_accelerationHeight;
	m_rotation += 3.0f;
	if (m_height <= 0.0f)
	{
		m_height = 0.0f;
		getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
		m_velocityHeight = 0.0f;
		m_accelerationHeight = 0.0f;
		m_rotation = 0.0f;
	}
}

bool Potion::IsReadyToDelete()
{
	return m_forDelete;
}
