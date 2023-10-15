#pragma once
#include <Windows.h>
#include "Vector.h"
#include <string>

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
	
	// �E�B���h�E�T�C�Y
	static const Vector2 WIN_SIZE;
	// �C���X�^���X�擾
	static WindowsAPI* GetInstance();
	// ������
	void Initialize(const std::wstring& windowName = L"");
	// ���b�Z�[�W�̏���
	bool ProcessMessage();
	// �I��
	void Finalize();
	
	// �t�H���g��ݒ�(���݂͎g��Ȃ�)
	//HDC SetFont(const std::wstring& fontName);
	
	// getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }
};