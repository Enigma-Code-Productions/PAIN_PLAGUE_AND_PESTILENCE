#include "Skull.h"
#include "TextureManager.h"


Skull::Skull()
{
	TextureManager::Instance().load("../Assets/textures/Skull.png","Skull");
	
	//set Health 
	setMaxHealth(100);
	setHealth(getMaxHealth());
	setDamage(10);
	setCollisionDamage(true);

	const auto size = TextureManager::Instance().getTextureSize("Skull");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(ENEMY);
}

Skull::~Skull()
= default;

void Skull::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Skull
	TextureManager::Instance().draw("Skull", x, y, 0, 255, true);
}

void Skull::update()
{
}

void Skull::clean()
{
}


