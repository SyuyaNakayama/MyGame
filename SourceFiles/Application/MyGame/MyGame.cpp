#include "AudioManager.h"
#include "CollisionManager.h"
#include "ImGuiManager.h"
#include "ModelManager.h"
#include "MyGame.h"
#include "ParticleManager.h"
#include "PauseMenu.h"
using namespace WristerEngine::_2D;
using namespace WristerEngine::_3D;

void MyGame::Initialize()
{
	windowName = L"クアッドホッケー";
	Framework::Initialize();
#ifdef _DEBUG
	sceneManager->ChangeScene(Scene::Title, false, false, false);
#endif // _DEBUG
#ifdef NDEBUG
	sceneManager->ChangeScene(Scene::Title, false, false, false);
#endif // NDEBUG

	ModelManager::Initialize();
	WristerEngine::ParticleManager::Initialize();
	WristerEngine::ParticleManager::AddParticleGroup("Fire.png");
	WristerEngine::ParticleManager::AddParticleGroup("CollisionParticle.png");
	ImGuiManager::Initialize();
	WristerEngine::AudioManager::Initialize();
	PostEffect::StaticInitialize();
	postEffect.Initialize(PostEffect::Type::None);
	WristerEngine::BasePauseMenu* pauseMenu = PauseMenu::GetInstance();
	pauseMenu->Initialize();
	sceneManager->SetPauseMenu(pauseMenu);
}

void MyGame::Update()
{
	ImGuiManager::Begin();
	Framework::Update();
	ModelManager::Update();
	WristerEngine::CollisionManager::CheckAllCollisions();
	WristerEngine::Physics::ResetCollideList();
	WristerEngine::ParticleManager::Update();
	WristerEngine::AudioManager::Update();
	ImGuiManager::End();
}

void MyGame::Draw()
{
	postEffect.PreDrawScene();
	ModelManager::DrawObjects();
	WristerEngine::ParticleManager::Draw();
	postEffect.PostDrawScene();

	dxCommon->PreDraw();
	postEffect.Draw();
	Sprite::PreDraw();
	sceneManager->Draw();
	ImGuiManager::Draw();
	dxCommon->PostDraw();
}

void MyGame::Finalize()
{
	ImGuiManager::Finalize();
	WristerEngine::AudioManager::Finalize();
	Framework::Finalize();
}