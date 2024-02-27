#pragma once
#include "OperateDrawer.h"
#include "Stage.h"
#include "BitMapNumber.h"

// チュートリアルとプレイシーンで共有しているもの
class PlayMode : public OperateDrawer
{
private:
	std::unique_ptr<WristerEngine::_2D::Sprite> uiScore;
	WristerEngine::_2D::BitMapNumber scoreSprite;

protected:
	Stage* stage;

	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 描画(オーバーライド)
	void Draw();
};