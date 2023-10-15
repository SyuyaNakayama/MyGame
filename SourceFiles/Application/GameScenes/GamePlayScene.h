#pragma once
#include "BaseScene.h"
#include "Stage.h"
#include "AudioManager.h"
#include "BitMapNumber.h"
#include "MathUtility.h"
#include "FPS.h"

// スタート前のカウントダウン演出
class StartCountDown
{
private:
	const float COUNT_DOWN_TIME = 3.0f;
	BitMapNumber countUI;
	RealTimer count = COUNT_DOWN_TIME;

public:
	static std::unique_ptr<StartCountDown> Create();
	void Update();
	void Draw();
	bool IsFinish() { return count.Update(); }
};

// ゲームプレイシーンの処理
class GamePlayScene : public BaseScene
{
private:
	Stage stage;
	ViewProjection viewProjection;
	Audio* audio = nullptr;
	std::unique_ptr<Sprite> uiScore;
	std::unique_ptr<Sprite> uiClock;
	BitMapNumber scoreSprite;
	BitMapNumber timeIntSprite; // 残り時間整数部
	BitMapNumber timeDecSprite; // 残り時間小数部
	BitMapNumber timeIntSprite2; // 残り時間整数部
	BitMapNumber timeDecSprite2; // 残り時間小数部
	Angle easingColor = 0; // 時間UI色のイージングに使う
	std::unique_ptr<StartCountDown> countDown;
	FPS* fps = FPS::GetInstance();
	FrameTimer timer = 20 * 60;

	void Initialize();
	void Update();
	void Draw();

	void UIInitialize();
	void UIUpdate();
};