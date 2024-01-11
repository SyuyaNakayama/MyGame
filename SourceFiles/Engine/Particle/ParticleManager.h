#pragma once
#include "Matrix4.h"
#include "ParticleGroup.h"

namespace WristerEngine
{
	// �p�[�e�B�N���O���[�v�̊Ǘ�
	class ParticleManager final
	{
	private:
		// Microsoft::WRL::���ȗ�
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

		// �萔�o�b�t�@�p�f�[�^�\����
		struct ConstBufferData
		{
			Matrix4 mat;	// 3D�ϊ��s��
			Matrix4 matBillboard; // �r���{�[�h�s��
		};

		// �萔�o�b�t�@
		static ComPtr<ID3D12Resource> constBuff;
		static ConstBufferData* constMap;
		// �p�[�e�B�N���O���[�v�̔z��
		static std::vector<ParticleGroup> particleGroups;

		ParticleManager() = delete;
		ParticleManager(const ParticleManager& obj) = delete;

	public:
		// �ÓI������
		static void Initialize();
		// �X�V
		static void Update();
		// �`��
		static void Draw();
		// �p�[�e�B�N���̍폜
		static void Clear();
		// �p�[�e�B�N���O���[�v�ǉ�
		static void AddParticleGroup(const std::string& textureName); // �p�[�e�B�N���O���[�v�̒ǉ�
		// �p�[�e�B�N���O���[�v�擾
		static ParticleGroup* GetParticleGroup(size_t index) { return &particleGroups[index]; }
	};
}