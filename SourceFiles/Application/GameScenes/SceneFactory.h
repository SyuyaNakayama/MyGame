#pragma once
#include "AbstractSceneFactory.h"

// �e�V�[���̐����N���X
class SceneFactory : public AbstractSceneFactory
{
private:
	SceneFactory() = default;

public:
	// �R���X�g���N�^
	SceneFactory(const SceneFactory& obj) = delete;
	// �C���X�^���X�擾
	static SceneFactory* GetInstance();

	/// <summary>
	/// �V�[���쐬
	/// </summary>
	/// <param name="scene">���ɍ��V�[��</param>
	/// <returns>�쐬���ꂽ�N���X�̃|�C���^</returns>
	BaseScene* CreateScene(Scene scene) override;
};