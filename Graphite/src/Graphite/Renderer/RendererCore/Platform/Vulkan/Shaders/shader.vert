#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 textureCoordinates;
layout(location = 3) in vec3 normal;

layout(set = 0, binding = 0) uniform ViewProjection {
	mat4 view;
	mat4 projection;
} viewProjection;

layout(push_constant) uniform Model {
	mat4 modelMatrix;
} model;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTextureCoordinates;

void main() {
	gl_Position = viewProjection.projection * viewProjection.view * model.modelMatrix * vec4(position, 1);

	fragColor = color;
	fragTextureCoordinates = textureCoordinates;
}