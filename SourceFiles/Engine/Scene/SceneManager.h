#pragma once
#include "BaseScene.h"
#include "FadeManager.h"
#include "SceneFactory.h"

// �V�[���Ǘ�
class SceneManager final
{
private:
	BaseScene* scene_ = nullptr;
	Scene nowScene_ = Scene::Null;
	Scene nextScene_ = Scene::Null;
	FadeManager fadeManager_;
	AbstractSceneFactory* sceneFactory_ = SceneFactory::GetInstance();

	SceneManager() = default;
public:
	SceneManager(const SceneManager& obj) = delete;
	// �C���X�^���X�擾
	static SceneManager* GetInstance();
	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �I��
	void Finalize() { scene_->Finalize(); delete scene_; }
	// �V�[���؂�ւ�
	void ChangeScene(Scene nextScene, bool isUseFade = true);
	// ���݂̃V�[���擾
	Scene GetNowScene() { return nowScene_; }
};