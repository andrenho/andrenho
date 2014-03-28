#version 150

uniform mat4 vp;
uniform mat4 model;
uniform mat4 shadow_vp;
uniform bool smooth_model;

in vec3 vert;
in vec3 normals;
in vec3 material_color;

out vec3 normal;
out vec3 f_material_color;
out vec4 st_shadow;

void main() {
    gl_Position = vp * model * vec4(vert, 1);
    if(smooth_model) {
        normal = (vec4(normals, 1)).xyz;
    } else {
        normal = (vec4(vert, 1)).xyz;
    }
    f_material_color = material_color;

    st_shadow = shadow_vp * model * vec4(vert, 1);
    st_shadow.xyz /= st_shadow.w;
    st_shadow.xyz += 1;
    st_shadow.xyz *= 0.5;
}

// vim: ts=4:sw=4:sts=4:expandtab
