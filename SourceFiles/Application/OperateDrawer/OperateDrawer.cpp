#include "OperateDrawer.h"

using namespace WristerEngine::_2D;

void OperateDrawer::Initialize()
{
	frame = Sprite::Create("UI/uiFrame.png");
	frame->position = { 50,420 };
	frame->size = { 350,286 };
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

	const float UI_POS_COMPRESS = 10.0f; // 操作UI間の距離を圧縮するための変数
	const float DISTANCE_BETWEEN_KEY_ARROW = 148.0f; // キー操作UIとアローUI間の距離

	keyUI[Key::A]->position += { UI_POS_COMPRESS, keyUI[Key::A]->size.y };
	keyUI[Key::D]->position += { keyUI[Key::D]->size.x * 2.0f - UI_POS_COMPRESS, keyUI[Key::D]->size.y };
	keyUI[Key::W]->position += { keyUI[Key::W]->size.x, UI_POS_COMPRESS };
	keyUI[Key::S]->position += { keyUI[Key::S]->size.x, keyUI[Key::S]->size.y };

	std::map<Key, Key> keyPair =
	{
		{Key::Left,Key::A},
		{Key::Right,Key::D},
		{Key::Up,Key::W},
		{Key::Down,Key::S}
	};

	for (auto& pair : keyPair)
	{
		keyUI[pair.first]->position = keyUI[pair.second]->position;
		keyUI[pair.first]->position.y += DISTANCE_BETWEEN_KEY_ARROW;
	}

	operateUI["player"] = Sprite::Create("UI/Move.png");
	operateUI["player"]->anchorPoint.y = 0.25f;
	operateUI["player"]->position = { keyUI[Key::D]->position.x, keyUI[Key::W]->position.y };
	operateUI["player"]->position += { keyUI[Key::D]->size.x, Half(keyUI[Key::D]->size.y) };

	operateUI["camera"] = Sprite::Create("UI/Camera.png");
	operateUI["camera"]->anchorPoint.y = 0.25f;
	operateUI["camera"]->position = { keyUI[Key::Right]->position.x, keyUI[Key::Up]->position.y };
	operateUI["camera"]->position += { keyUI[Key::D]->size.x, Half(keyUI[Key::D]->size.y) };

	for (auto& s : operateUI) { s.second->Update(); }
}

void OperateDrawer::Update()
{
	for (auto& s : keyUI)
	{
		// キーを押したらレクト位置を変える
		s.second->textureLeftTop.x = WristerEngine::Input::GetInstance()->IsInput(s.first) * s.second->size.x;
		s.second->Update();
	}
}

void OperateDrawer::Draw()
{
	frame->Draw();
	for (auto& s : keyUI) { s.second->Draw(); }
	for (auto& s : operateUI) { s.second->Draw(); }
}
