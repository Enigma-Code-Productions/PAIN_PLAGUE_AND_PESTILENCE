#include "Explosion1.h"

#include "Game.h"
#include "TextureManager.h"

Explosion1::Explosion1(glm::vec2 pos, glm::vec2 size)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Explosion1.txt",
		"../Assets/sprites/Explosion1.png",
		"Explosion1");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("Explosion1"));
	
	setWidth(size.x);
	setHeight(size.y);

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
			x, y, 0.75f, 0, 255, true, SDL_FLIP_NONE, (getWidth() / getAnimation("Explosion1").frames[0].w));
	}
	else
	{
		Game::Instance().getSceneState()->removeChild(this);
	}
};
void Explosion1::update()
{
	
}

void Explosion1::dealDamage()
{
	
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