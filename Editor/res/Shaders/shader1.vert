#version 450

layout(location = 0) in vec3 position;

layout(location = 0) out vec3 fragColor;

vec3 colors[4] = vec3[](
	vec3(1.0, 0.0, 0.0),
	vec3(0.0, 1.0, 0.0),
	vec3(0.0, 0.0, 1.0),
	vec3(1.0, 1.0, 1.0)
);

void main() {
	gl_Position = vec4(position, 1.0);
	fragColor = colors[gl_VertexIndex];
}
