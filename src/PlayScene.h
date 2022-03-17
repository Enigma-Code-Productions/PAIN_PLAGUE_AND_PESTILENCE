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
#include "Bullet.h"
#include "TileGrid.h"
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
	Zombie* m_pZombie;

	SoyKnife* m_pKnife;
	WinchesterShotgun* m_pShotgun;
	std::vector<Bullet*> m_pPlayersBullets;
	std::vector<Bullet*> m_pEnemiesBullets;

	TileGrid* m_pGrid;

	//Score
	int m_scoreCounter;

	//Boss Battle
	bool m_bBossActive = false;
	bool m_bBossSpawned;
	bool m_bBossDead;
	AliveObject* m_pBoss;

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

	void checkWin();
	void CleanEnemies();

	int getScore();

	void CleanObjects();

	Player* getPlayer();
	std::vector<AliveObject*>* getEnemies();

	void addBullet(Bullet* b);
	void removeBullet(Bullet* b);

private: //Functions
	// IMGUI Function
	void GUI_Function() const;
	
};

#endif /* defined (__PLAY_SCENE__) */