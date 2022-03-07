#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance().draw("Background", 0, 0);
	drawDisplayList();

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	collisionCheck();
	deleteDeadEnemies();
	if (m_pScore!= nullptr)
	{
		m_pScore->setText(std::to_string(m_scoreCounter) + " Pts");

		if (m_scoreCounter >= 10)
		{
			TheGame::Instance().changeSceneState(WIN_SCENE);

		}
		//spawnEnemy();
	}
	
}


void PlayScene::clean()
{
	CleanObjects();
	removeAllChildren();
	SoundManager::Instance().stopMusic(0);
	SoundManager::Instance().unload("Level-Music", SOUND_MUSIC);
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";


	// Background
	TextureManager::Instance().load("../Assets/textures/Full-tile.png", "Background");


	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_pPlayer->setCanMove(true);

	m_pPlayer->setWeapon(new SoyKnife(m_pPlayer));

	//Ui
	m_scoreCounter = 0;
	const SDL_Color black = { 0, 0, 0, 255 };
	m_pScore = new Label( std::to_string(m_scoreCounter) + " Pts", "Toxia-OwOA", 60, black, glm::vec2(700.0f, 30.0f)); //800X600 window size
	addChild(m_pScore);
	m_pScore->setParent(this);

	SoundManager::Instance().load("../Assets/audio/Aftermath.mp3", "Level-Music", SOUND_MUSIC);
	SoundManager::Instance().playMusic("Level-Music", -1, 0);
	SoundManager::Instance().setMusicVolume(3);


	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::collisionCheck()
{
	for(auto enemy: m_pEnemies)
	{
		if (CollisionManager::AABBCheck(enemy, m_pPlayer))
		{
			if (enemy->hasCollisionDamage())
			{
				m_pPlayer->takeDamage(enemy->getDamage());
			}
			// Can be added stuff if player has collision damage
		}
		if (m_pPlayer->getWeapon() != nullptr)
		{
			if (m_pPlayer->getWeapon()->getType() == MELEE_WEAPON)
			{
				if (m_pPlayer->getWeapon()->hasCollisionDamage())
				{
					if (CollisionManager::AABBCheck(enemy, m_pPlayer->getWeapon()))
					{
						
						if (enemy->getLastHitFrame() < m_pPlayer->getWeapon()->getAttackStart())
						{
							enemy->takeDamage(m_pPlayer->getDamage());
						}
					}
				}
			}
		}
	}
	
}

void PlayScene::spawnEnemy()
{
	//spawn skull every 1 seconds.
	const int enemySpawnInterval = 1 * 60;
	if (TheGame::Instance().getFrames() % enemySpawnInterval == 0)
	{
		int x = rand() % 800;
		int y = rand() % 600;
		m_pEnemies.push_back(new Skull(m_pPlayer, glm::vec2(x, y)));
		addChild(m_pEnemies.back());
	}
}

void PlayScene::deleteDeadEnemies()
{
	for (int i = 0; i < m_pEnemies.size(); i++)
	{
		if (!m_pEnemies[i]->isAlive())
		{
			m_scoreCounter++;
			removeChild(m_pEnemies[i]);
			m_pEnemies[i] = nullptr;
			m_pEnemies.erase(m_pEnemies.begin() + i);
			i--;
		}
	}
}

void PlayScene::CleanObjects()
{
	for (auto& count : m_pEnemies)
	{
		count = nullptr;
	}

	m_pEnemies.clear();
	m_pScore = nullptr;
}

Player* PlayScene::getPlayer()
{
	return m_pPlayer;
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Debug", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	if(ImGui::Button("Kill Player"))
	{
		std::cout << "Player Killed" << std::endl;
		m_pPlayer->takeDamage(1000);
	}

	ImGui::Separator();
	
	ImGui::End();
}
