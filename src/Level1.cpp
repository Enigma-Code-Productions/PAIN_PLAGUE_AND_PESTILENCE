#include "Level1.h"

#include "Game.h"
#include "SoundManager.h"

void Level1::update()
{
	PlayScene::update();

	if (m_pPlayer->isAlive())
	{
		checkWin();
	}
}

void Level1::start()
{
	PlayScene::start();

	m_pGrid = new TileGrid("Level1Data.txt");

	//Boss Sprite
	m_bBossSpawned = false;

	m_pBoss = nullptr;
}

void Level1::checkWin()
{
	if (m_scoreCounter >= 10)
	{
		m_bBossActive = true;

		//Delete all enemies in scene
		if (!m_bBossSpawned)
		{
			SoundManager::Instance().stopMusic(0);
			SoundManager::Instance().unload("Level-Music", SOUND_MUSIC);

			SoundManager::Instance().playMusic("Boss-Music", -1, 0);
			SoundManager::Instance().setMusicVolume(3);

			for (auto enemy : m_pEnemies)
			{
				enemy->setAlive(false);
			}
			deleteDeadEnemies();

			int x = rand() % 800;
			int y = rand() % 600;
			m_pEnemies.push_back(new SpellCaster(m_pPlayer, glm::vec2(x, y)));
			addChild(m_pEnemies.back());
			m_pBoss = m_pEnemies.back();
			m_bBossSpawned = true;
		}

		//If the boss is in scene, check if it is dead
		if (m_bBossSpawned)
		{
			if (!m_pBoss->isAlive())
				m_bBossDead = true;

			if (m_bBossDead)
			{
				TheGame::Instance().changeSceneState(WIN_SCENE); //Change to win scene if boss dies
			}
		}
	}
	if (!m_bBossActive)
	{
		spawnEnemy();
	}
}

void Level1::spawnEnemy()
{
	//spawn skull every 1 seconds.
	const int enemySpawnInterval = 2 * 60;
	if (TheGame::Instance().getFrames() % enemySpawnInterval == 0)
	{
		int x = rand() % 800;
		int y = rand() % 600;
		m_pEnemies.push_back(new Skull(m_pPlayer, glm::vec2(x, y)));
		addChild(m_pEnemies.back());
	}
	//10 seconds
	const int ZombieSpawnInterval = 4 * 60;
	if (TheGame::Instance().getFrames() % ZombieSpawnInterval == 0)
	{
		int x = rand() % 800;
		int y = rand() % 600;
		m_pEnemies.push_back(new Zombie(m_pPlayer, glm::vec2(x, y)));
		addChild(m_pEnemies.back());
	}

}
