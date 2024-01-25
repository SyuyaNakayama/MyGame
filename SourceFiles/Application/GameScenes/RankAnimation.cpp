#include "RankAnimation.h"
#include "Input.h"

using namespace WristerEngine::_2D;

void RankAnimation::ChangePhase()
{
	if (nextPhase == AnimationPhase::Null) { return; }
	animation.release();

	switch (nextPhase)
	{
	case AnimationPhase::Judge:
		animation = std::make_unique<JudgeAnimation>();
		break;
	case AnimationPhase::Disappear:
		animation = std::make_unique<DisappearAnimation>();
		break;
	case AnimationPhase::Appear:
		animation = std::make_unique<AppearAnimation>();
		break;
	case AnimationPhase::Result:
		animation = std::make_unique<ResultAnimation>();
		break;
	case AnimationPhase::End:
		animation = std::make_unique<AnimationEnd>();
		break;
	}
	animation->Initialize(this);
	nextPhase = AnimationPhase::Null;
}

void RankAnimation::Initialize(const ScoreGauge* pScoreGauge_)
{
	animation = std::make_unique<JudgeAnimation>();
	pScoreGauge = pScoreGauge_;
	animation->Initialize(this);
}

void RankAnimation::Update()
{
	ChangePhase();
	// ランク表示UIのアニメーション
	animation->Update();
}

void RankAnimation::Draw()
{
	animation->Draw();
}

void BaseAnimation::Initialize(RankAnimation* pRankAnimation_)
{
	pRankAnimation = pRankAnimation_;
	pScoreGauge = pRankAnimation_->GetScoreGauge();
	CreateRankUI(pScoreGauge->GetRank());
}

void BaseAnimation::CreateRankUI(Rank rank)
{
	switch (rank)
	{
	case Rank::Max:
	case Rank::S:
		rankUI = Sprite::Create("ui/Rank/RankS.png");
		break;
	case Rank::A:
		rankUI = Sprite::Create("ui/Rank/RankA.png");
		break;
	case Rank::B:
		rankUI = Sprite::Create("ui/Rank/RankB.png");
		break;
	case Rank::C:
		rankUI = Sprite::Create("ui/Rank/RankC.png");
		break;
	}
	rankUI->SetCenterAnchor();
	rankUI->position = { 1030,Half(WristerEngine::WIN_SIZE.y) };
}

void JudgeAnimation::Initialize(RankAnimation* pRankAnimation_)
{
	BaseAnimation::Initialize(pRankAnimation_);
	preRank = pScoreGauge->GetRank();
	rankUI->Update();
}

void JudgeAnimation::Update()
{
	// ランクが変わったらランク表示UIのアニメーションをする
	if (preRank != pScoreGauge->GetRank()) { pRankAnimation->ReservePhase(AnimationPhase::Disappear); }
	// スコア上昇のアニメーションが終わったら最終ランク演出を出す
	if (pScoreGauge->IsAnimationEnd()) { pRankAnimation->ReservePhase(AnimationPhase::Result); }
	preRank = pScoreGauge->GetRank();
}

void DisappearAnimation::Initialize(RankAnimation* pRankAnimation_)
{
	BaseAnimation::Initialize(pRankAnimation_);
	rankUI.release();
	CreateRankUI(pScoreGauge->GetPreRank());
	rankSpriteFade.Initialize(RANK_ANIMATION_TIME, WristerEngine::Easing::Type::Sqrt);
}

void DisappearAnimation::Update()
{
	rankUI->color.a = WristerEngine::Color::MAX - rankSpriteFade.Update(); // 透明に
	// アニメーション終了
	if (rankSpriteFade.IsFinish()) { pRankAnimation->ReservePhase(AnimationPhase::Appear); }
	rankUI->Update();
}

void AppearAnimation::Initialize(RankAnimation* pRankAnimation_)
{
	BaseAnimation::Initialize(pRankAnimation_);
	rankSpriteFade.Initialize(RANK_ANIMATION_TIME, WristerEngine::Easing::Type::Sqrt);
	rankSpriteScale.Initialize(RANK_ANIMATION_TIME, WristerEngine::Easing::Type::OutBounce);
	rankSpriteSizeMem = rankUI->size;
}

void AppearAnimation::Update()
{
	rankUI->color.a = rankSpriteFade.Update(); // 濃く
	const float SIZE_RATE = 3.0f;
	rankUI->size = rankSpriteSizeMem * (SIZE_RATE - (SIZE_RATE - 1.0f) * rankSpriteScale.Update());
	// アニメーション終了
	if (rankSpriteFade.IsFinish()) { pRankAnimation->ReservePhase(AnimationPhase::Judge); }
	rankUI->Update();
}

void ResultAnimation::Initialize(RankAnimation* pRankAnimation_)
{
	BaseAnimation::Initialize(pRankAnimation_);
	rankUI->Update();

	// ランク発表時に背景を暗くするためのスプライト
	blind = Sprite::Create("white1x1.png");
	blind->size = WristerEngine::WIN_SIZE;
	blind->color = { 0,0,0,0.5f };
}

void ResultAnimation::Update()
{
	resultRankSprite = Sprite::Create(rankUI->tex->fileName);
	resultRankSprite->SetCenterAnchor();
	resultRankSprite->SetCenterPos();
	resultRankSprite->size *= 4.0f;
	blind->Update();
	resultRankSprite->Update();
	if (WristerEngine::Input::GetInstance()->IsTrigger(WristerEngine::Key::Return))
	{
		pRankAnimation->ReservePhase(AnimationPhase::End);
	}
}

void ResultAnimation::Draw()
{
	rankUI->Draw();
	blind->Draw();
	resultRankSprite->Draw();
}

void AnimationEnd::Initialize(RankAnimation* pRankAnimation_)
{
	BaseAnimation::Initialize(pRankAnimation_);
	rankUI->Update();
}