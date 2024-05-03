#pragma once
#include "OperateDrawer.h"
#include "Stage.h"
#include "BitMapNumber.h"

// チュートリアルとプレイシーンで共有しているもの
class PlayMode : public OperateDrawer
{
private:
	WristerEngine::_2D::BitMapNumber scoreSprite;

protected:
	Stage* stage = nullptr;

	// 初期化(オーバーライド)
	void Initialize();
	// 更新(オーバーライド)
	void Update();
	// 描画(オーバーライド)
	void Draw();
};