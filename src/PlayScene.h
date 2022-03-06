#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"
#include "Skull.h"
#include "Zombie.h"
#include "SpellCaster.h"
#include "Label.h"
#include "SoyKnife.h"

class PlayScene : public Scene
{
private: //Properties
	// IMGUI Function
	std::string m_guiTitle;

	//Objects
	std::vector<AliveObject*> m_pEnemies;
	Player* m_pPlayer;
	Skull* m_pSkull;
	Zombie* m_pZombie;
	Label* m_pScore;

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

	void CleanEnemies();

private: //Functions
	// IMGUI Function
	void GUI_Function() const;
	
};

#endif /* defined (__PLAY_SCENE__) */