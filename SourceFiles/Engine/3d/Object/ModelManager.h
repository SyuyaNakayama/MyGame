#pragma once
#include "Camera.h"
#include "LightGroup.h"
#include "Object3d.h"

namespace WristerEngine::_3D
{
	enum class RootParamNum { MatWorld = (int)TexType::Num, Material, Light, Camera };

	// 3D�I�u�W�F�N�g�̊Ǘ�
	class ModelManager
	{
	private:
		// ���C�g
		static std::unique_ptr<LightGroup> lightGroup;
		// �ǂݍ��񂾃��f�����
		static std::unordered_map<std::string, std::array<std::unique_ptr<Mesh>, 2>> meshes;
		// ���������I�u�W�F�N�g
		static std::list<std::unique_ptr<Object3d>> objects;
		// �J�����̃|�C���^
		static Camera* camera;

	public:
		// ������
		static void Initialize();
		// �X�V
		static void Update();
		// �`�揈��
		static void DrawObjects();
		// ���f���쐬
		static Object3d* Create(const std::string& modelName, bool smoothing = false);
		// �I�u�W�F�N�g�̉��
		static void ClearObjects() { objects.clear(); }
		// setter
		static void SetViewProjection(Camera* viewProjection_) { camera = viewProjection_; }
		// getter
		static LightGroup* GetLightGroup() { return lightGroup.get(); }
		static Camera* GetViewProjection() { return camera; }
	};
}