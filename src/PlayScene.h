#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"
#include "Skull.h"
#include "Label.h"
#include "SoyKnife.h"
#include "Bullet.h"
#include "WinchesterShotgun.h"

class PlayScene : public Scene
{
private: //Properties
	// IMGUI Function
	std::string m_guiTitle;

	//Objects
	std::vector<AliveObject*> m_pEnemies;
	Player* m_pPlayer;
	Skull* m_pSkull;
	Label* m_pScore;

	WinchesterShotgun* m_pShotgun;
	std::vector<Bullet*> m_pShotgunBullets;

	//Score
	int m_scoreCounter;

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
	void spawnEnemy();
	void deleteDeadEnemies();

private: //Functions
	// IMGUI Function
	void GUI_Function() const;
	
};

#endif /* defined (__PLAY_SCENE__) */