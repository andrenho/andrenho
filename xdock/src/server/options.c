#include "options.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

Options opt = {
	.toolkit = X11,
	.debug = 1,
	.theme = "led",
	.dock_color = 0x909090,
	.attract = 40,
	.listen_to = LOCALHOST,
	.server_port = 52530,
	.colors = NULL,
};


// Display version information and exit.
static void print_version()
{
	printf("xdockserver %s\n", VERSION);
	printf("Copyright (C) 2010 Andre' Wagner\n");
	printf("This is free software.  You may redistribute copies of it under the terms of\n");
	printf("the GNU General Public License <http://www.gnu.org/licenses/gpl.html>.\n");
	printf("There is NO WARRANTY, to the extent permitted by law.\n\n");
	printf("Written by Andre' Wagner.\n");
	exit(EXIT_SUCCESS);
}


// Display help information and exit.
static void print_usage(FILE* f)
{
	fprintf(f, "Usage: xdockserver [OPTION]...\n");
	fprintf(f, "Starts the xdock server. The xdock is is a applet server that emulates Window\nMaker docks.\n");
	fprintf(f, "\n");
	fprintf(f, "No arguments are mandatory. These arguments override the options set in the\n");
	fprintf(f, "config file ($HOME/.xdock/xdock.rc).\n");
	fprintf(f, "  -t, --theme    Choose the theme used to display the docks. Common themes\n");
	fprintf(f, "                 names are `led` and `lcd`. The themes are registered in\n");
	fprintf(f, "                 $SHARE/xdock/themes.rc or $HOME/.xdock/themes.rc.\n");
	fprintf(f, "  -c, --color    Color of the docks, in the format #rrggbb.\n");
	fprintf(f, "  -a, --attract  Distance (in pixels) from the right border where the dock will\n");
	fprintf(f, "                 start to be attracted.\n");
	fprintf(f, "  -l, --listen   Address the server will listen to. Possible values are\n");
	fprintf(f, "                 `localhost` and `all`.\n");
	fprintf(f, "  -p, --port     Server port.\n");
	fprintf(f, "  -d, --debug    Show debug information.\n");
	fprintf(f, "  -h, --help     Display this help and exit.\n");
	fprintf(f, "  -v, --version  Display version information and exit.\n");
	exit(EXIT_SUCCESS);
}


// Parse the configuration file.
static void parse_config_file()
{
	// TODO
}


// Parse the theme file.
void parse_theme()
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
		&& !strncmp(&buf[1], opt.theme, strlen(opt.theme)))
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


// Parse the arguments given in the command line, and the configuration files.
void opt_parse(int argc, char* argv[])
{
	char r[3], g[3], b[3];

	// parse config file
	parse_config_file();

	// parse arguments; the arguments override the config file
	int c;
	while(1)
	{
		static struct option long_options[] = {
			{ "version",  no_argument,          0, 'v' },
			{ "help",     no_argument,          0, 'h' },
			{ "theme",    required_argument,    0, 't' },
			{ "color",    required_argument,    0, 'c' },
			{ "attract",  required_argument,    0, 'a' },
			{ "listen",   required_argument,    0, 'l' },
			{ "port",     required_argument,    0, 'p' },
			{ "debug",    no_argument, &opt.debug, 'd' },
			{ 0, 0, 0, 0 }
		};

		int option_index = 0;
		if((c = getopt_long(argc, argv, "vhdt:c:a:l:p:", 
				    long_options, &option_index)) == -1)
			break;

		switch(c)
		{
			case 0: // set flag
				break;

			case 'v':
				print_version();
				break;

			case 'h':
				print_usage(stdout);
				break;

			case 't':
				opt.theme = strdup(optarg);
				break;

			case 'c':
				if(sscanf(optarg, "#%2s%2s%2s", r, g, b) != 3)
				{
					fprintf(stderr, "Invalid color %s.",
							optarg);
					exit(EXIT_FAILURE);
				}
				opt.dock_color = (strtol(r, NULL, 16) << 16) + 
					         (strtol(g, NULL, 16) << 8)  + 
						 strtol(b, NULL, 16);
				break;

			case 'a':
				opt.attract = strtol(optarg, NULL, 10);
				break;

			case 'l':
				if(strcmp(optarg, "localhost") == 0)
					opt.listen_to = LOCALHOST;
				else if(strcmp(optarg, "all") == 0)
					opt.listen_to = EVERYONE;
				else
				{
					fprintf(stderr, "Invalid value %s to "
						"parameter. Valid values are "
						"`localhost` and `all`.",
						optarg);
					exit(EXIT_FAILURE);
				}
				break;

			case 'p':
				opt.server_port = strtol(optarg, NULL, 10);
				if(opt.server_port == 0)
				{
					fprintf(stderr, "Invalid port %s.\n",
							optarg);
					exit(EXIT_FAILURE);
				}
				break;

			case '?':
				break;

			default:
				abort();
		}

		if (optind < argc)
		{
			fprintf(stderr, "Invalid option %s.\n", argv[optind]);
			exit(EXIT_FAILURE);
		}
	}

		
	// parse theme file
	parse_theme();

}
