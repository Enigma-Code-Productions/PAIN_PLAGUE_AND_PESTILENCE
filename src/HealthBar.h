#pragma once
#ifndef __HEALTH_BAR__
#define __HEALTH_BAR__
#include "DisplayObject.h"

class HealthBar final : public DisplayObject
{
private: //Properties
	int m_maxHealth;
	int m_health;

public: // Functions
	HealthBar();
	HealthBar(int max_health);
	~HealthBar();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setMaxHealth(int mh);
	void setHealth(int h);

private: // Functions

};

#endif /* defined (__HEALTH_BAR__) */