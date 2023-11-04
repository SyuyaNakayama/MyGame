#include "TitleScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "ImGuiManager.h"

void TitleScene::Initialize()
{
	ui = Sprite::Create("ui/title_JP.png");
	ui->position = Half(WindowsAPI::WIN_SIZE);
	ui->position.y -= 100;
	ui->anchorPoint = { 0.5f,0.5f };
	ui->size *= 1.5f;
	ui->Update();
	debugCamera.Initialize();
	stage.Initialize();
	camera.Initialize();
	camera.eye.y = 250;
	camera.eye.z = -50;
	camera.target.z = 10;
	ModelManager::SetViewProjection(&camera);
	spaceKeyUI.Initialize("ui/key_SPACE.png", 128, 30);
	Sprite* spaceKeySprite = spaceKeyUI.GetSprite();
	spaceKeySprite->position = Half(WindowsAPI::WIN_SIZE);
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