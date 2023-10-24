#pragma once

namespace BetterThanNothing
{
	struct UniformBufferObject
	{
		alignas(16) glm::mat4	m_Model;
		alignas(16) glm::mat4	m_View;
		alignas(16) glm::mat4	m_Projection;
	};
};
