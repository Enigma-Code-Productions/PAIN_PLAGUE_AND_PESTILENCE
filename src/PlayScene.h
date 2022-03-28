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
private: // Properties
	std::vector<GameObject*> m_pCollidableObjects;
	float m_drag;
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

	// Makes this class abstract
	virtual void checkWin() = 0;

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void virtual  addChild(DisplayObject* child, DrawLayers layer_index = BACKGROUND, std::optional<uint32_t> order_index = std::nullopt) override;
	void virtual addChildAfterUpdate(DisplayObject* child, DrawLayers layer_index = BACKGROUND, std::optional<uint32_t> order_index = std::nullopt) override;
	void virtual removeChild(DisplayObject* child) override;
	void virtual removeChildAfterUpdate(DisplayObject* child) override;

	std::vector<GameObject*> getCollidables();

	void collisionCheck();
	void deleteDeadEnemies();

	int getScore();

	void CleanObjects();

	Player* getPlayer();
	std::vector<AliveObject*>* getEnemies();

	void addBullet(Bullet* b);
	void removeBullet(Bullet* b);

	float getDrag() const;
	void setDrag(float drag);
	
private: //Functions
	friend class Player;
	void moveAllObjects(glm::vec2 dPos);

	// IMGUI Function
	void GUI_Function() const;
};

#endif /* defined (__PLAY_SCENE__) */