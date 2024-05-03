#include "GamePlayScene.h"
#include "SceneManager.h"
#include <imgui.h>

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

int StartCountDown::fps = 0;

void GamePlayScene::Initialize()
{
	debugCamera.Initialize({ 0,0 });
	stage.Initialize();

	// UI描画クラスのインスタンス生成
	uiDrawer = std::make_unique<UIDrawerGameScene>(&stage);
	uiDrawer->Initialize();
	// カウントダウン前に一回更新する
	stage.Update();
	uiDrawer->Update();
}

void GamePlayScene::Update()
{
	// UIの更新
	uiDrawer->Update();
	UIDrawerGameScene* uiDrawer_ = dynamic_cast<UIDrawerGameScene*>(uiDrawer.get());
	if (uiDrawer_) { if (uiDrawer_->IsCountDown()) { return; } }

	// ステージの更新
	stage.Update();

	// ゲーム終了時にリザルト画面へ飛ぶ
	if (stage.IsFinished())
	{
		sceneManager->ChangeScene(Scene::Result);
		GoalManager::GetInstance()->ResetGoalPointer();
	}
}

void GamePlayScene::Draw()
{
	WristerEngine::BaseScene::Draw();
}

std::unique_ptr<StartCountDown> StartCountDown::Create()
{
	std::unique_ptr<StartCountDown> countDown = std::make_unique<StartCountDown>();

	*countDown->countUI.GetBitMapProp() = WEConst(BitMapProp, "UiCountDown");
	countDown->countUI.GetBitMapProp()->fileName = "ui/num.png";
	countDown->countUI.Initialize();
	if (fps == 0) { fps = WristerEngine::MAX_FPS; }
	countDown->countTimer = COUNT_DOWN_TIME * fps;

	return countDown;
}

bool StartCountDown::Update()
{
	bool isFinish = countTimer.Update();
	// カウントダウン描画の更新
	int time = countTimer.GetRemainTime() / fps;
	time = min(COUNT_DOWN_TIME, time + 1);
	countUI.Update(time);
	// 数字のスライド演出
	auto timeSecond = countTimer.GetRemainTime(fps);
	const int SLIDE_START = 250; // スライド演出が始まるタイミング
	if (timeSecond[1] <= SLIDE_START)
	{
		// スプライトのUV座標をずらす
		float offsetRate = 1.0f - (float)timeSecond[1] / SLIDE_START;
		countUI.GetBitMapProp()->texLTOffset.x = countUI.GetAllSpriteSize().x * offsetRate;
	}
	else { countUI.GetBitMapProp()->texLTOffset.x = 0; }

	return isFinish;
}

void StartCountDown::Draw()
{
	countUI.Draw();
}

void UIDrawerGameScene::Initialize()
{
	PlayMode::Initialize();

	// 残り時間
	// 整数部
	*timeIntSprite.GetBitMapProp() = Const(BitMapProp, "UiTimeInt");
	timeIntSprite.GetBitMapProp()->fileName = "ui/num.png";
	timeIntSprite.Initialize();
	// 小数部
	*timeDecSprite.GetBitMapProp() = Const(BitMapProp, "UiTimeDec");
	timeDecSprite.GetBitMapProp()->fileName = "ui/num.png";
	timeDecSprite.Initialize();
	// 時計アイコン
	sprites["Clock"] = Sprite::Create("ui/clock.png");
	sprites["Clock"]->SetCenterAnchor();
	sprites["Clock"]->position = { 112.5f,54 };

	// カウントダウンUI
	countDown = StartCountDown::Create();
	sprites["Go"] = Sprite::Create("ui/GO.png");
	sprites["Go"]->SetCenterAnchor();
	sprites["Go"]->position = Half(WristerEngine::WIN_SIZE);
	sprites["Go"]->isInvisible = true; // 透明
	const int GO_EASING_DEC = 4;
	uiGoEasing.Initialize(StartCountDown::GetFPS() / GO_EASING_DEC, WristerEngine::Easing::Type::Sqrt);
	UIGoAnimation = &UIDrawerGameScene::UIGoSlide;

	AbstractUIDrawer::Update();
}

void UIDrawerGameScene::Update()
{
	PlayMode::Update();

	if (countDown)
	{
		// カウントダウン中は60.000秒固定
		timeIntSprite.Update(60);
		timeDecSprite.Update(0);

		if (countDown->Update())
		{
			countDown.release();
			stage->ResetTime();
			sprites["Go"]->isInvisible = false;
		}
		else { return; }
	}

	if (!sprites["Go"]->isInvisible)
	{
		(this->*UIGoAnimation)();
		sprites["Go"]->Update();
	}

	// 残り時間を取得
	std::array<int, 2> remainTime = stage->GetRemainTime();

	// 残り時間が10秒以下になると時間の文字が赤点滅する
	if (remainTime[0] < 10)
	{
		easingColor += (int)15 - remainTime[0];
		float colorGB = (cos(easingColor) + 1) * 0.5f;
		timeIntSprite.GetBitMapProp()->color = { 1,colorGB,colorGB,1 };
		timeDecSprite.GetBitMapProp()->color = { 1,colorGB,colorGB,1 };
	}

	timeIntSprite.Update(remainTime[0]);
	timeDecSprite.Update(remainTime[1]);

	AbstractUIDrawer::Update();
}

void UIDrawerGameScene::UIGoSlide()
{
	float easingNum = uiGoEasing.Update();
	sprites["Go"]->position.x = WristerEngine::WIN_SIZE.x / 2.0f + SLIDE_DIS_UI_GO * (1.0f - easingNum);
	sprites["Go"]->color.a = easingNum;
	if (uiGoEasing.IsFinish())
	{
		UIGoAnimation = &UIDrawerGameScene::UIGoIdle;
	}
}

void UIDrawerGameScene::UIGoIdle()
{
	const int IDLE_TIME = 20;
	static WristerEngine::FrameTimer idle = IDLE_TIME;
	if (idle.Update())
	{
		uiGoSize = sprites["Go"]->size;
		UIGoAnimation = &UIDrawerGameScene::UIGoZoom;
		uiGoEasing.Restart();
	}
}

void UIDrawerGameScene::UIGoZoom()
{
	float easingNum = uiGoEasing.Update();
	sprites["Go"]->size = uiGoSize * (1.0f + easingNum);
	sprites["Go"]->color.a = (1.0f - easingNum);
	if (uiGoEasing.IsFinish())
	{
		sprites["Go"]->isInvisible = false;
	}
}

void UIDrawerGameScene::Draw()
{
	timeIntSprite.Draw();
	timeDecSprite.Draw();
	PlayMode::Draw();
	if (countDown) { countDown->Draw(); }
}