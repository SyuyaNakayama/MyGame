#pragma once
#include <array>
#include "Color.h"
#include "Vector.h"
#include "DirectXCommon.h"

namespace WristerEngine::_2D
{
	class PostEffect
	{
	public:
		enum class Type
		{
			None, // なし
			ColorFlip, // 色反転
			GrayScale, // グレースケール
			GetHighLumi, // 高輝度抽出
			Blur, // 平均ぼかし
			GaussianBlur, // ガウシアンブラー
			GaussianBlurLinear, // 単方向のガウシアンブラー
			CreateDotFilter, // クロスフィルタ
			Bloom // ブルーム
		};

	private:
		struct Vertex { Vector2 pos, uv; };

		struct ConstBufferData
		{
			UINT32 effectType = 0;
			float angle = 0;
			float brightness = 1;
			Vector2 uvOffset;
		};

		template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		static const float CLEAR_COLOR[4];

		static ID3D12Device* device;
		ComPtr<ID3D12Resource> texBuff;
		ComPtr<ID3D12Resource> depthBuff;
		static ComPtr<ID3D12DescriptorHeap> descHeapSRV;
		static int staticSRVIndex;
		int srvIndex;
		ComPtr<ID3D12DescriptorHeap> descHeapRTV;
		ComPtr<ID3D12DescriptorHeap> descHeapDSV;
		std::array<Vertex, 4> vertices;
		D3D12_VERTEX_BUFFER_VIEW vbView{};
		Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
		ConstBufferData* constMap = nullptr;
		static ComPtr<ID3D12RootSignature> rootSignature;
		static ComPtr<ID3D12PipelineState> pipelineState;

		void CreateBuffers();
		void CreateSRV();
		void CreateRTV();
		void CreateDSV();

	public:
		static void StaticInitialize();
		void Initialize(Type effectType = Type::None);
		void SetEffectType(Type effectType) { constMap->effectType = (UINT32)effectType; }
		void SetAngle(float angle) { constMap->angle = angle; }
		static ID3D12DescriptorHeap* GetSRV() { return descHeapSRV.Get(); }
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() const;
		void Draw();
		void PreDrawScene();
		void PostDrawScene();
	};
}