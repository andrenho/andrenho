#ifndef UI_CHARENGINE_H
#define UI_CHARENGINE_H

class World;
class GraphicLibrary;
class Resources;

class CharEngine {
public:
	CharEngine(World const& world, GraphicLibrary const& video, 
			Resources const& res)
		: world(world), video(video), res(res) { }
	~CharEngine();

private:
	World const& world;
	GraphicLibrary const& video;
	Resources const& res;
};

#endif
