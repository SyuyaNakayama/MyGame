#pragma once
#include "WindowsAPI.h"
#include <d2d1.h>
#include <dwrite.h>

class FontManager
{
private:
	HDC hdc;
	ID2D1Factory* pD2d1Factory = NULL;
	IDWriteFactory* pDWFactory = NULL;
	ID2D1HwndRenderTarget* pRenderTarget = NULL;
	IDWriteTextFormat* pTextFormat = NULL;
	ID2D1SolidColorBrush* pBrush = NULL;
	WindowsAPI* winApp = NULL;

public:
	void Initialize();
	void Draw();
};