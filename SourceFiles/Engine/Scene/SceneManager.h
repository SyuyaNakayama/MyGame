#pragma once
#include "BaseScene.h"
#include "FadeManager.h"
#include "SceneFactory.h"
#include "BasePauseMenu.h"

namespace WristerEngine
{
	// �V�[���Ǘ�
	class SceneManager final
	{
	private:
		std::unique_ptr<BaseScene> scene;
		Scene nowScene = Scene::Null;
		Scene nextScene = Scene::Null;
		FadeManager fadeManager;
		AbstractSceneFactory* sceneFactory = SceneFactory::GetInstance();
		bool isObjectClear = false, isParticleClear = false;
		BasePauseMenu* pauseMenu = nullptr;

		SceneManager() = default;
		~SceneManager() = default;

	public:
		SceneManager(const SceneManager& obj) = delete;
		SceneManager& operator=(const SceneManager& obj) = delete;
		// �C���X�^���X�擾
		static SceneManager* GetInstance();
		// ������
		void Initialize();
		// �X�V
		void Update();
		// �`��
		void Draw();
		// �I��
		void Finalize() { scene->Finalize(); }
		// �|�[�Y���j���[���Z�b�g
		void SetPauseMenu(BasePauseMenu* pauseMenu_) { pauseMenu = pauseMenu_; }
		// �|�[�Y�؂�ւ�
		void Pause() { pauseMenu->Pause(); }
		// �V�[���؂�ւ�
		void ChangeScene(Scene nextScene_, bool isObjectClear = true, bool isParticleClear = true, bool isUseFade = true);
		// ���݂̃V�[���擾
		Scene GetNowScene() const { return nowScene; }
	};
}