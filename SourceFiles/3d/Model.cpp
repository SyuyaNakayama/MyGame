#include "Model.h"
#include "Sprite.h"
using namespace Microsoft::WRL;
using namespace std;

// �ÓI�����o�ϐ��̎���
PipelineManager2 Model::pipelineManager;
unique_ptr<LightGroup> Model::lightGroup;
list<unique_ptr<Mesh>> Model::meshes;
ViewProjection* Model::viewProjection = nullptr;

void Model::StaticInitialize()
{
	PipelineProp pipelineProp;
	pipelineProp.shaderNames = { L"ObjVS", L"ObjPS" };
	pipelineProp.inputLayoutProps.push_back({ "POSITION", DXGI_FORMAT_R32G32B32_FLOAT });
	pipelineProp.inputLayoutProps.push_back({ "NORMAL", DXGI_FORMAT_R32G32B32_FLOAT });
	pipelineProp.inputLayoutProps.push_back({ "TEXCOORD", DXGI_FORMAT_R32G32_FLOAT });
	pipelineProp.isDepthTest = true;
	pipelineProp.blendProp = { D3D12_BLEND_OP_ADD, D3D12_BLEND_SRC_ALPHA, D3D12_BLEND_INV_SRC_ALPHA };
	pipelineProp.rootParamProp = { 1,4 };
	pipelineManager.CreatePipeline(pipelineProp);
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

void Model::PreDraw()
{
	// �R�}���h���X�g���Z�b�g
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();

	pipelineManager.SetPipeline();
	// �v���~�e�B�u�`���ݒ�
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// ���C�g�̕`��
	lightGroup->Draw();
	// �J����
	cmdList->SetGraphicsRootConstantBufferView(4, viewProjection->constBuffer->GetGPUVirtualAddress());
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
	cmdList->SetGraphicsRootConstantBufferView(1, worldTransform.constBuffer->GetGPUVirtualAddress());
	material.Draw();
	mesh->Draw();
}

void Model::StaticUpdate()
{
	lightGroup->Update();
	viewProjection->Update();
}