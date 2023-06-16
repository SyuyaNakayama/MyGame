#include "DirectXCommon.h"
#include "D3D12Common.h"
#include <vector>
#include <thread>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
using namespace std;
using namespace std::chrono;

const Vector2 WIN_SIZE = WindowsAPI::WIN_SIZE;

DirectXCommon* DirectXCommon::GetInstance()
{
	static DirectXCommon* dxCommon = new DirectXCommon;
	return dxCommon;
}

void DirectXCommon::Initialize()
{
	InitializeFixFPS();				// FPS�Œ菉����
	InitializeDevice();				// �f�o�C�X�̐���
	InitializeCommand();			// �R�}���h�֘A�̏�����
	InitializeSwapchain();			// �X���b�v�`�F�[���̏�����
	InitializeRenderTargetView();	// �����_�[�^�[�Q�b�g�r���[�̏�����
	InitializeDepthBuffer();		// �[�x�o�b�t�@�̏�����
	InitializeFence();				// �t�F���X�̏�����

	// �r���[�|�[�g�ݒ�R�}���h
	viewport = CD3DX12_VIEWPORT(0.0f, 0.0f, WIN_SIZE.x, WIN_SIZE.y);
}

void DirectXCommon::InitializeDevice()
{
#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	ComPtr<ID3D12Debug1> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif
	Result result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));

	vector<ComPtr<IDXGIAdapter4>> adapters;
	ComPtr<IDXGIAdapter4> tmpAdapter;
	// �p�t�H�[�}���X���������̂��珇�ɁA�S�ẴA�_�v�^�[��񋓂���
	for (UINT i = 0;
		dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;	i++)
	{
		// ���I�z��ɒǉ�����
		adapters.push_back(tmpAdapter);
	}
	// �Ó��ȃA�_�v�^��I�ʂ���
	for (auto& adapter : adapters)
	{
		DXGI_ADAPTER_DESC3 adapterDesc;
		// �A�_�v�^�[�̏����擾����
		adapter->GetDesc3(&adapterDesc);
		// �\�t�g�E�F�A�f�o�C�X�����
		if ((adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) { continue; }
		// �f�o�C�X���̗p���ă��[�v�𔲂���
		tmpAdapter = adapter;
		break;
	}

	D3D_FEATURE_LEVEL featureLevel{};
	// �Ή����x���̔z��
	vector<D3D_FEATURE_LEVEL> levels =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	for (auto& level : levels)
	{
		// �̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
		if (FAILED(D3D12CreateDevice(tmpAdapter.Get(), level, IID_PPV_ARGS(&device)))) { continue; }
		// �f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
		featureLevel = level;
		break;
	}

#ifdef _DEBUG
	// �G���[���Ƀu���[�N�𔭐�������
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
		// �}������G���[
		D3D12_MESSAGE_ID denyIds[] = {
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE };
		// �}������\�����x��
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		// �w�肵���G���[�̕\����}������
		infoQueue->PushStorageFilter(&filter);
		// �G���[���Ƀu���[�N�𔭐�������
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
	}
#endif
}

void DirectXCommon::InitializeCommand()
{
	Result result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));

	result = device->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator.Get(), nullptr,
		IID_PPV_ARGS(&commandList));

	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
}

void DirectXCommon::InitializeSwapchain()
{
	swapchainDesc.Width = (UINT)WIN_SIZE.x;
	swapchainDesc.Height = (UINT)WIN_SIZE.y;
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �F���̏���
	swapchainDesc.SampleDesc.Count = 1; // �}���`�T���v�����Ȃ�
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER; // �o�b�N�o�b�t�@�p
	swapchainDesc.BufferCount = 2; // �o�b�t�@����2�ɐݒ�
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // �t���b�v��͔j��
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ComPtr<IDXGISwapChain1> swapchain1;
	Result result = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue.Get(), WindowsAPI::GetInstance()->GetHwnd(), &swapchainDesc, nullptr, nullptr,
		&swapchain1);

	result = swapchain1->QueryInterface(IID_PPV_ARGS(&swapchain));
}

void DirectXCommon::InitializeRenderTargetView()
{
	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // �����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = swapchainDesc.BufferCount; // ���\��2��
	// �f�X�N���v�^�q�[�v�̐���
	Result result = device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

	backBuffers.resize(swapchainDesc.BufferCount);

	for (int i = 0; i < backBuffers.size(); i++)
	{
		swapchain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		rtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeap->GetCPUDescriptorHandleForHeapStart(),
			i, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		device->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}

void DirectXCommon::InitializeDepthBuffer()
{
	CD3DX12_RESOURCE_DESC depthResourceDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			(UINT64)WindowsAPI::WIN_SIZE.x,
			(UINT)WindowsAPI::WIN_SIZE.y,
			1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

	ID3D12Resource* depthBuff = nullptr;
	Result result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE, &depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0),
		IID_PPV_ARGS(&depthBuff));

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(
		depthBuff, &dsvDesc, dsvHeap->GetCPUDescriptorHandleForHeapStart());
}

void DirectXCommon::InitializeFence()
{
	Result result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}

void DirectXCommon::InitializeFixFPS() { reference_ = steady_clock::now(); }

void DirectXCommon::UpdateFixFPS()
{
	// 1/60�b�҂�����̎���
	const microseconds MIN_TIME(uint64_t(1000000.0f / 60.0f));
	// 1/60�b���킸���ɒZ������
	const microseconds MIN_CHECK_TIME(uint64_t(1000000.0f / 65.0f));

	// ���ݎ��Ԃ��擾����
	steady_clock::time_point now = steady_clock::now();
	// �O��L�^����̌o�ߎ��Ԃ��擾����
	microseconds elapsed = duration_cast<microseconds>(now - reference_);

	// 1/60�b(���킸���ɒZ������)�o���Ă��Ȃ��ꍇ
	if (elapsed < MIN_CHECK_TIME)
	{
		// 1/60�b�o�߂���܂Ŕ����ȃX���[�v���J��Ԃ�
		while (steady_clock::now() - reference_ < MIN_TIME)
		{
			// 1�}�C�N���b�X���[�v
			this_thread::sleep_for(microseconds(1));
		}
	}

	// ���݂̎��Ԃ��L�^����
	reference_ = steady_clock::now();
}

void DirectXCommon::PreDraw()
{
	UINT bbIndex = swapchain->GetCurrentBackBufferIndex();

	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffers[bbIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	rtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeap->GetCPUDescriptorHandleForHeapStart(),
		(size_t)bbIndex, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));

	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	commandList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	float clearColor[] = { 0,0,0,0 }; // ��
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	commandList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, (LONG)WIN_SIZE.x, (LONG)WIN_SIZE.y)); // �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	commandList->RSSetViewports(1, &viewport); // �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
}

void DirectXCommon::PostDraw()
{
	UINT bbIndex = swapchain->GetCurrentBackBufferIndex();

	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffers[bbIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	// ���߂̃N���[�Y
	Result result = commandList->Close();
	// �R�}���h���X�g�̎��s
	ID3D12CommandList* commandLists[] = { commandList.Get() };
	commandQueue->ExecuteCommandLists(1, commandLists);

	// ��ʂɕ\������o�b�t�@���t���b�v(���\�̓��ւ�)
	result = swapchain->Present(1, 0);

	// �R�}���h�̎��s������҂�
	commandQueue->Signal(fence.Get(), ++fenceVal);
	if (fence->GetCompletedValue() != fenceVal)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceVal, event);
		if (event != 0)
		{
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
	}

	UpdateFixFPS(); // FPS�Œ�

	// �L���[���N���A
	result = commandAllocator->Reset();
	// �ĂуR�}���h���X�g�𒙂߂鏀��
	result = commandList->Reset(commandAllocator.Get(), nullptr);
}

void DirectXCommon::SetViewport(Vector2 viewportSize, Vector2 viewportLeftTop)
{
	viewport = CD3DX12_VIEWPORT(viewportLeftTop.x, viewportLeftTop.y,
		viewportSize.x, viewportSize.y);
}

Matrix4 DirectXCommon::GetViewportMatrix()
{
	Matrix4 mat;
	mat.m[0][0] = viewport.Width / 2.0f;
	mat.m[1][1] = viewport.Height / 2.0f;
	mat.m[3][0] = viewport.TopLeftX + viewport.Width / 2.0f;
	mat.m[3][1] = viewport.TopLeftY + viewport.Height / 2.0f;
	return mat;
}
