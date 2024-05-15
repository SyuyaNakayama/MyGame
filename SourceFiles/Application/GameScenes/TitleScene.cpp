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
	sprites["operate"] = OperateConfig::GetInstance()->CreateOperateSpriteAnimation("SceneChange");
	sprites["operate"]->position = Const(Vector2, "UiSpacePosTitle");
	sprites["operate"]->size *= 1.5f;
	sprites["operate"]->anchorPoint.x = 0.5f;
	sprites["operate"]->color = { 0.7f,0.7f,0.7f,1 };
}

void UIDrawerTitleScene::Draw()
{
	AbstractUIDrawer::Draw();
}