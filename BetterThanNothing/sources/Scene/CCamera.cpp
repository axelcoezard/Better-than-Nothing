#include "Scene/CCamera.hpp"
#include "Handlers/CInput.hpp"

namespace BetterThanNothing
{
	CCamera::CCamera(float x, float y, float z, double yaw, double pitch)
	{
		m_Position = glm::vec3(x, y, z);
		m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		m_Yaw = yaw;
		m_Pitch = pitch;

		CalculateCameraVectors();
	}

	CCamera::~CCamera()
	{

	}

	void CCamera::SetPerspectiveProjection(float fov, float zNear, float zFar)
	{
		m_Fov = fov;
		m_ZNear = zNear;
		m_ZFar = zFar;
	}

	void CCamera::Update()
	{
		static float lastMouseX = 0;
		static float lastMouseY = 0;

		float velocity = 0.01f;
		float sensitivity = 0.001f;

		// compute keyboard inputs
		if (CInput::IsKeyPressed(GLFW_KEY_W)) {
			m_Position += velocity * m_Front;
		}
		if (CInput::IsKeyPressed(GLFW_KEY_S)) {
			m_Position -= velocity * m_Front;
		}
		if (CInput::IsKeyPressed(GLFW_KEY_A)) {
			m_Position -= velocity * m_Right;
		}
		if (CInput::IsKeyPressed(GLFW_KEY_D)) {
			m_Position += velocity * m_Right;
		}
		if (CInput::IsKeyPressed(GLFW_KEY_SPACE)) {
			m_Position += velocity * m_Up;
		}
		if (CInput::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
			m_Position -= velocity * m_Up;
		}

		// compute mouse inputs
		if (CInput::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			glm::vec2 mousePosition = CInput::GetMousePosition();

			glm::vec2 offset = glm::vec2(mousePosition.x - lastMouseX, lastMouseY - mousePosition.y);
			lastMouseX = mousePosition.x;
			lastMouseY = mousePosition.y;

			offset *= sensitivity;

			m_Yaw += offset.x;
			m_Pitch += offset.y;

			if (m_Pitch > 89.0f) {
				m_Pitch = 89.0f;
			}
			if (m_Pitch < -89.0f) {
				m_Pitch = -89.0f;
			}

			CalculateCameraVectors();
		}

		CalculateViewMatrix();
		CalculateProjectionMatrix();

		std::cout << "Camera position: " << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << std::endl;
		std::cout << "Camera rotation"	<< m_Yaw << ", " << m_Pitch << std::endl;
	}

	void CCamera::CalculateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void CCamera::CalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void CCamera::CalculateProjectionMatrix()
	{
		float aspectRatio = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;

		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), aspectRatio, m_ZNear, m_ZFar);
		m_ProjectionMatrix[1][1] *= -1;
	}
};
