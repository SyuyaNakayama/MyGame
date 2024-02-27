#include "PlayMode.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void PlayMode::Initialize()
{
	OperateDrawer::Initialize();

	// ビットマップの設定
	BitMapProp bitMapProp =
	{
		"ui/num.png",{30,30},{30,30},{1100,100},4
	};

	// スコア
	*scoreSprite.GetBitMapProp() = bitMapProp;
	scoreSprite.Initialize();
	uiScore = Sprite::Create("ui/score.png");
	uiScore->SetCenterAnchor();
	uiScore->position = { 1160,70 };
	uiScore->Update();
}

void PlayMode::Update()
{
	OperateDrawer::Update();
	scoreSprite.Update(stage->GetScore());
}

void PlayMode::Draw()
{
	OperateDrawer::Draw();
	scoreSprite.Draw();
	uiScore->Draw();
}