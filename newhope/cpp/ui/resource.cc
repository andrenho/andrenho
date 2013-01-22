#include "ui/resource.h"

#include <cstdlib>
#include <sys/stat.h>
#include <iostream>
using namespace std;

#include "libs/graphiclibrary.h"
#include "ui/resource_list.h"
#include "util/logger.h"
#include "util/rect.h"

Resources::Resources(const GraphicLibrary& video)
	: video(video)
{
	for(const auto& res: reslist) {
		string filepath(FindFile(res.filename));

		if(res.suffix.empty()) {
			LoadFile(res.name, filepath);
		} else {
			for(unsigned int i(0); i<res.suffix.size(); i++) {
				LoadFile(res.name, filepath, res.r[i],
						res.suffix[i]);
			}
		}
		logger.Debug(filepath + " loaded.");
	}
}


Resources::~Resources()
{
	logger.Debug("Freeing resources.");
	for(auto it(res.begin()); it != res.end(); it++) {
		delete (*it).second;
	}
}


const string 
Resources::FindFile(const string& filename)
{
	string buf[2];
	buf[0] = string(DATADIR) + "/" + filename; // data dir
	buf[1] = string("data/") + filename;       // runs without install

	for(int i=0; i<2; i++) {
		struct stat b;
		if(stat(buf[i].c_str(), &b) == 0) {
			return buf[i];
		}
	}

	return "";
}


void
Resources::LoadFile(const string& name, const string& path, 
		const Rect& r, const string& suffix)
{
	size_t found(path.find_last_of('.'));
	string filesuffix(path.substr(found));
	if(filesuffix == ".png") {
		res[name+suffix] = video.LoadImage(path, r);
	} else if(filesuffix == ".ttf") {
		res[name+suffix] = video.LoadFont(path, r.x);
	} else {
		logger.Error(1, "Unsupported file type %s.", filesuffix.c_str());
	}
}


void
Resources::LoadFile(const string& name, const string& path)
{
	LoadFile(name, path, Rect(0, 0, 0, 0), "");
}
