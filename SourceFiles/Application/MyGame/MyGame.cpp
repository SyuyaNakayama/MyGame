#include "MyGame.h"
#include "ModelManager.h"
#include "ImGuiManager.h"
#include "AudioManager.h"
#include "CollisionManager.h"

void MyGame::Initialize()
{
	windowName = L"クアッドホッケー";
	Framework::Initialize();
	sceneManager->ChangeScene(Scene::Title, false);
	ModelManager::Initialize();
	ParticleManager::Initialize();
	ParticleManager::AddParticleGroup("Fire.png");
	ParticleManager::AddParticleGroup("CollisionParticle.png");
	ImGuiManager::Initialize();
	AudioManager::Initialize();
	postEffect = std::make_unique<PostEffect>();
	postEffect->Initialize();
}

void MyGame::Update()
{
	ImGuiManager::Begin();
	Framework::Update();
	ModelManager::Update();
	CollisionManager::CheckAllCollisions();
	Physics::ResetCollideList();
	ParticleManager::Update();
	AudioManager::Update();
	ImGuiManager::End();
}

void MyGame::Draw()
{
	postEffect->PreDrawScene();
	ModelManager::DrawObjects();
	ParticleManager::Draw();
	Sprite::PreDraw();
	sceneManager->Draw();
	postEffect->PostDrawScene();

	dxCommon->PreDraw();
	postEffect->Draw();
	ImGuiManager::Draw();
	dxCommon->PostDraw();
}

void MyGame::Finalize()
{
	ImGuiManager::Finalize();
	AudioManager::Finalize();
	Framework::Finalize();
}