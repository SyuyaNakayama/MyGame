#include "FontManager.h"
#include <assert.h>
#include <locale.h>

// lib
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )

void FontManager::Initialize()
{
	//// �W���o�͂Ƀ��j�R�[�h��\���ł���悤�ɂ���
	//setlocale(LC_ALL, "Japanese");
	//
	//hdc = WindowsAPI::GetInstance()->SetFont(L"");
	//// �t�H���g�r�b�g�}�b�v�擾
	//const wchar_t* c = L"S";
	//UINT code = (UINT)*c;
	//const int gradFlag = GGO_GRAY4_BITMAP;
	//// �K���̍ő�l
	//int grad = 0;
	//switch (gradFlag)
	//{
	//case GGO_GRAY2_BITMAP:
	//	grad = 4;
	//	break;
	//case GGO_GRAY4_BITMAP:
	//	grad = 16;
	//	break;
	//case GGO_GRAY8_BITMAP:
	//	grad = 64;
	//	break;
	//}

	//TEXTMETRIC tm;
	//GetTextMetrics(hdc, &tm);
	//GLYPHMETRICS gm;
	//CONST MAT2 mat = { {0,1},{0,0},{0,0},{0,1} };
	//DWORD size = GetGlyphOutlineW(hdc, code, gradFlag, &gm, 0, NULL, &mat);
	//BYTE* pMono = new BYTE[size];
	//GetGlyphOutlineW(hdc, code, gradFlag, &gm, size, pMono, &mat);

	//D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &pD2d1Factory);

	winApp = WindowsAPI::GetInstance();

	 /*
				ID2D1Factory�̐���
			*/
	HRESULT hResult = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &pD2d1Factory);
	assert(SUCCEEDED(hResult));


	/*
		IDWriteFactory�̐���
	*/
	hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWFactory));
	assert(SUCCEEDED(hResult));

	/*
		ID2D1HwndRenderTarget�̐���
	*/
	{
		D2D1_SIZE_U oPixelSize = {
			  WindowsAPI::WIN_SIZE.x
			, WindowsAPI::WIN_SIZE.y
		};

		D2D1_RENDER_TARGET_PROPERTIES oRenderTargetProperties = D2D1::RenderTargetProperties();

		D2D1_HWND_RENDER_TARGET_PROPERTIES oHwndRenderTargetProperties = D2D1::HwndRenderTargetProperties(winApp->GetHwnd(), oPixelSize);


		/*
			ID2D1HwndRenderTarget�̐���
		*/
		hResult = pD2d1Factory->CreateHwndRenderTarget(
			oRenderTargetProperties
			, oHwndRenderTargetProperties
			, &pRenderTarget
		);
		assert(SUCCEEDED(hResult));
	}



	// �w�i�̃N���A
	D2D1_COLOR_F oBKColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	pRenderTarget->Clear(oBKColor);

	// �u���V�̐���
		pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black)
			, &pBrush
		);
	// �e�L�X�g�t�H�[�}�b�g�̐���
		pDWFactory->CreateTextFormat(
			L"Meiryo"
			, NULL
			, DWRITE_FONT_WEIGHT_NORMAL
			, DWRITE_FONT_STYLE_NORMAL
			, DWRITE_FONT_STRETCH_NORMAL
			, 128
			, L""
			, &pTextFormat
		);
}

void FontManager::Draw()
{
	// �`��J�n(Direct2D)
	pRenderTarget->BeginDraw();
	
	std::wstring strText = L"Hello World!!";
	// �^�[�Q�b�g�T�C�Y�̎擾
	D2D1_SIZE_F oTargetSize = pRenderTarget->GetSize();
	// �e�L�X�g�̕`��
	pRenderTarget->DrawText(
		strText.c_str(),   // ������
		strText.size(),   // ������
		pTextFormat,
		&D2D1::RectF(0, 0, oTargetSize.width, oTargetSize.height),
		pBrush,
		D2D1_DRAW_TEXT_OPTIONS_NONE
	);
	
	// �`��I��(Direct2D)
	pRenderTarget->EndDraw();
}
