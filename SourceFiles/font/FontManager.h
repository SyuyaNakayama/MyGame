#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

class FontManager
{
private:
	FT_Library library;   /* handle to library     */
	FT_Face face;      /* handle to face object */
	unsigned char* image;
	FT_GlyphSlot slot;  // グリフへのショートカット
	void DrawBitmap(int x, int y);

public:
	void Initialize();
	~FontManager();
	
	void SetFont(const char* font_file_name, int char_width, int char_height);
	void DrawString(const std::string& text);
	unsigned char* GetImage() { return image; }

};