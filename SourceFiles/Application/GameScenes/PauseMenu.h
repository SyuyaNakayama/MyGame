#pragma once
#include "BasePauseMenu.h"
#include "OperateConfig.h"

// �ݒ荀�ڊ��N���X
class BaseItem : WristerEngine::_2D::AbstractUIDrawer
{
private:


public:
	virtual ~BaseItem() = default;

	// AbstractUIDrawer ����Čp������܂���
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

class PauseMenu final : public WristerEngine::BasePauseMenu
{
	OperateConfig* operateConfig = OperateConfig::GetInstance();

	PauseMenu() = default;
	~PauseMenu() = default;

public:
	PauseMenu(const PauseMenu& obj) = delete;
	const PauseMenu& operator=(const PauseMenu& obj) = delete;

	static PauseMenu* GetInstance();

	// BasePauseMenu ����Čp������܂���
	void Initialize() override;
	void Update() override;
};