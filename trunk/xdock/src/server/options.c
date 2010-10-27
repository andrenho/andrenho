#include "options.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Options opt = {
	.toolkit = NO_VIEW,
	.listen_to = LOCALHOST,
	.debug = 1,
	.dock_color = 0x909090,
	.theme = "led",
	.colors = NULL,
	.attract = 40,
	.server_port = 52530,
};


static void parse_theme()
{
	char buf[255];
	FILE* f = fopen("../../share/themes.rc", "r"); // TODO
	if(f == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	int ret;
	do
	{
		ret = fscanf(f, "%255s", buf);
		if(buf[0] == '[' 
		&& !strncmp(&buf[1], opt.theme, strlen(opt.theme)-2))
		{
			char color_name[25];
			do
			{
				// theme found, start reading colors
				char eq[2], color[25];
				if(fscanf(f, "%25s", color_name) == EOF)
					break;
				if(color_name[0] == '[')
					break;
				if(fscanf(f, "%2s", eq) == EOF)
					break;
				if(fscanf(f, "%25s", color) == EOF)
					break;
				if(eq[0] != '=')
				{
					fprintf(stderr, "Parse error on theme file: "
							"'=' expected.\n");
					exit(EXIT_FAILURE);
				}

				struct ThemeColor* cl = malloc(sizeof(struct ThemeColor));
				strncpy(cl->name, color_name, 25);
				strncpy(cl->color, color, 20);
				HASH_ADD_STR(opt.colors, name, cl);
			} while(color_name[0] != '[');
		}
	} while(ret != EOF);

	// TODO - check that all colors are there

	fclose(f);
}


void opt_parse(int argc, char* argv[])
{
	(void) argc;
	(void) argv;

	// TODO - parse options
	parse_theme();
}
