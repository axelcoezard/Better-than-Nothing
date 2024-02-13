#version 450

layout(binding = 0) uniform GlobalUniforms {
	mat4 view;
	mat4 projection;
} globalUniforms;

layout(binding = 1) uniform DynamicUniforms {
	mat4 model;
} dynamicUniforms;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragPosition;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;

void main() {
	vec4 worldPosition = globalUniforms.view * dynamicUniforms.model * vec4(inPosition, 1.0);

	gl_Position = globalUniforms.projection * worldPosition;

	fragPosition = worldPosition.xyz;
	fragNormal = mat3(transpose(inverse(globalUniforms.view * dynamicUniforms.model))) * inNormal;
	fragTexCoord = inTexCoord;
}
