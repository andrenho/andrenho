#ifndef UI_RESOURCE_H
#define UI_RESOURCE_H

#include <string>
#include <map>

#include "libs/graphiclibrary.h"
#include "libs/rect.h"
#include "libs/resource.h"

class Resources {
public:
	Resources(GraphicLibrary const& video);
	~Resources();

	// TODO - use find!
	inline const Resource* & operator[](std::string const& s) { return res[s]; }
	inline const Image* Img(std::string const& s) const { return dynamic_cast<const Image*>(res[s]); }

private:
	std::string FindFile(std::string const& filename);
	void LoadFile(std::string const& name, std::string const& path, 
			Rect const& r, std::string const& suffix);
	void LoadFile(std::string const& name, std::string const& path);

	GraphicLibrary const& video;
	std::map<const std::string, const Resource*> res;
};

#endif
