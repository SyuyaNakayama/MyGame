#include "TitleScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "ImGuiManager.h"

using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void TitleScene::Initialize()
{
	debugCamera.Initialize();
	stage.Initialize();
	camera.Initialize();
	camera.eye = { -50,250,0 };
	camera.target.x = 0;
	ModelManager::SetViewProjection(&camera);
	uiDrawer = std::make_unique<UIDrawerTitleScene>();
	uiDrawer->Initialize();
}

void TitleScene::Update()
{
	if (operateConfig->GetTrigger("SceneChange"))
	{
		sceneManager->ChangeScene(Scene::Tutorial);
		Stage::ResetScore();
		GoalManager::GetInstance()->ResetGoalPointer();
		return;
	}

	debugCamera.Update();
	stage.Update();
	uiDrawer->Update();
}

void UIDrawerTitleScene::Initialize()
{
	sprites["TitleJP"] = Sprite::Create("ui/title_JP.png", Const(Vector2, "UiTitleJPPos"));
	sprites["TitleEN"] = Sprite::Create("ui/title_EN.png", Const(Vector2, "UiTitleENPos"));

	for (auto& ui : sprites)
	{
		ui.second->anchorPoint = { 0.5f,1.0f };
		ui.second->size *= 1.5f;
	}
	operateKey = OperateConfig::GetInstance()->CreateOperateSpriteAnimation("SceneChange");
	Sprite* spaceKeySprite = operateKey->GetSprite();
	spaceKeySprite->position = Const(Vector2, "UiSpacePosTitle");
	spaceKeySprite->size *= 1.5f;
	spaceKeySprite->anchorPoint.x = 0.5f;
	spaceKeySprite->color = { 0.7f,0.7f,0.7f,1 };

	AbstractUIDrawer::Update();
}

void UIDrawerTitleScene::Update()
{
	operateKey->Update();
}

void UIDrawerTitleScene::Draw()
{
	AbstractUIDrawer::Draw();
	operateKey->Draw();
}