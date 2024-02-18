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
	if (input->IsTrigger(WristerEngine::Key::Space))
	{
		sceneManager->ChangeScene(Scene::Tutorial);
		Stage::ResetScore();
		return;
	}

	debugCamera.Update();
	stage.Update();
	uiDrawer->Update();
}

void UIDrawerTitleScene::Initialize()
{
	title["JP"] = Sprite::Create("ui/title_JP.png");
	title["EN"] = Sprite::Create("ui/title_EN.png");

	for (auto& ui : title)
	{
		ui.second->position = Half(WristerEngine::WIN_SIZE);
		ui.second->anchorPoint = { 0.5f,1.0f };
		ui.second->size *= 1.5f;
	}
	title["JP"]->position.y -= 200;
	title["EN"]->position.y -= 80;
	for (auto& ui : title) { ui.second->Update(); }

	spaceKey.Initialize("ui/Key/key_SPACE.png", 128, 30);
	Sprite* spaceKeySprite = spaceKey.GetSprite();
	spaceKeySprite->position = Half(WristerEngine::WIN_SIZE);
	spaceKeySprite->position.y += 80;
	spaceKeySprite->size *= 1.5f;
	spaceKeySprite->anchorPoint.x = 0.5f;
	spaceKeySprite->color = { 0.7f,0.7f,0.7f,1 };

	selectCursorUI = Sprite::Create("UI/SelectCursor.png");
	selectCursorUI->SetCenterAnchor();
	selectCursorUI->SetCenterPos();
}

void UIDrawerTitleScene::Update()
{
	spaceKey.Update();
	cosAngle += 10;
	selectCursorUI->size.y = 400 * (cos(cosAngle) + 1) * 0.5f;
	selectCursorUI->Update();
}

void UIDrawerTitleScene::Draw()
{
	for (auto& ui : title) { ui.second->Draw(); }
	spaceKey.Draw();
	//selectCursorUI->Draw();
}