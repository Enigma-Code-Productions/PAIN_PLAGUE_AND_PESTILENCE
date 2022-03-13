#include "Explosion1.h"

#include "Game.h"
#include "TextureManager.h"
#include "Util.h"

Explosion1::Explosion1(glm::vec2 pos) : m_damageDone(false)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Explosion1.txt",
		"../Assets/sprites/Explosion1.png",
		"Explosion1");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("Explosion1"));
	
	setWidth(96);
	setHeight(96);



	getTransform()->position = pos;
	m_buildAnimations();
}

Explosion1::~Explosion1()
= default;

void Explosion1::clean()
{
	
}
void Explosion1::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	if (getAnimation("Explosion1").current_frame != getAnimation("Explosion1").frames.size() - 1)
	{
		TextureManager::Instance().playAnimation("Explosion1", getAnimation("Explosion1"),
			x, y, 0.75f, 0, 255, true);

	}
	else
	{
		Game::Instance().getCurrentScene()->removeChild(this);
	}
};
void Explosion1::update()
{
	if (getAnimation("Explosion1").current_frame == 3 && !m_damageDone)
	{
		dealDamage();
		m_damageDone = true;
	}
}

void Explosion1::dealDamage()
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


void Explosion1::m_buildAnimations()
{
	Animation Explosion1 = Animation();

	Explosion1.name = "Explosion1";
	Explosion1.frames.push_back(getSpriteSheet()->getFrame("Explosion1-0"));
	Explosion1.frames.push_back(getSpriteSheet()->getFrame("Explosion1-1"));
	Explosion1.frames.push_back(getSpriteSheet()->getFrame("Explosion1-2"));
	Explosion1.frames.push_back(getSpriteSheet()->getFrame("Explosion1-3"));
	Explosion1.frames.push_back(getSpriteSheet()->getFrame("Explosion1-4"));
	Explosion1.frames.push_back(getSpriteSheet()->getFrame("Explosion1-5"));
	Explosion1.frames.push_back(getSpriteSheet()->getFrame("Explosion1-6"));
	Explosion1.frames.push_back(getSpriteSheet()->getFrame("Explosion1-7"));
	Explosion1.frames.push_back(getSpriteSheet()->getFrame("Explosion1-8"));
	Explosion1.frames.push_back(getSpriteSheet()->getFrame("Explosion1-9"));
	setAnimation(Explosion1);
}