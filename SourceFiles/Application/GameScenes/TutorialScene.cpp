#include "TutorialScene.h"
#include "SceneManager.h"

void TutorialScene::Initialize()
{
	stage.Initialize();
	uiDrawer = std::make_unique<UIDrawerTutorialScene>();
	uiDrawer->Initialize();
}

void TutorialScene::Update()
{
	if (input->IsTrigger(Key::Space))
	{
		sceneManager->ChangeScene(Scene::Play);
		Stage::ResetScore();
		return;
	}

	stage.Update();
	uiDrawer->Update();
}

void UIDrawerTutorialScene::Initialize()
{
	frame = Sprite::Create("UI/uiFrame.png");
	frame->position = { 50,420 };
	frame->size = { 300,286 };
	frame->Update();

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
}

void UIDrawerTutorialScene::Update()
{
	for (auto& s : keyUI)
	{
		// キーを押したらレクト位置を変える
		s.second->textureLeftTop.x = Input::GetInstance()->IsInput(s.first) * s.second->size.x;
		s.second->Update();
	}
}

void UIDrawerTutorialScene::Draw()
{
	frame->Draw();
	for (auto& s : keyUI) { s.second->Draw(); }
}