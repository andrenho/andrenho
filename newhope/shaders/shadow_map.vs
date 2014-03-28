#version 150

uniform mat4 wvp;

in vec3 vert;

void main() {
    gl_Position = wvp * vec4(vert, 1);
}

// vim: ts=4:sw=4:sts=4:expandtab
