#include "Framework.h"
#include "Sprite.h"
#include "D3D12Common.h"
using namespace WristerEngine;

void Framework::Initialize()
{
	wAPI->Initialize(windowName);
	dxCommon->Initialize();
	_2D::Sprite::StaticInitialize();
	input->Initialize();
	sceneManager->Initialize();
	PipelineManager::Initialize();
	constant->LoadConstants();
}

void Framework::Update()
{
	input->Update();
	sceneManager->Update();
}

void Framework::Finalize()
{
	constant->Finalize();
	sceneManager->Finalize();
	wAPI->Finalize();
}

bool Framework::IsEndRequest()
{
	// Xボタンで終了メッセージが来たらゲームループを抜ける
	if (wAPI->ProcessMessage()) { return true; }
	// ESCキーを押したらゲームループを抜ける
	if (input->IsTrigger(WristerEngine::Key::Escape)) { return true; }
	return false;
}

void Framework::Run()
{
	Initialize();

	while (!IsEndRequest())
	{
		Update();
		Draw();
	}

	Finalize();
}