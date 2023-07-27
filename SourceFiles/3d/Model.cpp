#include "Model.h"
#include "Sprite.h"
using namespace Microsoft::WRL;
using namespace std;

// 静的メンバ変数の実体
unique_ptr<LightGroup> Model::lightGroup;
list<unique_ptr<Mesh>> Model::meshes;
ViewProjection* Model::viewProjection = nullptr;

void Model::StaticInitialize()
{
	// ライトグループ生成
	lightGroup = LightGroup::Create();
	// カメラ生成
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
		// 既に読み込んでいたモデルの場合
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
		// 既に読み込んでいたモデルの場合
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
	// コマンドリストをセット
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();

	PipelineManager::SetPipeline(PipelineType::Object);
	// プリミティブ形状を設定
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// ライトの描画
	lightGroup->Draw((UINT)RootParamNum::Light);
	// カメラ
	cmdList->SetGraphicsRootConstantBufferView((UINT)RootParamNum::Camera, viewProjection->constBuffer->GetGPUVirtualAddress());
	// デスクリプタヒープセット
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