#version 450

layout(location = 0) in vec4 color;
layout(location = 1) in vec2 textureCoordinates;

layout(set = 1, binding = 0) uniform sampler2D textureSampler;

layout(location = 0) out vec4 outColor;

void main() {
	// Maybe add color input to have an effect on the resulting texture with color blending
	outColor = texture(textureSampler, textureCoordinates);
}