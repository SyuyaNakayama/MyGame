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
		if (input->IsConnectGamePad()) { pad = input->IsTrigger(Pad::A); }
	}
	else if (str == "SceneChange")
	{
		key = input->IsTrigger(Key::Space);
		if (input->IsConnectGamePad()) { pad = input->IsTrigger(Pad::X); }
	}
	else if (str == "Pause")
	{
		key = input->IsTrigger(Key::H);
		if (input->IsConnectGamePad()) { pad = input->IsTrigger(Pad::Y); }
	}
	return key || pad;
}

std::unique_ptr<Sprite> OperateConfig::CreateOperateSprite(const std::string& str)
{
	std::unique_ptr<Sprite> sprite;
	if (str == "Select")
	{
		if (!input->IsConnectGamePad())
		{
			sprite = Sprite::Create("UI/Key/key_enter.png");
			sprite->SetRect({ 96,96 });
			sprite->size *= 0.5f;
		}
		else
		{
			sprite = Sprite::Create("UI/Key/button_A.png");
			sprite->Split({ 2,1 });
		}
	}
	else if (str == "SceneChange")
	{
		if (!input->IsConnectGamePad())
		{
			sprite = Sprite::Create("UI/Key/key_SPACE.png");
			sprite->Split({ 2,1 });
		}
		else
		{
			sprite = Sprite::Create("UI/Key/button_X.png");
			sprite->Split({ 2,1 });
		}
	}
	return sprite;
}

std::unique_ptr<SpriteAnimation> OperateConfig::CreateOperateSpriteAnimation(const std::string& str)
{
	std::unique_ptr<SpriteAnimation> spriteAnimation = std::make_unique<SpriteAnimation>();
	int aInterval = Const(int, "SpriteAnimationInterval");
	if (str == "Select")
	{
		if (!input->IsConnectGamePad()) 
		{
			spriteAnimation->Initialize("UI/Key/key_Enter.png", 96, aInterval); 
			spriteAnimation->GetSprite()->size *= 0.5f;
		}
		else { spriteAnimation->Initialize("ui/Key/button_A.png", 64, aInterval); }
	}
	else if (str == "SceneChange")
	{
		if (!input->IsConnectGamePad()) { spriteAnimation->Initialize("ui/Key/key_SPACE.png", 128, aInterval); }
		else { spriteAnimation->Initialize("ui/Key/button_X.png", 64, aInterval); }
	}

	return spriteAnimation;
}
