#include "TutorialEvent.h"
#include "Input.h"
#include <imgui.h>
#include "OperateConfig.h"
using namespace WristerEngine::_2D;

const float TutorialEvent::TEX_SIZE_Y = 32.0f;

TutorialEvent* TutorialEvent::GetInstance()
{
	static TutorialEvent instance;
	return &instance;
}

void TutorialEvent::Initialize()
{
	phase = 0;
	isEnd = false;
	OperateConfig* operateConfig = OperateConfig::GetInstance();
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
	// Selectキー
	sprites["Select"] = operateConfig->CreateOperateSprite("Select");
	sprites["Select"]->position = sprites["Hint"]->position + Vector2(sprites["Hint"]->size.x, 0);
	sprites["Select"]->SetCenterAnchor();
	sprites["Select"]->isInvisible = true;

	// Selectキー(アニメーション)
	select = operateConfig->CreateOperateSpriteAnimation("Select");
	select->position = Const(Vector2, "UiEnterAnimePos");

	tutorialEventPhase = Const(std::vector<UINT32>, "TutorialEventPhase");
}

void TutorialEvent::EnterEventManager()
{
	if (IsAny(phase, tutorialEventPhase)) { EnterEvent = &TutorialEvent::PrintFlip; }
	else { EnterEvent = &TutorialEvent::NextPhase; }
}

void TutorialEvent::PrintFlip()
{
	select->isInvisible = !select->isInvisible;
	for (auto& s : sprites) { s.second->isInvisible = !s.second->isInvisible; }
}

void TutorialEvent::Update()
{
	EnterEventManager();
	select->Update();
	if (OperateConfig::GetInstance()->GetTrigger("Select"))
	{
		if (EnterEvent) { (this->*EnterEvent)(); }
	}
	for (auto& s : sprites) { s.second->Update(); }
}

void TutorialEvent::Draw()
{
	for (auto& s : sprites) { s.second->Draw(); }
	select->Draw();
}

void TutorialEvent::NextPhase()
{
	if (isEnd) { return; }
	if (!sprites["Select"]->isInvisible) { PrintFlip(); }
	phase = min(phase + 1, tutorialEventPhase.back());
	if (phase == tutorialEventPhase.back()) { isEnd = true; }
	// 説明の表示を変える
	sprites["text"]->textureLeftTop.y = TEX_SIZE_Y * (float)phase;
	sprites["text"]->Update();
}