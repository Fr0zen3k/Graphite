#version 450

layout(location = 0) in vec2 textureCoordinates;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 vertex;

layout(set = 1, binding = 0) uniform sampler2D textureSampler;

layout(push_constant) uniform PushData {
	mat4 modelMatrix;
	mat4 normalMatrix;
	vec4 ambientColor;
	vec4 specularColor;
	vec4 lightPosition;
	vec4 phongData;
} pushData;

layout(location = 0) out vec4 outColor;

void main() {
	float Ka = pushData.phongData.x;
	float Kd = pushData.phongData.y;
	float Ks = pushData.phongData.z;
	float shininess = pushData.phongData.w;

	vec3 light = vec3(pushData.lightPosition) / pushData.lightPosition.w;

	vec3 N = normalize(normal);
	vec3 L = normalize(light - vertex);

	float lambertian = max(dot(N, L), 0.0);
	float specular = 0.0;

	if(lambertian > 0.0) {
		vec3 vert = normalize(-vertex);
		vec3 reflection = reflect(-L, N);

		float specularAngle = max(dot(reflection, vert), 0.0);
		specular = pow(specularAngle, shininess);
	}

	vec3 diffuseColor = vec3(texture(textureSampler, textureCoordinates));
	vec3 ambientColor = vec3(pushData.ambientColor);
	vec3 specularColor = vec3(pushData.specularColor);

	outColor = vec4(Ka * ambientColor + Kd * diffuseColor + Ks * specular * specularColor, 1.0);
}