#pragma once
#include <array>
#include <memory>
#include "Color.h"
#include "DirectXCommon.h"

namespace WristerEngine::_2D
{
	// テクスチャ1枚分のデータ
	struct TextureData
	{
		std::string fileName;
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle{};
		D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle{};
	};

	//struct Sprite;


	// スプライト
	struct Sprite
	{
		// デフォルトディレクトリ
		static std::string DEFAULT_TEXTURE_DIRECTORY_PATH;

		Vector2 position;
		float rotation = 0;
		ColorRGBA color;
		Vector2 size; // 表示サイズ
		Vector2 anchorPoint;
		bool isFlipX = false;
		bool isFlipY = false;
		bool isInvisible = false;
		Vector2 textureLeftTop; // 切り取り領域の左上座標
		Vector2 textureSize; // 切り取り領域のサイズ
		TextureData* tex = nullptr;

	private:
		class Animation
		{
		private:
			Sprite* sprite = nullptr;
			float width = 0;
			FrameTimer interval;
			size_t animeNum = 0;
			size_t animeNumMax = 0;

		public:
			/// <summary>
			/// 初期化
			/// </summary>
			/// <param name="sprite">spriteポインタ</param>
			/// <param name="spriteNum">アニメーション枚数</param>
			/// <param name="animationIntervel">アニメーション速度</param>
			void Initialize(Sprite* sprite, size_t spriteNum, int animationIntervel);
			// 更新
			void Update();
		};

		struct Vertex { Vector2 pos, uv; };

		struct ConstBufferData
		{
			Matrix4 mat;
			ColorRGBA color;
		};

		enum class VertexNumber
		{
			LB, // 左下
			LT, // 左上
			RB, // 右下
			RT  // 右上
		};

		template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

		static const size_t MAX_SRV_COUNT = 2056;
		static const uint32_t MIP_LEVELS_DEFAULT = UINT32_MAX;
		static ComPtr<ID3D12DescriptorHeap> srvHeap;
		static std::list<TextureData*> textures;
		const static Matrix4 matProj;
		std::array<Vertex, 4> vertices;
		D3D12_VERTEX_BUFFER_VIEW vbView{};
		Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
		ConstBufferData* constMap = nullptr;
		Vertex* vertMap = nullptr;
		Matrix4 matWorld;
		std::unique_ptr<Animation> animation;

		// テクスチャサイズをイメージに合わせる
		void AdjustTextureSize();
		// 初期化
		void Initialize();

	public:
		void SetAnimation(size_t spriteNum, int animationIntervel);
		// 更新
		void Update();
		// 描画
		void Draw();
		// 位置を画面中央にする
		void SetCenterPos() { position = Half(WIN_SIZE); }
		// anchorPoint = { 0.5f,0.5f } にする
		void SetCenterAnchor() { anchorPoint = { 0.5f,0.5f }; }
		// 静的初期化
		static void StaticInitialize();
		// テクスチャ読み込み
		static TextureData* LoadTexture(const std::string& FILE_NAME, uint32_t mipLevels = MIP_LEVELS_DEFAULT);
		// スプライト生成
		static std::unique_ptr<WristerEngine::_2D::Sprite> Create(const std::string& fileName,
			const Vector2& pos = {}, const Vector2& anchorPoint = {},
			const Vector2& textureSize = {}, const Vector2& textureLeftTop = {});
		// 描画前処理
		static void PreDraw();
		// getter
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() const { return tex->gpuHandle; }
		static ID3D12DescriptorHeap* GetDescriptorHeap() { return srvHeap.Get(); }
		// デスクリプタヒープのセット
		static void SetDescriptorHeaps();
		/// <summary>
		/// 切り取り領域を指定(描画サイズも変える)
		/// </summary>
		/// <param name="textureSize">切り取り領域のサイズ</param>
		/// <param name="textureLeftTop">切り取り領域の左上座標</param>
		void SetRect(const Vector2& textureSize, const Vector2& textureLeftTop = {});

		/// <summary>
		/// テクスチャ分割
		/// </summary>
		/// <param name="spritNum">分割数</param>
		void Split(const Vector2& spritNum);
	};
}