#include "ScoreGauge.h"

Rank ScoreGauge::GetRank() const
{
	if (printScore >= (int)Rank::S) { return Rank::S; }
	if (printScore >= (int)Rank::A) { return Rank::A; }
	if (printScore >= (int)Rank::B) { return Rank::B; }
	return Rank::C;
}

Rank ScoreGauge::GetPreRank() const
{
	switch (GetRank())
	{
	case Rank::Max:
	case Rank::S:
		return Rank::A;
	case Rank::A:
		return Rank::B;
	case Rank::B:
	case Rank::C:
		return Rank::C;
	}
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