#pragma once
#ifndef __TEMPLATE_OBJECT__
#define __TEMPLATE_OBJECT__

#include "DisplayObject.h"

class TemplateObject final : public DisplayObject
{
public:
	TemplateObject();
	 ~TemplateObject();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_move();
	void m_checkBounds();
	void m_reset();
};


#endif /* defined (__TEMPLATE_OBJECT__) */