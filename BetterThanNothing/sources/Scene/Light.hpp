#pragma once

namespace BetterThanNothing
{
	struct Light
	{
		glm::vec3	m_Color;
		float		m_AmbientIntensity;
		float		m_DiffuseIntensity;
	};

	struct DirectionalLight : public Light
	{
		glm::vec3	m_Direction;
	};

	struct PointLight : public Light
	{
		glm::vec3	m_Position;
		float		m_Constant;
		float		m_Linear;
		float		m_Quadratic;
	};

	struct SpotLight : public PointLight
	{
		glm::vec3	m_Direction;
		float		m_CutOff;
		float		m_OuterCutOff;
	};
};
