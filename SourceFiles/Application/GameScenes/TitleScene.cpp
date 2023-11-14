#include "TitleScene.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "ImGuiManager.h"

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
	if (input->IsTrigger(Key::Space))
	{
		sceneManager->ChangeScene(Scene::Play);
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
		ui.second->position = Half(WindowsAPI::WIN_SIZE);
		ui.second->anchorPoint = { 0.5f,1.0f };
		ui.second->size *= 1.5f;
	}
	title["JP"]->position.y -= 200;
	title["EN"]->position.y -= 80;
	for (auto& ui : title) { ui.second->Update(); }

	spaceKey.Initialize("ui/key_SPACE.png", 128, 30);
	Sprite* spaceKeySprite = spaceKey.GetSprite();
	spaceKeySprite->position = Half(WindowsAPI::WIN_SIZE);
	spaceKeySprite->position.y += 80;
	spaceKeySprite->size *= 1.5f;
	spaceKeySprite->anchorPoint.x = 0.5f;
}

void UIDrawerTitleScene::Update()
{
	spaceKey.Update();
}

void UIDrawerTitleScene::Draw()
{
	for (auto& ui : title) { ui.second->Draw(); }
	spaceKey.Draw();
}