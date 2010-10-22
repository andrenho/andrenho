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
};

Theme theme;

static void parse_theme(char* theme, Theme* t)
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
		if(buf[0] == '[' && !strncmp(&buf[1], theme, strlen(theme)-2))
		{
			// theme found, start reading colors
			char color_name[25], eq[2], color[25];
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

			// select color
			if(!strcmp(color_name, "panel_bg"))
				t->panel_bg = strdup(color);
			else if(!strcmp(color_name, "panel_lt"))
				t->panel_lt = strdup(color);
			else if(!strcmp(color_name, "panel_lt"))
				t->panel_lt = strdup(color);
			else if(!strcmp(color_name, "panel_sw"))
				t->panel_sw = strdup(color);
			else if(!strcmp(color_name, "unlit"))
				t->unlit = strdup(color);
			else if(!strcmp(color_name, "lit"))
				t->lit = strdup(color);
			else if(!strcmp(color_name, "bright"))
				t->bright = strdup(color);
			else if(!strcmp(color_name, "glow"))
				t->glow = strdup(color);
			else if(!strcmp(color_name, "warning"))
				t->warning = strdup(color);
			else
				fprintf(stderr, "Color not found on theme file: %s.\n",
						color);
		}
	} while(ret != EOF);

	// check for valid theme
	if(t->panel_bg && t->panel_lt && t->panel_sw && t->unlit
	&& t->lit && t->bright && t->glow && t->warning)
	{
		fprintf(stderr, "Invalid theme %s.\n", theme);
		exit(EXIT_FAILURE);
	}

	fclose(f);
}


void opt_parse(int argc, char* argv[])
{
	(void) argc;
	(void) argv;

	// TODO - parse options
	memset(&theme, 0, sizeof(Theme));
	parse_theme(opt.theme, &theme);
}
