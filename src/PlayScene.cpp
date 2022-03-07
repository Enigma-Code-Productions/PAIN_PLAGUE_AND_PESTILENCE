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

	//temporary---------------------------------------------------
	for (unsigned i = 0; i < m_pShotgun->getBullets().size(); i++)
	{
		m_pShotgun->getBullets()[i]->draw();
	}
	//------------------------------------------------------------

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	//temporary---------------------------------------------------
	for (unsigned i = 0; i < m_pShotgun->getBullets().size(); i++)
	{
		m_pShotgun->getBullets()[i]->update();
	}
	//------------------------------------------------------------

	// Clean up bullets that go off screen.
	for (unsigned i = 0; i < m_pShotgun->getBullets().size(); i++)
	{
		if (m_pShotgun->getBullets()[i]->getTransform()->position.x > 800 || m_pShotgun->getBullets()[i]->getTransform()->position.x < 0 || m_pShotgun->getBullets()[i]->getTransform()->position.y > 600 || m_pShotgun->getBullets()[i]->getTransform()->position.y < 0)
		{
			
			//delete m_pShotgun->getBullets()[i];
			//m_pShotgun->getBullets()[i] = nullptr;
			//m_pShotgun->getBullets().erase(m_pShotgun->getBullets().begin() + i);
			//m_pShotgun->getBullets().shrink_to_fit();
		}
	}

	collisionCheck();
	deleteDeadEnemies();
	m_pScore->setText(std::to_string(m_scoreCounter) + " Pts");

	if (!m_pPlayer->isAlive())
	{
		TheGame::Instance().changeSceneState(END_SCENE);TheGame::Instance().changeSceneState(END_SCENE);
	}

	if (m_scoreCounter >= 10)
	{
		TheGame::Instance().changeSceneState(WIN_SCENE); TheGame::Instance().changeSceneState(WIN_SCENE);
		
	}
	//spawnEnemy();
}


void PlayScene::clean()
{
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

	//m_pPlayer->setWeapon(new SoyKnife(m_pPlayer));

	m_pShotgun = new WinchesterShotgun(m_pPlayer);
	m_pPlayer->setWeapon(m_pShotgun);
	//m_pBullets


	//m_pEnemies.push_back(new Skull(m_pPlayer));
	//addChild(m_pEnemies[0]);


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
			else if (m_pPlayer->getWeapon()->getType() == RANGED_WEAPON)
			{
				for (unsigned i = 0; i < m_pEnemies.size(); i++)
				{
					for (unsigned j = 0; j < m_pShotgun->getBullets().size(); j++)
					{
						if (CollisionManager::AABBCheck(m_pShotgun->getBullets()[j], m_pEnemies[i]))
						{
							m_pEnemies[i]->takeDamage(m_pShotgun->getDamage());

							//delete bullet
							delete m_pShotgun->getBullets()[j];
							m_pShotgun->getBullets()[j] = nullptr;
							m_pShotgun->getBullets().erase(m_pShotgun->getBullets().begin() + j);
							m_pShotgun->getBullets().shrink_to_fit();
						}
					}
				}
			}
		}
	}
	
}

void PlayScene::spawnEnemy()
{
	//spawn skull every 5 seconds.
	const int enemySpawnInterval = 5 * 60;
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

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
	}
	
	ImGui::End();
}
