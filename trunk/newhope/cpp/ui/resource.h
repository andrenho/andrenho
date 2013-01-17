#ifndef UI_RESOURCE_H
#define UI_RESOURCE_H

#include <map>
#include <stdexcept>
#include <string>

#include "libs/graphiclibrary.h"
#include "libs/resource.h"
#include "util/logger.h"
#include "util/rect.h"

typedef std::map<const std::string, const Resource*> mapR;

class Resources {
public:
	Resources(GraphicLibrary const& video);
	~Resources();

	inline const Image* operator[](std::string const& s) const {
		try 
		{
			return dynamic_cast<const Image*>(res.at(s));
		} 
		catch(std::out_of_range& e)
		{
			logger.Error(1, "Image resource %s does not exists.", 
					s.c_str());
			abort();
		}
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
