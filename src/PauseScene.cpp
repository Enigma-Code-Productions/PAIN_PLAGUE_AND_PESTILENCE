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
	SDL_Rect rect = { 200,200,200,200 };
	SDL_RenderFillRect(Renderer::Instance().getRenderer(), &rect);
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
	
}





