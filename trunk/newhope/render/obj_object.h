#ifndef RENDER_OBJ_OBJECT_H_
#define RENDER_OBJ_OBJECT_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render/object.h"

#include <array>
#include <string>
#include <vector>
using namespace std;

namespace render {

class OBJ_Object : public Object {
public:
    OBJ_Object(string const& filename);
    void Render() const;

	OBJ_Object(const OBJ_Object&) = delete;
    OBJ_Object& operator=(const OBJ_Object&) = delete;

private:
    void LoadOBJ(string const& filename);
    void SetupObject();

    // TODO - this could go into a generic class?
    vector<string> Split(string const& s, char delim, vector<string>& elems) const;

    vector<glm::vec3> vertices = {};
    vector<array<int,3>> triangles = {};
};

}

#endif  // RENDER_OBJ_OBJECT_H_

// vim: ts=4:sw=4:sts=4:expandtab
