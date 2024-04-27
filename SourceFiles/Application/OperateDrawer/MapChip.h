#pragma once
#include "BaseMapChip.h"

// マップチップ描画クラス
class MapChip : public WristerEngine::_2D::BaseMapChip
{
	// BaseMapChip を介して継承されました
	void VirtualInitialize(WristerEngine::_2D::Sprite* sprite, float splitNum=2.0f) override;
	void Update() override;

};

