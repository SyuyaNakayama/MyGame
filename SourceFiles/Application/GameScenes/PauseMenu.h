#pragma once
#include "BasePauseMenu.h"
#include "OperateConfig.h"

class PauseMenu final : public WristerEngine::BasePauseMenu
{
	OperateConfig* operateConfig = OperateConfig::GetInstance();

	PauseMenu() = default;
	~PauseMenu() = default;

public:
	PauseMenu(const PauseMenu& obj) = delete;
	const PauseMenu& operator=(const PauseMenu& obj) = delete;

	static PauseMenu* GetInstance();

	// BasePauseMenu ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
};