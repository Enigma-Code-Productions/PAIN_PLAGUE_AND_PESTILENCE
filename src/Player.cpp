#include "Player.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Game.h"
#include "Util.h"

Player::Player(): m_speed(5), m_invTime(60), HEALING_TIME(66)
{
	
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Player-animation.txt",
		"../Assets/sprites/Player-animation.png",
		"Player");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("Player"));

	// set players collider
	setWidth(56);
	setHeight(80);

	//set players health
	setDamage(10);
	setMaxHealth(100);
	setHealth(getMaxHealth());
	setCollisionDamage(false);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);

	m_buildAnimations();
	setAnimationState(PLAYER_IDLE_RIGHT);
	m_bHealing = false;
	m_pHealingPotion = nullptr;
	m_pPlayerUI = new PlayerUI(this);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y - 8;


	// draw the player according to animation state

	int alpha = 255;
	if (m_invTimeLeft > 0)
	{
		alpha = 128;
	}

	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance().playAnimation("Player", getAnimation("idle"),
			x, y, 0.04f, 0, alpha, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance().playAnimation("Player", getAnimation("idle"),
			x, y, 0.04f, 0, alpha, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance().playAnimation("Player", getAnimation("run"),
			x, y, 0.50f, 0, alpha, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance().playAnimation("Player", getAnimation("run"),
			x, y, 0.50f, 0, alpha, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
	
	if (m_pWeapon != nullptr && !m_bHealing)
	{
		m_pWeapon->draw();
	}
	if (m_pHealingPotion != nullptr)
	{
		m_pHealingPotion->draw();
	}
	if (m_pPlayerUI != nullptr)
	{
		m_pPlayerUI->draw();
	}
	
}

void Player::update()
{

	//Player Movement
	bool running = false;
	bool facingRight = isFacingRight();

#pragma region inputHandling
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		this->getTransform()->position.y -= m_speed;
		running = true;
		
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		this->getTransform()->position.y += m_speed;
		running = true;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		this->getTransform()->position.x -= m_speed;
		facingRight = false;
		running = true;
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		this->getTransform()->position.x += m_speed;
		facingRight = true;
		running = true;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		if (!m_bHealing)
			getWeapon()->attack();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_H))
	{
		if (!getWeapon()->isAttacking())
			Heal();
	}

	if(running)
	{
		if (facingRight)
			setAnimationState(PLAYER_RUN_RIGHT);
		else
			setAnimationState(PLAYER_RUN_LEFT);
	}
	else
	{
		if (facingRight)
			setAnimationState(PLAYER_IDLE_RIGHT);
		else
			setAnimationState(PLAYER_IDLE_LEFT);
	}
#pragma endregion inputHandling

	if (m_pHealingPotion != nullptr)
	{
		if (m_healingTimeLeft == 0)
		{
			takeHeal(50);
			m_pPlayerUI->getHealthBar()->setHealth(getHealth());
			m_bHealing = false;
			delete m_pHealingPotion;
			m_pHealingPotion = nullptr;
		}
		else
		{
			m_pHealingPotion->update();
			m_healingTimeLeft--;
		}
	}
	if(m_pWeapon != nullptr )
	{
		m_pWeapon->update();
	}
	if (m_invTimeLeft > 0)
	{
		m_invTimeLeft--;
	}
}

void Player::clean()
{
	if (m_pWeapon != nullptr)
	{
		m_pWeapon->clean();
		delete m_pWeapon;
		m_pWeapon = nullptr;
	}
	if (m_pPlayerUI != nullptr)
	{
		m_pPlayerUI->clean();
		delete m_pPlayerUI;
		m_pPlayerUI = nullptr;
	}
	if (m_pHealingPotion != nullptr)
	{
		m_pHealingPotion->clean();
		delete m_pHealingPotion;
		m_pHealingPotion = nullptr;
	}
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::setWeapon(Weapon* w)
{
	m_pWeapon = w;
}

void Player::setInvTime(int t)
{
	m_invTime = t;
}

void Player::setInvTimeLeft(int t)
{
	m_invTimeLeft = t;
}

int Player::getInvTime()
{
	return m_invTime;
}

int Player::getInvTimeLeft()
{
	return m_invTimeLeft;
}


Weapon* Player::getWeapon()
{
	return m_pWeapon;
}

bool Player::isFacingRight()
{
	if (m_currentAnimationState == PLAYER_IDLE_RIGHT || m_currentAnimationState == PLAYER_RUN_RIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Player::getDamage()
{
	if (m_pWeapon != nullptr)
		return m_pWeapon->getDamage();

	return AliveObject::getDamage();
}

void Player::takeDamage(int damage)
{
	if (getInvTimeLeft() > 0)
		return;

	AliveObject::takeDamage(damage);
	m_invTimeLeft = getInvTime();
	m_pPlayerUI->getHealthBar()->setHealth(getHealth());
}



void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-idle-0"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-idle-1"));


	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-run-0"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-run-2"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-run-1"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-run-3"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-run-4"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-run-5"));

	setAnimation(runAnimation);
}

void Player::Heal()
{
	if (m_bHealing)
		return;

	m_pHealingPotion = new HealingPotion(this);
	m_bHealing = true;
	m_healingTimeLeft = HEALING_TIME;
}


