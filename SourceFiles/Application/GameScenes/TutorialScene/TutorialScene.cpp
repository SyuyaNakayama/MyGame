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
	using Key = WristerEngine::Key;

	operateUI["tutorial"] = Sprite::Create("UI/Tutorial.png");
	operateUI["tutorial"]->anchorPoint = { -0.1f,-1 };

	operateUI["skip"] = Sprite::Create("UI/Skip.png");
	operateUI["skip"]->anchorPoint.x = 0.5f;
	operateUI["skip"]->position = Const(Vector2, "UiSkipStringPos");

	PlayMode::Initialize();
	keyUI[Key::Space] = OperateConfig::GetInstance()->CreateOperateSprite("SceneChange");
	keyUI[Key::Space]->anchorPoint.x = 0.5f;
	keyUI[Key::Space]->position = Const(Vector2, "UiSpacePosTutorial");

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