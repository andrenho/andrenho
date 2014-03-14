#version 150

in vec3 position;
uniform mat4 MVP;

void main() {
	vec4 v = vec4(position, 1);
	gl_Position = MVP * v;

	//gl_Position = vec4(position, 1);
}
