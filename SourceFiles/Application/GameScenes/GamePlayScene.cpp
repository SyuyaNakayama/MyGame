#include "GamePlayScene.h"
#include "SceneManager.h"
#include <imgui.h>

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	viewProjection.Initialize();
	viewProjection.eye.y = 350;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	stage.Initialize();
	UIInitialize();
	//ModelManager::SetViewProjection(&debugCamera);
}

void GamePlayScene::Update()
{
	//if (input->IsTrigger(Key::_1)) { ModelManager::SetViewProjection(&viewProjection); }
	//if (input->IsTrigger(Key::_2)) { ModelManager::SetViewProjection(&debugCamera); }
	debugCamera.Update();
	stage.Update();
	UIUpdate();
	if (stage.IsFinished() /*|| input->IsTrigger(Key::Space)*/)
	{
		sceneManager->ChangeScene(Scene::Result);
		ModelManager::ClearObjects();
	}
}

void GamePlayScene::Draw()
{
	scoreSprite.Draw();
	timeIntSprite.Draw();
	timeDecSprite.Draw();
	uiClock->Draw();
	uiScore->Draw();
}

void GamePlayScene::UIInitialize()
{
	// ビットマップの設定
	BitMapProp bitMapProp =
	{
		"ui/num.png",{30,30},{30,30},{1100,100},4
	};

	// スコア
	scoreSprite.Initialize(bitMapProp);
	uiScore = Sprite::Create("ui/score.png");
	uiScore->anchorPoint = { 0.5f,0.5f };
	uiScore->position = { 1160,70 };
	uiScore->Update();

	// 残り時間
	bitMapProp.pos.x = 60;
	bitMapProp.digit = 2;
	timeIntSprite.Initialize(bitMapProp); // 整数部

	bitMapProp.pos = { 120,115 };
	bitMapProp.digit = 3;
	bitMapProp.size /= 2;
	timeDecSprite.Initialize(bitMapProp); // 小数部

	uiClock = Sprite::Create("ui/clock.png");
	uiClock->anchorPoint = { 0.5f,0.5f };
	uiClock->position = { 112.5f,54 };
	uiClock->Update();
}

void GamePlayScene::UIUpdate()
{
	scoreSprite.Update(stage.GetScore());

	float remainTime = stage.GetRemainTime();

	// 残り時間が10秒以下になると時間の文字が赤点滅する
	if (remainTime <= 10.0f)
	{
		easingColor += (int)(15.0f - remainTime);
		float colorGB = (cos(easingColor) + 1) * 0.5f;
		timeIntSprite.ChangeColor({ 1,colorGB,colorGB,1 });
		timeDecSprite.ChangeColor({ 1,colorGB,colorGB,1 });
	}

	timeIntSprite.Update((int)remainTime);

	float temp = stage.GetRemainTime();
	float decimal = modf(remainTime, &temp) * 1000;
	timeDecSprite.Update((int)decimal);
}