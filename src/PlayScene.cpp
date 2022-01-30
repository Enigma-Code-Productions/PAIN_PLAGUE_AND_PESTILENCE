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
	drawDisplayList();

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	collisionCheck();
	if (!m_pPlayer->isAlive())
	{
		TheGame::Instance().changeSceneState(END_SCENE);TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::clean()
{
	removeAllChildren();
	SoundManager::Instance().stopMusic(0);
	SoundManager::Instance().unload("../Assets/audio/Aftermath.mp3", SOUND_MUSIC);
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

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);

	m_pPlayer->setWeapon(new SoyKnife(m_pPlayer));
	addChild(m_pPlayer->getWeapon());

	m_pSkull = new Skull(m_pPlayer, 300);
	addChild(m_pSkull);
	m_pEnemies.push_back(m_pSkull);


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
				std::cout << m_pPlayer->getHealth() << std::endl;
			}
			// Can be added stuff if player has collision damage
		}
		if (m_pPlayer->getWeapon()->hasCollisionDamage())
		{
			if (CollisionManager::AABBCheck(enemy, m_pPlayer->getWeapon()))
			{
				enemy->takeDamage(m_pPlayer->getDamage());
				std::cout << enemy->getHealth() << std::endl;
			}
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
