#pragma once
#include <array>
#include <wrl.h>
#include <d3d12.h>
#include "Color.h"
#include "Matrix4.h"

// ポストエフェクト
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

	// バッファ生成
	void CreateBuffers();
	// シェーダーリソースビュー生成
	void CreateSRV();
	// レンダーターゲットビュー生成
	void CreateRTV();
	// デプスステンシルビュー生成
	void CreateDSV();
public:
	// 初期化
	void Initialize();
	// 描画
	void Draw();
	// シーン描画前処理
	void PreDrawScene();
	// シーン描画後処理
	void PostDrawScene();
};