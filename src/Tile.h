#pragma once
#ifndef __TILE__
#define __TILE__
#include <SDL_rect.h>

#include "DisplayObject.h"


class Tile : public DisplayObject
{
private:
	int m_width;
	int m_height;

	SDL_Rect m_src;

	std::string m_srcKey;

public:
	Tile(SDL_Rect src, std::string key, bool is_collider);
	~Tile();

	Tile* Clone();

	void update() override;
	void draw() override;
	void clean() override;

private:

};
#endif 