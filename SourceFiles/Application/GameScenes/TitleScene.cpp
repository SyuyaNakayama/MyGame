#include "TitleScene.h"
#include "SceneManager.h"
#include "ModelManager.h"

void TitleScene::Initialize()
{
	ui = Sprite::Create("ui/title_JP.png");
	ui->position = WindowsAPI::WIN_SIZE / 2.0f;
	ui->anchorPoint = { 0.5f,0.5f };
	ui->Update();
	debugCamera.Initialize({ 0,0 });
	ModelManager::SetViewProjection(&debugCamera);
}

void TitleScene::Update()
{
	if (input->IsTrigger(Key::Space)) { sceneManager->ChangeScene(Scene::Play); }
}

void TitleScene::Draw()
{
	Sprite::PreDraw();
	ui->Draw();
}