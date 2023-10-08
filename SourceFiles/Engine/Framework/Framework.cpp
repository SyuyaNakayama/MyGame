#include "Framework.h"
#include "Sprite.h"
#include "D3D12Common.h"

void Framework::Initialize()
{
	wAPI->Initialize(windowName);
	dxCommon->Initialize();
	Sprite::StaticInitialize();
	input->Initialize();
	sceneManager->Initialize();
	PipelineManager::Initialize();
}

void Framework::Update()
{
	input->Update();
	sceneManager->Update();
}

void Framework::Finalize()
{
	sceneManager->Finalize();
	wAPI->Finalize();
}

bool Framework::IsEndRequest()
{
	// X�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
	if (wAPI->ProcessMessage()) { return true; }
	// ESC�L�[����������Q�[�����[�v�𔲂���
	if (input->IsTrigger(Key::Escape)) { return true; }
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