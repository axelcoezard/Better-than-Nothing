#pragma once

namespace BetterThanNothing
{
	class Camera
	{
	private:
		glm::vec3				m_Position;

		glm::vec3				m_Front;
		glm::vec3				m_Up;
		glm::vec3				m_Right;
		glm::vec3				m_WorldUp;

		float					m_Yaw;
		float					m_Pitch;

		float					m_Fov;
		float					m_ZNear;
		float					m_ZFar;

		glm::mat4				m_ViewMatrix;
		glm::mat4				m_ProjectionMatrix;
	public:
								Camera(float x, float y, float z, double yaw, double pitch);
								~Camera();

								Camera(const Camera&) = delete;
		Camera&				operator=(const Camera&) = delete;
								Camera(Camera&&) = delete;
		Camera&				operator=(Camera&&) = delete;

	public:
		void					SetPerspectiveProjection(float fov, float zNear, float zFar);

		void 					Update(float deltatime);

	private:
		void					CalculateCameraVectors();
		void					CalculateViewMatrix();
		void					CalculateProjectionMatrix();

	public:
		glm::vec3&				GetPosition()			{ return m_Position; }
		glm::vec3&				GetFront()				{ return m_Front; }
		glm::vec3&				GetUp()					{ return m_Up; }
		glm::vec3&				GetRight()				{ return m_Right; }
		glm::vec3&				GetWorldUp()			{ return m_WorldUp; }
		float					GetYaw()				{ return m_Yaw; }
		float					GetPitch()				{ return m_Pitch; }
		float					GetFov()				{ return m_Fov; }
		float					GetZNear()				{ return m_ZNear; }
		float					GetZFar()				{ return m_ZFar; }
		glm::mat4&				GetViewMatrix()			{ return m_ViewMatrix; }
		glm::mat4&				GetProjectionMatrix()	{ return m_ProjectionMatrix; }
	};
};
