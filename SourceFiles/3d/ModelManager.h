#pragma once
#include "ViewProjection.h"
#include "LightGroup.h"
#include "D3D12Common.h"
#include "Object3d.h"

enum class RootParamNum { MatWorld = (int)TexType::Num, Material, Light, Camera };

class ModelManager
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	// ���C�g
	static std::unique_ptr<LightGroup> lightGroup;
	// �ǂݍ��񂾃��f�����
	static std::list<std::unique_ptr<Mesh>> meshes;
	// �r���[�v���W�F�N�V�����̃|�C���^
	static ViewProjection* viewProjection;

public:
	// �ÓI������
	static void StaticInitialize();
	// �ÓI�X�V
	static void StaticUpdate();
	// �`��O����
	static void PreDraw();
	// �`��㏈��
	static void PostDraw() {}
	// ���f���쐬
	static std::unique_ptr<Object3d> Create(const std::string& modelName, bool smoothing = false);
	static LightGroup* GetLightGroup() { return lightGroup.get(); }
	static void SetViewProjection(ViewProjection* viewProjection_) { viewProjection = viewProjection_; }
	static ViewProjection* GetViewProjection() { return viewProjection; }
};