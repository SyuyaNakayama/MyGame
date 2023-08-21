#pragma once
#include "ViewProjection.h"
#include "LightGroup.h"
#include "Object3d.h"

enum class RootParamNum { MatWorld = (int)TexType::Num, Material, Light, Camera };

class ModelManager
{
private:
	// ���C�g
	static std::unique_ptr<LightGroup> lightGroup;
	// �ǂݍ��񂾃��f�����
	static std::unordered_map<std::string, std::array<std::unique_ptr<Mesh>, 2>> meshes;
	// ���������I�u�W�F�N�g
	static std::list<std::unique_ptr<Object3d>> objects;
	// �r���[�v���W�F�N�V�����̃|�C���^
	static ViewProjection* viewProjection;

public:
	// ������
	static void Initialize();
	// �X�V
	static void Update();
	// �`�揈��
	static void DrawObjects();
	// ���f���쐬
	static Object3d* Create(const std::string& modelName, bool smoothing = false);
	static void ClearObjects() { objects.clear(); }
	static LightGroup* GetLightGroup() { return lightGroup.get(); }
	static void SetViewProjection(ViewProjection* viewProjection_) { viewProjection = viewProjection_; }
	static ViewProjection* GetViewProjection() { return viewProjection; }
};