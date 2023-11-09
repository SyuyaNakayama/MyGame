#pragma once
#include "BaseScene.h"
#include "BitMapNumber.h"
#include "Easing.h"
#include <map>

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

enum class Rank
{
	Max = 3000,
	S = Max * 9 / 10,
	A = Max * 7 / 10,
	B = Max * 5 / 10,
	C = Max * 0 / 10
};

// ランクを取得
Rank GetRank(int score);

class ScoreGauge
{
private:
	const Vector2 GAUGE_SIZE = { 641,40 }; // ランクと点数
	const int GAUGE_INC_SPD = 15; // ゲージ上昇速度

	std::unique_ptr<Sprite> scoreUI;
	int score = 0;
	int printScore = 0; // 今表示されてるゲージ量
	BitMapNumber printScoreUI; // 今表示されてるゲージ量のUI

	std::unique_ptr<Sprite> rankGauge;
	std::unique_ptr<Sprite> rankGaugeBG;
	std::map<Rank, std::unique_ptr<Sprite>> rankGaugeSplit;

public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// スコアをモニター座標に変換
	float ScoreToMoniter(int score_) { return min((float)score_ * GAUGE_SIZE.x / (float)Rank::Max, GAUGE_SIZE.x); }
	// 表示スコアのランクを取得
	Rank GetPrintRank() const { return GetRank(printScore); }
	// アニメーションの終わりを取得
	bool IsAnimationEnd() const { return score == printScore; }
};

class RankAnimation
{
private:
	const int RANK_ANIMATION_TIME = 10;

	std::unique_ptr<Sprite> resultRankSprite;
	std::map<Rank, std::unique_ptr<Sprite>> rankUI;
	std::unique_ptr<Sprite> blind; // 画面を暗くする
	Rank preRank;
	Easing rankSpriteFade;
	Easing rankSpriteScale;
	Vector2 rankSpriteSizeMem;
	const ScoreGauge* pScoreGauge;

	// ランクアニメーションの関数ポインタ
	void (RankAnimation::* Animation)() = &RankAnimation::Judge;
	// ランクとスコアの判定
	void Judge();
	// 消える
	void Disappear();
	// 現れる
	void Appear();
	// 最終ランク発表
	void Result();

public:
	// 初期化
	void Initialize(const ScoreGauge* pScoreGauge);
	// 更新
	void Update();
	// 描画
	void Draw();
};

// UI描画クラス(リザルトシーン用)
class UIDrawerResultScene : public AbstractUIDrawer
{
private:
	ScoreGauge scoreGauge; 
	RankAnimation rankAnimation;

public:
	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 描画(オーバーライド)
	void Draw();
};