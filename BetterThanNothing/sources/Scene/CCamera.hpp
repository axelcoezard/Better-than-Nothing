#pragma once

namespace BetterThanNothing
{
	class CCamera
	{
	private:
		glm::vec3				m_Position;
		glm::vec3				m_Rotation;

		glm::vec3				m_Front;
		glm::vec3				m_Up;

		glm::mat4				m_ViewMatrix;
		glm::mat4				m_ProjectionMatrix;
	public:
								CCamera();
								~CCamera();

								CCamera(const CCamera&) = delete;
		CCamera&				operator=(const CCamera&) = delete;
								CCamera(CCamera&&) = delete;
		CCamera&				operator=(CCamera&&) = delete;

	public:
		void					SetPerspectiveProjection(float fov, float zNear, float zFar);

		void					Move(float x, float y, float z);
		void					Rotate(float pitch, float yaw, float roll);

	public:
		glm::vec3&				GetPosition()			{ return m_Position; }
		glm::vec3&				GetRotation()			{ return m_Rotation; }
		glm::vec3&				GetFront()				{ return m_Front; }
		glm::vec3&				GetUp()					{ return m_Up; }
		glm::mat4&				GetViewMatrix()			{ return m_ViewMatrix; }
		glm::mat4&				GetProjectionMatrix()	{ return m_ProjectionMatrix; }
	};
};
