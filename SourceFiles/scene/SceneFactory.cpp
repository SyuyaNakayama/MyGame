#include "SceneFactory.h"
#include "GamePlayScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include <cassert>

SceneFactory* SceneFactory::GetInstance()
{
	static SceneFactory instance;
	return &instance;
}

BaseScene* SceneFactory::CreateScene(Scene scene)
{
	BaseScene* newScene = nullptr;

	switch (scene)
	{
	case Scene::Title: newScene = new TitleScene; break;
	case Scene::Play: newScene = new GamePlayScene; break;
	case Scene::Result: newScene = new ResultScene; break;
	default: newScene = nullptr;
	}

	assert(newScene);
	return newScene;
}