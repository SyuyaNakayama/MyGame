#pragma once
#include "BaseMapChip.h"

// �}�b�v�`�b�v�`��N���X
class MapChip : public WristerEngine::_2D::BaseMapChip
{
	// BaseMapChip ����Čp������܂���
	void VirtualInitialize(WristerEngine::_2D::Sprite* sprite, float splitNum=2.0f) override;
	void Update() override;

};

