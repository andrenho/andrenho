#include "font.h"

Font::Font()
{
	int error = FT_Init_FreeType(&library);
	if(error)
		throw "FT_Init_FreeType";
	
	error = FT_New_Face(library,
			"data/Nouveau_IBM_Stretch.ttf",
			0,
			&face);
	if(error)
		throw "FT_New_Face";

	error = FT_Set_Char_Size(face, 0, 12*64, 300, 300);
	if(error)
		throw "FT_Set_Char_Size";

	slot = face->glyph;

	InitChar('A');
}


void Font::InitChar(const char c)
{
	int error = FT_Load_Char(face, c, FT_LOAD_DEFAULT);
	if(error)
		throw "FT_Load_Char";

	FT_Bitmap *bmp = &slot->bitmap;

	int i = 0;
	for(int y=0; y<bmp->rows; y++)
	{
		for(int x=0; x<bmp->width; x++, i++)
			printf("%02X ", bmp->buffer[i]);
		printf("\n");
	}
}
