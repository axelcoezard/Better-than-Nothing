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
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = max(dot(viewDir, reflectDir), 0.0);

	// combine results
	vec3 ambient = ubo.material.ambient;
	vec3 diffuse = ubo.material.diffuse * diff;
	vec3 specular = ubo.material.specular * spec;

	return (ambient + diffuse + specular) * light.color;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = max(dot(viewDir, reflectDir), 0.0);

	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
					light.quadratic * (distance * distance));

	// combine results
	vec3 ambient = ubo.material.ambient;
	vec3 diffuse =  ubo.material.diffuse * diff;
	vec3 specular = ubo.material.specular * spec;

	return (ambient + diffuse + specular) * attenuation * light.color;
}

void main()
{
	vec3 norm = normalize(fragNormal);
	vec3 viewDir = normalize(ubo.cameraPosition - fragPosition);

	// phase 1: Directional lighting
	vec3 result = CalcDirectionalLight(ubo.directionalLight, norm, viewDir);

	// phase 2: Point lights
	//for(int i = 0; i < 2; i++) {
	//	result += CalcPointLight(ubo.pointLights[i], norm, fragPosition, viewDir);
	//}

	outColor = vec4(result, 1.0) * texture(texSampler, fragTexCoord);
}
