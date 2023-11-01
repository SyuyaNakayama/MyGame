#pragma once
#include "BaseScene.h"
#include "BitMapNumber.h"

// UI描画クラス(リザルトシーン用)
class UIDrawerResultScene : public AbstractUIDrawer
{
private:
	std::unique_ptr<Sprite> rankGauge;
	std::unique_ptr<Sprite> rankGaugeBG;
	std::unique_ptr<Sprite> scoreUI;
	int score;
	int printScore; // 今表示されてるゲージ量
	BitMapNumber printScoreUI; // 今表示されてるゲージ量のUI
	const Vector2 GAUGE_SIZE = { 641,40 };
	const int GAUGE_MAX_SCORE = 3000;
	const int GAUGE_INC_SPD = 15; // ゲージ上昇速度

public:
	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 描画(オーバーライド)
	void Draw();
};


// 結果発表シーンの処理
class ResultScene : public BaseScene
{

	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 描画(オーバーライド)
	void Draw();
};