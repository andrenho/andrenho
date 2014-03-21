#ifndef RENDER_OBJ_LOADER_H_
#define RENDER_OBJ_LOADER_H_

#include <glm/glm.hpp>

#include <string>
#include <map>
#include <vector>
using namespace std;

namespace render {

class OBJ_Loader {
public:
    void Load(string const& filename, class Object& obj);

private:
    void LoadMaterials(string const& filename);
    vector<string> Split(string const& s, char delim, vector<string>& elems) const;

    map<string, glm::vec3> colors;
};

}

#endif  // RENDER_OBJ_LOADER_H_

// vim: ts=4:sw=4:sts=4:expandtab
