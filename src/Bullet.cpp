#include "Bullet.h"
#include <iostream>

#include "PlayScene.h"
#include "TextureManager.h"

Bullet::Bullet(float speed, float initialDirection, glm::vec2 weaponPos, BulletOwner bullet_owner)
{
	setOwner(bullet_owner);
	if(bullet_owner == ENEMY_BULLET)
	{
		TextureManager::Instance().loadSpriteSheet(
			"../Assets/sprites/SpellCasterBullet-animation.txt",
			"../Assets/sprites/SpellCasterBullet-animation.png",
			"SpellCasterBullet");

		setSpriteSheet(TextureManager::Instance().getSpriteSheet("SpellCasterBullet"));
		setWidth(30);
		setHeight(30);
		m_buildAnimations();
	}

	m_bulletSpeed = speed;
	m_direction = initialDirection;

	m_bulletSpeed = 10;//why

	getTransform()->position = weaponPos;

}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	glm::vec4 yellow = { 255 - 247, 255 - 215, 255 - 126, 255 };
	if(getOwner() == ENEMY_BULLET)
	{
		//Util::DrawFilledRect(getTransform()->position, 10, 10, glm::vec4(1,0,0,1));
		TextureManager::Instance().playAnimation(this, "SpellCasterBullet-move", 0.4f, 0, 255);
		//std::cout << "Play Animation" << std::endl;
	}
	else
	{
		glm::vec4 yellow = { 255 - 247, 255 - 215, 255 - 126, 255 };
		Util::DrawFilledRect(getTransform()->position, 10, 10, yellow);
	}

}

void Bullet::update()
{
	m_move();
	if (getTransform()->position.x > 800 ||getTransform()->position.x < 0 ||getTransform()->position.y > 600 || getTransform()->position.y < 0)
	{
		dynamic_cast<PlayScene*>(getParent())->removeBullet(this);
	}
}

void Bullet::clean()
{
}

void Bullet::setBulletSpeed(float speed)
{
	m_bulletSpeed = speed;
}

float Bullet::getBulletSpeed()
{
	return m_bulletSpeed;
}

void Bullet::setOwner(BulletOwner o)
{
	m_owner = o;
}


BulletOwner Bullet::getOwner()
{
	return m_owner;
}

void Bullet::m_move()
{
	getTransform()->position += glm::vec2(cos(Util::Deg2Rad * m_direction), sin(Util::Deg2Rad * m_direction)) * m_bulletSpeed;
}

void Bullet::m_buildAnimations()
{
	Animation moveAnimation = Animation();

	moveAnimation.name = "SpellCasterBullet-move";
	
	moveAnimation.frames.push_back(getSpriteSheet()->getFrame("SpellCasterBullet-move-0"));
	moveAnimation.frames.push_back(getSpriteSheet()->getFrame("SpellCasterBullet-move-1"));
	moveAnimation.frames.push_back(getSpriteSheet()->getFrame("SpellCasterBullet-move-2"));

	setAnimation(moveAnimation);
}

