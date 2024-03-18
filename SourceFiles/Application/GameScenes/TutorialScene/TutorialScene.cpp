#include "TutorialScene.h"
#include "SceneManager.h"
#include <DirectXTex.h>
#include "D3D12Common.h"
#include "Physics.h"

using namespace WristerEngine::_2D;

void TutorialScene::Initialize()
{
	stage.Initialize();
	uiDrawer = std::make_unique<UIDrawerTutorialScene>();
	uiDrawer->Initialize();
}

void TutorialScene::Update()
{
	if (input->IsTrigger(WristerEngine::Key::Space))
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
	using Key = WristerEngine::Key;
	keyUI[Key::Space] = Sprite::Create("UI/Key/key_SPACE.png");

	operateUI["tutorial"] = Sprite::Create("UI/Tutorial.png");
	operateUI["tutorial"]->anchorPoint = { -0.1f,-1 };

	operateUI["play"] = Sprite::Create("UI/Play.png");
	operateUI["play"]->anchorPoint = { 0.5f,2 };
	operateUI["play"]->position = { Half(WristerEngine::WIN_SIZE.x), WristerEngine::WIN_SIZE.y };

	PlayMode::Initialize();
	keyUI[Key::Space]->anchorPoint = { 0.5f,2 };
	keyUI[Key::Space]->position = { Half(WristerEngine::WIN_SIZE.x), WristerEngine::WIN_SIZE.y };

	eventManager->Initialize();
}

void UIDrawerTutorialScene::Update()
{
	PlayMode::Update();
	if (WristerEngine::Input::GetInstance()->IsTrigger(WristerEngine::Key::Return))
	{
		//eventManager->NextPhase();
	}

	eventManager->Update();
}

void UIDrawerTutorialScene::Draw()
{
	PlayMode::Draw();
	eventManager->Draw();
}