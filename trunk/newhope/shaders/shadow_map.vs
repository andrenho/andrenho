#version 150

uniform mat4 wvp;
uniform bool s;

in vec3 vert;

out vec3 n;

void main() {
    if(s) { n = vec3(1,1,1); } // TODO 
    gl_Position = wvp * vec4(vert, 1);
}

// vim: ts=4:sw=4:sts=4:expandtab
