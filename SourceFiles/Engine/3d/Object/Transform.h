#pragma once
#include "Matrix4.h"
#include "WindowsAPI.h"
#include <wrl.h>
#include <d3d12.h>

namespace WristerEngine::_3D
{
	// ���[���h�g�����X�t�H�[��
	class Transform
	{
	private:
		// �萔�o�b�t�@�p�f�[�^�\����
		struct ConstBufferData
		{
			Matrix4 world; // ���[���h�s��
		};

	public:
		Matrix4 matWorld;
		ConstBufferData* constMap = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer;
		Vector3 scale = { 1,1,1 }, rotation, translation;
		Transform* parent = nullptr;
		bool isUpdated = false;

		// ������
		void Initialize();
		// �X�V
		void Update();
		// �`��
		void Draw();
		// getter
		Vector3 GetWorldPosition() const { return { matWorld.m[3][0],matWorld.m[3][1],matWorld.m[3][2] }; }
		Vector3 GetScale() const;
	};
}