#pragma once
#include "AbstractUIDrawer.h"
#include "MapChip.h"

// ������@��`�悷��
class OperateDrawer : public WristerEngine::_2D::AbstractUIDrawer
{
protected:
	std::unique_ptr<WristerEngine::_2D::BaseMapChip> mapChip;

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};