#include "Poison1.h"

#include "Game.h"
#include "TextureManager.h"
#include "Util.h"

Poison1::Poison1(glm::vec2 pos) : m_damageDone(false)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Poison1.txt",
		"../Assets/sprites/Poison1.png",
		"Poison1");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("Poison1"));
	
	setWidth(64);
	setHeight(64);

	getTransform()->position = pos;
	m_buildAnimations();
}

Poison1::~Poison1()
= default;

void Poison1::clean()
{
	
}

void Poison1::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	if (getAnimation("Poison1").current_frame != getAnimation("Poison1").frames.size() - 1)
	{
		TextureManager::Instance().playAnimation(this, "Poison1", 0.75, 0, 255);
	}
	else
	{
		Game::Instance().getCurrentScene()->removeChildAfterUpdate(this);
	}
};
void Poison1::update()
{
	if (getAnimation("Poison1").current_frame == 3 && !m_damageDone)
	{
		dealDamage();
		m_damageDone = true;
	}
}

void Poison1::dealDamage()
{
	SDL_FRect collider({ getTransform()->position.x - (getWidth() / 5), getTransform()->position.y - (getHeight() / 5), (float)getWidth(), (float)getHeight()});

	auto pPlayer = dynamic_cast<PlayScene*>(TheGame::Instance().getCurrentScene())->getPlayer();

	auto pEnemies = dynamic_cast<PlayScene*>(TheGame::Instance().getCurrentScene())->getEnemies();

	if (CollisionManager::circleAABBCheck(this, pPlayer))
	{
		pPlayer->takeDamage(90);
		pPlayer->getRigidBody()->isColliding = false;
	}
	for (auto enemy : *(pEnemies))
	{
		if (CollisionManager::circleAABBCheck(this, enemy))
		{
			enemy->takeDamage(90);
		}
	}
}


void Poison1::m_buildAnimations()
{
	Animation Poison1 = Animation();

	Poison1.name = "Poison1";
	Poison1.frames.push_back(getSpriteSheet()->getFrame("Poison1-0"));
	Poison1.frames.push_back(getSpriteSheet()->getFrame("Poison1-1"));
	Poison1.frames.push_back(getSpriteSheet()->getFrame("Poison1-2"));
	Poison1.frames.push_back(getSpriteSheet()->getFrame("Poison1-3"));
	Poison1.frames.push_back(getSpriteSheet()->getFrame("Poison1-4"));
	Poison1.frames.push_back(getSpriteSheet()->getFrame("Poison1-5"));
	setAnimation(Poison1);
}