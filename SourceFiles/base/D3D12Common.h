#pragma once
#include <memory>
#include <cassert>
#include <array>
#include <map>
#include "DirectXCommon.h"

template<class T> void CreateBuffer(ID3D12Resource** buff, T** map, UINT64 width)
{
	// バッファの生成
	Result result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(width),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(buff));

	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	result = (*buff)->Map(0, nullptr, (void**)map);
	// 繋がりを解除
	(*buff)->Unmap(0, nullptr);
}

D3D12_INPUT_ELEMENT_DESC SetInputLayout(LPCSTR semanticName, DXGI_FORMAT format);
void LoadShader(ID3DBlob** shaderBlob, std::wstring shaderName, LPCSTR target);

// result値がエラーなら自動で警告が出る
struct Result
{
private:
	HRESULT result = S_OK;

public:
	Result() {}
	Result(const HRESULT& result) { operator=(result); }

	void operator=(HRESULT result_)
	{
		result = result_;
		assert(SUCCEEDED(result));
	}
};

enum class RootParamType { CBV, DescriptorTable };

struct PipelineProp
{
private:
	struct InputLayoutProp
	{
		LPCSTR semanticName;
		DXGI_FORMAT format;
	};

	struct BlendProp
	{
		D3D12_BLEND_OP blendOp = D3D12_BLEND_OP_ADD;
		D3D12_BLEND srcBlend = D3D12_BLEND_SRC_ALPHA;
		D3D12_BLEND destBlend = D3D12_BLEND_INV_SRC_ALPHA;
	};

	struct RootParameterProp
	{
		UINT descriptorNum;
		UINT constBuffNum;
	};

public:
	// VS,PS,GS
	std::array<std::wstring, 3> shaderNames;
	std::vector<InputLayoutProp> inputLayoutProps;
	BlendProp blendProp;
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	bool isDepthTest = true; // 深度テストを行う = 3D用 か
	D3D12_DEPTH_WRITE_MASK depthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	RootParameterProp rootParamProp;
	D3D12_TEXTURE_ADDRESS_MODE textureAddressMode = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	D3D12_CULL_MODE cullMode = D3D12_CULL_MODE_BACK;
};

enum class PipelineType { Sprite, PostEffect, Object, Dissolve, Particle };

class PipelineManager
{
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	static std::map<PipelineType, PipelineManager> pipelines;
	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;

public:
	void CreatePipeline(const PipelineProp& pipelineProp);
	static void Initialize();
	static void SetPipeline(PipelineType pipelineType);
};