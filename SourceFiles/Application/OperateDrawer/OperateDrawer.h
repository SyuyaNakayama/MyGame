#pragma once
#include "AbstractUIDrawer.h"

// ������@��`�悷��
class OperateDrawer : public WristerEngine::_2D::AbstractUIDrawer
{
private:

public:
	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};