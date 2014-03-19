#version 150

out vec4 finalColor;
in vec3 normal;

struct AmbientLight {
    vec3 color;
    float intensity;
};
uniform AmbientLight amb_light;

struct DiffuseLight {
    vec3 color;
    float intensity;
    vec3 direction;
};
uniform DiffuseLight dif_light;

void main() {
    // ambient light
    vec4 amb_color = vec4(amb_light.color, 1.0f) * amb_light.intensity;

    // diffuse light
    vec4 diffuse_color;
    float diffuse_factor = dot(normalize(normal), -dif_light.direction);
    if(diffuse_factor > 0) {
        diffuse_color = vec4(dif_light.color, 1.0f) * dif_light.intensity * diffuse_factor;
    } else {
        diffuse_color = vec4(0, 0, 0, 0);
    }

    // calculate final color
	finalColor = vec4(1.0, 1.0, 1.0, 1.0) * (amb_color + diffuse_color);
}

// vim: ts=4:sw=4:sts=4:expandtab
