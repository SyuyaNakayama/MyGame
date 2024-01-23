#pragma once
#include "AbstractUIDrawer.h"
#include <map>
#include <Sprite.h>
#include <Input.h>

// 操作方法を描画する
class OperateDrawer : public WristerEngine::_2D::AbstractUIDrawer
{
protected:
	std::map<std::string, std::unique_ptr<WristerEngine::_2D::Sprite>> operateUI;
	std::map<WristerEngine::Key, std::unique_ptr<WristerEngine::_2D::Sprite>> keyUI;
	std::unique_ptr<WristerEngine::_2D::Sprite> frame;

public:
	// AbstractUIDrawer を介して継承されました
	void Initialize() override;
	void Update() override;
	void Draw() override;
};