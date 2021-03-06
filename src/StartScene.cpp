#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	TextureManager::Instance().draw("Background", 0, 0);
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();

	SoundManager::Instance().stopMusic(0);
	SoundManager::Instance().unload("../Assets/audio/Horror-Game-Intro.mp3", SOUND_MUSIC);
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_EQUALS))
	{
		TheGame::Instance().changeSceneState(LEVEL_1);
	}
}

void StartScene::start()
{
	const SDL_Color red = { 128, 0, 0, 255 };
	const SDL_Color white = { 255,255,255,255 };

	SoundManager::Instance().load("../Assets/audio/Horror-Game-Intro.mp3", "StartLevel-Music", SOUND_MUSIC);
	SoundManager::Instance().playMusic("StartLevel-Music", -1, 0);
	SoundManager::Instance().setMusicVolume(2);

	TextureManager::Instance().load("../Assets/textures/Full-tile.png", "Background");

	m_pStartLabel = new Label("Pain Plague And Pestilence", "YouMurderer", 90, white, glm::vec2(400.0f, 120.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);


	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance().changeSceneState(LEVEL_1);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	ImGuiWindowFrame::Instance().setDefaultGUIFunction();
}

