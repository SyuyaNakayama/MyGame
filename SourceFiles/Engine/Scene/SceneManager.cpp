#include "SceneManager.h"
#include "Sprite.h"
#include "ModelManager.h"
#include "ParticleManager.h"

BaseScene::BaseScene() { sceneManager = SceneManager::GetInstance(); }

SceneManager* SceneManager::GetInstance()
{
	static SceneManager sceneManager;
	return &sceneManager;
}

void SceneManager::Initialize()
{
	fadeManager.Initialize();
}

void SceneManager::Update()
{
	fadeManager.Update();

	bool isChangeScene = fadeManager.IsChange() || !fadeManager.IsFade();
	isChangeScene &= nextScene != Scene::Null;
	if (isChangeScene)
	{
		if (scene)
		{
			scene->Finalize();
			scene.release();
		}

		scene = sceneFactory->CreateScene(nextScene);
		nowScene = nextScene;
		nextScene = Scene::Null;

		if (isObjectClear)
		{
			ModelManager::ClearObjects();
			isObjectClear = false;
		}
		if (isParticleClear)
		{
			ParticleManager::Clear();
			isParticleClear = false;
		}

		scene->Initialize();
		scene->Update();
	}

	if (!fadeManager.IsFade()) { scene->Update(); }
}

void SceneManager::Draw()
{
	scene->Draw();
	if (fadeManager.IsFade())
	{
		Sprite::PreDraw();
		fadeManager.Draw();
	}
}

void SceneManager::ChangeScene(Scene nextScene_, bool isObjectClear_, bool isParticleClear_, bool isUseFade)
{
	nextScene = nextScene_;
	isObjectClear = isObjectClear_;
	isParticleClear = isParticleClear_;
	if (isUseFade) { fadeManager.FadeScene(); }
}
