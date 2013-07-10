typedef struct {
	int w, h;
	const char* const* map;
} LevelMap;

LevelMap levels[] = {
	{ 
		9, 7, (const char const*[]) {
			".........",
			"1       .",
			".    X  #",
			".       .",
			".       .",
			".       .",
			".........", 
		}
       },
};
