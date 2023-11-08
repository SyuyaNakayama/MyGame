#pragma once
#include "BaseScene.h"
#include "BitMapNumber.h"
#include "Easing.h"
#include <map>

// UI描画クラス(リザルトシーン用)
class UIDrawerResultScene : public AbstractUIDrawer
{
private:
	// ランクと点数
	static const int GAUGE_MAX_SCORE = 3000;
	const Vector2 GAUGE_SIZE = { 641,40 };
	const int GAUGE_INC_SPD = 15; // ゲージ上昇速度
	const int RANK_ANIMATION_TIME = 10;

	enum class Rank
	{
		MAX = GAUGE_MAX_SCORE,
		S = Rank::MAX * 9 / 10,
		A = Rank::MAX * 7 / 10,
		B = Rank::MAX * 5 / 10,
		C = Rank::MAX * 0 / 10
	};

	std::unique_ptr<Sprite> scoreUI;
	int score = 0;
	int printScore = 0; // 今表示されてるゲージ量
	BitMapNumber printScoreUI; // 今表示されてるゲージ量のUI

	std::unique_ptr<Sprite> rankGauge;
	std::unique_ptr<Sprite> rankGaugeBG;
	std::unique_ptr<Sprite> resultRankSprite;
	std::map<Rank, std::unique_ptr<Sprite>> rankGaugeSplit;
	std::map<Rank, std::unique_ptr<Sprite>> rankUI;
	std::unique_ptr<Sprite> blind; // 画面を暗くする
	Rank preRank;
	Easing rankSpriteFade;
	Easing rankSpriteScale;
	Vector2 rankSpriteSizeMem;

	// スコア表示関連の初期化
	void ScoreInitialize();
	// スコア表示関連の更新
	void ScoreUpdate();
	// スコアをモニター座標に変換
	float ScoreToMoniter(int score_) { return min((float)score_ * GAUGE_SIZE.x / GAUGE_MAX_SCORE, GAUGE_SIZE.x); }
	// ランク表示関連の初期化
	void RankInitialize();
	// ランク表示関連の更新
	void RankUpdate();
	// ランクアニメーションの関数ポインタ
	void (UIDrawerResultScene::* RankAnimation)() = &UIDrawerResultScene::Judge;
	// ランクとスコアの判定
	void Judge();
	// 消える
	void Disappear();
	// 現れる
	void Appear();
	// 最終ランク発表
	void Result();
	// ランクを取得
	Rank GetRank(int score);

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