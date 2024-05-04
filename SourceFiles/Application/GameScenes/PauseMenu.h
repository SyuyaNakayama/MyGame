#pragma once
#include "BasePauseMenu.h"
#include "OperateConfig.h"

// �ݒ荀�ڊ��N���X
class BaseItem : public WristerEngine::_2D::AbstractUIDrawer
{
public:
	virtual ~BaseItem() = default;

	// AbstractUIDrawer ����Čp������܂���
	virtual void Initialize() override;
	virtual void Update() override { for (auto& s : sprites) { s.second->Draw(); } }
	void Draw() override { for (auto& s : sprites) { s.second->Draw(); } }
};

class CameraModeItem : public BaseItem
{
	
	void Initialize() override;
	void Update() override;
};

class PauseMenu final : public WristerEngine::BasePauseMenu
{
	OperateConfig* operateConfig = OperateConfig::GetInstance();
	std::vector<std::unique_ptr<BaseItem>> items; // �ݒ荀��

	PauseMenu() = default;
	~PauseMenu() = default;

public:
	PauseMenu(const PauseMenu& obj) = delete;
	const PauseMenu& operator=(const PauseMenu& obj) = delete;

	static PauseMenu* GetInstance();

	// BasePauseMenu ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};