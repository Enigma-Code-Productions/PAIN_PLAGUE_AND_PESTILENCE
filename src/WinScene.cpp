#include "WinScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

WinScene::WinScene()
{

}

WinScene::~WinScene()
= default;

void WinScene::draw()
{
	TextureManager::Instance().draw("Background", 0, 0);
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

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_MINUS))
	{
		TheGame::Instance().changeSceneState(LEVEL_1);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_EQUALS))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void WinScene::start()
{
	const SDL_Color red = { 128, 0, 0, 255 };
	const SDL_Color white = { 255,255,255,255 };

	SoundManager::Instance().load("../Assets/audio/Surreal-Game-Menu_Looping.mp3", "EndLevel-Music", SOUND_MUSIC);
	SoundManager::Instance().playMusic("EndLevel-Music", -1, 0);
	SoundManager::Instance().setMusicVolume(2);

	TextureManager::Instance().load("../Assets/textures/Full-tile.png", "Background");

	m_label = new Label("Congrats You Made It, Now Find The Cure", "YouMurderer", 60, white, glm::vec2(400.0f, 200.0f));
	m_label->setParent(this);
	addChild(m_label);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2(400.0f, 400.0f);
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
		{
			m_pRestartButton->setActive(false);
			TheGame::Instance().changeSceneState(LEVEL_1);
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
