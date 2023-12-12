#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Camera::Camera(f32 x, f32 y, f32 z, f64 yaw, f64 pitch)
	{
		m_Position = glm::vec3(x, y, z);
		m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		m_Yaw = yaw;
		m_Pitch = pitch;

		CalculateCameraVectors();
	}

	Camera::~Camera()
	{

	}

	void Camera::SetPerspectiveProjection(f32 fov, f32 zNear, f32 zFar)
	{
		m_Fov = fov;
		m_ZNear = zNear;
		m_ZFar = zFar;
	}

	void Camera::Update(Window* window, f32 deltatime)
	{
		static bool firstMouse = true;
		static f32 lastMouseX = 0;
		static f32 lastMouseY = 0;

		if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
			return;
		}

		f32 velocity = 100.0f * deltatime;
		f32 sensitivity = 10.0f * deltatime;

		// compute keyboard inputs
		glm::vec3 movement = glm::vec3(0.0f);
		if (Input::IsKeyPressed(GLFW_KEY_W)) {
			movement += m_Front * velocity;
		}
		if (Input::IsKeyPressed(GLFW_KEY_S)) {
			movement -= m_Front * velocity;
		}
		if (Input::IsKeyPressed(GLFW_KEY_A)) {
			movement -= m_Right * velocity;
		}
		if (Input::IsKeyPressed(GLFW_KEY_D)) {
			movement += m_Right * velocity;
		}
		if (Input::IsKeyPressed(GLFW_KEY_SPACE)) {
			movement += m_Up * velocity;
		}
		if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
			movement -= m_Up * velocity;
		}

		m_Position += movement;

		// compute mouse inputs
		if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			glm::vec2 mousePosition = Input::GetMousePosition();

			if (firstMouse) {
				lastMouseX = mousePosition.x;
				lastMouseY = mousePosition.y;
				firstMouse = false;
			}

			glm::vec2 offset = glm::vec2(mousePosition.x - lastMouseX, lastMouseY - mousePosition.y);
			lastMouseX = mousePosition.x;
			lastMouseY = mousePosition.y;

			offset *= sensitivity;

			m_Yaw = glm::mod(m_Yaw + offset.x, 360.0f);
			m_Pitch += offset.y;

			if (m_Pitch > 89.0f) {
				m_Pitch = 89.0f;
			}
			if (m_Pitch < -89.0f) {
				m_Pitch = -89.0f;
			}

			CalculateCameraVectors();
		} else {
			firstMouse = true;
		}

		CalculateViewMatrix();
		CalculateProjectionMatrix(window);
	}

	void Camera::OnEvent(Event* pEvent)
	{
		(void) pEvent;
	}

	void Camera::CalculateCameraVectors()
	{
		glm::vec3 front;
		front.x = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = -1 * cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void Camera::CalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::CalculateProjectionMatrix(Window* window)
	{
		f32 aspectRatio = (f32) window->GetWidth() / (f32) window->GetHeight();

		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), aspectRatio, m_ZNear, m_ZFar);
		m_ProjectionMatrix[1][1] *= -1;
	}
};
