#include "TutorialEvent.h"
#include "Input.h"
using namespace WristerEngine::_2D;

const float TutorialEvent::TEX_SIZE_Y = 32.0f;

void TutorialEvent::Initialize()
{
	// チュートリアルのテキスト画像
	sprites["text"] = Sprite::Create("UI/TutorialText.png");
	sprites["text"]->textureLeftTop.y = TEX_SIZE_Y * (float)phase;
	sprites["text"]->textureSize.y = TEX_SIZE_Y;
	sprites["text"]->size.y = TEX_SIZE_Y;
	sprites["text"]->SetCenterAnchor();
	sprites["text"]->position = { Half(WristerEngine::WIN_SIZE.x),300 };
	// テキストのフレーム
	const Sprite& s = *sprites["text"].get();
	sprites["frame"] = Sprite::Create("UI/uiFrame.png");
	sprites["frame"]->size = { s.size.x + TEX_SIZE_Y * 2.0f,s.size.y * 3.0f };
	sprites["frame"]->position = s.position;
	sprites["frame"]->anchorPoint = s.anchorPoint;
	// ヒントアイコン
	sprites["Hint"] = Sprite::Create("UI/Hint.png", { 1150,s.position.y }, { 0.5f,0.5f });
	sprites["Hint"]->size /= 8.0f;
	sprites["Hint"]->isInvisible = true;
	// Enterキー
	sprites["Enter"] = Sprite::Create("UI/Key/key_Enter.png",
		sprites["Hint"]->position + Vector2(sprites["Hint"]->size.x, 0),
		{ 0.5f,0.5f }, { 96,96 });
	sprites["Enter"]->size *= 0.5f;
	sprites["Enter"]->isInvisible = true;

	// Enterキー(アニメーション)
	enter.Initialize("UI/Key/key_Enter.png", (int)sprites["Enter"]->textureSize.x, 30);

}

void TutorialEvent::Update()
{
	if (WristerEngine::Input::GetInstance()->IsTrigger(WristerEngine::Key::Return))
	{
		for (auto& s : sprites) { s.second->isInvisible = !s.second->isInvisible; }
	}
	for (auto& s : sprites) { s.second->Update(); }
}

void TutorialEvent::Draw()
{
	for (auto& s : sprites) { s.second->Draw(); }
}

void TutorialEvent::NextPhase()
{
	phase++;
	sprites["text"]->textureLeftTop.y = TEX_SIZE_Y * (float)phase;
}
