#pragma once
#include "BaseMapChip.h"

// マップチップ描画クラス
class MapChip : public WristerEngine::_2D::BaseMapChip
{
	void VirtualInitialize(WristerEngine::_2D::Sprite* sprite) override;
	void Update() override;
};

