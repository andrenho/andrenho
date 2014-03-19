#version 150

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 model;

in vec3 vert;
in vec3 normals;
out vec3 normal;
out vec3 ec_pos;

void main() {
    gl_Position = projection * camera * model * vec4(vert, 1);
    normal = (model * vec4(normals, 1)).xyz;
    ec_pos = (model * vec4(vert, 1)).xyz;
}

// vim: ts=4:sw=4:sts=4:expandtab
