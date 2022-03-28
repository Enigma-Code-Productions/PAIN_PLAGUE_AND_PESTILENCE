#include "PauseManager.h"

#include "Game.h"

void PauseManager::PushScene(Scene* pScene)
{
	m_isPaused = true;
	s_scenes.push_back(pScene);
	previousScene = Game::Instance().getCurrentSceneState();
	//std::cout << "Actual Scene: " << pScene << std::endl;
	Game::Instance().pauseSceneState(PAUSE_SCENE, pScene);
	//std::cout << "SIZE: " << s_scenes.size() << std::endl;
}

void PauseManager::AddScene(Scene* aScene)
{
	s_scenes.push_back(aScene);
}


void PauseManager::PopScene()
{
	m_isPaused = false;
	if (s_scenes.size() <= 1) return;
	if(!s_scenes.empty())
	{
		s_scenes.back()->clean();
		delete s_scenes.back();
		s_scenes.back() = nullptr;
		s_scenes.pop_back();
	}
	Game::Instance().resumeSceneState(s_scenes.back(), previousScene);
	s_scenes.clear();
}

std::vector<Scene*>& PauseManager::GetScenes()
{
	return s_scenes;
}


const bool PauseManager::getIsPaused()
{
	return m_isPaused;
}


std::vector<Scene*> PauseManager::s_scenes;

bool PauseManager::m_isPaused = false;
SceneState PauseManager::previousScene = NO_SCENE;