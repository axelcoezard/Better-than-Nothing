#version 450

layout(binding = 0) uniform UniformBufferObject {
	mat4 m_Model;
	mat4 m_View;
	mat4 m_Projection;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragPosition;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;

void main() {
	vec4 worldPosition = ubo.m_View * ubo.m_Model * vec4(inPosition, 1.0);
	vec4 worldNormal = ubo.m_View * ubo.m_Model * vec4(inNormal, 0.0);

	gl_Position = ubo.m_Projection * worldPosition;

	fragPosition = worldPosition.xyz;
	fragNormal = worldNormal.xyz;
	fragTexCoord = inTexCoord;
}
