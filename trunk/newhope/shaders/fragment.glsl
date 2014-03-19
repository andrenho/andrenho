#version 150

out vec4 finalColor;

struct DirectionalLight {
    vec3 color;
    float intensity;
};
uniform DirectionalLight dir_light;

void main() {
	finalColor = vec4(1.0, 1.0, 1.0, 1.0) * vec4(dir_light.color, 1.0f) * dir_light.intensity;
}

// vim: ts=4:sw=4:sts=4:expandtab
