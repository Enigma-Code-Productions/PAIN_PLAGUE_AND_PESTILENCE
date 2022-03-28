#pragma once
#ifndef __PAUSE_MANAGER__
#define __PAUSE_MANAGER__

#include "Scene.h"
#include <vector>
#include "SceneState.h"
class PauseManager
{
private:
	static bool m_isPaused;
	static std::vector<Scene*> s_scenes;
	static SceneState previousScene;
	PauseManager(){}
public:

	static void PopScene();
	static void PushScene(Scene* pScene);
	static void AddScene(Scene* aScene);
	static std::vector<Scene*>& GetScenes();
	static const bool getIsPaused();
};

typedef PauseManager PAMA;

#endif
