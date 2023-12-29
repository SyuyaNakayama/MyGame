#pragma once
#include "BaseScene.h"
#include "SpriteAnimation.h"
#include "Stage.h"

// タイトルシーンの処理
class TitleScene : public BaseScene
{
	Stage stage;
	ViewProjection camera;

	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 終了
	void Finalize() { stage.Finalize(); }
};

class UIDrawerTitleScene : public AbstractUIDrawer
{
	std::map<std::string, std::unique_ptr<Sprite>> title;
	SpriteAnimation spaceKey;
	std::unique_ptr<Sprite> selectCursorUI;
	Angle cosAngle = 0;
	std::unique_ptr<Sprite> sprite;

	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};