#pragma once
#ifndef __LEVEL_1__
#define __LEVEL_1__
#include "PlayScene.h"


class Level1 final : public PlayScene
{
private:
	//Boss Battle
	bool m_bBossActive = false;
	bool m_bBossSpawned;
	bool m_bBossDead;
	AliveObject* m_pBoss;

public:

	void update() override;
	void start() override;

	void checkWin() override;

	void spawnEnemy();

private:

};
#endif 