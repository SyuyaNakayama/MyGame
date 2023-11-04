#pragma once
#include "BaseScene.h"
#include "BitMapNumber.h"
#include <map>

// UI描画クラス(リザルトシーン用)
class UIDrawerResultScene : public AbstractUIDrawer
{
private:
	// ランクと点数
	static const int GAUGE_MAX_SCORE = 3000;
	enum class Rank
	{
		MAX = GAUGE_MAX_SCORE,
		S = Rank::MAX * 9 / 10,
		A = Rank::MAX * 7 / 10,
		B = Rank::MAX * 5 / 10,
		C = Rank::MAX * 0 / 10
	};

	std::unique_ptr<Sprite> rankGauge;
	std::unique_ptr<Sprite> rankGaugeBG;
	std::map<Rank, std::unique_ptr<Sprite>> rankGaugeSplit;
	std::map<Rank, std::unique_ptr<Sprite>> rankUI;
	std::unique_ptr<Sprite> scoreUI;
	int score;
	int printScore; // 今表示されてるゲージ量
	BitMapNumber printScoreUI; // 今表示されてるゲージ量のUI
	const Vector2 GAUGE_SIZE = { 641,40 };
	const int GAUGE_INC_SPD = 15; // ゲージ上昇速度

	// スコアをモニター座標に変換
	float ScoreToMoniter(int score_) { return min((float)score_ * GAUGE_SIZE.x / GAUGE_MAX_SCORE, GAUGE_SIZE.x); }

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