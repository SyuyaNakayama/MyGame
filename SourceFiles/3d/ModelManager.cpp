#include "ModelManager.h"
#include "Sprite.h"
#include "D3D12Common.h"
using namespace Microsoft::WRL;
using namespace std;

// 静的メンバ変数の実体
unique_ptr<LightGroup> ModelManager::lightGroup;
list<unique_ptr<Mesh>> ModelManager::meshes;
ViewProjection* ModelManager::viewProjection = nullptr;

void ModelManager::StaticInitialize()
{
	// ライトグループ生成
	lightGroup = LightGroup::Create();
	// カメラ生成
	ViewProjection* viewProjection = new ViewProjection;
	viewProjection->Initialize();
	ModelManager::viewProjection = viewProjection;
}

std::unique_ptr<Object3d> ModelManager::Create(const std::string& modelName, bool smoothing)
{
	unique_ptr<Object3d> newModel = make_unique<Object3d>();

	for (auto& mesh : meshes)
	{
		if (!mesh->IsLoaded(modelName, smoothing)) { continue; }
		// 既に読み込んでいたモデルの場合
		newModel->Initialize(mesh.get());
		return newModel;
	}

	unique_ptr<Mesh> newMesh = make_unique<Mesh>();
	newMesh->LoadOBJ(modelName, smoothing);
	newModel->Initialize(newMesh.get());
	meshes.push_back(move(newMesh));
	return newModel;
}

void ModelManager::PreDraw()
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

void ModelManager::StaticUpdate()
{
	lightGroup->Update();
	viewProjection->Update();
}