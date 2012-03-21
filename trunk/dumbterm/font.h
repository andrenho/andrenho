#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>

class Font
{
public:
	Font();

private:
	void InitChar(const char c);

	FT_Library library;
	FT_Face face;
	FT_GlyphSlot slot;
};

#endif
