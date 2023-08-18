#include "FontManager.h"
#include <assert.h>
#include <codecvt>
constexpr auto WIDTH = 500;
constexpr auto HEIGHT = 300;

void FontManager::Initialize()
{
	// library��������
	if (image != nullptr) { free(image); }
	image = nullptr;
	auto error = FT_Init_FreeType(&library);
	assert(!error);
}

void FontManager::SetFont(const char* font_file_name, int char_width, int char_height)
{
	// 2. face���쐬
	auto error = FT_New_Face(library, font_file_name, 0, &face);
	assert(!error);

	// 3. �����T�C�Y��ݒ�
	error = FT_Set_Char_Size(face, 0,
		char_width * char_height, // ���ƍ���
		300, 300);  // �����A�����𑜓x*/
	assert(!error);
	
	slot = face->glyph;  // �O���t�ւ̃V���[�g�J�b�g
}

void FontManager::DrawBitmap(int x, int y)
{
	int  i, j, p, q;
	const int  x_max = x + (slot->bitmap).width;
	const int  y_max = y + (slot->bitmap).rows;

	for (i = x, p = 0; i < x_max; i++, p++) {
		for (j = y, q = 0; j < y_max; j++, q++) {
			if (i < 0 || j < 0 || i >= WIDTH || j >= HEIGHT) continue;
			image[j * WIDTH + i] |= (slot->bitmap).buffer[q * (slot->bitmap).width + p];
		}
	}
}

void FontManager::DrawString(const std::string& text)
{
	image = new unsigned char[WIDTH * HEIGHT];

	int curPosX = 0;
	int curPosY = 60; //���݂̃J�[�\���ʒu
	int last_height = 0; //�Ō�ɕ������������Ƃ��̕����̑傫��

	for (int n = 0; n < text.size(); n++) {
		if (text[n] == '\n') {
			curPosX = 0;
			curPosY += last_height + 20;
		}
		else {
			if (FT_Load_Char(face, text[n], FT_LOAD_RENDER)) continue; //�ꕶ�������_�����O
			// int yMax = face->bbox.yMax;
			// int yMin = face->bbox.yMin;
			// int baseline = bitmap->rows * yMax / (yMax - yMin);
			DrawBitmap(curPosX, curPosY - slot->bitmap_top); //image��slot->bitmap�̒��g���R�s�[����
		}
		last_height = (slot->bitmap).rows;

		curPosX += slot->advance.x >> 6;
		curPosY += slot->advance.y >> 6;
	}
}

FontManager::~FontManager()
{
	if (image != nullptr) free(image);
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}