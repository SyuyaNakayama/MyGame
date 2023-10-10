#include "TitleScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "ImGuiManager.h"

void TitleScene::Initialize()
{
	ui = Sprite::Create("ui/title_JP.png");
	ui->position = WindowsAPI::WIN_SIZE / 2.0f;
	ui->position.y -= 100;
	ui->anchorPoint = { 0.5f,0.5f };
	ui->size *= 1.5f;
	ui->Update();
	debugCamera.Initialize({ 0,0 });
	stage.Initialize();
	camera.Initialize();
	camera.eye.y = 250;
	camera.eye.z = -50;
	camera.target.z = 10;
	ModelManager::SetViewProjection(&camera);
	spaceKeyUI.Initialize("ui/key_SPACE.png", 128, 30);
	Sprite* spaceKeySprite = spaceKeyUI.GetSprite();
	spaceKeySprite->position = WindowsAPI::WIN_SIZE / 2.0f;
	spaceKeySprite->position.y += 100;
	spaceKeySprite->size *= 1.5f;
	spaceKeySprite->anchorPoint = { 0.5f,0.5f };
}

void TitleScene::Update()
{
	if (input->IsTrigger(Key::Space))
	{
		sceneManager->ChangeScene(Scene::Play); 
		ModelManager::ClearObjects();
		return; 
	}
	debugCamera.Update();
	stage.Update();
	spaceKeyUI.Update();
}

void TitleScene::Draw()
{
	ui->Draw();
	spaceKeyUI.Draw();
}