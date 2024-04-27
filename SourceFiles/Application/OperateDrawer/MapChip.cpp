#include "MapChip.h"
#include "Input.h"
#include "OperateConfig.h"

using namespace WristerEngine::_2D;

void MapChip::VirtualInitialize(Sprite* sprite, float splitNum)
{
	sprite->textureSize.x /= splitNum;
	sprite->size.x /= splitNum;
}

void MapChip::Update()
{
	WristerEngine::Input* input = WristerEngine::Input::GetInstance();
	using Key = WristerEngine::Key;

	std::vector<bool> keyInput;

	if(!input->IsConnectGamePad())
	{
		// �L�[�{�[�h����
		keyInput =
		{
			input->IsInput(Key::A),
			input->IsInput(Key::D),
			input->IsInput(Key::W),
			input->IsInput(Key::S),
			input->IsInput(Key::Left),
			input->IsInput(Key::Right),
			input->IsInput(Key::Up),
			input->IsInput(Key::Down),
			OperateConfig::GetInstance()->GetPush("Dash")
		};
	}
	else
	{
		// �Q�[���p�b�h����
		keyInput =
		{
			false,
			false,
			OperateConfig::GetInstance()->GetPush("Dash")
		};
	}

	for (size_t i = 0; i < sprites.size(); i++)
	{
		// �L�[���������烌�N�g�ʒu��ς���
		sprites[i]->textureLeftTop.x = keyInput[i] * sprites[i]->textureSize.x;
		sprites[i]->Update();
	}
}