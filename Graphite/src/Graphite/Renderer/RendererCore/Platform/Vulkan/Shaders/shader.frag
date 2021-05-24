#version 450

layout(location = 0) in vec2 textureCoordinates;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec3 vertex;

layout(set = 1, binding = 0) uniform sampler2D textureSampler;

layout(push_constant) uniform PushData {
	mat4 modelMatrix;
	mat4 normalMatrix;
	vec3 ambientColor;
	vec3 specularColor;
	vec3 lightPosition;
	float Ka;
	float Kd;
	float Ks;
	float shinyCoef;
} pushData;

layout(location = 0) out vec4 outColor;

void main() {
	vec3 N = normalize(normal);
	vec3 L = normalize(pushData.lightPosition - vertex);

	float lambertian = max(dot(N, L), 0.0);
	float specular = 0.0;

	if(lambertian > 0.0) {
		vec3 vert = normalize(-vertex);
		vec3 reflection = reflect(-L, N);

		float specularAngle = max(dot(reflection, vert), 0.0);
		specular = pow(specularAngle, pushData.shinyCoef);
	}

	vec3 diffuseColor = vec3(texture(textureSampler, textureCoordinates));

	outColor = vec4(pushData.Ka * pushData.ambientColor + pushData.Kd * diffuseColor + pushData.Ks * specular * pushData.specularColor, 1.0);
}