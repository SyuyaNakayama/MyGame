#pragma once
#include <Windows.h>
#include "Vector.h"
#include <string>

// ウィンドウクラス処理
class WindowsAPI final
{
private:
	HWND hwnd;
	WNDCLASSEX w{};
	WindowsAPI() = default;
	
	// ウィンドウプロシージャ
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
	WindowsAPI(const WindowsAPI& obj) = delete;
	
	// ウィンドウサイズ
	static const Vector2 WIN_SIZE;
	// インスタンス取得
	static WindowsAPI* GetInstance();
	// 初期化
	void Initialize(const std::wstring& windowName = L"");
	// メッセージの処理
	bool ProcessMessage();
	// 終了
	void Finalize();
	
	// フォントを設定(現在は使わない)
	//HDC SetFont(const std::wstring& fontName);
	
	// getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }
};