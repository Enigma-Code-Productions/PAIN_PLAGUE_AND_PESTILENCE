#include "SpellCasterBullet.h"

#include "TextureManager.h"

SpellCasterBullet::SpellCasterBullet(float s, float d, glm::vec2 pos, BulletOwner o) : Bullet(s,d,pos,o)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/SpellCasterBullet-animation.txt",
		"../Assets/sprites/SpellCasterBullet-animation.png",
		"SpellCasterBullet");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("SpellCasterBullet"));

	setWidth(30);
	setHeight(30);

	setBulletSpeed(5);
	setBulletDamage(25);

	m_buildAnimations();
}

void SpellCasterBullet::draw()
{
	TextureManager::Instance().playAnimation(this, "SpellCasterBullet-move", 0.4f, 0, 255);
}


void SpellCasterBullet::m_buildAnimations()
{
	Animation moveAnimation = Animation();

	moveAnimation.name = "SpellCasterBullet-move";

	moveAnimation.frames.push_back(getSpriteSheet()->getFrame("SpellCasterBullet-move-0"));
	moveAnimation.frames.push_back(getSpriteSheet()->getFrame("SpellCasterBullet-move-1"));
	moveAnimation.frames.push_back(getSpriteSheet()->getFrame("SpellCasterBullet-move-2"));

	setAnimation(moveAnimation);
}

