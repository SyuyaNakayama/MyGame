#pragma once
#include <string>
#include <d3dx12.h>
#include <wrl.h>
#include "Quaternion.h"
#include "Color.h"

namespace WristerEngine::_2D
{
	// ImGUI�̊Ǘ�
	class ImGuiManager final
	{
	private:
		ImGuiManager() = delete;
		~ImGuiManager() = delete;
		static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;

	public:
		// ������
		static void Initialize();
		// ImGui��t�J�n
		static void Begin();
		// ImGui��t�I��
		static void End();
		// ��ʂւ̕`��
		static void Draw();
		// �I������
		static void Finalize();
		// �x�N�g���l�̕`��
		static void PrintVector(std::string str, const Vector2& vec);
		static void PrintVector(std::string str, const Vector3& vec);
		// �N�H�[�^�j�I���̕`��
		static void PrintQuaternion(std::string str, const Quaternion& q);
		// �x�N�g���l�̃X���C�_�[�ύX
		static void SliderVector(std::string str, Vector2& vec, float minVal, float maxVal);
		static void SliderVector(std::string str, Vector3& vec, float minVal, float maxVal);
		// �x�N�g���l�̃h���b�O�ύX
		static void DragVector(std::string str, Vector2& vec, float spd = 0.1f);
		static void DragVector(std::string str, Vector3& vec, float spd = 0.1f);
		// �x�N�g���l�̓��͕ύX
		static void InputVector(std::string str, Vector2& vec);
		static void InputVector(std::string str, Vector3& vec);
		// �F�ύX
		static void ColorEdit(std::string str, ColorRGB& color);
		static void ColorEdit(std::string str, ColorRGBA& color);
	};
}