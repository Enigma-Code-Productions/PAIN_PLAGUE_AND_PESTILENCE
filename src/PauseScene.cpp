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
	//std::cout << "PAUSE SCENE" << std::endl;
	if (EventManager::Instance().keyPressed(SDL_SCANCODE_R))
	{
		//std::cout << "POP" << std::endl;
		PAMA::PopScene();
	}
}

void PauseScene::draw()
{
	PAMA::GetScenes().front()->draw();

	SDL_SetRenderDrawBlendMode(Renderer::Instance().getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), (float)0.5f, (float)0.5f, (float)0.5f, 170);
	SDL_Rect rect = { 275,150,250,320 };
	SDL_RenderFillRect(Renderer::Instance().getRenderer(), &rect);
	drawDisplayList();
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

	m_pauseLabel = new Label("Paused", "YouMurderer", 40, white, glm::vec2(400, 200));
	m_pauseLabel->setParent(this);
	addChild(m_pauseLabel);

	m_instructionLabel = new Label("Press 'R' to Resume", "YouMurderer", 30, white, glm::vec2(400, 300));
	m_instructionLabel->setParent(this);
	addChild(m_instructionLabel);
}





