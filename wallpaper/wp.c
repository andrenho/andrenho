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
	struct Image* image = (struct Image*)lua_newuserdata(L, sizeof(struct Image));
	image->w = row_stride/3;
	image->h = cinfo.output_height;
	image->buffer = malloc(image->w * 3 * image->h); // TODO how to free?

	// load image
	uint8_t* ptr = image->buffer;
	buffer = (*cinfo.mem->alloc_sarray) 
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
	while(cinfo.output_scanline < cinfo.output_height)
	{
		jpeg_read_scanlines(&cinfo, buffer, 1);
		memcpy(ptr, buffer, row_stride);
		ptr += row_stride;
	}
	jpeg_finish_decompress(&cinfo);

	// finish
	jpeg_destroy_decompress(&cinfo);
	fclose(f);

	printf("load_image\n");
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
	printf("save_image\n");
	lua_pushnumber(L, 0);
	return 1;
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
