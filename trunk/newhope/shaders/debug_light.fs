#version 150

in vec2 uv;

out vec4 color;

uniform sampler2D sampler;

void main()
{
    color = texture(sampler, uv);
}

// vim: ts=4:sw=4:sts=4:expandtab
