#include "GamePlayScene.h"
#include "Sprite.h"

void GamePlayScene::Initialize()
{
	debugCamera.Initialize();
	stage.Initialize();
	Model::SetViewProjection(&debugCamera);
	level = JsonLoader::LoadJson("map3");
	for (size_t i = 1; i < 3; i++)
	{
		Model::GetLightGroup()->SetDirLightActive(i, false);
	}
}

void GamePlayScene::Update()
{
	debugCamera.Update();
	stage.Update();
}

void GamePlayScene::Draw()
{
	Model::PreDraw();
	//stage.Draw();
	level->Draw();
	Model::PostDraw();
}