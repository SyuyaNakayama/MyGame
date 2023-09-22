#include "GamePlayScene.h"
#include "SceneManager.h"
#include <imgui.h>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	viewProjection.Initialize();
	viewProjection.eye.y = 350;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	stage.Initialize();
	//ModelManager::SetViewProjection(&debugCamera);
}

void GamePlayScene::Update()
{
	//if (input->IsTrigger(Key::_1)) { ModelManager::SetViewProjection(&viewProjection); }
	//if (input->IsTrigger(Key::_2)) { ModelManager::SetViewProjection(&debugCamera); }
	debugCamera.Update();
	stage.Update();
	//if (stage.IsFinished() || input->IsTrigger(Key::Space))
	//{
	//	sceneManager->ChangeScene(Scene::Result);
	//	ModelManager::ClearObjects();
	//}
}

void GamePlayScene::Draw()
{
}