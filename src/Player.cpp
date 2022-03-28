#include "Player.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Game.h"
#include "Util.h"

Player::Player(): m_speed(5), m_invTime(60), HEALING_TIME(66), m_healingTimeLeft(0),
	m_healsLeft(3), m_bHealing(false), m_pHealingPotion(nullptr)

{
	
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Player-spritesheet.txt",
		"../Assets/sprites/Player-spritesheet.png",
		"Player");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("Player"));

	// Player sounds
	SoundManager::Instance().load("../Assets/audio/Hit.wav", "Hit", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Heal.wav", "Heal", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Portal.mp3", "Portal", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Walking.mp3", "Walking", SOUND_SFX);

	// set players collider
	setWidth(90);
	setHeight(96);

	//set players health
	setDamage(10);
	setMaxHealth(100);
	setHealth(getMaxHealth());
	setCollisionDamage(false);

	//this needs to be here until weapons can be picked up from an external source like a chest
	m_pKnife = new SoyKnife(this);
	m_pShotgun = new WinchesterShotgun(this);

	getParent()->addChild(m_pKnife, FRONT_OBJECTS);
	getParent()->addChild(m_pShotgun, FRONT_OBJECTS);
	m_pShotgun->setEnabled(false);
	setWeapon(m_pKnife);
	//-----------------------------------------------------------------------------------------

	m_thrower = new PotionThrower(this);
	getParent()->addChild(m_thrower);
	m_pPlayerUI = new PlayerUI(this);
	getParent()->addChild(m_pPlayerUI, UI);
	
	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	getRigidBody()->hasCollider = true;
	setType(PLAYER);

	m_buildAnimations();
	setAnimationState(PLAYER_IDLE_RIGHT);
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
	if (m_invTimeLeft > 0 && isAlive())
	{
		alpha = 128;
	}

	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance().playAnimation(this, "idle", 0.04f, 0, alpha);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance().playAnimation(this, "idle", 0.04f, 0, alpha, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance().playAnimation(this, "run", 0.5f, 0, alpha);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance().playAnimation(this, "run", 0.5f, 0, alpha, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_DEATH_RIGHT:
		TextureManager::Instance().playAnimation(this, "death", 0.5f, 0, alpha);
		break;
	case PLAYER_DEATH_LEFT:
		TextureManager::Instance().playAnimation(this, "death", 0.5f, 0, alpha, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
}

void Player::Death()
{
	if (m_pWeapon != nullptr)
	{
		getParent()->removeChildAfterUpdate(m_pWeapon);
		m_pWeapon = nullptr;

		SoundManager::Instance().playSound("Portal", 0, -1);
	}
	if (m_pHealingPotion != nullptr)
	{
		getParent()->removeChildAfterUpdate(m_pHealingPotion);
		m_pHealingPotion = nullptr;
	}
	setCanMove(false);
	if (isFacingRight())
	{
		setAnimationState(PLAYER_DEATH_RIGHT);
	}
	else
	{
		setAnimationState(PLAYER_DEATH_LEFT);
	}


	if (getAnimation("death").current_frame == 9) //When death animation is done, end game
	{
		setAlive(false);
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}


void Player::update()
{

	//Player Movement
	bool running = false;
	bool facingRight = isFacingRight();

#pragma region inputHandling

	if(m_bCanMove)
	{
		glm::vec2 d_pos = glm::vec2(0.0f, 0.0f);

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{

			if (CollisionManager::canMoveWithoutCollison(this, glm::vec2(getTransform()->position.x, getTransform()->position.y - m_speed)))
				d_pos.y += m_speed;
			running = true;
		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			if (CollisionManager::canMoveWithoutCollison(this, glm::vec2(getTransform()->position.x, getTransform()->position.y + m_speed)))
				d_pos.y -= m_speed;
			running = true;
		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			if (CollisionManager::canMoveWithoutCollison(this, glm::vec2(getTransform()->position.x - m_speed, getTransform()->position.y)))
				d_pos.x += m_speed;
			facingRight = false;
			running = true;
		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			if (CollisionManager::canMoveWithoutCollison(this, glm::vec2(getTransform()->position.x + m_speed, getTransform()->position.y)))
				d_pos.x -= m_speed;
			
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

		//swap weapons
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
		{
			if (getWeapon()->getType() == RANGED_WEAPON)
			{
				if (!getWeapon()->isAttacking())
				{
					m_pKnife->setEnabled(true);
					m_pShotgun->setEnabled(false);

					setWeapon(m_pKnife);
					getWeapon()->getTransform()->position = getTransform()->position + glm::vec2(0, 25);
				}
			}
		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
		{
			if (getWeapon()->getType() == MELEE_WEAPON)
			{
				if (!getWeapon()->isAttacking())
				{
					m_pKnife->setEnabled(false);
					m_pShotgun->setEnabled(true);
					setWeapon(m_pShotgun);
					getWeapon()->getTransform()->position = getTransform()->position + glm::vec2(0, 25);
				}
			}
		}

		if (running)
		{
			// walk sound
			//SoundManager::Instance().playSound("Walking", 0, 1);
			//SoundManager::Instance().setSoundVolume(10);

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

		if (d_pos.x != 0.0f || d_pos.y != 0.0f)
		{
			dynamic_cast<PlayScene*>(getParent())->moveAllObjects(d_pos);
		}


		if (m_pHealingPotion != nullptr)
		{
			if (m_healingTimeLeft == 0)
			{
				takeHeal(50);
				m_healsLeft--;
				m_pPlayerUI->getHealthBar()->setHealth(getHealth());
				m_pPlayerUI->setHeals();
				m_bHealing = false;
				getParent()->removeChildAfterUpdate(m_pHealingPotion);
				m_pHealingPotion = nullptr;
				m_pWeapon->setEnabled(true);
			}
			else
			{
				m_healingTimeLeft--;
			}
		}
		if (m_invTimeLeft > 0)
		{
			m_invTimeLeft--;
		}
	}
	if (m_invTimeLeft > 0)
	{
		m_invTimeLeft--;
	}

	if(!isAlive())
	{
		Death();
	}
}



void Player::clean()
{
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

void Player::setHealsLeft(int c)
{
	m_healsLeft = c;
}

void Player::setCanMove(bool m)
{
	m_bCanMove = m;
}


bool Player::getCanMove()
{
	return m_bCanMove;
}


int Player::getHealsLeft()
{
	return m_healsLeft;
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

PotionThrower* Player::getThrower()
{
	return m_thrower;
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

	SoundManager::Instance().playSound("Hit", 0, -1);
	SoundManager::Instance().setSoundVolume(6);

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

	Animation deathAnimation = Animation();

	deathAnimation.name = "death";
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-death-0"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-death-1"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-death-2"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-death-3"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-death-4"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-death-5"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-death-6"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-death-7"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-death-8"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("Player-death-9"));

	setAnimation(deathAnimation);
}

void Player::Heal()
{
	if (m_bHealing)
		return;
	if (m_healsLeft == 0)
		return;

	// sound effect for healing
	SoundManager::Instance().playSound("Heal", 0, 0);
	SoundManager::Instance().setSoundVolume(6);

	m_pWeapon->setEnabled(false);
	m_pHealingPotion = new HealingPotion(this);
	getParent()->addChildAfterUpdate(m_pHealingPotion);
	m_bHealing = true;
	m_healingTimeLeft = HEALING_TIME;
}


