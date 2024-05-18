#pragma once
#include <array>
#include <memory>
#include "Color.h"
#include "DirectXCommon.h"

namespace WristerEngine::_2D
{
	// �e�N�X�`��1�����̃f�[�^
	struct TextureData
	{
		std::string fileName;
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle{};
		D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle{};
	};

	//struct Sprite;


	// �X�v���C�g
	struct Sprite
	{
		// �f�t�H���g�f�B���N�g��
		static std::string DEFAULT_TEXTURE_DIRECTORY_PATH;

		Vector2 position;
		float rotation = 0;
		ColorRGBA color;
		Vector2 size; // �\���T�C�Y
		Vector2 anchorPoint;
		bool isFlipX = false;
		bool isFlipY = false;
		bool isInvisible = false;
		Vector2 textureLeftTop; // �؂���̈�̍�����W
		Vector2 textureSize; // �؂���̈�̃T�C�Y
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
			/// ������
			/// </summary>
			/// <param name="sprite">sprite�|�C���^</param>
			/// <param name="spriteNum">�A�j���[�V��������</param>
			/// <param name="animationIntervel">�A�j���[�V�������x</param>
			void Initialize(Sprite* sprite, size_t spriteNum, int animationIntervel);
			// �X�V
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
			LB, // ����
			LT, // ����
			RB, // �E��
			RT  // �E��
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

		// �e�N�X�`���T�C�Y���C���[�W�ɍ��킹��
		void AdjustTextureSize();
		// ������
		void Initialize();

	public:
		void SetAnimation(size_t spriteNum, int animationIntervel);
		// �X�V
		void Update();
		// �`��
		void Draw();
		// �ʒu����ʒ����ɂ���
		void SetCenterPos() { position = Half(WIN_SIZE); }
		// anchorPoint = { 0.5f,0.5f } �ɂ���
		void SetCenterAnchor() { anchorPoint = { 0.5f,0.5f }; }
		// �ÓI������
		static void StaticInitialize();
		// �e�N�X�`���ǂݍ���
		static TextureData* LoadTexture(const std::string& FILE_NAME, uint32_t mipLevels = MIP_LEVELS_DEFAULT);
		// �X�v���C�g����
		static std::unique_ptr<WristerEngine::_2D::Sprite> Create(const std::string& fileName,
			const Vector2& pos = {}, const Vector2& anchorPoint = {},
			const Vector2& textureSize = {}, const Vector2& textureLeftTop = {});
		// �`��O����
		static void PreDraw();
		// getter
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() const { return tex->gpuHandle; }
		static ID3D12DescriptorHeap* GetDescriptorHeap() { return srvHeap.Get(); }
		// �f�X�N���v�^�q�[�v�̃Z�b�g
		static void SetDescriptorHeaps();
		/// <summary>
		/// �؂���̈���w��(�`��T�C�Y���ς���)
		/// </summary>
		/// <param name="textureSize">�؂���̈�̃T�C�Y</param>
		/// <param name="textureLeftTop">�؂���̈�̍�����W</param>
		void SetRect(const Vector2& textureSize, const Vector2& textureLeftTop = {});

		/// <summary>
		/// �e�N�X�`������
		/// </summary>
		/// <param name="spritNum">������</param>
		void Split(const Vector2& spritNum);
	};
}