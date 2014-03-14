#ifndef RENDER_BOX_H_
#define RENDER_BOX_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include <array>
using namespace std;

namespace render {

class Box {
public:
    Box();

	Box(const Box&) = delete;
    Box& operator=(const Box&) = delete;

    int NumTriangles() const { return 6*2*3; }

    const float vertexData[180];
};

}

#endif  // RENDER_BOX_H_

// vim: ts=4:sw=4:sts=4:expandtab
