#pragma once
#include "ScoreGauge.h"
#include "Easing.h"

// ランクアニメーション基底クラス
class BaseAnimation
{
public:
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
};

// ランクとスコアの判定
class JudgeAnimation : public BaseAnimation
{
	// BaseAnimation を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

// 消える
class DisappearAnimation : public BaseAnimation
{
	// BaseAnimation を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

// 現れる
class AppearAnimation : public BaseAnimation
{
	// BaseAnimation を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

// 最終ランク発表
class ResultAnimation : public BaseAnimation
{
	// BaseAnimation を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
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
	void Judge();
	void Disappear();
	void Appear();
	void Result();

public:
	// 初期化
	void Initialize(const ScoreGauge* pScoreGauge);
	// 更新
	void Update();
	// 描画
	void Draw();
};