#pragma once
#include <array>
#include <wrl.h>
#include <d3d12.h>
#include "Color.h"
#include "Matrix4.h"
#include "D3D12Common.h"

class PostEffect
{
private:
	struct Vertex { Vector2 pos, uv; };

	struct ConstBufferData
	{
		Matrix4 mat;
		ColorRGBA color;
	};

	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	static const float CLEAR_COLOR[4];

	ComPtr<ID3D12Resource> texBuff;
	ComPtr<ID3D12Resource> depthBuff;
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	std::array<Vertex, 4> vertices;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	PipelineManager2 pipelineManager2;

	void CreateGraphicsPipelineState();
	void CreateBuffers();
	void CreateSRV();
	void CreateRTV();
	void CreateDSV();
public:
	void Initialize();
	void Draw();
	void PreDrawScene();
	void PostDrawScene();
};