#include "GameObject.h"

#include "Game.h"

GameObject::GameObject() :
	m_width(0), m_height(0), m_type(NONE), m_enabled(true), m_visible(true)
{
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	getRigidBody()->hasCollider = false;
	getRigidBody()->maxVelocity = 10;
}

GameObject::~GameObject()
= default;

Transform* GameObject::getTransform()
{
	return &m_transform;
}

RigidBody* GameObject::getRigidBody()
{
	return &m_rigidBody;
}

int GameObject::getWidth() const
{
	return m_width;
}

int GameObject::getHeight() const
{
	return m_height;
}

GameObjectType GameObject::getType() const
{
	return m_type;
}

void GameObject::setWidth(const int new_width)
{
	m_width = new_width;
}

void GameObject::setHeight(const int new_height)
{
	m_height = new_height;
}

void GameObject::setType(const GameObjectType new_type)
{
	m_type = new_type;
}

void GameObject::setEnabled(const bool state)
{
	m_enabled = state;
}

bool GameObject::isEnabled() const
{
	return m_enabled;
}

void GameObject::setVisible(const bool state)
{
	m_visible = state;
}

bool GameObject::isVisible() const
{
	return m_visible;
}

void GameObject::move()
{
	const auto rigid_body = getRigidBody();

	
	rigid_body->velocity += rigid_body->acceleration;
	rigid_body->velocity *= dynamic_cast<PlayScene*>(Game::Instance().getCurrentScene())->getDrag();
	rigid_body->velocity = Util::clamp(rigid_body->velocity, rigid_body->maxVelocity);

	if (rigid_body->hasCollider)
	{
		if (!CollisionManager::canMoveWithoutCollison(this, getTransform()->position + rigid_body->velocity))
		{
			rigid_body->velocity = glm::vec2(0.0f, 0.0f);
		}
	}
	getTransform()->position += rigid_body->velocity;
	rigid_body->acceleration = glm::vec2(0.0f, 0.0f);
}
