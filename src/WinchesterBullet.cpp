#include "WinchesterBullet.h"
#include "TextureManager.h"

WinchesterBullet::WinchesterBullet(float s, float d, glm::vec2 pos, BulletOwner o) : Bullet(s,d,pos,o)
{
	//Load Textures Here
	//setSpriteSheet
	//setWidth
	//setHeight

	setBulletSpeed(10);
	//setBulletDamage(?);
	m_buildAnimations();
}

void WinchesterBullet::m_buildAnimations()
{
	//Build Animation Here
}

