#pragma once
#include "AbstractSceneFactory.h"

// �e�V�[���̐����N���X
class SceneFactory : public AbstractSceneFactory
{
private:
	// �R���X�g���N�^��
	SceneFactory() = default;
	~SceneFactory() = default;

public:
	SceneFactory(const SceneFactory& obj) = delete;
	SceneFactory& operator=(const SceneFactory& obj) = delete;
	// �C���X�^���X�擾
	static SceneFactory* GetInstance();

	/// <summary>
	/// �V�[���쐬
	/// </summary>
	/// <param name="scene">���ɍ��V�[��</param>
	/// <returns>�쐬���ꂽ�N���X�̃|�C���^</returns>
	std::unique_ptr<BaseScene> CreateScene(Scene scene) override;
};