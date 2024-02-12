#version 450

struct DirectionalLight {
	vec3 color;
	vec3 direction;
};

struct PointLight {
	vec3 color;
	vec3 position;

	float constant;
	float linear;
	float quadratic;
};

struct Material {
	float ambient;
	float diffuse;
	float specular;
	float shininess;
};

layout(binding = 0) uniform GlobalUniforms {
	mat4 view;
	mat4 projection;
	vec3 cameraPosition;

	DirectionalLight directionalLight;
	PointLight pointLights[4];
} globalUniforms;


layout(binding = 1) uniform DynamicUniforms {
	mat4 model;
	Material material;
} dynamicUniforms;

layout(binding = 2) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragPosition;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
	vec3 lightDirection = globalUniforms.directionalLight.direction;

	// ambient light
	float ambient = dynamicUniforms.material.ambient;

	// diffuse light
	vec3 unitNormal = normalize(fragNormal);
	vec3 unitLightDirection = normalize(lightDirection);
	float diffuse = dynamicUniforms.material.diffuse * max(dot(unitNormal, unitLightDirection), 0.0);

	// specular light
	vec3 viewDirection = normalize(globalUniforms.cameraPosition - fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, unitNormal);
	float specular = dynamicUniforms.material.specular * pow(max(dot(viewDirection, reflectDirection), 0.0), dynamicUniforms.material.shininess);

	float brightness = max(ambient + diffuse + specular, 1.0);

	outColor = vec4(brightness * globalUniforms.directionalLight.color, 1.0) * texture(texSampler, fragTexCoord);
}
