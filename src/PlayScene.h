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
protected: //Properties

	//Objects
	std::vector<AliveObject*> m_pEnemies;

	std::vector<Bullet*> m_pPlayersBullets;
	std::vector<Bullet*> m_pEnemiesBullets;

	Player* m_pPlayer;

	TileGrid* m_pGrid;

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
	void deleteDeadEnemies();

	virtual void checkWin() = 0;

	int getScore();

	void CleanObjects();

	Player* getPlayer();
	std::vector<AliveObject*>* getEnemies();

	void addBullet(Bullet* b);
	void removeBullet(Bullet* b);

	

private: //Functions
	// IMGUI Function
	void GUI_Function() const;

	friend void Player::update();

	void moveAllObjects(glm::vec2 dPos);
};

#endif /* defined (__PLAY_SCENE__) */