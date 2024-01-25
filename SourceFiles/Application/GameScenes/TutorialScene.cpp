#include "TutorialScene.h"
#include "SceneManager.h"

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

	OperateDrawer::Initialize();
	keyUI[Key::Space]->anchorPoint = { 0.5f,2 };
	keyUI[Key::Space]->position = { Half(WristerEngine::WIN_SIZE.x), WristerEngine::WIN_SIZE.y };
}

void UIDrawerTutorialScene::Update()
{
	OperateDrawer::Update();
}

void UIDrawerTutorialScene::Draw()
{
	OperateDrawer::Draw();
}