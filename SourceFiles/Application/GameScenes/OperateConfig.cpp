#include "OperateConfig.h"

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
