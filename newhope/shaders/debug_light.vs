#version 150

in vec2 vert;
in vec2 v_uv;

out vec2 uv;

void main()
{
    gl_Position = vec4(vert, 0, 1);
    uv = v_uv;
}

// vim: ts=4:sw=4:sts=4:expandtab
