#include "PlayMode.h"
#include "Constant.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void PlayMode::Initialize()
{
	OperateDrawer::Initialize();

	// スコア
	*scoreSprite.GetBitMapProp() = Const(BitMapProp, "UiScore");
	scoreSprite.GetBitMapProp()->fileName = "ui/num.png";
	scoreSprite.Initialize();
	sprites["Score"] = Sprite::Create("ui/score.png", Const(Vector2, "UiScorePosition"), { 0.5f,0.5f });
}

void PlayMode::Update()
{
	// ポーズメニュー切り替え
	if (OperateConfig::GetInstance()->GetTrigger("Pause"))
	{
		WristerEngine::SceneManager::GetInstance()->Pause();
		return;
	}

	OperateDrawer::Update();
	scoreSprite.Update(stage->GetScore());
}

void PlayMode::Draw()
{
	OperateDrawer::Draw();
	scoreSprite.Draw();
}