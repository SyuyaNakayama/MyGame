#include "ModelManager.h"
#include "Sprite.h"
#include "D3D12Common.h"
using namespace Microsoft::WRL;
using namespace std;
using namespace WristerEngine;
using namespace _3D;

// �ÓI�����o�ϐ��̎���
unique_ptr<LightGroup> ModelManager::lightGroup;
unordered_map<string, array<unique_ptr<Mesh>, 2>> ModelManager::meshes;
list<unique_ptr<Object3d>> ModelManager::objects;
Camera* ModelManager::camera = nullptr;

void ModelManager::Initialize()
{
	// ���C�g�O���[�v����
	lightGroup = LightGroup::Create();
	// �J��������
	camera = new Camera;
	camera->Initialize();
}

Object3d* ModelManager::Create(const string& modelName, bool smoothing)
{
	unique_ptr<Object3d> newObj3d = make_unique<Object3d>();

	// ���f���̍ēǂݍ��݂��`�F�b�N
	Mesh* mesh = meshes[modelName][smoothing].get();
	if (mesh)
	{
		// ���ɓǂݍ���ł������f���̏ꍇ
		newObj3d->Initialize(mesh);
		objects.push_back(move(newObj3d));
		return objects.back().get();
	}

	unique_ptr<Mesh> newMesh = make_unique<Mesh>();
	newMesh->LoadOBJ(modelName, smoothing);
	newObj3d->Initialize(newMesh.get());
	meshes[modelName][smoothing] = move(newMesh);
	objects.push_back(move(newObj3d));
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
	cmdList->SetGraphicsRootConstantBufferView((UINT)RootParamNum::Camera, camera->constBuffer->GetGPUVirtualAddress());
	// �f�X�N���v�^�q�[�v�Z�b�g
	_2D::Sprite::SetDescriptorHeaps();
	for (auto& object : objects) { object->Draw(); }
}

void ModelManager::Update()
{
	lightGroup->Update();
	camera->Update();
	objects.remove_if([](std::unique_ptr<Object3d>& object) { return object->isDestroy; });
	for (auto& object : objects) { object->Update(); }
}