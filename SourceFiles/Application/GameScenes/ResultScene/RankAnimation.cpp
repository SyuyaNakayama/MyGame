#include "RankAnimation.h"
#include "Input.h"
#include "OperateConfig.h"

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
	// イージングの初期化
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

	rankUI->SetCenterPos();
	rankSpriteSizeMem = rankUI->size * 6.0f;
	rankSpriteScale.Initialize(RANK_ANIMATION_TIME * 6, WristerEngine::Easing::Type::OutBounce);

	operateKey = operateConfig->CreateOperateSpriteAnimation("Select");
	operateKey->GetSprite()->SetCenterAnchor();
	operateKey->GetSprite()->position = { Half(WristerEngine::WIN_SIZE.x),640 };
	if (!WristerEngine::Input::GetInstance()->IsConnectGamePad()) { operateKey->GetSprite()->size *= 2.0f; }

	// ランク発表時に背景を暗くするためのスプライト
	blind = Sprite::Create("white1x1.png");
	blind->size = WristerEngine::WIN_SIZE;
	blind->color = { 0,0,0,0.5f };
	blind->Update();

	Phase = &ResultAnimation::PrePushSelect;
}

void ResultAnimation::Update()
{
	(this->*Phase)();
	rankUI->Update();
}

void ResultAnimation::PrePushSelect()
{
	rankUI->size = rankSpriteSizeMem * rankSpriteScale.Update();
	operateKey->Update();

	if (operateConfig->GetTrigger("Select"))
	{
		operateKey->GetSprite()->isInvisible = true;
		rankSpriteScale.Restart();
		Phase = &ResultAnimation::PostPushSelect;
	}
}

void ResultAnimation::PostPushSelect()
{
	rankUI->size = rankSpriteSizeMem * (1.0f - rankSpriteScale.Update());
	if (rankSpriteScale.IsFinish()) { pRankAnimation->ReservePhase(AnimationPhase::End); }
}

void ResultAnimation::Draw()
{
	blind->Draw();
	rankUI->Draw();
	operateKey->Draw();
}

void AnimationEnd::Initialize(RankAnimation* pRankAnimation_)
{
	BaseAnimation::Initialize(pRankAnimation_);

	operateKey = operateConfig->CreateOperateSpriteAnimation("SceneChange");
	Sprite* spaceKeySprite = operateKey->GetSprite();
	spaceKeySprite->position = Half(WristerEngine::WIN_SIZE);
	spaceKeySprite->position.y += 80;
	spaceKeySprite->size *= 1.5f;
	spaceKeySprite->anchorPoint.x = 0.5f;
	spaceKeySprite->color = { 0.7f,0.7f,0.7f,1 };

	rankUI->Update();
}

void AnimationEnd::Update() { operateKey->Update(); }

void AnimationEnd::Draw() { operateKey->Draw(); }