#pragma once
#include "ScoreGauge.h"
#include "Easing.h"

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