#include <stdio.h>

#include "size5.xpm"
#include "size6.xpm"
#include "size7.xpm"

int main()
{
	char** size[3] = { size5, size6, size7 };

	int i;
	for(i=0; i<1; i++) {
		int img_w, img_h, colors, _;
		sscanf(size[i][0], "%d %d %d %d", &img_w, &img_h, &colors, &_);
		int w = img_w / 16, h = img_h / 16;
		
		char filename[50];
		sprintf(filename, "cgmono%d.bdf", i+5);
		FILE* f = fopen(filename, "w");
		if(!f)
			fprintf(stderr, "Could not open file.\n");
		fprintf(f, "STARTFONT 2.1\n");
		fprintf(f, "FONT -gnu-cgmono-medium-r-normal--%d-160-75-75-c-80-iso10646-1\n", i+5);
		fprintf(f, "SIZE %d %d %d\n", i+5, w, h);
		fprintf(f, "STARTPROPERTIES 2\n");
		fprintf(f, "FONT_ASCENT %d\n", h);
		fprintf(f, "FONT_DESCENT 1\n");
		fprintf(f, "ENDPROPERTIES\n");

		fprintf(f, "CHARS 1\n");
		fprintf(f, "STARTCHAR U+0041\n");
		fprintf(f, "ENCODING 65\n");
		fprintf(f, "SWIDTH 500 0\n");
		fprintf(f, "DWIDTH 8 0\n");
		fprintf(f, "BBX 8 16 0 -2\n");
		fprintf(f, "BITMAP\n");
		fprintf(f, "01\n");
		fprintf(f, "00\n");
		fprintf(f, "00\n");
		fprintf(f, "00\n");
		fprintf(f, "00\n");
		fprintf(f, "00\n");
		fprintf(f, "00\n");
		fprintf(f, "00\n");
		fprintf(f, "00\n");
		fprintf(f, "ENDCHAR\n");
		fprintf(f, "ENDFONT\n");
	}

	return 0;
}
