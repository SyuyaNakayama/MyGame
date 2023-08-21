#include "GamePlayScene.h"
#include <imgui.h>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	viewProjection.Initialize();
	viewProjection.eye.y = 350;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	stage.Initialize();
	ModelManager::SetViewProjection(&debugCamera);
	ui = Sprite::Create("ui/–³‘è149_20230821175205.png");
	ui->position = WindowsAPI::WIN_SIZE / 2.0f;
	ui->Update();
}

void GamePlayScene::Update()
{
	if (input->IsTrigger(Key::_1)) { ModelManager::SetViewProjection(&viewProjection); }
	if (input->IsTrigger(Key::_2)) { ModelManager::SetViewProjection(&debugCamera); }
	debugCamera.Update();
	stage.Update();
}

void GamePlayScene::Draw()
{
	Sprite::PreDraw();
	ui->Draw();
}