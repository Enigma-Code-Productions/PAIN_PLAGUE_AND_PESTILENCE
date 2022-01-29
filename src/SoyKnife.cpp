#include "SoyKnife.h"
#include "TextureManager.h"
#include"EventManager.h"

SoyKnife::SoyKnife(Player* player)
{
	//TextureManager::Instance().load("../Assets/textures/Soy-Knife-Anim/Soy-knife-1.png", "SoyKnife1");
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Soy-Knife-Animation.txt",
		"../Assets/sprites/Soy-Knife-Animation.png",
		"SoyKnife");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("SoyKnife"));

	//const auto size = TextureManager::Instance().getTextureSize("SoyKinfe1");
	//setWidth(size.x);
	//setHeight(size.y);
	setWidth(48);
	setHeight(72);
	setOwner(player);
	getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(45, 20));
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;


	setType(WEAPON);

	m_buildAnimations();
}

SoyKnife::SoyKnife()
{
}

SoyKnife::~SoyKnife() = default;

void SoyKnife::draw()
{
	/*const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance().draw("SoyKnife1", x, y, 0, 255, true);*/

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case SOY_KNIFE_IDLE_RIGHT:
		TextureManager::Instance().playAnimation("SoyKnife", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case SOY_KNIFE_IDLE_LEFT:
		TextureManager::Instance().playAnimation("SoyKnife", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case SOY_KNIFE_ATTACK_RIGHT:
		TextureManager::Instance().playAnimation("SoyKnife", getAnimation("attack"),
			x, y, 0.75f, 0, 255, true);
		break;
	case SOY_KNIFE_ATTACK_LEFT:
		TextureManager::Instance().playAnimation("SoyKnife", getAnimation("attack"),
			x, y, 0.75f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
}

void SoyKnife::update()
{
	m_move();
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		setAnimationState(SOY_KNIFE_ATTACK_RIGHT);
	}
	else
	{
		setAnimationState(SOY_KNIFE_IDLE_RIGHT);
	}

}

void SoyKnife::clean()
{
}

void SoyKnife::setAnimationState(SoyKnifeAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void SoyKnife::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-idle"));
	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "attack";
	
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-0"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-1"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-2"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-3"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-4"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-5"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("SoyKnife-attack-6"));

	setAnimation(runAnimation);
}

void SoyKnife::m_move()
{
	getTransform()->position = glm::vec2(getOwner()->getTransform()->position + glm::vec2(45, 20));
}


void SoyKnife::m_attack()
{
}
