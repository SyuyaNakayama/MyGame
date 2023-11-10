#pragma once
#include "ScoreGauge.h"
#include "Easing.h"

enum class AnimationPhase { Null, Judge, Disappear, Appear, Result, End };
// 前方定義
class RankAnimation;

// ランクアニメーション基底クラス
class BaseAnimation
{
protected:
	const int RANK_ANIMATION_TIME = 10;
	const ScoreGauge* pScoreGauge = nullptr;
	RankAnimation* pRankAnimation = nullptr;
	std::unique_ptr<Sprite> rankUI;

public:
	// 仮想デストラクタ
	virtual ~BaseAnimation() = default;
	// 初期化
	virtual void Initialize(RankAnimation* pRankAnimation);
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
	// ランクスプライトの生成
	void CreateRankUI(Rank rank);
};

// ランクとスコアの判定
class JudgeAnimation : public BaseAnimation
{
	Rank preRank;

	// BaseAnimation を介して継承されました
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
	void Draw() override;
};

// 消える
class DisappearAnimation : public BaseAnimation
{
	Easing rankSpriteFade;
	Easing rankSpriteScale;

	// BaseAnimation を介して継承されました
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
	void Draw() override;
};

// 現れる
class AppearAnimation : public BaseAnimation
{
	Vector2 rankSpriteSizeMem;
	Easing rankSpriteFade;
	Easing rankSpriteScale;

	// BaseAnimation を介して継承されました
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
	void Draw() override;
};

// 最終ランク発表
class ResultAnimation : public BaseAnimation
{
	std::unique_ptr<Sprite> blind; // 画面を暗くする
	std::unique_ptr<Sprite> resultRankSprite;

	// BaseAnimation を介して継承されました
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override;
	void Draw() override;
};

// アニメーション終了
class AnimationEnd : public BaseAnimation
{
	// BaseAnimation を介して継承されました
	void Initialize(RankAnimation* pRankAnimation) override;
	void Update() override {};
	void Draw() override { rankUI->Draw(); };
};

// ランクUIのアニメーション
class RankAnimation
{
private:
	AnimationPhase nextPhase = AnimationPhase::Null;
	const ScoreGauge* pScoreGauge = nullptr;

	// アニメーションクラス
	std::unique_ptr<BaseAnimation> animation;

	// アニメーションフェーズの切り替え
	void ChangePhase();

public:
	// 初期化
	void Initialize(const ScoreGauge* pScoreGauge);
	// 更新
	void Update();
	// 描画
	void Draw();
	// 次のアニメーションフェーズの予約
	void ReservePhase(AnimationPhase next) { nextPhase = next; }
	// スコアゲージクラスのポインタを取得
	const ScoreGauge* GetScoreGauge() { return pScoreGauge; }
};