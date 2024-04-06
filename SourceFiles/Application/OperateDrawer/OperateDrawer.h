#pragma once
#include "AbstractUIDrawer.h"
#include "MapChip.h"
#include "Sprite.h"
#include "Input.h"
#include <map>

// ������@��`�悷��
class OperateDrawer : public WristerEngine::_2D::AbstractUIDrawer
{
protected:
	std::map<std::string, std::unique_ptr<WristerEngine::_2D::Sprite>> operateUI;
	std::map<WristerEngine::Key, std::unique_ptr<WristerEngine::_2D::Sprite>> keyUI;
	std::unique_ptr<WristerEngine::_2D::Sprite> frame;
	std::unique_ptr<WristerEngine::_2D::BaseMapChip> mapChip;

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};