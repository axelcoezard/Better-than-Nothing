#version 450

layout(binding = 0) uniform GlobalUniforms {
	mat4 model;
	mat4 view;
	mat4 projection;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragPosition;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;

void main() {
	vec4 worldPosition = ubo.view * ubo.model * vec4(inPosition, 1.0);

	gl_Position = ubo.projection * worldPosition;

	fragPosition = worldPosition.xyz;
	fragNormal = mat3(transpose(inverse(ubo.view * ubo.model))) * inNormal;
	fragTexCoord = inTexCoord;
}
