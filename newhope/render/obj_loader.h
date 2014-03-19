#ifndef RENDER_OBJ_LOADER_H_
#define RENDER_OBJ_LOADER_H_

#include <string>
#include <vector>
using namespace std;

namespace render {

class OBJ_Loader {
public:
    static void Load(string const& filename, class Object& obj);

private:
    static vector<string> Split(string const& s, char delim, vector<string>& elems);
};

}

#endif  // RENDER_OBJ_LOADER_H_

// vim: ts=4:sw=4:sts=4:expandtab
