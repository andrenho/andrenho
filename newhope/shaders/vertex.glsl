#version 150

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 model;

in vec3 vert;
in vec3 normals;

void main() {
    gl_Position = projection * camera * model * vec4(vert, 1);
}

// vim: ts=4:sw=4:sts=4:expandtab
