#pragma once
#include "Mesh.h"
#include "Transform.h"

namespace WristerEngine::_3D
{
	// �I�u�W�F�N�g�N���X
	struct Object3d
	{
		Material material;
		std::unique_ptr<Transform> worldTransform;
		bool isDestroy = false;
		bool isInvisible = false;

	private:
		friend class ModelManager;
		Mesh* mesh;
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="mesh">���b�V���f�[�^</param>
		void Initialize(Mesh* mesh);
		// �X�V
		void Update();
		// �`��
		void Draw();
	};
}