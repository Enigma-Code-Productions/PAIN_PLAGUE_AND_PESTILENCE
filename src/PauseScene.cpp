#include "PauseScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "PauseManager.h"

PauseScene::PauseScene()
{}

PauseScene::~PauseScene()
= default;

void PauseScene::update()
{
	updateDisplayList();
	//std::cout << "PAUSE SCENE" << std::endl;
	if (m_resume)
		PAMA::PopScene();
	else if (m_exit)
		PAMA::ExitScene();
}

void PauseScene::draw()
{
	PAMA::GetScenes().front()->draw();

	SDL_SetRenderDrawBlendMode(Renderer::Instance().getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), (float)0.5f, (float)0.5f, (float)0.5f, 170);
	SDL_Rect rect = { 0,0,800,800 };
	SDL_RenderFillRect(Renderer::Instance().getRenderer(), &rect);

	TextureManager::Instance().draw("scroll", 235.0f, 295.0f, 0, 255, true, SDL_FLIP_NONE, 1);
	drawDisplayList();
	//TextureManager::Instance().draw("resume_button", 225.0f, 220.0f, 0, 255, true, SDL_FLIP_NONE, 1.2f);
	//TextureManager::Instance().draw("exit_button", 225.0f, 320.0f, 0, 255, true, SDL_FLIP_NONE, 1.2f);
	TextureManager::Instance().draw("controls", 560.0f, 200.0f, 0, 255, true, SDL_FLIP_NONE, 1);
	TextureManager::Instance().draw("attack_instructions", 580.0f, 310.0f, 0, 255, true, SDL_FLIP_NONE, 1);
	TextureManager::Instance().draw("change_potion", 540.0f, 375.0f, 0, 255, true, SDL_FLIP_NONE, 0.8f);
	TextureManager::Instance().draw("heal", 650.0f, 375.0f, 0, 255, true, SDL_FLIP_NONE, 0.8f);
	TextureManager::Instance().draw("throw_potion", 535.0f, 430.0f, 0, 255, true, SDL_FLIP_NONE, 0.8f);
}

void PauseScene::handleEvents()
{
	EventManager::Instance().update();
}

void PauseScene::clean()
{
	
}

void PauseScene::start()
{
	const SDL_Color white = { 255,255,255,255 };

	m_resume = false;
	m_exit = false;

	TextureManager::Instance().load("../Assets/textures/PauseMenuBG.png", "scroll");
	TextureManager::Instance().load("../Assets/textures/ControlInstructions.png", "controls");
	TextureManager::Instance().load("../Assets/textures/AttackInstructions.png", "attack_instructions");
	TextureManager::Instance().load("../Assets/textures/ChangePotion.png", "change_potion");
	TextureManager::Instance().load("../Assets/textures/HealthKey.png", "heal");
	TextureManager::Instance().load("../Assets/textures/throwPotion.png", "throw_potion");

	// Resume Button
	m_pResumeButton = new Button("../Assets/textures/ResumeButton.png", "resume_button");
	m_pResumeButton->getTransform()->position = glm::vec2(230.0f, 205.0f);
	m_pResumeButton->addEventListener(CLICK, [&]()-> void
		{
			m_pResumeButton->setActive(false);
			m_resume = true;
		});

	m_pResumeButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pResumeButton->setAlpha(128);
		});

	m_pResumeButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pResumeButton->setAlpha(255);
		});
	addChild(m_pResumeButton);

	// Exit Button
	m_pExitButton = new Button("../Assets/textures/exitbutton.png", "exit_button");
	m_pExitButton->getTransform()->position = glm::vec2(230.0f, 320.0f);
	m_pExitButton->addEventListener(CLICK, [&]()-> void
		{
			m_pExitButton->setActive(false);
			m_exit = true;
		});

	m_pExitButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pExitButton->setAlpha(128);
		});

	m_pExitButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pExitButton->setAlpha(255);
		});
	addChild(m_pExitButton);

	//m_pauseLabel = new Label("Paused", "YouMurderer", 40, white, glm::vec2(400, 200));
	//m_pauseLabel->setParent(this);
	//addChild(m_pauseLabel);

	//m_instructionLabel = new Label("Press 'R' to Resume", "YouMurderer", 30, white, glm::vec2(400, 300));
	//m_instructionLabel->setParent(this);
	//addChild(m_instructionLabel);

}





