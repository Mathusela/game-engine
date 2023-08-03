#version 330

layout(location = 0) in vec3 vPos;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

out vec3 fPos;

void main() {
	fPos = vec3(world * vec4(vPos, 1.0));
	gl_Position = projection * view * world * vec4(vPos, 1.0);
}