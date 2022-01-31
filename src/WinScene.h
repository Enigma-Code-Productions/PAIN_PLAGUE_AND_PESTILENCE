#pragma once



#include "Scene.h"
#include "Label.h"
#include "Button.h"

class WinScene final : public Scene
{
public:
	 WinScene();
	~WinScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Label* m_label{};

	Button* m_pRestartButton;
};

