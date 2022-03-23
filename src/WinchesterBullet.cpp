#include "WinchesterBullet.h"
#include "TextureManager.h"

WinchesterBullet::WinchesterBullet(float damage, float s, float d, glm::vec2 pos, BulletOwner o) : Bullet(damage, s,d,pos,o)
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

void WinchesterBullet::draw()
{
	glm::vec4 yellow = { 255 - 247, 255 - 215, 255 - 126, 255 };
	Util::DrawFilledRect(getTransform()->position, 10, 10, yellow);
}

