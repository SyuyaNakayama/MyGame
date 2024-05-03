#pragma once
#include "BasePauseMenu.h"
#include "OperateConfig.h"

// 設定項目基底クラス
class BaseItem : WristerEngine::_2D::AbstractUIDrawer
{
private:


public:
	virtual ~BaseItem() = default;

	// AbstractUIDrawer を介して継承されました
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

	// BasePauseMenu を介して継承されました
	void Initialize() override;
	void Update() override;
};