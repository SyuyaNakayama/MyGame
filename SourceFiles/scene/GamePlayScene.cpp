#include "GamePlayScene.h"
#include "Sprite.h"
#include "ParticleManager.h"

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,-50 });
	stage.Initialize();
	for (size_t i = 1; i < 3; i++)
	{
		Model::GetLightGroup()->SetDirLightActive(i, false);
	}
	viewProjection.Initialize();
	viewProjection.eye.y = 250;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	Model::SetViewProjection(&viewProjection);
	Model::SetViewProjection(&debugCamera);
	multiTexModel = Model::Create("multiTexSphere", true);
	multiTexModel->GetMaterial()->GetSprite(TexType::Main)->color = { 0,0,1,1 };
	multiTexModel->Update();
	multiTexModelWT.Initialize();
	multiTexModelWT.translation.y = -50;
	multiTexModelWT.scale *= 10;
	multiTexModelWT.Update();
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	stage.Update();
}

void GamePlayScene::Draw()
{
	Model::PreDraw();
	stage.Draw();
	multiTexModel->Draw(multiTexModelWT);
	Model::PostDraw();
}