#include "GamePlayScene.h"
#include "Sprite.h"
#include "ParticleManager.h"
#include <imgui.h>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,10 });
	for (size_t i = 1; i < 3; i++)
	{
		//ModelManager::GetLightGroup()->SetDirLightActive(i, false);
	}
	viewProjection.Initialize();
	viewProjection.eye.y = 250;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	ModelManager::SetViewProjection(&viewProjection);
	stage.Initialize();
	ModelManager::SetViewProjection(&debugCamera);

	object = ModelManager::Create("cube");
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	stage.Update();

	object->worldTransform.translation.y -= 0.01f;
	object->Update();
}

void GamePlayScene::Draw()
{
	ModelManager::PreDraw();
	stage.Draw();
	object->Draw();
	ModelManager::PostDraw();
}