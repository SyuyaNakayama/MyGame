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
	// 定数再読み込み
	if (input->IsTrigger(WristerEngine::Key::R))
	{
		WristerEngine::Constant::GetInstance()->LoadConstants();
		sceneManager->ChangeScene(Scene::Tutorial, true, true, false);
	}

	// シーンチェンジ
	if (operateConfig->GetTrigger("SceneChange"))
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
	PlayMode::Initialize();
	using Key = WristerEngine::Key;

	sprites["tutorial"] = Sprite::Create("UI/Tutorial.png", {}, { -0.1f,-1 });
	sprites["skip"] = Sprite::Create("UI/Skip.png", Const(Vector2, "UiSkipStringPos"), { 0.5f,0 });
	sprites["SceneChange"] = OperateConfig::GetInstance()->CreateOperateSprite("SceneChange");
	sprites["SceneChange"]->anchorPoint.x = 0.5f;
	sprites["SceneChange"]->position = Const(Vector2, "UiSpacePosTutorial");

	tutorialEvent->Initialize();
}

void UIDrawerTutorialScene::Update()
{
	PlayMode::Update();
	tutorialEvent->Update();
	AbstractUIDrawer::Update();
}

void UIDrawerTutorialScene::Draw()
{
	PlayMode::Draw();
	tutorialEvent->Draw();
}