#pragma once
#include "LevelLoader.h"
#include "Input.h"
#include "SceneManager.h"
#include "Constant.h"

namespace WristerEngine::_3D
{
	// �Q�[���ɕ\������Ă���3D�I�u�W�F�N�g�̊��N���X
	class GameObject
	{
	protected:
		Input* input = Input::GetInstance();
		Constant* constant = Constant::GetInstance();

	public:
		// ���z�f�X�g���N�^
		virtual ~GameObject() = default;
		/// <summary>
		/// ������(�������z�֐�)
		/// </summary>
		/// <param name="objectData">Json�t�@�C������ǂݍ��񂾃f�[�^</param>
		virtual void Initialize(const ObjectData& objectData) = 0;
		// �X�V(�������z�֐�)
		virtual void Update() = 0;
		// ���݂̃V�[�����擾
		Scene GetNowScene() const { return SceneManager::GetInstance()->GetNowScene(); }
	};
}