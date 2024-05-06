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

	// ポーズメニュー
	sprites["PauseIcon"] = Sprite::Create("UI/PauseIcon.png", Const(Vector2, "PauseIconPos"));
	sprites["PauseIcon"]->size = { 64,64 };
	sprites["PauseKey"] = OperateConfig::GetInstance()->CreateOperateSprite("Pause");
	sprites["PauseKey"]->position = Const(Vector2, "PauseKeyPos");
	sprites["PauseKey"]->size = { 64,64 };
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