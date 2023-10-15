#pragma once
#include "BaseScene.h"
#include "Sprite.h"

// 結果発表シーンの処理
class ResultScene : public BaseScene
{
	std::unique_ptr<Sprite> sprite;

	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 描画(オーバーライド)
	void Draw();
};