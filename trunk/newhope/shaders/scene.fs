#version 150

struct AmbientLight {
    vec3 color;
    float intensity;
};

struct DiffuseLight {
    vec3 color;
    float intensity;
    vec3 direction;
};

in vec3 normal;
in vec3 f_material_color;
in vec4 st_shadow;

uniform AmbientLight amb_light;
uniform DiffuseLight dif_light;
uniform bool smooth_model;
uniform sampler2D depth_map;

out vec4 finalColor;

const float epsilon = 0.0042;

bool eval_shadow(vec2 texcoods) {
    float shadow = texture(depth_map, texcoods).r;
    if(shadow + epsilon < st_shadow.z) {
        return false;
    }
    return true;
}

void main() {
    // ambient light
    vec4 amb_color = vec4(amb_light.color, 1.0f) * amb_light.intensity;

    // diffuse light
    vec4 diffuse_color;
    vec3 ec_normal = normal;
    if(!smooth_model) {
        ec_normal = normalize(cross(dFdx(normal), dFdy(normal)));
    }
    float diffuse_factor = dot(normalize(ec_normal), -dif_light.direction);
    if(diffuse_factor > 0) {
        diffuse_color = vec4(dif_light.color, 1.0f) * dif_light.intensity * diffuse_factor;
    } else {
        diffuse_color = vec4(0, 0, 0, 0);
    }

    // calculate final color
	finalColor = vec4(f_material_color, 1.0) * (amb_color + (eval_shadow(st_shadow.xy) ? diffuse_color : vec4(0,0,0,0)));
}

// vim: ts=4:sw=4:sts=4:expandtab
