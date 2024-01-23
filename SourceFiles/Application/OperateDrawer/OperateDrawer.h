#pragma once
#include "AbstractUIDrawer.h"

// ‘€ì•û–@‚ğ•`‰æ‚·‚é
class OperateDrawer : public WristerEngine::_2D::AbstractUIDrawer
{
private:

public:
	// AbstractUIDrawer ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Initialize() override;
	void Update() override;
	void Draw() override;
};