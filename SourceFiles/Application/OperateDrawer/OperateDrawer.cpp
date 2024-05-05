#include "OperateDrawer.h"
#include "Input.h"

using namespace WristerEngine::_2D;

void OperateDrawer::Initialize()
{
	sprites["01_frame"] = Sprite::Create("UI/uiFrame.png", Const(Vector2, "OperateFramePos"));
	sprites["01_frame"]->size = Const(Vector2, "OperateFrameSize");
	using Key = WristerEngine::Key;

	// 操作キーの画像の読み込みと位置調整
	mapChip = std::make_unique<MapChip>();
	mapChip->Initialize(Const(Vector2, "ChipLTPos"), Const(Vector2, "ChipSize"), Const(Vector2, "ChipAnchor"));
	if (!WristerEngine::Input::GetInstance()->IsConnectGamePad())
	{
		// キーボード操作の時
		mapChip->AddSprite("UI/Key/key_A.png", { 0,1 });
		mapChip->AddSprite("UI/Key/key_D.png", { 2,1 });
		mapChip->AddSprite("UI/Key/key_W.png", { 1,0 });
		mapChip->AddSprite("UI/Key/key_S.png", { 1,1 });
		mapChip->AddSprite("UI/Key/key_Left.png", { 0.5f,2.5f });
		mapChip->AddSprite("UI/Key/key_Right.png", { 1.5f,2.5f });
		mapChip->AddSprite("UI/Key/key_SHIFT.png", { 1,4 });
	}
	else
	{
		// パッド操作の時
		mapChip->AddSprite("UI/Key/stick_L.png", { 1,0.5f }, 1.0f);
		mapChip->AddSprite("UI/Key/stick_R.png", { 1,2.5f }, 1.0f);
		mapChip->AddSprite("UI/Key/button_B.png", { 1,4 });
	}

	sprites["player"] = Sprite::Create("UI/Move.png", Const(Vector2, "UiPlayerStringPos"), { 0,0.5f });
	sprites["camera"] = Sprite::Create("UI/Camera.png", Const(Vector2, "UiCameraStringPos"), { 0,0.5f });
	sprites["dash"] = Sprite::Create("UI/Dash.png", Const(Vector2, "UiDashStringPos"), { 0,0.5f });
}

void OperateDrawer::Update()
{
	mapChip->Update();
}

void OperateDrawer::Draw()
{
	AbstractUIDrawer::Draw();
	mapChip->Draw();
}