#pragma once
#pragma once

#include "Scene.h"
#include "Label.h"
#include "Button.h"
class PauseScene final : public Scene
{
public:
	PauseScene();
	~PauseScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Button* m_pResumeButton{};
	Button* m_pExitButton{};
	Label* m_pauseLabel{};
	Label* m_instructionLabel{};

	bool m_resume;
	bool m_exit;
};

