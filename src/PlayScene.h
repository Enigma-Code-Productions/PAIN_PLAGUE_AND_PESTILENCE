#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"
#include "Skull.h"
#include "Button.h"
#include "Label.h"
#include "SoyKnife.h"

class PlayScene : public Scene
{
private: //Properties
	// IMGUI Function
	std::string m_guiTitle;

	//Objects
	Player* m_pPlayer;
	Skull* m_pSkull;

public: // Functions
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void collisionCheck();

private: //Functions
	// IMGUI Function
	void GUI_Function() const;
	
};

#endif /* defined (__PLAY_SCENE__) */