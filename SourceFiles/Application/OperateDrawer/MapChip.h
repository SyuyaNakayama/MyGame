#pragma once
#include "BaseMapChip.h"

// �}�b�v�`�b�v�`��N���X
class MapChip : public WristerEngine::_2D::BaseMapChip
{
	void VirtualInitialize(WristerEngine::_2D::Sprite* sprite) override;
	void Update() override;
};

