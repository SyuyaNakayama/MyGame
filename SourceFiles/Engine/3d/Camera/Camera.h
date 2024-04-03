#pragma once
#include "Matrix4.h"
#include "WindowsAPI.h"
#include "CameraShake.h"
#include <wrl.h>
#include <d3d12.h>

namespace WristerEngine::_3D
{
	// �J����
	class Camera
	{
	private:
		Matrix4 matView, matProjection, matViewProjection;

		// �萔�o�b�t�@�p�f�[�^�\����
		struct ConstBufferData
		{
			Matrix4 viewproj; // �r���[�v���W�F�N�V�����s��
			Vector3 cameraPos; // �J�������W(���[���h���W)
		};

	public:
		ConstBufferData* constMap = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer;
		Vector3 eye = { 0, 0, -50.0f }, target, up = Vector3::MakeAxis(Axis::Y);
		Angle fovAngleY = 45; // ��p(�x)
		// �A�X�y�N�g��(��{��WIN_SIZE�ɏ���)
		float aspectRatio = WIN_SIZE.x / WIN_SIZE.y;
		float nearZ = 0.1f, farZ = 1000.0f; // �f��͈�
		// �V�F�C�N�@�\
		std::unique_ptr<CameraShake> shake;

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="shakeProp">�V�F�C�N���</param>
		void Initialize(const CameraShake::Prop* shakeProp = nullptr);
		// �X�V
		void Update();
		// �J�����ړ�
		void CameraMove(const Vector3& move);
		// �r���[�s��ƃv���W�F�N�V�����s����|�����킹���s��
		Matrix4 GetViewProjectionMatrix() const { return matViewProjection; }
	};
}