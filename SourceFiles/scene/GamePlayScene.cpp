#include "GamePlayScene.h"
#include "Sprite.h"
#include "ParticleManager.h"
#include <imgui.h>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,10 });
	for (size_t i = 1; i < 3; i++)
	{
		//Model::GetLightGroup()->SetDirLightActive(i, false);
	}
	viewProjection.Initialize();
	viewProjection.eye.y = 250;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	Model::SetViewProjection(&viewProjection);
	stage.Initialize();
	Model::SetViewProjection(&debugCamera);

	object = Model::Create2("cube");
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
	Model::PreDraw();
	stage.Draw();
	object->Draw();
	Model::PostDraw();
}