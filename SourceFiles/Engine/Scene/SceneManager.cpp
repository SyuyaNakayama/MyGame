#include "SceneManager.h"
#include "Sprite.h"
#include "ModelManager.h"
#include "ParticleManager.h"
using namespace WristerEngine;

BaseScene::BaseScene() { sceneManager = SceneManager::GetInstance(); }

SceneManager* SceneManager::GetInstance()
{
	static SceneManager sceneManager;
	return &sceneManager;
}

void SceneManager::Initialize()
{
	fadeManager.Initialize();
}

void SceneManager::Update()
{
	fadeManager.Update();

	bool isChangeScene = fadeManager.IsChange() || !fadeManager.IsFade();
	isChangeScene &= nextScene != Scene::Null;
	if (isChangeScene)
	{
		// �V�[�����
		if (scene)
		{
			scene->Finalize();
			scene.release();
		}

		scene = sceneFactory->CreateScene(nextScene);
		nowScene = nextScene;
		nextScene = Scene::Null;

		if (isObjectClear)
		{
			_3D::ModelManager::ClearObjects();
			isObjectClear = false;
		}
		if (isParticleClear)
		{
			ParticleManager::Clear();
			isParticleClear = false;
		}

		scene->Initialize();
		scene->Update();
		if (pauseMenu) { pauseMenu->Initialize(); }
	}

	if (fadeManager.IsFade()) { return; }
	// �|�[�Y���Ȃ�V�[���̍X�V�������|�[�Y���j���[�̂ݍX�V����
	if (pauseMenu) { if (pauseMenu->IsPause()) { pauseMenu->Update(); return; } }
	scene->Update();
}

void SceneManager::Draw()
{
	scene->Draw();
	if (fadeManager.IsFade())
	{
		_2D::Sprite::PreDraw();
		fadeManager.Draw();
	}
	// �|�[�Y���Ȃ�|�[�Y���j���[��`��
	if (pauseMenu) { if (pauseMenu->IsPause()) { pauseMenu->Draw(); } }
}

void SceneManager::ChangeScene(Scene nextScene_, bool isObjectClear_, bool isParticleClear_, bool isUseFade)
{
	nextScene = nextScene_;
	isObjectClear = isObjectClear_;
	isParticleClear = isParticleClear_;
	if (isUseFade) { fadeManager.FadeScene(); }
}
