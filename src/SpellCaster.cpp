#include "SpellCaster.h"
#include "TextureManager.h"
#include "Util.h"
#include "CollisionManager.h"

#include "TextureManager.h"
#include "Util.h"
#include "CollisionManager.h"


SpellCaster::SpellCaster(Player* player) : m_speed(1), m_detectionRadius(250)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/SpellCaster-1.txt",
		"../Assets/sprites/SpellCaster-1.png",
		"SpellCaster");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("SpellCaster"));
	//set Health 
	setMaxHealth(150);
	setHealth(getMaxHealth());
	setDamage(15);
	setCollisionDamage(true);


	setWidth(96);
	setHeight(96);
	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	m_pPlayer = player;

	setType(ENEMY);
	m_buildAnimations();
}

SpellCaster::SpellCaster(Player* player, glm::vec2 location) : SpellCaster(player)
{
	getTransform()->position = location;
}

SpellCaster::~SpellCaster()
= default;

void SpellCaster::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Skull
	TextureManager::Instance().playAnimation("SpellCaster", getAnimation("SpellCaster-idle"),
		x, y, 0.4f, 0, 255, true, SDL_FLIP_HORIZONTAL);
}

void SpellCaster::update()
{
	//if the player is within "seeing" range of the Zombie.
	if (CollisionManager::squaredDistance(getTransform()->position, m_pPlayer->getTransform()->position) < (m_detectionRadius * m_detectionRadius) && !getRigidBody()->isColliding)
	{
		getTransform()->position += Util::normalize(m_pPlayer->getTransform()->position - getTransform()->position) * glm::vec2(m_speed, m_speed);
	}
}

void SpellCaster::clean()
{
}

void SpellCaster::m_buildAnimations()
{
	Animation animation = Animation();

	animation.name = "SpellCaster-idle";
	//first 4 are idle
	animation.frames.push_back(getSpriteSheet()->getFrame("SpellCaster-animation-0"));
	animation.frames.push_back(getSpriteSheet()->getFrame("SpellCaster-animation-1"));
	animation.frames.push_back(getSpriteSheet()->getFrame("SpellCaster-animation-2"));
	animation.frames.push_back(getSpriteSheet()->getFrame("SpellCaster-animation-3"));
	//animation.frames.push_back(getSpriteSheet()->getFrame("SpellCaster-animation-4"));
	//animation.frames.push_back(getSpriteSheet()->getFrame("SpellCaster-animation-5"));
	//animation.frames.push_back(getSpriteSheet()->getFrame("SpellCaster-animation-6"));
	//animation.frames.push_back(getSpriteSheet()->getFrame("SpellCaster-animation-7"));
	setAnimation(animation);
}
