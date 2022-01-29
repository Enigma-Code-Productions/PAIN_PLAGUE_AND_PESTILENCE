#include "Player.h"
#include "TextureManager.h"
#include "EventManager.h"
Player::Player(): m_speed(5) //m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Player-animation.txt",
		"../Assets/sprites/Player-animation.png",
		"Player");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("Player"));

	// set frame width
	setWidth(56);

	// set frame height
	setHeight(70);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
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
	const auto y = getTransform()->position.y;


	// draw the player according to animation state
	
	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance().playAnimation("Player", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance().playAnimation("Player", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance().playAnimation("Player", getAnimation("run"),
			x, y, 0.50f, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance().playAnimation("Player", getAnimation("run"),
			x, y, 0.50f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
	
	
}

void Player::update()
{

	//Player Movement

	if (m_currentAnimationState == PLAYER_RUN_LEFT)
	{
		setAnimationState(PLAYER_IDLE_LEFT);
	}
	else if (m_currentAnimationState == PLAYER_RUN_RIGHT)
	{
		setAnimationState(PLAYER_IDLE_RIGHT);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		this->getTransform()->position.y -= m_speed;
		
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		this->getTransform()->position.y += m_speed;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		this->getTransform()->position.x -= m_speed;
		setAnimationState(PLAYER_RUN_LEFT);
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		this->getTransform()->position.x += m_speed;
		setAnimationState(PLAYER_RUN_RIGHT);
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

//
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
