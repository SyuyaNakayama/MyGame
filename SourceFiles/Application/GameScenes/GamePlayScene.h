#pragma once
#include "AudioManager.h"
#include "BaseScene.h"
#include "BitMapNumber.h"
#include "Easing.h"
#include "FPS.h"
#include "MathUtility.h"
#include "Stage.h"

// スタート前のカウントダウン演出
class StartCountDown
{
private:
	static const int COUNT_DOWN_TIME = 3;
	static int fps;
	BitMapNumber countUI;
	FrameTimer countTimer = 0;

public:
	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static std::unique_ptr<StartCountDown> Create();
	/// <summary>
	/// 更新
	/// </summary>
	/// <returns>カウントダウンが終わったかのフラグ</returns>
	bool Update();
	// 描画
	void Draw();
	// FPSを取得
	static int GetFPS() { return fps; }
};

// UI描画クラス(ゲームシーン用)
class UIDrawerGameScene : public AbstractUIDrawer
{
private:
	const float SLIDE_DIS_UI_GO = 500; // "Go!"のUIがスライドする距離

	Stage* stage;
	std::unique_ptr<Sprite> uiScore;
	std::unique_ptr<Sprite> uiClock;
	BitMapNumber scoreSprite;
	BitMapNumber timeIntSprite; // 残り時間整数部
	BitMapNumber timeDecSprite; // 残り時間小数部
	Angle easingColor = 0; // 時間UI色のイージングに使う
	std::unique_ptr<StartCountDown> countDown;
	std::unique_ptr<Sprite> uiGo;
	Vector2 uiGoSize;
	Easing uiGoEasing;

	// "Go!"のアニメーションの関数ポインタ
	void (UIDrawerGameScene::*UIGoAnimation)();
	// スライド
	void UIGoSlide();
	// 待機
	void UIGoIdle();
	// ズーム
	void UIGoZoom();

public:
	// コンストラクタ
	UIDrawerGameScene(Stage* stage_) { stage = stage_; }
	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 描画(オーバーライド)
	void Draw();
	// カウントダウン中か
	bool IsCountDown() { return countDown.get() != nullptr; }
};

// ゲームプレイシーンの処理
class GamePlayScene : public BaseScene
{
private:
	Stage stage;
	ViewProjection viewProjection;
	Audio* audio = nullptr;

	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 終了
	void Finalize() { stage.Finalize(); }
};