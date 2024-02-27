#include "TutorialEvent.h"

using namespace WristerEngine::_2D;

const float TutorialEvent::TEX_SIZE_Y = 32.0f;

void TutorialEvent::Initialize()
{
	text = Sprite::Create("UI/TutorialText.png");
	text->textureLeftTop.y = TEX_SIZE_Y * (float)phase;
	text->textureSize.y = TEX_SIZE_Y;
	text->size.y = TEX_SIZE_Y;
	text->SetCenterAnchor();
	text->SetCenterPos();
}

void TutorialEvent::Update()
{
	text->Update();
}

void TutorialEvent::Draw()
{
	text->Draw();
}

void TutorialEvent::NextPhase()
{
	phase++;
	text->textureLeftTop.y = TEX_SIZE_Y * (float)phase;
}
