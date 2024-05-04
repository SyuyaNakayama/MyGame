#pragma once
#include "BasePauseMenu.h"
#include "OperateConfig.h"

// İ’è€–ÚŠî’êƒNƒ‰ƒX
class BaseItem : public WristerEngine::_2D::AbstractUIDrawer
{
public:
	virtual ~BaseItem() = default;

	// AbstractUIDrawer ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
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
	std::vector<std::unique_ptr<BaseItem>> items; // İ’è€–Ú

	PauseMenu() = default;
	~PauseMenu() = default;

public:
	PauseMenu(const PauseMenu& obj) = delete;
	const PauseMenu& operator=(const PauseMenu& obj) = delete;

	static PauseMenu* GetInstance();

	// BasePauseMenu ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() override;
};