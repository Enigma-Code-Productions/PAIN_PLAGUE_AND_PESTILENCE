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

	getTransform()->position += rigid_body->velocity;
	rigid_body->acceleration = glm::vec2(0.0f, 0.0f);

	if (rigid_body->hasCollider)
	{
		const auto colliders = static_cast<PlayScene*>(Game::Instance().getCurrentScene())->getCollidables();

		const auto p1 = getTransform()->position - glm::vec2(getWidth() / 2, getHeight() / 2);
		const float p1Width = getWidth();
		const float p1Height = getHeight();

		for (auto object : colliders)
		{
			if (object == this)
				continue;

			const auto p2 = object->getTransform()->position - glm::vec2(object->getWidth() / 2, object->getHeight() / 2);
			const float p2Width = object->getWidth();
			const float p2Height = object->getHeight();
			if (
				p1.x < p2.x + p2Width &&
				p1.x + p1Width > p2.x &&
				p1.y < p2.y + p2Height &&
				p1.y + p1Height > p2.y
				)
			{
				if (dynamic_cast<Player*>(this))
				{
					std::cout << std::endl;
				}

				//if colliding with top side
				if ((getTransform()->position.y + getHeight() / 2) >= object->getTransform()->position.y - object->getHeight() / 2)
				{
					rigid_body->velocity.y = 0;
					getTransform()->position.y = object->getTransform()->position.y - ((float)object->getHeight() / 2.0f) - ((float)getHeight() / 2.0f);
					// pObj->SetY(pTile->y - pBound->h);

				}
				// if colliding with a bottom
				else if (getTransform()->position.y - getHeight() / 2  <= object->getTransform()->position.y + object->getHeight() / 2)
				{
					rigid_body->velocity.y = 0;
					getTransform()->position.y = object->getTransform()->position.y + ((float)object->getHeight() / 2.0f) + ((float)getHeight() / 2.0f);
					// pObj->SetY(pTile->y + pTile->h);

				}
				//if colliding with left side
				else if ((getTransform()->position.x + getWidth() / 2) >= object->getTransform()->position.x - object->getWidth() / 2)
				{
					rigid_body->velocity.x = 0;
					getTransform()->position.x = object->getTransform()->position.x - ((float)object->getWidth() / 2.0f) - ((float)getWidth() / 2.0f);
					// pObj->SetX(pTile->x - pBound->w);

				}
				// if colliding with right side
				else if ((getTransform()->position.x - getWidth() / 2) <= object->getTransform()->position.x + object->getWidth() / 2)
				{
					rigid_body->velocity.x = 0;
					getTransform()->position.x = object->getTransform()->position.x + ((float)object->getWidth() / 2.0f) + ((float)getWidth() / 2.0f);
					// pObj->SetX(pTile->x + pTile->w);

				}
			}
		}
	}
}
