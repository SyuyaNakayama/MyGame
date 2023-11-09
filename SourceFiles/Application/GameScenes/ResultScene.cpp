#include "ResultScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "Stage.h"

#pragma region ResultScene
void ResultScene::Initialize()
{
	debugCamera.Initialize();
	ModelManager::SetViewProjection(&debugCamera);

	uiDrawer = std::make_unique<UIDrawerResultScene>();
	uiDrawer->Initialize();
}

void ResultScene::Update()
{
	if (input->IsTrigger(Key::Space))
	{
		sceneManager->ChangeScene(Scene::Title);
		Stage::ResetScore();
	}

	uiDrawer->Update();
}

void ResultScene::Draw()
{
	uiDrawer->Draw();
}
#pragma endregion

#pragma region ResultScene
void UIDrawerResultScene::Initialize()
{
	// スコア表示関連の初期化
	scoreGauge.Initialize();
	// ランク表示関連の初期化
	rankAnimation.Initialize(&scoreGauge);
}

void UIDrawerResultScene::Update()
{
	// スコア表示関連の更新
	scoreGauge.Update();
	// ランク表示関連の更新
	rankAnimation.Update();
}

void UIDrawerResultScene::Draw()
{
	scoreGauge.Draw();
	rankAnimation.Draw();
}
#pragma endregion

Rank GetRank(int score)
{
	if (score >= (int)Rank::S) { return Rank::S; }
	if (score >= (int)Rank::A) { return Rank::A; }
	if (score >= (int)Rank::B) { return Rank::B; }
	return Rank::C;
}

void ScoreGauge::Initialize()
{
	// スコアを取得
	//score = Stage::GetScore();
	score = 3000;

	scoreUI = Sprite::Create("ui/score.png");
	scoreUI->SetCenterAnchor();
	scoreUI->position.y = 240;

	// ランクゲージ
	rankGauge = Sprite::Create("ui/RankGauge.png");
	rankGauge->position = Half(WindowsAPI::WIN_SIZE);
	rankGauge->SetCenterAnchor();
	rankGauge->Update();

	// ランクゲージ背景
	rankGaugeBG = Sprite::Create("white1x1.png");
	rankGaugeBG->position = Half(WindowsAPI::WIN_SIZE);
	rankGaugeBG->position.x -= 320;
	rankGaugeBG->anchorPoint = { 0.0f,0.5f };
	rankGaugeBG->size = GAUGE_SIZE;

	// ランクゲージの分割スプライト
	rankGaugeSplit[Rank::S] = Sprite::Create("white1x1.png");
	rankGaugeSplit[Rank::A] = Sprite::Create("white1x1.png");
	rankGaugeSplit[Rank::B] = Sprite::Create("white1x1.png");
	for (auto& s : rankGaugeSplit)
	{
		s.second->SetCenterAnchor();
		s.second->color = { 0,1,0,1 };
		s.second->size = { 5,GAUGE_SIZE.y };
		s.second->position = { ScoreToMoniter((int)s.first) + rankGaugeBG->position.x,rankGaugeBG->position.y };
	}

	// スコア表示のスプライト
	BitMapProp* bmProp = printScoreUI.GetBitMapProp();
	bmProp->SetVal("ui/num.png", { 30,30 }, { 30,30 }, {}, 4);
	bmProp->pos.y = rankGaugeBG->position.y - GAUGE_SIZE.y * 2.0f;
	bmProp->anchorPoint = { 0.0f,0.5f };
	printScoreUI.Initialize();
}

void ScoreGauge::Update()
{
	// ゲージを上昇させる
	if (printScore <= score) { printScore = min(printScore + GAUGE_INC_SPD, score); }

	// 表示スコアをモニター座標に変換して代入
	rankGaugeBG->size.x = ScoreToMoniter(printScore);

	// スコア表示スプライトの移動
	BitMapProp* bmProp = printScoreUI.GetBitMapProp();
	const float SCORE_UI_CENTER = bmProp->size.x * Half(bmProp->digit);
	bmProp->pos.x = -SCORE_UI_CENTER + rankGaugeBG->position.x + rankGaugeBG->size.x;
	scoreUI->position.x = bmProp->pos.x + SCORE_UI_CENTER;

	rankGaugeBG->Update();
	printScoreUI.Update(printScore);
	scoreUI->Update();
	for (auto& s : rankGaugeSplit) { s.second->Update(); }
}

void ScoreGauge::Draw()
{
	rankGauge->Draw();
	rankGaugeBG->Draw();
	for (auto& s : rankGaugeSplit) { s.second->Draw(); }
	printScoreUI.Draw();
	scoreUI->Draw();
}

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