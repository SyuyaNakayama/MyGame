#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "LightGroup.h"
#include "Mesh.h"

class Model
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// ���C�g
	static std::unique_ptr<LightGroup> lightGroup;
	// �ǂݍ��񂾃��f�����
	static std::list<std::unique_ptr<Mesh>> meshes;
	// �r���[�v���W�F�N�V�����̃|�C���^
	static ViewProjection* viewProjection;
	
	Mesh* mesh = nullptr; // ���b�V���̃|�C���^
	Material material;

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
	static std::unique_ptr<Model> Create(const std::string& modelName, bool smoothing = false);
	static LightGroup* GetLightGroup() { return lightGroup.get(); }
	static void SetViewProjection(ViewProjection* viewProjection_) { viewProjection = viewProjection_; }
	static ViewProjection* GetViewProjection() { return viewProjection; }
	
	Material* GetMaterial() { return &material; }
	void Update();
	void Draw(const WorldTransform& worldTransform);
};