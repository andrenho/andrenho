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
		      int* new_w, int* new_h)
{
	FT_GlyphSlot slot = face->glyph;
	int i = -1;

	(*new_w) = (*new_h) = 0;
	while(text[++i])
	{
		if(FT_Load_Char(face, text[i], FT_LOAD_RENDER))
			continue;
		(*new_w) += slot->advance.x >> 6;
		if((*new_h) < slot->metrics.height >> 6)
			(*new_h) = slot->metrics.height >> 6;
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
	int new_w, new_h, i;
	wrap_text(face, text, w, &new_w, &new_h);
	struct Image* image = malloc(sizeof(struct Image));
	image->w = new_w;
	image->h = new_h;
	image->has_alpha = 1;
	image->buffer = malloc(new_w * new_h * 4);
	for(i=0; i<(new_w * new_h * 4); i += 4)
	{
		image->buffer[i] = image->buffer[i+1] = image->buffer[i+2] = 0;
		image->buffer[i+3] = 0xff;
	}

	// draw text
	FT_GlyphSlot slot = face->glyph;
	int pen_x = 0, pen_y = 0;
	while(text[++i])
	{
		if(FT_Load_Char(face, text[i], FT_LOAD_RENDER))
			continue;
		// ...
		pen_x += slot->advance.x >> 6;
	}
	

	lua_pushnumber(L, 0);
	return 1;
}

static int paste(lua_State *L)
{
	printf("paste\n");
	lua_pushnumber(L, 0);
	return 1;
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
