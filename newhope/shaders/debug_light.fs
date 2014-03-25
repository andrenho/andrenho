#version 150

in vec2 uv;

out vec4 color;

uniform sampler2D sampler;

void main()
{
    color = texture(sampler, uv);
    //color = vec4(uv, 0, 0);
}

// vim: ts=4:sw=4:sts=4:expandtab
