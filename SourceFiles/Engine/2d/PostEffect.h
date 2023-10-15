#pragma once
#include <array>
#include <wrl.h>
#include <d3d12.h>
#include "Color.h"
#include "Matrix4.h"

// �|�X�g�G�t�F�N�g
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

	// �o�b�t�@����
	void CreateBuffers();
	// �V�F�[�_�[���\�[�X�r���[����
	void CreateSRV();
	// �����_�[�^�[�Q�b�g�r���[����
	void CreateRTV();
	// �f�v�X�X�e���V���r���[����
	void CreateDSV();
public:
	// ������
	void Initialize();
	// �`��
	void Draw();
	// �V�[���`��O����
	void PreDrawScene();
	// �V�[���`��㏈��
	void PostDrawScene();
};