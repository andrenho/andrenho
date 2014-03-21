#version 150

uniform mat4 wvp;
uniform bool smooth_model;

in vec3 vert;
in vec3 normals;
in vec3 material_color;

out vec3 normal;
out vec3 f_material_color;

void main() {
    gl_Position = wvp * vec4(vert, 1);
    if(smooth_model) {
        normal = (vec4(normals, 1)).xyz;
    } else {
        normal = (vec4(vert, 1)).xyz;
    }
    f_material_color = material_color;
}

// vim: ts=4:sw=4:sts=4:expandtab
