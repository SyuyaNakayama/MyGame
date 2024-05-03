#pragma once
#include "BasePauseMenu.h"
#include "OperateConfig.h"

// İ’è€–ÚŠî’êƒNƒ‰ƒX
class BaseItem : WristerEngine::_2D::AbstractUIDrawer
{
private:


public:
	virtual ~BaseItem() = default;

	// AbstractUIDrawer ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
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

	// BasePauseMenu ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
};