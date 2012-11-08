#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LUA_LIB
#include "lua.h"
#include "lauxlib.h"

#include <jpeglib.h>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Image {
	int w, h;
	int has_alpha;
	uint8_t* buffer;
};

struct Style {
	uint32_t color;
	const char* font;
	int point_size;
};


FT_Library lib;

static int load_image(lua_State *L)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPARRAY buffer;
	int row_stride;

	// get LUA arguments
	const char* filename = luaL_checkstring(L, 1);

	// initialize JPEG
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	// open file
	FILE* f;
	if((f = fopen(filename, "rb")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", filename);
		exit(1);
	}
	jpeg_stdio_src(&cinfo, f);

	// open image
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);
	row_stride = cinfo.output_width * cinfo.output_components;

	// create LUA image
	struct Image* image = (struct Image*) malloc(sizeof(struct Image));
	image->w = row_stride/3;
	image->h = cinfo.output_height;
	image->has_alpha = 0;
	image->buffer = malloc(image->w * 3 * image->h);

	// load image
	uint8_t* ptr = image->buffer;
	buffer = (*cinfo.mem->alloc_sarray) 
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
	while(cinfo.output_scanline < cinfo.output_height)
	{
		jpeg_read_scanlines(&cinfo, buffer, 1);
		memcpy(ptr, buffer[0], row_stride);
		ptr += row_stride;
	}
	jpeg_finish_decompress(&cinfo);

	// finish
	jpeg_destroy_decompress(&cinfo);
	fclose(f);

	lua_pushlightuserdata(L, image);
	return 1;
}

static void check_styles(lua_State *L, int idx, struct Style* style)
{
	lua_pushnil(L);
	while(lua_next(L, 3))
	{
		const char* key = luaL_checkstring(L, -2);
		if(!strcmp(key, "color"))
			style->color = luaL_checkinteger(L, -1);
		else if(!strcmp(key, "font"))
			style->font = luaL_checkstring(L, -1);
		else if(!strcmp(key, "pointsize"))
			style->point_size = luaL_checkinteger(L, -1);
		else
			luaL_error(L, "invalid style %s", key);

		lua_pop(L, 1);
	}
}

static void wrap_text(FT_Face face, const char* text, int w, 
		      int* new_w, int* new_h, int* origin)
{
	FT_GlyphSlot slot = face->glyph;
	int i = -1;

	(*new_w) = (*new_h) = (*origin) = 0;
	int down = 0;
	while(text[++i])
	{
		if(FT_Load_Char(face, text[i], FT_LOAD_RENDER))
			continue;
		(*new_w) += slot->advance.x >> 6;
		if((*origin) < slot->metrics.horiBearingY >> 6)
			(*origin) = slot->metrics.horiBearingY >> 6;
		if(down < (slot->metrics.height - slot->metrics.horiBearingY) >> 6)
			down = (slot->metrics.height - slot->metrics.horiBearingY) >> 6;
	}
	(*origin) = face->ascender >> 6;
	(*new_h) = face->height >> 6;
	printf("%d %d\n", *origin, *new_h);
}


static inline void draw_letter(struct Image* image, struct Style style, 
		FT_Bitmap* bitmap, int pos_x, int pos_y)
{
	int x, y, i=0;
	for(y=0; y<bitmap->rows; y++)
		for(x=0; x<bitmap->width; x++)
		{
			int px = pos_x + x, py = pos_y + y;
			if(px >= 0 && py >= 0 && px < image->w && py < image->h)
			{
				int p = ((py * image->w) + px) * 4;
				image->buffer[p] = (style.color >> 16) & 0xff;
				image->buffer[p+1] = (style.color >> 8) & 0xff;
				image->buffer[p+2] = style.color & 0xff;
				image->buffer[p+3] = bitmap->buffer[i++];
			}
		}
}


static int create_text(lua_State *L)
{
	// get LUA parameters
	const char* text = luaL_checkstring(L, 1);
	int w = luaL_checkinteger(L, 2);
	if(!lua_istable(L, 3))
		return luaL_argerror(L, 3, "a table is required");

	// check styles
	struct Style style = {
		.font = "Arial",
		.point_size = 36,
		.color = 0x0
	};
	check_styles(L, 3, &style);

	// load font
	FT_Face face;
	if(FT_New_Face(lib, style.font, 0, &face))
		return luaL_error(L, "error loading font");
	if(FT_Set_Char_Size(face, 0, style.point_size * 64, 0, 0))
		return luaL_error(L, "error setting font size");

	// create image
	int new_w, new_h, origin, i;
	wrap_text(face, text, w, &new_w, &new_h, &origin);
	struct Image* image = malloc(sizeof(struct Image));
	//printf("%d %d\n", new_w, new_h);
	image->w = new_w;
	image->h = new_h;
	image->has_alpha = 1;
	image->buffer = malloc(new_w * new_h * 4);
	for(i=0; i<(new_w * new_h * 4); i += 4)
	{
		image->buffer[i] = image->buffer[i+1] = image->buffer[i+2] = 0;
		image->buffer[i+3] = 0x0;
	}

	// draw text
	FT_GlyphSlot slot = face->glyph;
	int pen_x = 0, 
	    pen_y = origin;
	i = -1;
	while(text[++i])
	{
		if(FT_Load_Char(face, text[i], FT_LOAD_RENDER))
			continue;

		// draw letter
		draw_letter(image, style, &slot->bitmap, 
				pen_x + slot->bitmap_left,
				pen_y - slot->bitmap_top);
		
		pen_x += slot->advance.x >> 6;
	}
	
	// return value
	lua_pushlightuserdata(L, image);
	return 1;
}

static inline void paste_pixel(struct Image* from, struct Image* to, 
		int x, int y, int pos_x, int pos_y)
{	
	if(pos_x+x < 0 || pos_x+x >= to->w || pos_y+y < 0 || pos_y+y >= to->h)
		return;

	double alpha = (double)from->buffer[((y * from->w) + x) * 4 + 3] / 255;
	if(alpha == 0)
		return;

	int pt = (((pos_y+y) * to->w) + (pos_x+x)) * 3;
	int pf = ((y * from->w) + x) * 4;

	int i;
	for(i=0; i<3; i++)
	{
		int diff = (from->buffer[pf+i] - to->buffer[pt+i]) * alpha;
		to->buffer[pt+i] += diff;
	}
}

static int paste(lua_State *L)
{
	// get LUA params
	struct Image* from = lua_touserdata(L, 2);
	struct Image* to = lua_touserdata(L, 1);
	int pos_x = luaL_checkinteger(L, 3),
	    pos_y = luaL_checkinteger(L, 4);

	if(!from->has_alpha || to->has_alpha)
		luaL_error(L, "not implemented: from must not be alpha and to "
				"must be alpha");

	// paste
	int x, y;
	for(x=0; x<(from->w); x++)
		for(y=0; y<(from->h); y++)
			paste_pixel(from, to, x, y, pos_x, pos_y);
	return 0;
}

static int save_image(lua_State *L)
{
	// get LUA arguments
	struct Image* image = (struct Image*)lua_touserdata(L, 1);
	const char* filename = luaL_checkstring(L, 2);

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE * outfile;
	JSAMPROW row_pointer[1];
	int row_stride;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	if ((outfile = fopen(filename, "wb")) == NULL) 
	{
		fprintf(stderr, "can't open %s\n", filename);
		exit(1);
	}
	jpeg_stdio_dest(&cinfo, outfile);

	cinfo.image_width = image->w;
	cinfo.image_height = image->h;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 95, TRUE);

	jpeg_start_compress(&cinfo, TRUE);
	row_stride = image->w * 3;
	while(cinfo.next_scanline < cinfo.image_height)
	{
		row_pointer[0] = &image->buffer[cinfo.next_scanline * row_stride];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	fclose(outfile);
	jpeg_destroy_compress(&cinfo);

	free(image->buffer);
	free(image);

	return 0;
}

static const luaL_reg wp[] = 
{
	{ "load_image",  load_image  },
	{ "create_text", create_text },
	{ "paste",       paste       },
	{ "save_image",  save_image  },
	{ NULL, NULL }
};

LUALIB_API int luaopen_wp(lua_State *L)
{
	luaL_register(L, "wp", wp);

	if(FT_Init_FreeType(&lib))
	{
		fprintf(stderr, "Error intializing FreeType.\n");
		exit(1);
	}

	return 1;
}
