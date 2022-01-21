#pragma once
#ifndef __SKULL__
#define __SKULL__

#include "DisplayObject.h"

class Skull final : public DisplayObject {
public:
	Skull();
	~Skull();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

};


#endif /* defined (__Skull__) */