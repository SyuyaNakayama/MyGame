#pragma once
#include <Windows.h>
#include "Vector.h"
#include <string>

namespace WristerEngine
{
	// �E�B���h�E�T�C�Y
	const Vector2 WIN_SIZE = { 1280,720 };
	// �E�B���h�E�T�C�Y�̔���(UI�`��ȂǂɎg��)
	const Vector2 HALF_WIN_SIZE = WIN_SIZE / 2.0f;
	
	// �E�B���h�E�N���X����
	class WindowsAPI final
	{
	private:
		HWND hwnd;
		WNDCLASSEX w{};
		WindowsAPI() = default;

		// �E�B���h�E�v���V�[�W��
		static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	public:
		WindowsAPI(const WindowsAPI& obj) = delete;

		// �C���X�^���X�擾
		static WindowsAPI* GetInstance();
		// ������
		void Initialize(const std::wstring& windowName = L"");
		// ���b�Z�[�W�̏���
		bool ProcessMessage();
		// �I��
		void Finalize();

		// getter
		HWND GetHwnd() const { return hwnd; }
		HINSTANCE GetHInstance() const { return w.hInstance; }
	};
}