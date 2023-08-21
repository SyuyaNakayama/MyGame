#include "ResultScene.h"
#include "SceneManager.h"
#include "ModelManager.h"

void ResultScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	ModelManager::SetViewProjection(&debugCamera);
}

void ResultScene::Update()
{
	if (input->IsTrigger(Key::Space)) { sceneManager->ChangeScene(Scene::Title); }
}

void ResultScene::Draw()
{
}
