#include "TutorialScene.h"
#include "SceneManager.h"
#include <DirectXTex.h>
#include "D3D12Common.h"
#include "Physics.h"

using namespace WristerEngine::_2D;

void TutorialScene::Initialize()
{
	uiDrawer = std::make_unique<UIDrawerTutorialScene>();
	uiDrawer->Initialize();
	stage.Initialize();
}

void TutorialScene::Update()
{
	if (input->IsTrigger(WristerEngine::Key::R))
	{
		// ’è”Ä“Ç‚Ýž‚Ý
		WristerEngine::Constant::GetInstance()->LoadConstants();
		sceneManager->ChangeScene(Scene::Tutorial, true, true, false);
	}

	if (input->IsTrigger(WristerEngine::Key::Space))
	{
		sceneManager->ChangeScene(Scene::Play);
		Stage::ResetScore();
		GoalManager::GetInstance()->ResetGoalPointer();
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

	operateUI["play"] = Sprite::Create("UI/Skip.png");
	operateUI["play"]->anchorPoint = { 0.5f,2 };
	operateUI["play"]->position = { Half(WristerEngine::WIN_SIZE.x), WristerEngine::WIN_SIZE.y };

	PlayMode::Initialize();
	keyUI[Key::Space]->anchorPoint = { 0.5f,2 };
	keyUI[Key::Space]->position = { Half(WristerEngine::WIN_SIZE.x), WristerEngine::WIN_SIZE.y };
	keyUI[Key::Space]->Split({ 2,1 });

	for (auto& s : keyUI) { s.second->Update(); }

	tutorialEvent->Initialize();
}

void UIDrawerTutorialScene::Update()
{
	PlayMode::Update();
	tutorialEvent->Update();
}

void UIDrawerTutorialScene::Draw()
{
	PlayMode::Draw();
	tutorialEvent->Draw();
	for (auto& s : keyUI) { s.second->Draw(); }
}