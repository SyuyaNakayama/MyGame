#pragma once
#include "BaseScene.h"
#include "Sprite.h"
#include "Stage.h"
#include "CameraShake.h"

// タイトルシーンの処理
class TitleScene : public WristerEngine::BaseScene
{
	Stage stage;
	WristerEngine::_3D::Camera camera;

	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 終了
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTitleScene : public WristerEngine::_2D::AbstractUIDrawer
{
	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
	void Draw() override;
};