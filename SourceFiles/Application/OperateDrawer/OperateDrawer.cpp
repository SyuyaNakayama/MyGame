#include "OperateDrawer.h"
#include "Constant.h"

using namespace WristerEngine::_2D;

void OperateDrawer::Initialize()
{
	WristerEngine::Constant* constant = WristerEngine::Constant::GetInstance();

	frame = Sprite::Create("UI/uiFrame.png");
	frame->position = constant->GetConstant<Vector2>("OperateFramePos");
	frame->size = constant->GetConstant<Vector2>("OperateFrameSize");
	frame->Update();
	using Key = WristerEngine::Key;

	keyUI[Key::A] = Sprite::Create("UI/Key/key_A.png");
	keyUI[Key::D] = Sprite::Create("UI/Key/key_D.png");
	keyUI[Key::W] = Sprite::Create("UI/Key/key_W.png");
	keyUI[Key::S] = Sprite::Create("UI/Key/key_S.png");

	keyUI[Key::Left] = Sprite::Create("UI/Key/key_Left.png");
	keyUI[Key::Right] = Sprite::Create("UI/Key/key_Right.png");
	keyUI[Key::Up] = Sprite::Create("UI/Key/key_Up.png");
	keyUI[Key::Down] = Sprite::Create("UI/Key/key_Down.png");


	for (auto& s : keyUI)
	{
		s.second->textureSize.x /= 2.0f;
		s.second->size.x /= 2.0f;
		s.second->position = frame->position;
	}

	keyUI[Key::Rshift] = Sprite::Create("UI/Key/key_SHIFT.png",
		constant->GetConstant<Vector2>("UiShiftPos"), { 0.5f,0.5f });
	keyUI[Key::Rshift]->textureSize.x /= 2.0f;
	keyUI[Key::Rshift]->size.x /= 2.0f;

	const float UI_POS_COMPRESS = constant->GetConstant<float>("UiPosCompress"); // 操作UI間の距離を圧縮するための変数

	keyUI[Key::A]->position += { UI_POS_COMPRESS, keyUI[Key::A]->size.y };
	keyUI[Key::D]->position += { keyUI[Key::D]->size.x * 2.0f - UI_POS_COMPRESS, keyUI[Key::D]->size.y };
	keyUI[Key::W]->position += { keyUI[Key::W]->size.x, UI_POS_COMPRESS };
	keyUI[Key::S]->position += { keyUI[Key::S]->size.x, keyUI[Key::S]->size.y };

	std::map<Key, Key> keyPair =
	{
		{Key::Left,Key::A},
		{Key::Right,Key::D},
		{Key::Up,Key::W},
		{Key::Down,Key::S},
	};

	for (auto& pair : keyPair)
	{
		keyUI[pair.first]->position = keyUI[pair.second]->position;
		// キー操作UIとアローUI間の距離を足す
		keyUI[pair.first]->position.y += constant->GetConstant<float>("DistanceKeyArrow");
	}

	operateUI["player"] = Sprite::Create("UI/Move.png");
	operateUI["player"]->anchorPoint.y = 0.25f;
	operateUI["player"]->position = { keyUI[Key::D]->position.x, keyUI[Key::W]->position.y };
	operateUI["player"]->position += { keyUI[Key::D]->size.x, Half(keyUI[Key::D]->size.y) };

	operateUI["camera"] = Sprite::Create("UI/Camera.png");
	operateUI["camera"]->anchorPoint.y = 0.25f;
	operateUI["camera"]->position = { keyUI[Key::Right]->position.x, keyUI[Key::Up]->position.y };
	operateUI["camera"]->position += { keyUI[Key::D]->size.x, Half(keyUI[Key::D]->size.y) };

	operateUI["dash"] = Sprite::Create("UI/Dash.png");
	operateUI["dash"]->anchorPoint.y = 0.5f;
	operateUI["dash"]->position = keyUI[Key::Rshift]->position;
	operateUI["dash"]->position.x += Half(keyUI[Key::Rshift]->size.x);

	for (auto& s : operateUI) { s.second->Update(); }

	mapChip = std::make_unique<MapChip>();
	mapChip->Initialize(Const(Vector2, "ChipLTPos"), Const(Vector2, "ChipSize"), Const(Vector2, "ChipAnchor"));
	mapChip->AddSprite("UI/Key/key_A.png", { 0,1 });
}

void OperateDrawer::Update()
{
	WristerEngine::Input* input = WristerEngine::Input::GetInstance();
	for (auto& s : keyUI)
	{
		// キーを押したらレクト位置を変える
		s.second->textureLeftTop.x = input->IsInput(s.first) * s.second->textureSize.x;
		// LShiftにも対応させる
		if (s.first == WristerEngine::Key::Rshift && input->IsInput(WristerEngine::Key::Lshift))
		{
			s.second->textureLeftTop.x = input->IsInput(WristerEngine::Key::Lshift) * s.second->textureSize.x;
		}
		s.second->Update();
	}
	mapChip->Update();
}

void OperateDrawer::Draw()
{
	frame->Draw();
	for (auto& s : keyUI) { s.second->Draw(); }
	for (auto& s : operateUI) { s.second->Draw(); }
	mapChip->Draw();
}
