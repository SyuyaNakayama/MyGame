#pragma once
#include <array>
#include <memory>
#include "Color.h"
#include "DirectXCommon.h"

struct TextureData
{
	std::string fileName;
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle{};
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle{};
};

struct Sprite
{
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
	// �f�t�H���g�f�B���N�g��
	static std::string DEFAULT_TEXTURE_DIRECTORY_PATH;
	static ComPtr<ID3D12DescriptorHeap> srvHeap;
	static std::list<TextureData*> textures;
	const static Matrix4 matProj;
	std::array<Vertex, 4> vertices;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	ConstBufferData* constMap = nullptr;
	Vertex* vertMap = nullptr;
	Matrix4 matWorld;

	void AdjustTextureSize();
	void Initialize();

public:
	void Update();
	void Draw();
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() { return tex->gpuHandle; }
	static std::unique_ptr<Sprite> Create(const std::string& fileName);
	static void StaticInitialize();
	static TextureData* LoadTexture(const std::string& FILE_NAME, uint32_t mipLevels = MIP_LEVELS_DEFAULT);
	static void PreDraw();
	static ID3D12DescriptorHeap* GetDescriptorHeap() { return srvHeap.Get(); }
	static void SetDescriptorHeaps();
};