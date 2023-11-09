#include "RankAnimation.h"
#include "Input.h"

void RankAnimation::Judge()
{
	// ランクが変わったらランク表示UIのアニメーションをする
	if (preRank != pScoreGauge->GetPrintRank()) { Animation = &RankAnimation::Disappear; }
	// スコア上昇のアニメーションが終わったら最終ランク演出を出す
	if (pScoreGauge->IsAnimationEnd()) { Animation = &RankAnimation::Result; }
}

void RankAnimation::Disappear()
{
	// アニメーションするランクUIのペア
	std::map<Rank, Rank> animationPair;
	animationPair[Rank::B] = Rank::C;
	animationPair[Rank::A] = Rank::B;
	animationPair[Rank::S] = Rank::A;

	Rank printRank = pScoreGauge->GetPrintRank(); // 表示ランク
	Rank prePrintRank = animationPair[printRank]; // 前の表示ランク

	float easingRate = rankSpriteFade.Update();
	rankUI[prePrintRank]->color.a = Color::MAX - easingRate; // 透明に
	// アニメーション終了
	if (easingRate == Easing::MAX)
	{
		Animation = &RankAnimation::Appear;
		rankUI[prePrintRank]->isInvisible = true;
		rankSpriteSizeMem = rankUI[printRank]->size;
		rankSpriteFade.Restart();
	}
}

void RankAnimation::Appear()
{
	float easingRate = rankSpriteFade.Update();
	rankUI[pScoreGauge->GetPrintRank()]->color.a = easingRate; // 濃く
	const float SIZE_RATE = 3.0f;
	rankUI[pScoreGauge->GetPrintRank()]->size = rankSpriteSizeMem * (SIZE_RATE - (SIZE_RATE - 1.0f) * rankSpriteScale.Update());
	// アニメーション終了
	if (easingRate == Easing::MAX)
	{
		Animation = &RankAnimation::Judge;
		rankSpriteFade.Restart();
		rankSpriteScale.Restart();
	}
}

void RankAnimation::Result()
{
	blind->isInvisible = false;
	resultRankSprite = Sprite::Create(rankUI[pScoreGauge->GetPrintRank()]->tex->fileName);
	resultRankSprite->SetCenterAnchor();
	resultRankSprite->SetCenterPos();
	resultRankSprite->size *= 4.0f;
	if (Input::GetInstance()->IsTrigger(Key::Return))
	{
		blind->isInvisible = true;
		Animation = nullptr;
	}
}

void RankAnimation::Initialize(const ScoreGauge* pScoreGauge_)
{
	pScoreGauge = pScoreGauge_;

	// ランク発表時に背景を暗くするためのスプライト
	blind = Sprite::Create("white1x1.png");
	blind->size = WindowsAPI::WIN_SIZE;
	blind->color = { 0,0,0,0.5f };
	blind->isInvisible = true;

	// ランク表示のUI
	rankUI[Rank::S] = Sprite::Create("ui/Rank/RankS.png");
	rankUI[Rank::A] = Sprite::Create("ui/Rank/RankA.png");
	rankUI[Rank::B] = Sprite::Create("ui/Rank/RankB.png");
	rankUI[Rank::C] = Sprite::Create("ui/Rank/RankC.png");
	for (auto& s : rankUI)
	{
		s.second->SetCenterAnchor();
		s.second->position = { 1030,Half(WindowsAPI::WIN_SIZE.y) };
		s.second->color.a = 0.0f;
	}
	rankUI[Rank::C]->color.a = Color::MAX;

	rankSpriteFade.Initialize(RANK_ANIMATION_TIME, Easing::Type::Sqrt);
	rankSpriteScale.Initialize(RANK_ANIMATION_TIME, Easing::Type::OutBounce);
	preRank = pScoreGauge->GetPrintRank();
}

void RankAnimation::Update()
{
	// ランク表示UIのアニメーション
	if (Animation) { (this->*Animation)(); }

	// 各変数の更新
	preRank = pScoreGauge->GetPrintRank();
	for (auto& s : rankUI) { s.second->Update(); }
	if (blind->isInvisible) { return; }
	blind->Update();
	resultRankSprite->Update();
}

void RankAnimation::Draw()
{
	for (auto& s : rankUI) { s.second->Draw(); }
	if (blind->isInvisible) { return; }
	blind->Draw();
	resultRankSprite->Draw();
}

void JudgeAnimation::Initialize()
{
}

void JudgeAnimation::Update()
{
}

void JudgeAnimation::Draw()
{
}

void DisappearAnimation::Initialize()
{
}

void DisappearAnimation::Update()
{
}

void DisappearAnimation::Draw()
{
}

void AppearAnimation::Initialize()
{
}

void AppearAnimation::Update()
{
}

void AppearAnimation::Draw()
{
}

void ResultAnimation::Initialize()
{
}

void ResultAnimation::Update()
{
}

void ResultAnimation::Draw()
{
}
