#pragma once
#ifndef __IMAGE__
#define __IMAGE__
#include "DisplayObject.h"

class Image : public DisplayObject
{
private:


public:
	Image();
	~Image();

	void update() override;
	void draw() override;
	void clean() override;

private:

};
#endif #pragma once
