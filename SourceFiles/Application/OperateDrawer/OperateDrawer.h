#pragma once
#include "AbstractUIDrawer.h"
#include "MapChip.h"

// ‘€ì•û–@‚ğ•`‰æ‚·‚é
class OperateDrawer : public WristerEngine::_2D::AbstractUIDrawer
{
protected:
	std::unique_ptr<WristerEngine::_2D::BaseMapChip> mapChip;

	// AbstractUIDrawer ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() override;
};