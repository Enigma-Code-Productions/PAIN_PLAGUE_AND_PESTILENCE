#include "TemplateObject.h"
#include "TextureManager.h"


TemplateObject::TemplateObject()
{
	TextureManager::Instance().load("../Assets/textures/Circle.png","circle");

	const auto size = TextureManager::Instance().getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(NONE);
}

TemplateObject::~TemplateObject()
= default;

void TemplateObject::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance().draw("circle", x, y, 0, 255, true);
}

void TemplateObject::update()
{
	m_move();
	m_checkBounds();
}

void TemplateObject::clean()
{
}

void TemplateObject::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void TemplateObject::m_checkBounds()
{
}

void TemplateObject::m_reset()
{
}
