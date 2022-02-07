#include "WinScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

WinScene::WinScene()
{
	WinScene::start();
}

WinScene::~WinScene()
= default;

void WinScene::draw()
{
	drawDisplayList();
}

void WinScene::update()
{
	updateDisplayList();
}

void WinScene::clean()
{
	removeAllChildren();

	SoundManager::Instance().stopMusic(0);
	SoundManager::Instance().unload("../Assets/audio/Surreal-Game-Menu_Looping.mp3", SOUND_MUSIC);
}

void WinScene::handleEvents()
{
	EventManager::Instance().update();

	// Button Events
	m_pRestartButton->update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(PLAY_SCENE);
	}
}

void WinScene::start()
{
	const SDL_Color red = { 128, 0, 0, 255 };

	SoundManager::Instance().load("../Assets/audio/Surreal-Game-Menu_Looping.mp3", "EndLevel-Music", SOUND_MUSIC);
	SoundManager::Instance().playMusic("EndLevel-Music", -1, 0);
	SoundManager::Instance().setMusicVolume(2);


	m_label = new Label("Congrats You Made It Now Find The Cure", "YouMurderer", 60, red, glm::vec2(400.0f, 300.0f));
	m_label->setParent(this);
	addChild(m_label);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2(400.0f, 400.0f);
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
		{
			m_pRestartButton->setActive(false);
			TheGame::Instance().changeSceneState(PLAY_SCENE);
		});

	m_pRestartButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pRestartButton->setAlpha(128);
		});

	m_pRestartButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pRestartButton->setAlpha(255);
		});

	addChild(m_pRestartButton);

	ImGuiWindowFrame::Instance().setDefaultGUIFunction();
}
