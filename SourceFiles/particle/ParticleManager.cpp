#include <random>
#include "ParticleManager.h"
#include "Sprite.h"
#include "D3D12Common.h"
#include "Model.h"
using namespace Microsoft::WRL;

// 静的メンバ変数の実体
PipelineManager2 ParticleManager::pipelineManager;
ComPtr<ID3D12Resource> ParticleManager::constBuff;
ParticleManager::ConstBufferData* ParticleManager::constMap = nullptr;
std::vector<ParticleGroup> ParticleManager::particleGroups;

void ParticleManager::Initialize()
{
	PipelineProp pipelineProp;
	pipelineProp.shaderNames = { L"ParticleVS", L"ParticlePS", L"ParticleGS" };
	pipelineProp.inputLayoutProps.push_back({ "POSITION", DXGI_FORMAT_R32G32B32_FLOAT });
	pipelineProp.inputLayoutProps.push_back({ "TEXCOORD", DXGI_FORMAT_R32G32B32_FLOAT });
	pipelineProp.isDepthTest = true;
	pipelineProp.blendProp = { D3D12_BLEND_OP_ADD, D3D12_BLEND_ONE, D3D12_BLEND_ONE };
	pipelineProp.rootParamProp = { 1,1 };
	pipelineProp.depthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	pipelineProp.primitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
	pipelineManager.CreatePipeline(pipelineProp);
	
	CreateBuffer(&constBuff, &constMap, (sizeof(ConstBufferData) + 0xff) & ~0xff);
}

void ParticleManager::Update()
{
	for (auto& particleGroup : particleGroups) { particleGroup.Update(); }
	// 定数バッファへデータ転送
	constMap->mat = Model::GetViewProjection()->GetViewProjectionMatrix();
	constMap->matBillboard = Matrix4::GetBillboard();
}

void ParticleManager::Draw()
{
	// コマンドリストをセット
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	pipelineManager.SetPipeline();
	// プリミティブ形状を設定
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	// 定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(1, constBuff->GetGPUVirtualAddress());
	for (auto& particleGroup : particleGroups) { particleGroup.Draw(); }
}

void ParticleManager::Clear()
{
	for (auto& particleGroup : particleGroups) { particleGroup.Clear(); }
}

void ParticleManager::AddParticleGroup(const std::string& textureName)
{
	ParticleGroup pGroup;
	pGroup.Initialize(textureName);
	particleGroups.push_back(pGroup);
}