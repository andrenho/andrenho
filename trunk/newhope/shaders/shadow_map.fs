#version 150

struct DiffuseLight {
    vec3 color;
    float intensity;
    vec3 direction;
};

uniform DiffuseLight amb_light;
uniform DiffuseLight dif_light;

out vec4 final_color;

void main() {
    // diffuse light
    float diffuse_factor = dot(vec3(0,0,0), dif_light.direction);
    vec4 diffuse_color = vec4(dif_light.color, 1.0f) * dif_light.intensity * diffuse_factor + vec4(amb_light.color, 1.0f) * amb_light.intensity;

    // calculate final color
	final_color = diffuse_color;
}

// vim: ts=4:sw=4:sts=4:expandtab
