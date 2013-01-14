#ifndef UI_RESOURCE_H
#define UI_RESOURCE_H

#include <string>
#include <map>

#include "libs/graphiclibrary.h"
#include "libs/rect.h"
#include "libs/resource.h"

typedef std::map<const std::string, const Resource*> mapR;

class Resources {
public:
	Resources(GraphicLibrary const& video);
	~Resources();

	inline const Image* Img(std::string const& s) const {
		return dynamic_cast<const Image*>(res.at(s));
	}

	inline const Image* operator[](std::string const& s) const {
		return dynamic_cast<const Image*>(res.at(s));
	}

private:
	std::string const FindFile(std::string const& filename);
	void LoadFile(std::string const& name, std::string const& path, 
			Rect const& r, std::string const& suffix);
	void LoadFile(std::string const& name, std::string const& path);

	GraphicLibrary const& video;
	mapR res;
};

#endif
