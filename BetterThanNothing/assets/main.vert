#version 450

layout(binding = 0) uniform UniformBufferObject {
	mat4 m_Model;
	mat4 m_View;
	mat4 m_Projection;
} ubo;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
	gl_Position = ubo.m_Projection * ubo.m_View * ubo.m_Model * vec4(inPosition, 0.0, 1.0);
	fragColor = inColor;
	fragTexCoord = inTexCoord;
}
