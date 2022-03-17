#include "Tile.h"

#include "Game.h"
#include "TextureManager.h"

Tile::Tile(SDL_Rect src, std::string key, bool is_collider) : m_src(src), m_srcKey(key)
{
	setWidth(m_src.w);
	setHeight(m_src.h);

	getRigidBody()->hasCollider = is_collider;
}

Tile::~Tile()
= default;

Tile* Tile::Clone()
{
	return new Tile(m_src, m_srcKey, getRigidBody()->hasCollider);
}

void Tile::update()
{
}

void Tile::draw()
{
	SDL_FRect dst = { getTransform()->position.x - (getWidth() / 2.0f), getTransform()->position.y - (getHeight() / 2.0f), (float)getWidth(), (float)getHeight() };
//	std::cout << dst.x << " " << dst.y << std::endl;
	SDL_RenderCopyF(Renderer::Instance().getRenderer(), TextureManager::Instance().getTexture(m_srcKey), &m_src, &dst);
}

void Tile::clean()
{
}
