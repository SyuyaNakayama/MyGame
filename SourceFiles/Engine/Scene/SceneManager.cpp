#include "SceneManager.h"
#include "Sprite.h"

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
		scene->Initialize();
	}

	if (!fadeManager.IsFade())
	{
		scene->Update();
	}
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

void SceneManager::ChangeScene(Scene nextScene_, bool isUseFade)
{
	nextScene = nextScene_;
	if (isUseFade) { fadeManager.FadeScene(); }
}
