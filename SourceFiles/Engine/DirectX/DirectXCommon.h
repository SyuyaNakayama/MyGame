#pragma once
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <vector>
#include "FPS.h"
#include "WindowsAPI.h"
#include "Matrix4.h"

namespace WristerEngine
{
	// DirectX���
	class DirectXCommon final
	{
	private:
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

		ComPtr<ID3D12Device> device;
		ComPtr<IDXGIFactory7> dxgiFactory;
		ComPtr<ID3D12CommandAllocator> commandAllocator;
		ComPtr<ID3D12GraphicsCommandList> commandList;
		ComPtr<ID3D12CommandQueue> commandQueue;
		ComPtr<IDXGISwapChain4> swapchain;
		ComPtr<ID3D12DescriptorHeap> dsvHeap, rtvHeap;
		ComPtr<ID3D12Fence> fence;
		DXGI_SWAP_CHAIN_DESC1 swapchainDesc{};
		std::vector<ComPtr<ID3D12Resource>> backBuffers;
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle{};
		UINT64 fenceVal = 0;
		D3D12_VIEWPORT viewport{};
		FPS* fixFPS = nullptr;

		DirectXCommon() = default;
		~DirectXCommon() = default;
		// �f�o�C�X�̏�����
		void InitializeDevice();
		// �R�}���h���X�g�̏�����
		void InitializeCommand();
		// �X���b�v�`�F�[���̏�����
		void InitializeSwapchain();
		// �����_�[�^�[�Q�b�g�r���[�̏�����
		void InitializeRenderTargetView();
		// �[�x�o�b�t�@�̏�����
		void InitializeDepthBuffer();
		// �t�F���X�̏�����
		void InitializeFence();

	public:
		DirectXCommon(const DirectXCommon& obj) = delete;
		DirectXCommon& operator=(const DirectXCommon& obj) = delete;

		// �C���X�^���X�擾
		static DirectXCommon* GetInstance();
		// ������
		void Initialize();
		// �`��O����
		void PreDraw();
		// �`��㏈��
		void PostDraw();
		// setter
		void SetViewport(Vector2 viewportSize = WIN_SIZE, Vector2 viewportLeftTop = {});
		// getter
		ID3D12Device* GetDevice() const { return device.Get(); }
		ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
		size_t GetBackBufferCount() const { return backBuffers.size(); }
		Matrix4 GetViewportMatrix();
	};
}