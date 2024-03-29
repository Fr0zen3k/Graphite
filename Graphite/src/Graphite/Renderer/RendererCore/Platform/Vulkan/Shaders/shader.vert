#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 textureCoordinates;
layout(location = 3) in vec3 normal;

layout(set = 0, binding = 0) uniform ViewProjection {
	mat4 view;
	mat4 projection;
} viewProjection;

layout(push_constant) uniform PushData {
	mat4 modelMatrix;
	mat4 normalMatrix;
	vec4 ambientColor;
	vec4 specularColor;
	vec4 lightPosition;
	vec4 phongData;
} pushData;

layout(location = 0) out vec2 fragTextureCoordinates;
layout(location = 1) out vec3 normalInterpolation;
layout(location = 2) out vec3 vertexPosition;
layout(location = 3) out vec3 vertColor;

void main() {
	vec4 vertPos = viewProjection.view * pushData.modelMatrix * vec4(position, 1.0);

	fragTextureCoordinates = textureCoordinates;
	normalInterpolation = normal;
	vertexPosition = vec3(vertPos) / vertPos.w;
	vertColor = color;

	gl_Position = viewProjection.projection * vertPos;
}