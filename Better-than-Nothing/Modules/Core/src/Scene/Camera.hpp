#pragma once

namespace BetterThanNothing
{
	class Event;
	class KeyPressEvent;

	enum class CameraType
	{
		FirstPerson,
		// ThirdPerson,
		Free
	};

	/**
	 * @brief
	 * The Camera class is used to represent a camera in the 3D world,
	 * to calculate the View and Projection matrices,
	 * and to move the camera around.
	 */
	class Camera
	{
	protected:

		/**
		 * @brief The type of the camera.
		 */
		CameraType m_Type;

		/**
		 * @brief The position of the camera.
		*/
		glm::vec3 m_Position;

		/**
		 * @brief The front vector of the camera.
		*/
		glm::vec3 m_Front;

		/**
		 * @brief The up vector of the camera.
		*/
		glm::vec3 m_Up;

		/**
		 * @brief The right vector of the camera.
		 */
		glm::vec3 m_Right;

		/**
		 * @brief The up vector of the world.
		*/
		glm::vec3 m_WorldUp;

		/**
		 * @brief The yaw of the camera.
		*/
		f32 m_Yaw;

		/**
		 * @brief The pitch of the camera.
		*/
		f32 m_Pitch;

		/**
		 * @brief The field of view of the camera.
		 * @note It is in degrees.
		*/
		f32 m_Fov;

		/**
		 * @brief The near plane of the camera.
		 * @note It is the closest plane that is perpendicular to the camera's front vector.
		*/
		f32 m_ZNear;

		/**
		 * @brief The far plane of the camera.
		 * @note It is the farthest plane that is perpendicular to the camera's front vector.
		*/
		f32 m_ZFar;

		/**
		 * @brief The view matrix of the camera.
		 * @note It transforms the world to the camera's view.
		*/
		glm::mat4 m_ViewMatrix;

		/**
		 * @brief The projection matrix of the camera.
		 * @note It  transforms the camera's view to the screen.
		*/
		glm::mat4 m_ProjectionMatrix;

	public:
		/**
		 * @brief Construct a new Camera object.
		 *
		 * @param x The x position of the camera.
		 * @param y The y position of the camera.
		 * @param z The z position of the camera.
		 * @param yaw The yaw of the camera.
		 * @param pitch The pitch of the camera.
		 *
		 * @note Also calculate all the camera vectors (front, right, up).
		 */
		Camera(CameraType type, f32 x, f32 y, f32 z, f64 yaw, f64 pitch);

		/**
		 * @brief Destroy the Camera object.
		 */
		~Camera();

		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;
		Camera(Camera&&) = delete;
		Camera& operator=(Camera&&) = delete;

		/**
		 * @brief Set the perspective projection of the camera.
		 *
		 * @param fov The field of view of the camera.
		 * @param zNear The near plane of the camera.
		 * @param zFar The far plane of the camera.
		 *
		 * @note The field of view is in degrees.
		 * @note You have to call this function before calling Update().
		 */
		void SetPerspectiveProjection(f32 fov, f32 zNear, f32 zFar);

		/**
		 * @brief Called every frame.
		 * @param deltatime The time between the current frame and the last frame.
		 */
		void Update(Window* window, f32 deltatime);

		/**
		 * @brief Called when an Event is received.
		 * @param event A pointer to the Event object received.
		*/
		void OnEvent(Event* pEvent);

	private:
		/**
		 * @brief Calculate the camera vectors (front, right, up).
		 */
		void CalculateCameraVectors();

		/**
		 * @brief Calculate the view matrix.
		 */
		void CalculateViewMatrix();

		/**
		 * @brief Calculate the projection matrix.
		 */
		void CalculateProjectionMatrix(Window* window);

	public:
		/**
		 * @brief Get the position of the camera.
		 * @return The position vector of the camera.
		 */
		glm::vec3& GetPosition() { return m_Position; }

		/**
		 * @brief Get the front vector of the camera.
		 * @return The front vector of the camera.
		 */
		glm::vec3& GetFront() { return m_Front; }

		/**
		 * @brief Get the up vector of the camera.
		 * @return The up vector of the camera.
		 */
		glm::vec3& GetUp() { return m_Up; }

		/**
		 * @brief Get the right vector of the camera.
		 * @return The right vector of the camera.
		 */
		glm::vec3& GetRight() { return m_Right; }

		/**
		 * @brief Get the up vector of the world.
		 * @return The up vector of the world.
		 */
		glm::vec3& GetWorldUp() { return m_WorldUp; }

		/**
		 * @brief Get the yaw of the camera.
		 * @return The yaw of the camera.
		 */
		f32 GetYaw() { return m_Yaw; }

		/**
		 * @brief Get the pitch of the camera.
		 * @return The pitch of the camera.
		 */
		f32 GetPitch() { return m_Pitch; }

		/**
		 * @brief Get the field of view of the camera.
		 * @return The field of view of the camera.
		 */
		f32 GetFov() { return m_Fov; }

		/**
		 * @brief Get the near plane of the camera.
		 * @return The near plane of the camera.
		 */
		f32 GetZNear() { return m_ZNear; }

		/**
		 * @brief Get the far plane of the camera.
		 * @return The far plane of the camera.
		 */
		f32 GetZFar() { return m_ZFar; }

		/**
		 * @brief Get the view matrix of the camera.
		 * @return The view matrix of the camera.
		 */
		glm::mat4& GetViewMatrix() { return m_ViewMatrix; }

		/**
		 * @brief Get the projection matrix of the camera.
		 * @return The projection matrix of the camera.
		 */
		glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
	};
};
