#pragma once
#include "BaseScene.h"
#include "SpriteAnimation.h"
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
	std::map<std::string, std::unique_ptr<WristerEngine::_2D::Sprite>> title;
	std::unique_ptr<WristerEngine::_2D::SpriteAnimation> operateKey;
	std::unique_ptr<WristerEngine::_2D::Sprite> selectCursorUI;
	Angle cosAngle = 0;

	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};