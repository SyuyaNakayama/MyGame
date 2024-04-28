#include "OperateConfig.h"
using namespace WristerEngine::_2D;

OperateConfig* OperateConfig::GetInstance()
{
	static OperateConfig instance;
	return &instance;
}

bool OperateConfig::GetPush(const std::string& str)
{
	using Key = WristerEngine::Key;
	using Pad = WristerEngine::JoyPad;

	bool key = false, pad = false;

	if (str == "Dash")
	{
		key = input->IsInput(Key::Lshift) || input->IsInput(Key::Rshift);
		pad = false;
		if (input->IsConnectGamePad()) { pad = input->IsInput(Pad::B); }
	}
	return key || pad;
}

bool OperateConfig::GetTrigger(const std::string& str)
{
	using Key = WristerEngine::Key;
	using Pad = WristerEngine::JoyPad;

	bool key = false, pad = false;

	if (str == "Select")
	{
		key = input->IsTrigger(Key::Return);
		pad = false;
		if (input->IsConnectGamePad()) { pad = input->IsTrigger(Pad::A); }
	}
	else if (str == "SceneChange")
	{
		key = input->IsTrigger(Key::Space);
		pad = false;
		if (input->IsConnectGamePad()) { pad = input->IsTrigger(Pad::X); }
	}
	return key || pad;
}

std::unique_ptr<Sprite> OperateConfig::CreateOperateSprite(const std::string& str)
{
	std::unique_ptr<Sprite> sprite;
	if (str == "Select")
	{
	}
	else if (str == "SceneChange")
	{
	}
	return std::unique_ptr<WristerEngine::_2D::Sprite>();
}

std::unique_ptr<SpriteAnimation> OperateConfig::CreateOperateSpriteAnimation(const std::string& str)
{
	std::unique_ptr<SpriteAnimation> spriteAnimation = std::make_unique<SpriteAnimation>();
	int aInterval = Const(int, "SpriteAnimationInterval");
	if (str == "Select")
	{
		if (!input->IsConnectGamePad()) { spriteAnimation->Initialize("UI/Key/key_Enter.png", 96, aInterval); }
	}
	else if (str == "SceneChange")
	{
		if (!input->IsConnectGamePad()) { spriteAnimation->Initialize("ui/Key/key_SPACE.png", 128, aInterval); }
	}

	return spriteAnimation;
}
