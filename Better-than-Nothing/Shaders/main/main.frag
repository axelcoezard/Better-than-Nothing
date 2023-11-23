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
	mat4 model;
	mat4 view;
	mat4 projection;
	vec3 cameraPosition;

	Material material;
	DirectionalLight directionalLight;
	PointLight pointLights[4];
} ubo;

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragPosition;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
	vec3 lightDirection = ubo.directionalLight.direction;

	// ambient light
	float ambient = ubo.material.ambient;

	// diffuse light
	vec3 unitNormal = normalize(fragNormal);
	vec3 unitLightDirection = normalize(lightDirection);
	float diffuse = ubo.material.diffuse * max(dot(unitNormal, unitLightDirection), 0.0);

	// specular light
	vec3 viewDirection = normalize(ubo.cameraPosition - fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, unitNormal);
	float specular = ubo.material.specular * pow(max(dot(viewDirection, reflectDirection), 0.0), ubo.material.shininess);

	float brightness = max(ambient + diffuse + specular, 1.0);

	outColor = vec4(brightness * ubo.directionalLight.color, 1.0) * texture(texSampler, fragTexCoord);
}
