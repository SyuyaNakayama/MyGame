#include "ModelManager.h"
#include "Sprite.h"
#include "D3D12Common.h"
using namespace Microsoft::WRL;
using namespace std;

// �ÓI�����o�ϐ��̎���
unique_ptr<LightGroup> ModelManager::lightGroup;
list<unique_ptr<Mesh>> ModelManager::meshes;
list<unique_ptr<Object3d>> ModelManager::objects;
ViewProjection* ModelManager::viewProjection = nullptr;

void ModelManager::Initialize()
{
	// ���C�g�O���[�v����
	lightGroup = LightGroup::Create();
	// �J��������
	ViewProjection* viewProjection = new ViewProjection;
	viewProjection->Initialize();
	ModelManager::viewProjection = viewProjection;
}

Object3d* ModelManager::Create(const string& modelName, bool smoothing)
{
	unique_ptr<Object3d> newModel = make_unique<Object3d>();

	for (auto& mesh : meshes)
	{
		if (!mesh->IsLoaded(modelName, smoothing)) { continue; }
		// ���ɓǂݍ���ł������f���̏ꍇ
		newModel->Initialize(mesh.get());
		objects.push_back(move(newModel));
		return objects.back().get();
	}

	unique_ptr<Mesh> newMesh = make_unique<Mesh>();
	newMesh->LoadOBJ(modelName, smoothing);
	newModel->Initialize(newMesh.get());
	meshes.push_back(move(newMesh));
	objects.push_back(move(newModel));
	return objects.back().get();
}

void ModelManager::DrawObjects()
{
	// �R�}���h���X�g���Z�b�g
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();

	PipelineManager::SetPipeline(PipelineType::Object);
	// �v���~�e�B�u�`���ݒ�
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// ���C�g�̕`��
	lightGroup->Draw((UINT)RootParamNum::Light);
	// �J����
	cmdList->SetGraphicsRootConstantBufferView((UINT)RootParamNum::Camera, viewProjection->constBuffer->GetGPUVirtualAddress());
	// �f�X�N���v�^�q�[�v�Z�b�g
	Sprite::SetDescriptorHeaps();
	for (auto& object : objects) { object->Draw(); }
}

void ModelManager::Update()
{
	lightGroup->Update();
	viewProjection->Update();
	objects.remove_if([](std::unique_ptr<Object3d>& object) { return object->isDestroy; });
	for (auto& object : objects) { object->Update(); }
}