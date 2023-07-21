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
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	stage.Update();
	DiffuseParticle::AddProp addProp;
	addProp.start_scale = 5.0f;
	addProp.posOffset.y = -50.0f;
	ParticleManager::GetParticleGroup(0)->Add(addProp);
}

void GamePlayScene::Draw()
{
	Model::PreDraw();
	stage.Draw();
	Model::PostDraw();
}