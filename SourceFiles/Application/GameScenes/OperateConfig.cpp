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
	else if (str == "Left")
	{
		key = input->IsInput(Key::Left);
		if (input->IsConnectGamePad())
		{
			float horizontal = input->ConLStick(1.0f).x;
			pad = horizontal < 0.0f;
		}
	}
	else if (str == "Right")
	{
		key = input->IsInput(Key::Right);
		if (input->IsConnectGamePad())
		{
			float horizontal = input->ConLStick(1.0f).x;
			pad = horizontal > 0.0f;
		}
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
	else if (str == "Left")
	{
		key = input->IsTrigger(Key::Left);
		if (input->IsConnectGamePad())
		{
			float horizontal = input->ConLStick(1.0f).x;
			pad = horizontal < 0.0f;
		}
	}
	else if (str == "Right")
	{
		key = input->IsTrigger(Key::Right);
		if (input->IsConnectGamePad())
		{
			float horizontal = input->ConLStick(1.0f).x;
			pad = horizontal > 0.0f;
		}
	}
	else if (str == "Up")
	{
		key = input->IsTrigger(Key::Up);
		if (input->IsConnectGamePad())
		{
			float vertical = input->ConLStick(1.0f).y;
			pad = vertical > 0.0f;
		}
	}
	else if (str == "Down")
	{
		key = input->IsTrigger(Key::Down);
		if (input->IsConnectGamePad())
		{
			float vertical = input->ConLStick(1.0f).y;
			pad = vertical < 0.0f;
		}
	}
	else if (str == "Left")
	{
		key = input->IsTrigger(Key::Left);
		if (input->IsConnectGamePad())
		{
			float horizontal = input->ConLStick(1.0f).x;
			pad = horizontal < 0.0f;
		}
	}
	else if (str == "Right")
	{
		key = input->IsTrigger(Key::Right);
		if (input->IsConnectGamePad())
		{
			float horizontal = input->ConLStick(1.0f).x;
			pad = horizontal > 0.0f;
		}
	}

	return key || pad;
}

std::unique_ptr<Sprite> OperateConfig::LoadSprite(const std::string& str)
{
	std::unique_ptr<Sprite> sprite;
	if (str == "Select")
	{
		if (!input->IsConnectGamePad()) 
		{
			sprite = Sprite::Create("UI/Key/key_enter.png"); 
			sprite->size *= 0.5f;
		}
		else { sprite = Sprite::Create("UI/Key/button_A.png"); }
	}
	else if (str == "SceneChange")
	{
		if (!input->IsConnectGamePad()) { sprite = Sprite::Create("UI/Key/key_SPACE.png"); }
		else { sprite = Sprite::Create("UI/Key/button_X.png"); }
	}
	else if (str == "Pause")
	{
		if (!input->IsConnectGamePad()) { sprite = Sprite::Create("UI/Key/key_H.png"); }
		else { sprite = Sprite::Create("UI/Key/button_Y.png"); }
	}
	return sprite;
}

std::unique_ptr<Sprite> OperateConfig::CreateOperateSprite(const std::string& str)
{
	std::unique_ptr<Sprite> sprite;
	if (str == "Select")
	{
		if (!input->IsConnectGamePad())
		{
			sprite = Sprite::Create("UI/Key/key_enter.png");
			sprite->Split({ 2,1 });
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
	else if (str == "Pause")
	{
		if (!input->IsConnectGamePad())
		{
			sprite = Sprite::Create("UI/Key/key_H.png");
			sprite->Split({ 2,1 });
		}
		else
		{
			sprite = Sprite::Create("UI/Key/button_Y.png");
			sprite->Split({ 2,1 });
		}
	}
	return sprite;
}

std::unique_ptr<Sprite> OperateConfig::CreateOperateSpriteAnimation(const std::string& str)
{
	std::unique_ptr<Sprite> sprite = LoadSprite(str);
	int aInterval = Const(int, "SpriteAnimationInterval");
	sprite->SetAnimation(2, aInterval);
	return sprite;
}
