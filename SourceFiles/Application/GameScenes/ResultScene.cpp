#include "ResultScene.h"
#include "SceneManager.h"
#include "ModelManager.h"

void ResultScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	ModelManager::SetViewProjection(&debugCamera);

	sprite = Sprite::Create("white1x1.png");
	sprite->size = { 300,200 };
	sprite->anchorPoint = { 0.5f,0.5f };
	sprite->position = WindowsAPI::WIN_SIZE / 2.0f;
	sprite->Update();
}

void ResultScene::Update()
{
	if (input->IsTrigger(Key::Space)) { sceneManager->ChangeScene(Scene::Title); }
}

void ResultScene::Draw()
{
	Sprite::PreDraw();
	sprite->Draw();
}
