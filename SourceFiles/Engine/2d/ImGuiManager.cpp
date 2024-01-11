#include "ImGuiManager.h"
#include <imgui_impl_win32.h>
#include <imgui_impl_dx12.h>
#include "D3D12Common.h"
using namespace ImGui;
using namespace WristerEngine;
using namespace _2D;

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> ImGuiManager::srvHeap;

void ImGuiManager::Initialize()
{
	// �C���X�^���X�̎擾
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ImGui�̃R���e�L�X�g�𐶐�
	CreateContext();
	// ImGui�̃X�^�C����ݒ�
	StyleColorsDark();

	ImGui_ImplWin32_Init(WindowsAPI::GetInstance()->GetHwnd());

	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc{};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvHeapDesc.NumDescriptors = 1;
	Result result = DirectXCommon::GetInstance()->GetDevice()->
		CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));

	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	ImGui_ImplDX12_Init(dxCommon->GetDevice(),
		static_cast<int>(dxCommon->GetBackBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, srvHeap.Get(),
		srvHandle, srvGpuHandle);

	ImGuiIO& io = GetIO();
	// �W���t�H���g��ǉ�����
	io.Fonts->AddFontDefault();
}

void ImGuiManager::Begin()
{
	// ImGui�t���[���J�n
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	NewFrame();
}

void ImGuiManager::End() { Render(); }

void ImGuiManager::Draw()
{
	ID3D12GraphicsCommandList* cmdList = DirectXCommon::GetInstance()->GetCommandList();
	// �f�X�N���v�^�q�[�v�Z�b�g
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	ImGui_ImplDX12_RenderDrawData(GetDrawData(), cmdList);
}

void ImGuiManager::Finalize()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	DestroyContext();
}

void ImGuiManager::PrintVector(std::string str, const Vector2& vec)
{
	str += " = (%.3f, %.3f)";
	Text(str.c_str(), vec.x, vec.y);
}

void ImGuiManager::PrintVector(std::string str, const Vector3& vec)
{
	str += " = (%.3f, %.3f, %.3f)";
	Text(str.c_str(), vec.x, vec.y, vec.z);
}

void ImGuiManager::PrintQuaternion(std::string str, const Quaternion& q)
{
	str += " = (%.3f, %.3f, %.3f, %.3f)";
	Text(str.c_str(), q.w, q.x, q.y, q.z);
}

void ImGuiManager::SliderVector(std::string str, Vector2& vec, float minVal, float maxVal)
{
	float num[2] = { vec.x,vec.y };
	SliderFloat2(str.c_str(), num, minVal, maxVal);
	vec = { num[0],num[1] };
}

void ImGuiManager::SliderVector(std::string str, Vector3& vec, float minVal, float maxVal)
{
	float num[3] = { vec.x,vec.y,vec.z };
	SliderFloat3(str.c_str(), num, minVal, maxVal);
	vec = { num[0],num[1],num[2] };
}

void ImGuiManager::DragVector(std::string str, Vector2& vec, float spd)
{
	float num[2] = { vec.x,vec.y };
	DragFloat2(str.c_str(), num, spd);
	vec = { num[0],num[1] };
}

void ImGuiManager::DragVector(std::string str, Vector3& vec, float spd)
{
	float num[3] = { vec.x,vec.y,vec.z };
	DragFloat3(str.c_str(), num, spd);
	vec = { num[0],num[1],num[2] };
}

void ImGuiManager::InputVector(std::string str, Vector2& vec)
{
	float num[2] = { vec.x,vec.y };
	InputFloat2(str.c_str(), num);
	vec = { num[0],num[1] };
}

void ImGuiManager::InputVector(std::string str, Vector3& vec)
{
	float num[3] = { vec.x,vec.y,vec.z };
	InputFloat3(str.c_str(), num);
	vec = { num[0],num[1],num[2] };
}

void ImGuiManager::ColorEdit(std::string str, ColorRGB& color)
{
	float c[3] = { color.r,color.g,color.b };
	str += "Color";
	ColorEdit3(str.c_str(), c);
	color = { c[0],c[1],c[2] };
}

void ImGuiManager::ColorEdit(std::string str, ColorRGBA& color)
{
	float c[4] = { color.r,color.g,color.b,color.a };
	str += "Color";
	ColorEdit4(str.c_str(), c);
	color = { c[0],c[1],c[2],c[3] };
}