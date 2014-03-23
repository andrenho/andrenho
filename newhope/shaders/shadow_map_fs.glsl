#version 150

out float fragmentdepth;

void main() {
    fragmentdepth = gl_FragCoord.z;
}

// vim: ts=4:sw=4:sts=4:expandtab
