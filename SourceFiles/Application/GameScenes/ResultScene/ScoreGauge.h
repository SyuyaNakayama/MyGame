#pragma once
#include "BitMapNumber.h"
#include <map>

enum class Rank
{
	Max = 600,
	S = Max * 9 / 10,
	A = Max * 7 / 10,
	B = Max * 5 / 10,
	C = Max * 0 / 10
};

// スコアゲージ処理
class ScoreGauge
{
private:
	const Vector2 GAUGE_SIZE = { 641,40 }; // ランクと点数
	const int GAUGE_INC_SPD = 3; // ゲージ上昇速度

	std::unique_ptr<WristerEngine::_2D::Sprite> scoreUI;
	int score = 0;
	int printScore = 0; // 今表示されてるゲージ量
	WristerEngine::_2D::BitMapNumber printScoreUI; // 今表示されてるゲージ量のUI

	std::unique_ptr<WristerEngine::_2D::Sprite> rankGauge;
	std::unique_ptr<WristerEngine::_2D::Sprite> rankGaugeBG;
	std::map<Rank, std::unique_ptr<WristerEngine::_2D::Sprite>> rankGaugeSplit;

public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// スコアをモニター座標に変換
	float ScoreToMoniter(int score_) { return min((float)score_ * GAUGE_SIZE.x / (float)Rank::Max, GAUGE_SIZE.x); }
	// ランクを取得
	Rank GetRank() const;
	// 前のランクを取得
	Rank GetPreRank() const;
	// アニメーションの終わりを取得
	bool IsAnimationEnd() const { return score == printScore; }
};
