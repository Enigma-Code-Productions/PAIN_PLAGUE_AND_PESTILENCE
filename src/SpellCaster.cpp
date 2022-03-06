#include "SpellCaster.h"
#include "TextureManager.h"
#include "Util.h"
#include "CollisionManager.h"


#include "Zombie.h"
#include "TextureManager.h"
#include "Util.h"
#include "CollisionManager.h"


SpellCaster::SpellCaster(Player* player) : m_speed(2), m_detectionRadius(250)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/SpellCaster-1.txt",
		"../Assets/spritesSpellCaster-1.png",
		"SpellCaster");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("SpellCaster"));
	//set Health 
	setMaxHealth(150);
	setHealth(getMaxHealth());
	setDamage(15);
	setCollisionDamage(true);


	setWidth(48);
	setHeight(75);
	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	m_pPlayer = player;

	setType(ENEMY);
	m_buildAnimations();
}

Zombie::Zombie(Player* player, glm::vec2 location) : Zombie(player)
{
	getTransform()->position = location;
}

Zombie::~Zombie()
= default;

void Zombie::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Skull
	TextureManager::Instance().playAnimation("Zombie", getAnimation("Zombie-idle"),
		x, y, 0.4f, 0, 255, true, SDL_FLIP_HORIZONTAL);
}

void Zombie::update()
{
	//if the player is within "seeing" range of the Zombie.
	if (CollisionManager::squaredDistance(getTransform()->position, m_pPlayer->getTransform()->position) < (m_detectionRadius * m_detectionRadius) && !getRigidBody()->isColliding)
	{
		getTransform()->position += Util::normalize(m_pPlayer->getTransform()->position - getTransform()->position) * glm::vec2(m_speed, m_speed);
	}
}

void Zombie::clean()
{
}

void Zombie::m_buildAnimations()
{
	Animation animation = Animation();

	animation.name = "Zombie-idle";
	animation.frames.push_back(getSpriteSheet()->getFrame("Zombie-animation-0"));
	animation.frames.push_back(getSpriteSheet()->getFrame("Zombie-animation-1"));
	animation.frames.push_back(getSpriteSheet()->getFrame("Zombie-animation-2"));
	animation.frames.push_back(getSpriteSheet()->getFrame("Zombie-animation-3"));
	animation.frames.push_back(getSpriteSheet()->getFrame("Zombie-animation-4"));
	animation.frames.push_back(getSpriteSheet()->getFrame("Zombie-animation-5"));
	setAnimation(animation);
}
