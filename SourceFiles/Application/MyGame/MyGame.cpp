#include "MyGame.h"
#include "ModelManager.h"
#include "ImGuiManager.h"
#include "AudioManager.h"
#include "CollisionManager.h"

void MyGame::Initialize()
{
	windowName = L"クアッドホッケー";
	Framework::Initialize();
	sceneManager->ChangeScene(Scene::Play, false);
	ModelManager::Initialize();
	ParticleManager::Initialize();
	ParticleManager::AddParticleGroup("Particle.png");
	ImGuiManager::Initialize();
	Audio::StaticInitialize();
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
	sceneManager->Draw();
	ModelManager::DrawObjects();
	ParticleManager::Draw();
	postEffect->PostDrawScene();
	
	dxCommon->PreDraw();
	postEffect->Draw();
	ImGuiManager::Draw();
	dxCommon->PostDraw();
}

void MyGame::Finalize()
{
	ImGuiManager::Finalize();
	Audio::Finalize();
	Framework::Finalize();
}