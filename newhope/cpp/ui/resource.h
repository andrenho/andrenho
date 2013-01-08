#ifndef UI_RESOURCE_H
#define UI_RESOURCE_H

#include <string>

#include "libs/graphiclibrary.h"
#include "libs/rect.h"

class Resources {
public:
	Resources(GraphicLibrary const& video);
	~Resources();

private:
	std::string FindFile(std::string const& filename);
	void LoadFile(std::string const& name, std::string const& path, 
			Rect const& r, std::string const& suffix);
	void LoadFile(std::string const& name, std::string const& path);

	GraphicLibrary const& video;
};

#endif
