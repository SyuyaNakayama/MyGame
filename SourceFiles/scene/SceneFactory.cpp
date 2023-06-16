#include "SceneFactory.h"
#include "GamePlayScene.h"
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
	case Scene::Null: return nullptr;
	case Scene::Play: newScene = new GamePlayScene;
	}

	assert(newScene);
	return newScene;
}