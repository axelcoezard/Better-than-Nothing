#version 450

struct DirectionalLight {
	vec3 color;

	float ambient;
	float diffuse;
	float specular;

	vec3 position;
};

struct PointLight {
	vec3 color;

	float ambient;
	float diffuse;
	float specular;

	vec3 position;

	float constant;
	float linear;
	float quadratic;
};

layout(binding = 0) uniform GlobalUniforms {
	mat4 model;
	mat4 view;
	mat4 projection;
	vec3 cameraPosition;

	DirectionalLight directionalLight;
	PointLight pointLight[4];
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragPosition;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;

void main() {
	vec4 worldPosition = ubo.view * ubo.model * vec4(inPosition, 1.0);
	vec4 worldNormal = ubo.view * ubo.model * vec4(inNormal, 0.0);

	gl_Position = ubo.projection * worldPosition;

	fragPosition = worldPosition.xyz;
	fragNormal = worldNormal.xyz;
	fragTexCoord = inTexCoord;
}
