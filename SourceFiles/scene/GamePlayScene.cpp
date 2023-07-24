#include "GamePlayScene.h"
#include "Sprite.h"
#include "ParticleManager.h"

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,10 });
	stage.Initialize();
	for (size_t i = 1; i < 3; i++)
	{
		//Model::GetLightGroup()->SetDirLightActive(i, false);
	}
	Model::GetLightGroup()->SetPointLightActive(0, true);
	Model::GetLightGroup()->SetPointLightAtten(0, { 0,0.01f,0.001f });
	Model::GetLightGroup()->SetPointLightPos(0, { 0,20 });
	viewProjection.Initialize();
	viewProjection.eye.y = 250;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	Model::SetViewProjection(&viewProjection);
	Model::SetViewProjection(&debugCamera);
}

void GamePlayScene::Update()
{
	static bool flag = true;
	//Model::GetLightGroup()->SetCircleShadowActive(0, flag);
	flag = !flag;
	debugCamera.Update();
	stage.Update();
	rotQ = Quaternion::MakeAxisAngle(Vector3::MakeAxis(Axis::Z), rotAngle);
	rotAngle += 3;
	//Model::GetLightGroup()->SetCircleShadowDir(0, Quaternion::RotateVector({ 0,1,0 }, rotQ));
}

void GamePlayScene::Draw()
{
	Model::PreDraw();
	stage.Draw();
	Model::PostDraw();
}