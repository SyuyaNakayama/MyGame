#include "GamePlayScene.h"
#include "Sprite.h"
#include "ParticleManager.h"
#include <imgui.h>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	for (size_t i = 1; i < 3; i++)
	{
		//ModelManager::GetLightGroup()->SetDirLightActive(i, false);
	}
	viewProjection.Initialize();
	viewProjection.eye.y = 250;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	stage.Initialize();
	ModelManager::SetViewProjection(&debugCamera);
}

void GamePlayScene::Update()
{
	if(input->IsTrigger(Key::_1)){ ModelManager::SetViewProjection(&viewProjection); }
	if(input->IsTrigger(Key::_2)){ ModelManager::SetViewProjection(&debugCamera); }
	debugCamera.Update();
	stage.Update();
}

void GamePlayScene::Draw()
{
}