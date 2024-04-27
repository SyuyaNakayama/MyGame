#include "ResultScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "Stage.h"
using namespace WristerEngine::_3D;

void ResultScene::Initialize()
{
	debugCamera.Initialize();
	ModelManager::SetViewProjection(&debugCamera);

	uiDrawer = std::make_unique<UIDrawerResultScene>();
	uiDrawer->Initialize();
}

void ResultScene::Update()
{
	if (operateConfig->GetTrigger("SceneChange"))
	{
		sceneManager->ChangeScene(Scene::Title);
		Stage::ResetScore();
	}

	uiDrawer->Update();
}

void UIDrawerResultScene::Initialize()
{
	// スコア表示関連の初期化
	scoreGauge.Initialize();
	// ランク表示関連の初期化
	rankAnimation.Initialize(&scoreGauge);
}

void UIDrawerResultScene::Update()
{
	// スコア表示関連の更新
	scoreGauge.Update();
	// ランク表示関連の更新
	rankAnimation.Update();
}

void UIDrawerResultScene::Draw()
{
	scoreGauge.Draw();
	rankAnimation.Draw();
}