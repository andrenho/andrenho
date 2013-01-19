#include "ui/resource.h"

#include <cstdlib>
#include <sys/stat.h>
#include <iostream>

#include "ui/resource_list.h"
#include "util/logger.h"

Resources::Resources(GraphicLibrary const& video)
	: video(video)
{
	for(auto const& res: reslist)
	{
		std::string filepath = FindFile(res.filename);

		if(res.suffix.empty())
			LoadFile(res.name, filepath);
		else
			for(unsigned int i=0; i<res.suffix.size(); i++)
				LoadFile(res.name, filepath, res.r[i],
						res.suffix[i]);
		logger.Debug(filepath + " loaded.");
	}
}


Resources::~Resources()
{
	logger.Debug("Freeing resources.");
	std::map<const std::string, const Resource*>::iterator it;
	for(it=res.begin(); it != res.end(); it++)
		delete (*it).second;
}


std::string const 
Resources::FindFile(std::string const& filename)
{
	std::string buf[2];
	buf[0] = std::string(DATADIR) + "/" + filename; // data dir
	buf[1] = std::string("data/") + filename;       // runs without install

	for(int i=0; i<2; i++)
	{
		struct stat b;
		if(stat(buf[i].c_str(), &b) == 0)
			return buf[i];
	}

	return "";
}


void
Resources::LoadFile(std::string const& name, std::string const& path, 
		Rect const& r, std::string const& suffix)
{
	size_t found = path.find_last_of('.');
	std::string filesuffix = path.substr(found);
	if(filesuffix == ".png")
		res[name+suffix] = video.LoadImage(path, r);
	else if(filesuffix == ".ttf")
		res[name+suffix] = video.LoadFont(path, r.x);
	else
		logger.Error(1, "Unsupported file type %s.",
				filesuffix.c_str());
}


void
Resources::LoadFile(std::string const& name, std::string const& path)
{
	LoadFile(name, path, Rect(0, 0, 0, 0), "");
}
