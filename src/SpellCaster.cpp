#include "SpellCaster.h"
#include "TextureManager.h"
#include "Util.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "Util.h"
#include "CollisionManager.h"
#include "Game.h"


SpellCaster::SpellCaster(Player* player) : m_speed(1), m_detectionRadius(250)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/SpellCaster-1.txt",
		"../Assets/sprites/SpellCaster-1.png",
		"SpellCaster");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("SpellCaster"));
	//set Health 
	//setMaxHealth(150); //Non-Boss Health
	setMaxHealth(300); //Boss Health
	setHealth(getMaxHealth());
	//setDamage(15); //Non-boss Damage
	setDamage(30); //Boss Damage;
	setCollisionDamage(true);


	setWidth(96);
	setHeight(96);
	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;
	getRigidBody()->hasCollider = true;

	m_bulletSpeed = 2;

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

	if (m_pPlayer->getTransform()->position.x > x)
	{
		TextureManager::Instance().playAnimation(this, "SpellCaster-idle", 0.4f, 0, 255);
	}
	else if (m_pPlayer->getTransform()->position.x < x)
	{
		TextureManager::Instance().playAnimation(this, "SpellCaster-idle", 0.4f, 0, 255, SDL_FLIP_HORIZONTAL);
	}
}

void SpellCaster::update()
{
	//if the player is within "seeing" range of the Zombie.
	//if (CollisionManager::squaredDistance(getTransform()->position, m_pPlayer->getTransform()->position) < (m_detectionRadius * m_detectionRadius) && !getRigidBody()->isColliding)
	//{
	//	getTransform()->position += Util::normalize(m_pPlayer->getTransform()->position - getTransform()->position) * glm::vec2(m_speed, m_speed);
	//}

	//Boss Follow
	if (CollisionManager::canMoveWithoutCollison(this,
		getTransform()->position + Util::normalize(m_pPlayer->getTransform()->position - getTransform()->position) * glm::vec2(m_speed, m_speed)))
	{
		getTransform()->position += Util::normalize(m_pPlayer->getTransform()->position - getTransform()->position) * glm::vec2(m_speed, m_speed);
	}

	std::cout << "Distance: " << Util::distance(getTransform()->position, m_pPlayer->getTransform()->position) << std::endl;

	if(Game::Instance().getFrames() % m_bossProjectileInterval == 0)
	{
		if (Util::distance(getTransform()->position, m_pPlayer->getTransform()->position) < m_shootDistance)
			m_shootProjectile();
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

void SpellCaster::m_shootProjectile()
{
	m_setDirection();
	auto tempBullet = new Bullet(m_bulletSpeed, m_direction, getTransform()->position);
	tempBullet->setOwner(ENEMY_BULLET);
	dynamic_cast<PlayScene*>(getParent())->addBullet(tempBullet);
}

void SpellCaster::m_setDirection()
{
	float dx, dy;

	dx = getTransform()->position.x - m_pPlayer->getTransform()->position.x;
	dy = getTransform()->position.y - m_pPlayer->getTransform()->position.y;

	if(dy < 0)
	{
		m_direction = (Util::Rad2Deg * atan(dx / dy) - 90) * -1;
	}
	if(dy >= 0)
	{
		m_direction = (Util::Rad2Deg * atan(dx / dy) + 90) * -1;
	}
}


