#include "Skull.h"
#include "TextureManager.h"
#include "Util.h"
#include "CollisionManager.h"


Skull::Skull(Player* player, float detectionRadius) : m_speed(2)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Skull-animation.txt",
		"../Assets/sprites/Skull-animation.png",
		"Skull");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("Skull"));
	//set Health 
	setMaxHealth(100);
	setHealth(getMaxHealth());
	setDamage(10);
	setCollisionDamage(true);

	
	setWidth(48);
	setHeight(75);
	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	m_pPlayer = player;
	this->detectionRadius = detectionRadius;

	setType(ENEMY);
	m_buildAnimations();
}

Skull::~Skull()
= default;

void Skull::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Skull
	TextureManager::Instance().playAnimation("Skull", getAnimation("Skull-idle"),
		x, y, 0.4f, 0, 255, true, SDL_FLIP_HORIZONTAL);
}

void Skull::update()
{
	//if the player is within "seeing" range of the skull.
	if (CollisionManager::squaredDistance(getTransform()->position, m_pPlayer->getTransform()->position) < (detectionRadius * detectionRadius) && !getRigidBody()->isColliding)
	{
		getTransform()->position += Util::normalize(m_pPlayer->getTransform()->position - getTransform()->position) * glm::vec2(m_speed, m_speed);
		
		//getTransform()->position.x += ((m_pPlayer->getTransform()->position.x - getTransform()->position.x) / CollisionManager::squaredDistance(getTransform()->position, m_pPlayer->getTransform()->position)) * m_speed;
		//getTransform()->position.y += ((m_pPlayer->getTransform()->position.y - getTransform()->position.y) / CollisionManager::squaredDistance(getTransform()->position, m_pPlayer->getTransform()->position)) * m_speed;
	}
}

void Skull::clean()
{
}

void Skull::m_buildAnimations()
{
	Animation animation = Animation();

	animation.name = "Skull-idle";
	animation.frames.push_back(getSpriteSheet()->getFrame("skull-animation-0"));
	animation.frames.push_back(getSpriteSheet()->getFrame("skull-animation-1"));
	animation.frames.push_back(getSpriteSheet()->getFrame("skull-animation-2"));
	animation.frames.push_back(getSpriteSheet()->getFrame("skull-animation-3"));
	animation.frames.push_back(getSpriteSheet()->getFrame("skull-animation-4"));
	animation.frames.push_back(getSpriteSheet()->getFrame("skull-animation-5"));
	setAnimation(animation);
}


