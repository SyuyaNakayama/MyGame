#include "ResultScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "Stage.h"

void ResultScene::Initialize()
{
	debugCamera.Initialize();
	ModelManager::SetViewProjection(&debugCamera);

	uiDrawer = std::make_unique<UIDrawerResultScene>();
	uiDrawer->Initialize();
}

void ResultScene::Update()
{
	if (input->IsTrigger(Key::Space))
	{
		sceneManager->ChangeScene(Scene::Title);
		Stage::ResetScore();
	}

	uiDrawer->Update();
}

void UIDrawerResultScene::Initialize()
{
	// �X�R�A�\���֘A�̏�����
	scoreGauge.Initialize();
	// �����N�\���֘A�̏�����
	rankAnimation.Initialize(&scoreGauge);
}

void UIDrawerResultScene::Update()
{
	// �X�R�A�\���֘A�̍X�V
	scoreGauge.Update();
	// �����N�\���֘A�̍X�V
	rankAnimation.Update();
}

void UIDrawerResultScene::Draw()
{
	scoreGauge.Draw();
	rankAnimation.Draw();
}