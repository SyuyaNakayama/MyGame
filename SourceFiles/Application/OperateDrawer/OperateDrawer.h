#pragma once
#include "AbstractUIDrawer.h"

// 操作方法を描画する
class OperateDrawer : public WristerEngine::_2D::AbstractUIDrawer
{
private:

public:
	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};