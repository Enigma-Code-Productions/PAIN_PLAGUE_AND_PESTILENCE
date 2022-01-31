#pragma once
#ifndef __SKULL__
#define __SKULL__

#include "AliveObject.h"

class Skull final : public AliveObject
{
public:
	Skull();
	~Skull();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_buildAnimations();
};


#endif /* defined (__Skull__) */