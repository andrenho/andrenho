#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LUA_LIB
#include "lua.h"
#include "lauxlib.h"

#include <jpeglib.h>

struct Image {
	int w, h;
	uint8_t* buffer;
};

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

static int create_text(lua_State *L)
{
	printf("create_text\n");
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

static const luaL_reg wp[] = {
	{ "load_image",  load_image  },
	{ "create_text", create_text },
	{ "paste",       paste       },
	{ "save_image",  save_image  },
	{ NULL, NULL }
};

LUALIB_API int luaopen_wp(lua_State *L)
{
	luaL_register(L, "wp", wp);
	return 1;
}
