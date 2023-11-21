#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragPosition;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 fragLightDirection;

layout(location = 0) out vec4 outColor;

void main() {
	vec3 lightDirection = fragLightDirection;
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	float ambient  = 0.5;

	// diffuse light
	vec3 unitNormal = normalize(fragNormal);
	vec3 unitLightDirection = normalize(lightDirection);
	float diffuse = 0.1 * max(dot(unitNormal, unitLightDirection), 0.0);

	// specular light
	vec3 viewDirection = normalize(-fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, unitNormal);
	float specular = 0.05 * max(dot(viewDirection, reflectDirection), 0.0);

	float brightness = max(ambient + diffuse + specular, 1.0);

	outColor = vec4(brightness * lightColor, 1.0) * texture(texSampler, fragTexCoord);
}
