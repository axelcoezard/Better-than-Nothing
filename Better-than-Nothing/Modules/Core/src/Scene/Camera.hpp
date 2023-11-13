#pragma once

namespace BetterThanNothing
{
	class Event;
	class KeyPressEvent;

	class Camera
	{
	protected:
		glm::vec3				m_Position;

		glm::vec3				m_Front;
		glm::vec3				m_Up;
		glm::vec3				m_Right;
		glm::vec3				m_WorldUp;

		f32					m_Yaw;
		f32					m_Pitch;

		f32					m_Fov;
		f32					m_ZNear;
		f32					m_ZFar;

		glm::mat4				m_ViewMatrix;
		glm::mat4				m_ProjectionMatrix;
	public:
								Camera(f32 x, f32 y, f32 z, f64 yaw, f64 pitch);
								~Camera();

								Camera(const Camera&) = delete;
		Camera&					operator=(const Camera&) = delete;
								Camera(Camera&&) = delete;
		Camera&					operator=(Camera&&) = delete;

	public:
		void					SetPerspectiveProjection(f32 fov, f32 zNear, f32 zFar);

		void 					Update(f32 deltatime);
		void					OnEvent(Event* pEvent);

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
		f32					GetYaw()				{ return m_Yaw; }
		f32					GetPitch()				{ return m_Pitch; }
		f32					GetFov()				{ return m_Fov; }
		f32					GetZNear()				{ return m_ZNear; }
		f32					GetZFar()				{ return m_ZFar; }
		glm::mat4&				GetViewMatrix()			{ return m_ViewMatrix; }
		glm::mat4&				GetProjectionMatrix()	{ return m_ProjectionMatrix; }
	};
};
