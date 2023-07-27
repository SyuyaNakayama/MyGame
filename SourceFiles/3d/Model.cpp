#include "Model.h"
#include "Sprite.h"
using namespace Microsoft::WRL;
using namespace std;

// �ÓI�����o�ϐ��̎���
unique_ptr<LightGroup> Model::lightGroup;
list<unique_ptr<Mesh>> Model::meshes;
ViewProjection* Model::viewProjection = nullptr;

void Model::StaticInitialize()
{
	// ���C�g�O���[�v����
	lightGroup = LightGroup::Create();
	// �J��������
	ViewProjection* viewProjection = new ViewProjection;
	viewProjection->Initialize();
	Model::viewProjection = viewProjection;
}

std::unique_ptr<Model> Model::Create(const string& modelName, bool smoothing)
{
	unique_ptr<Model> newModel = make_unique<Model>();

	for (auto& mesh : meshes)
	{
		if (!mesh->IsLoaded(modelName, smoothing)) { continue; }
		// ���ɓǂݍ���ł������f���̏ꍇ
		newModel->mesh = mesh.get();
		newModel->material.Load(mesh.get());
		return newModel;
	}

	unique_ptr<Mesh> newMesh = make_unique<Mesh>();
	newMesh->LoadOBJ(modelName, smoothing);
	newModel->mesh = newMesh.get();
	newModel->material.Load(newMesh.get());
	meshes.push_back(move(newMesh));
	return newModel;
}

std::unique_ptr<Object3d> Model::Create2(const std::string& modelName, bool smoothing)
{
	unique_ptr<Object3d> newModel = make_unique<Object3d>();

	for (auto& mesh : meshes)
	{
		if (!mesh->IsLoaded(modelName, smoothing)) { continue; }
		// ���ɓǂݍ���ł������f���̏ꍇ
		newModel->mesh = mesh.get();
		newModel->material.Load(mesh.get());
		newModel->worldTransform.Initialize();
		return newModel;
	}

	unique_ptr<Mesh> newMesh = make_unique<Mesh>();
	newMesh->LoadOBJ(modelName, smoothing);
	newModel->mesh = newMesh.get();
	newModel->material.Load(newMesh.get());
	newModel->worldTransform.Initialize();
	meshes.push_back(move(newMesh));
	return newModel;
}

void Model::PreDraw()
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
}

void Model::Update()
{
	material.Update();
}

void Model::Draw(const WorldTransform& worldTransform)
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	cmdList->SetGraphicsRootConstantBufferView((UINT)RootParamNum::MatWorld, worldTransform.constBuffer->GetGPUVirtualAddress());
	material.Draw();
	mesh->Draw();
}

void Model::StaticUpdate()
{
	lightGroup->Update();
	viewProjection->Update();
}