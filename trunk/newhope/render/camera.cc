#include "render/camera.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render/renderengine.h"

namespace render {

Camera::Camera(RenderEngine const& engine)
    : engine(engine)
{
}


void 
Camera::setPosition(float x, float y, float z)
{
    position = { x, y, z };
}


void 
Camera::LookAt(float x, float y, float z)
{
    lookat = { x, y, z };
}

glm::mat4 
Camera::Projection() const
{
    return glm::perspective(45.0f, engine.ScreenRatio(), 1.0f, 100.0f); // TODO - 0.1f
}


glm::mat4 
Camera::View() const
{
    return glm::lookAt( 
        position,
        lookat,
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}


}

// vim: ts=4:sw=4:sts=4:expandtab
