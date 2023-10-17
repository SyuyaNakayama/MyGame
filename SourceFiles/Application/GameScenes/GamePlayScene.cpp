#include "GamePlayScene.h"
#include "SceneManager.h"
#include <imgui.h>

int StartCountDown::fps = 0;

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	viewProjection.Initialize();
	viewProjection.eye.y = 350;
	viewProjection.eye.z = -75;
	viewProjection.target.z = 10;
	stage.Initialize();
	UIInitialize();
	countDown = StartCountDown::Create();
	//ModelManager::SetViewProjection(&debugCamera);
	// カウントダウン前に一回更新する
	stage.Update();
	UIUpdate();
}

void GamePlayScene::Update()
{
#ifdef _DEBUG
	if (input->IsTrigger(Key::_1)) { ModelManager::SetViewProjection(&viewProjection); }
	if (input->IsTrigger(Key::_2)) { ModelManager::SetViewProjection(&debugCamera); }
	// カウントダウン演出
	ImGui::Text("FPS = %d", fps->GetFPS());
#endif // _DEBUG

	if (countDown)
	{
		countDown->Update();
		if (countDown->IsFinish()) { countDown.release(); stage.ResetTime(); }
		else { return; }
	}

	timer.Update();
	debugCamera.Update();
	stage.Update();
	UIUpdate();

	// ゲーム終了時にリザルト画面へ飛ぶ
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
	timeIntSprite2.Draw();
	timeDecSprite2.Draw();
	uiClock->Draw();
	uiScore->Draw();
	if (countDown) { countDown->Draw(); }
}

void GamePlayScene::UIInitialize()
{
	// ビットマップの設定
	BitMapProp bitMapProp =
	{
		"ui/num.png",{30,30},{30,30},{1100,100},4
	};

	// スコア
	*scoreSprite.GetBitMapProp() = bitMapProp;
	scoreSprite.Initialize();
	uiScore = Sprite::Create("ui/score.png");
	uiScore->anchorPoint = { 0.5f,0.5f };
	uiScore->position = { 1160,70 };
	uiScore->Update();

	// 残り時間
	bitMapProp.pos.x = 60;
	bitMapProp.digit = 2;
	*timeIntSprite.GetBitMapProp() = bitMapProp;
	timeIntSprite.Initialize(); // 整数部

	bitMapProp.pos = { 120,115 };
	bitMapProp.digit = 3;
	bitMapProp.size /= 2;
	*timeDecSprite.GetBitMapProp() = bitMapProp;
	timeDecSprite.Initialize(); // 小数部

	// 残り時間
	bitMapProp.size *= 2;
	bitMapProp.pos.y += 50;
	bitMapProp.pos.x = 60;
	bitMapProp.digit = 2;
	*timeIntSprite2.GetBitMapProp() = bitMapProp;
	timeIntSprite2.Initialize(); // 整数部

	bitMapProp.pos = { 120,180 };
	bitMapProp.digit = 3;
	bitMapProp.size /= 2;
	*timeDecSprite2.GetBitMapProp() = bitMapProp;
	timeDecSprite2.Initialize(); // 小数部

	uiClock = Sprite::Create("ui/clock.png");
	uiClock->anchorPoint = { 0.5f,0.5f };
	uiClock->position = { 112.5f,54 };
	uiClock->Update();
}

void GamePlayScene::UIUpdate()
{
	scoreSprite.Update(stage.GetScore());

	// カウントダウン中は60.000秒固定
	if (countDown)
	{
		timeIntSprite.Update(60);
		timeDecSprite.Update(000);
		return;
	}

	float remainTime = stage.GetRemainTime();

	// 残り時間が10秒以下になると時間の文字が赤点滅する
	if (remainTime <= 10.0f)
	{
		easingColor += (int)(15.0f - remainTime);
		float colorGB = (cos(easingColor) + 1) * 0.5f;
		timeIntSprite.GetBitMapProp()->color = { 1,colorGB,colorGB,1 };
		timeDecSprite.GetBitMapProp()->color = { 1,colorGB,colorGB,1 };
	}

	timeIntSprite.Update((int)remainTime);

	float temp = stage.GetRemainTime();
	float decimal = modf(remainTime, &temp) * 1000;
	timeDecSprite.Update((int)decimal);

	float nowtime = (float)timer.GetTime() / 20.0f;
	float nowtime2 = modf(nowtime, &temp) * 1000;
	timeIntSprite2.Update((int)nowtime);
	timeDecSprite2.Update((int)nowtime2);
}

std::unique_ptr<StartCountDown> StartCountDown::Create()
{
	std::unique_ptr<StartCountDown> countDown = std::make_unique<StartCountDown>();

	// ビットマップの設定
	BitMapProp bitMapProp =
	{
		"ui/num.png",{30,30},{180,180},{},1
	};

	bitMapProp.pos = (WindowsAPI::WIN_SIZE - bitMapProp.size) / 2.0f;
	*countDown->countUI.GetBitMapProp() = bitMapProp;
	countDown->countUI.Initialize();
	if (fps == 0) { fps = FPS::GetInstance()->GetFPS(); }
	countDown->count = COUNT_DOWN_TIME * fps;

	return countDown;
}

void StartCountDown::Update()
{
	int time = count.GetTime() / fps;
	time = min(3, time + 1);
	countUI.Update(time);
	ImGui::Text("count.GetTime() %d", count.GetTime());
}

void StartCountDown::Draw()
{
	countUI.Draw();
}
