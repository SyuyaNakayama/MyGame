#pragma once
#include "AbstractUIDrawer.h"
#include "MapChip.h"
#include "Sprite.h"
#include "Input.h"
#include <map>

// 操作方法を描画する
class OperateDrawer : public WristerEngine::_2D::AbstractUIDrawer
{
protected:
	std::map<std::string, std::unique_ptr<WristerEngine::_2D::Sprite>> operateUI;
	std::unique_ptr<WristerEngine::_2D::Sprite> frame;
	std::unique_ptr<WristerEngine::_2D::BaseMapChip> mapChip;

	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};